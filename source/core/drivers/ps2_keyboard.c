//CELEROS driver

#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_D 0x20
#define KEY_E 0x12
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_M 0x32
#define KEY_N 0x31
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_Q 0x10
#define KEY_R 0x13
#define KEY_S 0x1F
#define KEY_T 0x14
#define KEY_U 0x16
#define KEY_V 0x2F
#define KEY_W 0x11
#define KEY_X 0x2D
#define KEY_Y 0x15
#define KEY_Z 0x2C

#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0A
#define KEY_0 0x0B

#define KEY_F1 0x3B
#define KEY_F2 0x3C
#define KEY_F3 0x3D
#define KEY_F4 0x3E
#define KEY_F5 0x3F
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_F11 0x57
#define KEY_F12 0x58

#define KEY_ESC 0x01
#define KEY_ENTER 0x1C
#define KEY_SPACE 0x39
#define KEY_TAB 0x0F
#define KEY_BACKSPACE 0x0E
#define KEY_CAPSLOCK 0x3A
#define KEY_ESCAPE 0x01
#define KEY_DELETE 0x53

#define KEY_UP 0x48 
#define KEY_DOWN 0x50
#define KEY_LEFT 0x4B
#define KEY_RIGHT 0x4D

#define KEY_LEFT_SHIFT 0x2A
#define KEY_LEFT_CTRL 0x1D
#define KEY_RIGHT_SHIFT 0x36
#define KEY_NUMBER_LOCK 0x45
#define KEY_SCROLL_LOCK 0x46

#define KEY_KEYPAD_1 0x4F
#define KEY_KEYPAD_2 0x50
#define KEY_KEYPAD_3 0x51
#define KEY_KEYPAD_4 0x4B
#define KEY_KEYPAD_5 0x4C
#define KEY_KEYPAD_6 0x4D
#define KEY_KEYPAD_7 0x47
#define KEY_KEYPAD_8 0x48
#define KEY_KEYPAD_9 0x49
#define KEY_KEYPAD_0 0x52
#define KEY_KEYPAD_PLUS 0x4E
#define KEY_KEYPAD_MINUS 0x4A
#define KEY_KEYPAD_STAR 0x37  //*
#define KEY_KEYPAD_DOT 0x53  //.

#define KEY_LITTLE_DASH 0x0C  //-
#define KEY_EQUAL 0x0D  //=
#define KEY_LEFT_SQUARE 0x1A  //[
#define KEY_RIGHT_SQUARE 0x1B //]
#define KEY_SINGLE_QUOTE 0x28 //'
#define KEY_BACK_TICK 0x29 //`
#define KEY_BACKSLASH 0x2B  //"\" 
#define KEY_COMMA 0x33  //,
#define KEY_DOT 0x34  //.
#define KEY_SLASH 0x35  //"/"

#define KEY_LEFT_GUI 0x5B
#define KEY_RIGHT_GUI 0x5C
#define KEY_APPS 0x5D
#define KEY_POWER 0x5E
#define KEY_SLEEP 0x5F
#define KEY_WAKE 0x63

#define KEY_MULTIMEDIA_WWW_SEARCH 0x65
#define KEY_MULTIMEDIA_WWW_FAVORITES 0x66
#define KEY_MULTIMEDIA_WWW_REFRESH 0x67
#define KEY_MULTIMEDIA_WWW_FORWARD 0x68
#define KEY_MULTIMEDIA_WWW_BACK 0x69
#define KEY_MULTIMEDIA_MY_COMPUTER 0x6A
#define KEY_MULTIMEDIA_EMAIL 0x6B
#define KEY_MULTIMEDIA_MEDIA_SELECT 0x6C

#define KEY_RELEASED 0
#define KEY_PRESSED 1

uint8_t key=0;
uint8_t key_ascii=0;
uint32_t shift=KEY_RELEASED;
uint32_t capslock=KEY_RELEASED;
uint32_t handler_for_wait=0;

uint8_t ps2_keyboard_convert[2][256];

void wait_for_key(void) {
	handler_for_wait=0;

	while(1) {
		asm("hlt");
		if(handler_for_wait==1) {
			handler_for_wait=0;
			return;
		}
	}
}

void ps2_keyboard_set_sk(void) {

}

void keyboard_irq(void) {
	key = inb(0x60);

	if(key==42 || key==54) {
		shift=KEY_PRESSED;
	}
	if(key==170 || key==182) {
		shift=KEY_RELEASED;
	}

	//convert keycode to ascii
	key_ascii=0;
	if(shift==KEY_PRESSED) {
		key_ascii=ps2_keyboard_convert[1][key];
	}
	else {
		key_ascii=ps2_keyboard_convert[0][key];
	}

	handler_for_wait=1;

}
