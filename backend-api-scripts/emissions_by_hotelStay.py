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
            return carbon_footprint_kg
        else:
            return None  # Sau poți returna 0 sau altă valoare

    except json.JSONDecodeError:
        return None
    except Exception as e:
        return None

if __name__ == "__main__":
    if len(sys.argv) < 6:
        print(json.dumps({"error": "Insufficient arguments provided."}))
        sys.exit(1)

    country_code = sys.argv[1]
    city_name = sys.argv[2]
    hotel_rating = int(sys.argv[3])
    number_of_nights = int(sys.argv[4])
    number_of_rooms = int(sys.argv[5])

    # Calcularea amprentei de carbon
    carbon_footprint_kg = calculate_carbon_footprint(
        country_code, city_name, hotel_rating, number_of_nights, number_of_rooms
    )

    # Returnarea rezultatului
    if carbon_footprint_kg is not None:
        print(json.dumps({"co2e_kg": carbon_footprint_kg}))
    else:
        print(json.dumps({"error": "Failed to calculate carbon footprint."}))
