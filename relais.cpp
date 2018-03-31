#include <Arduino.h>
#include "state.h"
#include "relais.h"

#define OPEN_PIN 14
#define CLOSE_PIN 4

#define MIN_OFF_TIME 600

void setOpenRelais(bool on) {
    if (on && state.now - state.last_close_on_time < MIN_OFF_TIME) {
        Serial.println("preventing open");
        on = false;
    }
    if (on) {
        state.last_open_on_time = state.now;
    }
    digitalWrite(OPEN_PIN, on ? LOW : HIGH);
}

void setCloseRelais(bool on) {
    if (on && state.now - state.last_open_on_time < MIN_OFF_TIME) {
        Serial.println("preventing close");
        on = false;
    }
    if (on) {
        state.last_close_on_time = state.now;
    }
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

