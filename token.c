#include "terminal.h"
#include "functions.h"


iv tokenise(char *str, iv vals)
{


   const char delimiter[2] = ";";
   char *token;

   token = strtok(str, delimiter);

   while (token != NULL)
   {

      vals = default_terminal(token,vals);
      token = strtok(NULL, delimiter);
   }

   return vals;
}