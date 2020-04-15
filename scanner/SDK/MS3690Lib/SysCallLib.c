/****************************************Copyright (c)**************************************************
**
**-----------------------------------------File Info----------------------------------------------------
** File name:		SysCallLib.c
** Decriptions:         
**------------------------------------------------------------------------------------------------------
** Latest modified By: ZhangME, 2017-05-17
** Latest Version:	3.3.x
** Descriptions:		
**------------------------------------------------------------------------------------------------------
** Created by:		jason.lam
** Created date:		2012-07-10
** Version:		
** Descriptions: Add APIs	
** Notice: This APIs document is only provided for the MS3690 Mobile Scanner.
**------------------------------------------------------------------------------------------------------
**- Listing: List the functions' simplified descriptions here
**  
********************************************************************************************************/
#include "SysCallLib.h"
#include "ms3690_lib.h"

#define _SYSCALL_BASE									0x0000
#define _SYSCALL_BASE_PROCESS_MESSAGE					(_SYSCALL_BASE+1)
#define _SYSCALL_BASE_CHECK_VERIFICATION_CODE			(_SYSCALL_BASE_PROCESS_MESSAGE+1)
#define _SYSCALL_BASE_SAVE_PARAMETER					(_SYSCALL_BASE_CHECK_VERIFICATION_CODE+1)
#define _SYSCALL_BASE_CLEAR_PARAMETER					(_SYSCALL_BASE_SAVE_PARAMETER+1)
#define _SYSCALL_BASE_GET_PARAMETER						(_SYSCALL_BASE_CLEAR_PARAMETER+1)
#define _SYSCALL_BASE_SET_VERIFICATION_CODE				(_SYSCALL_BASE_GET_PARAMETER+1)
#define _SYSCALL_BASE_SET_INSTALLATION_KEY				(_SYSCALL_BASE_SET_VERIFICATION_CODE+1)

#define _SYSCALL_GUI									0x0100
#define _SYSCALL_GUI_BACKLIGHT_OFF						(_SYSCALL_GUI)
#define _SYSCALL_GUI_BACKLIGHT_ON						(_SYSCALL_GUI_BACKLIGHT_OFF+1)
#define _SYSCALL_GUI_CLEAR								(_SYSCALL_GUI_BACKLIGHT_ON+1)
#define _SYSCALL_GUI_DIS_IMAGE							(_SYSCALL_GUI_CLEAR+1)
#define _SYSCALL_GUI_PRINTF								(_SYSCALL_GUI_DIS_IMAGE+1)
#define _SYSCALL_GUI_INVERSE_PIXEL						(_SYSCALL_GUI_PRINTF+1)
#define _SYSCALL_GUI_INVERSE_REGION_PIXELS				(_SYSCALL_GUI_INVERSE_PIXEL+1)
#define _SYSCALL_GUI_BACKUP_DISPLAY_BUFFER				(_SYSCALL_GUI_INVERSE_REGION_PIXELS+1)
#define _SYSCALL_GUI_RELOAD_DISPLAY_BUFFER				(_SYSCALL_GUI_BACKUP_DISPLAY_BUFFER+1)
#define _SYSCALL_GUI_SET_LOCALE							(_SYSCALL_GUI_RELOAD_DISPLAY_BUFFER+1)
#define _SYSCALL_GUI_SET_INSTRUCTIONS_ICON				(_SYSCALL_GUI_SET_LOCALE+1)
#define _SYSCALL_GUI_LINE_PRINTF							(_SYSCALL_GUI_SET_INSTRUCTIONS_ICON+1)
#define _SYSCALL_GUI_SET_AUTO_REFRESH_SCREEN				(_SYSCALL_GUI_LINE_PRINTF+1)

#define _SYSCALL_KEY									0x0200
#define _SYSCALL_KEY_SCAN_KEYBOARD						(_SYSCALL_KEY)
#define _SYSCALL_KEY_GET_KEY_VALUE						(_SYSCALL_KEY_SCAN_KEYBOARD+1)
#define _SYSCALL_KEY_GET_LEFT_KEY_STATUS					(_SYSCALL_KEY_GET_KEY_VALUE+1)
#define _SYSCALL_KEY_GET_RIGHT_KEY_STATUS				(_SYSCALL_KEY_GET_LEFT_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_UP_KEY_STATUS					(_SYSCALL_KEY_GET_RIGHT_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_DOWN_KEY_STATUS				(_SYSCALL_KEY_GET_UP_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_LEFT_SOFT_KEY_STATUS			(_SYSCALL_KEY_GET_DOWN_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_RIGHT_SOFT_KEY_STATUS			(_SYSCALL_KEY_GET_LEFT_SOFT_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_TRIG_KEY_STATUS					(_SYSCALL_KEY_GET_RIGHT_SOFT_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_RETURN_KEY_STATUS				(_SYSCALL_KEY_GET_TRIG_KEY_STATUS+1)
#define _SYSCALL_KEY_CLEAR_KEY_BUFFER			        	(_SYSCALL_KEY_GET_RETURN_KEY_STATUS+1)
#define _SYSCALL_KEY_GET_BT_WIFI_KEY_STATUS				(_SYSCALL_KEY_CLEAR_KEY_BUFFER+1)
#define _SYSCALL_SET_WIRELESS_POWER_KEY					(_SYSCALL_KEY_GET_BT_WIFI_KEY_STATUS+1)

#define _SYSCALL_LED									0x0300
#define _SYSCALL_LED_GREEN_ON							(_SYSCALL_LED)
#define _SYSCALL_LED_GREEN_OFF							(_SYSCALL_LED_GREEN_ON+1)

#define _SYSCALL_BEEPER								0x0400
#define _SYSCALL_BEEPER_START							(_SYSCALL_BEEPER)
#define _SYSCALL_BEEPER_SET_FREP						(_SYSCALL_BEEPER_START+1)

#define _SYSCALL_VIBRATOR								0x0500
#define _SYSCALL_VIBRATOR_START							(_SYSCALL_VIBRATOR)

#define _SYSCALL_RTC									0x0600
#define _SYSCALL_RTC_GET_TIME							(_SYSCALL_RTC)
#define _SYSCALL_RTC_GET_DATE							(_SYSCALL_RTC_GET_TIME+1)
#define _SYSCALL_RTC_WEEKDAY							(_SYSCALL_RTC_GET_DATE+1)
#define _SYSCALL_RTC_SET_DATE							(_SYSCALL_RTC_WEEKDAY+1)
#define _SYSCALL_RTC_SET_TIME							(_SYSCALL_RTC_SET_DATE+1)

#define _SYSCALL_BATTERY								0x0700
#define _SYSCALL_BATTERY_GET_LIFT_PERC					(_SYSCALL_BATTERY)
#define _SYSCALL_BATTERY_GET_INFO						(_SYSCALL_BATTERY_GET_LIFT_PERC+1)

#define _SYSCALL_USB									0x0800
#define _SYSCALL_USB_HID_KEYBOARD_INIT					(_SYSCALL_USB)
#define _SYSCALL_USB_VIRTUAL_COM_INIT					(_SYSCALL_USB_HID_KEYBOARD_INIT+1)
#define _SYSCALL_USB_UDISK_INIT							(_SYSCALL_USB_VIRTUAL_COM_INIT+1)  
#define _SYSCALL_USB_GET_CONN_STAU						(_SYSCALL_USB_UDISK_INIT+1)
#define _SYSCALL_USB_HID_KEYBOARD_SEND					(_SYSCALL_USB_GET_CONN_STAU+1)
#define _SYSCALL_USB_VIRTUAL_COM_SEND					(_SYSCALL_USB_HID_KEYBOARD_SEND+1)
#define _SYSCALL_USB_VCOM_RECEIVE_DATA					(_SYSCALL_USB_VIRTUAL_COM_SEND+1)

