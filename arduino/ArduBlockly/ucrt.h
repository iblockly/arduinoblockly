
#ifndef _UCRT_H_
#define _UCRT_H_

///////////////////////////////////////////////////////
// String

char *get_string_end(char *pstr);
char *skip_space(char *pstr);
char *next_number(char *pstr);

char isdecdigit(char ch);
char *insert_numberstring(char *pstr, char *pistr);

#endif
