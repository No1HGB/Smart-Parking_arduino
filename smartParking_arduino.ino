#include <WiFi.h>
#include <FirebaseESP32.h>


// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "iptimeHGB"
#define WIFI_PASSWORD "8547sd12"

/* 2. Define the RTDB URL */
#define DATABASE_URL "arduino-test-ce6da-default-rtdb.firebaseio.com"

/* 3. Define the Firebase Data object */
FirebaseData fbdo;
FirebaseData stream;

/* 4, Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* Define the FirebaseConfig data for config data */
FirebaseConfig config;

unsigned long dataMillis = 0;

String parentPath = "/parkinglots/parking";
String childPath[8] = {"/name","/loc","/lot1", "/lot2","/lot3","/lot4","/lot5","/lot6"};

void streamCallback(MultiPathStreamData stream)
{
  size_t numChild = sizeof(childPath) / sizeof(childPath[0]);

  for (size_t i = 0; i < numChild; i++)
  {
    if (stream.get(childPath[i]))
    {
      Serial.printf("path: %s, event: %s, type: %s, value: %s%s", stream.dataPath.c_str(), stream.eventType.c_str(), stream.type.c_str(), stream.value.c_str(), i < numChild - 1 ? "\n" : "");
    }
  }

  Serial.println();

  // This is the size of stream payload received (current and max value)
  // Max payload size is the payload size under the stream path since the stream connected
  // and read once and will not update until stream reconnection takes place.
  // This max value will be zero as no payload received in case of ESP8266 which
  // BearSSL reserved Rx buffer size is less than the actual stream payload.
  Serial.printf("Received stream payload size: %d (Max. %d)\n\n", stream.payloadLength(), stream.maxPayloadLength());
}

void streamTimeoutCallback(bool timeout)
{
  if (timeout)
    Serial.println("stream timed out, resuming...\n");

  if (!stream.httpConnected())
    Serial.printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}

/*Ultrasound Distance */
int echoPin = 14;
int trigPin = 12;
int echoPin2 = 32;
int trigPin2 = 33;
int echoPin3 = 25;
int trigPin3 = 26;
int echoPin4 = 22;
int trigPin4 = 23;
int echoPin5 = 18;
int trigPin5 = 19;
int echoPin6 = 16;
int trigPin6 = 17;


void setup()
{

    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the certificate file (optional) */
    // config.cert.file = "/cert.cer";
    // config.cert.file_storage = StorageType::FLASH;

    /* Assign the database URL(required) */
    config.database_url = DATABASE_URL;

    config.signer.test_mode = true;

    /**
     Set the database rules to allow public read and write.
       {
          "rules": {
              ".read": true,
              ".write": true
          }
        }
    */

    Firebase.reconnectWiFi(true);

    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);
    
    /*Ultrasound Distance */
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);
    pinMode(trigPin4, OUTPUT);
    pinMode(echoPin4, INPUT);
    pinMode(trigPin5, OUTPUT);
    pinMode(echoPin5, INPUT);
    pinMode(trigPin6, OUTPUT);
    pinMode(echoPin6, INPUT);
    
}

void loop()
{
  /*Ultrasound Distance */
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration) * 17 /1000;
  delay(500);

  long duration2, distance2;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2) * 17 /1000;
  delay(500);

  long duration3, distance3;
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = (duration3) * 17 /1000;
  delay(500);

  long duration4, distance4;
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  distance4 = (duration4) * 17 /1000;
  delay(500);

  long duration5, distance5;
  digitalWrite(trigPin5, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin5, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin5, LOW);
  duration5 = pulseIn(echoPin5, HIGH);
  distance5 = (duration5) * 17 /1000;
  delay(500);

  long duration6, distance6;
  digitalWrite(trigPin6, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin6, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin6, LOW);
  duration6 = pulseIn(echoPin6, HIGH);
  distance6 = (duration6) * 17 /1000;
  delay(500);

  /*Data Send */
  if (millis() - dataMillis > 500)
  { 
    dataMillis = millis();
    FirebaseJson json;
       if( distance > 5){
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot1/bool", false);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }
      else{
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot1/bool", true);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }

      if( distance2 > 5){
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot2/bool", false);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }
      else{
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot2/bool", true);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }

      if( distance3 > 5){
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot3/bool", false);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }
      else{
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot3/bool", true);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }

      if( distance4 > 5){
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot4/bool", false);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }
      else{
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot4/bool", true);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }

      if( distance5 > 5){
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot5/bool", false);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }
      else{
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot5/bool", true);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }

      if( distance6 > 5){
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot6/bool", false);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }
      else{
        json.set("name", "1번 주차장(진)");
        json.set("loc", "37.455229,126.950959");
        json.set("lot6/bool", true);
        Firebase.setJSONAsync(fbdo, parentPath, json);
        }
      Serial.println("ok!");
    }
}
