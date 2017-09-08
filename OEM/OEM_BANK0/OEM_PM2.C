/*-----------------------------------------------------------------------------
 * @file     | OEM_PM2.C
 * ----------+-----------------------------------------------------------------
 * @function | Power Management Channel-2 Command & Data Handle
 * ----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2013, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_PMC2              FALSE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_PMC2
#define PMC2_RamDebug(x)        RamDebug(x)
#else
#define PMC2_RamDebug(x)        {}
#endif
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// The function of debuging 68 port
//----------------------------------------------------------------------------
void Hook_68Port(BYTE PM2Data)
{

}

//----------------------------------------------------------------------------
// The function of debuging 6C port
//----------------------------------------------------------------------------
void Hook_6CPort(BYTE PM2Cmd)
{
#if Support_RTC_hang25_wakeup
	if (PM2Cmd == 0x04)
    {
		Forece_Shutdown_timer = 4000;
		xEC_RTC_test_counter++;
    }
#endif

	if (PM2Cmd == 0xC9)
    {
		I2C_DD_Resend = 2;
    }
    if (PM2Cmd == 0xDC)
    {
        EA = 0;
        CacheDma(0, ITE_WinFlash);
        EA = 0;
        ITE_WinFlash();
        SCRA1H = 0x03;
        Reload_EC_Ver();
    }
}

//----------------------------------------------------------------------------
// Process Command/Data received from System via 68/6C interface
//----------------------------------------------------------------------------
void service_pci3(void)
{
    if (IS_MASK_CLEAR(PM2STS, P_IBF))
    {
        return;
    }
    if (PM2STS & P_C_D)
    {
        /* Command In */
        PM2Cmd = PM2DI;

        PMC2_RamDebug(0x6C);
        PMC2_RamDebug(PM2Cmd);

        PM2DataCount = 0;
        PM2Data2 = 0;
        EnablePMCIBFInt();
        Hook_6CPort(PM2Cmd);
    }
    else
    {
        /* Data In */
        PM2Data = PM2DI;

        PMC2_RamDebug(0x68);
        PMC2_RamDebug(PM2Data);

        EnablePMCIBFInt();
        Hook_68Port(PM2Data);
    }
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_PM2.C */
