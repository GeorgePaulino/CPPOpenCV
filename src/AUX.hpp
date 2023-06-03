/**
 * @file AUX.cpp
 * @brief File with some helper classes.
 *
 */

#pragma once

namespace Game
{
    /// @brief Vector with two dimensions.
    class Vector
    {
    public:
        int x;
        int y;
        Vector(int x, int y) : x(x), y(y) {}
        virtual ~Vector() {}
    };

    /// @brief Size of the object.
    class Size : public Vector
    {
    public:
        Size(int x, int y) : Vector(x, y) {}
    };

    /// @brief Position of the object.
    class Position : public Vector
    {
    public:
        Position(int x, int y) : Vector(x, y) {}
    };
}