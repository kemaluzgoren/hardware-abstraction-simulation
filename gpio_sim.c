#include "gpio_sim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[32]; 
    bool state; 
}sim_gpio_t; 

static void sim_set(void *context) {
    sim_gpio_t *gpio = (sim_gpio_t *)context;

    gpio->state = true; 
    printf("[GPIO] %s -> HIGH\n", gpio->name);

}

static void sim_reset(void *context) {
    sim_gpio_t *gpio = (sim_gpio_t *)context;
    
    gpio->state = false; 
    printf("[GPIO] %s -> LOW\n", gpio->name);
}

static bool sim_read(void *context) {
    sim_gpio_t *gpio = (sim_gpio_t *)context;
    return gpio->state; 
}

gpio_interface_t *gpio_sim_create(gpio_config_t *cfg){

    if(!cfg || !cfg->name) {
        return NULL;
    }

    gpio_interface_t *iface = malloc(sizeof(gpio_interface_t));

    if(!iface) {
        return NULL; 
    }

    sim_gpio_t *gpio = malloc(sizeof(sim_gpio_t));

    if(!gpio) {
        free(iface);
        return NULL; 
    }

    strncpy(gpio->name, cfg->name, sizeof(gpio->name)-1);
    gpio->name[sizeof(gpio->name) - 1] = '\0';
    gpio->state = false; 

    iface->context = gpio; 
    iface->set = sim_set; 
    iface->reset = sim_reset; 
    iface->read = sim_read; 

    return iface; 
}


void gpio_sim_destroy(gpio_interface_t *iface) {
    if(!iface) {
        return; 
    }

    if(iface->context) {
        free(iface->context);
    }
    free(iface);
}