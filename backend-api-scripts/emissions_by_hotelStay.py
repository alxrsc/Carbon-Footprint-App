import sys
import json
import http.client
import urllib.parse
import io

# Configurează consola pentru UTF-8
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

def calculate_carbon_footprint(country_code, city_name, hotel_rating, number_of_nights, number_of_rooms):
    try:
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
            'x-rapidapi-key': "b4475b47cemsh84ab8e10c393e19p129f25jsnfd1d45741f35",
            'x-rapidapi-host': "carbonsutra1.p.rapidapi.com",
            'Content-Type': "application/x-www-form-urlencoded",
            'Authorization': "Bearer fQ98oU704xFvsnXcQLVDbpeNEMGumlbzVf1lCI6ZBx"
        }

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

            # Salvează rezultatul într-un fișier
            with open("total.txt", "a", encoding="utf-8") as file:
                file.write(str(carbon_footprint_kg) + '\n')

            return carbon_footprint_kg
        else:
            return {"error": "Invalid response structure or no data available."}

    except Exception as e:
        return {"error": str(e)}


if __name__ == "__main__":
    # Verificarea numărului de argumente
    if len(sys.argv) != 6:
        print(json.dumps({"error": "Usage: python emissions_by_hotelStay.py <country_code> <city_name> <hotel_rating> <number_of_nights> <number_of_rooms>"}))
        sys.exit(1)

    # Citirea argumentelor din linia de comandă
    country_code = sys.argv[1]
    city_name = sys.argv[2]
    hotel_rating = sys.argv[3]
    number_of_nights = sys.argv[4]
    number_of_rooms = sys.argv[5]

    # Calcularea amprentei de carbon
    result = calculate_carbon_footprint(country_code, city_name, hotel_rating, number_of_nights, number_of_rooms)

    # Returnarea rezultatului
    if isinstance(result, dict) and "error" in result:
        print(json.dumps(result))
    else:
        print(json.dumps({"co2e_kg": result}))
