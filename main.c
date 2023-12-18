#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
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

	writeChunk(&chunk, OP_RETURN, 123);

	// disassemble all of the instructions in the entire chunk
	disassembleChunk(&chunk, "test chunk");
	freeChunk(&chunk);
  return 0;
}
