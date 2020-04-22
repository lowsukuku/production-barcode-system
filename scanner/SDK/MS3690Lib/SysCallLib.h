/****************************************Copyright
*(c)**************************************************
**
**-----------------------------------------File
*Info----------------------------------------------------
** File name:		SysCallLib.h
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
********************************************************************************************************/
#ifndef MS3690_SYS_CALL_LIB_H
#define MS3690_SYS_CALL_LIB_H

#ifndef __cplusplus
typedef _Bool bool;
#endif
typedef void (*Registry_t)(void);

#define FIRST_LINE 0
#define TWO_LINE 12
#define THREE_LINE 24
#define FOUR_LINE 36
#define BOTTOM_LINE 52

#define BARCODE_LENGTH 512
#define HOST_MAX_COUNT 8

#define FALSE 0
#define TRUE 1

#define INVALID 0  // Invalid
#define VALID 1    // Valid

#define OUT 0    // Extraction
#define IN !OUT  // Put in

#define DISABLE 0
#define ENABLE !DISABLE

#define DISCONNECT 0
#define CONNECT !DISCONNECT

#define NO_CONNECT HOST_MAX_COUNT

/*PSK*/
#define NONE_ENCRYPTED 0x00
#define ENCRYPTED 0x01

/*DHCP*/
#define DHCP_CLIENT 0x00
#define IP_STATIC 0x01

/*Frequency*/
#define BeeperFreq_2304Hz 1000000 / 2304
#define BeeperFreq_2404Hz 1000000 / 2404
#define BeeperFreq_2504Hz 1000000 / 2504
#define BeeperFreq_2554Hz 1000000 / 2554
#define BeeperFreq_2560Hz 1000000 / 2560
#define BeeperFreq_2602Hz 1000000 / 2602
#define BeeperFreq_2700Hz 1000000 / 2700
#define BeeperFreq_2730Hz 1000000 / 2730
#define BeeperFreq_2800Hz 1000000 / 2800
#define BeeperFreq_2890Hz 1000000 / 2890
#define BeeperFreq_2920Hz 1000000 / 2920
#define BeeperFreq_3000Hz 1000000 / 3000
#define BeeperFreq_Default BeeperFreq_2700Hz

/*Key Value*/
#define KEY_NULL 0x00              // Null Key
#define KEY_UP_VALUE 0x01          // Up Navigation Key��
#define KEY_DOWN_VALUE 0x02        // Down Navigation Key��
#define KEY_LEFT_VALUE 0x03        // Left Navigation Key��
#define KEY_RIGHT_VALUE 0x04       // Right Navigation Key��
#define KEY_LEFT_SOFT_VALUE 0x05   // Left Soft Key?
#define KEY_RIGHT_SOFT_VALUE 0x06  // Right Soft Key?
#define KEY_TRIGGER_VALUE 0x07     // Trigger Key
#define KEY_RETURN_VALUE 0x08      // Return Key
#define KEY_PAUSE_VALUE 0x09       // Pause Key

/*Key Status*/
#define IS_PRESSED 0
#define IS_RELEASED !IS_PRESSED

#define KEY_UP 1
#define KEY_DOWN (1 << 1)
#define KEY_LEFT (1 << 2)
#define KEY_RIGHT (1 << 3)
#define KEY_LEFT_UP (1 << 4)
#define KEY_RIGHT_UP (1 << 5)
#define KEY_TRIGGER (1 << 6)
#define KEY_RETURN (1 << 7)

/*Character Font*/
#define FONT_CharacterEncoding_UTF8 0
#define FONT_CharacterEncoding_GBK 1
#define FONT_CharacterEncoding_BIG5 2
#define FONT_CharacterEncoding_EUC_KR 3
#define FONT_CharacterEncoding_Shift_JIS 4
#define FONT_CharacterEncoding_Windows_1250 5
#define FONT_CharacterEncoding_Windows_1251 6
#define FONT_CharacterEncoding_Windows_1252 7
#define FONT_CharacterEncoding_Windows_1253 8
#define FONT_CharacterEncoding_Windows_1254 9
#define FONT_CharacterEncoding_Windows_1255 10
#define FONT_CharacterEncoding_Windows_1256 11
#define FONT_CharacterEncoding_Windows_1257 12
#define FONT_CharacterEncoding_Windows_1258 13

