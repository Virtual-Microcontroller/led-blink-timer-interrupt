# CK-RA6M5 Timer LED Blink

Bare-metal C demo for the Renesas CK-RA6M5 board (R7FA6M5B, ARM Cortex-M33).
Initialises UART, LED (PORT1 pin 5), and a 1 Hz GPT0 timer interrupt that
blinks the LED, printing "on" and "off" over SCI0 each tick.

## Build

Requirements: `arm-none-eabi-gcc` (13.2) and GNU Make.

```bash
make
```

Produces `app.elf` and `app.hex`.

## Run in Renode

Requirements: Renode on your `PATH`.

```bash
make test
```

Loads `app.elf` onto the CK-RA6M5 platform and expects alternating `on`/`off`
messages on SCI0.

## Structure

- `link.ld` - memory layout (flash 0x0, SRAM 0x20000000, 512K)
- `startup.c` - vector table, data/BSS init, and reset handler
- `uart.c` - SCI0 UART driver (base 0x40118000)
- `led.c` - GPIO LED driver for PORT1 pin 5 (base 0x400C0000)
- `timer.c` - GPT0 compare-match timer at 1 Hz with IRQ handler (base 0x40188000)
- `main.c` - entry point: inits peripherals and idles

## CI

Every push to GitHub builds, verifies in Renode, and uploads `app.elf` as an
artifact. Add the `BACKEND_WEBHOOK_URL` and `BACKEND_WEBHOOK_SECRET` repository
secrets to notify the simulator backend.
