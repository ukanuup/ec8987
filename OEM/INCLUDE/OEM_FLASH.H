/*-----------------------------------------------------------------------------
 * @file     | OEM_FLASH.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_FLASH.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_FLASH_H
#define OEM_FLASH_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void RamProgram(BYTE useport);
extern void LPC_RamCode(void);
extern void ITE_WinFlash(void);
extern void Do_SPI_Write_1Byte(XBYTE *DataPointer,BYTE Addr2,BYTE Addr1,BYTE Addr0);
extern BYTE Read_flash_Byte(BYTE FA2,BYTE FA1,BYTE FA0);
extern void SPI_Write_1Byte(void);
extern void Eflash_Write_1Byte(void);
extern void Do_Eflash_Write_1Byte(BYTE OneByte,BYTE Addr2,BYTE Addr1,BYTE Addr0);
extern BYTE Read_Eflash_Byte(BYTE FA2,BYTE FA1,BYTE FA0);

//-----------------------------------------------------------------------------
#endif  //OEM_FLASH_H
/*-----------------------------------------------------------------------------
 * End of OEM_FLASH.H */