#include "Boxofficer.h"

#include <err.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "Chief.h"
#include "Defines.h"
#include "Heads.h"
#include "Tools.h"

Form form_boxofficer;
char *response;
int status;

char *Ask_User(char *message) {
  size_t length = LENGTH_READ_STRING;

  Free_String(response);
  response = Create_empty_String();

  printf("%s%s ", message, QUESTION);

  int n_chars = getline(&response, &length, stdin);
  if (n_chars == EOF) {
    clearerr(stdin);
    printf("\n\n");
    status = STATUS_REPEAT;
    Free_String(response);
    response = NULL;
    return (NULL);
  }

  if (response[strlen(response) - 1] == '\n') {
    Remove_last_char(response);
  } else {
    clearerr(stdin);
    printf("\n");
  }
  return (response);
}

char *Ask_User_String(char *message) {
  char *tmp = NULL;

  while (1) {
    tmp = NULL;
    response = Ask_User(message);
    if (status == STATUS_REPEAT) break;

    tmp = Create_empty_String();
    strcpy(tmp, response);

    Free_String(response);
    response = NULL;

    if (strcmp(tmp, "") != 0) {
      return (tmp);
    }

    Free_String(tmp);
    fprintf(stderr, "%s\n", ANSWER_INCORRECT_STRING);
  }

  return (tmp);
}

float Ask_User_Float(char *message) {
  char *tmp = "";
  float number = -1;

  while (number == -1) {
    tmp = Ask_User_String(message);
    if (status == STATUS_REPEAT) break;

    if (Check_float(tmp) == 1) {
      number = atof(tmp);
    }

    Free_String(tmp);
  }

  return (number);
}

Topic Ask_User_Topic(char *message) {
  Topic choice = DEFAULT;

  while ((int)choice == DEFAULT) {
    response = Ask_User(message);
    if (status == STATUS_REPEAT) break;

    To_upper(&response);

    choice = Get_topic_from_string(response);

    if ((int)choice == DEFAULT) {
      fprintf(stderr, "%s\n", ANSWER_UNKNOWN_TOPIC);
    }

    Free_String(response);
    response = NULL;
  }

  return (choice);
}

Top Ask_User_Top(char *message) {
  Topic choice = DEFAULT;

  while ((int)choice == DEFAULT) {
    response = Ask_User(message);
    if (status == STATUS_REPEAT) break;

    To_upper(&response);

    choice = Get_top_from_string(response);

    if ((int)choice == EMPTY) {
      Free_String(response);
      response = NULL;
      break;
    } else if ((int)choice == DEFAULT) {
      fprintf(stderr, "%s\n", ANSWER_UNKNOWN_OPERATION);
    }

    Free_String(response);
    response = NULL;
  }

  return (choice);
}

Type_of_customer Ask_User_Type_of_customer(char *message) {
  Type_of_customer choice = DEFAULT;

  while ((int)choice == DEFAULT) {
    response = Ask_User(message);
    if (status == STATUS_REPEAT) break;

    To_upper(&response);

    choice = Get_type_of_customer_from_string(response);

    if ((int)choice == EMPTY) {
      Free_String(response);
      response = NULL;
      break;
    } else if ((int)choice == DEFAULT) {
      fprintf(stderr, "%s\n", ANSWER_UNKNOWN_CUSTOMER);
    }

    Free_String(response);
    response = NULL;
  }

  return (choice);
}

void Ask_LS_form() {
  form_boxofficer.ls_form = Create_empty_LS_form();

  form_boxofficer.ls_form->name = Ask_User_String(TEXT_NAME);
  if (status == STATUS_REPEAT) return;
  form_boxofficer.ls_form->nif = Ask_User_String(TEXT_NIF);
  if (status == STATUS_REPEAT) return;
  form_boxofficer.ls_form->topic = Ask_User_Topic(TEXT_TOPIC);
  if (status == STATUS_REPEAT) return;
  form_boxofficer.ls_form->amount = Ask_User_Float(TEXT_AMOUNT);
  if (status == STATUS_REPEAT) return;
}

void Ask_LC_form() {
  form_boxofficer.lc_form = Create_empty_LC_form();

  form_boxofficer.lc_form->company = Ask_User_String(TEXT_COMPANY);
  if (status == STATUS_REPEAT) return;
  form_boxofficer.lc_form->cif = Ask_User_String(TEXT_CIF);
  if (status == STATUS_REPEAT) return;
  form_boxofficer.lc_form->amount_A = Ask_User_Float(TEXT_AMOUNT_A);
  if (status == STATUS_REPEAT) return;
  form_boxofficer.lc_form->amount_B = Ask_User_Float(TEXT_AMOUNT_B);
  if (status == STATUS_REPEAT) return;
  form_boxofficer.lc_form->amount_C = Ask_User_Float(TEXT_AMOUNT_C);
  if (status == STATUS_REPEAT) return;
}

