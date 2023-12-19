#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

// Entrypoint to my interpreter!

int main(int argc, const char* argv[]) {
	initVM();

	Chunk chunk;
	initChunk(&chunk);

	// this is essentially hand-compiling an instruction to our test chunk
	// since we don't have a compiler yet. So:
	// Add the constant value itself to the chunk's constant pool.
	// The return value (constant) is the index of the constant
	// in the array.
	int constant = addConstant(&chunk, 1.2);
	writeChunk(&chunk, OP_CONSTANT, 123);
	// write a one-byte constant index operand.
	writeChunk(&chunk, constant, 123);

	constant = addConstant(&chunk, 3.4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_ADD, 123);

  constant = addConstant(&chunk, 5.6);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_DIVIDE, 123);

	writeChunk(&chunk, OP_NEGATE, 123);

	writeChunk(&chunk, OP_RETURN, 123);

	// disassemble all of the instructions in the entire chunk
	disassembleChunk(&chunk, "test chunk");

	// the entrypoint into the VM!
	interpret(&chunk);

	freeVM();
	freeChunk(&chunk);
  return 0;
}
