#include "aircraft_factory.hpp"

#include <string>
#include <unordered_set>

std::string AircraftFactory::new_aicraft_number() const
{
    std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));

    while (aircraft_numbers.find(flight_number) != aircraft_numbers.end())
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }

    return flight_number;
}

[[nodiscard]] std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type,
                                                                         Airport* airport)
{
    assert(airport); // make sure the airport is initialized before creating aircraft
    const std::string flight_number = new_aicraft_number();
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    aircraft_numbers.emplace(flight_number);
    return std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower());
}

[[nodiscard]] std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Airport* airport)
{
    return create_aircraft(*(aircraft_types[rand() % 3]), airport);
}

std::string AircraftFactory::airline(int index)
{
    assert(index >= 0 && index < 8);
    return airlines[index];
}