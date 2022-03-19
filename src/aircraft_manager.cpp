#include "aircraft_manager.hpp"

#include <iostream>
#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](auto& aircraft) { return !aircraft->update(); }),
                    aircrafts.end());

    return true;
}

void AircraftManager::number_aircraft_in_airline(const std::string& airline) const
{
    const auto cnt = std::count_if(aircrafts.begin(), aircrafts.end(),
                                   [airline](const auto& aircraft)
                                   { return aircraft->get_flight_num().substr(0, 2).compare(airline) == 0; });
    std::cout << "Number of Aircraft in Airline " << airline << ": " << cnt << std::endl;
}