/****************************************Copyright (c)**************************************************
**
**-----------------------------------------File Info----------------------------------------------------
** File name:		SysCallLib.h
** Decriptions:         
**------------------------------------------------------------------------------------------------------
** Latest modified By: YeYW, 2015-08-18
** Latest Version:	3.3.x
** Descriptions:		  
**------------------------------------------------------------------------------------------------------
** Created by:		jason.lam
** Created date:		2012-07-10
** Version:		2.1.5
** Descriptions: Add APIs(Bluetooth Receive and Database Delete)	
** Notice: This APIs document is only provided for the MS3590 Mobile Scanner.
**------------------------------------------------------------------------------------------------------
**- Listing: List the functions' simplified descriptions here
********************************************************************************************************/
#ifndef MS3590_SYS_CALL_LIB_H 
#define MS3590_SYS_CALL_LIB_H

typedef _Bool bool;
typedef void (*Registry_t) (void);

#define 	BARCODE_LENGTH	4096

#define  FALSE  		0
#define  TRUE 			1

#define	INVALID		0			//Invalid	
#define	VALID  		1			//Valid

#define     OUT                     0             //Put in
#define     IN                      !OUT          //Extraction

#define      DISABLE                0
#define      ENABLE                 !DISABLE

#define      DISCONNECT       		0
#define      CONNECT         		!DISCONNECT

/*Frequency*/
#define  BEEP_HIGH_FREQ					2660
#define  BEEP_MIDD_FREQ					1500
#define  BEEP_LOW_FREQ					500

/*Key Value*/
#define 	KEY_NULL                0x00		//Null Key
 #define 	KEY_UP_VALUE            0x01		//Up Navigation Key¡ü
 #define 	KEY_DOWN_VALUE         	0x02		//Down Navigation Key¡ý
 #define 	KEY_LEFT_VALUE          0x03 		//Left Navigation Key¡û
 #define 	KEY_RIGHT_VALUE         0x04 		//Right Navigation Key¡ú
 #define 	KEY_LEFT_SOFT_VALUE   	0x05 		//Left Soft Key?
 #define 	KEY_RIGHT_SOFT_VALUE 	0x06 		//Right Soft Key?
 #define 	KEY_TRIGGER_VALUE     	0x07 		//Trigger Key
 #define 	KEY_RETURN_VALUE       	0x08 		//Return Key

/*Key Status*/
#define       IS_PRESSED          	0
#define       IS_RELEASED        	!IS_PRESSED

#define     KEY_UP               1
#define     KEY_DOWN            (1<<1)
#define     KEY_LEFT            (1<<2)
#define     KEY_RIGHT           (1<<3)
#define     KEY_LEFT_UP         (1<<4)
#define     KEY_RIGHT_UP        (1<<5)
#define     KEY_TRIGGER       	(1<<6)
#define     KEY_RETURN         	(1<<7)  

/*Character Font*/
#define FONT_CharacterEncoding_UTF8			0
#define FONT_CharacterEncoding_GBK			1
#define FONT_CharacterEncoding_BIG5			2
#define FONT_CharacterEncoding_EUC_KR			3
#define FONT_CharacterEncoding_Shift_JIS		4
#define FONT_CharacterEncoding_Windows_1250	5
#define FONT_CharacterEncoding_Windows_1251	6
#define FONT_CharacterEncoding_Windows_1252	7
#define FONT_CharacterEncoding_Windows_1253	8
#define FONT_CharacterEncoding_Windows_1254	9
#define FONT_CharacterEncoding_Windows_1255	10
#define FONT_CharacterEncoding_Windows_1256	11
#define FONT_CharacterEncoding_Windows_1257	12
#define FONT_CharacterEncoding_Windows_1258	13	
		
#define FONT_CharacterEncoding_DEFAULT	FONT_CharacterEncoding_GBK

/* Character Font Size*/
//Apply to English Font
#define  FontSize6X12          0
#define  FontSize8X16          2
//Apply to Chinese Font
#define  FontSize12X12         1
#define  FontSize16X16         3

/* Display Area*/
#define  LCD_W                    128
#define  LCD_H                    64

/* Refurbish Flag*/
#define      DISPLAY_1to3_LINE      1 // Display 1 to 3 line;
#define      DISPLAY_2to4_LINE      2 // Display 2 to 4 line;

