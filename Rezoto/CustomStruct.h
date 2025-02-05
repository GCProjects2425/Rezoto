#pragma once
#include <iostream>
#include <sstream>
#include <string>

class Rectangle;
class Vector2;

class CustomStruct
{
};

struct LeRectangle
{
    float x;
    float y;
    float width;
    float height;

    LeRectangle() : x(0), y(0), width(0), height(0) {};
    LeRectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {};

    struct Rectangle ToRectangle() const;
};

struct LeVector2 {

    float x;
    float y;

    LeVector2() : x(0), y(0) {}  // Constructeur par d�faut
    LeVector2(float x, float y) : x(x), y(y) {}  // Constructeur avec param�tres

    std::string toString() const {
        std::stringstream ss;
        ss << x << "," << y;
        return ss.str();
    }

    static LeVector2 fromString(const std::string& str) {
        LeVector2 v;
        std::stringstream ss(str);
        char sep;
        ss >> v.x >> sep >> v.y;  // Lire x, y s�par�s par une virgule
        return v;
    }

    struct Vector2 ToVector2() const;
};


