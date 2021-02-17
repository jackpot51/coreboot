/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootblock_common.h>
#include <gpio.h>
#include "gpio.h"
#include <drivers/system76/dgpu/bootblock.c>

#include <commonlib/region.h>
#include <fmap.h>
#include <spi_flash.h>
#include <ec/system76/ec/system76_ec.h>

static int protect_region_by_name(const char * name) {
	int res;
	struct region region;

	res = fmap_locate_area(name, &region);
	if (res < 0) {
		printk(BIOS_ERR, "fmap_locate_area '%s' failed: %d\n", name, res);
		return res;
	}

	res = spi_flash_ctrlr_protect_region(
		boot_device_spi_flash(),
		&region,
		WRITE_PROTECT
	);
	if (res < 0) {
		printk(BIOS_ERR, "spi_flash_ctrlr_protect_region '%s' failed: %d\n", name, res);
		return res;
	}

	printk(BIOS_INFO, "protected '%s'\n", name);
	return 0;
}

void bootblock_mainboard_init(void) {
	gpio_configure_pads(early_gpio_table, ARRAY_SIZE(early_gpio_table));

	uint8_t state = SYSTEM76_EC_SECURITY_STATE_LOCK;
	if (system76_ec_security_get(&state) < 0) {
		printk(BIOS_INFO, "failed to get security state, assuming locked\n");
		state = SYSTEM76_EC_SECURITY_STATE_LOCK;
	}

	printk(BIOS_INFO, "security state: %d\n", state);
	if (state != SYSTEM76_EC_SECURITY_STATE_UNLOCK) {
		protect_region_by_name("SYSTEM76_RO");
	}

	dgpu_power_enable(1);
}
