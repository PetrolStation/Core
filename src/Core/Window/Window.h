#pragma once

#include <string>
#include <memory>
#include <utility>

#include "Core/Aliases.h"

#include "Core/Image.h"
#include "Core/EventStack.h"
#include "WindowResourceCreator.h"

namespace PetrolEngine {

    enum class Keys : uint16 {
        KeyNone = 0,
        KeyBackspace = 8,
        KeyDelete = 127,
        KeyTab = 9,
        KeyClear = 12,
        KeyReturn = 13,
        KeyPause = 19,
        KeyEscape = 27,
        KeySpace = 32,
        KeyKeypad0 = 256,
        KeyKeypad1 = 257,
        KeyKeypad2 = 258,
        KeyKeypad3 = 259,
        KeyKeypad4 = 260,
        KeyKeypad5 = 261,
        KeyKeypad6 = 262,
        KeyKeypad7 = 263,
        KeyKeypad8 = 264,
        KeyKeypad9 = 265,
        KeyKeypadPeriod = 266,
        KeyKeypadDivide = 267,
        KeyKeypadMultiply = 268,
        KeyKeypadMinus = 269,
        KeyKeypadPlus = 270,
        KeyKeypadEnter = 271,
        KeyKeypadEquals = 272,
        KeyUpArrow = 273,
        KeyDownArrow = 274,
        KeyRightArrow = 275,
        KeyLeftArrow = 276,
        KeyInsert = 277,
        KeyHome = 278,
        KeyEnd = 279,
        KeyPageUp = 280,
        KeyPageDown = 281,
        KeyF1 = 282,
        KeyF2 = 283,
        KeyF3 = 284,
        KeyF4 = 285,
        KeyF5 = 286,
        KeyF6 = 287,
        KeyF7 = 288,
        KeyF8 = 289,
        KeyF9 = 290,
        KeyF10 = 291,
        KeyF11 = 292,
        KeyF12 = 293,
        KeyF13 = 294,
        KeyF14 = 295,
        KeyF15 = 296,
        Key0 = 48,
        Key1 = 49,
        Key2 = 50,
        Key3 = 51,
        Key4 = 52,
        Key5 = 53,
        Key6 = 54,
        Key7 = 55,
        Key8 = 56,
        Key9 = 57,
        KeyExclaim = 33,
        KeyDoubleQuote = 34,
        KeyHash = 35,
        KeyDollar = 36,
        KeyPercent = 37,
        KeyAmpersand = 38,
        KeyQuote = 39,
        KeyLeftParen = 40,
        KeyRightParen = 41,
        KeyAsterisk = 42,
        KeyPlus = 43,
        KeyComma = 44,
        KeyMinus = 45,
        KeyPeriod = 46,
        KeySlash = 47,
        KeyColon = 58,
        KeySemicolon = 59,
        KeyLess = 60,
        KeyEquals = 61,
        KeyGreater = 62,
        KeyQuestion = 63,
        KeyAt = 64,
        KeyLeftBracket = 91,
        KeyBackslash = 92,
        KeyRightBracket = 93,
        KeyCaret = 94,
        KeyUnderscore = 95,
        KeyBackQuote = 96,
        KeyA = 97 ,
        KeyB = 98 ,
        KeyC = 99 ,
        KeyD = 100,
        KeyE = 101,
        KeyF = 102,
        KeyG = 103,
        KeyH = 104,
        KeyI = 105,
        KeyJ = 106,
        KeyK = 107,
        KeyL = 108,
        KeyM = 109,
        KeyN = 110,
        KeyO = 111,
        KeyP = 112,
        KeyQ = 113,
        KeyR = 114,
        KeyS = 115,
        KeyT = 116,
        KeyU = 117,
        KeyV = 118,
        KeyW = 119,
        KeyX = 120,
        KeyY = 121,
        KeyZ = 122,
        KeyLeftCurlyBracket = 123,
        KeyPipe = 124,
        KeyRightCurlyBracket = 125,
        KeyTilde = 126,
        KeyNumlock = 300,
        KeyCapsLock = 301,
        KeyScrollLock = 302,
        KeyRightShift = 303,
        KeyLeftShift = 304,
        KeyRightControl = 305,
        KeyLeftControl = 306,
        KeyRightAlt = 307,
        KeyLeftAlt = 308,
        KeyLeftMeta = 310,
        KeyRightMeta = 309,
        KeyLeftCommand = 310,
        KeyRightCommand = 309,
        KeyLeftApple = 310,
        KeyRightApple = 309,
        KeyLeftWindows = 311,
        KeyRightWindows = 312,
        KeyAltGr = 313,
        KeyHelp = 315,
        KeyPrint = 316,
        KeySysReq = 317,
        KeyBreak = 318,
        KeyMenu = 319,
        KeyMouse0 = 323,
        KeyMouse1 = 324,
        KeyMouse2 = 325,
        KeyMouse3 = 326,
        KeyMouse4 = 327,
        KeyMouse5 = 328,
        KeyMouse6 = 329,
        KeyJoystickButton0 = 330,
        KeyJoystickButton1 = 331,
        KeyJoystickButton2 = 332,
        KeyJoystickButton3 = 333,
        KeyJoystickButton4 = 334,
        KeyJoystickButton5 = 335,
        KeyJoystickButton6 = 336,
        KeyJoystickButton7 = 337,
        KeyJoystickButton8 = 338,
        KeyJoystickButton9 = 339,
        KeyJoystickButton10 = 340,
        KeyJoystickButton11 = 341,
        KeyJoystickButton12 = 342,
        KeyJoystickButton13 = 343,
        KeyJoystickButton14 = 344,
        KeyJoystickButton15 = 345,
        KeyJoystickButton16 = 346,
        KeyJoystickButton17 = 347,
        KeyJoystickButton18 = 348,
        KeyJoystickButton19 = 349
    };
	class WindowApi {
	public:
		struct WindowData {
			int width;
			int height;

