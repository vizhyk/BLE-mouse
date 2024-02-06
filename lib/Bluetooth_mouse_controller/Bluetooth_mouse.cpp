#include "Bluetooth_mouse.hpp"

static const char *LOG_TAG = "BLEDevice";

Battery_checker battery_check;
Set_values set_values;

static const uint8_t HIDDescriptor[] = {
    USAGE_PAGE(1), 0x01,
    USAGE(1), 0x02,
    COLLECTION(1), 0x01,
    USAGE(1), 0x01,
    COLLECTION(1), 0x00,
    USAGE_PAGE(1), 0x09,
    USAGE_MINIMUM(1), 0x01,
    USAGE_MAXIMUM(1), 0x05,
    LOGICAL_MINIMUM(1), 0x00,
    LOGICAL_MAXIMUM(1), 0x01,
    REPORT_SIZE(1), 0x01,
    REPORT_COUNT(1), 0x05,
    HIDINPUT(1), 0x02,
    REPORT_SIZE(1), 0x03,
    REPORT_COUNT(1), 0x01,
    HIDINPUT(1), 0x03,
    USAGE_PAGE(1), 0x01,
    USAGE(1), 0x30,
    USAGE(1), 0x31,
    USAGE(1), 0x38,
    LOGICAL_MINIMUM(1), 0x81,
    LOGICAL_MAXIMUM(1), 0x7f,
    REPORT_SIZE(1), 0x08,
    REPORT_COUNT(1), 0x03,
    HIDINPUT(1), 0x06,
    USAGE_PAGE(1), 0x0c,
    USAGE(2), 0x38, 0x02,
    LOGICAL_MINIMUM(1), 0x81,
    LOGICAL_MAXIMUM(1), 0x7f,
    REPORT_SIZE(1), 0x08,
    REPORT_COUNT(1), 0x01,
    HIDINPUT(1), 0x06,
    END_COLLECTION(0),
    END_COLLECTION(0)};

Bluetooth_mouse::Bluetooth_mouse(std::string deviceName, std::string deviceManufacturer, uint8_t batteryLevel) : mouse_buttons{0},
                                                                                                                 hid{0}
{
  this->device_name = deviceName;
  this->battery_level = batteryLevel;
  this->deviceManufacturer = deviceManufacturer;
  this->connection_status = new Bluetooth_connection();
  this->onWrite = new Bluetooth_onWrite();
  this->iclickWrite = new Bluetooth_iclickWrite();
}

void Bluetooth_mouse::begin(void)
{
  xTaskCreate(this->taskServer, "server", 20000, (void *)this, 5, NULL);
}

void Bluetooth_mouse::click(uint8_t button)
{
  mouse_buttons = button;
  move(0, 0, 0, 0);
  mouse_buttons = 0;
  move(0, 0, 0, 0);
}

void Bluetooth_mouse::move(signed char coordinate_X, signed char coordinate_Y, signed char mouse_wheel, signed char hWheel)
{
  if (this->isConnected())
  {
    uint8_t data[5];
    data[0] = mouse_buttons;
    data[1] = coordinate_X;
    data[2] = coordinate_Y;
    data[3] = mouse_wheel;
    data[4] = hWheel;
    this->mouse->setValue(data, 5);
    this->mouse->notify();
  }
}

void Bluetooth_mouse::buttons(uint8_t button)
{
  if (button != mouse_buttons)
  {
    mouse_buttons = button;
    move(0, 0, 0, 0);
  }
}

void Bluetooth_mouse::press(uint8_t button)
{
  buttons(mouse_buttons | button);
}

void Bluetooth_mouse::release(uint8_t button)
{
  buttons(mouse_buttons & ~button);
}

bool Bluetooth_mouse::isPressed(uint8_t button)
{
  if ((button & mouse_buttons) > 0)
    return true;
  return false;
}

bool Bluetooth_mouse::isConnected(void)
{
  return this->connection_status->is_connected;
}

void Bluetooth_mouse::setBatteryLevel(uint8_t level)
{
  this->battery_level = level;
  if (hid != 0)
    this->hid->setBatteryLevel(this->battery_level);
}

