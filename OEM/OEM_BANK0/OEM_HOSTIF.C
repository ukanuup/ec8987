/*-----------------------------------------------------------------------------
 * @file     | OEM_HOSTIF.C
 * ----------+-----------------------------------------------------------------
 * @function | LPC & Host interface process
 * ----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2014, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition (Can move to OEM_Project.H)
 *---------------------------------------------------------------------------*/
//#define   SUPPORT_SIO_UART1
//#define   SUPPORT_SIO_UART2
//#define   SUPPORT_SIO_MOUSE
//#define   SUPPORT_SIO_CIR
//#define   SUPPORT_SIO_H2RAM
//#define   SUPPORT_SIO_SSPI
//#define   SUPPORT_SIO_PECI
#define     SUPPORT_SIO_BRAMP80
//#define   SUPPORT_SIO_PMC3
//#define   SUPPORT_SIO_PMC4
//#define   SUPPORT_SHARED_MEM

//*****************************************************************************
/* initsio_table */
//*****************************************************************************
const BYTE code initsio_table[] =
{
#ifdef SUPPORT_SIO_UART1
    // Configure and Enable Logical Device 01h(UART1)
    0x07 ,0x01, // Select Logical Device 01h(UART1)
    0x60, 0x03, // I/O Base Address 3F8h
    0x61, 0xF8, // I/O Base Address 3F8h
    0x70 ,0x04, // Set IRQ=05h for Logical Device 01h(UART1)
    0x30 ,0x01, // Enable Logical Device 01h(UART1)
#endif
#ifdef SUPPORT_SIO_UART2
    // Configure and Enable Logical Device 02h(UART2)
    0x07, 0x02, // Select Logical Device 02h(UART2)
    0x30, 0x02, // Enable Logical Device 02h(UART2)
#endif
    // Enable Logical Device 04h(MSWC)
    0x07, 0x04, // Logical Device 04h(MSWC)
    0x30, 0x00, // Enable MSWC
#ifdef SUPPORT_SIO_MOUSE
    // Configure and Enable Logical Device 05h(Mouse)
    0x07, 0x05, // Select Logical Device 05h(Mouse)
    0x70, 0x0C, // Set IRQ=0Ch for Logical Device 05h(Mouse)
    0x30, 0x01, // Enable Logical Device 05h(Mouse)
#endif
    // Configure and Enable Logical Device 06h(KBD)
    0x07, 0x06, // Select Logical Device 06h(KBD)
    0x70, 0x01, // Set IRQ=01h for Logical Device 06h(KBD)
    0x30, 0x01, // Enable Logical Device 06h(Mouse)

#ifdef SUPPORT_SIO_CIR
    0x07, 0x0A, // Enable Logical Device 0Ah(CIR)
    0x60, 0x03, // IO Port 300
    0x61, 0x00, //
    0x70, 0x0A, // IRQ=10 for CIR
    0x30, 0x01, // Enable CIR
#endif
    // Enable Logical Device 10h(RTCT)
    0x07, 0x10, // Logical Device 10h(BRAM)
    0x60, 0x09,
    0x61, 0x12, // BRAMLD address is 0x912 (index) and 0x913 (data)
    0x62, 0x09,
    0x63, 0x10, // BRAMLD address is 0x910 (index) and 0x911 (data)
#ifdef SUPPORT_SIO_BRAMP80
    0xF3, 0x3F, // P80 value begin of BRAM (Need 200DH.BIT(7))
    0xF4, 0x3F, // P80 value end of BRAM
    0xF5, 0x3F, // P80 value index of BRAM
#endif
    0x30, 0x01, // Enable BRAM
    // Enable Logical Device 11h(PM1)(Default:62h,66h)
    0x07, 0x11, // Select Logical Device 11h(PM1)
    0x70, 0x00, // Clear IRQ=0 for  Logical Device 11h(PM1)
    0x30, 0x01, // Enable Logical Device 11h(PM1)

    // Enable Logical Device 12h(PM2)(Default:68h,6Ch)
    0x07, 0x12, // Select Logical Device 12h(PM2)
    0x70, 0x00, // Clear IRQ=0 for  Logical Device 12h(PM2)
    0x30, 0x01, // Enable Logical Device 12h(PM2)
#ifdef  SUPPORT_SIO_SSPI
    // Enable Logical Device 13h(SSPI)
    0x07, 0x13, // Select Logical Device 13h(SSPI)
    0x30, 0x01, // Enable Logical Device 13h(SSPI)
#endif
#ifdef  SUPPORT_SIO_PECI
    // Enable Logical Device 14h(PECI)
    0x07, 0x14, // Select Logical Device 14h(PECI)
    0x30, 0x01, // Enable Logical Device 14h(PECI)
#endif
#ifdef SUPPORT_SIO_PMC3
    0x07, 0x17, // Select Logical Device 17h(PMC3)
    0x62, 0x06, // IO Port 6A0
    0x63, 0xA0, //
    0x60, 0x06, // IO Port 6A4
    0x61, 0xA4, //
    0x70, 0x00, // Clear IRQ for Logical Device 17h(PMC3)
    0x30, 0x01, // Enable Logical Device 17h(PMC3)
#endif
#ifdef SUPPORT_SIO_PMC4
    0x07, 0x18, // Select Logical Device 18h(PMC4)
    0x62, 0x06, // IO Port 6A2
    0x63, 0xA2, //
    0x60, 0x06, // IO Port 6A6
    0x61, 0xA6, //
    0x70, 0x00, // Clear IRQ for Logical Device 18h(PMC3)
    0x30, 0x01, // Enable Logical Device 18h(PMC4)
#endif
    // Enable Logical Device 0Fh(Shared Memory)
    0x07, 0x0F, // Logical Device 0Fh(Shared Memory)
    0x60 ,0x02, // Set Base address 200h
    0x61 ,0x00,
#ifdef SUPPORT_SIO_H2RAM
    // Define EC internal RAM base address on LPC memory space.
    //0xF5, 0xC0, // HLPCRAMBA[15:12]) high nibble
    //0xF6, 0xFF, // HLPCRAMBA[23:16])
    0xF5 ,0x00, // Host LPC RAM Base Address b7-b4[15:12]  b3-b0 always=0
    0xF6 ,0x70, // Host LPC RAM Base Address b7-b0[23:16]
#endif
#ifdef SUPPORT_SHARED_MEM
    0xF4, 0x09, // MSWC Shared Memory
    0x30, 0x01, // MSWC Shared Memory
#else
    0xF4, 0x00, // MSWC Shared Memory
    0x30, 0x00, // MSWC Shared Memory
#endif
};

