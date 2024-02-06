#include "Set_values.hpp"

std::string Set_values::setDefaultvalues()
{
    std::string payload = "";
    payload += "s_0:"; //Current mode
    payload += std::to_string(false);
    payload += ",";
    payload += "s_1:"; // Invertation
    payload += std::to_string(false);
    payload += ",";
    payload += "s_2:"; //Clear mode senibility
    payload += std::to_string(3); 
    payload += ",";
    payload += "s_3:"; //Sensetive mode senibility
    payload += std::to_string(4);
    payload += ",";

    payload += "s_4:"; //clear mode scrolling move
    payload += std::to_string(0); 
    payload += ",";
    payload += "s_5:"; //clear mode right click move
    payload += std::to_string(2); 
    payload += ",";
    payload += "s_6:"; //clear mode left click move
    payload += std::to_string(3); 
    payload += ",";

    payload += "s_7:"; //clear mode up move limit 
    payload += std::to_string(-6500);
    payload += ",";
    payload += "s_8:"; //clear mode down move limit 
    payload += std::to_string(6500);
    payload += ",";
    payload += "s_9:"; //clear mode left move limit 
    payload += std::to_string(-7000);
    payload += ",";
    payload += "s_10:"; //clear mode right move limit 
    payload += std::to_string(7000);
    payload += ",";

    payload += "s_11:"; //sensetive mode right click move 
    payload += std::to_string(0);
    payload += ",";
    payload += "s_12:"; //sensetive mode left click move
    payload += std::to_string(1);
    payload += ",";
    payload += "s_13:"; //sensetive mode scrolling move
    payload += std::to_string(2);
    payload += ",";

    payload += "s_14:";  //auto click mode on/off
    payload += std::to_string(false);
    payload += ",";
    payload += "s_15:";  //auto click mode time between clicks in seconds 
    payload += std::to_string(4);
    payload += ",";

    payload += "s_16:";      //iclick mode on/off
    payload += std::to_string(false);
    payload += ",";
    payload += "s_17:"; // left eye blink detection
    payload += std::to_string(4);
    payload += ",";
    payload += "s_18:"; // left eye blink detection
    payload += std::to_string(5);
    payload += ",";

    payload += "s_19:"; // Is double eyes click enabled
    payload += std::to_string(false);
    payload += ",";
    payload += "s_20:"; // Double eyes click left button action
    payload += std::to_string(7);
    payload += ",";
    payload += "s_21:"; // Double eyes click right button action
    payload += std::to_string(6);
    //payload += ",";


    /*payload += "s_4:"; //Default_up
    payload += std::to_string(redefined_up);
    payload += ",";
    payload += "s_5:"; //Default_down
    payload += std::to_string(redefined_down);
    payload += ",";
    payload += "s_6:"; //Default_left
    payload += std::to_string(redefined_left);
    payload += ",";
    payload += "s_7:"; //Default_right
    payload += std::to_string(redefined_right);
    payload += ",";*/
    /* payload += "s_16:"; //Default_head_left_click
    payload += std::to_string(default_head_left_click);
    payload += ",";
    payload += "s_17:"; //Default_head_right_click
    payload += std::to_string(default_head_right_click);
    payload += ",";
    payload += "s_18:"; //Default_head_sensibility
    payload += std::to_string(default_head_sensibility);
    payload += ",";
    payload += "s_19:"; //Default_head_scrolling_mode
    payload += std::to_string(default_head_scrolling_mode);
    payload += ",";
    payload += "s_20:"; //Default_head_scrolling_up
    payload += std::to_string(default_head_scrolling_up);
    payload += ",";
    payload += "s_21:"; //Default_head_scrolling_down
    payload += std::to_string(default_head_scrolling_down);
    payload += ",";
    payload += "s_22:"; //Default_head_scrolling_left
    payload += std::to_string(default_head_scrolling_left);
    payload += ",";
    payload += "s_23:"; //Default_head_scrolling_right
    payload += std::to_string(default_head_scrolling_right);
    payload += ",";*/
    /*payload += "s_10:"; //clear mode left move
    payload += std::to_string(static_cast<int>(clear_change_sensibility)); 
    payload += ",";*/
        /*payload += "s_11:"; //Sensetive_head_left_click
    payload += std::to_string(sensetive_head_left_click);
    payload += ",";
    payload += "s_12:"; //Sensetive_head_right_click
    payload += std::to_string(sensetive_head_right_click);
    payload += ",";
    payload += "s_13:"; //Sensetive_head_scrolling_mode
    payload += std::to_string(sensetive_head_scrolling_mode);
    payload += ",";*/

    return payload;
}
