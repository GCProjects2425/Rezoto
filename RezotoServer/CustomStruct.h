#pragma once
#include <iostream>
#include <sstream>
#include <string>

class CustomStruct
{
};

struct Vector2f {
    
	float x;
	float y;

    Vector2f() : x(0), y(0) {}  // Constructeur par défaut
    Vector2f(float x, float y) : x(x), y(y) {}  // Constructeur avec paramètres

    std::string toString() const {
        std::stringstream ss;
        ss << x << "," << y;
        return ss.str();
    }

    static Vector2f fromString(const std::string& str) {
        Vector2f v;
        std::stringstream ss(str);
        char sep;
        ss >> v.x >> sep >> v.y;  // Lire x, y séparés par une virgule
        return v;
    }
};

