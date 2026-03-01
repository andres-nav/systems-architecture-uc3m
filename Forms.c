#include "Forms.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "Heads.h"
#include "Tools.h"

Timestamp *Create_empty_Timestamp() {
  Timestamp *timestamp = (Timestamp *)calloc(1, sizeof(Timestamp));

  timestamp->year = 0;
  timestamp->month = 0;
  timestamp->day = 0;
  timestamp->hour = 0;
  timestamp->minute = 0;
  timestamp->second = 0;

  return (timestamp);
}

LS_form *Create_empty_LS_form() {
  LS_form *form = (LS_form *)calloc(1, sizeof(LS_form));

  form->request = LS;
  form->name = NULL;
  form->nif = NULL;
  form->topic = DEFAULT;
  form->amount = NUMBER_ZERO;
  form->opening = Create_empty_Timestamp();
  form->start = Create_empty_Timestamp();
  form->total = NUMBER_ZERO;
  form->end = Create_empty_Timestamp();
  form->closure = Create_empty_Timestamp();
  form->signature = NULL;

  return (form);
}

LC_form *Create_empty_LC_form() {
  LC_form *form = (LC_form *)calloc(1, sizeof(LC_form));

  form->request = LC;
  form->company = NULL;
  form->cif = NULL;
  form->amount_A = NUMBER_ZERO;
  form->amount_B = NUMBER_ZERO;
  form->amount_C = NUMBER_ZERO;
  form->opening = Create_empty_Timestamp();
  form->start = Create_empty_Timestamp();
  form->total = NUMBER_ZERO;
  form->end = Create_empty_Timestamp();
  form->closure = Create_empty_Timestamp();
  form->signature = NULL;

  return (form);
}

Operation *Create_empty_Operation() {
  Operation *operation = (Operation *)calloc(1, sizeof(Operation));

  operation->top = DEFAULT;
  operation->amount = NUMBER_ZERO;
  operation->following = NULL;

  return (operation);
}

Customer *Create_empty_Customer() {
  Customer *customer = (Customer *)calloc(1, sizeof(Customer));

  customer->ncustomer = NULL;
  customer->tcustomer = DEFAULT;
  customer->amount = NUMBER_ZERO;
  customer->following = NULL;

  return (customer);
}

DP_form *Create_empty_DP_form() {
  DP_form *form = (DP_form *)calloc(1, sizeof(DP_form));

  form->request = DP;
  form->name = NULL;
  form->nif = NULL;
  form->operation = NULL;
  form->opening = Create_empty_Timestamp();
  form->start = Create_empty_Timestamp();
  form->total = NUMBER_ZERO;
  form->end = Create_empty_Timestamp();
  form->closure = Create_empty_Timestamp();
  form->signature = NULL;

  return (form);
}

DM_form *Create_empty_DM_form() {
  DM_form *form = (DM_form *)calloc(1, sizeof(DM_form));

  form->request = DM;
  form->company = NULL;
  form->cif = NULL;
  form->customer = NULL;
  form->opening = Create_empty_Timestamp();
  form->start = Create_empty_Timestamp();
  form->total = NUMBER_ZERO;
  form->end = Create_empty_Timestamp();
  form->closure = Create_empty_Timestamp();
  form->signature = NULL;

  return (form);
}

Form Create_empty_form(Form_type form_type) {
  Form form;

  if (form_type == LS) {
    form.ls_form = Create_empty_LS_form();
  } else if (form_type == LC) {
    form.lc_form = Create_empty_LC_form();
  } else if (form_type == DP) {
    form.dp_form = Create_empty_DP_form();
  } else if (form_type == DM) {
    form.dm_form = Create_empty_DM_form();
  }

  return (form);
}

Token_content *Create_empty_Token_content() {
  Token_content *token_content =
      (Token_content *)calloc(1, sizeof(Token_content));

  token_content->token = Create_empty_String();
  token_content->content = Create_empty_String();

  return (token_content);
}

void Free_Timestamp(Timestamp *timestamp) {
  if (timestamp) {
    free(timestamp);
  }
}

