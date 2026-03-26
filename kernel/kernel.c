//#include "kernel.h"
#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "layouts/kb_layouts.h"
#include "terminal/terminal.h"
#include "commands.h" // Included by Ember2819: Adds commands
#include "colors.h" // Added by MorganPG1 to centralise colors into one file

// Ember2819: Add command functionality
void process_input(unsigned char *buffer) {
    run_command(buffer, TERM_COLOR);
}

static void kmain();

__attribute__((section(".text.entry"))) // Add section attribute so linker knows this should be at the start
void _entry() {
    // Initialise display.
    vga_clear(TERM_COLOR);
    printf("----- GeckoOS v1.0 -----\n", TERM_COLOR);
    printf("Built by random people on the internet.\n", TERM_COLOR);
    printf("Use help to see available commands.\n", TERM_COLOR);

    // Setup keyboard layouts
    set_layout(LAYOUTS[0]);

    printf("Enabling tables...\n", VGA_COLOR_LIGHT_GREY);
    // init_desc_tables();
    printf("Done!", VGA_COLOR_LIGHT_GREY);
    // printf("Testing interruption...", VGA_COLOR_LIGHT_GREY);
    // asm volatile("int $0x3");
    printf("\nInterruption test completed!\n", VGA_COLOR_LIGHT_GREY);
    // init_timer(150);
    kmain(); // _entry will be the initialization
}

static void kmain()
{
    // malloc(938);
    // outb(0x64, 0xfe); // Reboots the machine? (It acts weird in QEMU, but it reboots at least)

    while (1) {    // Shell loop
        // Prints shell prompt
        printf("> ", PROMPT_COLOR);
        
        //Obtains and processes the user input
        unsigned char buff[512];
        input(buff, 512, TERM_COLOR);
        process_input(buff);

    }

    //asm volatile ("hlt");
}
