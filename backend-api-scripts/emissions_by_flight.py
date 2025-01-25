import sys
import json
import http.client
import urllib.parse

def calculate_carbon_footprint_flight(iata_airport_from, iata_airport_to, flight_class, round_trip, number_of_passengers):
    # Configurare conexiune HTTPS
    conn = http.client.HTTPSConnection("carbonsutra1.p.rapidapi.com")

    # Pregătirea datelor de payload
    payload = {
        'iata_airport_from': iata_airport_from,
        'iata_airport_to': iata_airport_to,
        'flight_class': flight_class,  # Clasa de zbor
        'round_trip': round_trip,  # Dus-întors
        'number_of_passengers': number_of_passengers
    }

    # Codificarea payload-ului
    encoded_payload = urllib.parse.urlencode(payload)

    # Definirea header-urilor
    headers = {
        'x-rapidapi-key': "b4475b47cemsh84ab8e10c393e19p129f25jsnfd1d45741f35",
        'x-rapidapi-host': "carbonsutra1.p.rapidapi.com",
        'Content-Type': "application/x-www-form-urlencoded",
        'Authorization': "Bearer fQ98oU704xFvsnXcQLVDbpeCJHPglG1DcxiMLKfpeNEMGumlbzVf1lCI6ZBx"
    }

    # Trimiterea cererii POST către API
    conn.request("POST", "/flight_estimate", encoded_payload, headers)

    # Obținerea răspunsului
    res = conn.getresponse()
    data = res.read()

    # Decodarea răspunsului
    result = json.loads(data.decode("utf-8"))

    # Extrage doar cantitatea de carbon în kg
    carbon_footprint_kg = result['data']['co2e_kg']

    return carbon_footprint_kg


if __name__ == "__main__":
    # Citirea argumentelor din linia de comandă
    if len(sys.argv) != 6:
       print("Utilizare: python carbon_sutra.py <IATA_from> <IATA_to> <flight_class> <round_trip(Y/N)> <number_of_pass>")
       sys.exit(1)

    # Parametrii de intrare
    iata_airport_from = sys.argv[1]     # Aeroportul de plecare (ex. București)
    iata_airport_to = sys.argv[2]       # Aeroportul de sosire (ex. Malta)
    flight_class = sys.argv[3]       # Clasa de zbor
    round_trip = sys.argv[4]          # Dus-întors
    number_of_passengers = sys.argv[5]    # Numărul de pasageri

    # Calcularea amprentei de carbon
    carbon_footprint_kg = calculate_carbon_footprint_flight(iata_airport_from, iata_airport_to, flight_class, round_trip, number_of_passengers)

    # Afișarea rezultatului
    print(carbon_footprint_kg)

'''
double get_carbon_footprint_flight() {
    string iata_airport_from = "OTP";        // Aeroportul de plecare (ex. București)
    string iata_airport_to = "MLA";          // Aeroportul de sosire (ex. Malta)
    string flight_class = "economy";         // Clasa de zbor
    string round_trip = "Y";                 // Tipul de zbor (Dus-întors)
    string number_of_passengers = "50";      // Numărul de pasageri

    // Crearea comenzii pentru a executa scriptul Python
    string command = "python3 carbon_footprint_flight.py "
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
        return 1;
    }

    // Citirea rezultatului din stdout
    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    fclose(pipe);

    return result;

    return 0;
}
'''

# import sys
# import json
# import http.client
# import urllib.parse
#
# def calculate_carbon_footprint_flight(iata_airport_from, iata_airport_to, flight_class, round_trip, number_of_passengers):
#     # Configurare conexiune HTTPS
#     conn = http.client.HTTPSConnection("carbonsutra1.p.rapidapi.com")
#
#     # Pregătirea datelor de payload
#     payload = {
#         'iata_airport_from': iata_airport_from,
#         'iata_airport_to': iata_airport_to,
#         'flight_class': flight_class,  # Clasa de zbor
#         'round_trip': round_trip,  # Dus-întors
#         'number_of_passengers': number_of_passengers
#     }
#
#     # Codificarea payload-ului
#     encoded_payload = urllib.parse.urlencode(payload)
#
#     # Definirea header-urilor
#     headers = {
#         'x-rapidapi-key': "5d10ec62c3mshc305a7605de54b7p1ac4a0jsn6b52cfbed578",
#         'x-rapidapi-host': "carbonsutra1.p.rapidapi.com",
#         'Content-Type': "application/x-www-form-urlencoded",
#         'Authorization': "Bearer fQ98oU704xFvsnXcQLVDbpeCJHPglG1DcxiMLKfpeNEMGumlbzVf1lCI6ZBx"
#     }
#
#     # Trimiterea cererii POST către API
#     conn.request("POST", "/flight_estimate", encoded_payload, headers)
#
#     # Obținerea răspunsului
#     res = conn.getresponse()
#     data = res.read()
#
#     # Decodarea răspunsului
#     result = json.loads(data.decode("utf-8"))
#
#     # Extrage doar cantitatea de carbon în kg
#     try:
#         carbon_footprint_kg = result['data']['co2e_kg']
#     except KeyError:
#         print("Eroare: Răspunsul API nu conține datele așteptate.", file=sys.stderr)
#         sys.exit(1)
#
#     # Închiderea conexiunii
#     conn.close()
#     return carbon_footprint_kg
#
#
# if __name__ == "__main__":
#     # Citirea argumentelor din linia de comandă
#     iata_airport_from = sys.argv[1]
#     iata_airport_to = sys.argv[2]
#     flight_class = sys.argv[3]
#     round_trip = sys.argv[4]
#     number_of_passengers = sys.argv[5]
#
#     # Calcularea amprentei de carbon
#     carbon_footprint_kg = calculate_carbon_footprint_flight(iata_airport_from, iata_airport_to, flight_class, round_trip, number_of_passengers)
#
#     # Afișarea rezultatului
#     print(carbon_footprint_kg)
