import sys
import json
import http.client
import urllib.parse

def calculate_carbon_footprint(vehicle_make, vehicle_model, distance_value, distance_unit):
    try:
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
            'x-rapidapi-key': "5d10ec62c3mshc305a7605de54b7p1ac4a0jsn6b52cfbed578",
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

        # Verificarea răspunsului pentru date valide
        if 'data' in result and 'co2e_kg' in result['data']:
            carbon_footprint_kg = result['data']['co2e_kg']
            return  carbon_footprint_kg
        else:
            return {"error": "No data available for this request."}

    except Exception as e:
        return {"error": str(e)}

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print(json.dumps({"error": "Usage: python emissions_by_vehicle_model.py <vehicle_make> <vehicle_model> <distance_value> <distance_unit>"}))
        sys.exit(1)

    vehicle_make = sys.argv[1]
    vehicle_model = sys.argv[2]
    distance_value = sys.argv[3]
    distance_unit = sys.argv[4]

    # Calcularea amprentei de carbon
    result = calculate_carbon_footprint(vehicle_make, vehicle_model, distance_value, distance_unit)

    # Salvarea rezultatului în fișier
    with open("total.txt", "a") as file:
        file.write(f"{result}\n")

    # Returnarea rezultatului
    print(result)
