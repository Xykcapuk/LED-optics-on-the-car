#include <Adafruit_NeoPixel.h> //подключение библиотеки NeoPix, NeoPix library connection

//Габаритные огни переменные, Variable side lights
int outPinSideLights = 12;        // подключение диодной ленты на выход D12, diode strip connection to output D12
int inPinButtonSideLights = 7;    // подключение управляющего сигнала на выход D7, connection of control signal to output D7
int numsLedSideLights = 9;        // количество пикселей на диодной ленте, number of pixels on the diode strip
int posPixSideLights = 0;         // позиция пикселя на диодной ленте, pixel position on the diode strip
int lapscount = 0;                // количество итераций приветствия, number of greeting iterations

//Поворотники переменные, Variable turn signals
int outPinTurnSignals = 13;       // подключение диодной ленты на выход D13, diode strip connection to output D13
int inPinButtonTurnSignals = 6;   // подключение управляющего сигнала на выход D6, connection of control signal to output D6
int numsLedTurnSignals = 9;       // количество пикселей на диодной ленте, number of pixels on the diode strip
int posPixTurnSignals = 0;        // позиция пикселя на диодной ленте, pixel position on the diode strip
int pixAllLed = 3;                // номер пикселя после которого включаются все пиксели разом, pixel number after which all pixels are turned on at once

Adafruit_NeoPixel adaLedSideLights= Adafruit_NeoPixel(numsLedSideLights, outPinSideLights, NEO_GRB + NEO_KHZ800);     // переменная NeoPix для габаритных огней, NeoPix variable for side lights
Adafruit_NeoPixel adaLedTurnSignals = Adafruit_NeoPixel(numsLedTurnSignals, outPinTurnSignals, NEO_GRB + NEO_KHZ800); // переменная NeoPix для поворотников, NeoPix variable for turn signals

void setup() {
  pinMode(inPinButtonSideLights, INPUT);
    adaLedSideLights.begin();
  pinMode(inPinButtonTurnSignals, INPUT);
    adaLedTurnSignals.begin();
}

//Габаритные огни режим приветствия, Side lights welcome mode
void lapsSideLights() {
  while (lapscount < 2) {
    adaLedSideLights.setBrightness(115);
    for (int count = 0; count < numsLedSideLights; count++) {
      adaLedSideLights.setPixelColor(posPixSideLights-2, adaLedSideLights.Color(255,0,0));
      posPixSideLights = posPixSideLights + 1;
      adaLedSideLights.show();
      delay(165);
    }
    adaLedSideLights.clear();
    for (int count = 0; count < numsLedSideLights; count++) {
      adaLedSideLights.setPixelColor(posPixSideLights-2, adaLedSideLights.Color(255,0,0));
      posPixSideLights = posPixSideLights - 1;
      adaLedSideLights.show();
      delay(165);
    }
    adaLedSideLights.clear();
    lapscount++;
  }
}
//Габаритные огни режим работы, Side lights operating mode
void allLedSideLightsON() {
  adaLedSideLights.setBrightness(255);
  for (int count = 0; count <= numsLedSideLights; count++) {
    adaLedSideLights.setPixelColor(count, adaLedSideLights.Color(255,0,0));
    delay(60);
  }
  adaLedSideLights.show();
}

//Поворотники режим работы, Turn signals operating mode
void turnSignals() {
  adaLedTurnSignals.setBrightness(15);
  for (int count = 0; count < numsLedTurnSignals - pixAllLed; count++) {
    adaLedTurnSignals.setPixelColor(posPixTurnSignals, adaLedTurnSignals.Color(255,47,0)); // он бежит с индекса 0 и при условии, что работает аварийка
    posPixTurnSignals = posPixTurnSignals + 1;
    adaLedTurnSignals.show();
    delay(92);
  }
  for (int count = 0; count < pixAllLed; count++) {
    adaLedTurnSignals.setPixelColor(posPixTurnSignals, adaLedTurnSignals.Color(255,47,0));
    posPixTurnSignals = posPixTurnSignals + 1;
    adaLedTurnSignals.show();
  }
  delay(80);
  adaLedTurnSignals.clear();
}

void loop() {
//Габаритные огни, Side lights
  int valueSideLights = digitalRead(inPinButtonSideLights);
  if (valueSideLights == HIGH) {
    lapsSideLights();
    allLedSideLightsON();
  }
  if (valueSideLights == LOW) {
    adaLedSideLights.clear();
    adaLedSideLights.show();
    lapscount = 0;
  }
//Поворотники, Turn signals 
  int valueTurnSignals = digitalRead(inPinButtonTurnSignals);
  if (valueTurnSignals == HIGH) {
    turnSignals();
    posPixTurnSignals = 0;
  }
  if (valueTurnSignals == LOW) {
    adaLedTurnSignals.setPixelColor(numsLedTurnSignals, adaLedTurnSignals.Color(0,0,0));
    adaLedTurnSignals.show();
  }
}