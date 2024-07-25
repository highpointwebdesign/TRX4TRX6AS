#include <Preferences.h>
#include <WiFi.h>
#include <WebServer.h>

Preferences preferences;
#define LED_BUILTIN 2

WebServer server(80);

void flashLED(int flashes) {
  for (int i = 0; i < flashes; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  preferences.begin("settings", false);

  readSettings();
  setupWiFi();
  setupServer();
}

void loop() {
  server.handleClient();
}

void readSettings() {
  Serial.println("Settings read from Preferences:");
  
  String adm_APSSID = preferences.getString("adm_APSSID", "host);
  String adm_APPassword = preferences.getString("adm_APPassword", "password);
  String adm_STASSID = preferences.getString("adm_STASSID", "networkssid);
  String adm_STAPassword = preferences.getString("adm_STAPassword", "password);
  float vs_rideheight = preferences.getFloat("vs_rideheight", 1.0);
  float vs_multiplier = preferences.getFloat("vs_multiplier", 1.0);
  float vs_balance = preferences.getFloat("vs_balance", 0.0);
  float vs_range = preferences.getFloat("vs_range", 0.0);
  float vs_speed = preferences.getFloat("vs_speed", 1.5);
  float vs_damping = preferences.getFloat("vs_damping", 2.0);

  Serial.printf("adm_APSSID = %s\n", adm_APSSID.c_str());
  Serial.printf("adm_APPassword = %s\n", adm_APPassword.c_str());
  Serial.printf("adm_STASSID = %s\n", adm_STASSID.c_str());
  Serial.printf("adm_STAPassword = %s\n", adm_STAPassword.c_str());
  Serial.printf("vs_rideheight = %.1f\n", vs_rideheight);
  Serial.printf("vs_multiplier = %.1f\n", vs_multiplier);
  Serial.printf("vs_balance = %.1f\n", vs_balance);
  Serial.printf("vs_range = %.1f\n", vs_range);
  Serial.printf("vs_speed = %.1f\n", vs_speed);
  Serial.printf("vs_damping = %.1f\n", vs_damping);

  flashLED(1);
}

void setupWiFi() {
  String APSSID = preferences.getString("adm_APSSID", "host);
  String APPassword = preferences.getString("adm_APPassword", "password);
  String STASSID = preferences.getString("adm_STASSID", "networkssid);
  String STAPassword = preferences.getString("adm_STAPassword", "password);

  WiFi.begin(STASSID.c_str(), STAPassword.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(STASSID);
  IPAddress localIP = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(localIP);

  // Update the IP address in preferences
  preferences.putString("adm_ipaddress", localIP.toString());
}

void setupServer() {
  server.on("/data", HTTP_GET, [](){
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");

    String json = "{";
    
    json += "\"adm_APSSID\":\"" + preferences.getString("adm_APSSID", "host) + "\",";
    json += "\"adm_APPassword\":\"" + preferences.getString("adm_APPassword", "password) + "\",";
    json += "\"adm_STASSID\":\"" + preferences.getString("adm_STASSID", "networkssid) + "\",";
    json += "\"adm_STAPassword\":\"" + preferences.getString("adm_STAPassword", "password) + "\",";
    json += "\"adm_ipaddress\":\"" + preferences.getString("adm_ipaddress", "0.0.0.0") + "\",";
    json += "\"vs_rideheight\":" + String(preferences.getFloat("vs_rideheight", 1.0)) + ",";
    json += "\"vs_multiplier\":" + String(preferences.getFloat("vs_multiplier", 1.0)) + ",";
    json += "\"vs_balance\":" + String(preferences.getFloat("vs_balance", 0.0)) + ",";
    json += "\"vs_range\":" + String(preferences.getFloat("vs_range", 0.0)) + ",";
    json += "\"vs_speed\":" + String(preferences.getFloat("vs_speed", 1.5)) + ",";
    json += "\"vs_damping\":" + String(preferences.getFloat("vs_damping", 2.0));
    json += "}";

    server.send(200, "application/json", json);
    flashLED(1);
  });

  server.on("/update", HTTP_POST, [](){
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");

    if (server.hasArg("value")) {
      String paramValue = server.arg("value");
      int separatorIndex = paramValue.indexOf('=');
      if (separatorIndex != -1) {
        String setting = paramValue.substring(0, separatorIndex);
        String value = paramValue.substring(separatorIndex + 1);
        updateSetting(setting, value);
        server.send(200, "application/json", "{\"message\":\"Setting updated successfully\"}");
      } else {
        server.send(400, "application/json", "{\"message\":\"Invalid setting format\"}");
        flashLED(5);
      }
    } else {
      server.send(400, "application/json", "{\"message\":\"No value parameter provided\"}");
      flashLED(5);
    }
  });

  server.begin();
}

void updateSetting(const String& setting, const String& value) {
  if (setting.startsWith("vs_")) {
    preferences.putFloat(setting.c_str(), value.toFloat());
  } else {
    preferences.putString(setting.c_str(), value);
  }

  flashLED(1);
}
