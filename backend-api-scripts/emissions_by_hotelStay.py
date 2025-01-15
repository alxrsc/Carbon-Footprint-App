import sys
import json
import http.client
import urllib.parse

def calculate_carbon_footprint(country_code, city_name, hotel_rating, number_of_nights, number_of_rooms):
    # Configurare conexiune HTTPS
    conn = http.client.HTTPSConnection("carbonsutra1.p.rapidapi.com")

    # Pregătirea datelor de payload
    payload = {
        'country_code': country_code,
        'city_name': city_name,
        'hotel_rating': hotel_rating,
        'number_of_nights': number_of_nights,
        'number_of_rooms': number_of_rooms
    }

    # Codificarea payload-ului
    encoded_payload = urllib.parse.urlencode(payload)

    # Definirea header-urilor
    headers = {
        'x-rapidapi-key': "5d10ec62c3mshc305a7605de54b7p1ac4a0jsn6b52cfbed578",
        'x-rapidapi-host': "carbonsutra1.p.rapidapi.com",
        'Content-Type': "application/x-www-form-urlencoded",
        'Authorization': "Bearer fQ98oU704xFvsnXcQLVDbpeNEMGumlbzVf1lCI6ZBx"
    }

    try:
        # Trimiterea cererii POST către API
        conn.request("POST", "/hotel_estimate", encoded_payload, headers)

        # Obținerea răspunsului
        res = conn.getresponse()
        data = res.read()

        # Decodarea răspunsului
        result = json.loads(data.decode("utf-8"))

        # Verificarea existenței cheilor necesare
        if 'data' in result and 'co2e_kg' in result['data']:
            # Extrage amprenta de carbon din răspuns
            carbon_footprint_kg = result['data']['co2e_kg']

            with open("total.txt", "a") as file:
                file.write(str(carbon_footprint_kg) + '\n')

            return carbon_footprint_kg
        else:
            print("Nu există date disponibile pentru această cerere.")
            return None  # Sau poți returna 0 sau altă valoare

    except json.JSONDecodeError:
        print("Eroare la decodarea răspunsului JSON.")
        return None
    except Exception as e:
        print(f"A apărut o eroare: {e}")
        return None

if __name__ == "__main__":
    country_code = 'QA'  # sys.argv[1]
    city_name = 'Doha'  # sys.argv[2]
    hotel_rating = 5  # sys.argv[3]
    number_of_nights = 5  # sys.argv[4]
    number_of_rooms = 1

    # Calcularea amprentei de carbon
    carbon_footprint_kg = calculate_carbon_footprint(country_code, city_name, hotel_rating, number_of_nights, number_of_rooms)

    # Returnarea rezultatului
    if carbon_footprint_kg is not None:
        print(f"Amprenta de carbon: {carbon_footprint_kg} kg CO₂")
    else:
        print("Nu s-au putut obține informațiile despre amprenta de carbon.")
    

'''
double get_emissions_by_vehicle_type() {
    string vehicle_type = "Train-National";      // Tipul
    string fuel_type = "Diesel";    // Carburant
    string distance = "4500";    // Distanța
    string unit = "km";         // Unitatea de măsură

    string command = "python3 emissions_by_publicTransport.py " + vehicle_type + " " + fuel_type + " " + distance + " " + unit;

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
}
'''