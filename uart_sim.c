#include "uart_sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int port_num; 
    uint32_t baudrate; 
}uart_sim_internal_t; 

static bool uart_sim_init(void *context, uint32_t baudrate) {
    uart_sim_internal_t *internal = (uart_sim_internal_t*)context;

    internal->baudrate = baudrate; 
    printf("[UART] Simulated UART initialized at %u baud\n", baudrate); 
    return true; 
}

static int uart_sim_write(void *context, const uint8_t *data, size_t len) {
    (void)context; 

    printf("[UART TX]"); 
    fwrite(data, 1, len, stdout); 
    printf("\n"); 
    return (int)len; 
}

static int uart_sim_read(void *context, uint8_t *buffer, size_t len) {
    (void)context; 

    printf("[UART RX] Enter data: ");
    if(fgets((char *)buffer, (int)len, stdin) != NULL) {
        size_t rlen = strlen((char *)buffer); 
        if(rlen > 0 && buffer[rlen - 1] == '\n') {
            buffer[rlen-1] = '\0'; 
            --rlen; 
        }

        return (int)rlen; 
    }

    return -1; 
}

uart_interface_t *uart_sim_create(uart_config_t *cfg) {

    if(!cfg) {
        return NULL;
    }

    uart_interface_t *iface = malloc(sizeof(uart_interface_t)); 
    if(!iface) {
        return NULL; 
    }

    uart_sim_internal_t *internal = malloc(sizeof(uart_sim_internal_t));
    if(!internal) {
        free(iface); 
        return NULL;
    }

    internal->port_num = cfg->port_num; 
    internal->baudrate = cfg->baudrate; 

    iface->context = internal; 
    iface->init = uart_sim_init; 
    iface->write = uart_sim_write; 
    iface->read = uart_sim_read; 

    return iface; 
}

void uart_sim_destroy(uart_interface_t *iface) {
    if(!iface) {
        return; 
    }

    if(iface->context){
        free(iface->context);
    }
    free(iface); 
}

