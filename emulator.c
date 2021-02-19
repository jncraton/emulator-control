#include <stdio.h>
#include <string.h>

// Define operations
typedef enum {Halt, LoadImmediate, Add, AddImmediate, And, Or, Xor, Jump, BranchOnEqual}  __attribute__ ((__packed__)) Operation;

// Define registers
typedef enum {R0, R1, R2, R3, R4, IP, FLAGS}  __attribute__ ((__packed__)) Register;

// Define instruction format
typedef struct {
  Operation op;
  Register src;
  Register dst;
  signed char immediate;
} Instruction;

void print_registers(int * registers) {
  // Helper function to print register contents for debugging
  printf("IP: %d ", registers[IP]);
  for (int i = 0; i<5; i++) {
    printf("R%d: %d ", i, registers[i+1]);
  }
  printf("\n");
}

void print_instruction(Instruction inst) {
  // Helper function to print instruction information for debugging
  static char* instruction_names[6] = {"Halt", "LoadImmediate", "Add", "AddImmediate", "And", "Or", "Xor", "Jump", "BranchOnEqual"};

  printf("%s src=%d dst=%d imm=%d\n", instruction_names[inst.op], inst.src, inst.dst, inst.immediate);
}

void execute(Instruction * instructions, int * registers) {
}

/* 
Test code 

It is not recommended to modify any code below this point
*/

#define test_int_equal(exp, result) \
printf("Test %s == %d ", #exp, result); \
if ((exp) != result) { \
  printf("FAILED as %d.\n", exp); \
} else { \
  printf("succeeded.\n"); \
}

#define test_float_equal(exp, result) \
printf("Test %s == %f ", #exp, result); \
if ((exp) != result) { \
  printf("FAILED as %f.\n", exp); \
} else { \
  printf("succeeded.\n"); \
}

int main() {
  printf("Halt Tests\n");
  Instruction halt_instructions[4]={
    {Halt, 0, 0, 0}
  };
  int registers[6] = {0,0,0,0,0,0};
  execute(halt_instructions, registers);
  test_int_equal(registers[IP], 0);
  test_int_equal(registers[R0], 0);
  test_int_equal(registers[R1], 0);
  test_int_equal(registers[R2], 0);

  printf("Load Immediate Tests\n");
  Instruction load_imm_instructions[4]={
    {LoadImmediate, 0, R0, 1},
    {LoadImmediate, 0, R1, 80},
    {LoadImmediate, 0, R2, 13},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(load_imm_instructions, registers);
  test_int_equal(registers[IP], 3);
  test_int_equal(registers[R0], 1);
  test_int_equal(registers[R1], 80);
  test_int_equal(registers[R2], 13);

  printf("Add Tests\n");
  Instruction add_instructions[4]={
    {LoadImmediate, 0, R0, 42},
    {LoadImmediate, 0, R1, 100},
    {Add, R0, R1, 0},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(add_instructions, registers);
  test_int_equal(registers[IP], 3);
  test_int_equal(registers[R0], 42);
  test_int_equal(registers[R1], 142);
  test_int_equal(registers[R2], 0);

  printf("Add Immediate Tests\n");
  Instruction addi_instructions[6]={
    {AddImmediate, R0, R0, 1},
    {AddImmediate, R0, R0, 2},
    {AddImmediate, R1, R1, 21},
    {AddImmediate, R1, R1, 30},
    {AddImmediate, R1, R2, 1},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(addi_instructions, registers);
  test_int_equal(registers[IP], 5);
  test_int_equal(registers[R0], 3);
  test_int_equal(registers[R1], 51);
  test_int_equal(registers[R2], 52);

  printf("Bitwise Tests\n");
  Instruction bitwise_instructions[9]={
    {LoadImmediate, 0, R0, 1},
    {LoadImmediate, 0, R1, 1},
    {And, R0, R1},
    {LoadImmediate, 0, R2, 0},
    {Or, R0, R2},
    {LoadImmediate, 0, R3, 0},
    {Xor, 0, R0, R3},
    {Xor, 0, R0, R3},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(bitwise_instructions, registers);
  test_int_equal(registers[IP], 8);
  test_int_equal(registers[R1], 1);
  test_int_equal(registers[R2], 1);
  test_int_equal(registers[R3], 0);


  printf("Jump Tests\n");
  Instruction jump_instructions[4]={
    {LoadImmediate, 0, R0, 1},
    {Jump, 0, 0, 3},
    {LoadImmediate, 0, R1, 2},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(jump_instructions, registers);
  test_int_equal(registers[IP], 3);
  test_int_equal(registers[R0], 1);
  test_int_equal(registers[R1], 0);
  test_int_equal(registers[R2], 0);

  printf("BranchOnEqual equal test\n");
  Instruction beq_instructions[5]={
    {LoadImmediate, 0, R0, 1},
    {LoadImmediate, 0, R1, 1},
    {BranchOnEqual, R0, R1, 4},
    {Halt, 0, 0, 0},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(beq_instructions, registers);
  test_int_equal(registers[IP], 4);
  test_int_equal(registers[R0], 1);
  test_int_equal(registers[R1], 1);
  test_int_equal(registers[R2], 0);

  printf("BranchOnEqual not equal Test\n");
  Instruction beq2_instructions[5]={
    {LoadImmediate, 0, R0, 1},
    {LoadImmediate, 0, R1, 2},
    {BranchOnEqual, R0, R1, 4},
    {Halt, 0, 0, 0},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(beq2_instructions, registers);
  test_int_equal(registers[IP], 3);
  test_int_equal(registers[R0], 1);
  test_int_equal(registers[R1], 2);
  test_int_equal(registers[R2], 0);

  printf("Extended Tests\n");
  Instruction ext_instructions[11]={
    {LoadImmediate, 0, R0, 1},
    {LoadImmediate, 0, R1, 12},
    {LoadImmediate, 0, R2, 100},
    {Add, R0, R1, 0},
    {Add, R2, R1, 0},
    {Add, R2, R1, 0},
    {LoadImmediate, 0, R0, -12},
    {Add, R0, R1, 0},
    {LoadImmediate, 0, R0, 1},
    {LoadImmediate, 0, R2, 3},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(ext_instructions, registers);
  test_int_equal(registers[IP], 10);
  test_int_equal(registers[R0], 1);
  test_int_equal(registers[R1], 201);
  test_int_equal(registers[R2], 3);

  printf("Loop Test\n");
  Instruction loop_instructions[11]={
    {LoadImmediate, 0, R0, 0}, // Stays zero
    {LoadImmediate, 0, R1, -1}, // Stays -1
    {LoadImmediate, 0, R2, 11}, // Loop counter
    {LoadImmediate, 0, R3, 3}, // Stays 3
    {LoadImmediate, 0, R4, 0}, // Counting by 3s
    // Decrement loop counter
    {Add, R1, R2, 0}, // Instruction 5
    {BranchOnEqual, R2, R0, 10}, // Exit loop
    // Increment output
    {Add, R3, R4, 0},
    {Jump, 0, 0, 5},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(loop_instructions, registers);
  test_int_equal(registers[IP], 10);
  test_int_equal(registers[R0], 0);
  test_int_equal(registers[R1], -1);
  test_int_equal(registers[R2], 0);
  test_int_equal(registers[R3], 3);
  test_int_equal(registers[R4], 30);
}