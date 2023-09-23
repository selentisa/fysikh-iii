import paho.mqtt.client as mqtt
import json
import time

# MQTT broker configuration
broker_address = "localhost"  # Update with your MQTT broker address
android_topic = "android/data"  # The topic for Android device data

# Example Android device location data
android_id = "android_device_1"
latitude = 35.12345  # Replace with the actual latitude
longitude = -120.67890  # Replace with the actual longitude

# Create a dictionary to store Android device location data
android_location_data = {
    "android_id": android_id,
    "latitude": latitude,
    "longitude": longitude
}

# Create an MQTT client instance for Android data publisher
client = mqtt.Client()

# Connect to the MQTT broker
client.connect(broker_address)

while True:
    # Convert the dictionary to a JSON-formatted string
    
    
    # Publish Android device location data to the specified topic as JSON
    client.publish(android_topic, json.dumps(android_location_data))
    
    # Sleep for a short period (e.g., 5 seconds) before publishing again
    time.sleep(5)

# Disconnect from the MQTT broker (This part may not be reached in an infinite loop)
client.disconnect()
