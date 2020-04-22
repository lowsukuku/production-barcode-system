/****************************************Copyright (c)**************************************************
**
**-----------------------------------------File Info----------------------------------------------------
** File name:		SysCallLib.c
** Decriptions:         
**------------------------------------------------------------------------------------------------------
** Latest modified By: YeYW, 2015-08-18
** Latest Version:		3.3.		
** Descriptions:		   
**------------------------------------------------------------------------------------------------------
** Created by:		jason.lam
** Created date:		2012-07-10
** Version:		2.1.5
** Descriptions: 	
** Notice: This APIs document is only provided for the MS3590 Mobile Scanner.
**------------------------------------------------------------------------------------------------------
**- Listing: List the functions' simplified descriptions here
**  
********************************************************************************************************/
#include "SysCallLib.h"
#include "ms3590_lib.h"

#define _SYSCALL_BASE					0x0000
#define _SYSCALL_BASE_PROCESS_MESSAGE	(_SYSCALL_BASE+1)
#define _SYSCALL_BASE_CHECK_VERIFICATION_CODE	(_SYSCALL_BASE_PROCESS_MESSAGE+1)
#define _SYSCALL_BASE_SAVE_PARAMETER	(_SYSCALL_BASE_CHECK_VERIFICATION_CODE+1)
#define _SYSCALL_BASE_CLEAR_PARAMETER	(_SYSCALL_BASE_SAVE_PARAMETER+1)
#define _SYSCALL_BASE_GET_PARAMETER		(_SYSCALL_BASE_CLEAR_PARAMETER+1)
#define _SYSCALL_BASE_SET_VERIFICATION_CODE		(_SYSCALL_BASE_GET_PARAMETER+1)
#define _SYSCALL_BASE_SET_INSTALLATION_KEY		(_SYSCALL_BASE_SET_VERIFICATION_CODE+1)

#define _SYSCALL_LCD					0x0100
#define _SYSCALL_LCD_BACKLIGHT_OFF		(_SYSCALL_LCD)
#define _SYSCALL_LCD_BACKLIGHT_ON		(_SYSCALL_LCD_BACKLIGHT_OFF+1)
#define _SYSCALL_LCD_CLEAR				(_SYSCALL_LCD_BACKLIGHT_ON+1)
#define _SYSCALL_LCD_DIS_IMAGE			(_SYSCALL_LCD_CLEAR+1)
#define _SYSCALL_LCD_PRINTF				(_SYSCALL_LCD_DIS_IMAGE+1)
#define _SYSCALL_LCD_PRINT_PAGE_INIT	(_SYSCALL_LCD_PRINTF+1)
#define _SYSCALL_LCD_PRINT_PRE_PAGE		(_SYSCALL_LCD_PRINT_PAGE_INIT+1)
#define _SYSCALL_LCD_PRINT_NEXT_PAGE	(_SYSCALL_LCD_PRINT_PRE_PAGE+1)
#define _SYSCALL_LCD_INVERSE_PIXEL		(_SYSCALL_LCD_PRINT_NEXT_PAGE+1)
#define _SYSCALL_LCD_INVERSE_REGION_PIXELS		(_SYSCALL_LCD_INVERSE_PIXEL+1)
#define _SYSCALL_LCD_BACKUP_DISPLAY_BUFFER		(_SYSCALL_LCD_INVERSE_REGION_PIXELS+1)
#define _SYSCALL_LCD_RELOAD_DISPLAY_BUFFER		(_SYSCALL_LCD_BACKUP_DISPLAY_BUFFER+1)
#define _SYSCALL_LCD_SET_LOCALE				(_SYSCALL_LCD_RELOAD_DISPLAY_BUFFER+1)
#define _SYSCALL_LCD_PRINTF_UTF8			(_SYSCALL_LCD_SET_LOCALE+1)

#define _SYSCALL_KEY					0x0200
#define _SYSCALL_KEY_SCAN_KEYBOARD		(_SYSCALL_KEY)
#define _SYSCALL_KEY_GET_KEY_VALUE		(_SYSCALL_KEY_SCAN_KEYBOARD+1)
#define _SYSCALL_KEY_GET_LEFT_KEY_STATUS		(_SYSCALL_KEY_GET_KEY_VALUE+1)
#define _SYSCALL_KEY_GET_RIGHT_KEY_STATUS		(_SYSCALL_KEY_GET_LEFT_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_UP_KEY_STATUS			(_SYSCALL_KEY_GET_RIGHT_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_DOWN_KEY_STATUS		(_SYSCALL_KEY_GET_UP_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_LEFT_SOFT_KEY_STATUS	(_SYSCALL_KEY_GET_DOWN_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_RIGHT_SOFT_KEY_STATUS	(_SYSCALL_KEY_GET_LEFT_SOFT_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_TRIG_KEY_STATUS		(_SYSCALL_KEY_GET_RIGHT_SOFT_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_RETURN_KEY_STATUS		(_SYSCALL_KEY_GET_TRIG_KEY_STATUS+1)
#define _SYSCALL_KEY_CLEAR_KEY_BUFFER		(_SYSCALL_KEY_GET_RETURN_KEY_STATUS+1)
#define _SYSCALL_KEY_ENABLE_INTERRUPT_SCSN_KEY	(_SYSCALL_KEY_CLEAR_KEY_BUFFER+1)
#define _SYSCALL_KEY_DISABLE_INTERRUPT_SCSN_KEY	(_SYSCALL_KEY_ENABLE_INTERRUPT_SCSN_KEY+1)

#define _SYSCALL_LED					0x0300
#define _SYSCALL_LED_GREEN_ON			(_SYSCALL_LED)
#define _SYSCALL_LED_GREEN_OFF			(_SYSCALL_LED_GREEN_ON+1)

#define _SYSCALL_BEEPER					0x0400
#define _SYSCALL_BEEPER_START			(_SYSCALL_BEEPER)
#define _SYSCALL_BEEPER_SET_FREP		(_SYSCALL_BEEPER_START+1)

#define _SYSCALL_VIBRATOR				0x0500
#define _SYSCALL_VIBRATOR_START			(_SYSCALL_VIBRATOR)

#define _SYSCALL_RTC					0x0600
#define _SYSCALL_RTC_GET_TIME			(_SYSCALL_RTC)
#define _SYSCALL_RTC_GET_DATA			(_SYSCALL_RTC_GET_TIME+1)
#define _SYSCALL_RTC_WEEKDAY			(_SYSCALL_RTC_GET_DATA+1)
#define _SYSCALL_RTC_SET_DATA			(_SYSCALL_RTC_WEEKDAY+1)
#define _SYSCALL_RTC_SET_TIME			(_SYSCALL_RTC_SET_DATA+1)

#define _SYSCALL_BATTERY				0x0700
#define _SYSCALL_BATTERY_GET_LIFT_PERC	(_SYSCALL_BATTERY)
#define _SYSCALL_BATTERY_GET_INFO		(_SYSCALL_BATTERY_GET_LIFT_PERC+1)

#define _SYSCALL_USB					0x0800
#define _SYSCALL_USB_PROTOCOL			(_SYSCALL_USB)
#define _SYSCALL_USB_GET_CONN_STAU		(_SYSCALL_USB_PROTOCOL+1)
#define _SYSCALL_USB_SEND_DATA			(_SYSCALL_USB_GET_CONN_STAU+1)
#define _SYSCALL_USB_VCOM_RECEIVE_DATA	(_SYSCALL_USB_SEND_DATA+1)
#define _SYSCALL_USB_VCOM_SEND_DATA		(_SYSCALL_USB_VCOM_RECEIVE_DATA+1)

