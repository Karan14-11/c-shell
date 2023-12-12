#include "terminal.h"
#include "functions.h"


iv warp_fn(char *str, int start, iv vals)
{
   int length = strlen(str);
   start = start + 4;
   char *warp_args = malloc(length - start + 10);
   int c = 0;
   for (int i = start; i <= length; i++)
      warp_args[c++] = str[i];
   vals= warp_tok(warp_args,vals);
   return vals;
}