/*USB Protocol*/
#define     USB_HID             0x01          //HID 
#define     USB_VIRTUAL_COM     0x02          //Virtual COM
#define     USB_MASS_STORAGE  	0x03          //Mass Storage Device

/*WiFi Power Mode*/
#define PWRMODE0			0   // Normal
#define PWRMODE1			1	// Shallow Sleep
#define PWRMODE2			2	// Deep Sleep
#define PWRMODE3			3	// Shut Down

/*Bluetooth Protocol*/
#define      HID_KEYBOARD   	0x00          //HID 
#define      SPP_SLAVE          0x01          //SPP(Slave)
#define      SPP_HOST           0x02          //SPP(Host)
#define      BA2110             0x03          // Dedicated receiver

/*BA2110 Protocol*/
#define 	BA2110_HID_KEYBOARD   	0x00		//HID Keyboard
#define 	BA2110_SPP				0x01		//Virtual COM

/*BA2110 Keyboard Layout*/
#define BA2110_KBL_USA   			0x00		//USA
#define BA2110_KBL_Turkish_F		0x01		//Turkish F
#define	BA2110_KBL_Turkish_Q		0x02		//Turkish Q
#define	BA2110_KBL_French			0x03		//French
#define	BA2110_KBL_Italian			0x04		//Italian	
#define	BA2110_KBL_Spanish			0x05		//Spanish
#define	BA2110_KBL_Slovak			0x06		//Slovak
#define	BA2110_KBL_Denmark			0x07		//Denmark	
#define	BA2110_KBL_Japan			0x08		//Japan
#define	BA2110_KBL_German			0x09		//German

#define	BA2110_HIDDEY_LOW   	0x00		//LOW speed
#define BA2110_HIDDEY_MIDDLE	0x01		//MIDDLE speed
#define	BA2110_HIDDEY_HIGH		0x02		//HIGH speed

#define	CENTRAL_SECTION				0x00	//Central Section in keyboard*
#define NUMBER_AIDED_SECTION		0x01	//Number aided section in keyboard
#define	ALT_NUMBER_AIDED_SECTION	0x02	//ALT+Number aided section in keyboard


/*File Operation Return Value*/
#define       ERROR_PARA             -1              //Parameter Error
#define       FAILURE                0               //Failure
#define       SUCCESS              	 1               //Success
#define       EXIST                  2               //Exist
#define       NOT_EXIST         	 3               //Not Exist
#define       NO_ROOM           	 4               //No Room

/*File Attribute*/
#define       READWRITE          0x00          //For read and write
#define       READONLY           0x01          //Read only
#define       HIDE               0x02          //Hide
#define       SYSTEM             0x04          //System File
#define       VOLUME             0x08          // Volume
#define       SUBDIRECTORY       0x10          // Subdirectory
#define       FILE               0x20          //File

/*Keyboard Layout*/
#define       USA               0x00          // USA
#define       Turkish_F         0x01          // Turkish F
#define       Turkish_Q         0x02          // Turkish Q
#define       French            0x03          // French
#define       Italian           0x04          // Italian
#define       Spanish           0x05      	  // Spanish
#define       Slovak            0x06          // Slovak
#define		  Denmark			0x07
#define       Japan             0x08          // Japan
#define		  German			0x09

#define      ENGLISH         0               //English
#define      SIM_CHINESE  	 1               // Simplified Chinese
#define      TRAN_CHINESE    1               //Traditional Chinese

/*Buzzer Volume Macro Definition*/
#define       LOW               0x00     //Low
#define       MIDDLE            0x01     //Middle
#define       HIGH              0x02     //High
#define       SHUT_DOWN   		0x03     //Shut down

/*Backlight Timeout*/
#define      TIME_10S        0               //10 seconds
#define      TIME_30S        1               //30 seconds
#define      TIME_60S        2               //50 seconds

/*Sleep Timeout*/
#define      TIME_1MIN       0               // 1 Minute
#define      TIME_5MIN       1               // 5 Minutes
#define      TIME_10MIN      2               //10 Minutes

#define		 TIMEOUT_NOWAIT		0			// No wait 
#define		 TIMEOUT_INFINITE	0xFFFF		// Always waiting 

