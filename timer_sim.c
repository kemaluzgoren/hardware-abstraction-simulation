#include "timer_sim.h"
#include <unistd.h>
#include <sys/time.h>

static void sim_delay_ms(uint32_t ms) {
    usleep(ms * 1000);  // POSIX usleep type micro min
}

static uint32_t sim_get_tick_ms(void) {
    struct timeval tv; 
    gettimeofday(&tv, NULL); 
    return (uint32_t)((tv.tv_sec*1000) + (tv.tv_usec/1000));
}

timer_interface_t timer_sim_create(void) {
    timer_interface_t iface = {
        .delay_ms = sim_delay_ms, 
        .get_tick_ms = sim_get_tick_ms
    }; 

    return iface; 
}