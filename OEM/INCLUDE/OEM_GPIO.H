/*-----------------------------------------------------------------------------
 * @file     | OEM_GPIO.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_GPIO.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_GPIO_H
#define OEM_GPIO_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
//PROJECT: Intel SKL_Y_MRD_EC_GPIO

//-----------------------------------------------------------------------------
// GPIO Registers define
//-----------------------------------------------------------------------------
/* General Control Register (GCR)
 * BIT7     - GPIOB5 HIGH Follow LPCRST# HIGH-to-LOW
 * BIT6     - WUI7 Enabled
 * BIT5     - WUI6 Enabled
 * BIT[2:1] - [01] LPCRST# in GPIOB7
 *            [10] LPCRST# in GPIOD2
 *            [11] LPCRST# is disabled
 *---------------------------------------------------------------------------*/
#define GCR_Init        0x06
#define GCR1_Init       0x01
#define GCR2_Init       0x00
#define GCR22_Init      0x00
//-----------------------------------------------------------------------------
// GPIO Port A Registers define
//-----------------------------------------------------------------------------
#define PortA_Init      0x01            // PORT Data
//
#define PortA0_Ctrl     OUTPUT          // CHG_LED
#define PortA1_Ctrl     OUTPUT          // SLP_SX_N (OLD:VCCSTG_EN)
//#define PortA2_Ctrl   [X]IT8110E no this pin
//#define PortA3_Ctrl   [X]IT8110E no this pin
//#define PortA4_Ctrl   [X]IT8110E no this pin
//#define PortA5_Ctrl   [X]IT8110E no this pin
//#define PortA6_Ctrl   [X]IT8110E no this pin
//#define PortA7_Ctrl   [X]IT8110E no this pin
//-----------------------------------------------------------------------------
// GPIO Port B Registers define
//-----------------------------------------------------------------------------
#define PortB_Init      0x20            // PORT Data
//
#define PortB0_Ctrl     OUTPUT          // PM_PWRBTN_N
#define PortB1_Ctrl     OUTPUT          // PM_RSMRST_N
//#define PortB2_Ctrl   [X]IT8110E no this pin
#define PortB3_Ctrl     INPUT           //[1.8]SM_BAT_CLK
#define PortB4_Ctrl     INPUT           //[1.8]SM_BAT_DATA
#define PortB5_Ctrl     OUTPUT          //[1.8]EC_PWR_LATCH
#define PortB6_Ctrl     INPUT           //[1.8]VCC_DDR_PWROK
//#define PortB7_Ctrl   [X]IT8110E no this pin
//-----------------------------------------------------------------------------
// GPIO Port C Registers define
//-----------------------------------------------------------------------------
#define PortC_Init      0x00            // PORT Data
//
#define PortC0_Ctrl     INPUT           // VOL_DOWN
#define PortC1_Ctrl     INPUT           //[1.8]SML1_CK
#define PortC2_Ctrl     INPUT           //[1.8]SML1_DATA
//#define PortC3_Ctrl   [X]IT8110E no this pin
//#define PortC4_Ctrl   [X]IT8110E no this pin
//#define PortC5_Ctrl   [X]IT8110E no this pin
//#define PortC6_Ctrl   [X]IT8110E no this pin
//#define PortC7_Ctrl   [X]IT8110E no this pin
//-----------------------------------------------------------------------------
// GPIO Port D Registers define
//-----------------------------------------------------------------------------
#define PortD_Init      0x00            // PORT Data
//
#define PortD0_Ctrl     INPUT           //[1.8]SLP_S0_N (OLD:SUS_PWR_DN_ACK)
//#define PortD1_Ctrl   [X]IT8110E no this pin
#define PortD2_Ctrl     INPUT           //[1.8]BUF_PLT_RST_N
//#define PortD3_Ctrl   [X]IT8110E no this pin
//#define PortD4_Ctrl   [X]IT8110E no this pin
#define PortD5_Ctrl     INPUT   // VOLUME_UP_R
#define PortD6_Ctrl     INPUT           // V5P0A_PGOOD
//#define PortD7_Ctrl   [X]IT8110E no this pin
//-----------------------------------------------------------------------------
// GPIO Port E Registers define
//-----------------------------------------------------------------------------
#define PortE_Init      0x00            // PORT Data
//
#define PortE0_Ctrl     INPUT           //[1.8]USBPD_INT_N
//#define PortE1_Ctrl   [X]IT8110E no this pin
//#define PortE2_Ctrl   [X]IT8110E no this pin
//#define PortE3_Ctrl   [X]IT8110E no this pin
#define PortE4_Ctrl     INPUT           // EC_PWRBTN_IN_N
//#define PortE5_Ctrl   [X]IT8110E no this pin
//#define PortE6_Ctrl   [X]IT8110E no this pin
#define PortE7_Ctrl     OUTPUT          //[1.8]SYS_PWROK
//-----------------------------------------------------------------------------
// GPIO Port F Registers define
//-----------------------------------------------------------------------------
#define PortF_Init      0x00            // PORT Data
//
//#define PortF0_Ctrl   [X]IT8110E no this pin
//#define PortF1_Ctrl   [X]IT8110E no this pin
#define PortF2_Ctrl     INPUT           // PM_SLP_S3_N
#define PortF3_Ctrl     INPUT           // WPT_PGOOD (for Wireless Charger)
//#define PortF4_Ctrl   [X]IT8110E no this pin
//#define PortF5_Ctrl   [X]IT8110E no this pin
#define PortF6_Ctrl     INPUT           //[1.8]PECI_EC
#define PortF7_Ctrl     OUTPUT           //[1.8]EC_PCH_PWROK
//-----------------------------------------------------------------------------
// GPIO Port G Registers define
//-----------------------------------------------------------------------------
#define PortG_Init      0x00            // PORT Data
//
//#define PortG0_Ctrl   [X]IT8110E no this pin
#define PortG1_Ctrl     INPUT           // SLP_S4_N
#if Support_MRD_NOREWORK
#define PortG2_Ctrl     INPUT           // SPI_MIRROR_MODE
#else
#define PortG2_Ctrl     OUTPUT           // SPI_MIRROR_MODE
#endif
#define PortG3_Ctrl     INPUT           // SPI_CS0_CON_N
#define PortG4_Ctrl     INPUT           // SPI0_SI_R
#define PortG5_Ctrl     INPUT           // SPI0_SO_R
#define PortG6_Ctrl     OUTPUT          // EC_PROCHOT
#define PortG7_Ctrl     INPUT           // SPI0_CK_R
//-----------------------------------------------------------------------------
// GPIO Port H Registers define
//-----------------------------------------------------------------------------
#define PortH_Init      0x00            // PORT Data
//
#define PortH0_Ctrl     OUTPUT          //[1.8]EC_TYPEC_POUT_EN (for USB TYPE C)
//#define PortH0_Ctrl   ALT             //[1.8]EC_TYPEC_POUT_EN (for USB TYPE C)
#define PortH1_Ctrl     INPUT+PULL_UP   //[3.3]CHG_ACOK (AC in)
#if Support_MRD_NOREWORK
#define PortH2_Ctrl     OUTPUT          //[1.8]SMC_RUNTIME_SCI_N
#else
#define PortH2_Ctrl     INPUT          //[1.8]SMC_RUNTIME_SCI_N  ADP_SEL
#endif
//#define PortH3_Ctrl   [X]IT8110E no this pin
//#define PortH4_Ctrl   [X]IT8110E no this pin
//#define PortH5_Ctrl   [X]IT8110E no this pin
//#define PortH6_Ctrl   [X]IT8110E no this pin
//-----------------------------------------------------------------------------
// GPIO Port I Registers define
//-----------------------------------------------------------------------------
#define PortI_Init      0x00           // PORT Data
//
#define PortI0_Ctrl     INPUT           // EC_SYS_THERM1
#define PortI1_Ctrl     INPUT           // EC_SYS_THERM0
#define PortI2_Ctrl     INPUT           // HotPlugDetect /P1:EC_TYPE_C_OUT_EN
#define PortI3_Ctrl     INPUT           // LID_INT_N
//#define PortI4_Ctrl   [X]IT8110E no this pin
//#define PortI5_Ctrl   [X]IT8110E no this pin
//#define PortI6_Ctrl   [X]IT8110E no this pin
//#define PortI7_Ctrl   [X]IT8110E no this pin
//-----------------------------------------------------------------------------
// GPIO Port J Registers define
//-----------------------------------------------------------------------------
#define PortJ_Init      0x00            // PORT Data
//
//#define PortJ0_Ctrl   [X]IT8110E no this pin
//#define PortJ1_Ctrl   [X]IT8110E no this pin
//#define PortJ2_Ctrl   [X]IT8110E no this pin
#define PortJ3_Ctrl     OUTPUT          // PM_BATLOW_N
//#define PortJ4_Ctrl   [X]IT8110E no this pin
//#define PortJ5_Ctrl   [X]IT8110E no this pin
//-----------------------------------------------------------------------------
// Others Registers Notes
//-----------------------------------------------------------------------------
//KSO11 AC_PRESENT      OUTPUT
//KSO12 ALLSYSPWRGD     OUTPUT
//KSI0  HOME_BTN        INPUT
/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
typedef struct InitGPIOReg
{
    XBYTE   *reg;
    BYTE    value;
} sInitGPIOReg;

