const int outPins[] = {3, 5, 6, 9, 10};
const unsigned long pulseTimes[] = {10000, 1000, 500, 100, 50};
volatile bool toggleStates[] = {LOW, LOW, LOW, LOW, LOW};
unsigned long timeStampA, timeStampB, timeStampC, timeStampD, timeStampE;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(outPins[i], OUTPUT);
  }
  unsigned long startMicros = micros();
  timeStampA = startMicros;
  timeStampB = startMicros;
  timeStampC = startMicros;
  timeStampD = startMicros;
  timeStampE = startMicros;
}

void loop() {
  unsigned long nowMicros = micros();

  if (nowMicros - timeStampE >= pulseTimes[4]) {
    PORTB ^= B00000100;
    timeStampE = nowMicros;
  }
  if (nowMicros - timeStampD >= pulseTimes[3]) {
    PORTB ^= B00000010;
    timeStampD = nowMicros;
  }
  if (nowMicros - timeStampC >= pulseTimes[2]) {
    PORTD ^= B01000000;
    timeStampC = nowMicros;
  }
  if (nowMicros - timeStampB >= pulseTimes[1]) {
    PORTD ^= B00100000;
    timeStampB = nowMicros;
  }
  if (nowMicros - timeStampA >= pulseTimes[0]) {
    PORTD ^= B00001000;
    timeStampA = nowMicros;
  }
}
