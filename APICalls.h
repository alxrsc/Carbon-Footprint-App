//
// Created by Alexandru Roșca on 14.01.2025.
//

#ifndef CARBONFOOTPRINTAPP_APICALLS_H
#define CARBONFOOTPRINTAPP_APICALLS_H

#include <iostream>

using namespace std;

string get_emissions_by_car_fuel(string fuel_usage, string fuel_type, string fuel_value);
string get_emissions_by_electricity(string country_name, string electricity_value, string electricity_unit);
string get_carbon_footprint_flight(string iata_airport_from, string iata_airport_to, string flight_class, string round_trip, string number_of_passengers);
string get_emissions_by_vehicle_type(string vehicle_type, string fuel_type, string distance, string unit);
string get_emissions_by_house_fuel(string fuel_usage, string fuel_type, string fuel_value);
string get_emissions_by_motorcycle(string vehicle_type, string fuel_type, string distance, string unit);
string get_emissions_by_publicTransport(string vehicle_type, string fuel_type, string distance, string unit);
string get_emissions_by_vehicle_model(string make, string model, string distance, string unit);
string get_emissions_by_hotelStay(string country_code, string city_name, string hotel_rating, string number_of_nights, string number_of_rooms);

#endif //CARBONFOOTPRINTAPP_APICALLS_H
