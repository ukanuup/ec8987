/*-----------------------------------------------------------------------------
 * @file     | OEM_PM3.C
 * ----------+-----------------------------------------------------------------
 * @function | Power Management Channel-3 Command & Data Handle
 * ----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Kernel Copyright(c)2012, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_PMC3                  FALSE


/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_PMC3
#define PMC3_RamDebug(x)        RamDebug(x)
#else
#define PMC3_RamDebug(x)        {}
#endif
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - service_pci4
 * @function - Service power management channel-4
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void service_pci4(void)
{


}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_PM3.C */