			String title;
		};

		struct WindowResizedEvent: Event { WindowData data; explicit WindowResizedEvent(WindowData data) : data(std::move(data)) {} };
		struct WindowClosedEvent : Event { WindowData data; explicit WindowClosedEvent (WindowData data) : data(std::move(data)) {} };

		struct MouseMovedEvent   : Event { double x, y; MouseMovedEvent   (double x, double y) : x(x), y(y) {} };
		struct MouseScrolledEvent: Event { double x, y; MouseScrolledEvent(double x, double y) : x(x), y(y) {} };
		struct MouseClickEvent   : Event { Keys key   ; MouseClickEvent   (Keys key) : key(key) {} };
		
		struct KeyPressedEvent   : Event { Keys key; bool repeat; KeyPressedEvent (Keys key, bool repeat) : key(key), repeat(repeat) {} };
		struct KeyReleasedEvent  : Event { Keys key;              KeyReleasedEvent(Keys key             ) : key(key)                 {} };
		struct KeyTypedEvent     : Event { Keys key;              KeyTypedEvent   (Keys key             ) : key(key)                 {} };

	public:
		NO_DISCARD int getWidth () const { return windowData.width ; };
		NO_DISCARD int getHeight() const { return windowData.height; };
		
		virtual int  init       () = 0;
		virtual void swapBuffers() = 0;
		virtual bool shouldClose() = 0;
		virtual void close      () = 0;
		virtual void pollEvents () = 0;

        virtual void showCursor(bool   enabled) = 0;
		virtual void setVSync  (bool   enabled) = 0;
		virtual void setIcon   (Image* image  ) = 0;

		virtual bool isPressed(Keys key) = 0;

        virtual ~WindowApi() = default;

		// Vulkan specific
		virtual void createWindowSurface(void* instance, const void* allocation, void* surface) = 0;

		NO_DISCARD float getAspectRatio() const;

	protected:
		WindowData windowData;
        Image* icon = nullptr;
	};
}