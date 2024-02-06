#include "BLE_logic.hpp"

int mouse_sensibility = 3;
int alternative_mode_sensibility = 6;

bool alternative_mode = true;
bool is_inverted = false;
bool scrolling_enabled = false;

int16_t default_head_up = -3500;
int16_t default_head_down = 3000;
int16_t default_head_left = -1000;
int16_t default_head_right = 6000;

int16_t default_head_left_click = 6000;
int16_t default_head_right_click = -10000;
int16_t default_head_sensibility = -30000;
int16_t default_head_scrolling_mode = 25000;

int16_t default_head_scrolling_up = -6500;
int16_t default_head_scrolling_down = 6500;
int16_t default_head_scrolling_left = -7000;
int16_t default_head_scrolling_right = 7000;

int16_t sensetive_head_left_click = -1500;
int16_t sensetive_head_right_click = 10000;
int16_t sensetive_head_scrolling_mode = -17000;

int redefined_up = MOUSE_MOVE_UP;
int redefined_down = MOUSE_MOVE_DOWN;
int redefined_left = MOUSE_MOVE_LEFT;
int redefined_right = MOUSE_MOVE_RIGHT;

int redefined_left_click = MOUSE_LEFT_CLICK;
int redefined_right_click = MOUSE_RIGHT_CLICK;
int redefined_sensibility = CHANGE_SENSIBILITY;
int redefined_scrolling_mode = ENABLE_SCROLLING_MODE;

Redefined_action clear_scrolling = Redefined_action::TURN_RIGHT;
Redefined_action clear_change_sensibility = Redefined_action::TURN_LEFT; //this niu
Redefined_action clear_left_click = Redefined_action::DOWN;
Redefined_action clear_right_click = Redefined_action::UP;

Redefined_action disabled = Redefined_action::DISABLED_ACTION;

Redefined_action sensetive_right_click = Redefined_action::TURN_RIGHT;
Redefined_action sensetive_left_click = Redefined_action::TURN_LEFT ; 
Redefined_action sensetive_down = Redefined_action::DOWN; //this niu
Redefined_action sensetive_scrolling = Redefined_action::UP;

int left_click_time = 3;

bool i_click_mode = false;
int i_click_left = 4; 
int i_click_right = 5;

bool isDoubleEyesClick = false;
int eyesDoubleClickLeftButtonControl = 7;
int eyesDoubleClickRightButtonControl = 6;

Battery_checker battery_checker;
Bluetooth_mouse bluetooth_mouse("mouse ble", "me", battery_checker.battery_check());

void BLE_logic::ble_mouse_init(void)
{
  Serial.begin(115200);
  Serial.println("[INFO]: Starting BLE work! ");
  bluetooth_mouse.begin();
  delay(1000);
}

bool BLE_logic::deviceConnected()
{
  return bluetooth_mouse.isConnected();
}

void BLE_logic::l_click_action()
{
  bluetooth_mouse.click(MOUSE_LEFT);
    Serial.println("[INFO]: auto click happened");
}

bool BLE_logic::mouse_up(int16_t aX, int16_t aZ, int mouse_sensibility, bool is_inverted, bool scrolling_enabled, int redefined_side)
{

  switch (redefined_side)
  {
  case MOUSE_MOVE_UP:
  if (aX <= default_head_up)
  {
    if (!is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, mouse_sensibility);
      return true;
    }
    if (is_inverted && !scrolling_enabled) 
    {
      bluetooth_mouse.move(0, -mouse_sensibility);
      return true;
    }
    if (scrolling_enabled)
    {
      bluetooth_mouse.move(0, 0, -1);
      return true;
      //delay(20);
    }
    return false;
  }
    break;
  case MOUSE_MOVE_DOWN:
  if (aX >= default_head_down)
  {
    mouse_down(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_DOWN);
    return true;
  }
    break;
  
  case MOUSE_MOVE_LEFT:
  if (aZ <= default_head_left)
  {
    mouse_left(aX, aZ,mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_LEFT);
    return true;
  }
    break;
  case MOUSE_MOVE_RIGHT:
  if (aZ >= default_head_right) 
  {
    mouse_right(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_RIGHT);
    return true;
  }
    break;
  case DISABLED_SIDE:
    break;

  default:
  Serial.println("[WARNING]:[CLEAR MODE]: Mouse up suspicious behaviour");
  if (aX <= default_head_up)
  {
    if (!is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, mouse_sensibility);
      return true;
    }
    if (is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, -mouse_sensibility);
      return true;
    }
    if (scrolling_enabled)
    {
      bluetooth_mouse.move(0, 0, -1);
      return true;
      //delay(20);
    }
    return false;
  }
    break;
  }
  return false;
}

