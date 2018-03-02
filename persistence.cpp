#include <Arduino.h>
#include <EEPROM.h>
#include "state.h"
#include "persistence.h"

struct header {
  uint16_t magic;
  uint16_t version;
};

struct header expectedHeader = {0xEAEA, 1};

void printSettings() {
  Serial.println("Settings:");
  Serial.print("max on duration: "); Serial.print(settings.max_on_duration_ms); Serial.println("ms");
}

void defaultSettings() {
  settings.max_on_duration_ms = 1000;
}

void readSettings() {
  EEPROM.begin(512);
  struct header header;
  EEPROM.get(0, header);
  if (header.magic != expectedHeader.magic) {
    Serial.println("header magic mismatch");
    defaultSettings();
    printSettings();
    writeSettings();
    return;
  }
  else if (header.version != expectedHeader.version) {
    Serial.println("header version mismatch");
    defaultSettings();
    printSettings();
    writeSettings();
    return;
  }
  else {
    EEPROM.get(sizeof(struct header), settings);
    printSettings();
  }
}

void writeSettings() {
  EEPROM.put(0, expectedHeader);
  EEPROM.put(sizeof(struct header), settings);
  EEPROM.commit();
}