#define _SYSCALL_BT						0x0900
#define _SYSCALL_BT_DEFAULT_SETTING		(_SYSCALL_BT)
#define _SYSCALL_BT_PROTOCOL			(_SYSCALL_BT_DEFAULT_SETTING+1)
#define _SYSCALL_BT_GET_CURRENT_PROTOCOL (_SYSCALL_BT_PROTOCOL+1)
#define _SYSCALL_BT_AUTO_RECONN			(_SYSCALL_BT_GET_CURRENT_PROTOCOL+1)
#define _SYSCALL_BT_SEND_PACKET			(_SYSCALL_BT_AUTO_RECONN+1)
#define _SYSCALL_BT_SPP_MASTER_SEARCH	(_SYSCALL_BT_SEND_PACKET+1)
#define _SYSCALL_BT_BA2110_SEARCH		(_SYSCALL_BT_SPP_MASTER_SEARCH+1)
#define _SYSCALL_BT_GET_CONNECT_STATUS (_SYSCALL_BT_BA2110_SEARCH+1)
#define _SYSCALL_BT_FLUSH_BUFFER			 (_SYSCALL_BT_GET_CONNECT_STATUS+1)
#define _SYSCALL_BT_HID_DELAY_TIME		(_SYSCALL_BT_FLUSH_BUFFER+1)
#define _SYSCALL_BT_SPP_RECEIVE_BT_PACKET	(_SYSCALL_BT_HID_DELAY_TIME+1)
#define _SYSCALL_BT_SPP_RECEIVE_BA2110_PACKET	(_SYSCALL_BT_SPP_RECEIVE_BT_PACKET+1)
#define _SYSCALL_BT_SET_BA2110_PROCOTOL				(_SYSCALL_BT_SPP_RECEIVE_BA2110_PACKET+1)
#define _SYSCALL_BT_SET_BA2110_KEYBOARD_LAYOUT		(_SYSCALL_BT_SET_BA2110_PROCOTOL+1)
#define _SYSCALL_BT_SET_BA2110_HIDTRANSMISSION_RATE	(_SYSCALL_BT_SET_BA2110_KEYBOARD_LAYOUT+1)
#define _SYSCALL_BT_SET_BA2110_KEYBOARD_DIVISION	(_SYSCALL_BT_SET_BA2110_HIDTRANSMISSION_RATE+1)
#define _SYSCALL_BT_SET_NAME			(_SYSCALL_BT_SET_BA2110_KEYBOARD_DIVISION+1)
#define _SYSCALL_BT_POWER_ON			(_SYSCALL_BT_SET_NAME+1)
#define _SYSCALL_BT_POWER_OFF			(_SYSCALL_BT_POWER_ON+1)
#define _SYSCALL_BT_DISCONNECT			(_SYSCALL_BT_POWER_OFF+1)
#define _SYSCALL_BT_CONNECT			(_SYSCALL_BT_DISCONNECT+1)

#define _SYSCALL_FAT32					0x0A00
#define _SYSCALL_FAT32_INIT				(_SYSCALL_FAT32)
#define _SYSCALL_FAT32_GET_DIRECTORY_LIST		(_SYSCALL_FAT32_INIT+1)
#define _SYSCALL_FAT32_CREAT_NEW_FILE			(_SYSCALL_FAT32_GET_DIRECTORY_LIST+1)
#define _SYSCALL_FAT32_FILE_SUPERADDITION		(_SYSCALL_FAT32_CREAT_NEW_FILE+1)
#define _SYSCALL_FAT32_GET_TARGET_FILE		(_SYSCALL_FAT32_FILE_SUPERADDITION+1)
#define _SYSCALL_FAT32_DELETE_FILE		(_SYSCALL_FAT32_GET_TARGET_FILE+1)
#define _SYSCALL_FAT32_CLEAR_FILE		(_SYSCALL_FAT32_DELETE_FILE+1)
#define _SYSCALL_FAT32_READ_FILE		(_SYSCALL_FAT32_CLEAR_FILE+1)
#define _SYSCALL_FAT32_FORMAT			(_SYSCALL_FAT32_READ_FILE+1)
#define _SYSCALL_FAT32_CLOSE			(_SYSCALL_FAT32_FORMAT+1)
#define _SYSCALL_FAT32_FLUSH_RAM			(_SYSCALL_FAT32_CLOSE+1)
#define _SYSCALL_FAT32_GET_FILE_SIZE		(_SYSCALL_FAT32_FLUSH_RAM+1)
#define _SYSCALL_FAT32_SET_FILE_ATTIRBUTE	(_SYSCALL_FAT32_GET_FILE_SIZE+1)
#define _SYSCALL_FAT32_STORE_DATA_IN_UDISK	(_SYSCALL_FAT32_SET_FILE_ATTIRBUTE+1)
#define _SYSCALL_FAT32_SET_TARGET_FILE		(_SYSCALL_FAT32_STORE_DATA_IN_UDISK+1)

#define _SYSCALL_DB						0x0B00
#define _SYSCALL_DB_FETCH_SET			(_SYSCALL_DB)
#define _SYSCALL_DB_FETCH_GET_STATUS	(_SYSCALL_DB_FETCH_SET+1)
#define _SYSCALL_DB_OPEN				(_SYSCALL_DB_FETCH_GET_STATUS+1)
#define _SYSCALL_DB_FETCH_DATA			(_SYSCALL_DB_OPEN+1)
#define _SYSCALL_DB_STORE_DATA			(_SYSCALL_DB_FETCH_DATA+1)
#define _SYSCALL_DB_DELETE_RECORD		(_SYSCALL_DB_STORE_DATA+1)
#define _SYSCALL_DB_EXPORT			(_SYSCALL_DB_DELETE_RECORD+1)

#define _SYSCALL_SCAN					0x0C00
#define _SYSCALL_SCAN_OPEN_SCANNER		(_SYSCALL_SCAN+1)
#define _SYSCALL_SCAN_CLOSE_SCANNER		(_SYSCALL_SCAN_OPEN_SCANNER+1)
#define _SYSCALL_SCAN_MODE				(_SYSCALL_SCAN_CLOSE_SCANNER+1)
#define _SYSCALL_SCAN_OPERATION			(_SYSCALL_SCAN_MODE+1)
#define _SYSCALL_SCAN_GET_DECODE_STATUS	(_SYSCALL_SCAN_OPERATION+1)
#define _SYSCALL_SCAN_GET_BARCODE		(_SYSCALL_SCAN_GET_DECODE_STATUS+1)
#define _SYSCALL_SCAN_ADD_TIME			(_SYSCALL_SCAN_GET_BARCODE+1)
#define _SYSCALL_SCAN_ADD_DATE			(_SYSCALL_SCAN_ADD_TIME+1)
#define _SYSCALL_SCAN_GET_QUANTITY		(_SYSCALL_SCAN_ADD_DATE+1)
#define _SYSCALL_SCAN_ADD_QUANTITY		(_SYSCALL_SCAN_GET_QUANTITY+1)
#define _SYSCALL_SCAN_CLEAR_QUANTITY	(_SYSCALL_SCAN_ADD_QUANTITY+1)
#define _SYSCALL_SCAN_BARCODE_FORMAT	(_SYSCALL_SCAN_CLEAR_QUANTITY+1)
#define _SYSCALL_SCAN_GET_BARCODE_TYPE	(_SYSCALL_SCAN_BARCODE_FORMAT+1)