/*Scan Mode*/
#define      GOOD_READ_OFF  	0         // Good-read off
#define      MOMENTARY          1         // Momentary
#define      CONTINUE           2         // Continuous

/*Code Type*/
#define MACR_CODE_TYPE_EAN13		1
#define MACR_CODE_TYPE_EAN8			2
#define MACR_CODE_TYPE_UPCA			3
#define MACR_CODE_TYPE_UPCE			4
#define MACR_CODE_TYPE_UCCEAN128	5
#define MACR_CODE_TYPE_CODE128		6
#define MACR_CODE_TYPE_CODE39		7
#define MACR_CODE_TYPE_CODABAR		8 
#define MACR_CODE_TYPE_INTL25		9
#define MACR_CODE_TYPE_CODE93		10
#define MACR_CODE_TYPE_INDS25		11
#define MACR_CODE_TYPE_MATR25		12
#define MACR_CODE_TYPE_CHNPST		13
#define MACR_CODE_TYPE_CODE11		14
#define MACR_CODE_TYPE_UKPL			15
#define MACR_CODE_TYPE_MSIPL		16
#define MACR_CODE_TYPE_GS1DB		17 
#define MACR_CODE_TYPE_GS1LIMI		18
#define MACR_CODE_TYPE_GS1EXPA		19

#define MACR_CODE_TYPE_CHNFNC		21
#define MACR_CODE_TYPE_ISBT128  	22
#define MACR_CODE_TYPE_ISBN       	23
#define MACR_CODE_TYPE_UPCE1        24

#define MACR_CODE_TYPE_PDF417			60
#define MACR_CODE_TYPE_MICPDF417		61
#define MACR_CODE_TYPE_QRCODE			62
#define MACR_CODE_TYPE_DATAMATRIX		63
#define MACR_CODE_TYPE_MAXICODE			64
#define MACR_CODE_TYPE_AZTEC			65
#define MACR_CODE_TYPE_CSCODE			66

#define MACR_CODE_TYPE_NONE				255


/*Instructions Icons*/
#define   NOINSTRUCTIONS		0x00	//No instructions
#define   BTCONNECT				0x01	//Show Bluetooth icon
#define   TIME					0x02	//Show Time
#define   USBCONNECT			0x04	//Show USB icon
#define   BATTERYCAPACITY		0x08	//Show Battery cappacity icon

/*Database Information Struct*/
typedef struct {
  char   idxfile[13];
  char   datfile[13];
  char  idxbuf[128];
  char datbuf[256];   
  unsigned int fatheridxoff;
  unsigned int idxoff;
  unsigned char idxlen;
  unsigned int datoff;
  unsigned char datlen;      
  unsigned int ptroff;
  unsigned char ptrsize;     
  unsigned int ptrval;
  unsigned int chainoff;
  unsigned char freelistoff; 
  unsigned char hashtaleoff;
  unsigned int hashsize;
  unsigned char hashoptions;
} DB;

/*Database Open Flag*/
#define O_OPEN              1         //Only open database files flag
#define O_CREAT             2         //Only create and opens database files
#define O_TRUNC             4         //Only open database files and truncates it to zero length and rebuild empty database files.

/*Database Store Data Flag*/
#define DB_INSERT        1         // Insert new record only 
#define DB_REPLACE       2         // Replace existing record
#define DB_STORE         4         // Insert new record when it is not existing. Replace record when it is exist. 
 

/*Battery Information Struct*/
typedef struct _BatteryInfo
{
 unsigned int MinVoltage;
 unsigned int MaxVoltage;
 unsigned int CurVoltage;
 unsigned int Percent; 
}BATTERY_INFO;

/*Week Day Macro Definition*/
#define SUNDAY          0x00          //Sunday
#define MONDAY          0x01          //Monday
#define TUESDAY         0x02          //Tuesday
#define WEDNESDAY    	0x03          //Wednesday
#define THURSDAY       	0x04          //Thursday
#define FRIDAY          0x05          //Friday
#define SATURDAY       	0x06          //Saturday


/*Time Information Structure*/
typedef struct Time_s/* Time Structure definition */
{
  unsigned char Sec;
  unsigned char Min;
  unsigned char Hour;
} Time;


