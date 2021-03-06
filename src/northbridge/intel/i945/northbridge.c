/* SPDX-License-Identifier: GPL-2.0-only */

#include <cbmem.h>
#include <commonlib/helpers.h>
#include <console/console.h>
#include <device/pci_ops.h>
#include <stdint.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <acpi/acpi.h>
#include <cpu/intel/smm_reloc.h>
#include "i945.h"

int decode_pcie_bar(u32 *const base, u32 *const len)
{
	*base = 0;
	*len = 0;

	struct device *dev = pcidev_on_root(0, 0);
	if (!dev)
		return 0;

	const u32 pciexbar_reg = pci_read_config32(dev, PCIEXBAR);

	if (!(pciexbar_reg & (1 << 0)))
		return 0;

	switch ((pciexbar_reg >> 1) & 3) {
	case 0: /* 256MB */
		*base = pciexbar_reg & (0x0f << 28);
		*len = 256 * MiB;
		return 1;
	case 1: /* 128M */
		*base = pciexbar_reg & (0x1f << 27);
		*len = 128 * MiB;
		return 1;
	case 2: /* 64M */
		*base = pciexbar_reg & (0x3f << 26);
		*len = 64 * MiB;
		return 1;
	}

	return 0;
}

static void mch_domain_read_resources(struct device *dev)
{
	uint32_t pci_tolm, tseg_sizek, cbmem_topk, delta_cbmem;
	uint8_t tolud;
	uint16_t reg16;
	unsigned long long tomk, tomk_stolen;
	uint64_t uma_memory_base = 0, uma_memory_size = 0;
	uint64_t tseg_memory_base = 0, tseg_memory_size = 0;
	struct device *const d0f0 = pcidev_on_root(0, 0);

	pci_domain_read_resources(dev);

	/* Can we find out how much memory we can use at most
	 * this way?
	 */
	pci_tolm = find_pci_tolm(dev->link_list);
	printk(BIOS_DEBUG, "pci_tolm: 0x%x\n", pci_tolm);

	tolud = pci_read_config8(d0f0, TOLUD);
	printk(BIOS_SPEW, "Top of Low Used DRAM: 0x%08x\n", tolud << 24);

	tomk = tolud << 14;
	tomk_stolen = tomk;

	/* Note: subtract IGD device and TSEG */
	reg16 = pci_read_config16(d0f0, GGC);
	if (!(reg16 & 2)) {
		printk(BIOS_DEBUG, "IGD decoded, subtracting ");
		int uma_size = decode_igd_memory_size((reg16 >> 4) & 7);

		printk(BIOS_DEBUG, "%dM UMA\n", uma_size >> 10);
		tomk_stolen -= uma_size;

		/* For reserving UMA memory in the memory map */
		uma_memory_base = tomk_stolen * 1024ULL;
		uma_memory_size = uma_size * 1024ULL;

		printk(BIOS_SPEW, "Base of stolen memory: 0x%08x\n",
		       (unsigned int)uma_memory_base);
	}

	tseg_sizek = decode_tseg_size(pci_read_config8(d0f0, ESMRAMC)) >> 10;
	printk(BIOS_DEBUG, "TSEG decoded, subtracting %dM\n", tseg_sizek >> 10);
	tomk_stolen -= tseg_sizek;
	tseg_memory_base = tomk_stolen * 1024ULL;
	tseg_memory_size = tseg_sizek * 1024ULL;

	/* cbmem_top can be shifted downwards due to alignment.
	   Mark the region between cbmem_top and tomk as unusable */
	cbmem_topk = ((uint32_t)cbmem_top() >> 10);
	delta_cbmem = tomk_stolen - cbmem_topk;
	tomk_stolen -= delta_cbmem;

	printk(BIOS_DEBUG, "Unused RAM between cbmem_top and TOM: 0x%xK\n", delta_cbmem);

	/* The following needs to be 2 lines, otherwise the second
	 * number is always 0
	 */
	printk(BIOS_INFO, "Available memory: %dK", (uint32_t)tomk_stolen);
	printk(BIOS_INFO, " (%dM)\n", (uint32_t)(tomk_stolen >> 10));

	/* Report the memory regions */
	ram_resource(dev, 3, 0, 640);
	ram_resource(dev, 4, 768, (tomk - 768));
	uma_resource(dev, 5, uma_memory_base >> 10, uma_memory_size >> 10);
	mmio_resource(dev, 6, tseg_memory_base >> 10, tseg_memory_size >> 10);
	uma_resource(dev, 7, cbmem_topk, delta_cbmem);
	/* legacy VGA memory */
	mmio_resource(dev, 8, 640, 768 - 640);
}

static void mch_domain_set_resources(struct device *dev)
{
	struct resource *res;

	for (res = dev->resource_list; res; res = res->next)
		report_resource_stored(dev, res, "");

	assign_resources(dev->link_list);
}

static const char *northbridge_acpi_name(const struct device *dev)
{
	if (dev->path.type == DEVICE_PATH_DOMAIN)
		return "PCI0";

	if (dev->path.type != DEVICE_PATH_PCI || dev->bus->secondary != 0)
		return NULL;

	switch (dev->path.pci.devfn) {
	case PCI_DEVFN(0, 0):
		return "MCHC";
	}

	return NULL;
}

void northbridge_write_smram(u8 smram)
{
	struct device *dev = pcidev_on_root(0, 0);

	if (dev == NULL)
		die("could not find pci 00:00.0!\n");

	pci_write_config8(dev, SMRAM, smram);
}

	/* TODO We could determine how many PCIe busses we need in
	 * the bar. For now that number is hardcoded to a max of 64.
	 */
static struct device_operations pci_domain_ops = {
	.read_resources   = mch_domain_read_resources,
	.set_resources    = mch_domain_set_resources,
	.scan_bus         = pci_domain_scan_bus,
	.acpi_name        = northbridge_acpi_name,
};

static void mc_read_resources(struct device *dev)
{
	u32 pcie_config_base, pcie_config_len;

	pci_dev_read_resources(dev);

	if (decode_pcie_bar(&pcie_config_base, &pcie_config_len)) {
		const int buses = pcie_config_len / MiB;
		struct resource *resource = new_resource(dev, PCIEXBAR);
		mmconf_resource_init(resource, pcie_config_base, buses);
	}
}

static struct device_operations mc_ops = {
	.read_resources   = mc_read_resources,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.acpi_fill_ssdt   = generate_cpu_entries,
	.ops_pci          = &pci_dev_ops_pci,
};

static const unsigned short pci_device_ids[] = {
	0x2770, /* desktop */
	0x27a0, 0x27ac, /* mobile */
	0 };

static const struct pci_driver mc_driver __pci_driver = {
	.ops    = &mc_ops,
	.vendor = PCI_VENDOR_ID_INTEL,
	.devices = pci_device_ids,
};

static struct device_operations cpu_bus_ops = {
	.read_resources   = noop_read_resources,
	.set_resources    = noop_set_resources,
	.init             = mp_cpu_bus_init,
};

static void enable_dev(struct device *dev)
{
	/* Set the operations if it is a special bus type */
	if (dev->path.type == DEVICE_PATH_DOMAIN)
		dev->ops = &pci_domain_ops;
	else if (dev->path.type == DEVICE_PATH_CPU_CLUSTER)
		dev->ops = &cpu_bus_ops;
}

struct chip_operations northbridge_intel_i945_ops = {
	CHIP_NAME("Intel i945 Northbridge")
	.enable_dev = enable_dev,
};
