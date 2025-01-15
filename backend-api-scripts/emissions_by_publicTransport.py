
import sys
import json
import http.client
import urllib.parse


def calculate_carbon_footprint(vehicle_type, fuel_type, distance_value, distance_unit):
    # Configure HTTPS connection
    conn = http.client.HTTPSConnection("carbonsutra1.p.rapidapi.com")

    # Prepare payload
    payload = {
        'vehicle_type': vehicle_type,
        'fuel_type': fuel_type,
        'distance_value': distance_value,
        'distance_unit': distance_unit
    }

    # Encode payload
    encoded_payload = urllib.parse.urlencode(payload)

    # Define headers
    headers = {
        'x-rapidapi-key': "5d10ec62c3mshc305a7605de54b7p1ac4a0jsn6b52cfbed578",
        'x-rapidapi-host': "carbonsutra1.p.rapidapi.com",
        'Content-Type': "application/x-www-form-urlencoded",
        'Authorization': "Bearer fQ98oU704xFvsnXcQLVDbpeCJHPglG1DcxiMLKfpeNEMGumlbzVf1lCI6ZBx"
    }

    # Send POST request
    conn.request("POST", "/vehicle_estimate_by_type", encoded_payload, headers)

    # Get response
    res = conn.getresponse()
    data = res.read()

    # Decode and parse response
    result = json.loads(data.decode("utf-8"))
    print("API Response:", result)  # Debugging

    # Extract carbon footprint
    if 'data' in result and 'co2e_kg' in result['data']:
        carbon_footprint_kg = result['data']['co2e_kg']
        return carbon_footprint_kg
    else:
        print("Error in API response:", result)
        sys.exit(1)


if __name__ == "__main__":
    # Read command-line arguments
    if len(sys.argv) != 5:
        print("Usage: python carbon_sutra.py <vehicle_type> <fuel_type> <distance_value> <distance_unit>")
        sys.exit(1)

    vehicle_type = sys.argv[1]
    fuel_type = sys.argv[2]
    distance_value = sys.argv[3]
    distance_unit = sys.argv[4]

    # Calculate carbon footprint
    try:
        carbon_footprint_kg = calculate_carbon_footprint(vehicle_type, fuel_type, distance_value, distance_unit)
        print(carbon_footprint_kg)
    except Exception as e:
        print("An error occurred:", e)
        sys.exit(1)

'''
double get_emissions_by_vehicle_type() {
    string vehicle_type = "Train-National";      // Tipul
    string fuel_type = "Diesel";    // Carburant
    string distance = "4500";    // Distanța
    string unit = "km";         // Unitatea de măsură

    string command = "python3 emissions_by_publicTransport.py " + vehicle_type + " " + fuel_type + " " + distance + " " + unit;

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
}
'''