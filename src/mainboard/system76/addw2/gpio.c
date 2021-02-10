/* SPDX-License-Identifier: GPL-2.0-only */

#include <mainboard/gpio.h>
#include <soc/gpe.h>
#include <soc/gpio.h>

static const struct pad_config gpio_table[] = {
	/* ------- GPIO Group GPD ------- */
	PAD_CFG_NF(GPD0, NONE, DEEP, NF1), // PM_BATLOW#
	PAD_CFG_NF(GPD1, NATIVE, DEEP, NF1), // AC_PRESENT
	PAD_NC(GPD2, NONE),
	PAD_CFG_NF(GPD3, UP_20K, DEEP, NF1), // PWR_BTN#
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1), // SUSB#_PCH
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1), // SUSC#_PCH
	PAD_NC(GPD6, NONE),
	PAD_CFG_GPI(GPD7, NONE, DEEP), // RESERVED STRAP
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1), // SUS_CLK
	PAD_NC(GPD9, NONE),
	PAD_NC(GPD10, NONE),
	PAD_NC(GPD11, NONE),

	/* ------- GPIO Group GPP_A ------- */
	PAD_NC(GPP_A0, NONE),
	PAD_CFG_NF(GPP_A1, NATIVE, DEEP, NF1), // LPC_AD0
	PAD_CFG_NF(GPP_A2, NATIVE, DEEP, NF1), // LPC_AD1
	PAD_CFG_NF(GPP_A3, NATIVE, DEEP, NF1), // LPC_AD2
	PAD_CFG_NF(GPP_A4, NATIVE, DEEP, NF1), // LPC_AD3
	PAD_CFG_NF(GPP_A5, NONE, DEEP, NF1), // LPC_FRAME#
	PAD_CFG_NF(GPP_A6, NONE, DEEP, NF1), // SERIRQ
	PAD_CFG_GPI(GPP_A7, NONE, DEEP), // SCI#_GPP_A7
	PAD_CFG_NF(GPP_A8, NONE, DEEP, NF1), // ECCLKRUN#
	PAD_CFG_NF(GPP_A9, DN_20K, DEEP, NF1), // PCLK_KBD
	PAD_NC(GPP_A10, DN_20K),
	PAD_NC(GPP_A11, UP_20K),
	PAD_NC(GPP_A12, NONE),
	PAD_CFG_NF(GPP_A13, NONE, DEEP, NF1), // SUSWARN#
	PAD_CFG_GPI_APIC(GPP_A14, NONE, PLTRST, EDGE_SINGLE, INVERT), // TCHPD_INT#
	PAD_CFG_NF(GPP_A15, UP_20K, DEEP, NF1), // SUS_PW_ACK#
	PAD_NC(GPP_A16, DN_20K),
	PAD_CFG_GPI(GPP_A17, NONE, DEEP), // AMP_TYPE_DET
	PAD_CFG_TERM_GPO(GPP_A18, 1, NONE, DEEP), // SB_BLON
	PAD_NC(GPP_A19, NONE),
	PAD_CFG_GPI(GPP_A20, NONE, DEEP), // PEX_WAKE#
	_PAD_CFG_STRUCT(GPP_A21, 0x46080100, 0x0000), // EAPD_MODE
	PAD_NC(GPP_A22, NONE),
	PAD_CFG_GPI(GPP_A23, NONE, DEEP), // DGPU_BOARD_ID

	/* ------- GPIO Group GPP_B ------- */
	_PAD_CFG_STRUCT(GPP_B0, 0x42080100, 0x3000), // TPM_PIRQ#
	PAD_NC(GPP_B1, NONE),
	PAD_NC(GPP_B2, NONE),
	PAD_CFG_TERM_GPO(GPP_B3, 1, NONE, DEEP), // BT_EN
	PAD_NC(GPP_B4, NONE),
	PAD_CFG_NF(GPP_B5, NONE, DEEP, NF1), // TBT_CLKREQ#
	PAD_NC(GPP_B6, NONE),
	PAD_CFG_TERM_GPO(GPP_B7, 0, NONE, DEEP), // GPP_B7_CR_RST#
	PAD_CFG_GPI(GPP_B8, NONE, DEEP), // GPP_B8_CR_WAKE#
	PAD_NC(GPP_B9, NONE),
	PAD_CFG_NF(GPP_B10, NONE, DEEP, NF1), // GLAN_CLKREQ#
	PAD_NC(GPP_B11, NONE),
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1), // SLP_S0#
	_PAD_CFG_STRUCT(GPP_B13, 0x44000601, 0x0000), // PLT_RST#
	PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1), // PCH_SPKR
	PAD_NC(GPP_B15, NONE),
	PAD_NC(GPP_B16, NONE),
	PAD_NC(GPP_B17, NONE),
	PAD_CFG_GPI(GPP_B18, NONE, DEEP), // NO REBOOT STRAP
	PAD_NC(GPP_B19, NONE),
	_PAD_CFG_STRUCT(GPP_B20, 0x42840101, 0x0000), // SMI#_GPP_B20
	PAD_NC(GPP_B21, NONE),
	PAD_CFG_GPI(GPP_B22, NONE, DEEP), // BIOS BOOT STRAP
	PAD_CFG_GPI(GPP_B23, NONE, DEEP), // DCI-OOB STRAP

	/* ------- GPIO Group GPP_C ------- */
	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1), // SMB_CLK
	PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1), // SMB_DATA
	PAD_CFG_GPI(GPP_C2, NONE, DEEP), // CNVI_WAKE#
	PAD_NC(GPP_C3, NONE),
	PAD_NC(GPP_C4, NONE),
	PAD_CFG_GPI(GPP_C5, NONE, DEEP), // WLAN_WAKEUP#
	PAD_NC(GPP_C6, NONE),
	PAD_NC(GPP_C7, NONE),
	PAD_NC(GPP_C8, NONE),
	PAD_CFG_GPI(GPP_C9, NONE, DEEP), // BOARD_ID1
	PAD_CFG_GPI(GPP_C10, NONE, DEEP), // BOARD_ID2
	PAD_CFG_GPI(GPP_C11, NONE, DEEP), // TBT_DET#
	PAD_CFG_GPI(GPP_C12, NONE, DEEP), // GC6_FB_EN_PCH
	PAD_CFG_GPI(GPP_C13, NONE, PLTRST), // TPM_DET
	PAD_CFG_TERM_GPO(GPP_C14, 1, NONE, DEEP), // GPU_EVENT#
	PAD_CFG_GPI(GPP_C15, NONE, DEEP),
	PAD_CFG_NF(GPP_C16, NONE, PLTRST, NF1), // TP_DAT_PCH_I2C0
	PAD_CFG_NF(GPP_C17, NONE, PLTRST, NF1), // TP_CLK_PCH_I2C0
	PAD_CFG_NF(GPP_C18, NONE, PLTRST, NF1), // I2C1_SDA
	PAD_CFG_NF(GPP_C19, NONE, PLTRST, NF1), // I2C1_SCL
	//PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1), // UART2_RXD
	//PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1), // UART2_TXD
	PAD_CFG_GPI(GPP_C22, NONE, DEEP), // UART2_RTS#
	PAD_CFG_GPI(GPP_C23, NONE, DEEP), // UART2_CTS#

	/* ------- GPIO Group GPP_D ------- */
	PAD_NC(GPP_D0, NONE),
	PAD_NC(GPP_D1, NONE),
	PAD_NC(GPP_D2, NONE),
	PAD_NC(GPP_D3, NONE),
	PAD_NC(GPP_D4, NONE),
	PAD_CFG_NF(GPP_D5, NONE, DEEP, NF3), // CNVI_RST#
	PAD_CFG_NF(GPP_D6, NONE, DEEP, NF3), // CNVI_CLKREQ
	PAD_NC(GPP_D7, NONE),
	PAD_NC(GPP_D8, NONE),
	PAD_NC(GPP_D9, NONE),
	PAD_NC(GPP_D10, NONE),
	PAD_NC(GPP_D11, NONE),
	PAD_NC(GPP_D12, NONE),
	PAD_NC(GPP_D13, NONE),
	PAD_NC(GPP_D14, NONE),
	PAD_NC(GPP_D15, NONE),
	PAD_NC(GPP_D16, NONE),
	PAD_NC(GPP_D17, NONE),
	PAD_NC(GPP_D18, NONE),
	PAD_NC(GPP_D19, NONE),
	PAD_NC(GPP_D20, NONE),
	PAD_NC(GPP_D21, NONE),
	PAD_NC(GPP_D22, NONE),
	PAD_NC(GPP_D23, NONE),

	/* ------- GPIO Group GPP_E ------- */
	PAD_NC(GPP_E0, NONE),
	PAD_CFG_NF(GPP_E1, UP_20K, DEEP, NF1), // SATAGP1
	PAD_NC(GPP_E2, NONE),
	PAD_NC(GPP_E3, NONE),
	PAD_NC(GPP_E4, NONE),
	PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1), // SATA_DEVSLP1
	PAD_NC(GPP_E6, NONE),
	PAD_NC(GPP_E7, NONE),
	PAD_CFG_NF(GPP_E8, NONE, DEEP, NF1), // SATAHDD_LED#
	PAD_NC(GPP_E9, NONE), // USB_OC0# (test point)
	PAD_NC(GPP_E10, NONE), // USB_OC1# (test point)
	PAD_NC(GPP_E11, NONE), // USB_OC2# (test point)
	PAD_NC(GPP_E12, NONE), // USB_OC3# (test point)

	/* ------- GPIO Group GPP_F ------- */
	PAD_NC(GPP_F0, NONE),
	PAD_NC(GPP_F1, NONE),
	PAD_NC(GPP_F2, NONE),
	PAD_CFG_TERM_GPO(GPP_F3, 0, NONE, DEEP), // GPP_F3_LAN_RST#
	PAD_CFG_GPI(GPP_F4, NONE, DEEP), // GPP_F4_TBT_RST#
	PAD_NC(GPP_F5, NONE),
	PAD_NC(GPP_F6, NONE),
	PAD_NC(GPP_F7, NONE),
	PAD_NC(GPP_F8, NONE),
	PAD_CFG_TERM_GPO(GPP_F9, 0, NONE, DEEP), // PS8331_SW
	PAD_CFG_GPI(GPP_F10, NONE, DEEP), // BIOS RECOVERY STRAP
	PAD_NC(GPP_F11, NONE),
	PAD_NC(GPP_F12, NONE),
	PAD_NC(GPP_F13, NONE),
	PAD_CFG_GPI(GPP_F14, NONE, DEEP), // H_SKTOCC_H
	PAD_NC(GPP_F15, NONE), // USB_OC4# (test point)
	PAD_NC(GPP_F16, NONE), // USB_OC5# (test point)
	PAD_NC(GPP_F17, NONE), // USB_OC6# (test point)
	PAD_NC(GPP_F18, NONE), // USB_OC7# (test point)
	PAD_CFG_NF(GPP_F19, NONE, DEEP, NF1), // NB_ENAVDD
	PAD_CFG_NF(GPP_F20, NONE, DEEP, NF1), // BLON
	PAD_CFG_NF(GPP_F21, NONE, DEEP, NF1), // EDP_BRIGHTNESS
	PAD_CFG_TERM_GPO(GPP_F22, 0, NONE, DEEP), // DGPU_RST#_PCH
	PAD_CFG_TERM_GPO(GPP_F23, 0, NONE, DEEP), // DGPU_PWR_EN

	/* ------- GPIO Group GPP_G ------- */
	PAD_CFG_GPI(GPP_G0, NONE, DEEP), // GSYNC_DET
	PAD_NC(GPP_G1, NONE),
	PAD_CFG_GPI(GPP_G2, NONE, DEEP), // DDS_DET
	PAD_NC(GPP_G3, NONE),
	PAD_NC(GPP_G4, NONE),
	PAD_NC(GPP_G5, NONE),
	PAD_CFG_GPI(GPP_G6, NONE, DEEP), // SWI#_GPP_G6
	PAD_NC(GPP_G7, NONE),

	/* ------- GPIO Group GPP_H ------- */
	PAD_CFG_NF(GPP_H0, NONE, DEEP, NF1), // WLAN_CLKREQ#
	PAD_CFG_NF(GPP_H1, NONE, DEEP, NF1), // CR_CLKREQ#
	PAD_CFG_NF(GPP_H2, NONE, DEEP, NF1), // PEG_CLKREQ#
	PAD_CFG_NF(GPP_H3, NONE, DEEP, NF1), // SSD1_CLKREQ#
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1), // SSD2_CLKREQ#
	PAD_NC(GPP_H5, NONE),
	PAD_CFG_TERM_GPO(GPP_H6, 1, NONE, DEEP), // PCIE_SSD1_RST#
	PAD_CFG_TERM_GPO(GPP_H7, 1, NONE, DEEP), // PCIE_SSD2_RST#
	PAD_CFG_GPI(GPP_H8, NONE, DEEP),  // GPP_H8_LAN_RST#
	_PAD_CFG_STRUCT(GPP_H9, 0x40880100, 0x0000), // GPP_H9_TBT_WAKE#
	PAD_NC(GPP_H10, NONE),
	PAD_NC(GPP_H11, NONE),
	PAD_CFG_GPI(GPP_H12, NONE, DEEP), // ESPI FLASH SHARING MODE STRAP
	PAD_CFG_GPI(GPP_H13, NONE, DEEP), // TBTA_HRESET
	PAD_NC(GPP_H14, NONE),
	PAD_CFG_GPI(GPP_H15, NONE, DEEP), // RESERVED STRAP
	PAD_CFG_TERM_GPO(GPP_H16, 1, NONE, DEEP), // TBT_RTD3_PWR_EN_R
	PAD_CFG_TERM_GPO(GPP_H17, 1, NONE, PLTRST), // TBT_FORCE_PWR_R
	PAD_NC(GPP_H18, NONE),
	PAD_CFG_TERM_GPO(GPP_H19, 0, NONE, DEEP), // GPP_H19_CR_AUX33
	PAD_CFG_TERM_GPO(GPP_H20, 0, NONE, DEEP), // GPP_H20_CR_MV33
	PAD_CFG_GPI(GPP_H21, NONE, DEEP),
	PAD_NC(GPP_H22, NONE),
	_PAD_CFG_STRUCT(GPP_H23, 0x82880100, 0x0000), // TBCIO_PLUG_EVENT#

	/* ------- GPIO Group GPP_I ------- */
	_PAD_CFG_STRUCT(GPP_I0, 0x46080100, 0x0000), // MDP_B_HPD
	_PAD_CFG_STRUCT(GPP_I1, 0x46080100, 0x0000), // HDMI_HPD
	_PAD_CFG_STRUCT(GPP_I2, 0x46080100, 0x0000), // MDP_E_HPD
	_PAD_CFG_STRUCT(GPP_I3, 0x46080100, 0x0000), // PS8330B_HPD
	PAD_CFG_NF(GPP_I4, NONE, DEEP, NF1), // SB_IEDP_HPD
	PAD_CFG_TERM_GPO(GPP_I5, 1, UP_20K, PLTRST), // TBT_GPIO_RST#
	PAD_NC(GPP_I6, NONE),
	PAD_NC(GPP_I7, NONE),
	PAD_CFG_TERM_GPO(GPP_I8, 1, NONE, DEEP), // SSD1_PWR_EN
	PAD_CFG_TERM_GPO(GPP_I9, 1, NONE, DEEP), // SSD2_PWR_EN
	PAD_NC(GPP_I10, NONE),
	PAD_NC(GPP_I11, NONE),
	PAD_CFG_TERM_GPO(GPP_I12, 1, NONE, DEEP),  // SATA_PWR_EN
	PAD_NC(GPP_I13, NONE),
	PAD_NC(GPP_I14, NONE),

	/* ------- GPIO Group GPP_J ------- */
	PAD_CFG_NF(GPP_J0, NONE, DEEP, NF1), // CNVI_GNSS_PA_BLANKING
	PAD_CFG_TERM_GPO(GPP_J1, 1, NONE, DEEP), // GPP_J1
	PAD_NC(GPP_J2, NONE),
	PAD_NC(GPP_J3, NONE),
	PAD_CFG_NF(GPP_J4, NONE, DEEP, NF1), // CNVI_BRI_DT
	PAD_CFG_NF(GPP_J5, UP_20K, DEEP, NF1), // CNVI_BRI_RSP
	PAD_CFG_NF(GPP_J6, NONE, DEEP, NF1), // CNVI_RGI_DT
	PAD_CFG_NF(GPP_J7, UP_20K, DEEP, NF1), // CNVI_RGI_RSP
	PAD_CFG_NF(GPP_J8, NONE, DEEP, NF1), // CNVI_MFUART2_RXD
	PAD_CFG_NF(GPP_J9, NONE, DEEP, NF1), // CNVI_MFUART2_TXD
	PAD_NC(GPP_J10, NONE),
	PAD_CFG_GPI(GPP_J11, DN_20K, DEEP),

	/* ------- GPIO Group GPP_K ------- */
	PAD_CFG_TERM_GPO(GPP_K0, 0, NONE, DEEP), // GPP_K0_SPK_MUTE
	PAD_CFG_TERM_GPO(GPP_K1, 0, NONE, DEEP), // GPP_K1_WOOFER_MUTE
	PAD_NC(GPP_K2, NONE),
	_PAD_CFG_STRUCT(GPP_K3, 0x40880100, 0x0000), // SCI#_GPP_K3
	PAD_NC(GPP_K4, NONE),
	PAD_NC(GPP_K5, NONE),
	_PAD_CFG_STRUCT(GPP_K6, 0x40880100, 0x0000), // SWI#_GPP_K6
	PAD_CFG_GPI(GPP_K7, NONE, DEEP), // GPP_K7_LAN_WAKEUP#
	PAD_CFG_TERM_GPO(GPP_K8, 0, NONE, DEEP), // GPP_K8_LAN_RTD3
	PAD_NC(GPP_K9, NONE),
	PAD_NC(GPP_K10, NONE),
	PAD_NC(GPP_K11, NONE),
	PAD_CFG_TERM_GPO(GPP_K12, 0, NONE, DEEP), // GPP_K12_PLVDD_SEL
	PAD_NC(GPP_K13, NONE),
	PAD_CFG_TERM_GPO(GPP_K14, 0, NONE, DEEP), // GPP_K14_TEST_R
	_PAD_CFG_STRUCT(GPP_K15, 0x80100100, 0x0000), // GPP_K15_INTP_OUT
	PAD_NC(GPP_K16, NONE),
	PAD_NC(GPP_K17, NONE),
	PAD_CFG_TERM_GPO(GPP_K18, 1, NONE, DEEP), // GPP_K18_TBT_WAKE#
	PAD_CFG_GPI(GPP_K19, NONE, DEEP), // SMI#_GPP_K19
	PAD_NC(GPP_K20, NONE),
	PAD_NC(GPP_K21, NONE),
	PAD_CFG_TERM_GPO(GPP_K22, 0, NONE, DEEP), // DGPU_OVRM
	PAD_CFG_GPI(GPP_K23, NONE, DEEP), // DGPU_PWR_OK
};

void mainboard_configure_gpios(void)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));
}
