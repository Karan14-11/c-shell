#include "terminal.h"
#include "def_term.c"

iv tokenise(char *str, iv vals)
{

   // const char delimiter[2] = ";";
   char *token = malloc(MaxLimit);
   int length = strlen(str);
   int cnt = 0;
   for (int i = 0; i < length; i++)
   {
      if (str[i] == ';')
         cnt++;
   }
   int c = 0;

   for (int i = 0; i <= cnt; i++)
   {
      int j = 0;
      while (str[c] != ';' && str[c] != '\0')
      {
         token[j++] = str[c++];
      }
      token[j++] = '\0';
      c++;
      vals = default_terminal(token, vals);
   }
   free(token);

   return vals;
}