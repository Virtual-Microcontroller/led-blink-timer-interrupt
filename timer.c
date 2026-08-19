#include <stdint.h>

#define SYST_CSR  (*(volatile uint32_t *)0xE000E010UL)
#define SYST_RVR  (*(volatile uint32_t *)0xE000E014UL)
#define SYST_CVR  (*(volatile uint32_t *)0xE000E018UL)

#define SYST_CSR_ENABLE    (1u << 0)
#define SYST_CSR_TICKINT   (1u << 1)
#define SYST_CSR_CLKSOURCE (1u << 2)
#define SYST_CSR_COUNTFLAG (1u << 16)

extern void led_toggle(void);
extern void uart_putc(char c);

static volatile uint32_t seconds;

static void print_u32(uint32_t n)
{
    char buf[11];
    int i = 10;
    buf[i] = '\0';
    do {
        buf[--i] = '0' + (char)(n % 10);
        n /= 10;
    } while (n > 0);
    const char *p = &buf[i];
    while (*p) {
        uart_putc(*p++);
    }
}

void timer_init_1hz(void)
{
    SYST_CSR = 0;
    SYST_CVR = 0;
    SYST_RVR = 32000000u - 1u;
    SYST_CSR = SYST_CSR_ENABLE | SYST_CSR_TICKINT;
}

void SysTick_Handler(void)
{
    seconds++;
    led_toggle();
    print_u32(seconds);
    uart_putc(':');
    uart_putc(' ');
    uart_putc('L');
    uart_putc('E');
    uart_putc('D');
    uart_putc(' ');
    if (seconds & 1u) {
        uart_putc('O');
        uart_putc('N');
    } else {
        uart_putc('O');
        uart_putc('F');
        uart_putc('F');
    }
    uart_putc('\r');
    uart_putc('\n');
}