/*-----------------------------------------------------------------------------
 * GPIO Signal Macro Definition
 *---------------------------------------------------------------------------*/
//----------------------------------------------------------------------------
/* EC STANDARD ALT FUNTION FIX PINs */
//----------------------------------------------------------------------------
#if Support_MRD_NOREWORK
#define EC_SCI_LO()             CLEAR_MASK(GPDRH, BIT(2))
#define EC_SCI_HI()             SET_MASK(GPDRH, BIT(2))
#define IS_EC_SCI_HI()          IS_MASK_SET(GPDRH, BIT(2))
#define READ_EC_SCI()           IS_MASK_SET(GPDRH, BIT(2))
#else
#define EC_SCI_LO()             CLEAR_MASK(GPDRG, BIT(2))
#define EC_SCI_HI()             SET_MASK(GPDRG, BIT(2))
#define IS_EC_SCI_HI()          IS_MASK_SET(GPDRG, BIT(2))
#define READ_EC_SCI()           IS_MASK_SET(GPDRG, BIT(2))
#endif
#define EC_SMI_LO()             //CLEAR_MASK(GPDR?, BIT(?))
#define EC_SMI_HI()             //SET_MASK(GPDR?, BIT(?))
#define IS_EC_SMI_HI()          1 //IS_MASK_SET(GPDR?, BIT(?))
#define READ_EC_SMI()           0 //IS_MASK_SET(GPDR?, BIT(?))

