import paho.mqtt.client as mqtt
import time
import json

# MQTT broker configuration
broker_address = "localhost"  # Update with your MQTT broker address

# Example sensor readings for device 1
smoke_value_1 = 110
gas_value_1 = 10
temperature_value_1 = 25.3
radiation_value_1 = 7.2
latitude_1 = 123.456  # Replace with actual latitude
longitude_1 = 789.012  # Replace with actual longitude
battery_level_1 = 75  # Replace with actual battery level

# Example sensor readings for device 2
smoke_value_2 = 110
gas_value_2 = 110
temperature_value_2 = 24.5
radiation_value_2 = 6.5
latitude_2 = 987.654  # Replace with actual latitude
longitude_2 = 321.098  # Replace with actual longitude
battery_level_2 = 85  # Replace with actual battery level

# Create a dictionary to store sensor values for device 1
sensor_data_1 = {
    "device_id": 1,
    "gas": gas_value_1,
    "smoke": smoke_value_1,
    "temperature": temperature_value_1,
    "radiation": radiation_value_1,
    "latitude": latitude_1,
    "longitude": longitude_1,
    "battery_level": battery_level_1
}

# Create a dictionary to store sensor values for device 2
sensor_data_2 = {
    "device_id": 2,
    "gas": gas_value_2,
    "smoke": smoke_value_2,
    "temperature": temperature_value_2,
    "radiation": radiation_value_2,
    "latitude": latitude_2,
    "longitude": longitude_2,
    "battery_level": battery_level_2
}

# Create an MQTT client instance
client = mqtt.Client()

# Connect to the MQTT broker
client.connect(broker_address)

# Publish sensor values for device 1 to its topic as JSON
topic_1 = "sensor_1/all_values"
client.publish(topic_1, json.dumps(sensor_data_1))

# Publish sensor values for device 2 to its topic as JSON
topic_2 = "sensor_2/all_values"
client.publish(topic_2, json.dumps(sensor_data_2))

# Disconnect from the MQTT broker
client.disconnect()

