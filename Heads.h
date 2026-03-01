#ifndef HEADS_H
#define HEADS_H

#include "Forms.h"

FILE *Open_Form_file(char *method);
void Close_file(FILE *file);

void Save_form(Form form);
void Save_and_free_form(Form form);

char *Get_next_line_of_file(FILE *file);
Token_content *Get_next_token_content_from_file(FILE *file, char *delimiter);

LS_form *Read_LS_form(FILE *file);
LC_form *Read_LC_form(FILE *file);
DP_form *Read_DP_form(FILE *file);
DM_form *Read_DM_form(FILE *file);
Form Read_form();
Form Read_print_pid_and_form(char *title, int do_print_pid);

#endif