#define GATEA20_LO()            //CLEAR_MASK(GPDR?, BIT(?))
#define GATEA20_HI()            //SET_MASK(GPDR?, BIT(?))
#define IS_GATEA20_HI()         1 //IS_MASK_SET(GPDR?, BIT(?))
#define READ_GATEA20()          0 //IS_MASK_SET(GPDR?, BIT(?))

#define KBRST_LO()              //CLEAR_MASK(GPDR?, BIT(?))
#define KBRST_HI()              //SET_MASK(GPDR?, BIT(?))
#define IS_KBRST_HI()           1 //IS_MASK_SET(GPDR?, BIT(?))
#define READ_KBRST()            0 //IS_MASK_SET(GPDR?, BIT(?))

//----------------------------------------------------------------------------
/* KEYBOARD LED FIX PINs */
//----------------------------------------------------------------------------
#define KB_NUMLED_ON()          //CLEAR_MASK(GPDR?, BIT(?))
#define KB_NUMLED_OFF()         //SET_MASK(GPDR?, BIT(?))
#define IS_NUMLED_ON()          //IS_MASK_SET(GPDR?, BIT(?))

#define KB_CAPLED_ON()          //CLEAR_MASK(GPDR?, BIT(?))
#define KB_CAPLED_OFF()         //SET_MASK(GPDR?, BIT(?))
#define IS_CAPLED_ON()          //IS_MASK_SET(GPDR?, BIT(?))

#define KB_SCROLLED_ON()        //CLEAR_MASK(GPDR?, BIT(?))
#define KB_SCROLLED_OFF()       //SET_MASK(GPDR?, BIT(?))
#define IS_SCROLLED_ON()        //IS_MASK_SET(GPDR?, BIT(?))

//----------------------------------------------------------------------------
/* EC PCH I/O CONTROL FUNTION PINs */
//----------------------------------------------------------------------------
#define PCH_RSMRST_HI()         SET_MASK(GPDRB, BIT(1))
#define PCH_RSMRST_LO()         CLEAR_MASK(GPDRB, BIT(1))
#define IS_PCH_RSMRST_HI()      IS_MASK_SET(GPDRB, BIT(1))
#define IS_PCH_RSMRST_LO()      IS_MASK_CLEAR(GPDRB, BIT(1))

