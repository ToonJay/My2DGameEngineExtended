#pragma once

#include "EventBus/Event.h"
#include <SDL.h>

class KeyReleaseEvent : public Event {
public:
	SDL_Keycode symbol;
	KeyReleaseEvent(SDL_Keycode symbol) : symbol(symbol) {}
};