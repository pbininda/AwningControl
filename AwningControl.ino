#include "WiFi.h"
#include "OTA.h"
#include "HTTP.h"
#include "state.h"
#include "persistence.h"
#include "relais.h"
#include "digin.h"

const bool DEBUG_TIMING = 0;


void loop() {
  static const int tickResolution = 1000;
  handleWiFi();
  handleServer();
  handleDigin();
  updateState();
  handleRelais();
  handleOta();
  wiFiGoToSleep(200);
  if (DEBUG_TIMING && state.tick % tickResolution == 0) {
    static time_t lastTickTime = 0;
    Serial.print("tick time: ");
    Serial.print((state.now - lastTickTime) / (tickResolution * 1.0));
    Serial.println("ms");
    lastTickTime = state.now;
  }
  delay(10);
  yield();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("initializing WIFI\r\n");
  initWiFi();
  Serial.println("WIFI initialized\r\n");
  readSettings();
  initState();
  initRelais();
  initDigin();
}