#define _SYSCALL_BT									0x0900
#define _SYSCALL_BT_SET_PROTOCOL						(_SYSCALL_BT)
#define _SYSCALL_BT_GET_PROTOCOL						(_SYSCALL_BT_SET_PROTOCOL+1)
#define _SYSCALL_BT_SSP_OPTION							(_SYSCALL_BT_GET_PROTOCOL+1)
#define _SYSCALL_BT_LPM_OPTION							(_SYSCALL_BT_SSP_OPTION+1)
#define _SYSCALL_BT_SEND_PACKET							(_SYSCALL_BT_LPM_OPTION+1)
#define _SYSCALL_BT_DEFAULT_SETTING						(_SYSCALL_BT_SEND_PACKET+1)
#define _SYSCALL_BT_GET_CONNECT_STATUS					(_SYSCALL_BT_DEFAULT_SETTING+1)
#define _SYSCALL_BT_SET_NAME							(_SYSCALL_BT_GET_CONNECT_STATUS+1)
#define _SYSCALL_BT_QUERY_NAME							(_SYSCALL_BT_SET_NAME+1)
#define _SYSCALL_BT_POWER_ON							(_SYSCALL_BT_QUERY_NAME+1)
#define _SYSCALL_BT_POWER_OFF							(_SYSCALL_BT_POWER_ON+1)
#define _SYSCALL_BT_DISCONNECT							(_SYSCALL_BT_POWER_OFF+1)
#define _SYSCALL_BT_HID_CONNECT						(_SYSCALL_BT_DISCONNECT+1)
#define _SYSCALL_BT_SPP_CONNECT						(_SYSCALL_BT_HID_CONNECT+1)
#define _SYSCALL_BT_LEC_CONNECT						(_SYSCALL_BT_SPP_CONNECT+1)
#define _SYSCALL_BT_BROADCAST_ADVDATA					(_SYSCALL_BT_LEC_CONNECT+1)
#define _SYSCALL_BT_BROADCAST_RSPDATA					(_SYSCALL_BT_BROADCAST_ADVDATA+1)
#define _SYSCALL_BT_RECEIVE_DATA						(_SYSCALL_BT_BROADCAST_RSPDATA+1)
#define _SYSCALL_BT_SET_ADVSTAT							(_SYSCALL_BT_RECEIVE_DATA+1)
#define _SYSCALL_BT_GET_ADVSTAT							(_SYSCALL_BT_SET_ADVSTAT+1)
#define _SYSCALL_BT_SCAN_DEVICE							(_SYSCALL_BT_GET_ADVSTAT+1)
#define _SYSCALL_BT_GET_DEVICE							(_SYSCALL_BT_SCAN_DEVICE+1)
#define _SYSCALL_BT_RECONNECT							(_SYSCALL_BT_GET_DEVICE+1)
#define _SYSCALL_BT_SPP_RECEIVE_CRADLE_PACKET			(_SYSCALL_BT_RECONNECT+1)
#define _SYSCALL_BT_SET_CRADLE_PROTOCOL					(_SYSCALL_BT_SPP_RECEIVE_CRADLE_PACKET+1)
#define _SYSCALL_BT_SET_CRADLE_KEYBOARD_LAYOUT			(_SYSCALL_BT_SET_CRADLE_PROTOCOL+1)
#define _SYSCALL_BT_SET_CRADLE_HIDTRANSMISSION_RATE		(_SYSCALL_BT_SET_CRADLE_KEYBOARD_LAYOUT+1)
#define _SYSCALL_BT_SET_CRADLE_KEYBOARD_DIVISION			(_SYSCALL_BT_SET_CRADLE_HIDTRANSMISSION_RATE+1)
#define _SYSCALL_BT_GET_RECENT_CONNECTED_DEVICE_MAC		(_SYSCALL_BT_SET_CRADLE_KEYBOARD_DIVISION+1)
#define _SYSCALL_BT_GET_RECEIVE_DATA_TYPE				(_SYSCALL_BT_GET_RECENT_CONNECTED_DEVICE_MAC+1)
#define _SYSCALL_BT_SET_BARCODE_DELAY_TIME				(_SYSCALL_BT_GET_RECEIVE_DATA_TYPE+1)
#define _SYSCALL_BT_HID_OSKey							(_SYSCALL_BT_SET_BARCODE_DELAY_TIME+1)
#define _SYSCALL_BT_GET_CRADLE_PROTOCOL					(_SYSCALL_BT_HID_OSKey+1)
#define _SYSCALL_BT_GET_CRADLE_KEYBOARD_LAYOUT			(_SYSCALL_BT_GET_CRADLE_PROTOCOL+1)
#define _SYSCALL_BT_GET_CRADLE_HIDTRANSMISSION_RATE		(_SYSCALL_BT_GET_CRADLE_KEYBOARD_LAYOUT+1)
#define _SYSCALL_BT_GET_CRADLE_KEYBOARD_DIVISION			(_SYSCALL_BT_GET_CRADLE_HIDTRANSMISSION_RATE+1)

#define _SYSCALL_FAT32									0x0A00
#define _SYSCALL_FAT32_INIT								(_SYSCALL_FAT32)
#define _SYSCALL_FAT32_GET_DIRECTORY_LIST				(_SYSCALL_FAT32_INIT+1)
#define _SYSCALL_FAT32_CREAT_NEW_FILE					(_SYSCALL_FAT32_GET_DIRECTORY_LIST+1)
#define _SYSCALL_FAT32_FILE_SUPERADDITION					(_SYSCALL_FAT32_CREAT_NEW_FILE+1)
#define _SYSCALL_FAT32_GET_TARGET_FILE					(_SYSCALL_FAT32_FILE_SUPERADDITION+1)
#define _SYSCALL_FAT32_DELETE_FILE						(_SYSCALL_FAT32_GET_TARGET_FILE+1)
#define _SYSCALL_FAT32_CLEAR_FILE						(_SYSCALL_FAT32_DELETE_FILE+1)
#define _SYSCALL_FAT32_READ_FILE							(_SYSCALL_FAT32_CLEAR_FILE+1)
#define _SYSCALL_FAT32_FORMAT							(_SYSCALL_FAT32_READ_FILE+1)
#define _SYSCALL_FAT32_CLOSE							(_SYSCALL_FAT32_FORMAT+1)
#define _SYSCALL_FAT32_GET_FILE_SIZE						(_SYSCALL_FAT32_CLOSE+1)
#define _SYSCALL_FAT32_SET_FILE_ATTIRBUTE					(_SYSCALL_FAT32_GET_FILE_SIZE+1)
#define _SYSCALL_FAT32_STORE_DATA_IN_UDISK				(_SYSCALL_FAT32_SET_FILE_ATTIRBUTE+1)
#define _SYSCALL_FAT32_SET_TARGET_FILE					(_SYSCALL_FAT32_STORE_DATA_IN_UDISK+1)
#define _SYSCALL_FAT32_WRITE_FILE						(_SYSCALL_FAT32_SET_TARGET_FILE + 1)

#define _SYSCALL_DB									0x0B00
#define _SYSCALL_DB_OPEN								(_SYSCALL_DB+1)
#define _SYSCALL_DB_FETCH_DATA							(_SYSCALL_DB_OPEN+1)
#define _SYSCALL_DB_STORE_DATA							(_SYSCALL_DB_FETCH_DATA+1)

