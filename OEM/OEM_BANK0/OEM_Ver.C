/*-----------------------------------------------------------------------------
 * @file     | OEM_Ver.C
 *-----------+-----------------------------------------------------------------
 * @function | Firmware version control
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2014, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


//-----------------------------------------------------------------------------
// Project Information
//-----------------------------------------------------------------------------
const unsigned char code SIGN_HEAD[] = {"_ITE$"};    /* Fixed Tag */
const unsigned char code SIGN_MUFG[] = {_BUILD_MUFG};
const unsigned char code SIGN_DATE[] = {_BUILD_DATE};
const unsigned char code SIGN_TIME[] = {_BUILD_TIME};
const unsigned char code SIGN_MODL[] = {_BUILD_MODEL};
const unsigned char code SIGN_GUST[] = {_BUILD_GUEST};
const unsigned char code SIGN_PCBV[] = {_BUILD_BOARD};
const unsigned char code SIGN_ECVR[] = {_BUILD_ECVER};
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Reload_EC_Ver(void)
{
    xEC_MainVersion = _EC_MAIN_VER;
    xEC_SubVersion  = _EC_SUB_VER;
    xEC_TestVersion = _EC_TEST_VER;
    //xEC_InfoBase = &SIGN_MUFG;
    I2C_EJ898A_CODING_VER = _EC_CODING_VER;
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_Ver.C */