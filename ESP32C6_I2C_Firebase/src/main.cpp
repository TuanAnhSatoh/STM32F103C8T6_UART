#define FIREBASE_HOST "gasmonitor-e027f-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "YZg4nCuQl7QVU30SjgMIRFNB3qfyAg83OYsDou0F"

#define WIFI_SSID "Satoh"
#define WIFI_PASSWORD "12345678"

#define USER_ID "2aKrubOfD2VTfiCNA7voeaS4AN92"

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <UUID.h>

WiFiClientSecure espClient;
PubSubClient mqttClient(espClient);
HTTPClient http;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600, 60000); 

HardwareSerial GasSerial(1);  

void wifiConnect();
String getUUID();
String localDateTime();
float randomGas(float min, float max);
void sendToFirebase(
  String measurementId, 
  String userId, 
  String dateTime, 
  float gas
);

void setup() {
  Serial.begin(115200);
  GasSerial.begin(9600, SERIAL_8N1, 5, 4);
  wifiConnect();
  espClient.setInsecure();
  timeClient.begin();
}

void loop() {
  timeClient.update();

  if (GasSerial.available()) {
      String gasString = GasSerial.readStringUntil('\n');
      gasString.trim(); 

      if (gasString.length() > 0) {
        float gasValue = gasString.toFloat(); 

        sendToFirebase(
          getUUID(),
          USER_ID,
          localDateTime(),
          gasValue
        );

      Serial.println("Đã gửi gas: " + gasString);
    }
  }

  delay(100);
}

void wifiConnect() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}


String getUUID() {
  UUID uuid;
  uuid.generate();
  return String(uuid.toCharArray()); 
}

String localDateTime() {
  time_t rawTime = timeClient.getEpochTime();
  struct tm* timeInfo = gmtime(&rawTime);
  char dateTime[25];
  strftime(dateTime, sizeof(dateTime), "%Y-%m-%dT%H:%M:%S", timeInfo);
  unsigned long ms = millis() % 1000;
  char millisStr[5];
  snprintf(millisStr, sizeof(millisStr), ".%03lu", ms);
  return String(dateTime) + String(millisStr); 
}

float randomGas(float min, float max) {
  return random(min, max);
}

void sendToFirebase(
  String measurementId, 
  String userId, 
  String dateTime, 
  float gas
) {
  String url = String("https://") + FIREBASE_HOST + "/measurements/" + measurementId + ".json?auth=" + FIREBASE_AUTH;
  String jsonPayload = String("{\"measurementId\":\"") + measurementId + 
                   "\",\"userId\":\"" + userId + 
                   "\",\"dateTime\":\"" + dateTime + 
                   "\",\"gas\":" + String(gas) + "}";

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int response = http.PUT(jsonPayload);
  if (response > 0) {
    Serial.println("Gửi Firebase OK: " + url);
  } else {
    Serial.println("Firebase lỗi: " + http.errorToString(response));
  }
  http.end();
}