#define _SYSCALL_SCAN									0x0C00
#define _SYSCALL_SCAN_OPEN_SCANNER						(_SYSCALL_SCAN+1)
#define _SYSCALL_SCAN_CLOSE_SCANNER					(_SYSCALL_SCAN_OPEN_SCANNER+1)
#define _SYSCALL_SCAN_MODE								(_SYSCALL_SCAN_CLOSE_SCANNER+1)
#define _SYSCALL_SCAN_OPERATION						(_SYSCALL_SCAN_MODE+1)
#define _SYSCALL_SCAN_GET_DECODE_STATUS				(_SYSCALL_SCAN_OPERATION+1)
#define _SYSCALL_SCAN_GET_BARCODE						(_SYSCALL_SCAN_GET_DECODE_STATUS+1)
#define _SYSCALL_SCAN_ADD_TIME_DATE						(_SYSCALL_SCAN_GET_BARCODE+1)
#define _SYSCALL_SCAN_GET_QUANTITY						(_SYSCALL_SCAN_ADD_TIME_DATE+1)
#define _SYSCALL_SCAN_ADD_QUANTITY						(_SYSCALL_SCAN_GET_QUANTITY+1)
#define _SYSCALL_SCAN_CLEAR_QUANTITY					(_SYSCALL_SCAN_ADD_QUANTITY+1)
#define _SYSCALL_SCAN_GET_BARCODE_TYPE					(_SYSCALL_SCAN_CLEAR_QUANTITY+1)
#define _SYSCALL_SCAN_HANDLE_BARCODE					(_SYSCALL_SCAN_GET_BARCODE_TYPE+1)
#define _SYSCALL_SCAN_GET_BARCODE_LENGH				(_SYSCALL_SCAN_HANDLE_BARCODE+1)

#define _SYSCALL_DATABATCH								0x0D00
#define _SYSCALL_DATABATCH_STORE_DATA					(_SYSCALL_DATABATCH)
#define _SYSCALL_DATABATCH_GET_BUFFER_STATUS			(_SYSCALL_DATABATCH_STORE_DATA+1)
#define _SYSCALL_DATABATCH_SEND_BATCH_DATA				(_SYSCALL_DATABATCH_GET_BUFFER_STATUS+1)
#define _SYSCALL_DATABATCH_SET_INTERFACE				(_SYSCALL_DATABATCH_SEND_BATCH_DATA+1)
#define _SYSCALL_DATABATCH_SEARCH_BARCODE				(_SYSCALL_DATABATCH_SET_INTERFACE+1)
#define _SYSCALL_DATABATCH_EXPORT_BARCODE_TO_TXTFILE		(_SYSCALL_DATABATCH_SEARCH_BARCODE+1)
#define _SYSCALL_DATABATCH_SET_BARCODE_DELAY_TIME		(_SYSCALL_DATABATCH_EXPORT_BARCODE_TO_TXTFILE+1)
#define _SYSCALL_DATABATCH_CLEAR_BATCH_DATA				(_SYSCALL_DATABATCH_SET_BARCODE_DELAY_TIME+1)

//add 2019.7.5 Customer settings
#define _SYSCALL_SDKBATCH								0x0D80
#define _SYSCALL_SDKBATCH_CLEAR_DATA					(_SYSCALL_SDKBATCH)
#define _SYSCALL_SDKBATCH_STORE_DATA					(_SYSCALL_SDKBATCH_CLEAR_DATA+1)
#define _SYSCALL_SDKBATCH_GET_DATA						(_SYSCALL_SDKBATCH_STORE_DATA+1)
#define _SYSCALL_SDKBATCH_EXPORT_TO_FILE				(_SYSCALL_SDKBATCH_GET_DATA+1)

#define _SYSCALL_SET									0x0E00
#define _SYSCALL_SET_USBKEYBOARD_LAYOUT					(_SYSCALL_SET)
#define _SYSCALL_SET_LANGUAGE							(_SYSCALL_SET_USBKEYBOARD_LAYOUT+1)
#define _SYSCALL_SET_VOLUME							(_SYSCALL_SET_LANGUAGE+1)
#define _SYSCALL_SET_KEYTONE							(_SYSCALL_SET_VOLUME+1)
#define _SYSCALL_SET_VIBRATOR							(_SYSCALL_SET_KEYTONE+1)
#define _SYSCALL_SET_BACKLIGHT_TIMEOUT					(_SYSCALL_SET_VIBRATOR+1)
#define _SYSCALL_SET_SLEEP_TIMEOUT						(_SYSCALL_SET_BACKLIGHT_TIMEOUT+1)
#define _SYSCALL_SET_SCANER_DEFAULT_SETTING				(_SYSCALL_SET_SLEEP_TIMEOUT+1)
#define _SYSCALL_SET_SEPARATOR_SETTING					(_SYSCALL_SET_SCANER_DEFAULT_SETTING + 1) 
#define _SYSCALL_SET_BRIGHTNESS							(_SYSCALL_SET_SEPARATOR_SETTING+1)
#define _SYSCALL_SET_BTKEYBOARD_LAYOUT					(_SYSCALL_SET_BRIGHTNESS+1)


#define _SYSCALL_INFO									0x0F00
#define _SYSCALL_INFO_GET_MEMORY_VOLU					(_SYSCALL_INFO)
#define _SYSCALL_INFO_ERASE_MEMORY						(_SYSCALL_INFO_GET_MEMORY_VOLU+1)
#define _SYSCALL_INFO_GET_BT_NAME						(_SYSCALL_INFO_ERASE_MEMORY+1)
#define _SYSCALL_INFO_GET_BT_ADDR						(_SYSCALL_INFO_GET_BT_NAME+1)
#define _SYSCALL_INFO_GET_SCANNER_VERS					(_SYSCALL_INFO_GET_BT_ADDR+1)
#define _SYSCALL_INFO_GET_SCAN_ENGINE_VERS				(_SYSCALL_INFO_GET_SCANNER_VERS+1)
#define _SYSCALL_INFO_GET_BT_VERS						(_SYSCALL_INFO_GET_SCAN_ENGINE_VERS+1)
#define _SYSCALL_INFO_GET_LANGUAGE						(_SYSCALL_INFO_GET_BT_VERS+1)
#define _SYSCALL_INFO_GET_VOLUME_OF_BEEPER				(_SYSCALL_INFO_GET_LANGUAGE+1)
#define _SYSCALL_INFO_GET_VIBRATOR_SETTING_STAU			(_SYSCALL_INFO_GET_VOLUME_OF_BEEPER+1)
#define _SYSCALL_INFO_GET_BACKLIGHT_TIMEOUT				(_SYSCALL_INFO_GET_VIBRATOR_SETTING_STAU+1)
#define _SYSCALL_INFO_GET_SLEEP_TIMEOUT					(_SYSCALL_INFO_GET_BACKLIGHT_TIMEOUT+1)
#define _SYSCALL_INFO_GET_KEYBOARD_LAYOUT				(_SYSCALL_INFO_GET_SLEEP_TIMEOUT+1)
#define _SYSCALL_INFO_GET_SERIAL_NUMBER					(_SYSCALL_INFO_GET_KEYBOARD_LAYOUT+1)
#define _SYSCALL_INFO_GET_BRIGHTNESS					(_SYSCALL_INFO_GET_SERIAL_NUMBER + 1)
#define _SYSCALL_INFO_GET_DATATRANSFER_MODE				(_SYSCALL_INFO_GET_BRIGHTNESS + 1)

#define _SYSCALL_REGISTER								0x1000
#define _SYSCALL_REGISTER_STARTUP_SHOW					(_SYSCALL_REGISTER)
#define _SYSCALL_REGISTER_POWEROFF_SHOW				(_SYSCALL_REGISTER_STARTUP_SHOW+1)

