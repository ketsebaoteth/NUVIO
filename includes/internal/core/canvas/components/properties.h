#pragma once
#include <variant>
#include <string>
#include "glm/glm.hpp"

enum class PropertyType {
    Color,
    Float,
    Int,
    String,
    Bool,
    // ...add more as needed
};

using PropertyValue = std::variant<float, int, std::string, bool, glm::vec4 /* color */>;

struct Property {
    bool isOnSameLine = true; // default to true
    PropertyType type;
    std::string name;
    void* value; // pointer to the actual value in the renderable
    float minValue = 0.0f; // for float and int types
    float maxValue = 1.0f; // for float and int types
    float step = 0.1f; // for float and int types
};