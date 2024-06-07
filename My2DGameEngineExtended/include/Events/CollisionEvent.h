#pragma once

#include <entt.hpp>
#include "EventBus/Event.h"

class CollisionEvent : public Event {
public:
	entt::entity a;
	entt::entity b;
	CollisionEvent(entt::entity a, entt::entity b) : a{a}, b{b} {}
};