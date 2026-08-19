#include <stdint.h>

#define GPIO_PORT6_BASE 0x400800C0UL
#define PORT6_PDR      (*(volatile uint16_t *)(GPIO_PORT6_BASE + 0x08))
#define PORT6_PODR     (*(volatile uint16_t *)(GPIO_PORT6_BASE + 0x00))
#define LED_BIT        (1u << 10)

void led_init(void)
{
    PORT6_PDR |= LED_BIT;
    PORT6_PODR &= (uint16_t)~LED_BIT;
}

void led_toggle(void)
{
    PORT6_PODR ^= (uint16_t)LED_BIT;
}