bool BLE_logic::mouse_down(int16_t aX, int16_t aZ, int mouse_sensibility, bool is_inverted, bool scrolling_enabled, int redefined_side)
{
  switch (redefined_side)
  {

  case MOUSE_MOVE_DOWN:
  if (aX >= default_head_down)
  {
    if (!is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, -mouse_sensibility);
      return true;
    }
    if (is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, mouse_sensibility);
      return true;
    }
    if (scrolling_enabled)
    {
      bluetooth_mouse.move(0, 0, 1);
      return true;
      //delay(20);
    }
    return false;
  }
    break;
  case MOUSE_MOVE_UP:
  if (aX <= default_head_up)
  {
    mouse_up(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_UP);
    return true;
  }
    break;
  case MOUSE_MOVE_LEFT:
  if (aZ <= default_head_left)
  {
    mouse_left(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_LEFT);
    return true;
  }
    break;
  case MOUSE_MOVE_RIGHT:
  if (aZ >= default_head_right) 
  {
    mouse_right(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_RIGHT);
    return true;
  }
    break;
  case DISABLED_SIDE:
    break;
  default:
  Serial.println("[WARNING]:[CLEAR MODE]: Mouse down suspicious behaviour");
  if (aX >= default_head_down)
  {
    if (!is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, -mouse_sensibility);
      return true;
    }
    if (is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, mouse_sensibility);
      return true;
    }
    if (scrolling_enabled)
    {
      bluetooth_mouse.move(0, 0, mouse_sensibility);
      return true;
      delay(20);
    }
    return false;
  }
    break;
  }
  return false;
}

bool BLE_logic::mouse_left(int16_t aX, int16_t aZ, int mouse_sensibility, bool is_inverted, bool scrolling_enabled, int redefined_side)
{
  switch (redefined_side)
  {
  case MOUSE_MOVE_LEFT:
  if (aZ <= default_head_left)
  {
    if (!is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(-mouse_sensibility, 0);
      return true;
    }
    if (is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(mouse_sensibility, 0);
      return true;
    }
    if (scrolling_enabled)
    {
      bluetooth_mouse.move(0, 0, 0, -1);
      return true;
      //delay(20);
    }
    return false;
  }
    break;
  case MOUSE_MOVE_UP:
  if (aX <= default_head_up)
  {
    mouse_up(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_UP);
    return true;
  }
    break;
  case MOUSE_MOVE_DOWN:
  if (aX >= default_head_down)
  {
    mouse_down(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_DOWN);
    return true;
  }
    break;
  case MOUSE_MOVE_RIGHT:
  if (aZ >= default_head_right) 
  {
    mouse_right(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_RIGHT);
    return true;
  }
    break;
  case DISABLED_SIDE:
    break;
  default:
  Serial.println("[WARNING]:[CLEAR MODE]: Mouse left suspicious behaviour");
  if (aZ <= default_head_left)
  {
    if (!is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, -mouse_sensibility);
      return true;
    }
    if (is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, mouse_sensibility);
      return true;
    }
    if (scrolling_enabled)
    {
      bluetooth_mouse.move(0, 0, -1);
      return true;
      //delay(20);
    }
    return false;
  }
    break;
  }
  return false;
}

bool BLE_logic::mouse_right(int16_t aX, int16_t aZ, int mouse_sensibility, bool is_inverted, bool scrolling_enabled, int redefined_side)
{
  switch (redefined_side)
  {
  case MOUSE_MOVE_RIGHT:
  if (aZ >= default_head_right) 
  //Serial.println(aZ);
  {
    if (!is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(mouse_sensibility, 0);
      return true;
    }
    if (is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(-mouse_sensibility, 0);
      return true;
    }
    if (scrolling_enabled)
    {
      bluetooth_mouse.move(0, 0, 0, 1);
      return true;
      //delay(20);
    }
    return false;
  }
    break;
  case MOUSE_MOVE_UP:
  if (aX <= default_head_up)
  {
    mouse_up(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_UP);
    return true;
  }
    break;
  case MOUSE_MOVE_DOWN:
  if (aX >= default_head_down)
  {
    mouse_down(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_DOWN);
    return true;
  }
    break;
  case MOUSE_MOVE_LEFT:
  if (aZ <= default_head_left)
  {
    mouse_left(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, MOUSE_MOVE_LEFT);
    return true;
  }
    break;
  case DISABLED_SIDE:
    break;
  default:
  Serial.println("[WARNING]:[CLEAR MODE]: Mouse right suspicious behaviour");
  if (aZ >= default_head_right) 
  {
    if (!is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, mouse_sensibility);
      return true;
    }
    if (is_inverted && !scrolling_enabled)
    {
      bluetooth_mouse.move(0, mouse_sensibility);
      return true;
    }
    if (scrolling_enabled)
    {
      bluetooth_mouse.move(0, 0, 0, 1);
      return true;
      //delay(20);
    }
    return false;
  }
    break;
  }
  return false;
}

