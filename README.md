# Embedded Portable Framework - Linux Simulation

This project demonstrates platfon-independent embedded software development principles. 
The goal is to simulate peripherals such as gpio, uart and timer through abstraction layers without relying on real hardware, running entirely on a Linux environment. 

---

## Project Structure

| Katman          | Açıklama                                          |
|-----------------|---------------------------------------------------|
| gpio_sim.*      | GPIO anstraction and simulation                   |
| uart_sim.*      | UART abstraction and terminal-based simulation    |
| timer_sim.*     | Timer abstaction (delay and tick management)      |
| main.c          | Hardware-independent application code             |

---

## Building 
To compile the project:
```bash
gcc main.c gpio_sim.c uart_sim.c timer_sim.c -o sim
```

## Running 

```bash
./sim
```

Sample terminal output
```bash
[UART1] Initialized at 115200 baud
The simulation is started. You can exit with Ctrl+C.
[GPIO] LED1 → HIGH
[GPIO] LED1 → LOW
[UART1 RX] Enter data: hello
[UART1 TX] Echo: hello
```

## Objectives

* Build a hardware-independent embedded software architecture
* Ensure portability across different platforms
* Provide a simulation and testing environment without needing physical hardware

## Related Article Series

This project is part of the [Platform-Independent Embedded Software Development](https://medium.com/@kemaluzgoren) article series.
