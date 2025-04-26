#include <stdio.h>
#include <string.h>
#include "gpio_sim.h"
#include "uart_sim.h"
#include "timer_sim.h"

static gpio_interface_t *led_gpio; 
static uart_interface_t *uart; 
static timer_interface_t timer; 

void led_blink_task(gpio_interface_t *gpio, timer_interface_t *timer) {
    gpio->set(gpio->context); 
    timer->delay_ms(2000); 
    gpio->reset(gpio->context); 
    timer->delay_ms(2000); 
}

void uart_echo_task(uart_interface_t *uart) {
    char buffer[128] = { 0 }; 
    int len = uart->read(uart, (uint8_t *)buffer, sizeof(buffer)); 
    if(len > 0) {
        uart->write(uart, (const uint8_t *)"Echo: ", 6); 
        uart->write(uart, (const uint8_t *)buffer, len); 
    }
}


int main(void) {

    gpio_config_t led_cfg = {
        .name = "LED1", 
        .initial_state = false, 
        .platform_config = NULL 
    };

    uart_config_t uart_cfg = {
        .port_num = 1, 
        .baudrate = 115200, 
        .platform_config = NULL
    };


    led_gpio = gpio_sim_create(&led_cfg);
    uart = uart_sim_create(&uart_cfg);
    timer = timer_sim_create();

    uart->init(uart->context, uart_cfg.baudrate); 

    printf("The simulation is started. you can exit with Ctrl+c.");

    while (1) {
        led_blink_task(led_gpio, &timer);
        uart_echo_task(uart);
    }
    
    return 0; 
}

