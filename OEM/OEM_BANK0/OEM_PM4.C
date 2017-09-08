/*-----------------------------------------------------------------------------
 * @file     | OEM_PM5.C
 * ----------+-----------------------------------------------------------------
 * @function | Power Management Channel-5 Command & Data Handle
 * ----------+-----------------------------------------------------------------
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
#define DEBUG_PMC4                  FALSE


/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_PMC4
#define PMC4_RamDebug(x)        RamDebug(x)
#else
#define PMC4_RamDebug(x)        {}
#endif
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * @subroutine - service_pci5
 * @function - Service power management channel-5
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void service_pci5(void)
{


}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_PM4.C */