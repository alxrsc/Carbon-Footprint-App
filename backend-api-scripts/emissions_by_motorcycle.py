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

    try:
        # Trimiterea cererii POST către API
        conn.request("POST", "/vehicle_estimate_by_type", encoded_payload, headers)

        # Obținerea răspunsului
        res = conn.getresponse()
        data = res.read()

        # Decodarea răspunsului
        result = json.loads(data.decode("utf-8"))

        # Verificare și extragere amprenta de carbon
        if 'data' in result and 'co2e_kg' in result['data']:
            carbon_footprint_kg = result['data']['co2e_kg']
            return carbon_footprint_kg
        else:
            raise ValueError("Răspuns invalid de la API")

    except Exception as e:
        return {"error": str(e)}

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print(json.dumps({"error": "Utilizare: python emissions_by_motorcycle.py <vehicle_type> <fuel_type> <distance_value> <distance_unit>"}))
        sys.exit(1)

    # Citirea argumentelor din linia de comandă
    vehicle_type = sys.argv[1]
    fuel_type = sys.argv[2]
    distance_value = sys.argv[3]
    distance_unit = sys.argv[4]

    # Calcularea amprentei de carbon
    result = calculate_carbon_footprint(vehicle_type, fuel_type, distance_value, distance_unit)

    # Returnarea rezultatului în format JSON
    if isinstance(result, dict) and "error" in result:
        print(json.dumps(result))
    else:
        print(json.dumps({"co2e_kg": result}))
