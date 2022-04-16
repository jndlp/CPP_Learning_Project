#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int nb_aicraft_crashed = 0;

public:
    void add(std::unique_ptr<Aircraft> aircraft);
    bool update() override;
    int get_required_fuel() const;
    int number_aircraft_in_airline(const std::string_view airline) const;
    int number_aircraft_crash() const { return nb_aicraft_crashed; }
};
