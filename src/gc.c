#include <assert.h>
#include <stdlib.h>
#include "gc.h"

/*
 *      This reference counting garbage collector works by simply storing a
 *      reference count next to the allocated memory in the following way:
 *
 *          [reference count][allocated memory]
 *
 *      When it gets a call to gc_malloc it simply allocates the give size plus
 *      sizeof(int), and whenever it gets a call to gc_register or gc_free it
 *      shifts the address over by the size of an int to inspect the reference
 *      count.
 *
 */

// Allocates a contiguous piece of garbage-collected memory of a certain size
void *gc_malloc(size_t size) {
    void *allocated = malloc(size + sizeof(int));

    *(int *) allocated = 1;

    return allocated + sizeof(int);
}

// Registers use of a certain piece of memory. IE takes a pointer to an
// already-allocated piece of memory and increments the reference counter for
// this memory.
void gc_register(void *address) {
    address = address - sizeof(int);
    int *reference_count = (int *) address;
    assert(*reference_count > 0);

    (*reference_count)++;
}

// Unregisters use of the memory pointed to by ptr. If the reference counter is
// zero at this point the memory can be safely freed, otherwise it must be kept
// intact. 

// denne funksjonen ble skrevet med chatgpt.com; loggen er vedlagt som fil
// chatlog_1.txt
void gc_free(void *address) {
    if (address == NULL) {
        return; // No action needed for NULL pointers
    }

    // Move the address pointer back to access the reference count
    int *reference_count = (int *)(address - sizeof(int));

    assert(*reference_count > 0);

    // Decrement the reference count
    (*reference_count)--;

    // If the reference count reaches zero, free the allocated memory
    if (*reference_count == 0) {
        free(reference_count);
    }
}
