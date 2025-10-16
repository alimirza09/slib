#include "stdlib.h"
#include "unistd.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/syscall.h>

#define ALIGN 16u
#define ALIGN_MASK (ALIGN - 1)

static inline size_t align_up(size_t v) {
  return (v + ALIGN_MASK) & ~ALIGN_MASK;
}

typedef struct block {
  size_t size;
  struct block *next;
  int free;
} block_t;

#define BLOCK_HEADER_SIZE align_up(sizeof(block_t))

static void *heap_start = NULL;

static block_t *free_list = NULL;

void *sbrk(ptrdiff_t increment) {
  static void *curr_brk = 0;

  if (curr_brk == 0)
    curr_brk = (void *)syscall(11, 0, 0, 0, 0, 0);

  if (increment == 0)
    return curr_brk;

  void *new_brk = (char *)curr_brk + increment;
  void *res = (void *)syscall(11, (long)new_brk, 0, 0, 0, 0);

  if (res == (void *)-1 || res < new_brk)
    return (void *)-1;

  void *old = curr_brk;
  curr_brk = res;
  return old;
}

static void *raw_sbrk_alloc(size_t size) {
  size_t total = align_up(size);
  void *old = sbrk((ptrdiff_t)total);
  if (old == (void *)-1)
    return NULL;
  return old;
}

static block_t *find_free_block(block_t **prev_out, size_t size) {
  block_t *prev = NULL;
  block_t *cur = free_list;
  while (cur) {
    if (cur->free && cur->size >= size) {
      if (prev_out)
        *prev_out = prev;
      return cur;
    }
    prev = cur;
    cur = cur->next;
  }
  if (prev_out)
    *prev_out = prev;
  return NULL;
}

static block_t *request_space(block_t *last, size_t size) {
  size_t total = BLOCK_HEADER_SIZE + size;
  void *p = sbrk((ptrdiff_t)total);
  if (p == (void *)-1) {
    return NULL;
  }
  block_t *b = (block_t *)p;
  b->size = size;
  b->next = NULL;
  b->free = 0;

  if (last) {
    last->next = b;
  }

  return b;
}

static inline block_t *ptr_to_block(void *ptr) {
  if (!ptr)
    return NULL;
  return (block_t *)((char *)ptr - BLOCK_HEADER_SIZE);
}

static inline void *block_to_ptr(block_t *b) {
  return (void *)((char *)b + BLOCK_HEADER_SIZE);
}

void *malloc(size_t size) {
  if (size == 0)
    return NULL;
  size = align_up(size);

  if (!heap_start) {
    void *curr = brk((void *)0);
    if (curr == (void *)-1 || curr == NULL) {
      curr = sbrk(0);
    }
    heap_start = curr;
    free_list = NULL;
  }

  block_t *prev = NULL;
  block_t *b = find_free_block(&prev, size);
  if (b) {
    b->free = 0;
    size_t remain = b->size - size;
    if (remain > BLOCK_HEADER_SIZE + ALIGN) {
      block_t *newb = (block_t *)((char *)block_to_ptr(b) + size);
      newb->size = remain - BLOCK_HEADER_SIZE;
      newb->free = 1;
      newb->next = b->next;
      b->next = newb;
      b->size = size;
    }
    return block_to_ptr(b);
  }

  block_t *last = NULL;
  if (free_list) {
    block_t *t = free_list;
    while (t->next)
      t = t->next;
    last = t;
  }

  block_t *nb = request_space(last, size);
  if (!nb)
    return NULL;

  if (!free_list) {
    free_list = nb;
  }
  return block_to_ptr(nb);
}

void free(void *ptr) {
  if (!ptr)
    return;
  block_t *b = ptr_to_block(ptr);
  b->free = 1;

  block_t *cur = free_list;
  while (cur && cur->next) {
    if (cur->free && cur->next->free) {
      cur->size = cur->size + BLOCK_HEADER_SIZE + cur->next->size;
      cur->next = cur->next->next;
      continue;
    }
    cur = cur->next;
  }
}

void *calloc(size_t nmemb, size_t size) {
  size_t total = nmemb * size;
  void *p = malloc(total);
  if (!p)
    return NULL;
  memset(p, 0, total);
  return p;
}

void *realloc(void *ptr, size_t size) {
  if (!ptr) {
    return malloc(size);
  }
  if (size == 0) {
    free(ptr);
    return NULL;
  }

  block_t *b = ptr_to_block(ptr);
  if (b->size >= size) {
    return ptr;
  }

  void *newp = malloc(size);
  if (!newp)
    return NULL;
  memcpy(newp, ptr, b->size);
  free(ptr);
  return newp;
}

void abort(void) {
  extern void _exit(int status);
  _exit(1);
  for (;;) {
  }
}
