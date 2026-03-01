#ifndef TOOLS_H
#define TOOLS_H

#include <stddef.h>
#include <stdio.h>

#include "Forms.h"

void Print_Jump_Line();
void Print_In(char *string);
void Print_In_Hex(int length, char *string);
void TPrint(const char *format, ...);
void TInit(int total);
void TPrint_int(const char *string, int value);
int Get_number_tabs();
int Random(int min, int max);
void Pause(int seconds);
void Pause_random();

int Check_float(const char *string);
void Remove_last_char(char *string);
void Remove_first_char(char *string);
void Remove_first_and_last_char(char *string);
void Free_String(char *string);
void Copy_string_to_empty_string(char **dest, char *source);
void Copy_string_to_float(float *number, char *source);
void Copy_string_to_int(int *number, char *source);

char *Get_string_to_print(char *string);
int Is_string_empty(char *string);

void Print_Line(FILE *file, char *token, char *content);
void Print_Line_Number(FILE *file, char *token, float number);
char *To_upper(char **string);

char *Create_empty_String();
char *Create_unknown_String();

char *Get_next_element_from_string(char *dest, char *delimiter);
Token_content *Get_next_token_content_from_string(char *string,
                                                  char *delimiter);

float Calcualte_number_rated(float number, float rate);

void Print_PID(Form form, char *title);
void Create_process_and_wait(void (*function)(), int t_print_length);

#endif
