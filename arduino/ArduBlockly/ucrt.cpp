
// string의 마지막 null 위치 
char *get_string_end(char *pstr)
{
    while (*pstr)
        pstr++;
    return pstr;
}

char *skip_space(char *pstr)
{
   while (*pstr) {
      switch (*pstr) {
      case ' ' :
      case '\t' :
      case '\n' :
      case '\r' :
         pstr++;
         continue;
      }
   }
   return pstr;
}

char *next_number(char *pstr)
{
   char ch;

   for (ch = *pstr; ch ;pstr++, ch = *pstr) {
      if (ch >= '0' && ch <= '9')
         return pstr;
   }
   return pstr;
}

char isdecdigit(char ch)
{
  if (ch >= '0' && ch <= '9')
     return 1;
  return 0;
}

char *insert_numberstring(char *pstr, char *pistr)
{
   while (isdecdigit(*pistr))
      *pstr++ = *pistr++;
   *pstr = 0;
   return pistr;
}
