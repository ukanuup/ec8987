/*-----------------------------------------------------------------------------
 * @file     | OEM_ADC.C
 *-----------+-----------------------------------------------------------------
 * @function | A/D Convertor
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




/*-----------------------------------------------------------------------------
 * @subroutine - Scan_ADC_CH01
 * @function - Process ADC Channel-0,1 Data
 * @upstream - service_100mS_A
 * @input    -
 * @return   -
 * @note     -
 *---------------------------------------------------------------------------*/
void Scan_ADC_CH01(void)
{
    //-------------------------------------------------------------------------
    if (IS_PCH_SLP_S3_LO())
    {
        GPCRI0 = INPUT;
        GPCRI1 = INPUT;
        ADCCFG = 0;
        return;
    }
    //--------------------------------------------------------------------------
    if (GPCRI0 == ALT)
    {
        if (IS_MASK_SET(VCH0CTL, BIT7))
        {
            wADC[0] = (((WORD)VCH0DATM << 8) | VCH0DATL);
            xADC[0] = wADC[0] >> 2;
        }
        //GPCRI0 = OUTPUT;
        //CLEAR_MASK(GPDRI, BIT(0));
        ADCCFG |= BIT0;
        GPCRI0 = INPUT;
        GPCRI1 = ALT;
        VCH1CTL = 0x81;

    }
    else
    {
        if (IS_MASK_SET(VCH1CTL, BIT7))
        {
            wADC[1] = (((WORD)VCH1DATM << 8) | VCH1DATL);
            xADC[1] = wADC[1] >> 2;
        }
        //GPCRI1 = OUTPUT;
        //CLEAR_MASK(GPDRI, BIT(1));
        GPCRI1 = INPUT;
        GPCRI0 = ALT;
        VCH0CTL = 0x80;
    }
    //--------------------------------------------------------------------------
}

