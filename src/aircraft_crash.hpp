#pragma once

#include "geometry.hpp"
#include "waypoint.hpp"

#include <stdexcept>
#include <string_view>

class AircraftCrash : public std::runtime_error
{
public:
    AircraftCrash(const std::string_view& flight_number, const Point3D& pos, const Point3D& speed,
                  const std::string_view& cause) :
        std::runtime_error { build_message(flight_number, pos, speed, cause) }
    {}

private:
    static std::string build_message(const std::string_view& flight_number, const Point3D& pos,
                                     const Point3D& speed, const std::string_view& cause)
    {
        assert(!flight_number.empty());
        assert(!cause.empty());

        std::string message;

        message += "Error: The Aircraft ";
        message += flight_number;
        message += " spewed at " + std::to_string(speed.length());
        message += " at coordinates [" + std::to_string(pos.x()) + "," + std::to_string(pos.y()) + "," +
                   std::to_string(pos.z()) + "]. Cause: ";
        message += cause;

        return message;
    }
};