#define _SYSCALL_DATABATCH						0x0D00
#define _SYSCALL_DATABATCH_STORE_DATA			(_SYSCALL_DATABATCH)
#define _SYSCALL_DATABATCH_GET_BUFFER_STATUS	(_SYSCALL_DATABATCH_STORE_DATA+1)
#define _SYSCALL_DATABATCH_SEND_BATCH_DATA		(_SYSCALL_DATABATCH_GET_BUFFER_STATUS+1)
#define _SYSCALL_DATABATCH_SET_INTERFACE		(_SYSCALL_DATABATCH_SEND_BATCH_DATA+1)
#define _SYSCALL_DATABATCH_SET_DATA_STATISTICS	(_SYSCALL_DATABATCH_SET_INTERFACE+1)
#define _SYSCALL_DATABATCH_SEARCH_BARCODE 		(_SYSCALL_DATABATCH_SET_DATA_STATISTICS+1)
#define _SYSCALL_DATABATCH_EXPORT_BARCODE_TO_TXTFILE (_SYSCALL_DATABATCH_SEARCH_BARCODE+1)

#define _SYSCALL_SET					0x0E00
#define _SYSCALL_SET_KEYBOARD_LAYOUT	(_SYSCALL_SET)
#define _SYSCALL_SET_LANGUAGE			(_SYSCALL_SET_KEYBOARD_LAYOUT+1)
#define _SYSCALL_SET_BEEPER				(_SYSCALL_SET_LANGUAGE+1)
#define _SYSCALL_SET_VIBRATOR			(_SYSCALL_SET_BEEPER+1)
#define _SYSCALL_SET_BACKLIGHT_TIMEOUT	(_SYSCALL_SET_VIBRATOR+1)
#define _SYSCALL_SET_SLEEP_TIMEOUT		(_SYSCALL_SET_BACKLIGHT_TIMEOUT+1)
#define _SYSCALL_SET_SCANER_DEFAULT_SETTING	(_SYSCALL_SET_SLEEP_TIMEOUT+1)
#define _SYSCALL_SET_BA2110_DEFAULT_SETTING	(_SYSCALL_SET_SCANER_DEFAULT_SETTING+1)
#define _SYSCALL_SET_SEPARATOR_SETTING	(_SYSCALL_SET_BA2110_DEFAULT_SETTING + 1) 

#define _SYSCALL_INFO						0x0F00
#define _SYSCALL_INFO_GET_MEMORY_VOLU		(_SYSCALL_INFO)
#define _SYSCALL_INFO_ERASE_MEMORY			(_SYSCALL_INFO_GET_MEMORY_VOLU+1)
#define _SYSCALL_INFO_GET_BT_INFO			(_SYSCALL_INFO_ERASE_MEMORY+1)
#define _SYSCALL_INFO_GET_SCANNER_VERS		(_SYSCALL_INFO_GET_BT_INFO+1)
#define _SYSCALL_INFO_GET_SCAN_ENGINE_VERS	(_SYSCALL_INFO_GET_SCANNER_VERS+1)
#define _SYSCALL_INFO_GET_BT_VERS			(_SYSCALL_INFO_GET_SCAN_ENGINE_VERS+1)
#define _SYSCALL_INFO_GET_LANGUAGE			(_SYSCALL_INFO_GET_BT_VERS+1)
#define _SYSCALL_INFO_GET_VOLUME_OF_BEEPER	(_SYSCALL_INFO_GET_LANGUAGE+1)
#define _SYSCALL_INFO_GET_VIBRATOR_SETTING_STAU		(_SYSCALL_INFO_GET_VOLUME_OF_BEEPER+1)
#define _SYSCALL_INFO_GET_BACKLIGHT_TIMEOUT		(_SYSCALL_INFO_GET_VIBRATOR_SETTING_STAU+1)
#define _SYSCALL_INFO_GET_SLEEP_TIMEOUT		(_SYSCALL_INFO_GET_BACKLIGHT_TIMEOUT+1)
#define _SYSCALL_INFO_GET_KEYBOARD_LAYOUT	(_SYSCALL_INFO_GET_SLEEP_TIMEOUT+1)
#define _SYSCALL_INFO_GET_SERIAL_NUMBER		(_SYSCALL_INFO_GET_KEYBOARD_LAYOUT+1)

#define _SYSCALL_REGISTER					0x1000
#define _SYSCALL_REGISTER_STARTUP_SHOW		(_SYSCALL_REGISTER)
#define _SYSCALL_REGISTER_POWEROFF_SHOW		(_SYSCALL_REGISTER_STARTUP_SHOW+1)
#define _SYSCALL_REGISTER_LOW_POWERO_INDICA (_SYSCALL_REGISTER_POWEROFF_SHOW+1)
#define _SYSCALL_REGISTER_Timer_FUNC		(_SYSCALL_REGISTER_LOW_POWERO_INDICA+1)
#define _SYSCALL_KILL_Timer_FUNC			(_SYSCALL_REGISTER_Timer_FUNC+1)
#define _SYSCALL_RESET_STARTUP_SHOW			(_SYSCALL_KILL_Timer_FUNC+1)	
#define _SYSCALL_RESET_POWEROFF_SHOW		(_SYSCALL_RESET_STARTUP_SHOW+1)

#define _SYSCALL_GUI						 0x2000
#define _SYSCALL_GUI_DISPLAY_NUMERIC_KEYPAD			(_SYSCALL_GUI)
#define _SYSCALL_GUI_DISPLAY_FULL_KEYPAD			(_SYSCALL_GUI_DISPLAY_NUMERIC_KEYPAD+1)
#define _SYSCALL_GUI_DISPLAY_SPECIAL_SIGN_KEYPAD	(_SYSCALL_GUI_DISPLAY_FULL_KEYPAD+1)
#define _SYSCALL_GUI_GET_NUMERIC_KEYPAD_VALUE			(_SYSCALL_GUI_DISPLAY_SPECIAL_SIGN_KEYPAD+1)
#define _SYSCALL_GUI_GET_FULL_KEYPAD_VALUE				(_SYSCALL_GUI_GET_NUMERIC_KEYPAD_VALUE+1)
#define _SYSCALL_GUI_GET_SPECIAL_SIGN_KEYPAD_VALUE		(_SYSCALL_GUI_GET_FULL_KEYPAD_VALUE+1)
#define _SYSCALL_GUI_SET_INSTRUCTIONS_ICON				(_SYSCALL_GUI_GET_SPECIAL_SIGN_KEYPAD_VALUE+1)
#define _SYSCALL_GUI_GET_FONT_DOT_MATRIX				(_SYSCALL_GUI_SET_INSTRUCTIONS_ICON+1)

