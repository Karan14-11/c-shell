#include "terminal.h"
#include "warp_run.c"

iv warp_tok(char *str, iv vals)
{
   const char delimiter[2] = " ";
   char *token;

   token = strtok(str, delimiter);

   while (token != NULL)
   {

      vals = warp_run(token,vals);
      token = strtok(NULL, delimiter);
   }

   return vals;
}