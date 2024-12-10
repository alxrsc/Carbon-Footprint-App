
import sys
import json
import http.client
import urllib.parse


def calculate_carbon_footprint(vehicle_type, fuel_type, distance_value, distance_unit):
    # Configurare conexiune HTTPS
    conn = http.client.HTTPSConnection("carbonsutra1.p.rapidapi.com")

    # Pregătirea datelor de payload
    payload = {
        'vehicle_type': vehicle_type,
        'fuel_type': fuel_type,
        'distance_value': distance_value,
        'distance_unit': distance_unit
    }

    # Codificarea payload-ului
    encoded_payload = urllib.parse.urlencode(payload)

    # Definirea header-urilor
    headers = {
        'x-rapidapi-key': "5d10ec62c3mshc305a7605de54b7p1ac4a0jsn6b52cfbed578",
        'x-rapidapi-host': "carbonsutra1.p.rapidapi.com",
        'Content-Type': "application/x-www-form-urlencoded",
        'Authorization': "Bearer fQ98oU704xFvsnXcQLVDbpeCJHPglG1DcxiMLKfpeNEMGumlbzVf1lCI6ZBx"
    }

    # Trimiterea cererii POST către API
    conn.request("POST", "/vehicle_estimate_by_type", encoded_payload, headers)

    # Obținerea răspunsului
    res = conn.getresponse()
    data = res.read()

    # Decodarea răspunsului
    result = json.loads(data.decode("utf-8"))

    # Extrage amprenta de carbon din răspuns
    carbon_footprint_kg = result['data']['co2e_kg']

    return carbon_footprint_kg


if __name__ == "__main__":
    # Citirea argumentelor din linia de comandă
    # if len(sys.argv) != 5:
    #    print("Utilizare: python carbon_sutra.py <make> <model> <dist> <unit>")
    #    sys.exit(1)

    vehicle_type = 'Motorbike-Size-Medium'  # sys.argv[1]
    fuel_type = 'Petrol'  # sys.argv[2]
    distance_value = '1000'  # sys.argv[3]
    distance_unit = 'km'  # sys.argv[4]

    # Calcularea amprentei de carbon
    carbon_footprint_kg = calculate_carbon_footprint(vehicle_type, fuel_type, distance_value, distance_unit)

    # Returnarea rezultatului
    print(carbon_footprint_kg)

'''
double get_emissions_by_vehicle_type() {
    string vehicle_type = "Motorbike-Size-Medium";      // Tipul
    string fuel_type = "Petrol";    // Carburant
    string distance = "1000";    // Distanța
    string unit = "km";         // Unitatea de măsură

    string command = "python3 emissions_by_motorcycle.py " + vehicle_type + " " + fuel_type + " " + distance + " " + unit;

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