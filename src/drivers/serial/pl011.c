/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <stdint.h>
#include <util.h>
#include <machine/io.h>
#include <plat/machine/devices_gen.h>

#define UARTDR                    0x000
#define UARTFR                    0x018

#define PL011_UARTFR_TXFF         BIT(5)
#define PL011_UARTFR_RXFE         BIT(4)

#define UART_REG(x) ((volatile uint32_t *)(UART_PPTR + (x)))

#if defined(CONFIG_DEBUG_BUILD) || defined(CONFIG_PRINTING)
void putDebugChar(unsigned char c)
{
    while ((*UART_REG(UARTFR) & PL011_UARTFR_TXFF) != 0);

    *UART_REG(UARTDR) = c;
}
#endif

#ifdef CONFIG_DEBUG_BUILD
unsigned char getDebugChar(void)
{
    while ((*UART_REG(UARTFR) & PL011_UARTFR_RXFE) != 0);

    return *UART_REG(UARTDR);
}
#endif //CONFIG_DEBUG_BUILD
