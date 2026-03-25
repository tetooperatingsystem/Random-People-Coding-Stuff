#include "commands.h"
#include "colors.h"
#include "drivers/tables/descriptor_tables.h"
#include "drivers/keyboard.h"
#include "drivers/tables/irq/irq.h"
#include "drivers/tables/irq/timer.h"
#include "drivers/tables/isr/isr.h"
#include "drivers/vga.h"
#include "layouts/kb_layouts.h"
#include "terminal/terminal.h"
#include "mem.h"

// The command table
static Command commands[] = {
    { "help",  cmd_help  },
    { "hello", cmd_hello },
    { "contributors", cmd_contributors},
    { "setkeyswe", cmd_setkeyswe},
    { "setkeyus", cmd_setkeyus},
    { "setkeyuk", cmd_setkeyuk},
    { "clear", cmd_clear },
    { "version", cmd_version },
    { "init_tables", cmd_init_gdtidt },
    { "send_intr", cmd_send_intr },
    { "start_timer", cmd_start_timer },
};

static int num_commands = sizeof(commands) / sizeof(commands[0]);

// ---- Command Functions ----

static void cmd_help(uint8_t color) {
    printf("\nhelp   - show this message\n", color);
    printf("hello  - say hello\n", color);
    printf("contributors - Displays names of all contributors\n", color);
    printf("setkeyswe - Sets keyboard layout to Swedish QWERTY\n", color); // Zorx555 - Keyboard layout commands
    printf("setkeyus - Sets keyboard layout to US QWERTY\n", color);
    printf("setkeyuk - Sets keyboard layout to UK QWERTY\n", color); // MorganPG1 - Add UK Keyboard layout
    printf("clear  - clear the screen\n", color); //ember
    printf("version - Version of the operating system\n", color); // TheOtterMonarch - Output version of the OS
    printf("init_tables - Inits descriptor tables\n", color); // Pumpkicks - Inits the descriptor tables
    printf("send_intr - Sends an interruption\n", color); // Pumpkicks - Sends the interruption 0x3
    printf("start_timer - Starts a timer within 50Hz of velocity\n", color); // Pumpkicks - Starts the timer
}

static void cmd_hello(uint8_t color) {
    printf("\nHello, world!\n", color);
}

static void cmd_contributors(uint8_t color) {
    printf("\n--- Contributors ---\n", color);
    printf("Ember2819 - Founder\n", BOLD_COLOR);
    printf("Sifi11\n", color);
    printf("Crim\n", color);
    printf("CheeseFunnel23\n", color);
    printf("bonk enjoyer/dorito girl\n", BOLD_COLOR);
    printf("KaleidoscopeOld5841\n", color);
    printf("billythemoon\n", color);
    printf("TheGirl790\n", color);
    printf("kotofyt\n", color);
    printf("xtn59\n", color);
    printf("c-bass\n", color);
    printf("u/EastConsequence3792\n", color);
    printf("MorganPG1\n", color);
    printf("Zorx555\n", color);
    printf("mckaylap2304\n", color);
    printf("TheOtterMonarch\n", color);
    printf("Pumpkicks\n", color);
}

static void cmd_setkeyswe(uint8_t color) {
    set_layout(LAYOUTS[1]); // Changed to work with my layout system
    printf("\nKeyboard layout set to Swedish QWERTY\n", color);
}

static void cmd_setkeyus(uint8_t color) {
    set_layout(LAYOUTS[0]); // Changed to work with my layout system
    printf("\nKeyboard layout set to US QWERTY\n", color);
}

static void cmd_setkeyuk(uint8_t color) { // Added by MorganPG1
    set_layout(LAYOUTS[2]); 
    printf("\nKeyboard layout set to UK QWERTY\n", color);
}

static void cmd_clear(uint8_t color) {
    terminal_clear(color);
}

static void cmd_version(uint8_t color) {
    printf("\nCommunity OS v0.5\n", color);
}

static void cmd_init_gdtidt(uint8_t color) { // Added by Pumpkicks
    init_desc_tables();
    printf("\n", color);
}
static void cmd_send_intr(uint8_t color) {
    /*
        If the descriptor tables aren't enable. This will reboot the system.
    */
    printf("\nSending interruption 0x3", color);
    asm volatile ("int $0x3");
}
static void cmd_start_timer(uint8_t color) {
    /*
        Needs idt and gdt
    */

    printf("\nStarting timer within 50Hz\n", color);
    init_timer(50);
}
static void s(registers_t r) {
    printf("HERE\n", VGA_COLOR_WHITE);
}

// ---- dispatcher ----
static int streq(unsigned char *a, char *b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++; b++;
    }
    return *a == *b;
}

void run_command(unsigned char *input, uint8_t color) {
    // Check the input against command table
    for (int i = 0; i < num_commands; i++) {
        if (streq(input, commands[i].name)) {
            commands[i].func(color);
            return;
        }
    }
    if (strlen(input) != 0) printf("\nUnknown command. Type 'help' for available commands\n", color);
    else printf("\n", color);
}
