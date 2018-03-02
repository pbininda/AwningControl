#include <Arduino.h>
#include "state.h"
#include "relais.h"

#define OPEN_PIN 14
#define CLOSE_PIN 4

void setOpenRelais(bool on) {
    digitalWrite(OPEN_PIN, on ? LOW : HIGH);
}

void setCloseRelais(bool on) {
    digitalWrite(CLOSE_PIN, on ? LOW : HIGH);
}

void initRelais() {
    setOpenRelais(false);
    setCloseRelais(false);
    pinMode(OPEN_PIN, OUTPUT);
    pinMode(CLOSE_PIN, OUTPUT);
    setOpenRelais(false);
    setCloseRelais(false);
}

void handleRelais() {
    setOpenRelais(state.open_on && !state.close_on);
    setCloseRelais(state.close_on);
}

