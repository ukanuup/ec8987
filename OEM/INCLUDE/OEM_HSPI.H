/*-----------------------------------------------------------------------------
 * @file     | OEM_HSPI.H
 * ----------+-----------------------------------------------------------------
 * @function | OEM_HSPI.C Function prototype include definition
 * ----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_HSPI_H
#define OEM_HSPI_H

//*****************************************************************************
// HSPI setting selection
//*****************************************************************************
/*-----------------------------------------------------------------------------
 * HSPI_Setting??:
 *  01: Host[All/20MHz], EC[READ(03h)/33MHz]
 *  02: Host[FREAD/33MHz,Otherwise/20MHz,DOFR isn't supported],
 *      EC[1.READ(03h)/33MHz, and 2.FREAD(0Bh)/66MHz, and 3.Others/66MHz]
 *  03: Host[FREAD/33MHz,Otherwise/20MHz,DOFR isn't supported],
 *      EC[1.READ(03h)/33MHz, and 2.Dual(BBh)/33MHz]
 *  04: Host[DOFR/50MHz Otherwise/20MHz FREAD isn't supported],
 *      EC[1.READ(03h)/33MHz, and 2.DIOFR(BBh)/66MHz, and 3.Others/66MHz]
 *  05: Host[All/20MHz],
 *      EC[1.READ(03h)/33MHz, and 2.FREAD(0Bh)/66MHz, and 3.Others/66MHz]
 *  06: Host[All/20MHz],
 *      EC[1.READ(03h)/33MHz, and 2.Dual(BBh)/33MHz]
 *  07: Host[DOFR/33MHz,Otherwise/20MHz,FREAD isn't supported],
 *      EC[1.READ(03h)/33MHz, and 2.DIOFR(BBh)/66MHz, and 3.Others/66MHz]
 *---------------------------------------------------------------------------*/
//#define HSPI_Setting01
//#define HSPI_Setting02
//#define HSPI_Setting03
//#define HSPI_Setting04
#define HSPI_Setting05
//#define HSPI_Setting06
//#define HSPI_Setting07

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define T_HSPI_ISRTime          Timer_85ms

#define PLLFreqSetting03        0x03    // 32.3 MHZ PLL frequency
#define PLLFreqSetting05        0x05    // 46.0 MHZ PLL frequency
#define PLLFreqSetting07        0x07    // 64.5 MHZ PLL frequency

#define SPIReadMode_0           0x00    // Read cycle
#define SPIReadMode_1           0x01    // Fast read cycle
#define SPIReadMode_2           0x02    // Fast read dual output
#define SPIReadMode_3           0x03    // Fast read dual input/output

#define HSPI_RequestSelection_0 0x00    // Setting 0, 1, 2, and 3
#define HSPI_RequestSelection_1 0x01    // Setting 6 and 7
#define HSPI_RequestSelection_2 0x02    // Setting 5
#define HSPI_RequestSelection_3 0x03    // Reserved

#if HSPI
//*****************************************************************************
// Define : HSPI deffering mode, Non define : HSPI non deffering mode
//*****************************************************************************
//#define HSPI_DefferingMode    // Define : HSPI is deffering mode
//-----------------------------------------------------------------------------
#ifdef HSPI_Setting01
#define PLLFrequency    PLLFreqSetting03        // 32.3MHZ PLL frequency
#define SPIReadMode     SPIReadMode_0           // Read cycle
#define HSRSMode        HSPI_RequestSelection_0 // HSPI request 1, 2, 3, and 4
#endif
//-----------------------------------------------------------------------------
#ifdef HSPI_Setting02
#define PLLFrequency    PLLFreqSetting07        // 64.5 MHZ PLL frequency
#define SPIReadMode     SPIReadMode_1           // Fast read cycle
#define HSRSMode        HSPI_RequestSelection_0 // HSPI request 1, 2, 3, and 4
#endif
//-----------------------------------------------------------------------------
#ifdef HSPI_Setting03
#define PLLFrequency    PLLFreqSetting03        // 32.3 MHZ PLL frequency
#define SPIReadMode     SPIReadMode_3           // Fast read dual input/output
#define HSRSMode        HSPI_RequestSelection_0 // HSPI request 1, 2, 3, and 4
#endif
//-----------------------------------------------------------------------------
#ifdef HSPI_Setting04
#define PLLFrequency    PLLFreqSetting07        // 64.5 MHZ PLL frequency
#define SPIReadMode     SPIReadMode_3           // Fast read dual input/output
#define HSRSMode        HSPI_RequestSelection_0 // HSPI request 1, 2, 3, and 4
#endif
//-----------------------------------------------------------------------------
#ifdef HSPI_Setting05
#define PLLFrequency    PLLFreqSetting07        // 64.5 MHZ PLL frequency
#define SPIReadMode     SPIReadMode_1           // Fast read cycle
#define HSRSMode        HSPI_RequestSelection_2 // HSPI request Setting 5
#endif
//-----------------------------------------------------------------------------
#ifdef HSPI_Setting06
#define PLLFrequency    PLLFreqSetting03        // 32.3 MHZ PLL frequency
#define SPIReadMode     SPIReadMode_3           // Fast read dual input/output
#define HSRSMode        HSPI_RequestSelection_1 // HSPI request Setting 6 and 7
#endif
//-----------------------------------------------------------------------------
#ifdef HSPI_Setting07
#define PLLFrequency    PLLFreqSetting07        // 64.5 MHZ PLL frequency
#define SPIReadMode     SPIReadMode_3           // Fast read dual input/output
#define HSRSMode        HSPI_RequestSelection_1 // HSPI request Setting 6 and 7
#endif
//-----------------------------------------------------------------------------
// HSPI share End
//-----------------------------------------------------------------------------
#else
//-----------------------------------------------------------------------------
// LPC share
//-----------------------------------------------------------------------------
#if 0
//*****************************************************************************
// EC SPI [fast read, 64.5MHZ]
//*****************************************************************************
#define PLLFrequency    PLLFreqSetting07    // 64.5 MHZ PLL frequency
#define SPIReadMode     SPIReadMode_1       // Fast read cycle
#endif
#if 0
//*****************************************************************************
// EC SPI [read, 46MHZ]
//*****************************************************************************
#define PLLFrequency    PLLFreqSetting05    // 46 MHZ PLL frequency
#define SPIReadMode     SPIReadMode_0       // read cycle
#endif
#if 1
//*****************************************************************************
// EC SPI [read, 32.3MHZ]
//*****************************************************************************
#define PLLFrequency    PLLFreqSetting03    // 32.3 MHZ PLL frequency
#define SPIReadMode     SPIReadMode_0       // read cycle
#endif
//-----------------------------------------------------------------------------
// LPC share End
//-----------------------------------------------------------------------------
#endif
//*****************************************************************************

/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void FuncAt_0xFE00(void);
extern void Init_HSPI(void);
extern void Enable_HSPI(void);
extern void Disable_HSPI(void);
//extern void HSPI_RamCode(void);
extern void HSPI_CmdRamCode(void);
extern void ChangePLLFrequency(BYTE newseting);
extern void ChangeSPIFlashReadMode(BYTE Mode);
extern void ChangeHSRSMode(BYTE Mode);


//-----------------------------------------------------------------------------
#endif  //OEM_HSPI_H
/*-----------------------------------------------------------------------------
 * End of OEM_HSPI.H */