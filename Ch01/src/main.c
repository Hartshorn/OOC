#include <stdio.h>

#include "../include/new.h"
#include "../include/Object.h"
#include "../include/Set.h"

void log_f(void *item_a, void *item_b, void *item_c, void *set);

int main()
{
  void *set    = new(Set);
  void *item_a = add(set, new(Object));
  void *item_b = add(set, new(Object));
  void *item_c = new(Object);


  log_f(item_a, item_b, item_c, set);

  if (contains(set, item_a) && contains(set, item_b))
    puts("ok");

  if(contains(set, item_c))
    puts("contains?");

  if(differ(item_a, add(set, item_a)))
    puts("differ?");

  if(contains(set, drop(set, item_a)))
    puts("drop?");

  delete(drop(set, item_b));
  delete(drop(set, item_c));

  return 0;
}

void log_f(void *item_a, void *item_b, void *item_c, void *set)
{
  fprintf(stdout, "\n\tMEMORY LAYOUT");
  fprintf(stdout, "\n---------------------------------------\n");
  fprintf(stdout, "set:\t\t%p\n", set);
  fprintf(stdout, "item_a:\t\t%p\n\tpoints to: %p\n", item_a, &item_a);
  fprintf(stdout, "item_b:\t\t%p\n\tpoints to: %p\n", item_b, &item_b);
  fprintf(stdout, "item_c:\t\t%p\n\tpoints to: %p\n", item_c, &item_c);
  fprintf(stdout, "---------------------------------------\n");
}
