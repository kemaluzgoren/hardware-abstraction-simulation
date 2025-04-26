#ifndef GPIO_SIM_H_
#define GPIO_SIM_H_

#include <stdbool.h>
#include <stdint.h>


// GPIO Configuration
typedef struct {
    const char *name; 
    bool initial_state; 
    void *platform_config; 
}gpio_config_t; 


// GPIO Interface
typedef struct {
    void *context; 
    void(*set)(void *context);
    void(*reset)(void *context);
    bool(*read)(void *context);
}gpio_interface_t; 


// Create & Destroy Functions
gpio_interface_t *gpio_sim_create(gpio_config_t *cfg);
void gpio_sim_destroy(gpio_interface_t *iface);

#endif  /*  GPIO_SIM_H_ */