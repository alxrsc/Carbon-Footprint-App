import requests

MY_API_KEY = "H83G22JV8S0JB02B5F496EFAFC"
activity_id = "41aa6bd4-0576-41b7-8ab6-9edaab9632dd"  # ID-ul pentru Clothing
region = "EU"  # Poți modifica cu regiunea dorită (de ex. EU, US, etc.)
data_version = "^3"

# Definirea sumei de bani cheltuite (exemplu: 100 USD)
spent_money = 100  # Poți înlocui cu suma dorită
currency = "usd"  # Sau EUR, GBP, etc.

url = "https://api.climatiq.io/data/v1/estimate"

# Parametrii necesari pentru estimare
parameters = {
    "money": spent_money,
    "money_unit": currency  # Corect: specifică unitatea ca "money_unit"
}

json_body = {
    "emission_factor": {
        "activity_id": activity_id,
        "data_version": data_version,
        "region": region,
    },
    "parameters": parameters
}

headers = {"Authorization": f"Bearer {MY_API_KEY}"}

# Trimiterea cererii POST pentru estimarea amprentei de carbon
response = requests.post(url, json=json_body, headers=headers)

# Verificarea și afișarea rezultatului
if response.status_code == 200:
    result = response.json()
    print("Carbon footprint estimation:", result)
else:
    print("Error:", response.status_code, response.text)