#define _SYSCALL_WIFI						0x2100
#define _SYSCALL_WIFI_SEND_PACKET			(_SYSCALL_WIFI)
#define _SYSCALL_WIFI_GET_CONNECT_STATUS	(_SYSCALL_WIFI_SEND_PACKET+1)
#define _SYSCALL_WIFI_DISCONNECT			(_SYSCALL_WIFI_GET_CONNECT_STATUS+1)
#define _SYSCALL_WIFI_POWER_ON				(_SYSCALL_WIFI_DISCONNECT+1)
#define _SYSCALL_WIFI_POWER_OFF				(_SYSCALL_WIFI_POWER_ON+1)
#define _SYSCALL_WIFI_STATION_SETTING		(_SYSCALL_WIFI_POWER_OFF+1)
#define _SYSCALL_WIFI_AP_SETTING			(_SYSCALL_WIFI_STATION_SETTING+1)
#define _SYSCALL_WIFI_STATION_SEARCH		(_SYSCALL_WIFI_AP_SETTING+1)
#define _SYSCALL_WIFI_STATION_GET_HOT_SPOT_INFO			(_SYSCALL_WIFI_STATION_SEARCH+1)
#define _SYSCALL_WIFI_STATION_WLAN_CONNECT				(_SYSCALL_WIFI_STATION_GET_HOT_SPOT_INFO+1)
#define _SYSCALL_WIFI_STATION_HOST_CONNECT				(_SYSCALL_WIFI_STATION_WLAN_CONNECT+1)
#define _SYSCALL_WIFI_AP_SSID_PASSPHRASE_SETTING			(_SYSCALL_WIFI_STATION_HOST_CONNECT+1)
#define _SYSCALL_WIFI_RECEIVE_DATA 						(_SYSCALL_WIFI_AP_SSID_PASSPHRASE_SETTING+1)
#define _SYSCALL_WIFI_STATION_GET_HOST_CONNECT_STATUS	(_SYSCALL_WIFI_RECEIVE_DATA + 1)
#define _SYSCALL_WIFI_STATION_DISCONNECT_WITH_HOST		(_SYSCALL_WIFI_STATION_GET_HOST_CONNECT_STATUS + 1)
#define _SYSCALL_WIFI_STATION_AUTO_CONNECTTION		(_SYSCALL_WIFI_STATION_DISCONNECT_WITH_HOST + 1)
#define _SYSCALL_WIFI_POWER_MODE					(_SYSCALL_WIFI_STATION_AUTO_CONNECTTION + 1)

#define _SYSCALL_USART					0x3000
#define _SYSCALL_USART_CONFIGURE								(_SYSCALL_USART)
#define _SYSCALL_USART_SEND_DATABYTE						(_SYSCALL_USART_CONFIGURE+1)
#define _SYSCALL_USART_SEND_STRING							(_SYSCALL_USART_SEND_DATABYTE+1)
#define _SYSCALL_USART_RECEIVE									(_SYSCALL_USART_SEND_STRING+1)



unsigned char  mSystem_CheckVerificationCode(const char VCStr[ ])
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;

	Arg[0] = (unsigned int)VCStr;

	SysCallLib(_SYSCALL_BASE_CHECK_VERIFICATION_CODE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char  mSystem_SetVerificationCode(const char VCStr[ ])
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;

	Arg[0] = (unsigned int)VCStr;

	SysCallLib(_SYSCALL_BASE_SET_VERIFICATION_CODE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char  mSystem_SetInstallationKey(const char IKStr[ ])
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;

	Arg[0] = (unsigned int)IKStr;

	SysCallLib(_SYSCALL_BASE_SET_INSTALLATION_KEY, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

int mSystem_SaveParameter(unsigned char SequenceNum, int Para)
{
	unsigned int Arg[2];
	unsigned char Argc = 2;
	int RetVal;

	Arg[0] = (unsigned int)SequenceNum;
	Arg[1] = (int)Para;
	
	SysCallLib(_SYSCALL_BASE_SAVE_PARAMETER, &RetVal, Argc, Arg);

	return (int)RetVal;
}

int  mSystem_ClearParameter(unsigned char SequenceNum)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;

	Arg[0] = (unsigned int)SequenceNum;
	
	SysCallLib(_SYSCALL_BASE_CLEAR_PARAMETER, &RetVal, Argc, Arg);

	return (int)RetVal;
}

int  mSystem_GetParameter(unsigned char SequenceNum)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;

	Arg[0] = (unsigned int)SequenceNum;
	
	SysCallLib(_SYSCALL_BASE_GET_PARAMETER, &RetVal, Argc, Arg);

	return (int)RetVal;
}


void mLCD_BacklightOn(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_LCD_BACKLIGHT_ON, &RetVal, 0, 0);
}

void mLCD_BacklightOff(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_LCD_BACKLIGHT_OFF, &RetVal, 0, 0);
}

void mLCD_Clear(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_LCD_CLEAR, &RetVal, 0, 0);
}

void mLCD_DisplayImage(unsigned char x, unsigned char y, const unsigned char *ImagePt, unsigned char ImageXSize, unsigned char ImageYSize)
{
	int RetVal;
	unsigned int Arg[5];
	unsigned char Argc = 5;

	Arg[0] = x;
	Arg[1] = y;
	Arg[2] = (unsigned int)ImagePt;
	Arg[3] = ImageXSize;
	Arg[4] = ImageYSize;

	SysCallLib(_SYSCALL_LCD_DIS_IMAGE, &RetVal, Argc, Arg);
}

void mLCD_Printf(unsigned char x, unsigned char y, const char *StrPt, unsigned char FontSize)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] = x;
	Arg[1] = y;
	Arg[2] = (unsigned int)StrPt;
	Arg[3] = FontSize;

	SysCallLib(_SYSCALL_LCD_PRINTF, &RetVal, Argc, Arg);
}


void mLCD_PrintPageInit(unsigned char top_x, unsigned char top_y, unsigned char bottom_x, unsigned char bottom_y, const char *StrPt, unsigned int StrLength)
{
	int RetVal;
	unsigned int Arg[5];
	unsigned char Argc = 5;

	Arg[0] = top_x;
	Arg[1] = top_y;
	Arg[2] = bottom_x;
	Arg[3] = bottom_y;
	Arg[4] = (unsigned int)StrPt;
	Arg[5] = StrLength;
	
	SysCallLib(_SYSCALL_LCD_PRINT_PAGE_INIT, &RetVal, Argc, Arg);
}

void mLCD_PrintPrePage()
{
	int RetVal;
	
	SysCallLib(_SYSCALL_LCD_PRINT_PRE_PAGE, &RetVal, 0, 0);
}

void mLCD_PrintNextPage()
{
	int RetVal;
	
	SysCallLib(_SYSCALL_LCD_PRINT_NEXT_PAGE, &RetVal, 0, 0);
}


void mLCD_InversePixel(unsigned char x, unsigned char y)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = x;
	Arg[1] = y;

	SysCallLib(_SYSCALL_LCD_INVERSE_PIXEL, &RetVal, Argc, Arg);
}


void mLCD_InverseRegionPixels( unsigned char x, unsigned char y, unsigned char RegionXSize, unsigned char RegionYSize)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] = x;
	Arg[1] = y;
	Arg[2] = RegionXSize;
	Arg[3] = RegionYSize;

	SysCallLib(_SYSCALL_LCD_INVERSE_REGION_PIXELS, &RetVal, Argc, Arg);
}

void mLCD_BackupDisplayBuffer()
{
	int RetVal;
	
	SysCallLib(_SYSCALL_LCD_BACKUP_DISPLAY_BUFFER, &RetVal, 0, 0);

}

void mLCD_ReloadDisplayBuffer()
{

	int RetVal;
	
	SysCallLib(_SYSCALL_LCD_RELOAD_DISPLAY_BUFFER, &RetVal, 0, 0);

}