void Free_LS_form(LS_form *form) {
  if (form) {
    Free_String(form->name);
    Free_String(form->nif);
    Free_String(form->signature);

    Free_Timestamp(form->opening);
    Free_Timestamp(form->start);
    Free_Timestamp(form->end);
    Free_Timestamp(form->closure);

    free(form);
  }
}

void Free_LC_form(LC_form *form) {
  if (form) {
    Free_String(form->company);
    Free_String(form->cif);
    Free_String(form->signature);

    Free_Timestamp(form->opening);
    Free_Timestamp(form->start);
    Free_Timestamp(form->end);
    Free_Timestamp(form->closure);

    free(form);
  }
}

void Free_Operation_and_following(Operation *operation) {
  if (operation) {
    if (operation->following) {
      Free_Operation_and_following(operation->following);
    }

    free(operation);
  }
}

void Free_Customer_and_following(Customer *customer) {
  if (customer) {
    if (customer->following) {
      Free_Customer_and_following(customer->following);
    }

    Free_String(customer->ncustomer);
    free(customer);
  }
}

void Free_DP_form(DP_form *form) {
  if (form) {
    Free_String(form->name);
    Free_String(form->nif);
    Free_String(form->signature);

    Free_Operation_and_following(form->operation);

    Free_Timestamp(form->opening);
    Free_Timestamp(form->start);
    Free_Timestamp(form->end);
    Free_Timestamp(form->closure);

    free(form);
  }
}

void Free_DM_form(DM_form *form) {
  if (form) {
    Free_String(form->company);
    Free_String(form->cif);
    Free_String(form->signature);

    Free_Customer_and_following(form->customer);

    Free_Timestamp(form->opening);
    Free_Timestamp(form->start);
    Free_Timestamp(form->end);
    Free_Timestamp(form->closure);

    free(form);
  }
}

void Free_form(Form form) {
  if (form.ls_form) {
    if (form.ls_form->request == LS) {
      Free_LS_form(form.ls_form);
    } else if (form.lc_form->request == LC) {
      Free_LC_form(form.lc_form);
    } else if (form.dp_form->request == DP) {
      Free_DP_form(form.dp_form);
    } else if (form.dm_form->request == DM) {
      Free_DM_form(form.dm_form);
    }
  }
}
void Free_Token_content(Token_content *token_content) {
  if (token_content) {
    Free_String(token_content->token);
    Free_String(token_content->content);

    free(token_content);
  }
}

void Seal(Timestamp *timestamp) {
  if (timestamp) {
    struct tm *local;
    time_t now;

    /* Pause(Random(1, 5) * 1000); */
    time(&now);
    local = localtime(&now);

    timestamp->year = local->tm_year + 1900;
    timestamp->month = local->tm_mon + 1;
    timestamp->day = local->tm_mday;
    timestamp->hour = local->tm_hour;
    timestamp->minute = local->tm_min;
    timestamp->second = local->tm_sec;
  }
}

void Seal_form(Form form, Timestamp_type type) {
  Timestamp *timestamp = NULL;
  if (form.ls_form->request == LS) {
    if (type == OPENING)
      timestamp = form.ls_form->opening;
    else if (type == START)
      timestamp = form.ls_form->start;
    else if (type == END)
      timestamp = form.ls_form->end;
    else if (type == CLOSURE)
      timestamp = form.ls_form->closure;

  } else if (form.lc_form->request == LC) {
    if (type == OPENING)
      timestamp = form.lc_form->opening;
    else if (type == START)
      timestamp = form.lc_form->start;
    else if (type == END)
      timestamp = form.lc_form->end;
    else if (type == CLOSURE)
      timestamp = form.lc_form->closure;

  } else if (form.dp_form->request == DP) {
    if (type == OPENING)
      timestamp = form.dp_form->opening;
    else if (type == START)
      timestamp = form.dp_form->start;
    else if (type == END)
      timestamp = form.dp_form->end;
    else if (type == CLOSURE)
      timestamp = form.dp_form->closure;

  } else if (form.dm_form->request == DM) {
    if (type == OPENING)
      timestamp = form.dm_form->opening;
    else if (type == START)
      timestamp = form.dm_form->start;
    else if (type == END)
      timestamp = form.dm_form->end;
    else if (type == CLOSURE)
      timestamp = form.dm_form->closure;
  }

  Seal(timestamp);
}

