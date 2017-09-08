/*-----------------------------------------------------------------------------
 * @file     | OEM_Ver.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_Ver.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_Ver_H
#define OEM_Ver_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/
extern const unsigned char code SIGN_MUFG[];
extern const unsigned char code SIGN_DATE[];
extern const unsigned char code SIGN_MODL[];
extern const unsigned char code SIGN_GUST[];
extern const unsigned char code SIGN_PCBV[];
extern const unsigned char code SIGN_ECVR[];

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Reload_EC_Ver(void);

#endif
/*-----------------------------------------------------------------------------
 * End of OEM_Ver.H */