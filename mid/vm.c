#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int regs[4];             
    unsigned char memory[256];
    int pc;                  
    int running;             
} VM;

enum {
    LOAD = 0x01,
    ADD  = 0x02,
    SUB  = 0x03,
    MOV  = 0x04,
    JMP  = 0x05,
    JZ   = 0x06,
    HALT = 0xFF
};

void execute(VM *vm) {
    while (vm->running) {
        unsigned char opcode = vm->memory[vm->pc++];
        switch (opcode) {
            case LOAD: {
                int reg = vm->memory[vm->pc++];
                int val = vm->memory[vm->pc++];
                vm->regs[reg] = val;
                printf("LOAD R%d <- %d\n", reg, val);
                break;
            }
            case ADD: {
                int r1 = vm->memory[vm->pc++];
                int r2 = vm->memory[vm->pc++];
                vm->regs[r1] += vm->regs[r2];
                printf("ADD R%d <- R%d (result: %d)\n", r1, r2, vm->regs[r1]);
                break;
            }
            case SUB: {
                int r1 = vm->memory[vm->pc++];
                int r2 = vm->memory[vm->pc++];
                vm->regs[r1] -= vm->regs[r2];
                printf("SUB R%d <- R%d (result: %d)\n", r1, r2, vm->regs[r1]);
                break;
            }
            case MOV: {
                int r1 = vm->memory[vm->pc++];
                int r2 = vm->memory[vm->pc++];
                vm->regs[r1] = vm->regs[r2];
                printf("MOV R%d <- R%d (result: %d)\n", r1, r2, vm->regs[r1]);
                break;
            }
            case JMP: {
                int addr = vm->memory[vm->pc++];
                vm->pc = addr;
                printf("JMP to %d\n", addr);
                break;
            }
            case JZ: {
                int reg = vm->memory[vm->pc++];
                int addr = vm->memory[vm->pc++];
                if (vm->regs[reg] == 0) {
                    vm->pc = addr;
                    printf("JZ R%d == 0, jumping to %d\n", reg, addr);
                } else {
                    printf("JZ R%d != 0, no jump\n", reg);
                }
                break;
            }
            case HALT: {
                vm->running = 0;
                printf("HALT\n");
                break;
            }
            default:
                printf("Unknown instruction: 0x%02X\n", opcode);
                vm->running = 0;
        }
    }
}

void load_program(VM *vm, unsigned char *program, size_t size) {
    for (size_t i = 0; i < size; i++) {
        vm->memory[i] = program[i];
    }
}

int main() {
    VM vm = {0};
    vm.running = 1;

    unsigned char program[] = {
        LOAD, 0, 5,     // R0 = 5
        LOAD, 1, 3,     // R1 = 3
        ADD,  0, 1,     // R0 = R0 + R1
        JZ,   0, 12,    // if R0 == 0 jump to HALT
        SUB,  0, 1,     // R0 = R0 - R1
        HALT            // stop
    };

    load_program(&vm, program, sizeof(program));
    execute(&vm);

    printf("\nFinal Registers:\n");
    for (int i = 0; i < 4; i++) {
        printf("R%d: %d\n", i, vm.regs[i]);
    }

    return 0;
}
