#include "stdafx.h"
#include "OISHelp.h"
std::string OISHelp::keyCodeToString(OIS::KeyCode keycode)
{
	switch (keycode)
	{
	case OIS::KC_UNASSIGNED:
		break;
	case OIS::KC_ESCAPE:
		break;
	case OIS::KC_1:
		break;
	case OIS::KC_2:
		break;
	case OIS::KC_3:
		break;
	case OIS::KC_4:
		break;
	case OIS::KC_5:
		break;
	case OIS::KC_6:
		break;
	case OIS::KC_7:
		break;
	case OIS::KC_8:
		break;
	case OIS::KC_9:
		break;
	case OIS::KC_0:
		break;
	case OIS::KC_MINUS:
		break;
	case OIS::KC_EQUALS:
		break;
	case OIS::KC_BACK:
		break;
	case OIS::KC_TAB:
		break;
	case OIS::KC_Q:
		break;
	case OIS::KC_W:
		break;
	case OIS::KC_E:
		return "E.";
	case OIS::KC_R:
		break;
	case OIS::KC_T:
		break;
	case OIS::KC_Y:
		break;
	case OIS::KC_U:
		break;
	case OIS::KC_I:
		break;
	case OIS::KC_O:
		break;
	case OIS::KC_P:
		break;
	case OIS::KC_LBRACKET:
		break;
	case OIS::KC_RBRACKET:
		break;
	case OIS::KC_RETURN:
		return "ENTER.";
	case OIS::KC_LCONTROL:
		break;
	case OIS::KC_A:
		break;
	case OIS::KC_S:
		break;
	case OIS::KC_D:
		break;
	case OIS::KC_F:
		break;
	case OIS::KC_G:
		break;
	case OIS::KC_H:
		break;
	case OIS::KC_J:
		break;
	case OIS::KC_K:
		break;
	case OIS::KC_L:
		break;
	case OIS::KC_SEMICOLON:
		break;
	case OIS::KC_APOSTROPHE:
		break;
	case OIS::KC_GRAVE:
		break;
	case OIS::KC_LSHIFT:
		break;
	case OIS::KC_BACKSLASH:
		break;
	case OIS::KC_Z:
		break;
	case OIS::KC_X:
		break;
	case OIS::KC_C:
		break;
	case OIS::KC_V:
		break;
	case OIS::KC_B:
		break;
	case OIS::KC_N:
		break;
	case OIS::KC_M:
		break;
	case OIS::KC_COMMA:
		break;
	case OIS::KC_PERIOD:
		break;
	case OIS::KC_SLASH:
		break;
	case OIS::KC_RSHIFT:
		break;
	case OIS::KC_MULTIPLY:
		break;
	case OIS::KC_LMENU:
		break;
	case OIS::KC_SPACE:
		return "SPACE.";
	case OIS::KC_CAPITAL:
		break;
	case OIS::KC_F1:
		break;
	case OIS::KC_F2:
		break;
	case OIS::KC_F3:
		break;
	case OIS::KC_F4:
		break;
	case OIS::KC_F5:
		break;
	case OIS::KC_F6:
		break;
	case OIS::KC_F7:
		break;
	case OIS::KC_F8:
		break;
	case OIS::KC_F9:
		break;
	case OIS::KC_F10:
		break;
	case OIS::KC_NUMLOCK:
		break;
	case OIS::KC_SCROLL:
		break;
	case OIS::KC_NUMPAD7:
		break;
	case OIS::KC_NUMPAD8:
		break;
	case OIS::KC_NUMPAD9:
		break;
	case OIS::KC_SUBTRACT:
		break;
	case OIS::KC_NUMPAD4:
		break;
	case OIS::KC_NUMPAD5:
		break;
	case OIS::KC_NUMPAD6:
		break;
	case OIS::KC_ADD:
		break;
	case OIS::KC_NUMPAD1:
		break;
	case OIS::KC_NUMPAD2:
		break;
	case OIS::KC_NUMPAD3:
		break;
	case OIS::KC_NUMPAD0:
		break;
	case OIS::KC_DECIMAL:
		break;
	case OIS::KC_OEM_102:
		break;
	case OIS::KC_F11:
		break;
	case OIS::KC_F12:
		break;
	case OIS::KC_F13:
		break;
	case OIS::KC_F14:
		break;
	case OIS::KC_F15:
		break;
	case OIS::KC_KANA:
		break;
	case OIS::KC_ABNT_C1:
		break;
	case OIS::KC_CONVERT:
		break;
	case OIS::KC_NOCONVERT:
		break;
	case OIS::KC_YEN:
		break;
	case OIS::KC_ABNT_C2:
		break;
	case OIS::KC_NUMPADEQUALS:
		break;
	case OIS::KC_PREVTRACK:
		break;
	case OIS::KC_AT:
		break;
	case OIS::KC_COLON:
		break;
	case OIS::KC_UNDERLINE:
		break;
	case OIS::KC_KANJI:
		break;
	case OIS::KC_STOP:
		break;
	case OIS::KC_AX:
		break;
	case OIS::KC_UNLABELED:
		break;
	case OIS::KC_NEXTTRACK:
		break;
	case OIS::KC_NUMPADENTER:
		break;
	case OIS::KC_RCONTROL:
		break;
	case OIS::KC_MUTE:
		break;
	case OIS::KC_CALCULATOR:
		break;
	case OIS::KC_PLAYPAUSE:
		break;
	case OIS::KC_MEDIASTOP:
		break;
	case OIS::KC_VOLUMEDOWN:
		break;
	case OIS::KC_VOLUMEUP:
		break;
	case OIS::KC_WEBHOME:
		break;
	case OIS::KC_NUMPADCOMMA:
		break;
	case OIS::KC_DIVIDE:
		break;
	case OIS::KC_SYSRQ:
		break;
	case OIS::KC_RMENU:
		break;
	case OIS::KC_PAUSE:
		break;
	case OIS::KC_HOME:
		break;
	case OIS::KC_UP:
		break;
	case OIS::KC_PGUP:
		break;
	case OIS::KC_LEFT:
		break;
	case OIS::KC_RIGHT:
		break;
	case OIS::KC_END:
		break;
	case OIS::KC_DOWN:
		break;
	case OIS::KC_PGDOWN:
		break;
	case OIS::KC_INSERT:
		break;
	case OIS::KC_DELETE:
		break;
	case OIS::KC_LWIN:
		break;
	case OIS::KC_RWIN:
		break;
	case OIS::KC_APPS:
		break;
	case OIS::KC_POWER:
		break;
	case OIS::KC_SLEEP:
		break;
	case OIS::KC_WAKE:
		break;
	case OIS::KC_WEBSEARCH:
		break;
	case OIS::KC_WEBFAVORITES:
		break;
	case OIS::KC_WEBREFRESH:
		break;
	case OIS::KC_WEBSTOP:
		break;
	case OIS::KC_WEBFORWARD:
		break;
	case OIS::KC_WEBBACK:
		break;
	case OIS::KC_MYCOMPUTER:
		break;
	case OIS::KC_MAIL:
		break;
	case OIS::KC_MEDIASELECT:
		break;
	default:
		break;
	}
	return "unkownKey";
}