void Ask_Operations(DP_form *form) {
  Top top = DEFAULT;
  do {
    top = Ask_User_Top(TEXT_TYPE);
    if (status == STATUS_REPEAT) return;

    if ((int)top != EMPTY) {
      Operation *operation = Create_empty_Operation();
      operation->top = top;
      operation->amount = Ask_User_Float(TEXT_AMOUNT);
      if (status == STATUS_REPEAT) {
        Free_Operation_and_following(operation);
        return;
      }

      Add_Operation_to_DP_form(form, operation);

      top = DEFAULT;
    } else {
      break;
    }
  } while ((int)top == DEFAULT);
}

void Ask_Clients(DM_form *form) {
  Type_of_customer type_of_customer = DEFAULT;
  do {
    type_of_customer = Ask_User_Type_of_customer(TEXT_TYPE);
    if (status == STATUS_REPEAT) return;

    if ((int)type_of_customer != EMPTY) {
      Customer *customer = Create_empty_Customer();
      customer->tcustomer = type_of_customer;
      customer->ncustomer = Ask_User_String(TEXT_NAME);
      if (status == STATUS_REPEAT) {
        Free_Customer_and_following(customer);
        return;
      }
      customer->amount = Ask_User_Float(TEXT_AMOUNT);
      if (status == STATUS_REPEAT) {
        Free_Customer_and_following(customer);
        return;
      }

      Add_Customer_to_DM_form(form, customer);

      type_of_customer = DEFAULT;
    } else {
      break;
    }
  } while ((int)type_of_customer == DEFAULT);
}

void Ask_DP_form() {
  form_boxofficer.dp_form = Create_empty_DP_form();

  form_boxofficer.dp_form->name = Ask_User_String(TEXT_NAME);
  if (status == STATUS_REPEAT) return;
  form_boxofficer.dp_form->nif = Ask_User_String(TEXT_NIF);
  if (status == STATUS_REPEAT) return;

  printf("%s\n", TEXT_OPERATIONS);
  Ask_Operations(form_boxofficer.dp_form);
}

void Ask_DM_form() {
  form_boxofficer.dm_form = Create_empty_DM_form();

  form_boxofficer.dm_form->company = Ask_User_String(TEXT_COMPANY);
  if (status == STATUS_REPEAT) return;
  form_boxofficer.dm_form->cif = Ask_User_String(TEXT_CIF);
  if (status == STATUS_REPEAT) return;

  printf("%s\n", TEXT_CUSTOMERS);
  Ask_Clients(form_boxofficer.dm_form);
}

void Ask_form(Form_type form_type) {
  if (form_type == LS) {
    Ask_LS_form();
  } else if (form_type == LC) {
    Ask_LC_form();
  } else if (form_type == DP) {
    Ask_DP_form();
  } else if (form_type == DM) {
    Ask_DM_form();
  }
}

void Ask_request() {
  form_boxofficer.ls_form = NULL;
  char *request = Ask_User_String(TEXT_REQUEST);
  if (status == STATUS_REPEAT) return;

  To_upper(&request);

  Form_type form_type;

  if (strcmp(request, FORM_TYPE_NAMES[LS]) == 0) {
    form_type = LS;
  } else if (strcmp(request, FORM_TYPE_NAMES[LC]) == 0) {
    form_type = LC;
  } else if (strcmp(request, FORM_TYPE_NAMES[DP]) == 0) {
    form_type = DP;
  } else if (strcmp(request, FORM_TYPE_NAMES[DM]) == 0) {
    form_type = DM;
  } else if ((strcmp(request, QUIT) == 0) || (strcmp(request, CANCEL) == 0)) {
    Free_String(request);
    TPrint(TEXT_I_END);
    status = STATUS_DONE;
    return;
  } else {
    Free_String(request);
    fprintf(stderr, "%s\n", ANSWER_UNKNOWN_REQUEST);
    return;
  }

  Free_String(request);
  Ask_form(form_type);
  if (status == STATUS_REPEAT) {
    Free_form(form_boxofficer);
    form_boxofficer.ls_form = NULL;
  }
}

void End_boxofficer() {
  Free_form(form_boxofficer);
  Free_String(response);
  exit(EXIT_SUCCESS);
}

void Handler_boxofficer(int signal) {
  if (signal == SIGINT) {
    End_boxofficer();
  }
}

void Boxofficer() {
  form_boxofficer.ls_form = NULL;
  response = NULL;

  signal(SIGINT, Handler_boxofficer);

  TInit(NUMBER_TABS_BOX_OFFICER);
  Print_PID(form_boxofficer, TEXT_TITLE_BOX_OFFICER);

  while (status != STATUS_DONE) {
    Ask_request();
    if (status == STATUS_REPEAT) {
      status = STATUS_OK;
      continue;
    }
    if (form_boxofficer.ls_form == NULL) continue;

    Seal_print_save_and_free_form(form_boxofficer, OPENING);
    form_boxofficer.ls_form = NULL;

    Create_process_and_wait(Chief, NUMBER_TABS_CHIEF);

    TInit(NUMBER_TABS_BOX_OFFICER);
    form_boxofficer = Read_form();
    Seal_form(form_boxofficer, CLOSURE);
    Print_final_form(form_boxofficer);
    Save_and_free_form(form_boxofficer);
    form_boxofficer.ls_form = NULL;
  }
}