void mLCD_SetPrintfLocale(unsigned char locale)
{
	int RetVal = 0;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)locale;
	
	SysCallLib(_SYSCALL_LCD_SET_LOCALE, &RetVal, Argc, Arg);
}

unsigned char mKey_ScanKeyboard(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_KEY_SCAN_KEYBOARD,&RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mKey_GetKeyValue(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_KEY_GET_KEY_VALUE, &RetVal, 0, 0);
	
	return (unsigned char)RetVal;
}

unsigned char mKey_GetLeftKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_LEFT_KEY_STATUS,&RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetRightKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_RIGHT_KEY_STATUS,&RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetUpKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_UP_KEY_STATUS, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetDownKeyStatus(void)
{	
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_DOWN_KEY_STATUS,&RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetLeftSoftKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_LEFT_SOFT_KEY_STATUS,&RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetRightSoftKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_RIGHT_SOFT_KEY_STATUS,&RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetTirgKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_TRIG_KEY_STATUS, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetReturnKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_RETURN_KEY_STATUS, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

void mKey_ClearKeyBuffer(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_CLEAR_KEY_BUFFER, &RetVal, 0, 0);

}


void mKey_EnableInterruptScanKeyMode(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_ENABLE_INTERRUPT_SCSN_KEY, &RetVal, 0, 0);

}

void mKey_DisableInterruptScanKeyMode(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_DISABLE_INTERRUPT_SCSN_KEY, &RetVal, 0, 0);

}


void mLED_GreenLedOn(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_LED_GREEN_ON, &RetVal, 0, 0);
}

void mLED_GreenLedOff(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_LED_GREEN_OFF, &RetVal, 0, 0);
}


void mBeeper_StartBeeper(unsigned int  nDuration)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = nDuration;
	
	SysCallLib(_SYSCALL_BEEPER_START, &RetVal, Argc, Arg);
}


void mBeeper_SetBeeperFreq(unsigned int Period_No_Of_CCLK)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 2;

	Arg[0] = Period_No_Of_CCLK;

	SysCallLib(_SYSCALL_BEEPER_SET_FREP, &RetVal, Argc, Arg);
}


void mVibrator_StartVibr(unsigned int  nDuration)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = nDuration;
	
	SysCallLib(_SYSCALL_VIBRATOR_START, &RetVal, Argc, Arg);
}


void  mRTC_GetTime (Time *TimeInfo)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int )TimeInfo;

	SysCallLib(_SYSCALL_RTC_GET_TIME, &RetVal, Argc, Arg);	
}

void  mRTC_GetDate (Date *DateInfo)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int )DateInfo;

	SysCallLib(_SYSCALL_RTC_GET_DATA, &RetVal, Argc, Arg);	
}

unsigned short mRTC_WeekDay(unsigned short CurrentYear, unsigned char CurrentMonth, unsigned char CurrentDay)
{
	unsigned int Arg[3];
	unsigned char Argc = 3;
	int RetVal;

	Arg[0] = CurrentYear;
	Arg[1] = CurrentMonth;
	Arg[2] = CurrentDay;

	SysCallLib(_SYSCALL_RTC_WEEKDAY, &RetVal, Argc, Arg);

	return (unsigned short)RetVal;
}

unsigned char  mRTC_SetDate(unsigned short CurrentYear, unsigned char CurrentMonth, unsigned char CurrentDay)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = CurrentYear;
	Arg[1] = CurrentMonth;
	Arg[2] =CurrentDay;

	SysCallLib(_SYSCALL_RTC_SET_DATA, &RetVal, Argc, Arg);
	return (unsigned short)RetVal;
}

unsigned char mRTC_SetTime(unsigned char Hour, unsigned char Minute, unsigned char Seconds)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = Hour;
	Arg[1] = Minute;
	Arg[2] = Seconds;

	SysCallLib(_SYSCALL_RTC_SET_TIME, &RetVal, Argc, Arg);
	return (unsigned short)RetVal;
}

unsigned char mBattery_GetBatteryLifePercent(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_BATTERY_GET_LIFT_PERC, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

void mBattery_GetBatteryInfo(BATTERY_INFO *Pbi)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)Pbi;

	SysCallLib(_SYSCALL_BATTERY_GET_INFO, &RetVal, Argc, Arg);	
}

void mUSB_USBProtocol (unsigned char USBPro)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)USBPro;

	SysCallLib(_SYSCALL_USB_PROTOCOL, &RetVal, Argc, Arg);	
}

unsigned char mUSB_GetUSBConnectStatus (void)
{
	int RetVal;

	SysCallLib(_SYSCALL_USB_GET_CONN_STAU, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mUSB_HIDSendData(const void *DataBuf, unsigned short DataSize)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int )DataBuf;
	Arg[1] = DataSize;

	SysCallLib(_SYSCALL_USB_SEND_DATA, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;

}

unsigned int mUSB_VCOMReceiveData(void *RxBuffer, unsigned short Size, unsigned short Timeout)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)RxBuffer;
	Arg[1] = Size;
	Arg[2] = Timeout;
	
	SysCallLib(_SYSCALL_USB_VCOM_RECEIVE_DATA, &RetVal, Argc, Arg);

	return (unsigned int)RetVal;
}

unsigned char mUSB_VCOMSendData(const void *DataBuf, unsigned short DataSize)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int )DataBuf;
	Arg[1] = DataSize;

	SysCallLib(_SYSCALL_USB_VCOM_SEND_DATA, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;

}
unsigned char mBT_BluetoothDefaultSetting(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_DEFAULT_SETTING, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mBT_GetBluetoothCurrentProtocol(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_GET_CURRENT_PROTOCOL, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char  mBT_SetBluetoothProtocol (unsigned char BpPro)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;	
	
	Arg[0] = BpPro;

	SysCallLib(_SYSCALL_BT_PROTOCOL, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_SetBluetoothName(const char *BTname)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;	
	
	Arg[0] = (unsigned int )BTname;

	SysCallLib(_SYSCALL_BT_SET_NAME,&RetVal, Argc, Arg);

	return (int)RetVal;

}


void mBT_SearchAndConnectDevicesInSPPMaster(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_SPP_MASTER_SEARCH, &RetVal, 0, 0);

}

void mBT_SearchAndConnectDevicesInBA2110(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_BA2110_SEARCH, &RetVal, 0, 0);

}

unsigned char  mBT_AutoReconnect(unsigned char ArStu)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;	
	
	Arg[0] = ArStu;

	SysCallLib(_SYSCALL_BT_AUTO_RECONN, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_SendPacket(const void *DatBuf, unsigned short DataSize)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)DatBuf;
	Arg[1] = DataSize;
	
	SysCallLib(_SYSCALL_BT_SEND_PACKET, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;

}

unsigned char mBT_GetConnectStatus(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_BT_GET_CONNECT_STATUS, &RetVal, 0, 0);

	return (unsigned char)RetVal;

}

void mBT_HIDDelayTime(unsigned char Nms)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;	
	
	Arg[0] = Nms;

	SysCallLib(_SYSCALL_BT_HID_DELAY_TIME, &RetVal, Argc, Arg);
}

unsigned int mBT_SPPReceiveBTPacket(void *RxBuffer, unsigned short Size, unsigned short Timeout)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)RxBuffer;
	Arg[1] = Size;
	Arg[2] = Timeout;
	
	SysCallLib(_SYSCALL_BT_SPP_RECEIVE_BT_PACKET, &RetVal, Argc, Arg);

	return (unsigned int)RetVal;

}

