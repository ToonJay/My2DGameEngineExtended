#pragma once

#include "EventCallback.h"
#include <list>
#include <map>
#include <memory>
#include <typeindex>

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus {
private:
	std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

public:
	void Reset() {
		subscribers.clear();
	}

	template <typename TEvent>
	void SubscribeToEvent(void (*callbackFunction)(std::unique_ptr<entt::registry>&, TEvent&)) {
		if (!subscribers[typeid(TEvent)].get()) {
			subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
		}
		auto subscriber = std::make_unique<EventCallback<TEvent>>(callbackFunction);
		subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
	}

	template <typename TEvent, typename ...TArgs>
	void EmitEvent(std::unique_ptr<entt::registry>& registry, TArgs&& ...args) {
		auto handlers = subscribers[typeid(TEvent)].get();
		if (handlers) {
			for (auto it = handlers->begin(); it != handlers->end(); it++) {
				auto handler = it->get();
				TEvent event(std::forward<TArgs>(args)...);
				handler->Execute(registry, event);
			}
		}
	}
};