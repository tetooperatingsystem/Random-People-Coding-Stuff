// Pumpkicks

#include "isr.h"
#include "../../../terminal/terminal.h"
#include "../../../colors.h"

void isr_handler(registers_t regs) {
    char number_buffer[5];
    printf("\nrecieved interrrupt: ", VGA_COLOR_RED);
    printf(atoi(regs.int_no, number_buffer), PROMPT_COLOR);
    printf("\n", PROMPT_COLOR);

    // for (;;) asm volatile("hlt"); Just for debugging
} 