#define FONT_CharacterEncoding_DEFAULT FONT_CharacterEncoding_GBK

/* Character Font Size*/
// Apply to English Font
#define FontSize6X12 0
#define FontSize8X16 2
// Apply to Chinese Font
#define FontSize12X12 1
#define FontSize16X16 3

/* Display Area*/
#define OLED_W 128
#define OLED_H 64

#define APP_BLED 0
#define APP_GLED 1
#define APP_RLED 2

#define APP_LED_CLOSE 0
#define APP_LED_OPEN 1

/* Refurbish Flag*/
#define DISPLAY_1to3_LINE 1  // Display 1 to 3 line;
#define DISPLAY_2to4_LINE 2  // Display 2 to 4 line;

/*WiFi Power Mode*/
#define PWRMODE0 0  // Normal
#define PWRMODE1 1  // Power_Save

#define BT_PUBLIC_ADDRESS 0
#define BT_RANDOM_ADDRESS 1

/*Bluetooth Protocol*/
#define HID 0x00         // HID
#define SPP 0x01         // SPP
#define BLE_SLAVE 0x02   // BLE SLAVE
#define CRADLE 0x03      // Dedicated receiver
#define BLE_MASTER 0x04  // BLE MASTER

/*Bluetooth Receive data*/
#define BT_NO_DATA 0
#define BT_SPP_DATA 1
#define BT_BLE_DATA 2

/*Bluetooth Search Device Type*/
#define BT_SPP 0x01  // SPP
#define BT_BLE 0x02  // BLE SLAVE
#define BT_HID 0x03  // HID
#define BT_ALL 0x04  // all device

/*Cradle Protocol*/
#define CRADLE_HID_KEYBOARD 0x00  // HID Keyboard
#define CRADLE_SPP 0x01           // Virtual COM

/*Cradle Keyboard Layout*/
#define CRADLE_KBL_USA 0x00        // USA
#define CRADLE_KBL_Turkish_F 0x01  // Turkish F
#define CRADLE_KBL_Turkish_Q 0x02  // Turkish Q
#define CRADLE_KBL_French 0x03     // French
#define CRADLE_KBL_Italian 0x04    // Italian
#define CRADLE_KBL_Spanish 0x05    // Spanish
#define CRADLE_KBL_Slovak 0x06     // Slovak
#define CRADLE_KBL_Denmark 0x07    // Denmark
#define CRADLE_KBL_Japan 0x08      // Japan
#define CRADLE_KBL_German 0x09     // German

#define CRADLE_HIDDEY_LOW 0x00     // LOW speed
#define CRADLE_HIDDEY_MIDDLE 0x01  // MIDDLE speed
#define CRADLE_HIDDEY_HIGH 0x02    // HIGH speed

#define CENTRAL_SECTION 0x00           // Central Section in keyboard*
#define NUMBER_AIDED_SECTION 0x01      // Number aided section in keyboard
#define ALT_NUMBER_AIDED_SECTION 0x02  // ALT+Number aided section in keyboard

#define CRADLE_ERROR 0xFF  // Failed to get the parameters.

/*File Operation Return Value*/
#define ERROR_PARA -1  // Parameter Error
#define FAILURE 0      // Failure
#define SUCCESS 1      // Success
#define EXIST 2        // Exist
#define NOT_EXIST 3    // Not Exist
#define NO_ROOM 4      // No Room

/*File Attribute*/
#define READWRITE 0x00     // For read and write
#define READONLY 0x01      // Read only
#define HIDE 0x02          // Hide
#define SYSTEM 0x04        // System File
#define VOLUME 0x08        // Volume
#define SUBDIRECTORY 0x10  // Subdirectory
#define FILE 0x20          // File

