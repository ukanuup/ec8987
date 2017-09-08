/*-----------------------------------------------------------------------------
 * @file     | OEM_FAN.C
 *-----------+-----------------------------------------------------------------
 * @function | FAN & Thermal control
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
#define DEBUG_FAN               FALSE

//-----------------------------------------------------------------------------
/* Fan Control & Fan Tachometer Parameter */
#define TACH1P                  2
#define TACH2P                  2

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_FAN
#define FAN_RamDebug(x)         RamDebug(x)
#else
#define FAN_RamDebug(x)         {}
#endif
//-----------------------------------------------------------------------------

#if SUPPORT_FAN_CONTROL
/*-----------------------------------------------------------------------------
 * @subroutine - GetFanRPM
 * @function - PWM/TACHX MODULE
 *             Calculation Fan Tachometer to Fan Speed (R.P.M)
 *             Fan Speed (R.P.M)=60/(1/fs sec * {FnTMRR,FnTLRR) * P )
 * @Upstream - Hook_Timer1SecEventA
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
WORD GetFanRPM(BYTE FnTMRR, BYTE FnTLRR)
{
    if ((FnTMRR != 0x00) || (FnTLRR != 0x00))
    {
        if (((FnTMRR * 256) + FnTLRR) < 7000)
        {
            ITempW01 = (4312500 / TACH1P / ((FnTMRR * 256) + FnTLRR));
        }
        else
        {
            ITempW01 = 7000;   /* MAX */
        }
    }
    else
    {

    }
    return (ITempW01);
}

/*-----------------------------------------------------------------------------
 * @subroutine - Fan1_Control
 * @function - Fan Control
 * @Upstream - None
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Fan1_Control(void)
{



}




//-----------------------------------------------------------------------------
#endif  //SUPPORT_FAN_CONTROL

/*-----------------------------------------------------------------------------
 * End */