#include "Arduino_SensorKit.h"// wraper sa svim biblotekama za nase senzore
// #include "DHT.h"
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 2     // what pin we're connected to（DHT10 and DHT20 don't need define it）
#define BUZZER_PIN 8
// #include "U8g2/src/U8x8lib.h"                    // OLED Display

DHT dht(DHTPIN, DHTTYPE);   //   DHT11 DHT21 DHT22
int frekvencija =1000; // frekvencija buzzarda 
int trajanje =1000; // duzina trajanja buzza 

const int analogPin = 15; // A1 pin na koju se kaci detektor
 int val ; // promenljiva koja se ocitava sa detektora
 int k=5; // prag za detekciju 
 int i=0; // brojac detektovanih cestica
 bool det=true; // rising edge
int LED_dioda =LED_BUILTIN; // led dioda za sada unutrasnja


void setup() {
  Oled.begin();
  Oled.setFlipMode(true);
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(LED_dioda, OUTPUT);
  Serial.println("DHT test!");
  Wire.begin();
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
 

  // citanje sa detektora vrednosti pomocu pina A1
  val = analogRead(A1);

 if (val > k) {
    // turn LED on:
    digitalWrite(LED_dioda, HIGH);
    if (det==false){
      i=i+1; 
      tone(BUZZER_PIN, frekvencija, trajanje); // okidanje buzzer a nakon detekcije
    Oled.setFont(u8x8_font_chroma48medium8_r); 
    Oled.setCursor(0, 3);
    Oled.print("Det: ");
    Oled.print(i); // s
 

      float temp_hum_val[2] = {0};
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

    if (!dht.readTempAndHumidity(temp_hum_val)) {
        Serial.print("Humidity: ");
        Serial.print(temp_hum_val[0]);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println(" *C");
    } else {
        Serial.println("Failed to get temprature and humidity value.");
    }
      det=true; 
      Serial.print(det);
    }
  } else {
    // turn LED off:
    digitalWrite(LED_dioda, LOW);
          det=false; 

  }
    Serial.print(i); // provera rada brojaca
    Serial.print("\n");
    Serial.print(val); // provera rada detektora
    Serial.print("\n");
    Serial.print(det); // provera rising edge
    Serial.print("\n");
delay(1000);
  
}