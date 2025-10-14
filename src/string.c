#include "string.h"
#include <stdint.h>

typedef uint64_t u64;
typedef unsigned long uintptr_t;

void *memcpy(void *restrict dest, const void *restrict src, size_t n) {
  unsigned char *d = dest;
  const unsigned char *s = src;

  while ((uintptr_t)s % 8 && n) {
    *d++ = *s++;
    n--;
  }
  for (; n >= 8; n -= 8, s += 8, d += 8)
    *(u64 *)d = *(const u64 *)s;
  while (n--)
    *d++ = *s++;
  return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
  unsigned char *d = dest;
  const unsigned char *s = src;

  if (d == s || n == 0)
    return dest;

  if (d < s)
    while (n--)
      *d++ = *s++;
  else {
    d += n;
    s += n;
    while (n--)
      *--d = *--s;
  }
  return dest;
}

void *memset(void *dest, int c, size_t n) {
  unsigned char *d = dest;
  while (n--)
    *d++ = (unsigned char)c;
  return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *a = s1, *b = s2;
  for (; n--; a++, b++)
    if (*a != *b)
      return *a - *b;
  return 0;
}

void *memchr(const void *s, int c, size_t n) {
  const unsigned char *p = s;
  for (; n--; p++)
    if (*p == (unsigned char)c)
      return (void *)p;
  return NULL;
}

size_t strlen(const char *s) {
  const char *p = s;
  while (*p)
    p++;
  return p - s;
}

char *strcpy(char *dest, const char *src) {
  char *d = dest;
  while ((*d++ = *src++))
    ;
  return dest;
}

char *strncpy(char *dest, const char *src, size_t n) {
  char *d = dest;
  while (n && (*d++ = *src++))
    n--;
  while (n--)
    *d++ = '\0';
  return dest;
}

char *strcat(char *dest, const char *src) {
  char *d = dest;
  while (*d)
    d++;
  while ((*d++ = *src++))
    ;
  return dest;
}

char *strncat(char *dest, const char *src, size_t n) {
  char *d = dest;
  while (*d)
    d++;
  while (n-- && (*d++ = *src++))
    ;
  *d = '\0';
  return dest;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && *s1 == *s2)
    s1++, s2++;
  return (unsigned char)*s1 - (unsigned char)*s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  for (; n && *s1 == *s2; s1++, s2++, n--)
    if (*s1 == '\0')
      return 0;
  return n ? (unsigned char)*s1 - (unsigned char)*s2 : 0;
}

char *strchr(const char *s, int c) {
  do {
    if (*s == (char)c)
      return (char *)s;
  } while (*s++);
  return NULL;
}

char *strrchr(const char *s, int c) {
  const char *last = NULL;
  do {
    if (*s == (char)c)
      last = s;
  } while (*s++);
  return (char *)last;
}

char *strstr(const char *hay, const char *needle) {
  if (!*needle)
    return (char *)hay;
  for (; *hay; hay++) {
    const char *h = hay, *n = needle;
    while (*h && *n && *h == *n)
      h++, n++;
    if (!*n)
      return (char *)hay;
  }
  return NULL;
}

size_t strspn(const char *s, const char *accept) {
  const char *p;
  size_t n = 0;
  for (; *s; s++) {
    for (p = accept; *p && *p != *s; p++)
      ;
    if (!*p)
      break;
    n++;
  }
  return n;
}

size_t strcspn(const char *s, const char *reject) {
  const char *p;
  size_t n = 0;
  for (; *s; s++) {
    for (p = reject; *p && *p != *s; p++)
      ;
    if (*p)
      break;
    n++;
  }
  return n;
}

char *strpbrk(const char *s, const char *accept) {
  for (; *s; s++) {
    const char *p;
    for (p = accept; *p; p++)
      if (*s == *p)
        return (char *)s;
  }
  return NULL;
}

char *strtok(char *str, const char *delim) {
  static char *next;
  if (!str)
    str = next;
  if (!str)
    return NULL;

  str += strspn(str, delim);
  if (!*str)
    return next = NULL, NULL;

  char *end = str + strcspn(str, delim);
  if (*end)
    *end++ = '\0';
  next = end;
  return str;
}
