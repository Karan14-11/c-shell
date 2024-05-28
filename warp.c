#include "terminal.h"
#include "warp_tok.c"

iv warp_fn(char *str, int start, iv vals)
{
   int length = strlen(str);
   start = start + 4;
   int home_dir = 0;
   char *warp_args = malloc(length - start + 10);
   int c = 0;
   for (int i = start; i <= length; i++)
      warp_args[c++] = str[i];
   vals= warp_tok(warp_args,vals);
   return vals;
}