void Sign_form(Form form, char *signature) {
  char **tmp = NULL;
  if (form.ls_form->request == LS) {
    tmp = &form.ls_form->signature;
  } else if (form.lc_form->request == LC) {
    tmp = &form.lc_form->signature;
  } else if (form.dp_form->request == DP) {
    tmp = &form.dp_form->signature;
  } else if (form.dm_form->request == DM) {
    tmp = &form.dm_form->signature;
  }

  Copy_string_to_empty_string(tmp, signature);
}

void Add_Operation_to_DP_form(DP_form *form, Operation *operation) {
  if (!form->operation) {
    form->operation = operation;
    return;
  }

  Operation *aux = form->operation;
  while (aux->following) {
    aux = aux->following;
  }

  aux->following = operation;
}

void Add_Customer_to_DM_form(DM_form *form, Customer *customer) {
  if (!form->customer) {
    form->customer = customer;
    return;
  }

  Customer *aux = form->customer;
  while (aux->following) {
    aux = aux->following;
  }

  aux->following = customer;
}

void Print_Timestamp(FILE *file, char *name, Timestamp *timestamp) {
  if (timestamp && file) {
    char *tmp = Create_empty_String(LENGTH_READ_STRING);
    sprintf(tmp, "%04d%s%02d%s%02d%s%02d%s%02d%s%02d", timestamp->year,
            DELIMITER_DASH, timestamp->month, DELIMITER_DASH, timestamp->day,
            DELIMITER_SPACE, timestamp->hour, DELIMITER_COLON,
            timestamp->minute, DELIMITER_COLON, timestamp->second);
    Print_Line(file, name, tmp);
    free(tmp);
  }
}

void Print_LS_form(FILE *file, LS_form *form) {
  if (form && file) {
    Print_Line(file, TEXT_TYPE, FORM_TYPE_NAMES[form->request]);
    Print_Line(file, TEXT_NAME, form->name);
    Print_Line(file, TEXT_NIF, form->nif);
    Print_Line(file, TEXT_TOPIC, TOPIC_NAMES[form->topic]);
    Print_Line_Number(file, TEXT_AMOUNT, form->amount);
    Print_Timestamp(file, TEXT_OPENING, form->opening);
    Print_Timestamp(file, TEXT_START, form->start);
    Print_Line_Number(file, TEXT_TOTAL, form->total);
    Print_Timestamp(file, TEXT_END, form->end);
    Print_Timestamp(file, TEXT_CLOSURE, form->closure);
    Print_Line(file, TEXT_SIGNATURE, form->signature);
  }
}

void Print_LC_form(FILE *file, LC_form *form) {
  if (form && file) {
    Print_Line(file, TEXT_TYPE, FORM_TYPE_NAMES[form->request]);
    Print_Line(file, TEXT_COMPANY, form->company);
    Print_Line(file, TEXT_CIF, form->cif);
    Print_Line_Number(file, TEXT_AMOUNT_A, form->amount_A);
    Print_Line_Number(file, TEXT_AMOUNT_B, form->amount_B);
    Print_Line_Number(file, TEXT_AMOUNT_C, form->amount_C);
    Print_Timestamp(file, TEXT_OPENING, form->opening);
    Print_Timestamp(file, TEXT_START, form->start);
    Print_Line_Number(file, TEXT_TOTAL, form->total);
    Print_Timestamp(file, TEXT_END, form->end);
    Print_Timestamp(file, TEXT_CLOSURE, form->closure);
    Print_Line(file, TEXT_SIGNATURE, form->signature);
  }
}

