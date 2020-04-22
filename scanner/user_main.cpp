/****************************************Copyright
 *(c)**************************************************
 **
 **-----------------------------------------File
 *Info----------------------------------------------------
 ** File name:		user_main.c
 ** Decriptions:
 **------------------------------------------------------------------------------------------------------
 ** Latest modified By:
 ** Latest Version:
 ** Descriptions:
 **------------------------------------------------------------------------------------------------------
 ** Created by:
 ** Created date:
 ** Version:
 ** Descriptions:
 ** Notice:
 **------------------------------------------------------------------------------------------------------
 **- Listing: List the functions' simplified descriptions here
 **
 ********************************************************************************************************/
/* Includes ------------------------------------------------------------------*/
extern "C" {
#include "SysCallLib.h"
#include "ms3690_lib.h"
}
#undef FILE
#include <cstdio>
#include <cstdlib>
#include <cstring>
/* Private function prototypes -----------------------------------------------*/
void DelaynMs(unsigned int time);

class A {
 private:
  /* data */
 public:
  void Run() {
    mBeeper_SetBeeperFreq(1000, 100);
    mBeeper_StartBeeper(10000);
  }
};

void RunA() {
  A a;
  a.Run();
}

/* Main functions ---------------------------------------------------------*/
extern "C" {
int user_main(void) {
  mGUI_SetPrintfLocale(FONT_CharacterEncoding_UTF8);
  unsigned char name[33] = {0};
  unsigned char encryptionStatus[20] = {0};
  unsigned char info[60] = {0};
  unsigned char hotspotsCount = mWiFi_StationModeSearchHotSpot();
  const unsigned char MatrixData[] = {0x00, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x12,
                                      0x00, 0x3F, 0x00, 0x3F, 0x00, 0x33, 0x00,
                                      0x3F, 0x00, 0x3F, 0x00, 0x00, 0x00};
  for (size_t i = 0; i < hotspotsCount; i++) {
    mWiFi_StationModeGetHotSpotInfo(name, encryptionStatus, i);
    mGUI_Printf(0, i * 10, (const char*)name, FontSize6X12);
    if (*encryptionStatus == ENCRYPTED) {
      mGUI_DisplayImage(strlen((const char*)name) * 6 + 2, i * 10, MatrixData,
                        10, 10, 0);
    }
  }
  size_t i = 0;
  mGUI_InverseRegionPixels(0, 0, 128, 10);
  while (true) {
    switch (mKey_ScanKeyboard()) {
      case KEY_DOWN:
        if (i < 5) {
          mGUI_InverseRegionPixels(0, i * 10, 128, 10);
          i++;
          mGUI_InverseRegionPixels(0, i * 10, 128, 10);
          while (mKey_GetDownKeyStatus() != IS_RELEASED) {
            /* code */
          }
        }
        break;
      case KEY_UP:
        if (i > 0) {
          mGUI_InverseRegionPixels(0, i * 10, 128, 10);
          i--;
          mGUI_InverseRegionPixels(0, i * 10, 128, 10);
          while (mKey_GetUpKeyStatus() != IS_RELEASED) {
            /* code */
          }
        }
        break;
      case KEY_RETURN: {
        while (mKey_GetReturnKeyStatus() != IS_RELEASED) {
          /* code */
        }
        return 0;
      }
      default:
        break;
    }
  }

  // mVibrator_StartVibr(0xFFFFFF);
  //   while (1) {
  //     // mLED_GreenLedOn();
  //     // DelaynMs(1000);
  //     // mLED_GreenLedOff();
  //     // DelaynMs(1000);
  //   }

  return 0;
}
}
/****The Private function******/

/*******************************************************************************
 * Function Name  : DelaynMs
 * Description    : Delay Function
 * Input          : Time(MS) unit.
 * Output         : None
 * Return         : None
 *******************************************************************************/
void DelaynMs(unsigned int time) {
  volatile unsigned int y;
  y = 10000 * time;
  while (y--) {
    for (; y > 0; y--)
      ;
  }
}
