#include "Tools.h"

#include <ctype.h>
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Boxofficer.h"
#include "Defines.h"

static char tabs[N_TABS];

void Print_Jump_Line() { printf("\n"); }

void Print_In(char *string) { printf("%s\n", string); }

void Print_In_Hex(int length, char *string) {
  for (int i = 0; i < length; i++) {
    printf("%02x ", (unsigned char)string[i]);
  }
  printf("\n");
}

void TPrint(const char *format, ...) {
  va_list arg;

  fprintf(stdout, "%s", tabs);
  va_start(arg, format);
  vfprintf(stdout, format, arg);
  va_end(arg);
}

void TInit(int total) {
  if (total + 1 > N_TABS) {
    tabs[0] = '\0';

    return;
  }

  for (int i = 0; i < total; i++) {
    tabs[i] = '\t';
  }

  tabs[total] = '\0';
}

void TPrint_int(const char *string, int value) {
  printf("%s%s%i\n", tabs, string, value);
}

int Get_number_tabs() {
  int length_tabs = strlen(tabs);
  return (length_tabs);
}

int Random(int min, int max) {
  if (min > max) return min;

  return ((rand() % (max - min + 1)) + min);
}

void Pause(int seconds) { sleep(seconds); }

void Pause_random() { Pause(Random(NUMBER_WAIT_MIN, NUMBER_WAIT_MAX)); }

int Check_float(const char *string) {
  int has_dot = 0;

  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == '\0') break;

    if (isdigit(string[i]) == 0) {
      if ((string[i] == '.' && has_dot > 0) || string[i] != '.') {
        printf("%s\n", ANSWER_INCORRECT_AMOUNT);
        return (0);
      }
    }

    if (string[i] == '.') {
      has_dot++;
    }
  }

  return 1;
}

void Remove_last_char(char *string) {
  if (string) {
    if (strlen(string) > 0) {
      string[strlen(string) - 1] = '\0';
    }
  }
}

void Remove_first_char(char *string) {
  for (int i = 0; i < strlen(string) - 1; i++) {
    string[i] = string[i + 1];
  }
  Remove_last_char(string);
}

void Remove_first_and_last_char(char *string) {
  Remove_last_char(string);
  Remove_first_char(string);
}

void Free_String(char *string) {
  if (string) {
    free(string);
  }
}

void Copy_string_to_empty_string(char **dest, char *source) {
  if (*dest == NULL) {
    *dest = Create_empty_String();
    strcpy(*dest, source);
  }
}

void Copy_string_to_float(float *number, char *source) {
  *number = atof(source);
}

void Copy_string_to_int(int *number, char *source) { *number = atof(source); }

char *Get_string_to_print(char *string) {
  if (string) return string;
  return (QUESTION);
}

int Is_string_empty(char *string) {
  if (strcmp(string, QUESTION) == 0) return (TRUE);
  return FALSE;
}

void Print_Line(FILE *file, char *token, char *content) {
  if (file == stdout) {
    TPrint("%s%s%s\n", token, DELIMITER_EQUAL, Get_string_to_print(content));
  } else {
    fprintf(file, "%s%s%s\n", token, DELIMITER_EQUAL,
            Get_string_to_print(content));
  }
}

void Print_Line_Number(FILE *file, char *token, float number) {
  char *tmp = Create_empty_String();
  sprintf(tmp, "%.02f", number);
  Print_Line(file, token, tmp);
  free(tmp);
}

char *To_upper(char **string) {
  if (*string) {
    char *tmp = *string;

    for (int i = 0; i < strlen(tmp); i++) {
      if (tmp[i] >= 0x61 && tmp[i] <= 0x7A) {
        tmp[i] &= 0xDF;
      }
    }

    *string = tmp;
  }

  return (*string);
}

char *Create_empty_String() {
  char *tmp = (char *)calloc(sizeof(char), LENGTH_READ_STRING);
  return (tmp);
}

char *Create_unknown_String() {
  char *tmp = Create_empty_String();
  tmp = QUESTION;
  return (tmp);
}

char *Get_next_element_from_string(char *dest, char *delimiter) {
  return (strtok(dest, delimiter));
}

Token_content *Get_next_token_content_from_string(char *string,
                                                  char *delimiter) {
  if (string) {
    if (strcmp(string, "") != 0) {
      char *string_copy = Create_empty_String();
      strcpy(string_copy, string);

      Token_content *token_content = Create_empty_Token_content();
      strcpy(token_content->token,
             Get_next_element_from_string(string_copy, delimiter));
      strcpy(token_content->content,
             Get_next_element_from_string(NULL, delimiter));

      Free_String(string_copy);
      return (token_content);
    }
  }

  return (NULL);
}

float Calcualte_number_rated(float number, float rate) {
  float tmp = (number * (1 + rate));
  return (tmp);
}

void Print_PID(Form form, char *title) {
  char *tmp = title;
  if (title == NULL) {
    if (form.ls_form->request == LS) {
      tmp = TEXT_TITLE_ADMIN_LS;
    } else if (form.lc_form->request == LC) {
      tmp = TEXT_TITLE_ADMIN_LC;
    } else if (form.dp_form->request == DP) {
      tmp = TEXT_TITLE_ADMIN_DP;
    } else if (form.dm_form->request == DM) {
      tmp = TEXT_TITLE_ADMIN_DM;
    }
  }

  TPrint("%s\n", tmp);
  TPrint("%s %i\n", TEXT_MY_PID_IS, getpid());
}

void Create_process_and_wait(void (*function)(), int t_print_length) {
  pid_t pid, pid_end = 0;
  int status;

  pid = fork();
  if (pid < 0) {
  }

  else if (pid == 0) {
    TPrint("%s %i\n", TEXT_I_CREATED, getpid());

    TInit(t_print_length);
    function();
    TPrint("%s\n", TEXT_I_END);

    _exit(EXIT_SUCCESS);
  } else {
    pid_end = wait(&status);

    TInit(t_print_length - 2);
    TPrint("\n");
    TPrint("%s %i\n", TEXT_END_CAPITAL, pid_end);
  }
}
