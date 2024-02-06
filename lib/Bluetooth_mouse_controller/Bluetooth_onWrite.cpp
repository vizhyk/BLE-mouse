#include "Bluetooth_onWrite.hpp"

Bluetooth_onWrite::Bluetooth_onWrite() {};

using json = nlohmann::json;
Preferences preferences;

int function_call_counter = 0;

void Bluetooth_onWrite::onWrite(BLECharacteristic *pCharacteristic)
{
      std::string payload = pCharacteristic->getValue();
      std::string str_for_dump;

      if (payload.length() > 0) {
        json example = json::parse(payload);
        str_for_dump =  example.dump(1);
        Serial.println(str_for_dump.c_str());


        auto mode_status = example["s_0"].get<int>();       //current mode
        auto invertation_status = example["s_1"].get<int>(); // invertation
        auto sens = example["s_2"].get<int>();                // clear mode sensibility
        auto alt_sensibility = example["s_3"].get<int>();      // sensitive mode sensibility

        auto redef_clear_scrolling =  example["s_4"].get<int>(); //clear mode scrolling move
        auto redef_clear_right_click =  example["s_5"].get<int>(); //clear mode right click move
        auto redef_clear_left_click =  example["s_6"].get<int>(); //clear mode left click move

        auto temp_default_head_up =  example["s_7"].get<int16_t>();  //clear mode up move limit 
        auto temp_default_head_down =  example["s_8"].get<int16_t>(); //clear mode down move limit
        auto temp_default_head_left =  example["s_9"].get<int16_t>(); //clear mode left move limit
        auto temp_default_head_right =  example["s_10"].get<int16_t>(); //clear mode right move limit

        auto sens_turn_right = example["s_11"].get<int>(); //sensetive mode right click move 
        auto sens_turn_left = example["s_12"].get<int>(); //sensetive mode left click move
        auto sens_up = example["s_13"].get<int>(); //sensetive mode scrolling move

        auto temp_enable_click = example["s_14"].get<int>();       //auto click mode on/off
        auto temp_left_click_time = example["s_15"].get<int>();     //auto click mode time between clicks in seconds 

        auto eye_click = example["s_16"].get<bool>();             //iclick mode on/off

        auto eye_click_lef = example["s_17"].get<int>();         //eye click left eye action
        auto eye_click_righ = example["s_18"].get<int>();        //eye click right eye action

        auto double_eyes_click = example["s_19"].get<bool>();        // is double eyes click detected
        auto double_eyes_click_left_button_control = example["s_20"].get<int>();            // double eyes click left button action
        auto double_eyes_click_right_button_control = example["s_21"].get<int>();           // double eyes click right button action

        /* auto sens_down = example["s_19"].get<int>();
        auto redef_left_move =  example["s_10"].get<int>();

        auto redef_up =  example["s_4"].get<int>();  //not in use
        auto redef_down =  example["s_5"].get<int>(); // not in use 
        auto redef_left =  example["s_6"].get<int>(); //not in use
        auto redef_right =  example["s_7"].get<int>(); //not in use 


        auto temp_default_head_left_click =  example["s_16"].get<int16_t>(); // not in use 
        auto temp_default_head_right_click =  example["s_17"].get<int16_t>(); // not in use 
        auto temp_default_head_sensibility =  example["s_18"].get<int16_t>(); // not in use  
        auto temp_default_head_scrolling_mode =  example["s_19"].get<int16_t>(); // not in use 

        auto temp_default_head_scrolling_up =  example["s_20"].get<int16_t>(); //not in use
        auto temp_default_head_scrolling_down =  example["s_21"].get<int16_t>(); //not in use
        auto temp_default_head_scrolling_left =  example["s_22"].get<int16_t>(); //not in use
        auto temp_default_head_scrolling_right =  example["s_23"].get<int16_t>(); //not in use*/

        /* auto temp_sensetive_head_left_click =  example["s_11"].get<int16_t>(); 
        auto temp_sensetive_head_right_click =  example["s_12"].get<int16_t>(); 
        auto temp_sensetive_head_scrolling_mode =  example["s_13"].get<int16_t>(); */

        mouse_sensibility = sens;
        alternative_mode = mode_status;
        alternative_mode_sensibility = alt_sensibility;
        is_inverted = invertation_status;

        //clear_change_sensibility = static_cast<Redefined_action>(redef_left_move);
        clear_scrolling = static_cast<Redefined_action>(redef_clear_scrolling);
        clear_right_click = static_cast<Redefined_action>(redef_clear_right_click);
        clear_left_click = static_cast<Redefined_action>(redef_clear_left_click);
       
        default_head_up = temp_default_head_up;
        default_head_down = temp_default_head_down;
        default_head_left = temp_default_head_left;
        default_head_right = temp_default_head_right;

        sensetive_right_click = static_cast<Redefined_action>(sens_turn_right);
        sensetive_left_click = static_cast<Redefined_action>(sens_turn_left);
        sensetive_scrolling = static_cast<Redefined_action>(sens_up);

        enable_click = temp_enable_click;
        left_click_time = temp_left_click_time;

        i_click_mode = eye_click;
        i_click_left = eye_click_lef;
        i_click_right= eye_click_righ;

        isDoubleEyesClick = double_eyes_click;
        eyesDoubleClickLeftButtonControl = double_eyes_click_left_button_control;
        eyesDoubleClickRightButtonControl = double_eyes_click_right_button_control;


        //sensetive_down = static_cast<Redefined_action>(sens_down);

        /*default_head_left_click = temp_default_head_left_click;
        default_head_right_click =  temp_default_head_right_click;
        default_head_sensibility = temp_default_head_sensibility;
        default_head_scrolling_mode = temp_default_head_scrolling_mode;

        default_head_scrolling_up = temp_default_head_scrolling_up;
        default_head_scrolling_down = temp_default_head_scrolling_down;
        default_head_scrolling_left = temp_default_head_scrolling_left;
        default_head_scrolling_right = temp_default_head_scrolling_right;*/
     
        /*sensetive_head_left_click = temp_sensetive_head_left_click;
        sensetive_head_right_click = temp_sensetive_head_right_click;
        sensetive_head_scrolling_mode = temp_sensetive_head_scrolling_mode;*/

        /*redefined_up = redef_up;
        redefined_down = redef_down;
        redefined_left = redef_left;
        redefined_right = redef_right;*/

        preferences.begin("mouse_sett", false); 
     
        preferences.putBool("alt_mode", mode_status);
        preferences.putBool("inverted", invertation_status);
        preferences.putInt("mouse_sens", sens);
        preferences.putInt("al_mouse_sen", alt_sensibility);


        preferences.putInt("redef_l_clk", redef_clear_left_click);
        preferences.putInt("redef_k_clk", redef_clear_right_click);
        //preferences.putInt("redef_lefteb", redef_left_move);
        preferences.putInt("redef_scroll", redef_clear_scrolling);

        preferences.putInt("def_hd_up", temp_default_head_up);
        preferences.putInt("def_hd_down", temp_default_head_down);
        preferences.putInt("def_hd_left", temp_default_head_left);
        preferences.putInt("def_hd_right", temp_default_head_right);

        preferences.putInt("senset_r_cl", sens_turn_right);
        preferences.putInt("senset_l_cl", sens_turn_left);
        preferences.putInt("senset_scroll", sens_up);

        preferences.putBool("click_mode", temp_enable_click);
        preferences.putInt("click_time", temp_left_click_time);

        preferences.putBool("i_click", eye_click);
        preferences.putInt("l_click", i_click_left);
        preferences.putInt("r_click", i_click_right);

        preferences.putBool("db_eye_click", double_eyes_click);
        preferences.putInt("db_eyes_l_b", double_eyes_click_left_button_control);
        preferences.putInt("db_eyes_r_b", double_eyes_click_right_button_control);

        /*preferences.putInt("redef_up", redef_up);
        preferences.putInt("redef_down", redef_down);
        preferences.putInt("redef_left", redef_left);
        preferences.putInt("redef_right", redef_right);*/

        /*preferences.putInt("def_hd_l_clk", temp_default_head_left_click);
        preferences.putInt("def_hd_r_clk", temp_default_head_right_click);
        preferences.putInt("def_hd_sens", temp_default_head_sensibility);
        preferences.putInt("def_hd_scrl", temp_default_head_scrolling_mode);

        preferences.putInt("def_hd_sc_up", temp_default_head_scrolling_up);
        preferences.putInt("def_hd_sc_d", temp_default_head_scrolling_down);
        preferences.putInt("def_hd_sc_l", temp_default_head_scrolling_left);
        preferences.putInt("def_hd_sc_r", temp_default_head_scrolling_right);*/

        /*preferences.putInt("sens_l_clk", temp_sensetive_head_left_click);
        preferences.putInt("sens_r_clk", temp_sensetive_head_right_click);
        preferences.putInt("sens_sc_mode", temp_sensetive_head_scrolling_mode);*/

        preferences.putBool("get_config", true);

        preferences.end();
    }
}