unsigned int mBT_SPPReceiveBA2110Packet(void *RxBuffer, unsigned short Size, unsigned short Timeout)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)RxBuffer;
	Arg[1] = Size;
	Arg[2] = Timeout;
	
	SysCallLib(_SYSCALL_BT_SPP_RECEIVE_BA2110_PACKET, &RetVal, Argc, Arg);

	return (unsigned int)RetVal;

}


unsigned char mBT_SetBA2110Protocol(unsigned char BA2110Pro)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = BA2110Pro;
	
	SysCallLib(_SYSCALL_BT_SET_BA2110_PROCOTOL, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;

}

unsigned char mBT_SetBA2110KeyboardLayout(unsigned char KblVal)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = KblVal;
	
	SysCallLib(_SYSCALL_BT_SET_BA2110_KEYBOARD_LAYOUT, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;

}

unsigned char mBT_SetBA2110HIDTransmissionRate(unsigned char HIDTRLevel)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = HIDTRLevel;
	
	SysCallLib(_SYSCALL_BT_SET_BA2110_HIDTRANSMISSION_RATE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;

}

unsigned char mBT_SetBA2110KeyboardDivision(unsigned char KbDin)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = KbDin;
	
	SysCallLib(_SYSCALL_BT_SET_BA2110_KEYBOARD_DIVISION, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;

}

void mBT_PowerUp(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_POWER_ON, &RetVal, 0, 0);
}

void mBT_PowerOff(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_POWER_OFF, &RetVal, 0, 0);	
}

void mBT_Disconnect(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_DISCONNECT, &RetVal, 0, 0);		
}

unsigned char mBT_Connect(unsigned char *BTAddress, unsigned int Timeout)
{
	int RetVal;
	
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)BTAddress;
	Arg[1] = Timeout;

	SysCallLib(_SYSCALL_BT_CONNECT, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

unsigned char mFAT32_SystemInit(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_FAT32_INIT, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

void mFAT32_GetFileList(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_FAT32_GET_DIRECTORY_LIST, &RetVal, 0, 0);
}

unsigned char mFAT32_NewFile(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;

	SysCallLib(_SYSCALL_FAT32_CREAT_NEW_FILE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mFAT32_FileSuperaddition(const char *FileName, const void *Pbuffer, unsigned short length)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)FileName;
	Arg[1] = (unsigned int)Pbuffer;
	Arg[2] = length;
	
	SysCallLib(_SYSCALL_FAT32_FILE_SUPERADDITION, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char  mFAT32_FileDelete(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;

	SysCallLib(_SYSCALL_FAT32_DELETE_FILE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char  mFAT32_FileClear(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;

	SysCallLib(_SYSCALL_FAT32_CLEAR_FILE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

int  mFAT32_FileRead(const char *FileName, unsigned int offset, void *Pbuffer, unsigned short length)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] = (unsigned int)FileName;
	Arg[1] = (unsigned int)offset;
	Arg[2] = (unsigned int)Pbuffer;
	Arg[3] = (unsigned int)length;

	SysCallLib(_SYSCALL_FAT32_READ_FILE, &RetVal, Argc, Arg);

	return RetVal;
}

unsigned char  mFAT32_DiskFormat(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_FAT32_FORMAT, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}


void  mFAT32_CloseSystem(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_FAT32_CLOSE, &RetVal, 0, 0);
}

unsigned char  mFAT32_GetTargetFile(char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;

	SysCallLib(_SYSCALL_FAT32_GET_TARGET_FILE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

int  mFAT32_GetFileSize(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;

	SysCallLib(_SYSCALL_FAT32_GET_FILE_SIZE, &RetVal, Argc, Arg);

	return RetVal;
}

unsigned char  mFAT32_SetFileAttribute(const char *FileName, unsigned char DeAttribute )
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)FileName;
	Arg[1] = DeAttribute;
	
	SysCallLib(_SYSCALL_FAT32_SET_FILE_ATTIRBUTE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

void  mFAT32_Flush(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_FAT32_FLUSH_RAM, &RetVal, 0, 0);
}

unsigned char  mFAT32_StoreDataInUdisk(const void *DataBuf, unsigned short DataSize)
{
	unsigned int Arg[2];
	unsigned char Argc = 2;
	int RetVal;
	
	Arg[0] = (unsigned int )DataBuf;
	Arg[1] = DataSize;

	SysCallLib(_SYSCALL_FAT32_STORE_DATA_IN_UDISK, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

int  mFAT32_SetTargetFileInUdisk(const char *FileName)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;
	
	Arg[0] = (unsigned int )FileName;

	SysCallLib(_SYSCALL_FAT32_SET_TARGET_FILE, &RetVal, Argc, Arg);

	return (int)RetVal;
}

unsigned char   mDB_Open(const char *DB_Name, DB *PDBStruct, unsigned char OFlag)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)DB_Name;
	Arg[1] = (unsigned int)PDBStruct;
	Arg[2] = OFlag;

	SysCallLib(_SYSCALL_DB_OPEN, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char   mDB_FetchData(DB *PDBStruct, void *Databuffer, const char *Key)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)PDBStruct;
	Arg[1] = (unsigned int)Databuffer;
	Arg[2] = (unsigned int)Key;

	SysCallLib(_SYSCALL_DB_FETCH_DATA,&RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mDB_StoreData (DB *PDBStruct, void *DataBuffer, unsigned char DataLength, const char *Key, int Flag)
{
	int RetVal;
	unsigned int Arg[5];
	unsigned char Argc = 5;

	Arg[0] = (unsigned int)PDBStruct;
	Arg[1] = (unsigned int)DataBuffer;
	Arg[2] = DataLength;
	Arg[3] = (unsigned int)Key;
	Arg[4] = Flag;

	SysCallLib(_SYSCALL_DB_STORE_DATA, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mDB_DeleteRecord(DB *PDBStruct, const char *Key)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)PDBStruct;
	Arg[1] = (unsigned int)Key;

	SysCallLib(_SYSCALL_DB_DELETE_RECORD, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mDB_Export(DB *PDBStruct,const char *FileName, const char *Separator)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)PDBStruct;
	Arg[1] = (unsigned int)FileName;
	Arg[2] = (unsigned int)Separator;

	SysCallLib(_SYSCALL_DB_EXPORT, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

void mScan_ScanMode(unsigned char SmType)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = SmType;
	
	SysCallLib(_SYSCALL_SCAN_MODE, &RetVal, Argc, Arg);
}

void mScan_Operation(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_SCAN_OPERATION, &RetVal,0, 0);
}

unsigned char mScan_GetDecodeStatus(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_SCAN_GET_DECODE_STATUS, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}


void mScan_GetBarcode(char  *BarcodeStr, unsigned short *BarcodeLen)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int )BarcodeStr;
	Arg[1] = (unsigned int)BarcodeLen;
	
	SysCallLib(_SYSCALL_SCAN_GET_BARCODE, &RetVal, Argc, Arg);
}

void mBarcodeForm_AddTime(unsigned char ATStu)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = ATStu;
	
	SysCallLib(_SYSCALL_SCAN_ADD_TIME, &RetVal, Argc, Arg);
}

void mBarcodeForm_AddData(unsigned char ADStu)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = ADStu;
	
	SysCallLib(_SYSCALL_SCAN_ADD_DATE, &RetVal, Argc, Arg);
}

unsigned char  mBarcodeForm_GetBarcodeType()
{
	int RetVal;
	
	SysCallLib(_SYSCALL_SCAN_GET_BARCODE_TYPE, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}


unsigned int  mScan_GetQuantity(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_SCAN_GET_QUANTITY, &RetVal, 0, 0);

	return (unsigned int)RetVal;
}

void mScan_AddQuantity(unsigned char num)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = num;
	SysCallLib(_SYSCALL_SCAN_ADD_QUANTITY, &RetVal, Argc, Arg);
}

void mScan_ClearQuantity(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_SCAN_CLEAR_QUANTITY, &RetVal, 0, 0);
}

