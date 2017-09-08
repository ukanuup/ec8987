/*-----------------------------------------------------------------------------
 * @file     | OEM_INIT.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_INIT.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_INI_H
#define OEM_INI_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/
typedef struct REG_INIT_DEF
{
    XBYTE   *address;
    BYTE    initdata;
} sREG_INIT_DEF;
//-----------------------------------------------------------------------------
typedef struct DMAScratchSRAM
{
    XBYTE   *scarh;
    XBYTE   *scarm;
    XBYTE   *scarl;
} sDMAScratchSRAM;

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Oem_StartUp(void);
extern void Oem_Initialization(void);
extern void Init_ClearRam(void);
extern void Hook_ECExitFollowMode(void);
extern BYTE Hook_ECRetunrMainFuncKeepCondition(void);
extern void Init_SMBus(void);

extern void Init_Cache(void);

#if SUPPORT_EC_RAM2K
extern void CacheDma(BYTE sramnum, WORD addr);
#endif

//-----------------------------------------------------------------------------
#endif  //OEM_INI_H
/*-----------------------------------------------------------------------------
 * End of OEM_INIT.H */