/*-----------------------------------------------------------------------------
 * @file     | OEM_EVENT.C
 *-----------+-----------------------------------------------------------------
 * @function | Event Process
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | Kernel-14.4, OEM-M.Style Reference Code-1.0
 * @author   | OEM
 * @note     | Copyright(c)2010-2014, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


/*-----------------------------------------------------------------------------
 * Local Parameter Definition
 *---------------------------------------------------------------------------*/
#define SUPPORT_GPI_HOMEKEY     FALSE

#define _KBSET2_LEFT_WIN        0x1F
#define _KBSET2_VOL_UP          0x32
#define _KBSET2_VOL_DN          0x21
#define _KBSET2_P               0x4D
#define _KBSET2_Enter			0x5A
#define _KBSET2_PrintScr		0x7C

#if SUPPORT_LID_SWITCH
/*-----------------------------------------------------------------------------
 * @subroutine - Process_LID_Switch
 * @function - LID Switch Module
 * @Upstream -
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Process_LID_Switch(void)
{
    //-------------------------------------------------------------------------
    if (IS_LID_SW_CLOSE())
    {
        LID_OpenDebounce = 0;
        /* LCD Cover Close (LID CLOSE) */
        if (LID_Debounce < 5)
        {
            LID_Debounce++;
            LID_Resend = 40;
        }
        else
        {
            //-----------------------------------------------------------------
            SET_MASK(xEC_LID_STATUS, F_GPI_LID_STA);
				CLEAR_MASK(xEC_LID_STATUS,F_LID_STA);
            //-----------------------------------------------------------------
            if (LID_Resend == 40)
            {
                WriteSCI_Buffer(_SCIEVT_LID_CLOSED);
            }
            if (LID_Resend > 0)
            {
                LID_Resend--;
                if (LID_Resend == 0)
                {
                    WriteSCI_Buffer(_SCIEVT_LID_CLOSED);
                }
            }
            //-----------------------------------------------------------------
        }

    }
    else
    {
        LID_Debounce = 0;
        /* LCD Cover Open (LID OPEN) */
        if (LID_OpenDebounce < 5)
        {
            LID_OpenDebounce++;
			LID_OpenResend = 40;

        }
        else
        {

          
		if(IS_MASK_SET(xEC_LID_STATUS, F_GPI_LID_STA))
			{
			   
	           if(SysPowState==_SYSTEM_S3)
	            {
	                if (IS_PCH_SLP_S3_LO())
	                {
	                    PCH_PWRBTN_LO();
							DelayXms(80);
	                    PCH_PWRBTN_HI();
	                }
					LID_OpenResend = 40;
	           	}

			 if(SysPowState==_SYSTEM_S0)
			 	{
					if (LID_OpenResend == 40)
					{
					WriteSCI_Buffer(_SCIEVT_LID_OPEN);
					//CLEAR_MASK(xEC_LID_STATUS, F_GPI_LID_STA);
						SET_MASK(xEC_LID_STATUS,F_LID_STA);
					}
					if (LID_OpenResend > 0)
					{
						LID_OpenResend--;
						if (LID_OpenResend == 0)
						{
						WriteSCI_Buffer(_SCIEVT_LID_OPEN);
						CLEAR_MASK(xEC_LID_STATUS, F_GPI_LID_STA);
					
						}
					}
        		}
			}
            //-----------------------------------------------------------------
        }
    }

}
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------