void Bluetooth_onWrite::set_settings()
{
  preferences.begin("mouse_sett", false); 

  auto change_settings = preferences.getBool("get_config", 0);
  if(function_call_counter < 1)
  {
  if(change_settings)
  {
     alternative_mode = preferences.getBool("alt_mode",0);
     Serial.println("alt_mode");
     Serial.println(alternative_mode);
     is_inverted = preferences.getBool("inverted", 0);
     Serial.println("inverted");
     Serial.println(is_inverted);
     mouse_sensibility = preferences.getInt("mouse_sens", 0);
     Serial.println("mouse_sens");
     Serial.println(mouse_sensibility);
     alternative_mode_sensibility = preferences.getInt("al_mouse_sen", 0);
     Serial.println("al_mouse_sen");
     Serial.println(alternative_mode_sensibility);

     clear_left_click = static_cast<Redefined_action>(preferences.getInt("redef_l_clk", 0));
     Serial.println("redef_l_clk");
     int d_val = static_cast<int>(clear_left_click); 
     Serial.println(d_val);
     clear_right_click = static_cast<Redefined_action>(preferences.getInt("redef_k_clk", 0));
     Serial.println("redef_k_clk");
     int u_val = static_cast<int>(clear_right_click); 
     Serial.println(u_val);
     /*clear_change_sensibility = static_cast<Redefined_action>(preferences.getInt("redef_lefteb", 0));
     Serial.println("redef_lefteb");
     int l_val = static_cast<int>(clear_change_sensibility); 
     Serial.println(l_val);*/
     clear_scrolling = static_cast<Redefined_action>(preferences.getInt("redef_scroll", 0));
     Serial.println("redef_scroll");
     int r_val = static_cast<int>(clear_scrolling); 
     Serial.println(r_val);

     default_head_up = preferences.getInt("def_hd_up", 0);
     Serial.println("def_hd_up");
     Serial.println(default_head_up);
     default_head_down = preferences.getInt("def_hd_down", 0);
     Serial.println("def_hd_down");
     Serial.println(default_head_down);
     default_head_left = preferences.getInt("def_hd_left", 0);
     Serial.println("def_hd_left");
     Serial.println(default_head_left);
     default_head_right = preferences.getInt("def_hd_right", 0);
     Serial.println("def_hd_right");
     Serial.println(default_head_right);

     sensetive_right_click = static_cast<Redefined_action>(preferences.getInt("senset_r_cl", 0));
     Serial.println("senset_r_cl");
     int sens_right = static_cast<int>(sensetive_right_click); 
     Serial.println(sens_right);
     sensetive_left_click = static_cast<Redefined_action>(preferences.getInt("senset_l_cl", 0));
     Serial.println("senset_l_cl");
     int sens_left = static_cast<int>(sensetive_left_click); 
     Serial.println(sens_left);
     sensetive_scrolling = static_cast<Redefined_action>(preferences.getInt("senset_scroll", 0));
     Serial.println("senset_scroll");
     int sens_up = static_cast<int>(sensetive_scrolling); 
     Serial.println(sens_up);
//------------------------------------------------------
     enable_click = preferences.getBool("click_mode", 0);
     Serial.println("click_mode");
     Serial.println(enable_click);

     /*left_click_time = preferences.getInt("click_time", 0);         
     Serial.println("click_time");
     Serial.println(left_click_time);*/
//---------------------------------------------------------
     i_click_mode = preferences.getBool("click_mode", 0);
     Serial.println("click_mode");
     Serial.println(i_click_mode);

     i_click_mode = preferences.getBool("l_click", 0);
     Serial.println("i_click_left");
     Serial.println(i_click_left);

     i_click_mode = preferences.getBool("r_click", 0);
     Serial.println("i_click_right");
     Serial.println(i_click_right);
//----------------------------------------------------------

     isDoubleEyesClick = preferences.getBool("db_eye_click",0);
     Serial.println("double eyes click enabled");
     Serial.println(isDoubleEyesClick);

     eyesDoubleClickLeftButtonControl = preferences.getInt("db_eyes_l_b",0);
     Serial.println("eyesDoubleClickLeftButtonControl");
     Serial.println(eyesDoubleClickLeftButtonControl);

     eyesDoubleClickRightButtonControl = preferences.getInt("db_eyes_r_b",0);
     Serial.println("eyesDoubleClickRightButtonControl");
     Serial.println(eyesDoubleClickRightButtonControl);



     /*sensetive_down = static_cast<Redefined_action>(preferences.getInt("sens_down", 0));
     Serial.println("sens_down");
     int sens_down = static_cast<int>(sensetive_down); 
     Serial.println(sens_down);*/

    /*redefined_up = preferences.getInt("redef_up", 0);
     Serial.println("redef_up");
     Serial.println(redefined_up);
     redefined_down = preferences.getInt("redef_down", 0);
     Serial.println("redef_down");
     Serial.println(redefined_down);
     redefined_left = preferences.getInt("redef_left", 0);
     Serial.println("redef_left");
     Serial.println(redefined_left);
     redefined_right = preferences.getInt("redef_right", 0);
     Serial.println("redef_right");
     Serial.println(redefined_right);*/

     /*default_head_left_click = preferences.getInt("def_hd_l_clk", 0);
     Serial.println("def_hd_l_clk");
     Serial.println(default_head_left_click);
     default_head_right_click = preferences.getInt("def_hd_r_clk", 0);
     Serial.println("def_hd_r_clk");
     Serial.println(default_head_right_click);
     default_head_sensibility= preferences.getInt("def_hd_sens", 0);
     Serial.println("def_hd_sens");
     Serial.println(default_head_sensibility);
     default_head_scrolling_mode = preferences.getInt("def_hd_scrl", 0);
     Serial.println("def_hd_scrl");
     Serial.println(default_head_scrolling_mode);

     default_head_scrolling_up = preferences.getInt("def_hd_sc_up", 0);
     Serial.println("def_hd_sc_up");
     Serial.println(default_head_scrolling_up);
     default_head_scrolling_down = preferences.getInt("def_hd_sc_d", 0);
     Serial.println("def_hd_sc_d");
     Serial.println(default_head_scrolling_down);
     default_head_scrolling_left = preferences.getInt("def_hd_sc_l", 0);
     Serial.println("def_hd_sc_l");
     Serial.println(default_head_scrolling_left);
     default_head_scrolling_right = preferences.getInt("def_hd_sc_r", 0);
     Serial.println("def_hd_sc_r");
     Serial.println(default_head_scrolling_right);*/

     /*sensetive_head_left_click = preferences.getInt("sens_l_clk", 0);
     Serial.println("sens_l_clk");
     Serial.println(sensetive_head_left_click);
     sensetive_head_right_click = preferences.getInt("sens_r_clk", 0);
     Serial.println("sens_r_clk");
     Serial.println(sensetive_head_right_click);
     sensetive_head_scrolling_mode = preferences.getInt("sens_sc_mode", 0);
     Serial.println("sens_sc_mode");
     Serial.println(sensetive_head_scrolling_mode);*/

     function_call_counter++;

    }
  }
  preferences.end();
}

void Bluetooth_onWrite::set_auto_click_timer()
{
    preferences.begin("mouse_sett", false);
    auto change_settings = preferences.getBool("get_config", 0);
    if(change_settings) 
    {
      left_click_time = preferences.getInt("click_time", 0); 
      Serial.println("[INFO]: auto click timer redefined");
    }
    preferences.end();
}