
import sys
import json
import http.client
import urllib.parse


def calculate_carbon_footprint(fuel_usage, fuel_type, fuel_value):
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
        'x-rapidapi-key': "b4475b47cemsh84ab8e10c393e19p129f25jsnfd1d45741f35",
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

    # Extrage amprenta de carbon din răspuns
    carbon_footprint_kg = result['data']['co2e_kg']

    return carbon_footprint_kg



if __name__ == "__main__":
    # Citirea argumentelor din linia de comandă
    if len(sys.argv) != 4:
        print("DEBUG: sys.argv =", sys.argv)
        sys.exit(1)

    fuel_usage = sys.argv[1]
    fuel_type = sys.argv[2]
    fuel_value = sys.argv[3]

    # Calcularea amprentei de carbon
    carbon_footprint_kg = calculate_carbon_footprint(fuel_usage, fuel_type, fuel_value)

    # Returnarea rezultatului
    print(carbon_footprint_kg)


