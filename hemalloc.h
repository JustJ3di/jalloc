#ifndef HEMALLOC
#define HEMALLOC


#include <unistd.h>
#include <assert.h>

#define DEBUG 0

struct block_meta {
  
  size_t size;
  
  struct block_meta *next;
  
  int free;

#if DEBUG
  int magic; // For debugging 
#endif

};

#define META_SIZE sizeof(struct block_meta)

void *global_base = NULL;

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  
  struct block_meta *current = global_base;

  while (current && !(current->free && current->size >= size)) {

    *last = current;

    current = current->next;

  }

  return current;

}

struct block_meta *request_space(struct block_meta* last, size_t size) {

    struct block_meta *block;

    block = sbrk(0);

    void *request = sbrk(size + META_SIZE); //offset request

    assert((void*)block == request); 
    
    if (request == (void*) -1) 
    {
        return NULL; // sbrk failed.
    }

    if (last) 
    { // NULL on first request.
        last->next = block;
    }
    block->size = size;

    block->next = NULL;//block is the new head
    
    block->free = 0;

#if DEBUG
    block->magic = 0x12345678;
#endif

    return block;
}

void *malloc(size_t size) {

    struct block_meta *block;
    // TODO: align size?

    if (size <= 0) 
    {
        return NULL;
    }

    if (!global_base) 
    { // First call.
        block = request_space(NULL, size);
        if (!block) {
            return NULL;
    }
    
    global_base = block;

    } else 
    {
        struct block_meta *last = global_base;
        block = find_free_block(&last, size);

        if (!block) 
        { // Failed to find free block.
            block = request_space(last, size);
        
            if (!block) 
            {
                return NULL;
            }


        } else 
        {     
          
             // Found free block
            block->free = 0;

#if DEBUG
            block->magic = 0x77777777;
#endif

        }
    }

    return(block+1);
}

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}


void free(void *ptr) {
  if (!ptr) {
    return;
  }

  struct block_meta* block_ptr = get_block_ptr(ptr);

  assert(block_ptr->free == 0);

#if DEBUG
    assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
#endif
 
  block_ptr->free = 1;

#if DEBUG
    block_ptr->magic = 0x55555555;
#endif

}

#endif 