/*Day Information Structure*/
typedef struct Date_s/* Date Structure definition */
{
  unsigned char Month;
  unsigned char Day;
  unsigned int Year;
} Date;


/*Memory Information Struct*/ 
typedef struct _MemoryInfo
{
 unsigned int TotalMemory;
 unsigned int UseMemory;
 unsigned int FreeMemory;
} MEMORY_INFO;
 

/*Bluetooth Information Struct*/
typedef struct _BluetoothInfo
{
volatile char DeviceName[20];
volatile char DeviceAdd[20];
} BLUETOOTH_INFO;


/*WiFi hot spot */
#define HOTSPOTNAMEMAXLEN 30
typedef struct _WIFIHotSpotInfo
{
	 char Hot_Spot_Name[HOTSPOTNAMEMAXLEN];
	 char EncryptionFlg;
}Hot_Spot_INFO;


/*List the functions*/
unsigned char  mSystem_CheckVerificationCode(const char VCStr[]);
unsigned char  mSystem_SetVerificationCode(const char VCStr[]);
int  mSystem_SaveParameter(unsigned char SequenceNum , int Para);
int  mSystem_ClearParameter(unsigned char SequenceNum);
int  mSystem_GetParameter(unsigned char SequenceNum);
unsigned char  mSystem_SetInstallationKey(const char IKStr [ ]);


void mLCD_BacklightOn();
void mLCD_BacklightOff();
void mLCD_Clear();
void mLCD_DisplayImage(unsigned char x, unsigned char y, const unsigned char* ImagePt, unsigned char ImageXSize, unsigned char ImageYSize );
void mLCD_Printf(unsigned char x, unsigned char y,  const char *StrPt,unsigned char FontSize);
void mLCD_InversePixel(unsigned char x,unsigned  char y);
void mLCD_InverseRegionPixels(unsigned char x,unsigned  char y,unsigned char RegionXSize, unsigned char RegionYSize);
void mLCD_BackupDisplayBuffer();
void mLCD_ReloadDisplayBuffer();
void mLCD_PrintPageInit(unsigned char top_x, unsigned char top_y, unsigned char bottom_x, unsigned char bottom_y, const char *StrPt, unsigned int StrLength);
void mLCD_PrintPrePage();
void mLCD_PrintNextPage();
void mLCD_SetPrintfLocale(unsigned char locale);


unsigned char mKey_ScanKeyboard();
unsigned char mKey_GetKeyValue();
unsigned char mKey_GetLeftKeyStatus(); 
unsigned char mKey_GetRightKeyStatus(); 
unsigned char mKey_GetUpKeyStatus(); 
unsigned char mKey_GetDownKeyStatus(); 
unsigned char mKey_GetLeftSoftKeyStatus(); 
unsigned char mKey_GetRightSoftKeyStatus(); 
unsigned char mKey_GetTirgKeyStatus(); 
unsigned char mKey_GetReturnKeyStatus(); 
void mKey_ClearKeyBuffer();
void mKey_EnableInterruptScanKeyMode(void);
void mKey_DisableInterruptScanKeyMode(void);


void mLED_GreenLedOn();
void mLED_GreenLedOff();


void mBeeper_StartBeeper(unsigned int nDuration);
void mBeeper_SetBeeperFreq(unsigned int Period_No_Of_CCLK);
void mVibrator_StartVibr(unsigned int  nDuration);


void  mRTC_GetTime(Time *SysTime);
void  mRTC_GetDate(Date *SysDate);
unsigned char mRTC_SetDate(unsigned short CurrentYear, unsigned char CurrentMonth, unsigned char CurrentDay);
unsigned char mRTC_SetTime(unsigned char Hour, unsigned char minute, unsigned char Seconds);
unsigned short mRTC_WeekDay(unsigned short CurrentYear, unsigned char CurrentMonth, unsigned char CurrentDay);

unsigned char mBattery_GetBatteryLifePercent();
void mBattery_GetBatteryInfo(BATTERY_INFO *Pbi);


void mUSB_USBProtocol(unsigned char USBPro);
unsigned char mUSB_GetUSBConnectStatus();
unsigned char mUSB_HIDSendData(const void *DataBuf, unsigned short DataSize);
unsigned int mUSB_VCOMReceiveData(void *RxBuffer, unsigned short Size, unsigned short Timeout);
unsigned char mUSB_VCOMSendData(const void *DataBuf, unsigned short DataSize);