void Print_Operation(FILE *file, Operation *operation) {
  if (operation && file) {
    char *tmp = Create_empty_String();
    sprintf(tmp, "%s%s%0.2f", TOP_NAMES[operation->top], DELIMITER_COMMA,
            operation->amount);
    Print_Line(file, TEXT_OPERATION, tmp);
    free(tmp);
  }
}

void Print_Operation_and_following(FILE *file, Operation *operation) {
  if (operation && file) {
    Print_Operation(file, operation);
    Print_Operation_and_following(file, operation->following);
  }
}

void Print_DP_form(FILE *file, DP_form *form) {
  if (form && file) {
    Print_Line(file, TEXT_TYPE, FORM_TYPE_NAMES[form->request]);
    Print_Line(file, TEXT_NAME, form->name);
    Print_Line(file, TEXT_NIF, form->nif);
    Print_Operation_and_following(file, form->operation);
    Print_Timestamp(file, TEXT_OPENING, form->opening);
    Print_Timestamp(file, TEXT_START, form->start);
    Print_Line_Number(file, TEXT_TOTAL, form->total);
    Print_Timestamp(file, TEXT_END, form->end);
    Print_Timestamp(file, TEXT_CLOSURE, form->closure);
    Print_Line(file, TEXT_SIGNATURE, form->signature);
  }
}

void Print_Customer(FILE *file, Customer *customer) {
  if (customer && file) {
    char *tmp = Create_empty_String();
    sprintf(tmp, "%s%s%s%s%0.2f", TYPE_OF_CUSTOMER_NAMES[customer->tcustomer],
            DELIMITER_COMMA, customer->ncustomer, DELIMITER_COMMA,
            customer->amount);
    Print_Line(file, TEXT_CUSTOMER, tmp);
    free(tmp);
  }
}

void Print_Customer_and_following(FILE *file, Customer *customer) {
  if (customer && file) {
    Print_Customer(file, customer);
    Print_Customer_and_following(file, customer->following);
  }
}

void Print_DM_form(FILE *file, DM_form *form) {
  if (form && file) {
    Print_Line(file, TEXT_TYPE, FORM_TYPE_NAMES[form->request]);
    Print_Line(file, TEXT_COMPANY, form->company);
    Print_Line(file, TEXT_CIF, form->cif);
    Print_Customer_and_following(file, form->customer);
    Print_Timestamp(file, TEXT_OPENING, form->opening);
    Print_Timestamp(file, TEXT_START, form->start);
    Print_Line_Number(file, TEXT_TOTAL, form->total);
    Print_Timestamp(file, TEXT_END, form->end);
    Print_Timestamp(file, TEXT_CLOSURE, form->closure);
    Print_Line(file, TEXT_SIGNATURE, form->signature);
  }
}

void Print_form(FILE *file, Form form) {
  if (form.ls_form->request == LS) {
    Print_LS_form(file, form.ls_form);
  } else if (form.lc_form->request == LC) {
    Print_LC_form(file, form.lc_form);
  } else if (form.dp_form->request == DP) {
    Print_DP_form(file, form.dp_form);
  } else if (form.dm_form->request == DM) {
    Print_DM_form(file, form.dm_form);
  }
}

void Print_final_form(Form form) {
  int length_prev = Get_number_tabs();

  TInit(0);
  TPrint("%s\n", TEXT_DASHED_LINE);
  TPrint("%s\n", TEXT_FINISHED_REQUEST);
  TPrint("%s\n", TEXT_FORM_TO_THE_CUSTOMER);
  TPrint("%s\n", TEXT_DASHED_LINE);
  Print_form(stdout, form);
  TPrint("%s\n", TEXT_DASHED_LINE);

  TInit(length_prev);
}

void Print_save_and_free_form(Form form) {
  Print_Jump_Line();
  TPrint("%s\n", TEXT_I_SEND);
  Print_form(stdout, form);
  Save_and_free_form(form);
}

void Seal_print_save_and_free_form(Form form, Timestamp_type timestamp_type) {
  Seal_form(form, timestamp_type);

  Print_save_and_free_form(form);
}

