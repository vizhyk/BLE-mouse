extern bool reset_values;
extern bool charging_status;
extern bool enable_click;

extern bool is_inverted;
extern bool alternative_mode;

extern bool i_click_mode;
extern int i_click_left; 
extern int i_click_right;

extern bool isDoubleEyesClick;
extern int eyesDoubleClickLeftButtonControl;
extern int eyesDoubleClickRightButtonControl;

extern int redefined_up;
extern int redefined_down;
extern int redefined_left;
extern int redefined_right;

extern int left_click_time;
extern int mouse_sensibility;
extern int alternative_mode_sensibility;

extern int16_t default_head_up;
extern int16_t default_head_down;
extern int16_t default_head_left;
extern int16_t default_head_right;

extern int16_t default_head_left_click;
extern int16_t default_head_right_click;
extern int16_t default_head_sensibility;
extern int16_t default_head_scrolling_mode;

extern int16_t default_head_scrolling_up;
extern int16_t default_head_scrolling_down;
extern int16_t default_head_scrolling_left;
extern int16_t default_head_scrolling_right;

extern int16_t sensetive_head_left_click;
extern int16_t sensetive_head_right_click;
extern int16_t sensetive_head_scrolling_mode;

enum class Redefined_action {
	TURN_RIGHT,
	TURN_LEFT,
	UP,
    DOWN,
	DISABLED_ACTION
};

extern Redefined_action clear_scrolling;
extern Redefined_action clear_change_sensibility ;
extern Redefined_action clear_right_click ;
extern Redefined_action clear_left_click;

extern Redefined_action sensetive_right_click;
extern Redefined_action sensetive_left_click;
extern Redefined_action sensetive_scrolling ;
extern Redefined_action sensetive_down;




enum Redefined_sides {
	MOUSE_MOVE_UP,
	MOUSE_MOVE_DOWN,
	MOUSE_MOVE_LEFT,
	MOUSE_MOVE_RIGHT,
	DISABLED_SIDE
};

enum Redefined_moves {
	MOUSE_LEFT_CLICK,
	MOUSE_RIGHT_CLICK,
	CHANGE_SENSIBILITY,
	ENABLE_SCROLLING_MODE,
	DISABLED_MOVE
};


