#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define SCREEN_WIDTH 128 // Ancho del display OLED, en píxeles
#define SCREEN_HEIGHT 64 // Alto del display OLED,en píxeles
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, -1);
#define DHTPIN 4 // Pin digital conectado al sensor DHT11
#define DHTTYPE DHT11 // Se usa el sensor DHT11
DHT dht(DHTPIN, DHTTYPE); // Inicializar el sensor DHT con el pin y tipo definidos

void setup() {
Serial.begin(115200); // Iniciar la comunicación serial para la depuración
dht.begin(); // Iniciar el sensor DHT
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
Serial.println(F("SSD1306 allocation failed"));
for(;;); // Bucle infinito si falla el OLED
}
delay(2000); // Esperar 2 segundos para estabilizar
display.clearDisplay(); // Limpiar cualquier contenido previo en la pantalla
display.setTextColor(WHITE); // Establecer el color del texto en blanco
display.display();
}
void loop() {
delay(5000); // Esperar 5 segundos entre lecturas
float t = dht.readTemperature(); // Leer temperatura en grados Celsius
float h = dht.readHumidity(); // Leer humedad en porcentaje
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return; // Salir si hay error
}

display.clearDisplay();
display.setTextSize(1);
display.setCursor(0,0);
display.print("Temperature: ");
display.setTextSize(2);
display.setCursor(0,10);
display.print(t);
display.print(" ");
display.setTextSize(1);
display.cp437(true);
display.write(167); // Mostrar el símbolo de grados
display.setTextSize(2);
display.print("C");
display.setTextSize(1);
display.setCursor(0, 35);
display.print("Humidity: ");
display.setTextSize(2);
display.setCursor(0, 45);
display.print(h);
display.print(" %");
display.display(); // Actualizar la pantalla con los nuevos datos
}
