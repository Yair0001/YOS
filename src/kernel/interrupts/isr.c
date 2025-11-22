#include "isr.h"

static void (*const isr_handlers[ISR_COUNT])(void) = {
    isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7,
    isr8,  isr9,  isr10, isr11, isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31
};

static const char *exception_names[] = {
    "Division Error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

void isrHandler(registers *regs) {
    printk("\n========== EXCEPTION ==========\n");

    if (regs->int_no < 32) {
        printk("Exception: %s (INT %d)\n", exception_names[regs->int_no], regs->int_no);
    } else {
        printk("Interrupt: %d\n", regs->int_no);
    }

    printk("Error Code: 0x%x\n", regs->err_code);

    printk("\n--- Registers ---\n");
    printk("EAX=0x%x  EBX=0x%x  ECX=0x%x  EDX=0x%x\n", regs->eax, regs->ebx, regs->ecx, regs->edx);
    printk("ESI=0x%x  EDI=0x%x  EBP=0x%x  ESP=0x%x\n", regs->esi, regs->edi, regs->ebp, regs->esp);

    printk("\n--- Segment Registers ---\n");
    printk("CS=0x%x  DS=0x%x  ES=0x%x  FS=0x%x  GS=0x%x  SS=0x%x\n",
           regs->cs, regs->ds, regs->es, regs->fs, regs->gs, regs->ss);

    printk("\n--- Instruction Pointer ---\n");
    printk("EIP=0x%x  EFLAGS=0x%x  UserESP=0x%x\n", regs->eip, regs->eflags, regs->useresp);

    printk("===============================\n");

    if (regs->int_no < 32) {
        printk("System halted.\n");
        for (;;) {
            __asm__ volatile("hlt");
        }
    }
}

void initISR(int amount, uint16_t selector, idtAttr attr) {
    for (int i = 0; i < amount && i < ISR_COUNT; i++) {
        setGate(i, (uint32_t)isr_handlers[i], selector, attr);
    }
}
