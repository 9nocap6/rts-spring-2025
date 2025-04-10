const int SENSOR_PIN = 18;
const int NUM_SAMPLES = 1000;

volatile uint32_t sampleIndex = 0;
volatile uint32_t totalTime = 0;
uint32_t intervals[NUM_SAMPLES];
uint32_t lastCaptureTime = 0;

void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), handlePulse, HIGH);
}

void handlePulse() {
    uint32_t currentTime = micros();
    uint32_t timeDiff = currentTime - lastCaptureTime;
    
    if (sampleIndex < NUM_SAMPLES) {
        intervals[sampleIndex] = timeDiff;
        totalTime += timeDiff;
        sampleIndex++;
    }
    
    lastCaptureTime = currentTime;
}

void loop() {
    if (sampleIndex >= NUM_SAMPLES) {
        noInterrupts();
        analyzeData();
        sampleIndex = 0;
        totalTime = 0;
        interrupts();
    }
}

void analyzeData() {
    float average = totalTime / (float)NUM_SAMPLES;
    float sumSquaredDiffs = 0;
    
    for (int i = 0; i < NUM_SAMPLES; i++) {
        float diff = intervals[i] - average;
        sumSquaredDiffs += diff * diff;
    }
    
    Serial.print("Average: ");
    Serial.print(average);
    Serial.print(" us, Std Dev: ");
    Serial.print(sqrt(sumSquaredDiffs / NUM_SAMPLES));
    Serial.println(" us");
}
