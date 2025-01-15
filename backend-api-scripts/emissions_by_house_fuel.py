import sys
import json
import http.client
import urllib.parse

def calculate_carbon_footprint(fuel_usage, fuel_type, fuel_value):
    try:
        # Configurare conexiune HTTPS
        conn = http.client.HTTPSConnection("carbonsutra1.p.rapidapi.com")

        # Pregătirea datelor de payload
        payload = {
            'fuel_usage': fuel_usage,
            'fuel_name': fuel_type,
            'fuel_value': fuel_value,
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
        conn.request("POST", "/fuel_estimate", encoded_payload, headers)

        # Obținerea răspunsului
        res = conn.getresponse()
        data = res.read()

        # Decodarea răspunsului
        result = json.loads(data.decode("utf-8"))

        # Verificarea structurii răspunsului și extragerea datelor
        if 'data' in result and 'co2e_kg' in result['data']:
            carbon_footprint_kg = result['data']['co2e_kg']

            with open("total.txt", "a") as file:
                file.write(str(carbon_footprint_kg) + '\n')

            return result['data']['co2e_kg']
        else:
            raise ValueError("Răspuns invalid de la API.")

    except Exception as e:
        return {"error": str(e)}

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print(json.dumps({"error": "Utilizare: python script.py <fuel_usage> <fuel_type> <fuel_value>"}))
        sys.exit(1)

    # Citirea argumentelor din linia de comandă
    fuel_usage = sys.argv[1]
    fuel_type = sys.argv[2]
    fuel_value = sys.argv[3]

    # Calcularea amprentei de carbon
    result = calculate_carbon_footprint(fuel_usage, fuel_type, fuel_value)

    # Returnarea rezultatului în format JSON
    if isinstance(result, dict) and "error" in result:
        print(json.dumps(result))
    else:
        print(json.dumps({"co2e_kg": result}))