unsigned char mDataBatch_StoreData(const void *Databuf, unsigned short DataSize)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)Databuf;
	Arg[1] = DataSize;
	
	SysCallLib(_SYSCALL_DATABATCH_STORE_DATA, &RetVal, Argc, Arg);
	return (unsigned char)RetVal;
}

unsigned char mDataBatch_TransmitData(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_DATABATCH_SEND_BATCH_DATA, &RetVal, 0, 0);
	
	return (unsigned char)RetVal;
}

void mDataBatch_SetInterface (unsigned char TcType)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = TcType;
	
	SysCallLib(_SYSCALL_DATABATCH_SET_INTERFACE, &RetVal, Argc, Arg);
}


unsigned char mDataBatch_GetBufferstatus(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_DATABATCH_GET_BUFFER_STATUS, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

void  mDataBatch_SetDataStatistics(unsigned char DsStu)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = DsStu;
	
	SysCallLib(_SYSCALL_DATABATCH_SET_DATA_STATISTICS, &RetVal, Argc, Arg);

}

unsigned char mDataBatch_SearchData(unsigned char String[])
{
	int RetVal = 0;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)String;
	
	SysCallLib(_SYSCALL_DATABATCH_SEARCH_BARCODE, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal; 
}

unsigned int  mDataBatch_ExportDatatoTXTFile(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;
	
	SysCallLib(_SYSCALL_DATABATCH_EXPORT_BARCODE_TO_TXTFILE, &RetVal, Argc, Arg);

	return (unsigned int)RetVal; 	
}

void mSysSet_KeyboardLayout(unsigned char KblVal)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = KblVal;
	
	SysCallLib(_SYSCALL_SET_KEYBOARD_LAYOUT, &RetVal, Argc, Arg);
}

void mSysSet_Language(unsigned char LVal)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = LVal;
	
	SysCallLib(_SYSCALL_SET_LANGUAGE, &RetVal, Argc, Arg);
}

void mSysSet_Beeper(unsigned char BLevel)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = BLevel;
	
	SysCallLib(_SYSCALL_SET_BEEPER, &RetVal, Argc, Arg);
}

void mSysSet_Vibrator(unsigned char VibStu)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = VibStu;
	
	SysCallLib(_SYSCALL_SET_VIBRATOR, &RetVal, Argc, Arg);
}

void mSysSet_BacklightTimeout(unsigned char Btval)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Btval;
	
	SysCallLib(_SYSCALL_SET_BACKLIGHT_TIMEOUT, &RetVal, Argc, Arg);
}

void mSysSet_SleepTimeout(unsigned char Stval)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Stval;
	
	SysCallLib(_SYSCALL_SET_SLEEP_TIMEOUT, &RetVal, Argc, Arg);
}

void mSysSet_LoadDefaultSettingForScanner(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_SET_SCANER_DEFAULT_SETTING,&RetVal, 0, 0);
}

void mSysSet_LoadDefaultSettingForBA2110(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_SET_BA2110_DEFAULT_SETTING, &RetVal, 0, 0);
}

void mSysSet_SeparatorSetting(unsigned char SepStr[ ])
{
	int RetVal;
	
	unsigned int Arg[1];
	unsigned char Argc = 1;
	
	Arg[0] = (unsigned int)SepStr;
	
	SysCallLib(_SYSCALL_SET_SEPARATOR_SETTING, &RetVal, Argc, Arg);
}


void mSysInfo_GetMemoryVolume(MEMORY_INFO *Pmi)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;
	
	Arg[0] = (unsigned int)Pmi;

	SysCallLib(_SYSCALL_INFO_GET_MEMORY_VOLU, &RetVal, Argc, Arg);

}

void mSysInfo_EraseMemory(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_ERASE_MEMORY, &RetVal, 0, 0);	
}

void mSysInfo_GetBluetoothInfo(BLUETOOTH_INFO *Pbli)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;
	
	Arg[0] = (unsigned int)Pbli;

	SysCallLib(_SYSCALL_INFO_GET_BT_INFO, &RetVal, Argc, Arg);
}

void mSysInfo_GetScannerVersion(char *Psv)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;
	
	Arg[0] = (unsigned int )Psv;

	SysCallLib(_SYSCALL_INFO_GET_SCANNER_VERS, &RetVal, Argc, Arg);
}

void mSysInfo_GetScanEngineVersion(char *Psev)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;
	
	Arg[0] = (unsigned int)Psev;

	SysCallLib(_SYSCALL_INFO_GET_SCANNER_VERS, &RetVal, Argc, Arg);
}

void mSysInfo_GetBluetoothVersion(char *Pblv)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;
	
	Arg[0] = (unsigned int)Pblv;

	SysCallLib(_SYSCALL_INFO_GET_BT_VERS, &RetVal, Argc, Arg);
}

unsigned char mSysInfo_GetLanguage(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_GET_LANGUAGE, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mSysInfo_GetVolumeOfBeeper(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_GET_VOLUME_OF_BEEPER, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mSysInfo_GetVibratorSettingStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_GET_VIBRATOR_SETTING_STAU, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mSysInfo_GetBacklightTimeout(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_GET_BACKLIGHT_TIMEOUT, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mSysInfo_GetSleepTimeout(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_GET_SLEEP_TIMEOUT, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mSysInfo_GetKeyboardLayout(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_GET_KEYBOARD_LAYOUT, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

void mSysInfo_GetScannerSerialNumber(char *pSSN)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)pSSN;
	
	SysCallLib(_SYSCALL_INFO_GET_SERIAL_NUMBER, &RetVal, Argc, Arg);
}

void mGUI_DrawNumericKeypad(unsigned char vernierX,  unsigned char vernierY)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = vernierX;
	Arg[1] = vernierY;
	
	SysCallLib(_SYSCALL_GUI_DISPLAY_NUMERIC_KEYPAD, &RetVal, Argc, Arg);
}


void mGUI_DrawSpecialSignKeypad(unsigned char vernierX, unsigned char vernierY, unsigned char Change_Screen_Flag)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = vernierX;
	Arg[1] = vernierY;
	Arg[2] = Change_Screen_Flag;
	
	SysCallLib(_SYSCALL_GUI_DISPLAY_SPECIAL_SIGN_KEYPAD, &RetVal, Argc, Arg);
}

void mGUI_DrawFullKeypad(unsigned char vernierX, unsigned char vernierY, unsigned char Change_Screen_Flag)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = vernierX;
	Arg[1] = vernierY;
	Arg[2] = Change_Screen_Flag;
	
	SysCallLib(_SYSCALL_GUI_DISPLAY_FULL_KEYPAD, &RetVal, Argc, Arg);
}