/*Keyboard Layout*/
#define USA 0x00        // USA
#define Turkish_F 0x01  // Turkish F
#define Turkish_Q 0x02  // Turkish Q
#define French 0x03     // French
#define Italian 0x04    // Italian
#define Spanish 0x05    // Spanish
#define Slovak 0x06     // Slovak
#define Denmark 0x07
#define Japan 0x08  // Japan
#define German 0x09

/*Language*/
#define ENGLISH 0       // English
#define SIM_CHINESE 1   // Simplified Chinese
#define TRAN_CHINESE 2  // Traditional Chinese

/*Buzzer Volume Macro Definition*/
#define LOW 0x00        // Low
#define MIDDLE 0x01     // Middle
#define HIGH 0x02       // High
#define SHUT_DOWN 0x03  // Shut down

/*Backlight Timeout*/
#define TIME_10S 0  // 10 second
#define TIME_30S 1  // 30 second
#define TIME_60S 2  // 60 second

/*Sleep Timeout*/
#define TIME_1MIN 0     // 1 Minute
#define TIME_5MIN 1     // 5 Minutes
#define TIME_10MIN 2    // 10 Minutes
#define TIME_DISABLE 3  // Disable

#define TIMEOUT_NOWAIT 0         // No wait
#define TIMEOUT_INFINITE 0xFFFF  // Always waiting

/*add Time or Date*/
#define ADD_NONE 0x00
#define ADD_TIME 0x01
#define ADD_DATE 0x02
#define ADD_TIME_AND_DATE 0x03

/*Scan Mode*/
#define GOOD_READ_OFF 0  // Good-read off
#define MOMENTARY 1      // Momentary
#define CONTINUE 2       // Continuous

/*DataBatch Interface*/
#define WIRELESS 0  // Wi-Fi or Bluetooth
#define USB_HID 1   // USB HID
#define USB_VCOM 2  // USB VCOM

/*Data transfer mode*/
#define DATA_TRANSFER_WIRELESS 0
#define DATA_TRANSFER_USB_KEY_BOARD 1
#define DATA_TRANSFER_USB_VIR_COM 2
#define DATA_TRANSFER_USB_DISK 3
#define DATA_TRANSFER_DATA_BATCH 4

/*DataBatch Return*/
#define DATABATCH_FALSE 0         // fail
#define DATABATCH_TRUE 1          // success
#define DATABATCH_NO_DATA 2       // not data
#define DATABATCH_ADDR_INVALID 3  // invalid
#define DATABATCH_FILE_EXIST 4    // file is exist

/*Code Type*/
// 1D code
#define MACR_CODE_TYPE_NONE 0x0
#define MACR_CODE_TYPE_CODE39 0x1
#define MACR_CODE_TYPE_CODABAR 0x2
#define MACR_CODE_TYPE_CODE128 0x3
#define MACR_CODE_TYPE_INDS25 0x4
#define MACR_CODE_TYPE_IATA25 0x5
#define MACR_CODE_TYPE_INTL25 0x6
#define MACR_CODE_TYPE_CODE93 0x7
#define MACR_CODE_TYPE_UPCA 0x8
#define MACR_CODE_TYPE_UPCA_ADDON2 0x48
#define MACR_CODE_TYPE_UPCA_ADDON5 0x88
#define MACR_CODE_TYPE_UPCE 0x09
#define MACR_CODE_TYPE_UPCE_ADDON2 0x49
#define MACR_CODE_TYPE_UPCE_ADDON5 0x89
#define MACR_CODE_TYPE_EAN8 0x0A
#define MACR_CODE_TYPE_EAN8_ADDON2 0x4A
#define MACR_CODE_TYPE_EAN8_ADDON5 0x8A
#define MACR_CODE_TYPE_UKPL 0x13
#define MACR_CODE_TYPE_ISBT128 0x19
#define MACR_CODE_TYPE_CODE11 0x0C
#define MACR_CODE_TYPE_EAN13 0x0B
#define MACR_CODE_TYPE_EAN13_ADDON2 0x4B
#define MACR_CODE_TYPE_EAN13_ADDON5 0x8B
#define MACR_CODE_TYPE_MSIPL 0x0E
#define MACR_CODE_TYPE_UCCEAN128 0x0F
#define MACR_CODE_TYPE_UPCE1 0x10
#define MACR_CODE_TYPE_UPCE1_ADDON2 0x50
#define MACR_CODE_TYPE_UPCE1_ADDON5 0x90
#define MACR_CODE_TYPE_TRIOPTIC_CODE39 0x15
#define MACR_CODE_TYPE_BOOKLAND_EAN 0x16
#define MACR_CODE_TYPE_COUPON_CODE 0x17
#define MACR_CODE_TYPE_GS1LIMI 0x31
#define MACR_CODE_TYPE_GS1DB 0x30
#define MACR_CODE_TYPE_GS1EXPA 0x32
#define MACR_CODE_TYPE_MATR25 0x0D
#define MACR_CODE_TYPE_CODE32 0x20
#define MACR_CODE_TYPE_CHNPST 0x72