#define _SYSCALL_WIFI									0x2100
#define _SYSCALL_WIFI_SEND_PACKET						(_SYSCALL_WIFI)
#define _SYSCALL_WIFI_GET_CONNECT_STATUS				(_SYSCALL_WIFI_SEND_PACKET+1)
#define _SYSCALL_WIFI_DISCONNECT						(_SYSCALL_WIFI_GET_CONNECT_STATUS+1)
#define _SYSCALL_WIFI_POWER_ON							(_SYSCALL_WIFI_DISCONNECT+1)
#define _SYSCALL_WIFI_POWER_OFF							(_SYSCALL_WIFI_POWER_ON+1)
#define _SYSCALL_WIFI_STATION_SETTING					(_SYSCALL_WIFI_POWER_OFF+1)
#define _SYSCALL_WIFI_AP_SETTING							(_SYSCALL_WIFI_STATION_SETTING+1)
#define _SYSCALL_WIFI_STATION_SEARCH					(_SYSCALL_WIFI_AP_SETTING+1)
#define _SYSCALL_WIFI_STATION_GET_HOT_SPOT_INFO			(_SYSCALL_WIFI_STATION_SEARCH+1)
#define _SYSCALL_WIFI_STATION_WLAN_CONNECT				(_SYSCALL_WIFI_STATION_GET_HOT_SPOT_INFO+1)
#define _SYSCALL_WIFI_STATION_HOST_CONNECT				(_SYSCALL_WIFI_STATION_WLAN_CONNECT+1)
#define _SYSCALL_WIFI_AP_SSID_PASSPHASE_SETTING			(_SYSCALL_WIFI_STATION_HOST_CONNECT+1)
#define _SYSCALL_WIFI_RECEIVE_DATA						(_SYSCALL_WIFI_AP_SSID_PASSPHASE_SETTING+1)
#define _SYSCALL_WIFI_STATION_GET_HOST_CONNECT_STATUS	(_SYSCALL_WIFI_RECEIVE_DATA+1)
#define _SYSCALL_WIFI_STATION_DISCONNECT_WITH_HOST		(_SYSCALL_WIFI_STATION_GET_HOST_CONNECT_STATUS+1)
#define _SYSCALL_WIFI_STATION_AUTO_CONNECTTION			(_SYSCALL_WIFI_STATION_DISCONNECT_WITH_HOST+1)
#define _SYSCALL_WIFI_SET_POWER_MODE					(_SYSCALL_WIFI_STATION_AUTO_CONNECTTION+1)
#define _SYSCALL_WIFI_GET_WLANLIST_NUM					(_SYSCALL_WIFI_SET_POWER_MODE+1)
#define _SYSCALL_WIFI_ADD_HOST_IP						(_SYSCALL_WIFI_GET_WLANLIST_NUM+1)
#define _SYSCALL_WIFI_SET_HOST_PORT						(_SYSCALL_WIFI_ADD_HOST_IP+1)
#define _SYSCALL_WIFI_SET_LOCAL_PORT						(_SYSCALL_WIFI_SET_HOST_PORT+1)
#define _SYSCALL_WIFI_GET_LOCAL_PORT					(_SYSCALL_WIFI_SET_LOCAL_PORT+1)
#define _SYSCALL_WIFI_GET_HOST_PORT						(_SYSCALL_WIFI_GET_LOCAL_PORT+1)
#define _SYSCALL_WIFI_SET_CURRENT_IP						(_SYSCALL_WIFI_GET_HOST_PORT+1)
#define _SYSCALL_WIFI_GET_HOST_INFO						(_SYSCALL_WIFI_SET_CURRENT_IP+1)
#define _SYSCALL_WIFI_GET_HOST_LIST_NUM					(_SYSCALL_WIFI_GET_HOST_INFO+1)
#define _SYSCALL_WIFI_DELETE_HOST_IP						(_SYSCALL_WIFI_GET_HOST_LIST_NUM+1)
#define _SYSCALL_WIFI_GET_CURRENT_HOST_NUM				(_SYSCALL_WIFI_DELETE_HOST_IP+1)
#define _SYSCALL_WIFI_STATION_GET_PASSPHRASE				(_SYSCALL_WIFI_GET_CURRENT_HOST_NUM+1)


//******************* The security design and save parameter *****************//

unsigned char mSystem_CheckVerificationCode(const char VCStr[])
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;

	Arg[0] = (unsigned int)VCStr;

	SysCallLib(_SYSCALL_BASE_CHECK_VERIFICATION_CODE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mSystem_SetVerificationCode(const char VCStr[])
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;

	Arg[0] = (unsigned int)VCStr;

	SysCallLib(_SYSCALL_BASE_SET_VERIFICATION_CODE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mSystem_SetInstallationKey(const char IKStr[])
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

//******************************** GUI management *****************************//

void mGUI_BacklightOn(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_GUI_BACKLIGHT_ON, &RetVal, 0, 0);
}

void mGUI_BacklightOff(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_GUI_BACKLIGHT_OFF, &RetVal, 0, 0);
}

void mGUI_Clear(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_GUI_CLEAR, &RetVal, 0, 0);
}

void mGUI_DisplayImage(unsigned char x, unsigned char y, const unsigned char *ImagePt, unsigned char ImageXSize, unsigned char ImageYSize, unsigned char Versa )
{
	int RetVal;
	unsigned int Arg[6];
	unsigned char Argc = 6;

	Arg[0] = x;
	Arg[1] = y;
	Arg[2] = (unsigned int)ImagePt;
	Arg[3] = ImageXSize;
	Arg[4] = ImageYSize;
	Arg[5] = Versa;

	SysCallLib(_SYSCALL_GUI_DIS_IMAGE, &RetVal, Argc, Arg);
}

void mGUI_Printf(unsigned char x, unsigned  char y, const char *StrPt, char FontSize)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] = x;
	Arg[1] = y;
	Arg[2] = (unsigned int)StrPt;
	Arg[3] = FontSize;

	SysCallLib(_SYSCALL_GUI_PRINTF, &RetVal, Argc, Arg);
}

void mGUI_InversePixel(unsigned char x, unsigned char y)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = x;
	Arg[1] = y;

	SysCallLib(_SYSCALL_GUI_INVERSE_PIXEL, &RetVal, Argc, Arg);
}


void mGUI_InverseRegionPixels(unsigned char x, unsigned char y, unsigned char RegionXSize, unsigned char RegionYSize)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] = x;
	Arg[1] = y;
	Arg[2] = RegionXSize;
	Arg[3] = RegionYSize;

	SysCallLib(_SYSCALL_GUI_INVERSE_REGION_PIXELS, &RetVal, Argc, Arg);
}

void mGUI_BackupDisplayBuffer(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_GUI_BACKUP_DISPLAY_BUFFER, &RetVal, 0, 0);
}

void mGUI_ReloadDisplayBuffer(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_GUI_RELOAD_DISPLAY_BUFFER, &RetVal, 0, 0);
}

void mGUI_SetPrintfLocale(unsigned char locale)
{
	int RetVal = 0;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = locale;

	SysCallLib(_SYSCALL_GUI_SET_LOCALE, &RetVal, Argc, Arg);
}

void mGUI_SetInstructionsIcon(unsigned char IconFlg)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;
	
	Arg[0] = IconFlg;
	
	SysCallLib(_SYSCALL_GUI_SET_INSTRUCTIONS_ICON, &RetVal, Argc,  Arg);
}

