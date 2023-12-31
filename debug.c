#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
	// print header to tell which chunk we're looking at
  printf("== %s ==\n", name);

	// crank through bytecode, disassembling each instruction
  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

static int constantInstruction(const char* name, Chunk* chunk,
                               int offset) {
	// pull out the constant index from the subsequent byte
	// in the chunk.
  uint8_t constantIdx = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constantIdx);
  printValue(chunk->constants.values[constantIdx]);
  printf("'\n");

	return offset+2; // OP_CONSTANT is two bytes: 1 for opcode, 1 for operand
}

static int simpleInstruction(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

int disassembleInstruction(Chunk* chunk, int offset) {
	// print byte offset of given instruction. This tells us
	// where in the chunk this instruction is.
  printf("%04d ", offset);

	if (offset > 0 &&
			chunk->lines[offset] == chunk->lines[offset - 1]) {
		// show a | for any instruction coming from the same source line
		// as the preceding one.
		printf("   | ");
	} else {
		// source line
		printf("%4d ", chunk->lines[offset]);
	}

	// read a single byte from the bytecode at the given offset.
	// This is our opcode.
  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
		case OP_CONSTANT:
				return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_ADD:
      return simpleInstruction("OP_ADD", offset);
    case OP_SUBTRACT:
      return simpleInstruction("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
      return simpleInstruction("OP_MULTIPLY", offset);
    case OP_DIVIDE:
      return simpleInstruction("OP_DIVIDE", offset);
		case OP_NEGATE:
				return simpleInstruction("OP_NEGATE", offset);
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}

