/*-----------------------------------------------------------------------------
 * @file     | OEM_DEBUG.C
 *-----------+-----------------------------------------------------------------
 * @function | Process Debug Function
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2014, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * @subroutine - RamDebug
 * @function - Debug code to RAM spaces
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void RamDebug(unsigned char dbgcode)
{
    PORT_BYTE_PNTR ClearIndex;
    PORT_BYTE_PNTR byte_register_pntr;
    BYTE    index;
    BYTE    i;

    byte_register_pntr = DebugRamAddr + DebugRamRange;
    index = *byte_register_pntr;
    *byte_register_pntr += 1;

    if (*byte_register_pntr == DebugRamRange)
    {
        *byte_register_pntr = 0;
        ClearIndex = DebugRamAddr;

        for (i = 0; i < DebugRamRange; i++)
        {
            *ClearIndex = 0x00;
            ClearIndex++;
        }
    }

    byte_register_pntr = DebugRamAddr + index;
    *byte_register_pntr = dbgcode;
}
//-----------------------------------------------------------------------------
void RamDebugP80(unsigned char dbgcode)
{
    PORT_BYTE_PNTR ClearIndex;
    PORT_BYTE_PNTR byte_register_pntr;
    BYTE    index;
    BYTE    i;

    byte_register_pntr = DebugRamAddrP80+ DebugRamRange;
    index = *byte_register_pntr;
    *byte_register_pntr += 1;

    if (*byte_register_pntr == DebugRamRange)
    {
        *byte_register_pntr = 0;
        ClearIndex = DebugRamAddrP80;

        for (i = 0; i < DebugRamRange; i++)
        {
           // *ClearIndex = 0x00;
           // ClearIndex++;
        }
    }

    byte_register_pntr = DebugRamAddrP80 + index;
    *byte_register_pntr = dbgcode;
}
//-----------------------------------------------------------------------------
void RamDebugh25(unsigned char dbgcode)
{
    PORT_BYTE_PNTR ClearIndex;
    PORT_BYTE_PNTR byte_register_pntr;
    BYTE    index;
    BYTE    i;

    byte_register_pntr = DebugRamAddrh25+ DebugRamRange;
    index = *byte_register_pntr;
    *byte_register_pntr += 1;

    if (*byte_register_pntr == DebugRamRange)
    {
        *byte_register_pntr = 0;
        ClearIndex = DebugRamAddrh25;

        for (i = 0; i < DebugRamRange; i++)
        {
           // *ClearIndex = 0x00;
           // ClearIndex++;
        }
    }

    byte_register_pntr = DebugRamAddrh25 + index;
    *byte_register_pntr = dbgcode;
}
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * End of OEM_DEBUG.C */