void BLE_logic::mouse_left_click(int16_t GyY, int16_t GyZ, Redefined_action value)
{
  switch (value)
  {
  case Redefined_action::DOWN:
    if (GyZ >= default_head_left_click)
    {
      bluetooth_mouse.click(MOUSE_LEFT);
      Serial.println("[INFO]:[CLEAR MODE]: Mouse  left click down");
      delay(300);
    }
      
    break;
  case Redefined_action::UP:
    if (GyZ <= default_head_right_click)
    {
      bluetooth_mouse.click(MOUSE_LEFT);
      Serial.println("[INFO]:[CLEAR MODE]: Mouse left click up ");
      delay(300);
    }
    break;
  case Redefined_action::TURN_LEFT:
    if (GyY <= default_head_sensibility)
    {
      bluetooth_mouse.click(MOUSE_LEFT);
      Serial.println("[INFO]:[CLEAR MODE]: Mouse left click turn left");
      delay(300);
    }
    break;
  case Redefined_action::TURN_RIGHT:
    if (GyY >= default_head_scrolling_mode)
    {
      bluetooth_mouse.click(MOUSE_LEFT);
      Serial.println("[INFO]:[CLEAR MODE]: Mouse left click turn right");
      delay(300);
    }
  case Redefined_action::DISABLED_ACTION:
    break;
  default:
  Serial.println("[WARNING]:[CLEAR MODE]: Mouse left click suspicious behaviour");
    if (GyZ >= default_head_left_click)
    {
      bluetooth_mouse.click(MOUSE_LEFT);
      delay(300);
    }
    break;
  }
}

void BLE_logic::mouse_right_click(int16_t GyY, int16_t GyZ, Redefined_action value)
{
  switch (value)
  {
  case Redefined_action::UP:
    if (GyZ <= default_head_right_click)
    {
      bluetooth_mouse.click(MOUSE_RIGHT);
      Serial.println("[INFO]:[CLEAR MODE]: Mouse right click up");
      delay(800);
    }
    break;
  case Redefined_action::DOWN:
    if (GyZ >= default_head_left_click)
    {
      bluetooth_mouse.click(MOUSE_RIGHT);
      Serial.println("[INFO]:[CLEAR MODE]: Mouse right click down");
      delay(800);
    }
    break;
  case Redefined_action::TURN_LEFT:
    if (GyY <= default_head_sensibility)
    {
      bluetooth_mouse.click(MOUSE_RIGHT);
      Serial.println("[INFO]:[CLEAR MODE]: Mouse right click turn left");
      delay(800);
    }
    break;
  case Redefined_action::TURN_RIGHT:
    if (GyY >= default_head_scrolling_mode)
    {
      bluetooth_mouse.click(MOUSE_RIGHT);
      Serial.println("[INFO]:[CLEAR MODE]: Mouse right click turn right");
      delay(800);
    }
  case Redefined_action::DISABLED_ACTION:
    break;
  default:
  Serial.println("[WARNING]:[CLEAR MODE]: Mouse right lick suspicious behaviour");
    if (GyZ <= default_head_right_click)
    {
      bluetooth_mouse.click(MOUSE_RIGHT);
      delay(800);
    }
    break;
  }
}

