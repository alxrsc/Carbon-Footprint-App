import sys
import json
import http.client
import urllib.parse


def calculate_carbon_footprint(vehicle_make, vehicle_model, distance_value, distance_unit):
    # Configurare conexiune HTTPS
    conn = http.client.HTTPSConnection("carbonsutra1.p.rapidapi.com")

    # Pregătirea datelor de payload
    payload = {
        'vehicle_make': vehicle_make,
        'vehicle_model': vehicle_model,
        'distance_value': distance_value,
        'distance_unit': distance_unit
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
    conn.request("POST", "/vehicle_estimate_by_model", encoded_payload, headers)

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
    #if len(sys.argv) != 5:
    #    print("Utilizare: python carbon_sutra.py <make> <model> <dist> <unit>")
    #    sys.exit(1)

    vehicle_make = sys.argv[1]
    vehicle_model = sys.argv[2]
    distance_value = sys.argv[3]
    distance_unit = 'km' #sys.argv[4]

    # Calcularea amprentei de carbon
    carbon_footprint_kg = calculate_carbon_footprint(vehicle_make, vehicle_model, distance_value, distance_unit)

    with open("total.txt", "a") as file:
        file.write(str(carbon_footprint_kg) + '\n')

    # Returnarea rezultatului
    print(carbon_footprint_kg)

'''
double get_emissions_by_vehicle_model() {
    string make = "Lexus";      // Marca
    string model = "RX 300";    // Modelul
    string distance = "421";    // Distanța
    string unit = "km";         // Unitatea de măsură
    
    string command = "python3 emissions_by_vehicle_model.py " + make + " " + model + " " + distance + " " + unit;

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