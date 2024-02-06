#include "Button.hpp"

Bounce debouncer = Bounce();

Button::Button() : PIN_BUTTON{5}
{

}

void Button::init_button(){
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    debouncer.attach(PIN_BUTTON);
    debouncer.interval(5);
    Serial.println("[INFO]: button initialized");   
}

void Button::press_button(){
    int value = debouncer.read();
    debouncer.update();
    if ( value == LOW ) {
    Serial.println("[INFO]: button pressed to restart");   
    ESP.restart();
    }
}