/*
//------------------------------------------------------------------------------
    Part Number NCP15WB473D
    Resistance  47KOhm
    B-Constant  4050K   ADC_VCC:3.3V, PULL_UP: 47KOhm
//------------------------------------------------------------------------------
Temp'C Resistance(KOhm) ADC_V       ADC_10Bit      ADC_8Bit
-40.00   1690.586       3.210738231 996    03E4    249     00F9    -3
-35.00   1215.318       3.177130802 986    03D9    246     00F6    -3
-30.00   882.908        3.133209307 972    03CC    243     00F3    -4
-25.00   647.911        3.076805951 955    03BA    239     00EE    -6
-20.00   480.069        3.005731128 933    03A4    233     00E9    -7
-15.00   359.009        2.917988764 905    0389    226     00E2    -8
-10.00   270.868        2.81206161  873    0368    218     00DA    -10
 -5.00   206.113        2.687230209 834    0341    208     00D0    -11
  0.00   158.126        2.543879372 789    0315    197     00C5    -12
  5.00   122.267        2.383696172 740    02E3    185     00B8    -13
 10.00   95.256         2.209712068 686    02AD    171     00AB    -14
 15.00   74.754         2.026119881 629    0274    157     009D    -15
 20.00   59.075         1.837827009 570    023A    143     008E    -15
 25.00   47             1.65        512    0200    128     0080    -14
 30.00   37.636         1.467446477 455    01C7    114     0071    -13
 35.00   30.326         1.294206347 402    0191    100     0064    -12
 40.00   24.583         1.133284439 352    015F    88      0057    -11
 45.00   20.043         0.986559372 306    0132    77      004C    -10
 50.00   16.433         0.854900446 265    0109    66      0042    -9
 55.00   13.545         0.738269056 229    00E5    57      0039    -8
 60.00   11.223         0.636104289 197    00C5    49      0031    -7
 65.00   9.345          0.547315645 170    00A9    42      002A    -6
 70.00   7.818          0.470637382 146    0092    37      0024    -5
 75.00   6.571          0.404776838 126    007D    31      001F    -4
 80.00   5.548          0.34841288  108    006C    27      001B    -4
 85.00   4.704          0.30023209  93     005D    23      0017    -3
 90.00   4.004          0.259062034 80     0050    20      0014    -3
 95.00   3.422          0.223961763 69     0045    17      0011    -2
 100.00  2.936          0.194024351 60     003C    15      000F    -2
 105.00  2.528          0.168438055 52     0034    13      000D    -2
 110.00  2.184          0.146535459 45     002D    11      000B    -1
 115.00  1.893          0.127766756 40     0027    10      0009    -1
 120.00  1.646          0.111659746 35     0022    9       0008    -1
 125.00  1.436          0.09783632  30     001E    8       0007    -8
//------------------------------------------------------------------------------
*/
/*-----------------------------------------------------------------------------
 * @subroutine - Get_ADC_Thermistor
 * @function - Get_ADC_Thermistor
 * @upstream - service_500mS_B
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
const unsigned char code NCP15WB473D[] =
{
/* -0-  -1-  -2-  -3-  -4-  -5-  -6-  -7-  -8-  -9-  -A-  -B-  -C-  -D-  -E-  -F- */
  125, 125, 125, 125, 125, 125, 125, 125, 120, 115, 113, 110, 108, 105, 103, 100,   //0
   98,  95,  94,  92,  90,  89,  87,  85,  84,  83,  81,  80,  79,  78,  76,  75,   //1
   74,  73,  72,  71,  70,  69,  69,  68,  67,  66,  65,  64,  63,  62,  61,  61,   //2
   60,  60,  59,  58,  58,  57,  56,  56,  55,  55,  54,  53,  53,  52,  52,  51,   //3
   51,  50,  50,  50,  49,  49,  48,  48,  47,  47,  46,  46,  45,  45,  44,  44,   //4
   43,  43,  42,  42,  41,  41,  40,  40,  39,  39,  39,  38,  38,  38,  37,  37,   //5
   37,  36,  36,  36,  35,  35,  34,  34,  34,  33,  33,  33,  32,  32,  31,  31,   //6
   30,  30,  29,  29,  29,  28,  28,  28,  27,  27,  27,  26,  26,  26,  25,  25,   //7
   25,  24,  24,  24,  23,  23,  23,  22,  22,  22,  21,  21,  21,  20,  20,  20,   //8
   19,  19,  19,  18,  18,  18,  17,  17,  17,  16,  16,  16,  15,  15,  15,  14,   //9
   14,  14,  13,  13,  13,  12,  12,  12,  11,  11,  10,  10,   9,   9,   8,   8,   //A
    8,   8,   7,   7,   7,   6,   6,   6,   5,   5,   5,   4,   4,   4,   3,   3,   //B
    3,   2,   2,   1,   1,   0,   0,   0,   0,   0,   0,   0, 201, 202, 203, 204,   //C
  205, 205, 206, 206, 207, 207, 208, 208, 209, 209, 210, 210, 211, 212, 212, 213,   //D
  214, 214, 215, 216, 217, 217, 218, 219, 219, 220, 221, 222, 223, 224, 225, 226,   //E
  227, 228, 229, 230, 232, 234, 235, 237, 239, 240, 240, 240, 240, 240, 240, 240,   //F
};
/* PS: 200=0'C ~ 240=-40'C */
//-----------------------------------------------------------------------------
void Get_ADC0_Thermistor(void)
{
    //-------------------------------------------------------------------------
    if (IS_PCH_SLP_S3_LO())
    {
        return;
    }
    //-------------------------------------------------------------------------
    /*if (xEC_T1_EventTimer > 0)
    {
        xEC_T1_EventTimer--;
    }*/
    //robert20150626

     if (xEC_T1_SendEvent > 0)
        {
            xEC_T1_SendEvent--;
        }
    else
    {
        /*
            if (xEC_T1_SendEvent > 0)
            {
                    xEC_T1_SendEvent--;
                    WriteSCI_Buffer(_SCIEVT_CHARGER_T);
                    xEC_T1_EventTimer = 10;
            }
            */ //robert20150626

     //robert20150626

        if (IS_MASK_CLEAR(xEC_ThermalSource, F_CHARG_HOT))
            {
                SET_MASK(xEC_ThermalSource, F_CHARG_HOT);
            }

    }

    //robert20150626

    if(xEC_CHARGER_T > ChargerTooHot)
        {
            xEC_T2_SendEvent = 2;
        }
    if(xEC_CHARGER_T < ChargerTooHot)
        {
          CLEAR_MASK(xEC_ThermalSource, F_CHARG_HOT);
        }

    //-------------------------------------------------------------------------
    ITempB05 = xADC[0];
    xEC_T1_THR = NCP15WB473D[ITempB05];
    if (xEC_T1_THR >= 200)
    {
        /* Under 0'C */
        xEC_T1_THR = 0;
        xEC_CHARGER_T = 0;
        return;
    }
    //-------------------------------------------------------------------------
    wEC_T1_THR_ACC += xEC_T1_THR;
    xEC_T1_CNT++;
    if (xEC_T1_CNT >= 4)
    {
        xEC_T1_CNT = 0;
        xEC_T1_AVG = wEC_T1_THR_ACC / 4;
        wEC_T1_THR_ACC = 0;
        xEC_CHARGER_T = xEC_T1_AVG;

        if (xEC_CHARGER_T >= xEC_T1_HiLimit)
        {
            xEC_T1_HiLimit = xEC_CHARGER_T + 3;
            if (xEC_CHARGER_T >= 3)
            {
                xEC_T1_LoLimit = xEC_CHARGER_T - 3;
            }
            //xEC_T1_SendEvent = 2;//robert20150626
        }
        else if (xEC_CHARGER_T < xEC_T1_LoLimit)
        {
            xEC_T1_HiLimit = xEC_CHARGER_T + 3;
            if (xEC_CHARGER_T >= 3)
            {
                xEC_T1_LoLimit = xEC_CHARGER_T - 3;
                //xEC_T1_SendEvent = 2;//robert20150626
            }
            else
            {
                xEC_T1_LoLimit = 0;
            }
        }
    }
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
void Get_ADC1_Thermistor(void)
{
    //-------------------------------------------------------------------------
    if (IS_PCH_SLP_S3_LO())
    {
        return;
    }
    if (IS_MASK_CLEAR(SystemFlag1, F_ACPI_MODE))
    {
        return;
    }
    //-------------------------------------------------------------------------
      /* if (xEC_T2_EventTimer > 0)
        {
            xEC_T2_EventTimer--;
        }
        else
        {
            if (xEC_T2_SendEvent > 0)
            {
                xEC_T2_SendEvent--;
                    if ((IS_MASK_CLEAR(xEC_ThermalSource, F_SKIN_HOT)) && (SkinTripFlag != 0))
                        {
                            SET_MASK(xEC_ThermalSource, F_SKIN_HOT);
                            WriteSCI_Buffer(_SCIEVT_TrigPoint);
                            SkinTripFlag = 0;

                        }
                xEC_T2_EventTimer = 10;
            }
        }*/
    //-------------------------------------------------------------------------
        //if((ChargingCurrent37CMD != 0) && (xEC_Sensor_TSHT != 0))
        /*if(xEC_Sensor_TSHT != 0)
        {
            if(xEC_SYS_SKIN_T > xEC_Sensor_TSHT)//xEC_Sensor_TSLT
                {
                    xEC_T2_SendEvent = 2;
                    SkinTripFlag = 1;
                }
            if(xEC_SYS_SKIN_T < (xEC_Sensor_TSHT - 0x03))
                {
                  //CLEAR_MASK(xEC_ThermalSource, F_SKIN_HOT);
                 SkinTripFlag = 0;
                }
        }*/

    if((xEC_Sensor_TSHT >0) || (xEC_Sensor_TSLT > 0))
            {
            if(xEC_Sensor_TSHT != xEC_Sensor_TSHT_New)
            {
            xEC_Sensor_TSHT_Send = 1;
            xEC_Sensor_TSHT_New = xEC_Sensor_TSHT;
            }
            if(xEC_Sensor_TSLT != xEC_Sensor_TSLT_New)
            {
            xEC_Sensor_TSLT_Send = 1;
            xEC_Sensor_TSLT_New = xEC_Sensor_TSLT;
            }
        if(xEC_Sensor_TSHT_Send >0)
            {
                if(xEC_SYS_SKIN_T >= (xEC_Sensor_TSHT))//xEC_Sensor_TSLT
                {
                    SkinTripFlag = 1;
                    xEC_Sensor_TSHT_Send = 0;
                }
            }
        if(xEC_Sensor_TSLT_Send > 0)
            {
                if(xEC_SYS_SKIN_T <= (xEC_Sensor_TSLT-2))
                {
                    SkinTripFlag = 1;
                    xEC_Sensor_TSLT_Send = 0;
                }
            }
            }
    //-------------------------------------------------------------------------
    ITempB05 = xADC[1];
    xEC_T2_THR = NCP15WB473D[ITempB05];
    xEC_SensorT_Error_F = 0;
    //xEC_T2_THR = 0x64;
    /*if(IS_MASK_CLEAR(xEC_Sensor_F,F_SKIN_Sensor))
        {
         if (xEC_T2_THR >= 70)
            {
            xEC_T2_SendEvent = 2;
            }
        }*/
        if((xEC_T2_THR >= 200) ||(xEC_T2_THR < 5))  /* Under 0'C */
            {
                xEC_T2_THR = 0;
                xEC_SYS_SKIN_T = 0;
                if ((xEC_T2_THR >= 226) ||(xEC_T2_THR < 5))
                {
                    SET_MASK(xEC_SensorT_Error_F,F_Skin_Sensor_error);
                }
                return;
            }
    //-------------------------------------------------------------------------
    wEC_T2_THR_ACC += xEC_T2_THR;
    xEC_T2_CNT++;
    if (xEC_T2_CNT >= 4)
    {
        xEC_T2_CNT = 0;
        xEC_T2_AVG = wEC_T2_THR_ACC / 4;
        wEC_T2_THR_ACC = 0;
        xEC_SYS_SKIN_T = xEC_T2_AVG;

        if (xEC_SYS_SKIN_T >= xEC_T2_HiLimit)
        {
            xEC_T2_HiLimit = xEC_SYS_SKIN_T + 3;
            if (xEC_SYS_SKIN_T >= 3)
            {
                xEC_T2_LoLimit = xEC_SYS_SKIN_T - 3;
            }
            //xEC_T2_SendEvent = 2;
        }
        else if (xEC_SYS_SKIN_T < xEC_T2_LoLimit)
        {
            xEC_T2_HiLimit = xEC_SYS_SKIN_T + 3;
            if (xEC_SYS_SKIN_T >= 3)
            {
                xEC_T2_LoLimit = xEC_SYS_SKIN_T - 3;
               // xEC_T2_SendEvent = 2;
            }
            else
            {
                xEC_T2_LoLimit = 0;
            }
        }
    }
    //-------------------------------------------------------------------------
}

//robert20150626
void Get_BIOSThermalChargCMD(void)
{
 if(xEC_ThermalChargCMD == 0x37)
    {
        xEC_ThermalChargFlag |= 0x02;
    }

 if(xEC_ThermalChargCMD == 0x4A)
    {
        xEC_ThermalChargFlag |= 0x02;
    }
}
 //-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_ADC.C */