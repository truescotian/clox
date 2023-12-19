#include <stdio.h>
#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm; 

static void resetStack() {
	// point to the beginning of the array to indicate
	// that the stack is empty.
	vm.stackTop = vm.stack;
}

void initVM() {
	resetStack();
}

void freeVM() {
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}


static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
	// since it takes an integer byte offset and we store the current
	// instruction reference as a direct pointer, do pointer math to convert
	// ip back to a relative offset from the beginning of the bytecode.
	// Then we disassemble the instruction that begins at that byte.
	disassembleInstruction(vm.chunk, 
			(int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
		// read the byte currently pointed at by ip
		// then advance the instruction pointer (ip).
		// Note that ip advances as soon as we read the
		// opcode, before we've actually started
		// executing the instruction, so, again, ip
		// points to the next byte of code to be used.
    switch (instruction = READ_BYTE()) {
			case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        printValue(constant);
        printf("\n");
        break;
      }
      case OP_RETURN: {
        return INTERPRET_OK;
      }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}