Topic Get_topic_from_string(char *string) {
  Topic choice = DEFAULT;

  if (strcmp(string, TOPIC_NAMES[GENERAL]) == 0) {
    choice = GENERAL;
  } else if (strcmp(string, TOPIC_NAMES[ASSIGNMENT]) == 0) {
    choice = ASSIGNMENT;
  } else if (strcmp(string, TOPIC_NAMES[PERMISSION]) == 0) {
    choice = PERMISSION;
  } else if (strcmp(string, TOPIC_NAMES[REMUNERATION]) == 0) {
    choice = REMUNERATION;
  }

  return (choice);
}

Top Get_top_from_string(char *string) {
  Top choice = DEFAULT;

  if (strcmp(string, TOP_NAMES[OWN]) == 0) {
    choice = OWN;
  } else if (strcmp(string, TOP_NAMES[TRANSPORT]) == 0) {
    choice = TRANSPORT;
  } else if (strcmp(string, TOP_NAMES[ENERGY]) == 0) {
    choice = ENERGY;
  } else if (strcmp(string, TOP_NAMES[FOOD]) == 0) {
    choice = FOOD;
  } else if (strcmp(string, TOP_NAMES[OTHERS]) == 0) {
    choice = OTHERS;
  } else if (strcmp(string, "") == 0) {
    choice = EMPTY;
  }

  return (choice);
}

Type_of_customer Get_type_of_customer_from_string(char *string) {
  Type_of_customer choice = DEFAULT;

  if (strcmp(string, TYPE_OF_CUSTOMER_NAMES[NGO]) == 0) {
    choice = NGO;
  } else if (strcmp(string, TYPE_OF_CUSTOMER_NAMES[FPS]) == 0) {
    choice = FPS;
  } else if (strcmp(string, TYPE_OF_CUSTOMER_NAMES[SME]) == 0) {
    choice = SME;
  } else if (strcmp(string, TYPE_OF_CUSTOMER_NAMES[GOVERNMENT]) == 0) {
    choice = GOVERNMENT;
  } else if (strcmp(string, TYPE_OF_CUSTOMER_NAMES[OTHER]) == 0) {
    choice = OTHER;
  } else if (strcmp(string, "") == 0) {
    choice = EMPTY;
  }

  return (choice);
}

void Get_timestamp_from_string(Timestamp *timestamp, char *string) {
  Token_content *date_time =
      Get_next_token_content_from_string(string, DELIMITER_SPACE);

  Copy_string_to_int(&timestamp->year, Get_next_element_from_string(
                                           date_time->token, DELIMITER_DASH));
  Copy_string_to_int(&timestamp->month,
                     Get_next_element_from_string(NULL, DELIMITER_DASH));
  Copy_string_to_int(&timestamp->day,
                     Get_next_element_from_string(NULL, DELIMITER_DASH));
  Copy_string_to_int(
      &timestamp->hour,
      Get_next_element_from_string(date_time->content, DELIMITER_COLON));
  Copy_string_to_int(&timestamp->minute,
                     Get_next_element_from_string(NULL, DELIMITER_COLON));
  Copy_string_to_int(&timestamp->second,
                     Get_next_element_from_string(NULL, DELIMITER_COLON));

  Free_Token_content(date_time);
}

Operation *Get_operation_from_string(char *string) {
  Operation *operation = Create_empty_Operation();
  Token_content *top_amount =
      Get_next_token_content_from_string(string, DELIMITER_COMMA);

  operation->top = Get_top_from_string(top_amount->token);
  Copy_string_to_float(&operation->amount, top_amount->content);

  Free_Token_content(top_amount);
  return (operation);
}

Customer *Get_customer_from_string(char *string) {
  Customer *customer = Create_empty_Customer();

  customer->tcustomer = Get_type_of_customer_from_string(
      Get_next_element_from_string(string, DELIMITER_COMMA));
  Copy_string_to_empty_string(
      &customer->ncustomer,
      Get_next_element_from_string(NULL, DELIMITER_COMMA));
  Copy_string_to_float(&customer->amount,
                       Get_next_element_from_string(NULL, DELIMITER_COMMA));

  return (customer);
}
