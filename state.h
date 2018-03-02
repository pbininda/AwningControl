#ifndef _STATE_H_
#define _STATE_H_

extern struct settings {
  uint32_t max_on_duration_ms;
} settings;

extern struct state {
  bool open_on;
  bool close_on;
  time_t open_off_time;
  time_t close_off_time;
  time_t now;
  uint16_t tick;
} state;


extern void initState();
extern void updateState();

extern void trigger_open(uint32_t duration);
extern void trigger_close(uint32_t duration);

extern void cancel_open();
extern void cancel_close();

#endif
