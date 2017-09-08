/*-----------------------------------------------------------------------------
 * @file     | OEM_6064.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_6064.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_6064_H
#define OEM_6064_H

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
extern void Hook_60Port(BYTE KBHIData);
extern void Hook_64Port(BYTE KBHICmd);
extern void Hook_Keyboard_Cmd(BYTE kbcmd);
extern void Hook_Keyboard_Cmd_Parameter(BYTE kbcmdp);
extern void Hook_Mouse_D4Cmd(BYTE mscmd);
extern void Hook_Mouse_90Cmd(BYTE mscmd);
extern void Hook_Mouse_91Cmd(BYTE mscmd);
extern void Hook_Mouse_92Cmd(BYTE mscmd);
extern void Hook_Mouse_93Cmd(BYTE mscmd);

//-----------------------------------------------------------------------------
#endif  //OEM_6064_H
/*-----------------------------------------------------------------------------
 * End of OEM_6064.H */