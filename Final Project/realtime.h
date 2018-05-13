#include <fsl_device_registers.h>

typedef struct {
	unsigned int sec;
	unsigned int msec;
} realtime_t;

// The current time 
extern realtime_t current_time;

void timer_init (void);