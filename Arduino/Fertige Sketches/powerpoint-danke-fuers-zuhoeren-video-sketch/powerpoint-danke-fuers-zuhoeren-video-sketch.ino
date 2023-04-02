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

// Laufschriften für Effekte
#define TEXT_REGENBOGEN "Der wandelnde Regenbogen:"
#define TEXT_SMILEY "Der laechelnde Smiley:"

#define NUMZEILEN 16
#define NUMSPALTEN 16

// Matrix besteht aus 2 horizontal und 2 vertikal angeordneten Kacheln
// mit je 8x8 LEDs.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
  8,                                // LEDs in Kachelbreite
  8,                                // LEDs in Kachelhoehe
  2,                                // Kacheln nebeneinander
  2,                                // Kacheln untereinander
  PIN,                              // Daten-Pin
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT  // 1. LED oben links
    + NEO_MATRIX_ROWS               // LED-Ausrichtung
    + NEO_MATRIX_ZIGZAG             // LED-Reihenfolge
    + NEO_TILE_TOP + NEO_TILE_LEFT  // 1. Kachel oben links
    + NEO_TILE_ROWS                 // Kacheln-Ausrichtung
    + NEO_TILE_PROGRESSIVE,         // Kachel-Reihenfolge
  NEO_GRB + NEO_KHZ800);            // LED Typ

// Helligkeit der LEDs. Werte von 0-255
#define NEO_BRIGHTNESS 75

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

// Jedes Symbol hat 16 Zeilen.
const int SYMBOL_ZEILEN_16x16 = 16;

// Jedes Symbol hat 16 Spalten.
const int SYMBOL_SPALTEN_16x16 = 16;

// Jedes Symbol hat 16x16 LEDs.
const int SYMBOL_PIXELS = SYMBOL_ZEILEN_16x16 * SYMBOL_SPALTEN_16x16;

// Die Symbole sind als lineare Folge von Pixelfarben
// dargestellt. Jede Pixelfarbe ist ein Index in die
// Farbtabelle COLORS.
const byte SYMBOLE_16x16[] PROGMEM = {
  /* clang-format off */

  // Smiley (smiling) 16x16
  8, 8, 8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 8, 8, 8, 8,
  8, 8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 8, 8,
  8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 8,
  8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8,
  2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 4, 4, 2, 2, 2, 2,
  2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 4, 4, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2,
  2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2,
  2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2,
  2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2,
  8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8,
  8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 8,
  8, 8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 8, 8,
  8, 8, 8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 8, 8, 8, 8,

  /* clang-format on */
};

// Sachen die nur einmal am Anfang gemacht werden.
void setup() {
  Serial.begin(115200);        // Einschalten des Monitors der Überwachung
  awaitSerialConnected(1000);  // Wartet eine Sekunde bis der Monitor der Überwachung eingeschaltet ist

  matrix.begin();                        // Einschalten der LEDs.
  matrix.setTextWrap(false);             // kein Textumbruch
  matrix.setTextColor(COLORS[6]);        // Textfarbe KIM_KLASSISCHLILA
  matrix.setBrightness(NEO_BRIGHTNESS);  // Einstellen der Helligkeit der LEDs.
  matrix.clear();                        // Schaltet alle LEDs aus.
  matrix.show();                         // Ausführung der vorherigen Befehle.

  // Kontrollausgaben der Anzahl der LEDs und der Helligkeit.
  Serial.print("Neomatrix initialisiert mit Breite ");
  Serial.print(matrix.width());
  Serial.print(" und Höhe ");
  Serial.print(matrix.height());
  Serial.print(" und Helligkeit ");
  Serial.println(matrix.getBrightness());
}

// Endlose Ausführung der folgenden Befehle
void loop() {

  // regenbogen(false);
  // regenbogen(true);  // umgekehrt
  // regenbogen(false);
  // regenbogen(true);  // umgekehrt
  // regenbogen(false);
  // regenbogen(true);  // umgekehrt

  laufschrift(TEXT_REGENBOGEN);
  wandelnderRegenbogen();

  delay(2000);

  laufschrift(TEXT_SMILEY);
  lachenderSmiley();

  delay(5000);

  //allesRot();
}