void BLE_logic::sensetive_left_click_action(int16_t aZ, int16_t GyZ, Redefined_action value)
{
  switch (value)
  {
    case Redefined_action::TURN_RIGHT:
    if (aZ >= sensetive_head_right_click)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[TURN_RIGHT]: Mouse left click happened");
      bluetooth_mouse.click(MOUSE_LEFT);
      delay(300);
    }
    break;

    case Redefined_action::TURN_LEFT:
    if (aZ <= sensetive_head_left_click)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[TURN_LEFT]: Mouse left click happened");
      bluetooth_mouse.click(MOUSE_LEFT);
      delay(300);
    }
    break;

    case Redefined_action::UP:
    if (GyZ <= sensetive_head_scrolling_mode)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[UP]: Mouse left click happened");
      bluetooth_mouse.click(MOUSE_LEFT);
      delay(300);
    }
    break;

    case Redefined_action::DOWN:
    if (GyZ >= sensetive_head_scrolling_mode)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[DOWN]: Mouse left click happened");
      bluetooth_mouse.click(MOUSE_LEFT);
      delay(300);
    }
    break;

    default:
    Serial.println("[WARNING]:[SENSETIVE MODE]: Mouse left lick suspicious behaviour");
    if (aZ >= sensetive_head_left_click)
    {
      bluetooth_mouse.click(MOUSE_LEFT);
      delay(300);
    }
    break;
  }
}

void BLE_logic::sensetive_right_click_action(int16_t aZ, int16_t GyZ, Redefined_action value)
{
  switch (value)
  {
    case Redefined_action::TURN_RIGHT:
    if (aZ >= sensetive_head_right_click)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[TURN_RIGHT]: Mouse right click happened");
      bluetooth_mouse.click(MOUSE_RIGHT);
      delay(800);
    }
    break;

    case Redefined_action::TURN_LEFT:
    if (aZ <= sensetive_head_left_click)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[TURN_LEFT]: Mouse right click happened");
      bluetooth_mouse.click(MOUSE_RIGHT);
      delay(800);
    }
    break;

    case Redefined_action::UP:
    if (GyZ <= sensetive_head_scrolling_mode)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[UP]: Mouse right click happened");
      bluetooth_mouse.click(MOUSE_RIGHT);
      delay(800);
    }
    break;

    case Redefined_action::DOWN:
    if (GyZ >= sensetive_head_scrolling_mode)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[DOWN]: Mouse right click happened");
      bluetooth_mouse.click(MOUSE_RIGHT);
      delay(800);
    }
    break;

    default:
    Serial.println("[WARNING]:[SENSETIVE MODE]: Mouse right click suspicious behaviour");
    if (aZ >= sensetive_head_left_click)
    {
      bluetooth_mouse.click(MOUSE_RIGHT);
      delay(800);
    }
    break;
  }
}

void BLE_logic::Notify()
{
  Serial.println("[INFO]: Notify was sent to application");
  bluetooth_mouse.setNotifications();
}

void BLE_logic::setCurrentvalues()
{
  bluetooth_mouse.setCurrentvalues();
  //Serial.println("Current values rewritten");
}

bool BLE_logic::getStatus()
{
  if(bluetooth_mouse.isConnected())
    return true;
    else return false;
}

bool BLE_logic::enable_scrolling_mode(int16_t GyY, int16_t GyZ, bool alternative_mode, Redefined_action value)
{
  switch (value)
  {
  case Redefined_action::TURN_RIGHT:
    if (GyY >= default_head_scrolling_mode)
    {
      scrolling_enabled = !scrolling_enabled;
      Serial.println("[INFO]:[CLEAR MODE]:[TURN RIGHT]:Scrolling mode enabled");
      delay(2000);
      return scrolling_enabled;
    }
    break;
  case Redefined_action::UP:
    if (GyZ <= default_head_right_click)
    {
      scrolling_enabled = !scrolling_enabled;
      Serial.println("[INFO]:[CLEAR MODE]:[UP]:Scrolling mode enabled");
      delay(2000);
      return scrolling_enabled; 
    }
    break;
  case Redefined_action::DOWN:
    if (GyZ >= default_head_left_click)
    {
      scrolling_enabled = !scrolling_enabled;
      Serial.println("[INFO]:[CLEAR MODE]:[DOWN]:Scrolling mode enabled");
      delay(2000);
      return scrolling_enabled;
    }
    break;
  case Redefined_action::TURN_LEFT:
    if (GyY <= default_head_sensibility)
    {
      scrolling_enabled = !scrolling_enabled;
      Serial.println("[INFO]:[CLEAR MODE]:[TURN_LEFT]:Scrolling mode enabled");
      delay(2000);
      return scrolling_enabled;
    }
    break;
  case Redefined_action::DISABLED_ACTION:
    break;

  default:
  Serial.println("[WARNING]:[CLEAR MODE]:[SCROLLING MODE]: scrolling mode suspicious behaviour");
    if (GyY >= default_head_scrolling_mode)
    {
      scrolling_enabled = !scrolling_enabled;
      Serial.println("Scrolling mode enabled");
      delay(1000);
      return scrolling_enabled;
    }
    break;
  }
  return scrolling_enabled;
}

