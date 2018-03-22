#include <Arduino.h>
#include "digin.h"
#include "state.h"

#define OPEN_IN_PIN 15
#define CLOSE_IN_PIN 5

void initDigin() {
    pinMode(OPEN_IN_PIN, INPUT);
    pinMode(CLOSE_IN_PIN, INPUT);
}

void handleDigin() {
    int cl = digitalRead(CLOSE_IN_PIN);
    int op = digitalRead(OPEN_IN_PIN);
    static time_t last_none = 0;
    static time_t last_one = 0;
    time_t now = millis();
    if ((cl || op) && now > last_one + 1000) {
        if (state.open_on || state.close_on) {
            cancel_close();
            cancel_open();
        }
        else {
            if (cl) {
                trigger_close(0);
            }
            else {
                trigger_open(0);
            }
        }
        last_one = now;
    }
    else {
        last_none = now;
    }
}
