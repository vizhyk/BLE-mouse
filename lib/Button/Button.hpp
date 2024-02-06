#include <Bounce2.h>
#include "BLE_logic.hpp"

class Button: public BLE_logic {
private:
int PIN_BUTTON;
public:
Button();
void init_button();
void press_button();

};