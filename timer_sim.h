#ifndef TIMER_SIM_H_
#define TIMER_SIM_H_

#include <stdint.h>

typedef struct {
    void (*delay_ms)(uint32_t ms); 
    uint32_t (*get_tick_ms)(void); 
}timer_interface_t; 

timer_interface_t timer_sim_create(void); 

#endif  /*  TIMER_SIM_H_ */