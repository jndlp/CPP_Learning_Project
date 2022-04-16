#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

template <std::size_t dimension, typename TypePoint,
          std::enable_if_t<std::is_arithmetic_v<TypePoint>, bool> = true>
class Point
{

private:
    std::size_t size() const { return dimension; }

public:
    std::array<TypePoint, dimension> values;

    Point() = default;

    template <typename... Arg>
    Point(const TypePoint& first, Arg... others) : values { first, static_cast<TypePoint>(others)... }
    {
        static_assert(dimension - 1 == sizeof...(Arg));
    };

    TypePoint& x()
    {
        static_assert(dimension >= 1);
        return values[0];
    }

    TypePoint x() const
    {
        static_assert(dimension >= 1);
        return values[0];
    }

    TypePoint& y()
    {
        static_assert(dimension >= 2);
        return values[1];
    }

    TypePoint y() const
    {
        static_assert(dimension >= 2);
        return values[1];
    }

    TypePoint& z()
    {
        static_assert(dimension >= 3);
        return values[2];
    }

    TypePoint z() const
    {
        static_assert(dimension >= 3);
        return values[2];
    }

    TypePoint& value(int dimension_value)
    {
        assert(dimension_value >= 0 && dimension_value < dimension);
        return values[dimension_value];
    }

    TypePoint value(int dimension_value) const
    {
        assert(dimension_value >= 0 && dimension_value < dimension);
        return values[dimension_value];
    }

    Point& operator+=(const Point& other)
    {
        assert(other.size() == size());

        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](const TypePoint& a, const TypePoint& b) { return a + b; });

        return *this;
    }

    Point& operator-=(const Point& other)
    {
        assert(other.size() == size());

        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](const TypePoint& a, const TypePoint& b) { return a - b; });

        return *this;
    }

    Point& operator*=(const TypePoint scalar)
    {

        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](const float& v) { return v * scalar; });

        return *this;
    }

    Point& operator*=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](const TypePoint& a, const TypePoint& b) { return a * b; });

        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const TypePoint scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator-() const
    {
        Point result = *this;
        std::transform(result.values.begin(), result.values.end(), result.values.begin(),
                       [](const TypePoint& v) { return -v; });
        return result;
    }

    bool operator!=(const Point& other)
    {
        return std::any_of(values.begin(), values.end(),
                           [&other](TypePoint v1, TypePoint v2) { return v1 != v2; });
    }

    TypePoint length() const
    {
        return std::sqrt(std::accumulate(values.begin(), values.end(), 0.,
                                         [](float f1, float f2) { return f1 + f2 * f2; }));
    }

    TypePoint distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const TypePoint target_len = 1.0f)
    {
        const TypePoint current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const TypePoint max_len)
    {
        assert(max_len > 0);

        const TypePoint current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }

    std::string print_coordinates() const
    {
        std::string coordinates = "coordinates{ ";
        return std::transform_reduce(
                   values.begin(), values.end(), coordinates,
                   [](std::string s1, std::string s2) { return s1 + s2 + " "; },
                   [](TypePoint v) { return std::to_string(v); }) +
               "}";
    }

    static void test_generic_points()
    {
        Point<dimension, TypePoint> p1 { 2, 4, 6 };
        Point<dimension, TypePoint> p2 { 1, 3, 5 };
        auto p3 = p1 + p2;
        p3 -= p1;
        p1 += p2;
        p1 *= 3;
    }
};