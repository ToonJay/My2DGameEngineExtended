#pragma once

#include <string>

struct TagComponent {
	std::string tag{""};

	TagComponent() = default;

	TagComponent(const std::string& tag) : tag{tag} {}
};
using Tag = TagComponent;