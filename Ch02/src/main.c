#include <stdio.h>

#include "../include/String.h"
#include "../include/new.h"

void log_f(void *a, void *b);

int main()
{
  void *a = new(String, "test a"), *aa = clone(a);
  void *b = new(String, "test b");

  log_f(a, b);

  printf("sizeof(a) == %lu\n", sizeof(a));

  if(differ(a, b))
    puts("ok");

  if(differ(a, aa))
    puts("differ?");

  if(a == aa)
    puts("clone?");

  delete(a), delete(aa), delete(b);
  return 0;
}

void log_f(void *item_a, void *item_b)
{
  fprintf(stdout, "\n\tMEMORY LAYOUT");
  fprintf(stdout, "\n---------------------------------------\n");
  fprintf(stdout, "item_a:\t\t%p\n", item_a);
  fprintf(stdout, "item_b:\t\t%p\n", item_b);
  fprintf(stdout, "---------------------------------------\n");
}
