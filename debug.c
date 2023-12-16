#include <stdio.h>

#include "debug.h"

void disassembleChunk(Chunk* chunk, const char* name) {
	// print header to tell which chunk we're looking at
  printf("== %s ==\n", name);

	// crank through bytecode, disassembling each instruction
  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

static int simpleInstruction(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

int disassembleInstruction(Chunk* chunk, int offset) {
	// print byte offset of given instruction. This tells us
	// where in the chunk this instruction is.
  printf("%04d ", offset);

	// read a single byte from the bytecode at the given offset.
	// This is our opcode.
  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}

