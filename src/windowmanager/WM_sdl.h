
#ifndef __WM_SDL_H__
#define __WM_SDL_H__

#include <SDL/SDL.h>

#define WM_KMOD_NONE  		KMOD_NONE
#define WM_KMOD_LSHIFT		KMOD_LSHIFT
#define WM_KMOD_RSHIFT		KMOD_RSHIFT
#define WM_KMOD_LCTRL 		KMOD_LCTRL
#define WM_KMOD_RCTRL 		KMOD_RCTRL
#define WM_KMOD_LALT  		KMOD_LALT
#define WM_KMOD_RALT  		KMOD_RALT

#define WM_KMOD_SHIFT		(WM_KMOD_LSHIFT | WM_KMOD_RSHIFT)
#define WM_KMOD_CTRL 		(WM_KMOD_LCTRL  | WM_KMOD_RCTRL )
#define WM_KMOD_ALT  		(WM_KMOD_LALT   | WM_KMOD_RALT  )

#define WM_KEY_UP			SDLK_UP
#define WM_KEY_DOWN			SDLK_DOWN
#define WM_KEY_LEFT			SDLK_LEFT
#define WM_KEY_RIGHT		SDLK_RIGHT

#endif

