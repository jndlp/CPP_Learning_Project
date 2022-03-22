#include "aircraft_manager.hpp"

#include "aircraft.hpp"

#include <iostream>
#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](auto& a1, auto& a2)
              {
                  if ((a1->has_terminal() && a2->has_terminal()) ||
                      (!a1->has_terminal() && !a2->has_terminal()))
                  {
                      return a1->get_fuel() > a2->get_fuel();
                  }
                  else if (a1->has_terminal() && !a2->has_terminal())
                  {
                      return true;
                  }
                  else
                  {
                      return false;
                  }
              });

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

int AircraftManager::get_required_fuel()
{
    int required_fuel = 0;

    std::for_each(aircrafts.begin(), aircrafts.end(),
                  [&required_fuel](auto& aircraft)
                  {
                      if (aircraft->is_low_on_fuel() && aircraft->in_terminal())
                      {
                          required_fuel += (3000 - aircraft->get_fuel());
                      }
                  });

    return required_fuel;
}