/*
 * BLEHIDDevice.h
 *
 *  Created on: Jan 03, 2018
 *      Author: chegewara
 */

#ifndef _BLEHIDDEVICE_H_
#define _BLEHIDDEVICE_H_

#include "sdkconfig.h"
#if defined(CONFIG_BLUEDROID_ENABLED)

#include "BLECharacteristic.h"
#include "BLEService.h"
#include "BLEDescriptor.h"
#include "BLE2902.h"
#include "HIDTypes.h"
#include "Global_variables.hpp"
#include "Battery_checker.hpp"

#define GENERIC_HID		0x03C0
#define HID_KEYBOARD	   0x03C1
#define HID_MOUSE		  0x03C2
#define HID_JOYSTICK	   0x03C3
#define HID_GAMEPAD		0x03C4
#define HID_TABLET		 0x03C5
#define HID_CARD_READER	0x03C6
#define HID_DIGITAL_PEN	0x03C7
#define HID_BARCODE		0x03C8
#define HID_BRAILLE_DISPLAY		0x03C9

class BLEHIDDevice {
public:
	BLEHIDDevice(BLEServer*);
	BLEHIDDevice();
	virtual ~BLEHIDDevice();

	void reportMap(uint8_t* map, uint16_t);
	void startServices();

	BLEService* deviceInfo();
	BLEService* hidService();
	BLEService* batteryService();

	BLECharacteristic* 	manufacturer();
	void 	manufacturer(std::string name);
	//BLECharacteristic* 	pnp();
	void	pnp(uint8_t sig, uint16_t vid, uint16_t pid, uint16_t version);
	//BLECharacteristic*	hidInfo();
	void	hidInfo(uint8_t country, uint8_t flags);
	//BLECharacteristic* 	batteryLevel();
	void 	setBatteryLevel(uint8_t level);
	//Custom Characteristics setters
	void 	setnotifyCharacteristic();

	BLECharacteristic* getwritedataCharacteristic();
	BLECharacteristic* getwriteiclickdataCharacteristic();
	BLECharacteristic* getdefaultvaluesCharacteristic();

	BLECharacteristic*  m_customnotifyCharacteristic;      //0x2FFF
	BLECharacteristic*  m_customdefaultvaluesCharacteristic;      //0x2FFA
	BLECharacteristic*  m_customcurrentvaluesCharacteristic;      //0x2FFB
	BLECharacteristic*  m_customwritedataCharacteristic;      //0x2FFC
    BLECharacteristic*  m_customwriteiclickdataCharacteristic;      //0x2FFD

	BLECharacteristic* 	reportMap();
	BLECharacteristic* 	hidControl();
	BLECharacteristic* 	inputReport(uint8_t reportID);
	BLECharacteristic* 	outputReport(uint8_t reportID);
	BLECharacteristic* 	featureReport(uint8_t reportID);
	BLECharacteristic* 	protocolMode();
	BLECharacteristic* 	bootInput();
	BLECharacteristic* 	bootOutput();



private:
	BLEService*			m_deviceInfoService;			//0x180a
	BLEService*			m_hidService;					//0x1812
	BLEService*			m_batteryService = 0;			//0x180f
	BLEService*         m_customdataService;            //0x3000
	BLEService*			m_customwriteService;            //0x3001

	BLECharacteristic* 	m_manufacturerCharacteristic;	//0x2a29
	BLECharacteristic* 	m_pnpCharacteristic;			//0x2a50
	BLECharacteristic* 	m_hidInfoCharacteristic;		//0x2a4a
	BLECharacteristic* 	m_reportMapCharacteristic;		//0x2a4b
	BLECharacteristic* 	m_hidControlCharacteristic;		//0x2a4c
	BLECharacteristic* 	m_protocolModeCharacteristic;	//0x2a4e
	BLECharacteristic*	m_batteryLevelCharacteristic;	//0x2a19

};

#endif // CONFIG_BLUEDROID_ENABLED
#endif /* _BLEHIDDEVICE_H_ */