#define PCH_PWROK_HI()        SET_MASK(GPDRF, BIT(7))
#define PCH_PWROK_LO()        CLEAR_MASK(GPDRF, BIT(7))
#define IS_PCH_PWROK_HI()       IS_MASK_SET(GPDRF, BIT(7))
#define IS_PCH_PWROK_LO()       IS_MASK_CLEAR(GPDRF, BIT(7))

#define PCH_PWRBTN_HI()         SET_MASK(GPDRB, BIT(0))
#define PCH_PWRBTN_LO()         CLEAR_MASK(GPDRB, BIT(0))
#define IS_PCH_PWRBTN_HI()      IS_MASK_SET(GPDRB, BIT(0))
#define IS_PCH_PWRBTN_LO()      IS_MASK_CLEAR(GPDRB, BIT(0))

#define IS_PCH_SLP_S5_HI()      IS_MASK_SET(GPDRG, BIT(1))
#define IS_PCH_SLP_S5_LO()      IS_MASK_CLEAR(GPDRG, BIT(1))

#define IS_PCH_SLP_S4_HI()      IS_MASK_SET(GPDRG, BIT(1))
#define IS_PCH_SLP_S4_LO()      IS_MASK_CLEAR(GPDRG, BIT(1))

#define IS_PCH_SLP_S3_HI()      IS_MASK_SET(GPDRF, BIT(2))
#define IS_PCH_SLP_S3_LO()      IS_MASK_CLEAR(GPDRF, BIT(2))

#define IS_PLT_RST_HI()         IS_MASK_SET(GPDRD, BIT(2))
#define IS_PLT_RST_Lo()         IS_MASK_CLEAR(GPDRD, BIT(2))
//----------------------------------------------------------------------------
/* EC SWITCH FUNTION PINs */
//----------------------------------------------------------------------------
#define IS_EC_PWRSW_DN()        IS_MASK_CLEAR(GPDRE, BIT(4))
#define IS_EC_PWRSW_UP()        IS_MASK_SET(GPDRE, BIT(4))

#define IS_LID_SW_CLOSE()       IS_MASK_CLEAR(GPDRI, BIT(3))
#define IS_LID_SW_OPEN()        IS_MASK_SET(GPDRI, BIT(3))

#define IS_VOLUME_DOWN_DN()     IS_MASK_CLEAR(GPDRC, BIT(0))
#define IS_VOLUME_DOWN_UP()     IS_MASK_SET(GPDRC, BIT(0))

#define IS_VOLUME_UP_DN()       IS_MASK_CLEAR(GPDRD, BIT(5))
#define IS_VOLUME_UP_UP()       IS_MASK_SET(GPDRD, BIT(5))

#define IS_HOMEKEY_SW_DN()      IS_MASK_CLEAR(KSI, BIT(0))
#define IS_HOMEKEY_SW_UP()      IS_MASK_SET(KSI, BIT(0))

//----------------------------------------------------------------------------
/* EC BATTERY & CHARGER FUNTION PINs */
//----------------------------------------------------------------------------
#define IS_ADAPTER_IN()         IS_MASK_SET(GPDRH, BIT(1))
#define IS_ADAPTER_OUT()        IS_MASK_CLEAR(GPDRH, BIT(1))
#define IS_AC_OK_LOW()          IS_MASK_CLEAR(GPDRH, BIT(1))

#define IS_BATTERY1_IN()        0   //IS_MASK_CLEAR(GPDRI, BIT(3))
#define IS_BATTERY1_OUT()       1   //IS_MASK_SET(GPDRI, BIT(3))


#if !Support_MRD_NOREWORK

#define IS_ADP_SEL_H()        	IS_MASK_SET(GPDRH, BIT(2))
#define IS_ADP_SEL_L()          IS_MASK_CLEAR(GPDRH, BIT(2))
#endif
//----------------------------------------------------------------------------
/* EC OEM LED CONTROL PINs */
//----------------------------------------------------------------------------
#define CHG_LED_ON()            CLEAR_MASK(GPDRA, BIT(0))
#define CHG_LED_OFF()           SET_MASK(GPDRA, BIT(0))
#define IS_CHG_LED_ON()         IS_MASK_CLEAR(GPDRA, BIT(0))
#define IS_CHG_LED_OFF()        IS_MASK_SET(GPDRA, BIT(0))