int BLE_logic::change_sensibility(int16_t GyY, int16_t GyZ, Redefined_action value)
{
  switch (value)
  {
  case Redefined_action::TURN_LEFT:
    if (GyY <= default_head_sensibility)
    {
      if (mouse_sensibility >= 5)
      {
        mouse_sensibility = 1;
        Serial.println("sensibility returned back to default value");
        return mouse_sensibility;
      }
    
      mouse_sensibility++;
      Serial.println("sensibility increased");
      delay(2000);
      return mouse_sensibility;
    }
    break;
  case Redefined_action::UP:
    if (GyZ <= default_head_right_click)
    {
      if (mouse_sensibility >= 5)
      {
        mouse_sensibility = 1;
        Serial.println("sensibility returned back to default value");
        return mouse_sensibility;
      }
    
      mouse_sensibility++;
      Serial.println("sensibility increased");
      delay(2000);
      return mouse_sensibility;
    }
    break;
  case Redefined_action::DOWN:
    if (GyZ >= default_head_left_click)
    {
      if (mouse_sensibility >= 5)
      {
        mouse_sensibility = 1;
        Serial.println("sensibility returned back to default value");
        return mouse_sensibility;
      }
    
      mouse_sensibility++;
      Serial.println("sensibility increased");
      delay(2000);
      return mouse_sensibility;
    }

    break;
  case Redefined_action::TURN_RIGHT:
      if (GyY >= default_head_scrolling_mode)
    {
      if (mouse_sensibility >= 5)
      {
        mouse_sensibility = 1;
        Serial.println("sensibility returned back to default value");
        return mouse_sensibility;
      }
    
      mouse_sensibility++;
      Serial.println("sensibility increased");
      delay(2000);
      return mouse_sensibility;
    }
    break;
  case Redefined_action::DISABLED_ACTION:
    break;

  default:
    if (GyY <= default_head_sensibility)
    {
     if (mouse_sensibility >= 5)
      {
        mouse_sensibility = 1;
        Serial.println("sensibility returned back to default value");
        return mouse_sensibility;
      }
      mouse_sensibility++;
      Serial.println("sensibility increased");
      delay(2000);
      break;
      return mouse_sensibility;
    }
  }
  return mouse_sensibility;
}

int  BLE_logic::alternative_mode_sensibility_converter(int alternative_sensibility)
{
  int difference = alternative_sensibility - 2;
  return 8 - difference;
}

bool BLE_logic::alternative_move(int16_t GyX, int16_t GyZ, int16_t aZ, bool is_inverted)
{
  if(alternative_mode_sensibility <= 0)
  {
    alternative_mode_sensibility = 6;
  }

  int changed_sensibility = alternative_mode_sensibility_converter(alternative_mode_sensibility);
  
  // Serial.print("\nGyX: "); Serial.print(GyX);
  // Serial.print("\nGyZ: "); Serial.print(GyZ);
  // Serial.print("\naY: "); Serial.print(aY);
  int16_t temp_GyX = GyX / (changed_sensibility * 100) / 1.05 * -1;
  int16_t temp_GyZ = GyZ / (changed_sensibility * 100) / 1 * -1;
  // Serial.print("\nGyX: ");
  //Serial.print(temp_GyX);
  // Serial.print("\nGyZ: ");
  //Serial.print(temp_GyZ);
  if (is_inverted)
  {
    bluetooth_mouse.move(temp_GyX, temp_GyZ);
  }
  else
  {
    bluetooth_mouse.move(-temp_GyX, -temp_GyZ);
  }
  if(temp_GyX != 0 && temp_GyZ != 0)
  {
    //Serial.println("alternative move returned true");
    return true;
  }
  //Serial.println("alternative move returned false");
  return false;
}

void BLE_logic::alternative_scrolling(int16_t GyX, int16_t GyZ)
{
  int16_t temp_GyX = GyX / 2000 / 1 * -1;
  int16_t temp_GyZ = GyZ / 800 / 1 * -1;
  // bluetooth_mouse.move(0,0, temp_GyX, -temp_GyZ);
  //bluetooth_mouse.move(0, 0, temp_GyZ);
  //bluetooth_mouse.move(0, 0, 0, -temp_GyX);
  bluetooth_mouse.move(0, 0, -temp_GyX );
  // delay(20);
}

