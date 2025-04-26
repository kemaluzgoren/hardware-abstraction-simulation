#ifndef UART_SIM_H_
#define UART_SIM_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>


// UART Configuration
typedef struct {
    int port_num; 
    uint32_t baudrate; 
    void *platform_config; 
}uart_config_t; 


// UART Interface
typedef struct {
    void *context; 
    bool (*init)(void *context, uint32_t baudrate); 
    int (*write)(void *context, const uint8_t *data, size_t len); 
    int (*read)(void *context, uint8_t *buffer, size_t len); 
}uart_interface_t; 


// Create & Destroy Functions
uart_interface_t *uart_sim_create(uart_config_t *cfg); 
void uart_sim_destroy(uart_interface_t *iface); 


#endif  /*  UART_SIM_H_ */