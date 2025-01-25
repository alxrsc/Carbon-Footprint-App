//
// Created by Alexandru Roșca on 14.01.2025.
//

#include "APICalls.h"

string get_emissions_by_car_fuel(string fuel_usage, string fuel_type, string fuel_value) {

    string command = "python3 ../backend-api-scripts/emissions_by_car_fuel.py " + fuel_usage + " " + fuel_type + " " + fuel_value;

    // Executarea comenzii și obținerea rezultatelor
    char buffer[128];
    string result = "";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Eroare la executarea scriptului Python!" << endl;
        return "Error";
    }

    // Citirea rezultatului din stdout
    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    fclose(pipe);

    return result;
}

string get_emissions_by_electricity(string country_name, string electricity_value, string electricity_unit) {
    // Crearea comenzii pentru a executa scriptul Python
    string command = "python3 ../backend-api-scripts/emissions_by_electricity.py "
                     + country_name + " "          // Țara
                     + electricity_value + " "    // Valoarea consumului
                     + electricity_unit;         // Unitatea de măsură

    // Executarea comenzii și obținerea rezultatelor
    char buffer[128];
    string result = "";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Eroare la executarea scriptului Python!" << endl;
        return "Error";
    }

    // Citirea rezultatului din stdout
    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    fclose(pipe);

    return result;
}

string get_carbon_footprint_flight(string iata_airport_from, string iata_airport_to, string flight_class, string round_trip, string number_of_passengers) {
    // Crearea comenzii pentru a executa scriptul Python
    string command = "python3 ../backend-api-scripts/emissions_by_flight.py "
                     + iata_airport_from + " "  // Aeroportul de plecare
                     + iata_airport_to + " "    // Aeroportul de sosire
                     + flight_class + " "       // Clasa de zbor
                     + round_trip + " "         // Tipul de zbor
                     + number_of_passengers;    // Numărul de pasageri

    // Executarea comenzii și obținerea rezultatelor
    char buffer[128];
    string result = "";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Eroare la executarea scriptului Python!" << endl;
        return "Error";
    }

    // Citirea rezultatului din stdout
    while (fgets(buffer, sizeof(buffer), pipe)) {
        cout << "Buffer " << buffer << endl;
        result += buffer;
    }

    fclose(pipe);

    return result;
}

string get_emissions_by_vehicle_type(string vehicle_type, string fuel_type, string distance, string unit) {

    string command = "python3 ../backend-api-scripts/emissions_by_publicTransport.py " + vehicle_type + " " + fuel_type + " " + distance + " " + unit;

    // Executarea comenzii și obținerea rezultatelor
    char buffer[128];
    string result = "";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Eroare la executarea scriptului Python!" << endl;
        return "Error";
    }

    // Citirea rezultatului din stdout
    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    fclose(pipe);

    return result;
}

string get_emissions_by_house_fuel(string fuel_usage, string fuel_type, string fuel_value) {
    string command = "python3 ../backend-api-scripts/emissions_by_house_fuel.py " + fuel_usage + " " + fuel_type + " " + fuel_value;

    // Executarea comenzii și obținerea rezultatelor
    char buffer[128];
    string result = "";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Eroare la executarea scriptului Python!" << endl;
        return "Error";
    }

    // Citirea rezultatului din stdout
    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    fclose(pipe);

    return result;
}

string get_emissions_by_motorcycle(string vehicle_type, string fuel_type, string distance, string unit) {

    string command = "python3 ../backend-api-scripts/emissions_by_motorcycle.py " + vehicle_type + " " + fuel_type + " " + distance + " " + unit;

    // Executarea comenzii și obținerea rezultatelor
    char buffer[128];
    string result = "";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Eroare la executarea scriptului Python!" << endl;
        return "Error";
    }

    // Citirea rezultatului din stdout
    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    fclose(pipe);

    return result;
}

string get_emissions_by_publicTransport(string vehicle_type, string fuel_type, string distance, string unit) {

    string command = "python3 ../backend-api-scripts/emissions_by_publicTransport.py " + vehicle_type + " " + fuel_type + " " + distance + " " + unit;

//    cout << command << endl;

    // Executarea comenzii și obținerea rezultatelor
    char buffer[128];
    string result = "";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Eroare la executarea scriptului Python!" << endl;
        return "Error";
    }

    // Citirea rezultatului din stdout
    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    fclose(pipe);

    return result;
}

string get_emissions_by_vehicle_model(string make, string model, string distance, string unit) {
    // Verificăm dacă parametrii sunt valizi
    // adaugam caracterul de escape pentru spatiu
    for(int i = 0; i < make.size(); i++) {
        if(make[i] == ' ') {
            make.insert(i, "\\");
            i++;
        }
    }

    for(int i = 0; i < model.size(); i++) {
        if(model[i] == ' ') {
            model.insert(i, "\\");
            i++;
        }
    }

    cout << make << " " << model << " " << distance << " " << unit << endl;

    // Construim comanda pentru a apela scriptul Python
    string command = "python3 ../backend-api-scripts/emissions_by_vehicle_model.py " + make + " " + model + " " + distance + " " + unit;

    // Buffer pentru citirea rezultatului
    char buffer[128];
    string result;

    // Deschidem un pipe pentru executarea comenzii
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Eroare la executarea scriptului Python!" << endl;
        return "Error";
    }

    // Citim răspunsul din stdout
    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    // Închidem pipe-ul
    int returnCode = pclose(pipe);
    if (returnCode != 0) {
        cerr << "Script Python a returnat un cod de eroare: " << returnCode << endl;
        return "Error";
    }

    // Eliminăm spațiile albe suplimentare din răspuns
    result.erase(result.find_last_not_of(" \n\r\t") + 1);

    return result;
}

//double get_emissions_by_vehicle_type() {
//    string vehicle_type = "Car-Type-Mini";      // Tipul
//    string fuel_type = "Diesel";    // Carburant
//    string distance = "421";    // Distanța
//    string unit = "km";         // Unitatea de măsură
//
//    string command = "python3 backend-api-scripts/emissions_by_vehicle_type.py " + vehicle_type + " " + fuel_type + " " + distance + " " + unit;
//
//    // Executarea comenzii și obținerea rezultatelor
//    char buffer[128];
//    string result = "";
//
//    FILE* pipe = popen(command.c_str(), "r");
//    if (!pipe) {
//        cerr << "Eroare la executarea scriptului Python!" << endl;
//        return 1;
//    }
//
//    // Citirea rezultatului din stdout
//    while (fgets(buffer, sizeof(buffer), pipe)) {
//        result += buffer;
//    }
//
//    fclose(pipe);
//
//    return stoi(result);
//}