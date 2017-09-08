/*-----------------------------------------------------------------------------
 * @file     | OEM_PS2.H
 * ----------+-----------------------------------------------------------------
 * @function | OEM_PS2.C Function prototype include definition
 * ----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_PS2_H
#define OEM_PS2_H

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
extern void Hook_ECRespondtoMouseDriver(BYTE mscmd);
extern void Hook_service_ps2(BYTE ps2_channel, BYTE ps2_data);
extern void Hook_DisablePS2Port_0(void);
extern void Hook_DisablePS2Port_1(void);
extern void Hook_DisablePS2Port_2(void);
extern void Hook_EnablePS2Port_0(void);
extern void Hook_EnablePS2Port_1(void);
extern void Hook_EnablePS2Port_2(void);
extern void Hook_TPOnlyLowLevelFunc(void);

//#ifdef Hook_Func_DisableTP   // For internal TB disable
#define InternalTB_Disable  0x01
#define InternalTB_Enable   0x00
extern BYTE Hook_DisableInternalTB(void);
//#endif

//-----------------------------------------------------------------------------
#endif  //OEM_PS2_H
/*-----------------------------------------------------------------------------
 * End of OEM_PS2.H */