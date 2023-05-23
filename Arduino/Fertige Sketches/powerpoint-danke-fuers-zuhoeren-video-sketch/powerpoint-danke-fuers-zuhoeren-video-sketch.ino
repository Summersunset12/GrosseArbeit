// NeoPixel Effekte für Große Arbeit von Kim K. Sander.

// Wir benutzen die Adafruit NeoMatrix Bibliothek, die wiederum
// die Adafruit NeoPixel Bibliothek und Adafruit Grafikbibliothek benutzt.
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// Welcher PIN ist mit den LEDs verbunden?
#define PIN 6

// Kims Farbpalette, in Rot, Grün, Blau. Werte 0-255
#define KIM_ROTROT 255, 0, 0
#define KIM_DUNKELORANGE 255, 40, 0
#define KIM_KLASSISCHGELB 255, 215, 0
#define KIM_GRASGRUEN 50, 205, 50
#define KIM_HELLBLAU 0, 191, 255
#define KIM_NAVY 0, 0, 128
#define KIM_KLASSISCHLILA 153, 50, 204
#define KIM_MAGENTAVIOLET 205, 0, 205
#define KIM_SCHWARZ 0, 0, 0

// Helligkeit der LEDs. Werte von 0-255
#define NEO_BRIGHTNESS 75

// Laufschriften für Effekte
#define TEXT "Danke fuer Ihre Aufmerksamkeit."

// Matrix besteht aus 2 horizontal und 2 vertikal angeordneten Kacheln
// mit je 8x8 LEDs.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
  8,                                // LEDs in Kachelbreite
  8,                                // LEDs in Kachelhoehe
  4,                                // Kacheln nebeneinander
  1,                                // Kacheln untereinander
  PIN,                              // Daten-Pin
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT  // 1. LED oben links
    + NEO_MATRIX_ROWS               // LED-Ausrichtung
    + NEO_MATRIX_ZIGZAG             // LED-Reihenfolge
    + NEO_TILE_TOP + NEO_TILE_LEFT  // 1. Kachel oben links
    + NEO_TILE_ROWS                 // Kacheln-Ausrichtung
    + NEO_TILE_PROGRESSIVE,         // Kachel-Reihenfolge
  NEO_GRB + NEO_KHZ800);            // LED Typ


// Farbtabelle mit Farben aus Farbpalette mit Index 0-7
const uint16_t COLORS[9] = {
  matrix.Color(KIM_ROTROT),
  matrix.Color(KIM_DUNKELORANGE),
  matrix.Color(KIM_KLASSISCHGELB),
  matrix.Color(KIM_GRASGRUEN),
  matrix.Color(KIM_HELLBLAU),
  matrix.Color(KIM_NAVY),
  matrix.Color(KIM_KLASSISCHLILA),
  matrix.Color(KIM_MAGENTAVIOLET),
  matrix.Color(KIM_SCHWARZ),
};
// !!!
int farbe = 7;

// Sachen die nur einmal am Anfang gemacht werden.
void setup() {
  matrix.begin();                        // Einschalten der LEDs.
  matrix.setTextWrap(false);             // kein Textumbruch
// !!!
  //matrix.setTextColor(COLORS[7]);        // Textfarbe KIM_MAGENTAVIOLET
  matrix.setBrightness(NEO_BRIGHTNESS);  // Einstellen der Helligkeit der LEDs.
  matrix.clear();                        // Schaltet alle LEDs aus.
  matrix.show();                         // Ausführung der vorherigen Befehle.
}

// Endlose Ausführung der folgenden Befehle
void loop() {
  laufschrift(TEXT, farbe);
// !!!
  farbe = (farbe + 1) % 8;
  delay(5000);
}
// !!!
void laufschrift(const char* text, int farbe) {
  int textLaenge = strlen(text) * 6; // Textlänge in Pixel (6 Pixel pro Buchstabe)
 // !!!
  matrix.setTextColor(COLORS[farbe]); // Textfarbe setzen.

  int x = matrix.width();            // In der Spalte ganz rechts anfangen.
  while (true) {
    matrix.fillScreen(0);            
    matrix.setCursor(x, 0);
    matrix.print(text);
    matrix.show();
    delay(100);

    x = x - 1;
    if (x + textLaenge < 0) {  // Text ist vollstaendig links vom 1. LED
      break;
    }
  }
}