// 2D code
#define MACR_CODE_TYPE_PDF417 0x11
#define MACR_CODE_TYPE_MICPDF417 0x1A
#define MACR_CODE_TYPE_QRCODE 0x1C
#define MACR_CODE_TYPE_DATAMATRIX 0x1B
#define MACR_CODE_TYPE_MAXICODE 0x25
#define MACR_CODE_TYPE_AZTEC 0x2D
#define MACR_CODE_TYPE_MICROQR 0x2C

/*Instructions Icons*/
#define NOINSTRUCTIONS 0x00   // No instructions
#define BTCONNECT 0x01        // Show Bluetooth icon
#define TIME 0x02             // Show Time
#define BATTERYCAPACITY 0x04  // Show USB icon

/*Database Information Struct*/
typedef struct {
  char idxfile[13];
  char datfile[13];
  char idxbuf[128];
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
#define O_OPEN 1   // Only open database files flag
#define O_CREAT 2  // Only create and opens database files
#define O_TRUNC \
  4  // Only open database files and truncates it to zero length and rebuild
     // empty database files.

/*Database Store Data Flag*/
#define DB_INSERT 1   // Insert new record only
#define DB_REPLACE 2  // Replace existing record
#define DB_STORE \
  4  // Insert new record when it is not existing. Replace record when it is
     // exist.

/*Battery Information Struct*/
typedef struct _BatteryInfo {
  unsigned int MinVoltage;
  unsigned int MaxVoltage;
  unsigned int CurVoltage;
  unsigned int Percent;
} BATTERY_INFO;

/*Week Day Macro Definition*/
#define SUNDAY 0x00     // Sunday
#define MONDAY 0x01     // Monday
#define TUESDAY 0x02    // Tuesday
#define WEDNESDAY 0x03  // Wednesday
#define THURSDAY 0x04   // Thursday
#define FRIDAY 0x05     // Friday
#define SATURDAY 0x06   // Saturday

/*Time Information Structure*/
typedef struct Time_s /* Time Structure definition */
{
  unsigned char Sec;
  unsigned char Min;
  unsigned char Hour;
} Time;

/*Day Information Structure*/
typedef struct Date_s /* Date Structure definition */
{
  unsigned char Month;
  unsigned char Day;
  unsigned int Year;
} Date;

/*Memory Information Struct*/
typedef struct _MemoryInfo {
  unsigned int TotalMemory;
  unsigned int UseMemory;
  unsigned int FreeMemory;
} MEMORY_INFO;

/*Wi-Fi hot spot */
#define HOTSPOTNAMEMAXLEN 30
typedef struct _WIFIHotSpotInfo {
  char Hot_Spot_Name[HOTSPOTNAMEMAXLEN];
  char EncryptionFlg;
} Hot_Spot_INFO;

/*Wi-Fi Host information*/
typedef struct _HostInfo {
  unsigned char Host_Addr[40];
  unsigned char Host_Port[5];
  unsigned char LinkUp_Flag;
  unsigned char Port_Flag;
} HOST_INFO;

/*Bluetooth device information*/
typedef struct _ConnectDeviceInfo {
  unsigned char MAC[13];
  unsigned char Name[20];
  unsigned char Type;
} BLUETOOTH_DEVICE_INFO;

/*List the functions*/

//******************************** The security design and save parameter
//*****************************//
unsigned char mSystem_CheckVerificationCode(const char VCStr[]);
unsigned char mSystem_SetVerificationCode(const char VCStr[]);
unsigned char mSystem_SetInstallationKey(const char IKStr[]);
int mSystem_SaveParameter(unsigned char SequenceNum, int Para);
int mSystem_ClearParameter(unsigned char SequenceNum);
int mSystem_GetParameter(unsigned char SequenceNum);

//******************************** GUI management
//*****************************//
void mGUI_BacklightOn(void);
void mGUI_BacklightOff(void);
void mGUI_Clear(void);
void mGUI_DisplayImage(unsigned char x, unsigned char y,
                       const unsigned char *ImagePt, unsigned char ImageXSize,
                       unsigned char ImageYSize, unsigned char Versa);
void mGUI_Printf(unsigned char x, unsigned char y, const char *StrPt,
                 char FontSize);
void mGUI_InversePixel(unsigned char x, unsigned char y);
void mGUI_InverseRegionPixels(unsigned char x, unsigned char y,
                              unsigned char RegionXSize,
                              unsigned char RegionYSize);
void mGUI_BackupDisplayBuffer(void);
void mGUI_ReloadDisplayBuffer(void);
void mGUI_SetPrintfLocale(unsigned char locale);
void mGUI_SetInstructionsIcon(unsigned char IconFlg);
unsigned short mGUI_LinePrintf(unsigned char x, unsigned char y,
                               const char *StrPt, unsigned char LineNum,
                               char FontSize);
void mGUI_SetAutoRefreshScreen(unsigned char SetFlg);

//******************************** KEY management
//*****************************//
unsigned char mKey_ScanKeyboard(void);
unsigned char mKey_GetKeyValue(void);
unsigned char mKey_GetLeftKeyStatus(void);
unsigned char mKey_GetRightKeyStatus(void);
unsigned char mKey_GetUpKeyStatus(void);
unsigned char mKey_GetDownKeyStatus(void);
unsigned char mKey_GetLeftSoftKeyStatus(void);
unsigned char mKey_GetRightSoftKeyStatus(void);
unsigned char mKey_GetTirgKeyStatus(void);
unsigned char mKey_GetReturnKeyStatus(void);
void mKey_ClearKeyBuffer(void);
unsigned char mKey_GetBTWiFiKeyStatus(void);
void mKey_SetWirelessPowerKey(unsigned char SetFlg);

//******************************** LED management
//*****************************//
void mLED_GreenLedOn(void);
void mLED_GreenLedOff(void);

//******************************** Beeper and vibrate management
//*****************************//
void mBeeper_StartBeeper(unsigned int nDuration);
void mBeeper_SetBeeperFreq(unsigned short Period_No_Of_CCLK,
                           unsigned char duty);
void mVibrator_StartVibr(unsigned int nDuration);

//******************************** Time management
//*****************************//
void mRTC_GetTime(unsigned char *p_hour, unsigned char *p_min,
                  unsigned char *p_sec);
void mRTC_GetDate(unsigned short *p_year, unsigned char *p_month,
                  unsigned char *p_day);
unsigned char mRTC_SetDate(unsigned short year, unsigned char month,
                           unsigned char day);
unsigned char mRTC_SetTime(unsigned char hour, unsigned char min,
                           unsigned char sec);
unsigned char mRTC_WeekDay(void);

//******************************** Power information
//*****************************//
void mBattery_GetBatteryInfo(BATTERY_INFO *Pbi);
unsigned char mBattery_GetBatteryLifePercent(void);

//******************************** USB management
//*****************************//
void mUSB_KeyboardInit(void);
void mUSB_VirtualComInit(void);
void mUSB_UdiskInit(void);
unsigned char mUSB_GetUSBConnectStatus(void);
unsigned char mUSB_HIDSendData(const void *DataBuf, unsigned short DataSize);
unsigned char mUSB_VCOMSendData(const void *DataBuf, unsigned short DataSize);
unsigned int mUSB_VCOMReceiveData(void *RxBuffer, unsigned short Size,
                                  unsigned short Timeout);

//******************************** Bluetooth information
//*****************************//
unsigned char mBT_GetBluetoothProtocol(void);
unsigned char mBT_SetBluetoothProtocol(unsigned char BpPro);
unsigned char mBT_LPMOption(unsigned char ArStu);
unsigned char mBT_SendPacket(unsigned char *DataBuf, unsigned short DataSize);
unsigned char mBT_BluetoothDefaultSetting(void);
unsigned char mBT_GetConnectStatus(void);
unsigned char mBT_SetBluetoothName(const char *BTname);
unsigned char mBT_QueryBluetoothName(unsigned char *BTname);
void mBT_PowerOn(void);
void mBT_PowerOff(void);
void mBT_Disconnect(void);
unsigned char mBT_HIDConnect(unsigned char *BTAddress);
unsigned char mBT_SPPConnect(unsigned char *BTAddress);
unsigned char mBT_LECConnect(unsigned char *BTAddress, unsigned char BT_Type,
                             unsigned char *Service_UUID,
                             unsigned char *Write_UUID,
                             unsigned char *Notify_UUID);
unsigned char mBT_BroadcastADVData(unsigned char *DataBuf,
                                   unsigned char DataSize);
unsigned char mBT_BroadcastRSPData(unsigned char *DataBuf,
                                   unsigned char DataSize);
unsigned char mBT_ReceiveData(unsigned char *DataBuf, unsigned char MaxLen,
                              unsigned short mSec);
unsigned char mBT_SetBroadcast(unsigned char Status);
unsigned char mBT_GetBroadcastStatus(unsigned char *p_Status);
unsigned char mBT_SearchDevice(unsigned char DeviceType,
                               unsigned char SearchTime);
void mBT_GetDevice(unsigned char count, BLUETOOTH_DEVICE_INFO *DeviceInfo);
void mBT_Reconnect(unsigned char Select);
unsigned int mBT_SPPReceiveCradlePacket(void *RxBuffer, unsigned short Size,
                                        unsigned short Timeout);
unsigned char mBT_SetCradleProtocol(unsigned char CrablePro);
unsigned char mBT_SetCradleKeyboardLayout(unsigned char KblVal);
unsigned char mBT_SetCradleHIDTransmissionRate(unsigned char HIDTRLevel);
unsigned char mBT_SetCradleKeyboardDivision(unsigned char KbDin);
unsigned char mBT_GetRecentConnectedDeviceMac(unsigned char *BTAddress);
unsigned char mBT_GetReceiveDataType(void);
void mBT_SetBarcodeDelayTime(unsigned char Nms);
void mBT_HIDOSKey(void);
unsigned char mBT_GetCradleProtocol(void);
unsigned char mBT_GetCradleKeyboardLayout(void);
unsigned char mBT_GetCradleHIDTransmissionRate(void);
unsigned char mBT_GetCradleKeyboardDivision(void);

//******************************** Wifi management
//*****************************//
unsigned char mWiFi_SendPacket(unsigned char *DataBuf,
                               unsigned short DataLength);
unsigned int mWiFi_ReceivePacket(unsigned char *RxBuffer, unsigned short Size,
                                 unsigned short Timeout);
unsigned char mWiFi_GetConnectStatus(unsigned char *SSID);
unsigned char mWiFi_Disconnect(void);
void mWiFi_PowerOn(void);
void mWiFi_PowerOff(void);
unsigned char mWiFi_PowerModeSetting(unsigned char powerMode);
unsigned char mWiFi_StationModeSearchHotSpot(void);
unsigned char mWiFi_StationModeGetHotSpotInfo(unsigned char *Hot_Spot_Name,
                                              unsigned char *Psk,
                                              unsigned char Number_HS);
unsigned char mWiFi_StationModeWLANConnect(unsigned char *SSID,
                                           unsigned char EncryptionFlag,
                                           unsigned char *Passphrase,
                                           unsigned char DHCPFlag,
                                           unsigned char *StaticIP);
unsigned char mWiFi_StationModeHostConnect(unsigned char *HostIP,
                                           unsigned char *HostPort,
                                           unsigned char *LocalPort,
                                           unsigned char Flag);
unsigned char mWiFi_APModeSSIDandPassphraseSetting(unsigned char *SSID,
                                                   unsigned char security,
                                                   unsigned char *PSK,
                                                   unsigned char *localport);
unsigned char mWiFi_StationModeGetHostConnectStatus(unsigned char *IP);
unsigned char mWiFi_StationModeHostDisconnect(unsigned char Number_HS);
unsigned char mWiFi_StationModeAutoConnect(void);
unsigned char mWiFi_StationModeGetHotSpotListNum(void);
unsigned char mWiFi_StationModeAddHostIP(unsigned char *IP);
unsigned char mWiFi_StationModeSetHostPort(unsigned char *host_port,
                                           unsigned char Number_HS);
unsigned char mWiFi_StationModeSetLocalPort(unsigned char *local_port);
void mWiFi_StationModeGetLocalPort(unsigned char *local_port);
unsigned char mWiFi_StationModeGetHostPort(unsigned char *host_port,
                                           unsigned char Number_HS);
unsigned char mWiFi_StationModeSetCurrentIP(unsigned char Number_HS);
unsigned char mWiFi_StationModeGetHostListNum();
unsigned char mWiFi_StationModeGetHostInfo(HOST_INFO *host_info,
                                           unsigned char Number_HS);
unsigned char mWiFi_StationModeDeleteHostIP(unsigned char Number_HS);
unsigned char mWiFi_StationModeGetCurrentConnectHostNum(void);
void mWiFi_StationModeGetPassphrase(unsigned char *psk);

//******************************** File system *****************************//
unsigned char mFAT32_SystemInit(void);
unsigned char mFAT32_NewFile(const char *FileName);
int mFAT32_FileRead(const char *FileName, unsigned int offset, void *Pbuffer,
                    unsigned short length);
int mFAT32_FileWrite(const char *FileName, unsigned int offset, void *Pbuffer,
                     unsigned short length);
unsigned char mFAT32_FileDelete(const char *FileName);
unsigned char mFAT32_FileClear(const char *FileName);
unsigned char mFAT32_DiskFormat(void);
unsigned char mFAT32_GetTargetFile(const char *FileName);
unsigned char mFAT32_FileSuperaddition(const char *FileName,
                                       const void *Pbuffer,
                                       unsigned short length);
void mFAT32_CloseSystem();
int mFAT32_GetFileSize(const char *FileName);
unsigned char mFAT32_SetFileAttribute(const char *FileName,
                                      unsigned char DeAttribute);
unsigned char mFAT32_GetDirectoryList(const char *FileName,
                                      unsigned short FileIndex);
unsigned char mFAT32_StoreDataInUdisk(const void *DataBuf,
                                      unsigned short DataSize);
char mFAT32_SetTargetFileInUdisk(const char *FileName);

//******************************** Database management
//*****************************//
unsigned char mDB_Open(const char *DB_Name, DB *PDBStruct, unsigned char OFlag);
unsigned char mDB_FetchData(DB *PDBStruct, void *Databuffer, const char *Key);
unsigned char mDB_StoreData(DB *PDBStruct, void *DataBuffer,
                            unsigned char DataLength, const char *Key,
                            int Flag);

//******************************** Scan engine operation
//*****************************//
void mScan_OpenScanner(void);
void mScan_CloseScanner(void);
void mScan_ScanMode(unsigned char SmType);
void mScan_Operation(void);
unsigned char mScan_GetDecodeStatus(void);
unsigned short mScan_GetBarcode(unsigned char *BarcodeStr,
                                unsigned short MaxLen);
unsigned short mScan_GetFormatBarcode(unsigned char *BarcodeStr,
                                      unsigned short MaxLen);
void mBarcodeForm_AddTimeDate(unsigned char select);
unsigned int mScan_GetQuantity(void);
void mScan_AddQuantity(unsigned char num);
void mScan_ClearQuantity(void);
unsigned char mScan_GetBarcodeType();
unsigned short mScan_GetBarcodeLen(void);

//******************************** Data batch *****************************//
unsigned char mDataBatch_StoreData(const void *Databuf,
                                   unsigned short DataSize);
void mDataBatch_SetInterface(unsigned char TcType);
unsigned char mDataBatch_GetBufferstatus(void);
unsigned char mDataBatch_TransmitData(void);
unsigned char mDataBatch_SearchData(unsigned short DataLen,
                                    unsigned char *Data);
unsigned char mDataBatch_ExportDatatoTXTFile(const char *FileName);
void mDataBatch_SetBarcodeDelayTime(unsigned char Nms);
void mDataBatch_Erase_Data(void);

//******************************** SDK batch *****************************//
void mSDKBatch_Erase_Data(void);
unsigned char mSDKBatch_StoreData(unsigned char *AddData,
                                  unsigned short AddSize);
unsigned char mSDKBatch_GetData(unsigned int Offset, unsigned char *GetData,
                                unsigned short GetSize);
unsigned char mSDKBatch_ExportToFile(const char *FileName);

//******************************** System setting - General
//*****************************//
void mSysSet_USBKeyboardLayout(unsigned char KblVal);
void mSysSet_Language(unsigned char LVal);
void mSysSet_Volume(unsigned char Level);
void mSysSet_KeyBeep(unsigned char Statue);
void mSysSet_Vibrator(unsigned char VibStu);
void mSysSet_BacklightTimeout(unsigned char Btval);
void mSysSet_Brightness(unsigned char BLevel);
void mSysSet_SleepTimeout(unsigned char Stval);
void mSysSet_LoadDefaultSettingForScanner(void);
void mSysSet_SeparatorSetting(unsigned char *SepStr, unsigned char Length);
void mSysSet_BTKeyboardLayout(unsigned char KblVal);

//******************************** System information
//*****************************//
void mSysInfo_GetMemoryVolume(MEMORY_INFO *Pmi);
void mSysInfo_EraseMemory(void);
unsigned char mSysInfo_GetLanguage(void);
unsigned char mSysInfo_GetKeyboardLayout(void);
unsigned char mSysInfo_GetVolumeOfBeeper(void);
unsigned char mSysInfo_GetVibratorSettingStatus(void);
unsigned char mSysInfo_GetBacklightTimeout(void);
unsigned char mSysInfo_GetSleepTimeout(void);
void mSysInfo_GetScannerVersion(unsigned char *Psv);
void mSysInfo_GetScanEngineVersion(unsigned char *Psev);
void mSysInfo_GetScannerSerialNumber(unsigned char *pSSN);
void mSysInfo_GetBluetoothVersion(unsigned char *Pblv);
void mSysInfo_GetBluetoothName(unsigned char *Name);
void mSysInfo_GetBluetoothAddr(unsigned char *Addr);
unsigned char mSysInfo_GetBrightness(void);
unsigned char mSysInfo_GetDataTransferMode(void);

//******************************** Power ON/OFF Screens
//*****************************//
void mReg_StartupShowFunc(Registry_t Func);
void mReg_PowerOffShowFunc(Registry_t Func);

#endif
