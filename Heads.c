#include "Heads.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defines.h"
#include "Tools.h"

FILE *Open_Form_file(char *method) {
  FILE *file = fopen(FILE_FORM, method);
  if (file == NULL) {
  }
  return (file);
}

void Close_file(FILE *file) { fclose(file); }

void Save_form(Form form) {
  FILE *file = Open_Form_file(METHOD_WRITE);

  Print_form(file, form);

  Close_file(file);
}

void Save_and_free_form(Form form) {
  Save_form(form);
  Free_form(form);
}

char *Get_next_line_of_file(FILE *file) {
  size_t length = LENGTH_READ_STRING;
  char *tmp = Create_empty_String();
  fgets(tmp, length, file);
  Remove_last_char(tmp);

  return (tmp);
}

Token_content *Get_next_token_content_from_file(FILE *file, char *delimiter) {
  char *line = Get_next_line_of_file(file);

  Token_content *token_content =
      Get_next_token_content_from_string(line, delimiter);

  free(line);
  return (token_content);
}

LS_form *Read_LS_form(FILE *file) {
  LS_form *form = Create_empty_LS_form();

  Token_content *token_content;
  do {
    token_content = Get_next_token_content_from_file(file, DELIMITER_EQUAL);
    if (token_content) {
      if (Is_string_empty(token_content->content) == FALSE) {
        if (strcmp(token_content->token, TEXT_NAME) == 0) {
          Copy_string_to_empty_string(&form->name, token_content->content);
        } else if (strcmp(token_content->token, TEXT_NIF) == 0) {
          Copy_string_to_empty_string(&form->nif, token_content->content);
        } else if (strcmp(token_content->token, TEXT_TOPIC) == 0) {
          form->topic = Get_topic_from_string(token_content->content);
        } else if (strcmp(token_content->token, TEXT_AMOUNT) == 0) {
          Copy_string_to_float(&form->amount, token_content->content);
        } else if (strcmp(token_content->token, TEXT_OPENING) == 0) {
          Get_timestamp_from_string(form->opening, token_content->content);
        } else if (strcmp(token_content->token, TEXT_START) == 0) {
          Get_timestamp_from_string(form->start, token_content->content);
        } else if (strcmp(token_content->token, TEXT_TOTAL) == 0) {
          Copy_string_to_float(&form->total, token_content->content);
        } else if (strcmp(token_content->token, TEXT_END) == 0) {
          Get_timestamp_from_string(form->end, token_content->content);
        } else if (strcmp(token_content->token, TEXT_CLOSURE) == 0) {
          Get_timestamp_from_string(form->closure, token_content->content);
        } else if (strcmp(token_content->token, TEXT_SIGNATURE) == 0) {
          Copy_string_to_empty_string(&form->signature, token_content->content);
        } else {
        }
      }

      Free_Token_content(token_content);
    }
  } while (token_content);

  return (form);
}

LC_form *Read_LC_form(FILE *file) {
  LC_form *form = Create_empty_LC_form();

  Token_content *token_content;
  do {
    token_content = Get_next_token_content_from_file(file, DELIMITER_EQUAL);
    if (token_content) {
      if (Is_string_empty(token_content->content) == FALSE) {
        if (strcmp(token_content->token, TEXT_COMPANY) == 0) {
          Copy_string_to_empty_string(&form->company, token_content->content);
        } else if (strcmp(token_content->token, TEXT_CIF) == 0) {
          Copy_string_to_empty_string(&form->cif, token_content->content);
        } else if (strcmp(token_content->token, TEXT_AMOUNT_A) == 0) {
          Copy_string_to_float(&form->amount_A, token_content->content);
        } else if (strcmp(token_content->token, TEXT_AMOUNT_B) == 0) {
          Copy_string_to_float(&form->amount_B, token_content->content);
        } else if (strcmp(token_content->token, TEXT_AMOUNT_C) == 0) {
          Copy_string_to_float(&form->amount_C, token_content->content);
        } else if (strcmp(token_content->token, TEXT_OPENING) == 0) {
          Get_timestamp_from_string(form->opening, token_content->content);
        } else if (strcmp(token_content->token, TEXT_START) == 0) {
          Get_timestamp_from_string(form->start, token_content->content);
        } else if (strcmp(token_content->token, TEXT_TOTAL) == 0) {
          Copy_string_to_float(&form->total, token_content->content);
        } else if (strcmp(token_content->token, TEXT_END) == 0) {
          Get_timestamp_from_string(form->end, token_content->content);
        } else if (strcmp(token_content->token, TEXT_CLOSURE) == 0) {
          Get_timestamp_from_string(form->closure, token_content->content);
        } else if (strcmp(token_content->token, TEXT_SIGNATURE) == 0) {
          Copy_string_to_empty_string(&form->signature, token_content->content);
        } else {
        }
      }

      Free_Token_content(token_content);
    }
  } while (token_content);

  return (form);
}