unsigned char mBT_BluetoothDefaultSetting();
unsigned char mBT_GetBluetoothCurrentProtocol();
unsigned char  mBT_SetBluetoothProtocol(unsigned char BpPro);
void mBT_SearchAndConnectDevicesInSPPMaster();
void mBT_SearchAndConnectDevicesInBA2110();
unsigned char  mBT_AutoReconnect(unsigned char ArStu);
unsigned char mBT_SendPacket(const void *DatBuf, unsigned short DataSize);
unsigned char mBT_GetConnectStatus();
void mBT_HIDDelayTime(unsigned char Nms);
unsigned int mBT_SPPReceiveBTPacket(void *RxBuffer, unsigned short Size, unsigned short Timeout);
unsigned int mBT_SPPReceiveBA2110Packet(void *RxBuffer, unsigned short Size, unsigned short Timeout);
unsigned char mBT_SetBA2110Protocol(unsigned char BA2110Pro);
unsigned char mBT_SetBA2110KeyboardLayout(unsigned char KblVal);
unsigned char mBT_SetBA2110HIDTransmissionRate(unsigned char HIDTRLevel);
unsigned char mBT_SetBA2110KeyboardDivision(unsigned char KbDin);
unsigned char mBT_SetBluetoothName(const char *BTname);
void mBT_PowerUp(void);
void mBT_PowerOff(void);
void mBT_Disconnect(void);
unsigned char mBT_Connect(unsigned char *BTAddress, unsigned int Timeout);

unsigned char mFAT32_SystemInit();
void mFAT32_GetFileList(void);
unsigned char mFAT32_NewFile(const char *FileName);
unsigned char mFAT32_FileSuperaddition(const char *FileName, const  void *Pbuffer, unsigned short length);
unsigned char  mFAT32_FileDelete(const char *FileName);
unsigned char  mFAT32_FileClear(const char *FileName);
int  mFAT32_FileRead(const char *FileName, unsigned int offset, void *Pbuffer, unsigned short length);
unsigned char  mFAT32_DiskFormat();
void  mFAT32_CloseSystem();
void  mFAT32_Flush();
unsigned char  mFAT32_GetTargetFile(char *FileName);
int  mFAT32_GetFileSize(const char *FileName);
unsigned char  mFAT32_SetFileAttribute(const char *FileName, unsigned char DeAttribute );
unsigned char  mFAT32_StoreDataInUdisk(const void *DataBuf, unsigned short DataSize);
int mFAT32_SetTargetFileInUdisk(const char *Filename);


unsigned char   mDB_Open(const char *DB_Name, DB *PDBStruct, unsigned char OFlag);
unsigned char  mDB_FetchData(DB *PDBStruct, void *Databuffer, const char *Key);
unsigned char mDB_StoreData(DB *PDBStruct, void *DataBuffer, unsigned char DataLength, const char *Key, int Flag);
unsigned char mDB_DeleteRecord(DB *PDBStruct, const char *Key);
unsigned char mDB_Export(DB *PDBStruct, const char *FileName, const char *Separator);


void mScan_ScanMode(unsigned char SmType);
unsigned char mScan_GetDecodeStatus();  
void mScan_Operation();
void mScan_GetBarcode(char *BarcodeStr, unsigned short *BarcodeLen);
void mBarcodeForm_AddTime(unsigned char ATStu);
void mBarcodeForm_AddData(unsigned char ADStu);
unsigned int  mScan_GetQuantity();
void mScan_AddQuantity(unsigned char num);
void mScan_ClearQuantity(void);
unsigned char  mBarcodeForm_GetBarcodeType();


unsigned char mDataBatch_StoreData(const void *Databuf,  unsigned short DataSize);
unsigned char mDataBatch_TransmitData();
void mDataBatch_SetInterface(unsigned char TcType);
unsigned char mDataBatch_GetBufferstatus();
void  mDataBatch_SetDataStatistics(unsigned char DsStu);
unsigned char mDataBatch_SearchData(unsigned char String[]);
unsigned int  mDataBatch_ExportDatatoTXTFile(const char *FileName);


