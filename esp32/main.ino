#include <Arduino.h>
#include "model_params.h"

// 7-in-1 sensor interface concept:
// moisture, temperature, pH, EC, N, P, K
// Current public-data model uses only pH, EC, N, P, K.

const char* TARGET_NAMES[N_TARGETS] = {
  "OC","Ca","Mg","S","B","Zn","Fe","Cu","Mn","C"
};

float predictOne(const float x[N_FEATURES], int target) {
  float y_std = MODEL_INTERCEPT[target];

  for (int j = 0; j < N_FEATURES; j++) {
    float x_std = (x[j] - X_MEAN[j]) / X_SCALE[j];
    y_std += MODEL_COEF[target][j] * x_std;
  }

  return y_std * Y_SCALE[target] + Y_MEAN[target];
}

void predictSoil(
  float moisture,
  float temperature,
  float pH,
  float ec,
  float n,
  float p,
  float k
) {
  // moisture and temperature are intentionally not used by the
  // current model because the training dataset did not contain them.
  (void)moisture;
  (void)temperature;

  float x[N_FEATURES] = {pH, ec, n, p, k};

  Serial.println("\n--- EDGE AI SOIL PREDICTION ---");
  for (int i = 0; i < N_TARGETS; i++) {
    float y = predictOne(x, i);
    Serial.print(TARGET_NAMES[i]);
    Serial.print(": ");
    Serial.println(y, 4);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Replace these demo values with your real RS485/Modbus 7-in-1 sensor values.
  float moisture = 42.0;
  float temperature = 27.5;
  float pH = 6.5;
  float ec = 0.07;
  float n = 150.0;
  float p = 18.0;
  float k = 120.0;

  predictSoil(moisture, temperature, pH, ec, n, p, k);
}

void loop() {
  delay(5000);
}