#if SUPPORT_GPI_HOMEKEY
/*-----------------------------------------------------------------------------
 * @subroutine - Service_GPI_Homekey
 * @function - Service_GPI_Homekey
 * @Upstream -
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Service_GPI_Homekey(void)
{
    if (LockHomekeyTimer > 0)
    {
        LockHomekeyTimer--;
        return;
    }
    if (IS_PCH_SLP_S4_LO())
    {
        /* System in S4,S5 */
        return;
    }
    if (IS_PCH_SLP_S3_LO())
    {
        /* System in S3 */
        if (IS_HOMEKEY_SW_UP())
        {
            WaitHomekeyRelease = 0;
            return;
        }
        if (WaitHomekeyRelease > 0)
        {
            return;
        }
        LockHomekeyTimer = 20;
        WaitHomekeyRelease = 1;
        PCH_PWRBTN_LO();
        Delay1MS(20);
        PCH_PWRBTN_HI();
        return;
    }
    if (IS_HOMEKEY_SW_UP())
    {
        if (DebounceHomekey > 2)
        {
            e0_prefix_code(0x1F, BREAK_EVENT);
        }
        DebounceHomekey = 0;
        return;
    }
    else
    {
        if (DebounceHomekey < 2)
        {
            DebounceHomekey++;
        }
        else if (DebounceHomekey == 2)
        {
            DebounceHomekey++;
            e0_prefix_code(0x1F, MAKE_EVENT);
        }
    }
}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - Service_GPI_Event
 * @function - Service_GPI_Event
 * @Upstream - Hook_Timer50msEventC
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Service_GPI_Event(void)
#if Support_CombinationKey
		{
			//-------------------------------------------------------------------------
			if (IS_PCH_SLP_S3_LO())
			{
				return;
			}
			if(PowSwDownTimer > 0)
			{
				return;
			}
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			if (IS_HOMEKEY_SW_DN())
			{
				if (DebounceGPI3 == 0)
				{
					DebounceGPI3 = 3;
					//WriteSCI_Buffer(_SCIEVT_WINDOWS_HOME);
					//e0_prefix_code(_KBSET2_LEFT_WIN, MAKE_EVENT);
					ViberatorTimer = 10;	//120141223V18		 
				}
				if(DebounceGPI1 == 0)
					{
						if ((IS_VOLUME_DOWN_DN()))
							{
							 
									if (DebounceGPI4 < 4)
									{
										DebounceGPI4++;
										if (DebounceGPI4 == 1)
										{
										e0_prefix_code(_KBSET2_LEFT_WIN, MAKE_EVENT);
										}
										else if (DebounceGPI4 == 3)
										{
										e0_prefix_code(_KBSET2_PrintScr, MAKE_EVENT);
										}
									}
									else
									{
										DebounceGPI4 = 10;
									}
									SET_MASK(DebounceGPIFlag, F_Volemdn_press);
							}
						else
							{
							if (DebounceGPI4 > 0)
								{
									if (DebounceGPI4==10)
									e0_prefix_code(_KBSET2_PrintScr, BREAK_EVENT);
									if (DebounceGPI4==1)
									e0_prefix_code(_KBSET2_LEFT_WIN, BREAK_EVENT);
									DebounceGPI4 --;
								}
													}
					}
				if(DebounceGPI2 == 0)
					{
							if ((IS_VOLUME_UP_DN()))
							{
							 
									if (DebounceGPI5 < 4)
									{
										DebounceGPI5++; 		
										if (DebounceGPI5 == 1)
										{
										e0_prefix_code(_KBSET2_LEFT_WIN, MAKE_EVENT);
										}
										else if (DebounceGPI5 == 3)
										{
										e0_prefix_code(_KBSET2_Enter, MAKE_EVENT); //ENTER KEY
										}
									}
									else
									{
										DebounceGPI5 = 10;
									}
									SET_MASK(DebounceGPIFlag, F_Volemup_press);
							}
						else
							{
								if (DebounceGPI5 > 0)
								{
									if (DebounceGPI5 ==10)
									e0_prefix_code(_KBSET2_Enter, BREAK_EVENT);
									if (DebounceGPI5 ==1)
									e0_prefix_code(_KBSET2_LEFT_WIN, BREAK_EVENT);
									DebounceGPI5 --;
								}
							
							}
					}
				
				
				if(PowSwDebounce == 0)
					{
						if (IS_EC_PWRSW_DN())
						{
						 
								if (DebounceGPI6 < 5)
								{
									DebounceGPI6++;
									if(DebounceGPI6 ==1)
									{
									e0_prefix_code(0x11, MAKE_EVENT);//Alt key
									}
									else if (DebounceGPI6 == 2)
									{
									e0_prefix_code(0x14, MAKE_EVENT);//Control key
									}
									else if(DebounceGPI6 == 3)
									{
									e0_prefix_code(0x71, MAKE_EVENT); //del key
									}
									else
									{
									DebounceGPI6 = 10;
									}
									SET_MASK(DebounceGPIFlag, F_pwrbtn_press);
								}
							}
					else
						{
						if(DebounceGPI6>0)
							{
								if (DebounceGPI6 == 10)
								e0_prefix_code(0x71, BREAK_EVENT); //del key
								if (DebounceGPI6 == 5)
								e0_prefix_code(0x14, BREAK_EVENT); //Control key
								if (DebounceGPI6 == 1)
								e0_prefix_code(0x11, BREAK_EVENT); //alt key
								DebounceGPI6 --;
							}
						}
	
				}
				}
			else
			{
				if(DebounceGPI3 > 0) 
				{
					if(DebounceGPIFlag > 0) 
						{
						DebounceGPIFlag = 0;
						DebounceGPI3 = 0;
						}
					else
						{
							if(DebounceGPI3 == 3)
								e0_prefix_code(_KBSET2_LEFT_WIN, MAKE_EVENT);
							if(DebounceGPI3 == 1)
								e0_prefix_code(_KBSET2_LEFT_WIN, BREAK_EVENT);
							DebounceGPI3--;
						}
				}	
			}
	
			//-------------------------------------------------------------------------
			//Volume+******************************************************************
			//-------------------------------------------------------------------------
		if (DebounceGPI5 > 0)
			{
				if (IS_VOLUME_UP_UP())
				{
					e0_prefix_code(_KBSET2_Enter, BREAK_EVENT);
					e0_prefix_code(_KBSET2_LEFT_WIN, BREAK_EVENT);
					DebounceGPI5 = 0;
				}
			}
								
			//-------------------------------------------------------------------------
		 if((DebounceGPI5 == 0)&&(DebounceGPI1==0))
			{
			if (IS_VOLUME_UP_DN())
			{
				if (DebounceGPI2 < 1)
				{
					DebounceGPI2++;
				}
				else if (DebounceGPI2 == 1)
				{
					DebounceGPI2++;
					//WriteSCI_Buffer(_SCIEVT_VOLUME_UP);
					e0_prefix_code(_KBSET2_VOL_UP, MAKE_EVENT);
				}
				else if (DebounceGPI2 < 11)
				{
					DebounceGPI2++;
					if (DebounceGPI2 == 11)
					{
						//WriteSCI_Buffer(_SCIEVT_VOLUME_UP);
						e0_prefix_code(_KBSET2_VOL_UP, REPEAT_EVENT);//20141027
		
						DebounceGPI2 = 10;
					}
				}
				else
				{
					DebounceGPI2 = 10;
				}
			}
			else
			{
				if (DebounceGPI2 > 1)
				{
					e0_prefix_code(_KBSET2_VOL_UP,BREAK_EVENT);
				}
				DebounceGPI2 = 0;
			}
			}
			//-------------------------------------------------------------------------
			//Volume-******************************************************************
			//-------------------------------------------------------------------------
			if (DebounceGPI4 > 0)
				{
					if (IS_VOLUME_DOWN_UP())
						{
						e0_prefix_code(_KBSET2_PrintScr, BREAK_EVENT);
						e0_prefix_code(_KBSET2_LEFT_WIN, BREAK_EVENT);
						DebounceGPI4 = 0;
						}
				}
	
			//-------------------------------------------------------------------------
			if((DebounceGPI4 == 0)&&(DebounceGPI2 ==0))
				{
					   if (IS_VOLUME_DOWN_DN())
					{
						if (DebounceGPI1 < 1)
						{
							DebounceGPI1++;
						}
						else if (DebounceGPI1 == 1)
						{
							DebounceGPI1++;
							//WriteSCI_Buffer(_SCIEVT_VOLUME_DOWN);
							e0_prefix_code(_KBSET2_VOL_DN, MAKE_EVENT);
						}
						else if (DebounceGPI1 < 12)
						{
							DebounceGPI1++;
							if (DebounceGPI1 == 12)
							{
								//WriteSCI_Buffer(_SCIEVT_VOLUME_DOWN);
								e0_prefix_code(_KBSET2_VOL_DN, REPEAT_EVENT);//20141027
								DebounceGPI1 = 10;
							}
						}
						else
						{
							DebounceGPI1 = 10;
						}
					}
					else
					{
						if (DebounceGPI1 > 1)
						{
							e0_prefix_code(_KBSET2_VOL_DN, BREAK_EVENT);
						}
						DebounceGPI1 = 0;
					}
				}
	
			//-------------------------------------------------------------------------
		}
