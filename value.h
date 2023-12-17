#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

// since C doesn't have generic data structures, we'll write another
// dynamic array data structure, this time for Value.
typedef struct {
  int capacity;
  int count;
  Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif
