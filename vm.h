#ifndef clox_vm_h
#define clox_vm_h

// VM is one part of our interpreters architecture.
// You hand it a chunk of code (literally Chunk) and it 
// runs it.
// https://craftinginterpreters.com/a-virtual-machine.html#an-instruction-execution-machine

#include "chunk.h"

typedef struct {
  Chunk* chunk;
	// ip always points to the NEXT instruction about to be executed
	uint8_t* ip; 
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);

#endif