#else
	{
//#if 1
				//-------------------------------------------------------------------------
				if (IS_PCH_SLP_S3_LO())
				{
					return;
				}
				if(PowSwDownTimer > 0)
				{
					return;
				}
				//-------------------------------------------------------------------------
				if (IS_HOMEKEY_SW_DN())
				{
					if (DebounceGPI3 == 0)
					{
						DebounceGPI3 = 1;
						//WriteSCI_Buffer(_SCIEVT_WINDOWS_HOME);
						e0_prefix_code(_KBSET2_LEFT_WIN, MAKE_EVENT);
						ViberatorTimer = 10;	//120141223V18		 
					}
				}
				else
				{
					if(DebounceGPI3 > 0) 
					{
						e0_prefix_code(_KBSET2_LEFT_WIN, BREAK_EVENT);
					}
					DebounceGPI3 = 0;
				
				}
		
									
				//-------------------------------------------------------------------------
			 //if(DebounceGPI5 == 0)
			//	{
				if (IS_VOLUME_UP_DN())
				{
					if (DebounceGPI2 < 1)
					{
						DebounceGPI2++;
					}
					else if (DebounceGPI2 == 1)
					{
						DebounceGPI2++;
						//WriteSCI_Buffer(_SCIEVT_VOLUME_UP);
						e0_prefix_code(_KBSET2_VOL_UP, MAKE_EVENT);
					}
					else if (DebounceGPI2 < 11)
					{
						DebounceGPI2++;
						if (DebounceGPI2 == 11)
						{
							//WriteSCI_Buffer(_SCIEVT_VOLUME_UP);
							e0_prefix_code(_KBSET2_VOL_UP, REPEAT_EVENT);//20141027
			
							DebounceGPI2 = 10;
						}
					}
					else
					{
						DebounceGPI2 = 10;
					}
				}
				else
				{
					if (DebounceGPI2 > 1)
					{
						e0_prefix_code(_KBSET2_VOL_UP,BREAK_EVENT);
					}
					DebounceGPI2 = 0;
				}
				//}
		
				//-------------------------------------------------------------------------
				//if(DebounceGPI4 == 0)
				//	{
						   if (IS_VOLUME_DOWN_DN())
						{
							if (DebounceGPI1 < 1)
							{
								DebounceGPI1++;
							}
							else if (DebounceGPI1 == 1)
							{
								DebounceGPI1++;
								//WriteSCI_Buffer(_SCIEVT_VOLUME_DOWN);
								e0_prefix_code(_KBSET2_VOL_DN, MAKE_EVENT);
							}
							else if (DebounceGPI1 < 12)
							{
								DebounceGPI1++;
								if (DebounceGPI1 == 12)
								{
									//WriteSCI_Buffer(_SCIEVT_VOLUME_DOWN);
									e0_prefix_code(_KBSET2_VOL_DN, REPEAT_EVENT);//20141027
									DebounceGPI1 = 10;
								}
							}
							else
							{
								DebounceGPI1 = 10;
							}
						}
						else
						{
							if (DebounceGPI1 > 1)
							{
								e0_prefix_code(_KBSET2_VOL_DN, BREAK_EVENT);
							}
							DebounceGPI1 = 0;
						}
				//	}
		
				//-------------------------------------------------------------------------
	}


