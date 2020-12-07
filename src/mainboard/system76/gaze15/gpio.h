/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef MAINBOARD_GPIO_H
#define MAINBOARD_GPIO_H

#define DGPU_RST_N GPP_F22
#define DGPU_PWR_EN GPP_F23
#define DGPU_GC6 GPP_K21

#ifndef __ACPI__

#include <soc/gpe.h>
#include <soc/gpio.h>

/* Pad configuration in romstage. */
static const struct pad_config early_gpio_table[] = {
	PAD_CFG_GPI(GPP_C20, NONE, DEEP), // UART2_RXD
	PAD_CFG_GPI(GPP_C21, NONE, DEEP), // UART2_TXD
	PAD_CFG_NF(GPP_F19, NONE, DEEP, NF1), // NB_ENAVDD
	PAD_CFG_TERM_GPO(DGPU_RST_N, 0, NONE, DEEP), // DGPU_RST#_PCH
	PAD_CFG_TERM_GPO(DGPU_PWR_EN, 0, NONE, DEEP), // DGPU_PWR_EN
};

/* Pad configuration in ramstage. */
static const struct pad_config gpio_table[] = {
	PAD_CFG_GPI(GPD0, NONE, PWROK), // PM_BATLOW#
	PAD_CFG_NF(GPD1, NATIVE, DEEP, NF1), // AC_PRESENT
	PAD_CFG_GPI(GPD2, NATIVE, PWROK), // LAN_WAKEUP#
	PAD_CFG_NF(GPD3, UP_20K, DEEP, NF1), // PWR_BTN#
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1), // SUSB#
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1), // SUSC#
	PAD_CFG_NF(GPD6, NONE, DEEP, NF1), // SLP_A# ==> NC (test point)
	PAD_CFG_GPI(GPD7, NONE, PWROK), // 100k pull up
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1), // SUS_CLK_R
	PAD_CFG_GPI(GPD9, NONE, PWROK), // PCH_SLP_WLAN# ==> NC (test point)
	PAD_CFG_NF(GPD10, NONE, DEEP, NF1), // NC
	PAD_CFG_GPI(GPD11, NONE, PWROK), // LAN_DISABLE_N ==> NC (test point)
	PAD_CFG_NF(GPP_A0, NONE, DEEP, NF1), // SB_KBCRST#
	PAD_CFG_NF(GPP_A1, NATIVE, DEEP, NF1), // LPC_AD0
	PAD_CFG_NF(GPP_A2, NATIVE, DEEP, NF1), // LPC_AD1
	PAD_CFG_NF(GPP_A3, NATIVE, DEEP, NF1), // LPC_AD2
	PAD_CFG_NF(GPP_A4, NATIVE, DEEP, NF1), // LPC_AD3
	PAD_CFG_NF(GPP_A5, NONE, DEEP, NF1), // LPC_FRAME#
	PAD_CFG_NF(GPP_A6, NONE, DEEP, NF1), // SERIRQ
	_PAD_CFG_STRUCT(GPP_A7, 0x80100100, 0x0000), // INTP_OUT
	PAD_CFG_NF(GPP_A8, NONE, DEEP, NF1), // PM_CLKRUN#
	PAD_CFG_NF(GPP_A9, DN_20K, DEEP, NF1), // CLK_PCI_KBC_R
	PAD_CFG_NF(GPP_A10, DN_20K, DEEP, NF1), // NC
	PAD_CFG_GPI(GPP_A11, UP_20K, DEEP), // LAN_WUP#
	PAD_CFG_GPI(GPP_A12, NONE, DEEP), // ISH_GP6 ==> NC
	PAD_CFG_NF(GPP_A13, NONE, DEEP, NF1), // SUSWARN#
	PAD_CFG_NF(GPP_A14, NONE, DEEP, NF1), // S4_STATE#
	PAD_CFG_NF(GPP_A15, UP_20K, DEEP, NF1), // SUS_PWR_ACK#_R
	PAD_CFG_GPI(GPP_A16, DN_20K, DEEP), // NC
	PAD_CFG_GPI(GPP_A17, NONE, DEEP), // NC
	PAD_CFG_TERM_GPO(GPP_A18, 1, NONE, DEEP), // SB_BLON
	PAD_CFG_GPI(GPP_A19, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_A20, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_A21, NONE, DEEP), // 3G_CONFIG2 (test point)
	PAD_CFG_TERM_GPO(GPP_A22, 1, NONE, DEEP), // SATA_PWR_EN
	PAD_CFG_GPI(GPP_A23, NONE, DEEP), // DGPU_PWM_SELECT# (test point)
	PAD_CFG_GPI(GPP_B0, NONE, DEEP),// TPM_PIRQ#
	PAD_CFG_GPI(GPP_B1, NONE, DEEP), // GPP_B1 ==> NC (test point)
	PAD_CFG_GPI(GPP_B2, NONE, DEEP), // VRALERTB# ==> NC (test point)
	PAD_CFG_GPI(GPP_B3, NONE, DEEP), // BT_EN_PCH
	PAD_CFG_GPI(GPP_B4, UP_20K, DEEP), // EXTTS_SNI_DRV1
	PAD_CFG_GPI(GPP_B5, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B6, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B7, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B8, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B9, NONE, DEEP), // NC
	PAD_CFG_NF(GPP_B10, NONE, DEEP, NF1), // LAN_CLKREQ#
	PAD_CFG_GPI(GPP_B11, NONE, DEEP), // NC
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1), // SLP_S0#
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1), // PLT_RST#
	PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1), // SPKR_SMC_EXTSMI (PCH_SPKR)
	PAD_CFG_GPI(GPP_B15, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B16, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B17, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B18, NONE, DEEP), // LPSS_GSPI0_MOSI (no reboot)
	PAD_CFG_GPI(GPP_B19, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B20, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B21, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_B22, NONE, DEEP), // LPSS_GSPI1_MOSI (boot strap)
	PAD_CFG_GPI(GPP_B23, NONE, DEEP), // PCH_HOT_GNSS_DISABLE
	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1), // SMB_CLK
	PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1), // SMB_DATA
	PAD_CFG_GPI(GPP_C2, NONE, DEEP), // SKIN_THRM_SNSR_ALERT_N
	PAD_CFG_GPI(GPP_C3, NONE, DEEP), // SML0_CLK
	PAD_CFG_GPI(GPP_C4, NONE, DEEP), // SMK0_DATA
	PAD_CFG_GPI(GPP_C5, NONE, DEEP), // GPP_C5 ==> NC (test point)
	PAD_CFG_GPI(GPP_C6, NONE, DEEP), // SMC_CPU_THERM
	PAD_CFG_GPI(GPP_C7, NONE, DEEP), // SMD_CPU_THERM
	PAD_CFG_GPI(GPP_C8, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_C9, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_C10, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_C11, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_C12, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_C13, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_C14, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_C15, NONE, DEEP), // NC
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1), // I2C_SDA_TP
	PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1), // I2C_SCL_TP
	PAD_CFG_NF(GPP_C18, NONE, DEEP, NF1), // SMD_7411_I2C
	PAD_CFG_NF(GPP_C19, NONE, DEEP, NF1), // SMC_7411_I2C
	PAD_CFG_GPI(GPP_C20, NONE, DEEP), // UART2_RXD
	PAD_CFG_GPI(GPP_C21, NONE, DEEP), // UART2_TXD
	PAD_CFG_GPI(GPP_C22, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_C23, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D0, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D1, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D2, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D3, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D4, NONE, DEEP), // I2C2_SDA
	PAD_CFG_NF(GPP_D5, NONE, DEEP, NF3), // CNVI_RF_RST#
	PAD_CFG_NF(GPP_D6, NONE, DEEP, NF3), // XTAL_CLKREQ
	PAD_CFG_GPI(GPP_D7, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D8, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D9, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D10, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D11, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D12, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D13, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D14, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D15, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D16, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D17, NONE, DEEP), // 100k pull down
	PAD_CFG_GPI(GPP_D18, NONE, DEEP), // NC
	PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1), // MIC_CLK_PCH_R
	PAD_CFG_NF(GPP_D20, NONE, DEEP, NF1), // MIC_DATA_PCH_R
	PAD_CFG_GPI(GPP_D21, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D22, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_D23, NONE, DEEP), // I2C2_SCL
	PAD_CFG_GPI(GPP_E0, NONE, DEEP), // SATAGP0 (test point)
	PAD_CFG_NF(GPP_E1, UP_20K, DEEP, NF1), // SATAGP1
	PAD_CFG_GPI(GPP_E2, NONE, DEEP), // SATAGP2
	PAD_CFG_GPI(GPP_E3, NONE, DEEP), // EXTTS_SNI_DRV0
	PAD_CFG_GPI(GPP_E4, NONE, DEEP), // DEVSLP0
	PAD_CFG_GPI(GPP_E5, NONE, DEEP), // DEVSLP1
	PAD_CFG_GPI(GPP_E6, NONE, DEEP), // PCH_MUTE# (test point)
	PAD_CFG_GPI_APIC_LOW(GPP_E7, NONE, PLTRST), // TP_ATTN#
	PAD_CFG_NF(GPP_E8, NONE, DEEP, NF1), // SATA_LED#
	PAD_CFG_GPI(GPP_E9, NONE, DEEP), // USB_OC0#
	PAD_CFG_GPI(GPP_E10, NONE, DEEP), // USB_OC1#
	PAD_CFG_GPI(GPP_E11, NONE, DEEP), // USB_OC2#
	PAD_CFG_GPI(GPP_E12, NONE, DEEP), // VISACH2_D3
	PAD_CFG_GPI(GPP_F0, NONE, DEEP), // SATAGP3
	PAD_CFG_GPI(GPP_F1, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_F2, NONE, DEEP), // ODD_DA#_R (test point)
	PAD_CFG_GPI(GPP_F3, NONE, DEEP), // (test point)
	PAD_CFG_GPI(GPP_F4, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_F5, NONE, DEEP), // KBLED_DET
	PAD_CFG_GPI(GPP_F6, NONE, DEEP), // DEVSLP4
	PAD_CFG_GPI(GPP_F7, NONE, DEEP), // LIGHT_KB_DET#
	PAD_CFG_GPI(GPP_F8, NONE, DEEP), // GPP_F8
	PAD_CFG_GPI(GPP_F9, NONE, DEEP), // GPP_F9
	PAD_CFG_GPI(GPP_F10, NONE, DEEP), // BIOS_REC
	PAD_CFG_GPI(GPP_F11, NONE, DEEP), // PCH_RSVD
	PAD_CFG_GPI(GPP_F12, NONE, DEEP), // MFG_MODE
	PAD_CFG_GPI(GPP_F13, NONE, DEEP), // GP39_GFX_CRB_DETECT
	PAD_CFG_GPI(GPP_F14, NONE, DEEP), // 10k pull up to H_SKTOCC_N
	PAD_CFG_GPI(GPP_F15, NONE, DEEP), // USB_OC4#
	PAD_CFG_GPI(GPP_F16, NONE, DEEP), // USB_OC5#
	PAD_CFG_GPI(GPP_F17, NONE, DEEP), // USB_OC6#
	PAD_CFG_GPI(GPP_F18, NONE, DEEP), // USB_OC7#
	PAD_CFG_NF(GPP_F19, NONE, DEEP, NF1), // NB_ENAVDD
	PAD_CFG_NF(GPP_F20, NONE, DEEP, NF1), // BLON
	PAD_CFG_NF(GPP_F21, NONE, DEEP, NF1), // EDP_BRIGHTNESS
	//PAD_CFG_TERM_GPO(GPP_F22, 1, NONE, DEEP), // DGPU_RST#_PCH
	//PAD_CFG_TERM_GPO(GPP_F23, 1, NONE, DEEP), // DGPU_PWR_EN
	PAD_CFG_GPI(GPP_G0, UP_20K, DEEP), // BOARD_ID1
	PAD_CFG_GPI(GPP_G1, NONE, DEEP), // BOARD_ID2
	PAD_CFG_GPI(GPP_G2, NONE, DEEP), // TPM_DET
	PAD_CFG_GPI(GPP_G3, NONE, DEEP), // GPIO4_1V8_MAIN_EN_R
	PAD_CFG_GPI(GPP_G4, NONE, DEEP), // SMI#_R
	PAD_CFG_GPI(GPP_G5, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_G6, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_G7, NONE, DEEP), // NC
	PAD_CFG_NF(GPP_H0, NONE, DEEP, NF1), // WLAN_CLKREQ#
	PAD_CFG_GPI(GPP_H1, NONE, DEEP), // NC
	PAD_CFG_NF(GPP_H2, NONE, DEEP, NF1), // PEG_CLKREQ#
	PAD_CFG_GPI(GPP_H3, NONE, DEEP), // NC
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1), // SSD_CLKREQ#
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1), // SSD2_CLKREQ#
	PAD_CFG_GPI(GPP_H6, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_H7, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_H8, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_H9, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_H10, NONE, DEEP), // SML2CLK (test point)
	PAD_CFG_GPI(GPP_H11, NONE, DEEP), // SML2DATA (test point)
	PAD_CFG_GPI(GPP_H12, NONE, DEEP), // GPP_H_12
	PAD_CFG_GPI(GPP_H13, NONE, DEEP), // SML3CLK
	PAD_CFG_GPI(GPP_H14, NONE, DEEP), // SML3DATA (test point)
	PAD_CFG_GPI(GPP_H15, NONE, DEEP), // SML3ALERT#
	PAD_CFG_GPI(GPP_H16, NONE, DEEP), // SML4CLK (test point)
	PAD_CFG_GPI(GPP_H17, NONE, DEEP), // SML4DATA (test point)
	PAD_CFG_GPI(GPP_H18, NONE, DEEP), // SML4ALERT# (test point)
	PAD_CFG_GPI(GPP_H19, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_H20, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_H21, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_H22, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_H23, NONE, DEEP), // DGPU_SELECT#
	PAD_CFG_NF(GPP_I0, NONE, DEEP, NF1), // I_MDP_HPD (on 1660 Ti), NC (on 1650/1650 Ti)
	PAD_CFG_NF(GPP_I1, NONE, DEEP, NF1), // HDMI_HPD
	PAD_CFG_GPI(GPP_I2, NONE, DEEP), // 1k pull to MDP_E_HPD
	PAD_CFG_NF(GPP_I3, NONE, DEEP, NF1), // 1k pull to MDP_E_HPD
	PAD_CFG_NF(GPP_I4, NONE, DEEP, NF1), // EDP_HPD
	PAD_CFG_NF(GPP_I5, NONE, DEEP, NF1), // I_MDP_CLK (on 1660 Ti), NC (on 1650/1650 Ti)
	PAD_CFG_NF(GPP_I6, NONE, DEEP, NF1), // I_MDP_DATA (on 1660 Ti), NC (on 1650/1650 Ti)
	PAD_CFG_NF(GPP_I7, NONE, DEEP, NF1), // HDMI_CTRLCLK (on 1650/1650 Ti), test point (on 1660 Ti)
	PAD_CFG_NF(GPP_I8, NONE, DEEP, NF1), // HDMI_CTRLDATA (on 1650/1650 Ti), test point (on 1660 Ti)
	PAD_CFG_GPI(GPP_I9, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_I10, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_I11, NONE, DEEP), // 10k pull up to H_SKTOCC_N
	PAD_CFG_GPI(GPP_I12, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_I13, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_I14, NONE, DEEP), // NC
	PAD_CFG_NF(GPP_J0, NONE, DEEP, NF1), // CNVI_GNSS_PA_BLANKING
	PAD_CFG_NF(GPP_J1, NONE, DEEP, NF2), // GPP_J1
	PAD_CFG_GPI(GPP_J2, NONE, DEEP), // 100k pull down
	PAD_CFG_GPI(GPP_J3, NONE, DEEP), // 100k pull down
	PAD_CFG_NF(GPP_J4, NONE, DEEP, NF1), // CNVI_BRI_DT
	PAD_CFG_NF(GPP_J5, UP_20K, DEEP, NF1), // CNVI_BRI_RSP
	PAD_CFG_NF(GPP_J6, NONE, DEEP, NF1), // CNVI_RGI_DT
	PAD_CFG_NF(GPP_J7, UP_20K, DEEP, NF1), // CNVI_RGI_RSP
	PAD_CFG_NF(GPP_J8, NONE, DEEP, NF1), // CNVI_MFUART2_RXD
	PAD_CFG_NF(GPP_J9, NONE, DEEP, NF1), // CNVI_MFUART2_TXD
	PAD_CFG_GPI(GPP_J10, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_J11, DN_20K, DEEP), // 75k pull down
	PAD_CFG_GPI(GPP_K0, NONE, DEEP), // PCH_GPPK0_PCH_PEXVDD_EN ==> NC (test point)
	PAD_CFG_GPI(GPP_K1, NONE, DEEP), // PCH_GPPK1_PCH_FBVDDQ_EN ==> NC (test point)
	PAD_CFG_GPI(GPP_K2, NONE, DEEP), // PCH_GPPK2_PCH_1V8RUN_EN ==> NC (test point)
	_PAD_CFG_STRUCT(GPP_K3, 0x80880100, 0x0000), // SCI#_R
	PAD_CFG_GPI(GPP_K4, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_K5, NONE, DEEP), // NC
	_PAD_CFG_STRUCT(GPP_K6, 0x40880100, 0x0000), // SWI#_R
	PAD_CFG_GPI(GPP_K7, NONE, DEEP), // NC
	PAD_CFG_TERM_GPO(GPP_K8, 1, NONE, DEEP), // SATA_M2_PWR_EN1
	PAD_CFG_TERM_GPO(GPP_K9, 1, NONE, DEEP), // SATA_M2_PWR_EN2
	PAD_CFG_GPI(GPP_K10, NONE, DEEP), // PCH_GPPK10_PCH_NVVDD_EN ==> NC (test point)
	PAD_CFG_GPI(GPP_K11, NONE, DEEP), // PCH_GPPK11_PCH_NVVDD_EN ==> NC (test point)
	PAD_CFG_GPI(GPP_K12, NONE, DEEP), // (test point)
	PAD_CFG_GPI(GPP_K13, NONE, DEEP), // NC
	PAD_CFG_TERM_GPO(GPP_K14, 0, NONE, DEEP), // GPP_K14_TEST_R
	PAD_CFG_GPI(GPP_K15, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_K16, NONE, DEEP), // (test point)
	PAD_CFG_GPI(GPP_K17, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_K18, NONE, DEEP), // NC
	PAD_CFG_GPI(GPP_K19, NONE, DEEP), // SMI#_RR
	PAD_CFG_TERM_GPO(GPP_K20, 1, NONE, DEEP), // GPU_EVENT#
	PAD_CFG_GPI(GPP_K21, NONE, PLTRST), // GC6_FB_EN_PCH
	PAD_CFG_GPI(GPP_K22, NONE, DEEP), // DGPU_PWRGD_R
	PAD_CFG_GPI(GPP_K23, NONE, DEEP), // DGPU_PRSNT#
};

#endif

#endif