void mSysSet_KeyboardLayout(unsigned char KblVal);
void mSysSet_Language(unsigned char LVal);
void mSysSet_Beeper(unsigned char BLevel);
void mSysSet_Vibrator(unsigned char VibStu);
void mSysSet_BacklightTimeout(unsigned char Btval);
void mSysSet_SleepTimeout(unsigned char Stval);
void mSysSet_LoadDefaultSettingForScanner(void);
void mSysSet_LoadDefaultSettingForBA2110(void);
void mSysSet_SeparatorSetting(unsigned char SepStr[ ]);


void mSysInfo_GetMemoryVolume(MEMORY_INFO *Pmi);
void mSysInfo_EraseMemory();
void mSysInfo_GetBluetoothInfo(BLUETOOTH_INFO *Pbli);
void mSysInfo_GetScannerVersion(char *Psv);
void mSysInfo_GetScanEngineVersion(char *Psev);
void mSysInfo_GetBluetoothVersion(char *Pblv);
unsigned char mSysInfo_GetLanguage();
unsigned char mSysInfo_GetVolumeOfBeeper();
unsigned char mSysInfo_GetVibratorSettingStatus();
unsigned char mSysInfo_GetBacklightTimeout();
unsigned char mSysInfo_GetSleepTimeout();
unsigned char mSysInfo_GetKeyboardLayout();
void mSysInfo_GetScannerSerialNumber(char *pSSN);


void mGUI_DrawNumericKeypad(unsigned char vernierX, unsigned char vernierY);
void mGUI_DrawSpecialSignKeypad(unsigned char vernierX, unsigned char vernierY, unsigned char change_screen_flag);
void mGUI_DrawFullKeypad(unsigned char vernierX, unsigned char vernierY, unsigned char change_screen_flag);
unsigned char mGUI_GetNumericKeypadValue(unsigned char vernierX, unsigned char vernierY);
unsigned char mGUI_GetSpecialSignKeypadValue(unsigned char vernierX, unsigned char vernierY);
unsigned char mGUI_GetFullKeypadValue(unsigned char vernierX, unsigned char vernierY);
void mGUI_SetInstructionsIcon(unsigned char IconFlg);
unsigned char mGUI_GetFontDotMatrix(unsigned char *MatBuffer, unsigned int Offset, unsigned char FontSize);


void mReg_StartupShowFunc(Registry_t Func);
void mReg_PowerOffShowFunc(Registry_t Func);
void mReg_LowPowerIndicationFunc(Registry_t Func);
void mReg_SetTimerFunc(unsigned short Nms, Registry_t Func);
void mReg_KillTimerFunc();
void mReg_ResetStartupShowFunc();
void mReg_ResetPowerOffShowFunc();


unsigned char mWiFi_SendPacket(unsigned char *TxBuffer, unsigned short DataLength);
unsigned char mWiFi_GetConnectStatus(void);
unsigned char mWiFi_Disconnect(void);
void mWiFi_PowerOn(void);
void mWiFi_PowerOff(void);
unsigned char mWiFi_PowerModeSetting(unsigned char mode);
void mWiFi_StationModeSetting(void);
void mWiFi_APModeSetting(void);
unsigned char mWiFi_StationModeSearchHotSpot(void);
unsigned char mWiFi_StationModeGetHotSpotInfo(Hot_Spot_INFO *HSI, unsigned short Index );
unsigned char mWiFi_StationModeWLANConnect(unsigned char *SSID, unsigned char EncryptionFlag, unsigned char *Passphrase, unsigned char DHCPFlag, unsigned char *StaticIP);
unsigned char mWiFi_StationModeHostConnect(unsigned char *HostIP, unsigned char *HostPort, unsigned char *LocalPort, unsigned char Flag);
unsigned char mWiFi_APModeSSIDandPassphraseSetting(unsigned char *SSID, unsigned char EncryptionFlag, unsigned char *Passphrase, unsigned char *LocalPort);
unsigned int mWiFi_ReceivePacket(unsigned char *RxBuffer, unsigned short Size, unsigned short Timeout);
unsigned char mWiFi_StationModeGetHostConnectStatus(void);
unsigned char mWiFi_StationModeHostDisconnect(void);
unsigned char mWiFi_StationModeAutoConnect(void);

#endif
