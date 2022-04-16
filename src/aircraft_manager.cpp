#include "aircraft_manager.hpp"

#include "aircraft.hpp"
#include "aircraft_crash.hpp"

#include <iostream>
#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    assert(aircraft != NULL);
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
                                   [this](auto& aircraft)
                                   {
                                       try
                                       {
                                           return !aircraft->update();
                                       } catch (AircraftCrash& exception)
                                       {
                                           this->nb_aicraft_crashed++;
                                           std::cerr << exception.what() << std::endl;
                                           return true;
                                       }
                                   }),
                    aircrafts.end());

    return true;
}

int AircraftManager::number_aircraft_in_airline(const std::string_view airline) const
{
    assert(!airline.empty());

    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [airline](const auto& aircraft)
                         { return aircraft->get_flight_num().substr(0, 2).compare(airline) == 0; });
}

int AircraftManager::get_required_fuel() const
{
    int required_fuel = 0;

    std::for_each(aircrafts.begin(), aircrafts.end(),
                  [&required_fuel](auto& aircraft)
                  {
                      if (aircraft->is_low_on_fuel() && aircraft->in_terminal())
                      {
                          required_fuel += (MAX_FUEL - aircraft->get_fuel());
                      }
                  });

    return required_fuel;
}