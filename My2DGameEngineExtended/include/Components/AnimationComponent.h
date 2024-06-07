#pragma once
#include <SDL.h>

struct AnimationComponent {
	int numFrames{1};
	int currentFrame{0};
	int currentAnimationSpeed{0};
	int defaultAnimationSpeed{0};
	Uint32 startTime{SDL_GetTicks()};
	bool isLooping{true};
	
	AnimationComponent() = default;

	AnimationComponent(const int numFrames, const int currentAnimationSpeed, const int defaultAnimationSpeed, const bool isLooping) 
		: numFrames{numFrames}, currentAnimationSpeed{currentAnimationSpeed}, defaultAnimationSpeed{defaultAnimationSpeed}, isLooping {isLooping} {}
};
using Animation = AnimationComponent;