unsigned short mGUI_LinePrintf(unsigned char x, unsigned  char y, const char *StrPt, unsigned  char LineNum, char FontSize)
{
	int RetVal;
	unsigned int Arg[5];
	unsigned char Argc = 5;

	Arg[0] = x;
	Arg[1] = y;
	Arg[2] = (unsigned int)StrPt;
	Arg[3] = LineNum;
	Arg[4] = FontSize;

	SysCallLib(_SYSCALL_GUI_LINE_PRINTF, &RetVal, Argc, Arg);
	return (unsigned short)RetVal;
}

void mGUI_SetAutoRefreshScreen(unsigned char SetFlg)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;
	
	Arg[0] = SetFlg;
	
	SysCallLib(_SYSCALL_GUI_SET_AUTO_REFRESH_SCREEN, &RetVal, Argc,  Arg);
}


//******************************** KEY management *****************************//

unsigned char mKey_ScanKeyboard(void)//此接口有问题
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
	SysCallLib(_SYSCALL_KEY_GET_LEFT_KEY_STATUS, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetRightKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_RIGHT_KEY_STATUS, &RetVal, 0, 0);
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
	SysCallLib(_SYSCALL_KEY_GET_DOWN_KEY_STATUS, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetLeftSoftKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_LEFT_SOFT_KEY_STATUS, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mKey_GetRightSoftKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_RIGHT_SOFT_KEY_STATUS, &RetVal, 0, 0);
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

unsigned char mKey_GetBTWiFiKeyStatus(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_KEY_GET_BT_WIFI_KEY_STATUS, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

void mKey_SetWirelessPowerKey(unsigned char SetFlg)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;
	
	Arg[0] = SetFlg;
	
	SysCallLib(_SYSCALL_SET_WIRELESS_POWER_KEY, &RetVal, Argc,  Arg);
}


//******************************** LED management *****************************//

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

//******************************** Beeper and vibrate management *****************************//

void mBeeper_StartBeeper(unsigned int nDuration)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = nDuration;

	SysCallLib(_SYSCALL_BEEPER_START, &RetVal, Argc, Arg);
}

void mBeeper_SetBeeperFreq(unsigned short Period_No_Of_CCLK, unsigned char duty)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = Period_No_Of_CCLK;
	Arg[1] = duty;

	SysCallLib(_SYSCALL_BEEPER_SET_FREP, &RetVal, Argc, Arg);
}

void mVibrator_StartVibr(unsigned int nDuration)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = nDuration;

	SysCallLib(_SYSCALL_VIBRATOR_START, &RetVal, Argc, Arg);
}

//******************************** Time management *****************************//

void mRTC_GetTime(unsigned char *p_hour, unsigned char *p_min, unsigned char *p_sec)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)p_hour;
	Arg[1] = (unsigned int)p_min;
	Arg[2] = (unsigned int)p_sec;

	SysCallLib(_SYSCALL_RTC_GET_TIME, &RetVal, Argc, Arg);	
}

void mRTC_GetDate(unsigned short *p_year, unsigned char *p_month, unsigned char *p_day)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)p_year;
	Arg[1] = (unsigned int)p_month;
	Arg[2] = (unsigned int)p_day;

	SysCallLib(_SYSCALL_RTC_GET_DATE, &RetVal, Argc, Arg);	
}

unsigned char mRTC_SetDate(unsigned short year, unsigned char month, unsigned char day)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = year;
	Arg[1] = month;
	Arg[2] = day;

	SysCallLib(_SYSCALL_RTC_SET_DATE, &RetVal, Argc, Arg);
	return (unsigned char)RetVal;
}

unsigned char mRTC_SetTime(unsigned char hour, unsigned char min, unsigned char sec)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = hour;
	Arg[1] = min;
	Arg[2] = sec;

	SysCallLib(_SYSCALL_RTC_SET_TIME, &RetVal, Argc, Arg);
	return (unsigned short)RetVal;
}

unsigned char mRTC_WeekDay(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_RTC_WEEKDAY, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

//******************************** Power information *****************************//
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

//******************************** USB management *****************************//

void mUSB_KeyboardInit(void)   
{
	int RetVal;

	SysCallLib(_SYSCALL_USB_HID_KEYBOARD_INIT, &RetVal, 0, 0);	
}

void mUSB_VirtualComInit(void)  
{
	int RetVal;

	SysCallLib(_SYSCALL_USB_VIRTUAL_COM_INIT, &RetVal, 0, 0);	
}

void mUSB_UdiskInit(void)  
{
	int RetVal;

	SysCallLib(_SYSCALL_USB_UDISK_INIT, &RetVal, 0, 0);	
}

unsigned char mUSB_GetUSBConnectStatus(void)
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

	Arg[0] = (unsigned int)DataBuf;
	Arg[1] = DataSize;

	SysCallLib(_SYSCALL_USB_HID_KEYBOARD_SEND, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;

}

unsigned char mUSB_VCOMSendData(const void *DataBuf, unsigned short DataSize)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)DataBuf;
	Arg[1] = DataSize;

	SysCallLib(_SYSCALL_USB_VIRTUAL_COM_SEND, &RetVal, Argc, Arg);

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

//******************************** Bluetooth information *****************************//

unsigned char mBT_GetBluetoothProtocol(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_GET_PROTOCOL, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mBT_SetBluetoothProtocol(unsigned char BpPro)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;	
	
	Arg[0] = BpPro;

	SysCallLib(_SYSCALL_BT_SET_PROTOCOL, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_LPMOption(unsigned char ArStu)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;	
	
	Arg[0] = ArStu;

	SysCallLib(_SYSCALL_BT_LPM_OPTION, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_SendPacket(unsigned char *DataBuf, unsigned short DataSize)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)DataBuf;
	Arg[1] = DataSize;
	
	SysCallLib(_SYSCALL_BT_SEND_PACKET, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_BluetoothDefaultSetting(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_DEFAULT_SETTING, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mBT_GetConnectStatus(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_BT_GET_CONNECT_STATUS, &RetVal, 0, 0);

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

unsigned char mBT_QueryBluetoothName(unsigned char *BTname)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;	
	
	Arg[0] = (unsigned int )BTname;

	SysCallLib(_SYSCALL_BT_QUERY_NAME,&RetVal, Argc, Arg);

	return (int)RetVal;
}

void mBT_PowerOn(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_POWER_ON, &RetVal, 0,  0);
}

void mBT_PowerOff(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_POWER_OFF, &RetVal, 0,  0);	
}

void mBT_Disconnect(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_BT_DISCONNECT, &RetVal, 0,  0);		
}