DP_form *Read_DP_form(FILE *file) {
  DP_form *form = Create_empty_DP_form();

  Token_content *token_content;
  do {
    token_content = Get_next_token_content_from_file(file, DELIMITER_EQUAL);
    if (token_content) {
      if (Is_string_empty(token_content->content) == FALSE) {
        if (strcmp(token_content->token, TEXT_NAME) == 0) {
          Copy_string_to_empty_string(&form->name, token_content->content);
        } else if (strcmp(token_content->token, TEXT_NIF) == 0) {
          Copy_string_to_empty_string(&form->nif, token_content->content);
        } else if (strcmp(token_content->token, TEXT_OPERATION) == 0) {
          Operation *operation =
              Get_operation_from_string(token_content->content);
          Add_Operation_to_DP_form(form, operation);
        } else if (strcmp(token_content->token, TEXT_OPENING) == 0) {
          Get_timestamp_from_string(form->opening, token_content->content);
        } else if (strcmp(token_content->token, TEXT_START) == 0) {
          Get_timestamp_from_string(form->start, token_content->content);
        } else if (strcmp(token_content->token, TEXT_TOTAL) == 0) {
          Copy_string_to_float(&form->total, token_content->content);
        } else if (strcmp(token_content->token, TEXT_END) == 0) {
          Get_timestamp_from_string(form->end, token_content->content);
        } else if (strcmp(token_content->token, TEXT_CLOSURE) == 0) {
          Get_timestamp_from_string(form->closure, token_content->content);
        } else if (strcmp(token_content->token, TEXT_SIGNATURE) == 0) {
          Copy_string_to_empty_string(&form->signature, token_content->content);
        } else {
        }
      }

      Free_Token_content(token_content);
    }
  } while (token_content);

  return (form);
}

DM_form *Read_DM_form(FILE *file) {
  DM_form *form = Create_empty_DM_form();

  Token_content *token_content;
  do {
    token_content = Get_next_token_content_from_file(file, DELIMITER_EQUAL);
    if (token_content) {
      if (Is_string_empty(token_content->content) == FALSE) {
        if (strcmp(token_content->token, TEXT_COMPANY) == 0) {
          Copy_string_to_empty_string(&form->company, token_content->content);
        } else if (strcmp(token_content->token, TEXT_CIF) == 0) {
          Copy_string_to_empty_string(&form->cif, token_content->content);
        } else if (strcmp(token_content->token, TEXT_CUSTOMER) == 0) {
          Customer *customer = Get_customer_from_string(token_content->content);
          Add_Customer_to_DM_form(form, customer);
        } else if (strcmp(token_content->token, TEXT_OPENING) == 0) {
          Get_timestamp_from_string(form->opening, token_content->content);
        } else if (strcmp(token_content->token, TEXT_START) == 0) {
          Get_timestamp_from_string(form->start, token_content->content);
        } else if (strcmp(token_content->token, TEXT_TOTAL) == 0) {
          Copy_string_to_float(&form->total, token_content->content);
        } else if (strcmp(token_content->token, TEXT_END) == 0) {
          Get_timestamp_from_string(form->end, token_content->content);
        } else if (strcmp(token_content->token, TEXT_CLOSURE) == 0) {
          Get_timestamp_from_string(form->closure, token_content->content);
        } else if (strcmp(token_content->token, TEXT_SIGNATURE) == 0) {
          Copy_string_to_empty_string(&form->signature, token_content->content);
        } else {
        }
      }

      Free_Token_content(token_content);
    }
  } while (token_content);

  return (form);
}

Form Read_form() {
  FILE *file = Open_Form_file(METHOD_READ);
  Form form;

  Token_content *token_content =
      Get_next_token_content_from_file(file, DELIMITER_EQUAL);

  if (strcmp(token_content->token, TEXT_TYPE) == 0) {
    if (strcmp(token_content->content, FORM_TYPE_NAMES[LS]) == 0) {
      form.ls_form = Read_LS_form(file);
    } else if (strcmp(token_content->content, FORM_TYPE_NAMES[LC]) == 0) {
      form.lc_form = Read_LC_form(file);
    } else if (strcmp(token_content->content, FORM_TYPE_NAMES[DP]) == 0) {
      form.dp_form = Read_DP_form(file);
    } else if (strcmp(token_content->content, FORM_TYPE_NAMES[DM]) == 0) {
      form.dm_form = Read_DM_form(file);
    } else {
    }
  }

  Free_Token_content(token_content);
  Close_file(file);
  return (form);
}

Form Read_print_pid_and_form(char *title, int do_print_pid) {
  Form form = Read_form();

  if (do_print_pid == TRUE) Print_PID(form, title);

  Print_Jump_Line();
  TPrint("%s\n", TEXT_I_RECEIVE);

  Print_form(stdout, form);

  return (form);
}