bool BLE_logic::sensetive_scrolling_mode(int16_t aZ, int16_t GyY, int16_t GyZ, bool alternative_mode, Redefined_action value)
{
  switch (value)
  {
  case Redefined_action::UP:

    if (GyZ <= sensetive_head_scrolling_mode)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[UP]:Scrolling mode enabled");
      scrolling_enabled = !scrolling_enabled;
      Serial.println("Scrolling mode enabled");
      delay(1000);
      return scrolling_enabled;
    }
    break;
  case Redefined_action::DOWN:
    if (GyZ >= sensetive_head_scrolling_mode)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[DOWN]:Scrolling mode enabled");
      scrolling_enabled = !scrolling_enabled;
      Serial.println("Scrolling mode enabled");
      Serial.println(GyZ);
      delay(1000);
      return scrolling_enabled;
    }
    break;

    case Redefined_action::TURN_LEFT:
    if (aZ <= sensetive_head_left_click)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[TURN_LEFT]:Scrolling mode enabled");
      scrolling_enabled = !scrolling_enabled;
      Serial.println("Scrolling mode enabled");
      delay(1000);
      return scrolling_enabled;
    }
    break;
    
    case Redefined_action::TURN_RIGHT:
    if (aZ >= sensetive_head_right_click)
    {
      Serial.println("[INFO]:[SENSETIVE MODE]:[TURN_RIGHT]:Scrolling mode enabled");
      scrolling_enabled = !scrolling_enabled;
      Serial.println("Scrolling mode enabled");
      delay(1000);
      return scrolling_enabled;
    }

    default:
      if (GyZ <= sensetive_head_scrolling_mode)
      {
        Serial.println("[WARNING]:[SENSETIVE MODE]:[SCROLLING MODE]: scrolling mode suspicious behaviour");
        scrolling_enabled = !scrolling_enabled;
        Serial.println("Scrolling mode enabled");
        delay(1000);
        return scrolling_enabled;
      }
      break;
    }
      return scrolling_enabled;
  }


bool BLE_logic::mouse_action(int16_t aX, int16_t aY, int16_t aZ, int16_t GyX, int16_t GyY, int16_t GyZ)
{
  
  if (bluetooth_mouse.isConnected())
  {

    //-----------------------------------------------------------------------------------------------------------
    if (alternative_mode)
    {

      if (scrolling_enabled)
      {

          scrolling_enabled = sensetive_scrolling_mode(aZ, GyY, GyZ, alternative_mode, sensetive_scrolling);
        
        alternative_scrolling(GyY, GyZ);
      }

      else
      {
          scrolling_enabled = sensetive_scrolling_mode(aZ, GyY, GyZ,alternative_mode, sensetive_scrolling);
        
          bool status = alternative_move(GyY, GyZ, aZ, is_inverted);

          sensetive_left_click_action(aZ, GyZ, sensetive_left_click);
          sensetive_right_click_action(aZ, GyZ, sensetive_right_click);
          return status;

      }    
        
      }
    //-----------------------------------------------------------------------------------------------------
    if (!alternative_mode)
    {

       // mouse_sensibility = change_sensibility(GyY, GyX, turn_left); 

      if (scrolling_enabled)
      {
          scrolling_enabled = enable_scrolling_mode(GyY, GyZ, alternative_mode, clear_scrolling);
          mouse_right(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, redefined_right);
          mouse_left(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, redefined_left);
          mouse_up(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, redefined_up);
          mouse_down(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, redefined_down);
      }
      //-------------------------------------------------------------------------------------------------------------------------
      else
      { 
          bool status_right, status_left, status_up, status_down;        
          scrolling_enabled = enable_scrolling_mode(GyY, GyZ,alternative_mode, clear_scrolling);
          status_right = mouse_right(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, redefined_right);
          status_left = mouse_left(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, redefined_left);
          status_up= mouse_up(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, redefined_up);
          status_down = mouse_down(aX, aZ, mouse_sensibility, is_inverted, scrolling_enabled, redefined_down);
          mouse_left_click(GyY, GyZ, clear_left_click);
          mouse_right_click(GyY, GyZ, clear_right_click);
          if(status_right || status_left || status_up || status_down)
          {
            //Serial.println("true");
            return true;
          }
          else
          {
            //Serial.println("false");
            return false;
          }
      }
    }
  }
  return true;
}
  

