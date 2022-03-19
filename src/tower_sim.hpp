#pragma once

#include "aircraft_factory.hpp"
#include "aircraft_manager.hpp"

#include <memory>

class Aircraft;
class Airport;

struct AircraftType;

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    AircraftManager aircraft_manager;
    AircraftFactory aircraft_factory;

    void create_keystrokes();
    void display_help() const;

    void init_airport();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
