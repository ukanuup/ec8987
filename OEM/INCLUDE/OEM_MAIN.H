/*-----------------------------------------------------------------------------
 * @file     | OEM_MAIN.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_MAIN.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_MAIN_H
#define OEM_MAIN_H

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
extern void Hook_Timer1msEvent(IBYTE EventId);
extern void Hook_Timer5msEvent(void);
extern void Hook_Timer10msEventA(void);
extern void Hook_Timer10msEventB(void);
extern void Hook_Timer50msEventA(void);
extern void Hook_Timer50msEventB(void);
extern void Hook_Timer50msEventC(void);
extern void Hook_Timer100msEventA(void);
extern void Hook_Timer100msEventB(void);
extern void Hook_Timer100msEventC(void);
extern void Hook_Timer500msEventA(void);
extern void Hook_Timer500msEventB(void);
extern void Hook_Timer500msEventC(void);
extern void Hook_Timer1SecEventA(void);
extern void Hook_Timer1SecEventB(void);
extern void Hook_Timer1SecEventC(void);
extern void Hook_Timer1MinEvent(void);
extern void service_OEM_1(void);
extern void service_OEM_2(void);
extern void service_OEM_3(void);
extern void service_OEM_4(void);
extern void Hook_main_service_H(void);
extern void Hook_main_service_L(void);
extern BYTE Hook_Only_Timer1msEvent(void);
extern BYTE OEM_SkipMainServiceFunc(void);
#if SupportP80_Restore
extern void P80_Write_To_eFlash(void);
extern void P80_Save_to_eFLash(void);
#endif

//-----------------------------------------------------------------------------
#endif  //OEM_MAIN_H
/*-----------------------------------------------------------------------------
 * End of OEM_ASM.H */
