#ifndef _STATE_H_
#define _STATE_H_

extern struct settings {
  uint32_t max_on_duration_ms;
} settings;

/**
 * State is updated once per cycle.
 * handleServer() and handleDigin() update state according to user input (trigger open and closed)
 * updateState() do automatic state updates (update time, off after timeout)
 * handleRelais() updates the relay outputs according to state.
 */
extern struct state {
  bool open_on;   // open relay should be on
  bool close_on;  // close relay should be on
  time_t open_off_time; // when open relay should be shut off automatically
  time_t close_off_time; // when close relay should be shut off automatically
  time_t now; // current time
  time_t last_open_on_time;   // last time, the open relay was on
  time_t last_close_on_time;  // last time, the close relay was on
  int32 current_pos; // current position
  int32 last_start_pos; // position when last movement was started
  time_t last_operation_start_time; // time when last operation was started
  uint16_t tick;  // tick count
} state;


extern void initState();
extern void updateState();

extern void trigger_open(uint32_t duration);
extern void trigger_close(uint32_t duration);

extern void cancel_open();
extern void cancel_close();

#endif
