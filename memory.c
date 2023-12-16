#include <stdlib.h>

#include "memory.h"

/*
  https://craftinginterpreters.com/chunks-of-bytecode.html
 This reallocate() function is the single function we’ll use for all dynamic memory management in clox—allocating memory, freeing it, and changing the size of an existing allocation. Routing all of those operations through a single function will be important later when we add a garbage collector that needs to keep track of how much memory is in use.
*/


void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
	// handle deallocation ourselves
	free(pointer);
    	return NULL;
  }

  void* result = realloc(pointer, newSize);
  return result;
}
