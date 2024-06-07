#pragma once

#include "Event.h"
#include <entt.hpp>
#include <memory>

class IEventCallback {
private:
	virtual void Call(std::unique_ptr<entt::registry>& registry, Event& e) = 0;
public:
	virtual ~IEventCallback() = default;

	void Execute(std::unique_ptr<entt::registry>& registry, Event& e) {
		Call(registry, e);
	}
};

template <typename TEvent>
class EventCallback : public IEventCallback {
private:
	typedef void (*CallbackFunction)(std::unique_ptr<entt::registry>&, TEvent&);
	CallbackFunction callbackFunction;

	void Call(std::unique_ptr<entt::registry>& registry, Event& e) override {
		callbackFunction(registry, static_cast<TEvent&>(e));
	}

public:
	EventCallback(CallbackFunction callbackFunction) 
		: callbackFunction{callbackFunction} {}
};