#endif

/*-----------------------------------------------------------------------------
 * @subroutine - Service_CPU_T_Event
 * @function - Service_CPU_T_Event
 * @upstream - service_500mS_B
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Service_CPU_T_Event(void)
    {
        //-------------------------------------------------------------------------
        if (IS_PCH_SLP_S3_LO())
        {
            return;
        }
        //-------------------------------------------------------------------------
        /* if (xEC_CPUT_EventTimer > 0)
        {
            xEC_CPUT_EventTimer--;
        }
        else
        {
            if (xEC_CPUT_SendEvent > 0)
            {
                xEC_CPUT_SendEvent--;
                WriteSCI_Buffer(_SCIEVT_CPU_T);
                xEC_CPUT_EventTimer = 10;
            }
        }
        //-------------------------------------------------------------------------
           if (xEC_PECI_CPU_T >= xEC_CPUT_HiLimit)
            {
                xEC_CPUT_HiLimit = xEC_PECI_CPU_T + 3;
                if (xEC_PECI_CPU_T >= 3)
                {
                    xEC_CPUT_LoLimit = xEC_PECI_CPU_T - 3;
                }
                xEC_CPUT_SendEvent = 2;
            }
            else if (xEC_PECI_CPU_T < xEC_CPUT_LoLimit)
            {
                xEC_CPUT_HiLimit = xEC_PECI_CPU_T + 3;
                if (xEC_PECI_CPU_T >= 3)
                {
                    xEC_CPUT_LoLimit = xEC_PECI_CPU_T - 3;
                    xEC_CPUT_SendEvent = 2;
                }
                else
                {
                    xEC_CPUT_LoLimit = 0;
                }
            }*/
        //-------------------------------------------------------------------------

        //-------------------------------------------------------------------------

        if (xEC_CPUT_SendEvent > 0)
            {
                xEC_CPUT_SendEvent--;
            }
        else
            {

                if (IS_MASK_CLEAR(xEC_ThermalSource, F_PECI_HOT))
                {
                    SET_MASK(xEC_ThermalSource, F_PECI_HOT);
                    //WriteSCI_Buffer(_SCIEVT_TrigPoint);

                }
            }


        if(xEC_PECI_CPU_T > PECICPUTooHot)
            {
              xEC_CPUT_SendEvent = 2;
            }
        if(xEC_PECI_CPU_T < PECICPUTooHot)
            {
              CLEAR_MASK(xEC_ThermalSource, F_PECI_HOT);
            }

        //-------------------------------------------------------------------------
    }

//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End */
