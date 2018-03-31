#include <Arduino.h>
#include "state.h"

#define MAX_ON_DURATION_MS (120 * 1000)

const int32 POS_SCALE = 10000;
const int32 POS_SCALE_OVER = POS_SCALE + POS_SCALE / 10;

struct state state;
struct settings settings;

void updateState() {
  state.now = millis();
  state.tick++;
  if (state.open_on) {
    state.current_pos = state.last_start_pos + (state.now - state.last_operation_start_time) * POS_SCALE_OVER / settings.max_on_duration_ms;
    if (state.current_pos > POS_SCALE) {
      state.current_pos = POS_SCALE;
    }
  }
  else if (state.close_on) {
    state.current_pos = state.last_start_pos - (state.now - state.last_operation_start_time) * POS_SCALE_OVER / settings.max_on_duration_ms;
    if (state.current_pos < 0) {
      state.current_pos = 0;
    }
  }
  if (state.now >= state.open_off_time) {
    cancel_open();
  }
  if (state.now >= state.close_off_time) {
    cancel_close();
  }
}

void initState() {
  cancel_open();
  cancel_close();
  state.now = millis();
  state.last_close_on_time = state.now;
  state.last_open_on_time = state.now;
  state.tick = 0;
}

uint32_t limit_duration(uint32_t duration_ms) {
  if (duration_ms == 0) {
    duration_ms = settings.max_on_duration_ms;
  }
  if (duration_ms > settings.max_on_duration_ms) {
    duration_ms = settings.max_on_duration_ms;
  }
  if (duration_ms > MAX_ON_DURATION_MS) {
    duration_ms = MAX_ON_DURATION_MS;
  }
  return duration_ms;
}

time_t target_time(uint32_t duration_ms) {
  duration_ms = limit_duration(duration_ms);
  return state.now + duration_ms;
}

void trigger_open(uint32_t duration_ms) {
  state.open_off_time = target_time(duration_ms);
  state.open_on = true;
  state.last_start_pos = state.current_pos;
  state.last_operation_start_time = state.now;
  Serial.println("trigger open");
  cancel_close();
}

void trigger_close(uint32_t duration_ms) {
  state.close_off_time = target_time(duration_ms);
  state.close_on = true;
  state.last_start_pos = state.current_pos;
  state.last_operation_start_time = state.now;
  Serial.println("trigger close");
  cancel_open();
}

void cancel_open() {
  if (state.open_on) Serial.println("cancel open");
  state.open_off_time = 0;
  state.open_on = false;
}

void cancel_close() {
  if (state.close_on) Serial.println("cancel close");
  state.close_off_time = 0;
  state.close_on = false;
}