unsigned char mGUI_GetNumericKeypadValue(unsigned char vernierX, unsigned char vernierY)
{
	unsigned int Arg[2];
	unsigned char Argc = 2;
	int RetVal;
	
	Arg[0] = vernierX;
	Arg[1] = vernierY;
	
	SysCallLib(_SYSCALL_GUI_GET_NUMERIC_KEYPAD_VALUE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mGUI_GetSpecialSignKeypadValue(unsigned char vernierX, unsigned char vernierY)
{
	unsigned int Arg[2];
	unsigned char Argc = 2;
	int RetVal;
	
	Arg[0] = vernierX;
	Arg[1] = vernierY;
	
	SysCallLib(_SYSCALL_GUI_GET_SPECIAL_SIGN_KEYPAD_VALUE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}


unsigned char mGUI_GetFullKeypadValue(unsigned char vernierX, unsigned char vernierY)
{
	unsigned int Arg[2];
	unsigned char Argc = 2;
	int RetVal;
	
	Arg[0] = vernierX;
	Arg[1] = vernierY;
	
	SysCallLib(_SYSCALL_GUI_GET_FULL_KEYPAD_VALUE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

void mGUI_SetInstructionsIcon(unsigned char IconFlg)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;
	
	Arg[0] = IconFlg;
	
	SysCallLib(_SYSCALL_GUI_SET_INSTRUCTIONS_ICON, &RetVal, Argc, Arg);
}


unsigned char  mGUI_GetFontDotMatrix(unsigned char *MatBuffer, unsigned int Offset, unsigned char FontSize)
{
	unsigned int Arg[3];
	unsigned char Argc = 3;
	int RetVal;
	
	Arg[0] = (unsigned int)MatBuffer;
	Arg[1] = Offset;	
	Arg[2] = FontSize;

	SysCallLib(_SYSCALL_GUI_GET_FONT_DOT_MATRIX, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}


void mReg_StartupShowFunc(Registry_t Func)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)Func;

	SysCallLib(_SYSCALL_REGISTER_STARTUP_SHOW, &RetVal, Argc, Arg);	
}

void mReg_PowerOffShowFunc(Registry_t Func)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)Func;

	SysCallLib(_SYSCALL_REGISTER_POWEROFF_SHOW, &RetVal, Argc, Arg);	
}

void mReg_LowPowerIndicationFunc(Registry_t Func)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)Func;

	SysCallLib(_SYSCALL_REGISTER_LOW_POWERO_INDICA, &RetVal, Argc, Arg);	
}

void mReg_ResetStartupShowFunc()
{
	int RetVal;

	SysCallLib(_SYSCALL_RESET_STARTUP_SHOW, &RetVal, 0, 0);	
}

void mReg_ResetPowerOffShowFunc()
{
	int RetVal;

	SysCallLib(_SYSCALL_RESET_POWEROFF_SHOW, &RetVal, 0, 0);
}

void mReg_SetTimerFunc(unsigned short Nms, Registry_t Func)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] =  Nms;
	Arg[1] =  (unsigned int)Func;
	
	SysCallLib(_SYSCALL_REGISTER_Timer_FUNC, &RetVal, Argc, Arg);	
}

void mReg_KillTimerFunc()
{
	int RetVal;

	SysCallLib(_SYSCALL_KILL_Timer_FUNC, &RetVal, 0, 0);	
}


unsigned char mWiFi_SendPacket(unsigned char *TxBuffer, unsigned short DataLength)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] =  (unsigned int)TxBuffer;
	Arg[1] =  (unsigned int)DataLength;
	
	SysCallLib(_SYSCALL_WIFI_SEND_PACKET, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}


unsigned char mWiFi_GetConnectStatus(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_GET_CONNECT_STATUS, &RetVal, 0, 0);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_Disconnect(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_DISCONNECT, &RetVal, 0, 0);	

	return (unsigned char)RetVal;	
}

void mWiFi_PowerOn(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_POWER_ON, &RetVal, 0, 0);	
}

void mWiFi_PowerOff(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_POWER_OFF, &RetVal, 0, 0);	
}
		
void mWiFi_StationModeSetting(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_STATION_SETTING, &RetVal, 0, 0);	
}


void mWiFi_APModeSetting(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_AP_SETTING, &RetVal, 0, 0);	
}

unsigned char mWiFi_StationModeSearchHotSpot(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_STATION_SEARCH, &RetVal, 0, 0);	

	return (unsigned char)RetVal;
}

unsigned char mWiFi_StationModeGetHotSpotInfo(Hot_Spot_INFO *HSI, unsigned short Index )
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)HSI;
	Arg[1] =  (unsigned int)Index;
	
	SysCallLib(_SYSCALL_WIFI_STATION_GET_HOT_SPOT_INFO, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}	

unsigned char mWiFi_StationModeWLANConnect(unsigned char *SSID, unsigned char EncryptionFlag, unsigned char *Passphrase, unsigned char DHCPFlag, unsigned char *StaticIP)
{
	int RetVal;
	unsigned int Arg[5];
	unsigned char Argc = 5;

	Arg[0] =  (unsigned int)SSID;
	Arg[1] =  (unsigned int)EncryptionFlag;
	Arg[2] =  (unsigned int)Passphrase;	
	Arg[3] =  (unsigned int)DHCPFlag;	
	Arg[4] =  (unsigned int)StaticIP;	
	
	SysCallLib(_SYSCALL_WIFI_STATION_WLAN_CONNECT, &RetVal, Argc, Arg);	
	
	return (unsigned char)RetVal;	
}	

unsigned char mWiFi_StationModeHostConnect(unsigned char *HostIP,unsigned char *HostPort, unsigned char *LocalPort, unsigned char Flag)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] =  (unsigned int)HostIP;
	Arg[1] =  (unsigned int)HostPort;
	Arg[2] =  (unsigned int)LocalPort;
	Arg[3] =  (unsigned int)Flag;	
	
	SysCallLib(_SYSCALL_WIFI_STATION_HOST_CONNECT, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}	

unsigned char mWiFi_APModeSSIDandPassphraseSetting(unsigned char *SSID, unsigned char EncryptionFlag, unsigned char *Passphrase, unsigned char *LocalPort)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] =  (unsigned int)SSID;
	Arg[1] =  (unsigned int)EncryptionFlag;
	Arg[2] =  (unsigned int)Passphrase;	
	Arg[3] =  (unsigned int)LocalPort;	
	
	SysCallLib(_SYSCALL_WIFI_AP_SSID_PASSPHRASE_SETTING, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

unsigned int mWiFi_ReceivePacket(unsigned char *RxBuffer, unsigned short Size, unsigned short Timeout)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)RxBuffer;
	Arg[1] = (unsigned int)Size;
	Arg[2] = (unsigned int)Timeout;
	
	SysCallLib(_SYSCALL_WIFI_RECEIVE_DATA, &RetVal, Argc, Arg);	

	return (unsigned int)RetVal;	
}

unsigned char mWiFi_StationModeGetHostConnectStatus(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_STATION_GET_HOST_CONNECT_STATUS, &RetVal, 0, 0);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeHostDisconnect(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_STATION_DISCONNECT_WITH_HOST, &RetVal, 0, 0);	

	return (unsigned char)RetVal;	
}


unsigned char mWiFi_StationModeAutoConnect(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_STATION_AUTO_CONNECTTION, &RetVal, 0, 0);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_PowerModeSetting(unsigned char mode)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)mode;

	SysCallLib(_SYSCALL_WIFI_POWER_MODE, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}
