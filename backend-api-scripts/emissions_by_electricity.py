import sys
import json
import http.client
import urllib.parse


def calculate_carbon_footprint(country_name, electricity_value, electricity_unit):
    # Configurare conexiune HTTPS
    conn = http.client.HTTPSConnection("carbonsutra1.p.rapidapi.com")

    # Pregătirea datelor de payload
    payload = {
        'country_name': country_name,
        'electricity_value': electricity_value,
        'electricity_unit': electricity_unit,
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
    conn.request("POST", "/electricity_estimate", encoded_payload, headers)

    # Obținerea răspunsului
    res = conn.getresponse()
    data = res.read()

    # Decodarea răspunsului
    result = json.loads(data.decode("utf-8"))

    # Extrage amprenta de carbon din răspuns
    carbon_footprint_kg = result['data']['co2e_kg']

    with open("total.txt", "a") as file:
        file.write(str(carbon_footprint_kg) + '\n')

    return carbon_footprint_kg


if __name__ == "__main__":
    # Citirea argumentelor din linia de comandă
    # if len(sys.argv) != 4:
    #    print("Utilizare: python carbon_sutra.py <country> <elec_value> <unit>")
    #    sys.exit(1)

    country_name = 'Romania'  # sys.argv[1]
    electricity_value = '3455'  # sys.argv[2]
    electricity_unit = 'kWh'  # sys.argv[3]

    # Calcularea amprentei de carbon
    carbon_footprint_kg = calculate_carbon_footprint(country_name, electricity_value, electricity_unit)

    # Returnarea rezultatului
    print(carbon_footprint_kg)

'''
double carbon_footprint_electricity.py() {
    // Parametrii de intrare pentru scriptul Python
    string country_name = "Romania";    // Țara
    string electricity_value = "3455";  // Valoarea consumului de electricitate
    string electricity_unit = "kWh";   // Unitatea de măsură

    // Crearea comenzii pentru a executa scriptul Python
    string command = "python3 carbon_footprint_electricity.py " 
                     + country_name + " "          // Țara
                     + electricity_value + " "    // Valoarea consumului
                     + electricity_unit;         // Unitatea de măsură

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