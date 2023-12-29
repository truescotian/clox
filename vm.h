#ifndef clox_vm_h
#define clox_vm_h

// VM is one part of our interpreters architecture.
// You hand it a chunk of code (literally Chunk) and it 
// runs it.
// https://craftinginterpreters.com/a-virtual-machine.html#an-instruction-execution-machine

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk* chunk;
	// ip always points to the NEXT instruction about to be executed
	uint8_t* ip; 
	Value stack[STACK_MAX];
	// stackTop points at the array element just past the element
	// containing the top value on the stack. Remember it like this:
	// stackTop points to where the next value to be pushed will go.
	Value* stackTop;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif
