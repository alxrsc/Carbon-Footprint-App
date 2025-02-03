import sys
import json
import http.client
import urllib.parse

def calculate_carbon_footprint(vehicle_type, distance_value, distance_unit):
    try:
        # Configurare conexiune HTTPS
        conn = http.client.HTTPSConnection("carbonsutra1.p.rapidapi.com")

        # Pregătirea datelor de payload
        payload = {
            'vehicle_type': vehicle_type,
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
        conn.request("POST", "/vehicle_estimate_by_type", encoded_payload, headers)

        # Obținerea răspunsului
        res = conn.getresponse()
        data = res.read()

        # Decodarea răspunsului
        result = json.loads(data.decode("utf-8"))

        # Verificarea răspunsului pentru date valide
        if 'data' in result and 'co2e_kg' in result['data']:
            carbon_footprint_kg = result['data']['co2e_kg']

            # Salvarea rezultatului într-un fișier
            with open("total.txt", "a") as file:
                file.write(str(carbon_footprint_kg) + '\n')

            return carbon_footprint_kg
        else:
            print("Nu există date disponibile pentru această cerere.")
            return None

    except Exception as e:
        print(f"A apărut o eroare: {e}")
        return None

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Utilizare: python emissions_by_publicTransport.py <vehicle_type> <distance_value> <distance_unit>")
        sys.exit(1)

    vehicle_type = sys.argv[1]
    distance_value = sys.argv[2]
    distance_unit = sys.argv[3]

    # Calcularea amprentei de carbon
    carbon_footprint_kg = calculate_carbon_footprint(vehicle_type, distance_value, distance_unit)


    # Returnarea rezultatului
    if carbon_footprint_kg is not None:
        print(carbon_footprint_kg)
    else:
        print(json.dumps({"error": "Nu s-au putut obține informațiile despre amprenta de carbon."}))
