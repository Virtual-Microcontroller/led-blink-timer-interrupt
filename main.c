void uart_init(void);
void uart_puts(const char *s);
void led_init(void);
void timer_init_1hz(void);

int main(void)
{
    uart_init();
    led_init();
    timer_init_1hz();

    for (;;) { }
}
