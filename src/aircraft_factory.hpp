#pragma once

#include "GL/texture.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "airport_type.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <string_view>
#include <unordered_set>

class AircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    std::unordered_set<std::string_view> aircraft_numbers;

    std::string new_aicraft_number() const;

public:
    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport);
    [[nodiscard]] std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);
    std::string airline(int index);

    // note: textures have to be initialized after initializing glut, so we'll need
    // our own init here
    inline void init_aircraft_types()
    {
        aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
        aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
        aircraft_types[2] = new AircraftType { .04f, .08f, .04f, MediaPath { "concorde_af.png" } };
    }
};