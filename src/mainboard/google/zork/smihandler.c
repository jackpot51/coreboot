/* SPDX-License-Identifier: GPL-2.0-or-later */
#include <acpi/acpi.h>
#include <cpu/x86/smm.h>
#include <ec/google/chromeec/smm.h>
#include <gpio.h>
#include <soc/smi.h>
#include <variant/ec.h>
#include <variant/gpio.h>
#include <console/console.h>

void mainboard_smi_gpi(u32 gpi_sts)
{
	if (CONFIG(EC_GOOGLE_CHROMEEC))
		chromeec_smi_process_events();
}
void mainboard_smi_sleep(u8 slp_typ)
{
	if (CONFIG(EC_GOOGLE_CHROMEEC))
		chromeec_smi_sleep(slp_typ, MAINBOARD_EC_S3_WAKE_EVENTS,
					MAINBOARD_EC_S5_WAKE_EVENTS);
}
int mainboard_smi_apmc(u8 apmc)
{
	if (CONFIG(EC_GOOGLE_CHROMEEC))
		chromeec_smi_apmc(apmc, MAINBOARD_EC_SCI_EVENTS,
					MAINBOARD_EC_SMI_EVENTS);
	return 0;
}