unsigned char mBT_HIDConnect(unsigned char *BTAddress)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)BTAddress;

	SysCallLib(_SYSCALL_BT_HID_CONNECT, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

unsigned char mBT_SPPConnect(unsigned char *BTAddress)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)BTAddress;

	SysCallLib(_SYSCALL_BT_SPP_CONNECT, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

unsigned char mBT_LECConnect(unsigned char *BTAddress, unsigned char BT_Type, unsigned char *Service_UUID, unsigned char *Write_UUID, unsigned char *Notify_UUID)
{
	int RetVal;
	unsigned int Arg[5];
	unsigned char Argc = 5;

	Arg[0] = (unsigned int)BTAddress;
	Arg[1] = BT_Type;
	Arg[2] = (unsigned int)Service_UUID;
	Arg[3] = (unsigned int)Write_UUID;
	Arg[4] = (unsigned int)Notify_UUID;

	SysCallLib(_SYSCALL_BT_LEC_CONNECT, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

unsigned char mBT_BroadcastADVData(unsigned char *DataBuf, unsigned char DataSize)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)DataBuf;
  Arg[1] = DataSize;

	SysCallLib(_SYSCALL_BT_BROADCAST_ADVDATA, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

unsigned char mBT_BroadcastRSPData(unsigned char *DataBuf, unsigned char DataSize)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)DataBuf;
  Arg[1] = DataSize;

	SysCallLib(_SYSCALL_BT_BROADCAST_RSPDATA, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

unsigned char mBT_ReceiveData(unsigned char *DataBuf, unsigned char MaxLen, unsigned short mSec)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)DataBuf;
	Arg[1] = MaxLen;
	Arg[2] = mSec;

	SysCallLib(_SYSCALL_BT_RECEIVE_DATA, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

unsigned char mBT_SetBroadcast(unsigned char Status)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Status;

	SysCallLib(_SYSCALL_BT_SET_ADVSTAT, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

unsigned char mBT_GetBroadcastStatus(unsigned char *p_Status)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)p_Status;

	SysCallLib(_SYSCALL_BT_GET_ADVSTAT, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

unsigned char mBT_SearchDevice(unsigned char DeviceType, unsigned char SearchTime)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = DeviceType;
	Arg[1] = SearchTime;

	SysCallLib(_SYSCALL_BT_SCAN_DEVICE, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal;
}

void mBT_GetDevice(unsigned char count, BLUETOOTH_DEVICE_INFO *DeviceInfo)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = count;
	Arg[1] = (unsigned int)DeviceInfo;

	SysCallLib(_SYSCALL_BT_GET_DEVICE, &RetVal, Argc, Arg);
}

void mBT_Reconnect(unsigned char Select)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Select;
	
	SysCallLib(_SYSCALL_BT_RECONNECT, &RetVal, Argc, Arg);
}

unsigned int mBT_SPPReceiveCradlePacket(void *RxBuffer, unsigned short Size, unsigned short Timeout)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)RxBuffer;
	Arg[1] = Size;
	Arg[2] = Timeout;
	
	SysCallLib(_SYSCALL_BT_SPP_RECEIVE_CRADLE_PACKET, &RetVal, Argc, Arg);

	return (unsigned int)RetVal;
}

unsigned char mBT_SetCradleProtocol(unsigned char CrablePro)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = CrablePro;
	
	SysCallLib(_SYSCALL_BT_SET_CRADLE_PROTOCOL, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_SetCradleKeyboardLayout(unsigned char KblVal)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = KblVal;
	
	SysCallLib(_SYSCALL_BT_SET_CRADLE_KEYBOARD_LAYOUT, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_SetCradleHIDTransmissionRate(unsigned char HIDTRLevel)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = HIDTRLevel;
	
	SysCallLib(_SYSCALL_BT_SET_CRADLE_HIDTRANSMISSION_RATE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_SetCradleKeyboardDivision(unsigned char KbDin)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = KbDin;
	
	SysCallLib(_SYSCALL_BT_SET_CRADLE_KEYBOARD_DIVISION, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_GetRecentConnectedDeviceMac(unsigned char *BTAddress)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)BTAddress;
	
	SysCallLib(_SYSCALL_BT_GET_RECENT_CONNECTED_DEVICE_MAC, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mBT_GetReceiveDataType(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_BT_GET_RECEIVE_DATA_TYPE,&RetVal, 0, 0);

	return (unsigned char)RetVal;
}

void mBT_SetBarcodeDelayTime(unsigned char Nms)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Nms;
	
	SysCallLib(_SYSCALL_BT_SET_BARCODE_DELAY_TIME, &RetVal, Argc, Arg);
}

void mBT_HIDOSKey(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_BT_HID_OSKey, &RetVal, 0, 0);
}

unsigned char mBT_GetCradleProtocol(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_BT_GET_CRADLE_PROTOCOL, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mBT_GetCradleKeyboardLayout(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_BT_GET_CRADLE_KEYBOARD_LAYOUT, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mBT_GetCradleHIDTransmissionRate(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_BT_GET_CRADLE_HIDTRANSMISSION_RATE, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mBT_GetCradleKeyboardDivision(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_BT_GET_CRADLE_KEYBOARD_DIVISION, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

//******************************** Wi-Fi management *****************************//

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

unsigned char mWiFi_StationModeSearchHotSpot(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_WIFI_STATION_SEARCH, &RetVal, 0, 0);	

	return (unsigned char)RetVal;
}

unsigned char mWiFi_GetConnectStatus(unsigned char *SSID)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)SSID;

	SysCallLib(_SYSCALL_WIFI_GET_CONNECT_STATUS, &RetVal, Argc,  Arg);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeGetHotSpotInfo(unsigned char *Hot_Spot_Name, unsigned char *Psk, unsigned char Number_HS)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] =  (unsigned int)Hot_Spot_Name;
	Arg[1] =  (unsigned int)Psk;
	Arg[2] =  Number_HS;

	SysCallLib(_SYSCALL_WIFI_STATION_GET_HOT_SPOT_INFO, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeWLANConnect(unsigned char *SSID, unsigned char EncryptionFlag, unsigned char *Passphrase, unsigned char DHCPFlag, unsigned char *StaticIP)
{
	int RetVal;
	unsigned int Arg[5];
	unsigned char Argc = 5;

	Arg[0] = (unsigned int)SSID;
	Arg[1] =  EncryptionFlag;
	Arg[2] = (unsigned int)Passphrase;	
	Arg[3] =  DHCPFlag;	
	Arg[4] = (unsigned int)StaticIP;	
	
	SysCallLib(_SYSCALL_WIFI_STATION_WLAN_CONNECT, &RetVal, Argc, Arg);	
	
	return (unsigned char)RetVal;	
}	

unsigned char mWiFi_Disconnect(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_DISCONNECT, &RetVal, 0,  0);
	
	return (unsigned char)RetVal;
}

unsigned char mWiFi_StationModeHostConnect(unsigned char *HostIP, unsigned char *HostPort, unsigned char *LocalPort, unsigned char Flag)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] = (unsigned int)HostIP;
	Arg[1] = (unsigned int)HostPort;
	Arg[2] = (unsigned int)LocalPort;
	Arg[3] = Flag;	
	
	SysCallLib(_SYSCALL_WIFI_STATION_HOST_CONNECT, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeAutoConnect(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_STATION_AUTO_CONNECTTION, &RetVal, 0, 0);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_APModeSSIDandPassphraseSetting(unsigned char *SSID, unsigned char security, unsigned char *PSK, unsigned char *localport)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] = (unsigned int)SSID;
	Arg[1] = security;
	Arg[2] = (unsigned int)PSK;
	Arg[3] = (unsigned int)localport;	

	SysCallLib(_SYSCALL_WIFI_AP_SSID_PASSPHASE_SETTING, &RetVal, Argc, Arg);	

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

unsigned char mWiFi_StationModeGetHostConnectStatus(unsigned char *IP)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

  Arg[0] = (unsigned int)IP;

	SysCallLib(_SYSCALL_WIFI_STATION_GET_HOST_CONNECT_STATUS, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeHostDisconnect(unsigned char Number_HS)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Number_HS;
	
	SysCallLib(_SYSCALL_WIFI_STATION_DISCONNECT_WITH_HOST, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}


unsigned char mWiFi_PowerModeSetting(unsigned char Mode)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Mode;

	SysCallLib(_SYSCALL_WIFI_SET_POWER_MODE, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_SendPacket(unsigned char *DataBuf, unsigned short DataLength)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] =  (unsigned int)DataBuf;
	Arg[1] =  (unsigned int)DataLength;
	
	SysCallLib(_SYSCALL_WIFI_SEND_PACKET, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}
unsigned char mWiFi_StationModeGetHotSpotListNum()
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_GET_WLANLIST_NUM, &RetVal, 0, 0);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeAddHostIP(unsigned char *IP)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)IP;
	
	SysCallLib(_SYSCALL_WIFI_ADD_HOST_IP, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeSetHostPort(unsigned char * host_port, unsigned char Number_HS)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] =  (unsigned int)host_port;
	Arg[1] =  Number_HS;

	SysCallLib(_SYSCALL_WIFI_SET_HOST_PORT, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeSetLocalPort(unsigned char * local_port)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)local_port;
	
	SysCallLib(_SYSCALL_WIFI_SET_LOCAL_PORT, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

void mWiFi_StationModeGetLocalPort(unsigned char * local_port)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)local_port;
	
	SysCallLib(_SYSCALL_WIFI_GET_LOCAL_PORT, &RetVal, Argc, Arg);	
}

