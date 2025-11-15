#include "isr.h"



#define X(n) isr##n,

void (*isr_table[])() = {
    X(0)  X(1)  X(2)  X(3)  X(4)
    X(5)  X(6)  X(7)  X(8)  X(9)
    X(10) X(11) X(12) X(13) X(14) NULL,
    X(16) X(17) X(18) X(19) X(20) 
    X(21)  X(28) X(29) X(30) 
    X(32) X(31)
};

#undef X

static const char* exceptionMessages[] = {
    "Divide by Zero",
};


void divideErrorHandler(registers* regs) {
    printk("\n=== DIVIDE ERROR EXCEPTION ===\n");
    printk("Attempted division by zero!\n");
    printk("Location: 0x%x\n", regs->eip);
    printk("EAX: 0x%x  EBX: 0x%x  ECX: 0x%x  EDX: 0x%x\n",
           regs->eax, regs->ebx, regs->ecx, regs->edx);
    printk("ESI: 0x%x  EDI: 0x%x  EBP: 0x%x  ESP: 0x%x\n",
           regs->esi, regs->edi, regs->ebp, regs->esp);
    printk("\nThis exception cannot be recovered from.\n");
    printk("System Halted.\n");

    while (1) {
        __asm__ volatile ("hlt");
    }
}

static void genericExceptionHandler(registers* regs) {
    printk("\n=== CPU EXCEPTION ===\n");
    printk("Exception: %s\n", exceptionMessages[regs->int_no]);
    printk("Interrupt Number: %d\n", regs->int_no);
    printk("Error Code: 0x%x\n", regs->err_code);
    printk("EIP: 0x%x\n", regs->eip);
    printk("CS: 0x%x\n", regs->cs);
    printk("EFLAGS: 0x%x\n", regs->eflags);
    printk("System Halted.\n");

    while (1) {
        __asm__ volatile ("hlt");
    }
}

void isrHandler(registers* regs) {
    switch (regs->int_no) {
        case 0:
            divideErrorHandler(regs);
            break;
        default:
            genericExceptionHandler(regs);
            break;
    }
}