/*-----------------------------------------------------------------------------
 * @subroutine - Init_SIO
 * @function - Initialize EC SuperIO registers
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Init_SIO(void)
{
    BYTE    code *data_pntr;

    RSTS &= 0x3F;   //VCC Detector Option (VCCDO)
    RSTS |= 0x40;   //01: The VCC power status is treated as power-on.

    SET_MASK(LSIOHA, LKCFG);
    SET_MASK(IBMAE, CFGAE);
    SET_MASK(IBCTL, CSAE);

    ITempB01 = 0;
    data_pntr = initsio_table;
    while (ITempB01 < (sizeof(initsio_table) / 2))
    {
        IHIOA = 0;      // Set indirect Host I/O Address
        IHD = *data_pntr;
        while (IS_MASK_SET(IBCTL, CWIB));
        data_pntr++;

        IHIOA = 1;      // Set indirect Host I/O Address
        IHD = *data_pntr;
        while (IS_MASK_SET(IBCTL, CWIB));
        data_pntr++;
        ITempB01++;
    }
    CLEAR_MASK(LSIOHA, LKCFG);
    CLEAR_MASK(IBMAE, CFGAE);
    CLEAR_MASK(IBCTL, CSAE);

#ifdef SUPPORT_SIO_H2RAM
    Init_SysMemory2ECRam();
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Init_SysMemory2ECRam
 * @function - Init system memory cycle to EC external ram
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Init_SysMemory2ECRam(void)
{
#ifdef SUPPORT_SIO_H2RAM
    HRAMW0BA = 0x10;    // Define RAM window 0 base address 0x100
    HRAMW1BA = 0x00;    // Host RAM Windows 1 Base Address
    HRAMW0AAS = HostRamSize256Byte;    // Host RAM Window 0 Size 256 bytes
    HRAMW1AAS = 0x00;   // Host RAM Windows 1 Access Allow Size
    HRAMWC = Window0En;
#endif
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End */