#define EC_HPD_OUT_LO()         CLEAR_MASK(GPDRI, BIT(2))
#define EC_HPD_OUT_HI()         SET_MASK(GPDRI, BIT(2))

#define CHG_DONE_LED_ON()       //CLEAR_MASK(GPDRG, BIT(2))
#define CHG_DONE_LED_OFF()      //SET_MASK(GPDRG, BIT(2))
#define IS_CHG_DONE_LED_ON()    0   //IS_MASK_CLEAR(GPDRG, BIT(2))
#define IS_CHG_DONE_LED_OFF()   1   //IS_MASK_SET(GPDRG, BIT(2))

//----------------------------------------------------------------------------
/* EC POWER CONTROL FUNTION PINs */
//----------------------------------------------------------------------------
#define PM_BATLOW_HI()          SET_MASK(GPDRJ, BIT(3))
#define PM_BATLOW_LO()          CLEAR_MASK(GPDRJ, BIT(3))

#define EC_PWR_LATCH_HI()       SET_MASK(GPDRB, BIT(5))
#define EC_PWR_LATCH_LO()       CLEAR_MASK(GPDRB, BIT(5))

#define EC_PROCHOT_HI()         SET_MASK(GPDRG, BIT(6))
#define EC_PROCHOT_LO()         CLEAR_MASK(GPDRG, BIT(6))

#define EC_TYPEC_POUT_EN_HI()   //SET_MASK(GPDRI, BIT(2))
#define EC_TYPEC_POUT_EN_LO()   //CLEAR_MASK(GPDRI, BIT(2))

#define IS_USBPD_INT_N_HI()     IS_MASK_SET(GPDRE, BIT(0))
#define IS_USBPD_INT_N_LO()     IS_MASK_CLEAR(GPDRE, BIT(0))

#define IS_WPT_PGOOD_HI()       IS_MASK_SET(GPDRF, BIT(3))
#define IS_WPT_PGOOD_LO()       IS_MASK_CLEAR(GPDRF, BIT(3))

#define IS_V5P0A_PGOOD_HI()     IS_MASK_SET(GPDRD, BIT(6))
#define IS_V5P0A_PGOOD_LO()     IS_MASK_CLEAR(GPDRD, BIT(6))

#define IS_BUF_PLT_RST_HI()     IS_MASK_SET(GPDRD, BIT(2))
#define IS_BUF_PLT_RST_LO()     IS_MASK_CLEAR(GPDRD, BIT(2))

#define IS_SLP_SX_N_HI()        IS_MASK_SET(GPDRA, BIT(1))
#define IS_SLP_SX_N_LO()        IS_MASK_CLEAR(GPDRA, BIT(1))
#define SLP_SX_N_HI()           SET_MASK(GPDRA, BIT(1))
#define SLP_SX_N_LO()           CLEAR_MASK(GPDRA, BIT(1))

#define IS_VCC_DDR_PWROK_HI()   IS_MASK_SET(GPDRB, BIT(6))
#define IS_VCC_DDR_PWROK_LO()   IS_MASK_CLEAR(GPDRB, BIT(6))

#define IS_SLP_S0_N_HI()        IS_MASK_SET(GPDRD, BIT(0))
#define IS_SLP_S0_N_LO()        IS_MASK_CLEAR(GPDRD, BIT(0))

#define EC_SYS_PWROK_HI()       SET_MASK(GPDRE, BIT(7))
#define EC_SYS_PWROK_LO()       CLEAR_MASK(GPDRE, BIT(7))

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Init_GPIO();
extern void Hook_SCION(void);
extern void Hook_SCIOFF(void);
extern void Hook_SMION(void);
extern void Hook_SMIOFF(void);
extern void Hook_A20ON(void);
extern void Hook_A20OFF(void);
extern void Hook_KBRSTON(void);
extern void Hook_KBRSTOFF(void);
extern void Hook_NUMLED_ON(void);
extern void Hook_NUMLED_OFF(void);
extern void Hook_CAPLED_ON(void);
extern void Hook_CAPLED_OFF(void);
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#endif  //OEM_GPIO_H
/*-----------------------------------------------------------------------------
 * End of OEM_GPIO.H */
