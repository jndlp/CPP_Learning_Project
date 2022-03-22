#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <algorithm>
#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    void add(std::unique_ptr<Aircraft> aircraft);
    bool update() override;
    int get_required_fuel();
    void number_aircraft_in_airline(const std::string& airline) const;
};
