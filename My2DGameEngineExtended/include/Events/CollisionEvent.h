#pragma once

#include "EventBus/Event.h"
#include <entt.hpp>

enum class CollisionType {
    None,
    Ground,
    Ceiling,
    Left,
    Right
};

class CollisionEvent : public Event {
public:
	entt::entity a;
	entt::entity b;
    CollisionType collisionType;
    CollisionEvent(entt::entity a, entt::entity b, CollisionType collisionType) : a{a}, b{b}, collisionType{collisionType} {}
};