void laufschrift(const char* text) {
  int x = matrix.width();
  int pass = 0;
  while (pass <= 0) {
    matrix.fillScreen(0);
    matrix.setCursor(x, 4);
    int textLaenge = strlen(text);
    matrix.print(text);
    // Die Lauflänge des obigen Texts beträgt Zeichen * 6.
    if (--x < -(textLaenge * 6)) {  // Text ist vollstaendig links vom 1. LED
      x = matrix.width();
      pass++;
    }
    matrix.show();
    delay(100);
  }
}

// Schalte alle LEDs hintereinander auf die Farbe RotRot.
void allesRot() {
  matrix.clear();  // Schalte alle Pixel aus

  // Laufe über die Pixel von 0 bis Anzahl der LEDs - 1
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 16; x++) {
      // Setze die LED an x,y
      matrix.drawPixel(x, y, COLORS[0]);
      matrix.show();  // Sende die Befehle an die LEDs.
      delay(10);      // Warte in Millisekunden vor dem nächsten Schleifendurchlauf.
    }
  }
}

// void regenbogen(bool umgekehrt) {
//   matrix.clear();  // Schalte alle Pixel aus

//   for (int zeile = 0; zeile < 1; zeile++) {
//     int i = zeile * 8;
//     bool istGeradeZeile = zeile % 2 == 0;
//     for (int c = 0; c < NUMSPALTEN; c++) {
//       if (umgekehrt) {
//         // Alle ungeraden Zeilen werden in umgekehrter Reihenfolge ausgegeben,
//         // weil die LEDS in Zickzack-Schlange verlegt sind.
//         matrix.drawPixel(i++, istGeradeZeile ? COLORS[7 - c] : COLORS[c]);
//       } else {
//         matrix.drawPixel(i++, istGeradeZeile ? COLORS[c] : COLORS[7 - c]);
//       }
//     }
//   }
//   matrix.show();

//   delay(1000);  // Warte eine Sekunde, d.h. 1000 Millisekunden.
// }

void wandelnderRegenbogen() {
  matrix.clear();  // Schalte alle Pixel aus

  for (int ende = 0; ende < 2 * NUMSPALTEN; ende++) {
    int colorIndex = NUMSPALTEN;
    for (int i = ende; i >= 0; i--) {
      colorIndex--;
      if (colorIndex < 0) {
        // Lösche vorherige Spalte, falls nötig.
        zeigeFarbeInSpalte(i, matrix.Color(0, 0, 0));
      } else {
        zeigeFarbeInSpalte(i, COLORS[colorIndex % 8]);
      }
    }
    matrix.show();
    if (ende == NUMSPALTEN - 1 || ende == NUMSPALTEN / 2 - 1 || ende == NUMSPALTEN + (NUMSPALTEN / 2) - 1) {
      delay(1500);  // Bleibe für 1,5 Sekunden stehen, wenn Regenbogen vollständig ist.
    }
    delay(200);
  }
}

void lachenderSmiley() {
  zeigeSymbol_16x16(0);
}
void zeigeSymbol_16x16(int symbolStart) {
  matrix.clear();

  int i = symbolStart;

  for (int y = 0; y < SYMBOL_ZEILEN_16x16; y++) {
    for (int x = 0; x < SYMBOL_SPALTEN_16x16; x++) {
      matrix.drawPixel(x, y, COLORS[pgm_read_byte(SYMBOLE_16x16 + i)]);
      i = i + 1;
    }
  }
  matrix.show();
}

/* Hilfsfunktionen */

void zeigeFarbeInSpalte(int spalte, uint32_t color) {
  for (int y = 0; y < 16; y++) {
    matrix.drawPixel(spalte, y, color);
  }
}

void awaitSerialConnected(unsigned long timeoutMillis) {
  unsigned long startMillis = millis();
  do {
    delay(100);
    if (Serial) {
      break;
    }
  } while (millis() - startMillis <= timeoutMillis);
}