void Bluetooth_mouse::taskServer(void *pvParameter)
{
  std::string default_values = set_values.setDefaultvalues();
  Bluetooth_mouse *instance = (Bluetooth_mouse *)pvParameter;
  BLEDevice::init(instance->device_name);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(instance->connection_status);

  instance->hid = new BLEHIDDevice(pServer);

  instance->pChar = instance->hid->getwritedataCharacteristic();
  instance->pChar->setCallbacks(instance->onWrite);

  instance->pChar = instance->hid->getwriteiclickdataCharacteristic();
  instance->pChar->setCallbacks(instance->iclickWrite);

  instance->hid->m_customdefaultvaluesCharacteristic->setValue(default_values);

  instance->mouse = instance->hid->inputReport(0);
  instance->connection_status->mouse = instance->mouse;

  instance->hid->manufacturer()->setValue(instance->deviceManufacturer);

  instance->hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
  instance->hid->hidInfo(0x00, 0x02);

  BLESecurity *pSecurity = new BLESecurity();

  pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);

  instance->hid->reportMap((uint8_t *)HIDDescriptor, sizeof(HIDDescriptor));

  instance->hid->startServices();

  instance->onStarted(pServer);

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->setAppearance(HID_MOUSE);

  pAdvertising->addServiceUUID(instance->hid->hidService()->getUUID());
  //pAdvertising->setScanResponse(true);
  //pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  //pAdvertising->setMinPreferred(0x12);

  pAdvertising->start();
  instance->hid->setBatteryLevel(instance->battery_level);
  instance->hid->setnotifyCharacteristic();

  ESP_LOGD(LOG_TAG, "Advertising started!");
  vTaskDelay(portMAX_DELAY);
}

void Bluetooth_mouse::setNotifications()
{
  std::string payload = "";
  float charge = battery_check.charging_value(); 
  bool charging_status = battery_check.charging_status(charge);
  int battery_charge = battery_check.battery_check();

  payload += "s_0:"; // Battery_level
  payload += std::to_string(battery_charge);
  payload += ",";
  payload += "s_1:";
  payload += std::to_string(charging_status);


  this->hid->m_customnotifyCharacteristic->setValue(payload);
  this->hid->m_customnotifyCharacteristic->notify();
}

void Bluetooth_mouse::setCurrentvalues()
{
    std::string payload = "";
    payload += "s_0:"; //Current mode
    payload += std::to_string(alternative_mode);
    payload += ",";
    payload += "s_1:"; // Invertation
    payload += std::to_string(is_inverted);
    payload += ",";
    payload += "s_2:"; //Clear mode senibility
    payload += std::to_string(mouse_sensibility); 
    payload += ",";
    payload += "s_3:"; //Sensetive mode senibility
    payload += std::to_string(alternative_mode_sensibility);
    payload += ",";

    payload += "s_4:"; //clear mode scrolling move
    payload += std::to_string(static_cast<int>(clear_scrolling)); 
    payload += ",";
    payload += "s_5:"; //clear mode right click move
    payload += std::to_string(static_cast<int>(clear_right_click)); 
    payload += ",";
    payload += "s_6:"; //clear mode left click move
    payload += std::to_string(static_cast<int>(clear_left_click)); 
    payload += ",";

    payload += "s_7:"; //clear mode up move limit 
    payload += std::to_string(default_head_up);
    payload += ",";
    payload += "s_8:"; //clear mode down move limit 
    payload += std::to_string(default_head_down);
    payload += ",";
    payload += "s_9:"; //clear mode left move limit 
    payload += std::to_string(default_head_left);
    payload += ",";
    payload += "s_10:"; //clear mode right move limit 
    payload += std::to_string(default_head_right);
    payload += ",";

    payload += "s_11:"; //sensetive mode right click move 
    payload += std::to_string(static_cast<int>(sensetive_right_click));
    payload += ",";
    payload += "s_12:"; //sensetive mode left click move
    payload += std::to_string(static_cast<int>(sensetive_left_click));
    payload += ",";
    payload += "s_13:"; //sensetive mode scrolling move
    payload += std::to_string(static_cast<int>(sensetive_scrolling));
    payload += ",";

    payload += "s_14:";  //auto click mode on/off
    payload += std::to_string(enable_click);
    payload += ",";
    payload += "s_15:";  //auto click mode time between clicks in seconds 
    payload += std::to_string(left_click_time);
    payload += ",";

    payload += "s_16:";      //iclick mode on/off
    payload += std::to_string(i_click_mode);
    payload += ",";
    payload += "s_17:"; // left eye blink detection
    payload += std::to_string(i_click_left);
    payload += ",";
    payload += "s_18:"; // left eye blink detection
    payload += std::to_string(i_click_right);
    payload += ",";

    payload += "s_19:"; // Is double eyes click enabled
    payload += std::to_string(isDoubleEyesClick);
    payload += ",";
    payload += "s_20:"; // Double eyes click left button action
    payload += std::to_string(eyesDoubleClickLeftButtonControl);
    payload += ",";
    payload += "s_21:"; // Double eyes click right button action
    payload += std::to_string(eyesDoubleClickRightButtonControl);
    /*payload += ",";
    payload += "version:"; // current firmware version
    payload += std::to_string(100);*/
    
    this->hid->m_customcurrentvaluesCharacteristic->setValue(payload);
}