unsigned char mWiFi_StationModeGetHostPort(unsigned char *host_port, unsigned char Number_HS)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] =  (unsigned int)host_port;
	Arg[1] =  Number_HS;
	
	SysCallLib(_SYSCALL_WIFI_GET_HOST_PORT, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;
}

unsigned char mWiFi_StationModeSetCurrentIP(unsigned char Number_HS)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Number_HS;

	SysCallLib(_SYSCALL_WIFI_SET_CURRENT_IP, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeGetHostInfo(HOST_INFO *host_info, unsigned char Number_HS)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] =  (unsigned int)host_info;
	Arg[1] =  Number_HS;
	
	SysCallLib(_SYSCALL_WIFI_GET_HOST_INFO, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeGetHostListNum(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_WIFI_GET_HOST_LIST_NUM, &RetVal, 0, 0);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeDeleteHostIP(unsigned char Number_HS)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Number_HS;

	SysCallLib(_SYSCALL_WIFI_DELETE_HOST_IP, &RetVal, Argc, Arg);	

	return (unsigned char)RetVal;	
}

unsigned char mWiFi_StationModeGetCurrentConnectHostNum(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_WIFI_GET_CURRENT_HOST_NUM, &RetVal, 0, 0);	

	return (unsigned char)RetVal;	
}

void mWiFi_StationModeGetPassphrase(unsigned char *psk)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] =  (unsigned int)psk;
	
	SysCallLib(_SYSCALL_WIFI_STATION_GET_PASSPHRASE, &RetVal, Argc, Arg);	
}

//******************************** File system *****************************//

unsigned char mFAT32_SystemInit(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_FAT32_INIT, &RetVal, 0, 0);

	return (unsigned char)RetVal;
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

int mFAT32_FileRead(const char *FileName, unsigned int offset, void *Pbuffer, unsigned short length)
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

int mFAT32_FileWrite(const char *FileName, unsigned int offset, void *Pbuffer, unsigned short length)
{
	int RetVal;
	unsigned int Arg[4];
	unsigned char Argc = 4;

	Arg[0] = (unsigned int)FileName;
	Arg[1] = (unsigned int)offset;
	Arg[2] = (unsigned int)Pbuffer;
	Arg[3] = (unsigned int)length;

	SysCallLib(_SYSCALL_FAT32_WRITE_FILE, &RetVal, Argc, Arg);

	return RetVal;
}

unsigned char mFAT32_FileDelete(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;

	SysCallLib(_SYSCALL_FAT32_DELETE_FILE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mFAT32_FileClear(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;

	SysCallLib(_SYSCALL_FAT32_CLEAR_FILE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mFAT32_DiskFormat(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_FAT32_FORMAT, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned char mFAT32_GetTargetFile(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;

	SysCallLib(_SYSCALL_FAT32_GET_TARGET_FILE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mFAT32_GetDirectoryList(const char *FileName, unsigned short FileIndex)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)FileName;
	Arg[1] = FileIndex;
	
	SysCallLib(_SYSCALL_FAT32_GET_DIRECTORY_LIST, &RetVal, Argc, Arg);

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

void mFAT32_CloseSystem(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_FAT32_CLOSE, &RetVal, 0, 0);
}

int mFAT32_GetFileSize(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;

	SysCallLib(_SYSCALL_FAT32_GET_FILE_SIZE, &RetVal, Argc, Arg);

	return RetVal;
}

unsigned char mFAT32_SetFileAttribute(const char *FileName, unsigned char DeAttribute)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)FileName;
	Arg[1] = DeAttribute;
	
	SysCallLib(_SYSCALL_FAT32_SET_FILE_ATTIRBUTE, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mFAT32_StoreDataInUdisk(const void *DataBuf,  unsigned short DataSize)
{
	unsigned int Arg[2];
	unsigned char Argc = 2;
	int RetVal;
	
	Arg[0] = (unsigned int )DataBuf;
	Arg[1] = DataSize;

	SysCallLib(_SYSCALL_FAT32_STORE_DATA_IN_UDISK, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

char mFAT32_SetTargetFileInUdisk(const char *FileName)
{
	unsigned int Arg[1];
	unsigned char Argc = 1;
	int RetVal;
	
	Arg[0] = (unsigned int )FileName;

	SysCallLib(_SYSCALL_FAT32_SET_TARGET_FILE, &RetVal, Argc, Arg);

	return (char)RetVal;
}

//******************************** Database management *****************************//

unsigned char mDB_Open(const char *DB_Name, DB *PDBStruct, unsigned char OFlag)
{
 	int RetVal;
 	unsigned int Arg[3];
 	unsigned char Argc = 3;
 
 	Arg[0] = (unsigned int)DB_Name;
 	Arg[1] = (unsigned int)PDBStruct;
 	Arg[2] = OFlag;
 
 	SysCallLib(_SYSCALL_DB_OPEN,&RetVal, Argc, Arg);
 
 	return (unsigned char)RetVal;
}

unsigned char mDB_FetchData(DB *PDBStruct, void *Databuffer, const char *Key)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = (unsigned int)PDBStruct;
	Arg[1] = (unsigned int)Databuffer;
	Arg[2] = (unsigned int)Key;

	SysCallLib(_SYSCALL_DB_FETCH_DATA, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mDB_StoreData(DB *PDBStruct, void *DataBuffer, unsigned char DataLength, const char *Key, int Flag)
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

//******************************** Scan engine operation *****************************//

void mScan_OpenScanner(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_SCAN_OPEN_SCANNER, &RetVal, 0, 0);
}

void mScan_CloseScanner(void)
{
	int RetVal;

	SysCallLib(_SYSCALL_SCAN_CLOSE_SCANNER, &RetVal, 0, 0);
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
	SysCallLib(_SYSCALL_SCAN_OPERATION, &RetVal, 0, 0);
}

unsigned char mScan_GetDecodeStatus(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_SCAN_GET_DECODE_STATUS, &RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned short mScan_GetBarcode(unsigned char *BarcodeStr,unsigned short MaxLen)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)BarcodeStr;
	Arg[1] = MaxLen;
	
	SysCallLib(_SYSCALL_SCAN_GET_BARCODE, &RetVal, Argc, Arg);
	return (unsigned short)RetVal;
}

unsigned short mScan_GetFormatBarcode(unsigned char *BarcodeStr,unsigned short MaxLen)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)BarcodeStr;
	Arg[1] = MaxLen;
	
	SysCallLib(_SYSCALL_SCAN_HANDLE_BARCODE, &RetVal, Argc, Arg);
	return (unsigned short)RetVal;
}

void mBarcodeForm_AddTimeDate(unsigned char select)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = select;
	
	SysCallLib(_SYSCALL_SCAN_ADD_TIME_DATE, &RetVal, Argc, Arg);
}

unsigned int  mScan_GetQuantity (void)
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

unsigned char mScan_GetBarcodeType(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_SCAN_GET_BARCODE_TYPE,&RetVal, 0, 0);

	return (unsigned char)RetVal;
}

unsigned short mScan_GetBarcodeLen(void)
{
	int RetVal;
	
	SysCallLib(_SYSCALL_SCAN_GET_BARCODE_LENGH,&RetVal, 0, 0);

	return (unsigned short)RetVal;
}



//******************************** Data batch *****************************//
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

void mDataBatch_SetInterface(unsigned char TcType)
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

unsigned char mDataBatch_TransmitData(void)
{
	int RetVal = 0;

	SysCallLib(_SYSCALL_DATABATCH_SEND_BATCH_DATA, &RetVal, 0, 0);
	
	return (unsigned char)RetVal;
}

unsigned char mDataBatch_SearchData(unsigned short DataLen, unsigned char *Data)
{
	int RetVal = 0;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = DataLen;
	Arg[1] = (unsigned int)Data;
	
	SysCallLib(_SYSCALL_DATABATCH_SEARCH_BARCODE, &RetVal, Argc, Arg);
	
	return (unsigned char)RetVal; 
}

unsigned char  mDataBatch_ExportDatatoTXTFile(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;
	
	SysCallLib(_SYSCALL_DATABATCH_EXPORT_BARCODE_TO_TXTFILE,&RetVal, Argc, Arg);

	return (unsigned int)RetVal; 	
}

void mDataBatch_SetBarcodeDelayTime(unsigned char Nms)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Nms;
	
	SysCallLib(_SYSCALL_DATABATCH_SET_BARCODE_DELAY_TIME, &RetVal, Argc, Arg);
}

void mDataBatch_Erase_Data(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_DATABATCH_CLEAR_BATCH_DATA, &RetVal, 0, 0);	
}

