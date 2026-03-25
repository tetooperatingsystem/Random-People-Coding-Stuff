// Pumpkicks

#ifndef _IRQ_H
#define _IRQ_H

// Irqs
#include <stdint.h>
#include "../isr/isr.h"

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(uint8_t n, isr_t handler); 

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

typedef struct irq_value {
    uint16_t base;
    uint8_t num;
} irq_value;

static const irq_value ire_table[] = {
    {0x20, 0x11},
    {0xA0, 0x11},
    {0x21, 0x20},
    {0xA1, 0x28},
    {0x21, 0x04},
    {0xA1, 0x02},
    {0x21, 0x01},
    {0xA1, 0x01},
    {0x21, 0x0},
    {0xA1, 0x0}
};

void register_interrupt_handler(uint8_t n, isr_t handler);
void irq_handler(registers_t regs);

#endif