//******************************** SDK batch *****************************//
void mSDKBatch_Erase_Data(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_SDKBATCH_CLEAR_DATA, &RetVal, 0, 0);	
}

unsigned char mSDKBatch_StoreData(unsigned char *AddData, unsigned short AddSize)
{
	int RetVal;
	unsigned int Arg[2];
	unsigned char Argc = 2;

	Arg[0] = (unsigned int)AddData;
	Arg[1] = (unsigned int)AddSize;
	
	SysCallLib(_SYSCALL_SDKBATCH_STORE_DATA, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mSDKBatch_GetData(unsigned int Offset, unsigned char *GetData, unsigned short GetSize)
{
	int RetVal;
	unsigned int Arg[3];
	unsigned char Argc = 3;

	Arg[0] = Offset;
	Arg[1] = (unsigned int)GetData;
	Arg[2] = (unsigned int)GetSize;
	
	SysCallLib(_SYSCALL_SDKBATCH_GET_DATA, &RetVal, Argc, Arg);

	return (unsigned char)RetVal;
}

unsigned char mSDKBatch_ExportToFile(const char *FileName)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)FileName;
	
	SysCallLib(_SYSCALL_SDKBATCH_EXPORT_TO_FILE,&RetVal, Argc, Arg);

	return (unsigned int)RetVal; 	
}


//******************************** System setting - General *****************************//

void mSysSet_Language(unsigned char LVal)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = LVal;
	
	SysCallLib(_SYSCALL_SET_LANGUAGE, &RetVal, Argc, Arg);
}

void mSysSet_Volume(unsigned char Level)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Level;
	
	SysCallLib(_SYSCALL_SET_VOLUME, &RetVal, Argc, Arg);
}

void mSysSet_KeyBeep(unsigned char Statue)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Statue;

	SysCallLib(_SYSCALL_SET_KEYTONE, &RetVal, Argc, Arg);
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

void mSysSet_Brightness(unsigned char BLevel)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = BLevel;
	
	SysCallLib(_SYSCALL_SET_BRIGHTNESS, &RetVal, Argc, Arg);
}

void mSysSet_SleepTimeout(unsigned char Stval)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = Stval;
	
	SysCallLib(_SYSCALL_SET_SLEEP_TIMEOUT, &RetVal, Argc, Arg);
}

void mSysSet_USBKeyboardLayout(unsigned char KblVal)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = KblVal;
	
	SysCallLib(_SYSCALL_SET_USBKEYBOARD_LAYOUT, &RetVal, Argc, Arg);
}

void mSysSet_LoadDefaultSettingForScanner(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_SET_SCANER_DEFAULT_SETTING,&RetVal, 0, 0);
}

void mSysSet_SeparatorSetting(unsigned char *SepStr, unsigned char Length)
{
	int RetVal;
	
	unsigned int Arg[2];
	unsigned char Argc = 2;
	
	Arg[0] = (unsigned int)SepStr;
	Arg[1] = (unsigned int)Length;

	SysCallLib(_SYSCALL_SET_SEPARATOR_SETTING, &RetVal, Argc, Arg);
}

void mSysSet_BTKeyboardLayout(unsigned char KblVal)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = KblVal;
	
	SysCallLib(_SYSCALL_SET_BTKEYBOARD_LAYOUT, &RetVal, Argc, Arg);
}


//******************************** System information *****************************//

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

void mSysInfo_GetBluetoothName(unsigned char *Name)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)Name;

	SysCallLib(_SYSCALL_INFO_GET_BT_NAME, &RetVal, Argc, Arg);
}

void mSysInfo_GetBluetoothAddr(unsigned char *Addr)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)Addr;

	SysCallLib(_SYSCALL_INFO_GET_BT_ADDR, &RetVal, Argc, Arg);
}

unsigned char mSysInfo_GetKeyboardLayout(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_GET_KEYBOARD_LAYOUT, &RetVal, 0, 0);

	return (unsigned char)RetVal;
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

void mSysInfo_GetScannerVersion(unsigned char *Psv)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;
	
	Arg[0] = (unsigned int )Psv;

	SysCallLib(_SYSCALL_INFO_GET_SCANNER_VERS, &RetVal, Argc, Arg);
}

void mSysInfo_GetScanEngineVersion(unsigned char *Psev)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;
	
	Arg[0] = (unsigned int)Psev;

	SysCallLib(_SYSCALL_INFO_GET_SCAN_ENGINE_VERS, &RetVal, Argc, Arg);
}

void mSysInfo_GetScannerSerialNumber(unsigned char *pSSN)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)pSSN;
	
	SysCallLib(_SYSCALL_INFO_GET_SERIAL_NUMBER, &RetVal, Argc, Arg);
}

void mSysInfo_GetBluetoothVersion(unsigned char *Pblv)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;
	
	Arg[0] = (unsigned int)Pblv;

	SysCallLib(_SYSCALL_INFO_GET_BT_VERS, &RetVal, Argc, Arg);
}

unsigned char mSysInfo_GetBrightness(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_GET_BRIGHTNESS, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

unsigned char mSysInfo_GetDataTransferMode(void)
{
	int RetVal;
	SysCallLib(_SYSCALL_INFO_GET_DATATRANSFER_MODE, &RetVal, 0, 0);
	return (unsigned char)RetVal;
}

//******************************** Power ON/OFF Screens *****************************//

void mReg_StartupShowFunc(Registry_t Func)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)Func;

	SysCallLib(_SYSCALL_REGISTER_STARTUP_SHOW, &RetVal, Argc, Arg);	
}

void mReg_PowerOffShowFunc(Registry_t Func)
{
	int RetVal;
	unsigned int Arg[1];
	unsigned char Argc = 1;

	Arg[0] = (unsigned int)Func;

	SysCallLib(_SYSCALL_REGISTER_POWEROFF_SHOW, &RetVal, Argc, Arg);	
}

