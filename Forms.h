#ifndef FORMS_H
#define FORMS_H

#include <stdio.h>

#include "Defines.h"

typedef struct {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
} Timestamp;

typedef enum { LS, LC, DP, DM } Form_type;

static char *const FORM_TYPE_NAMES[] = {
    [LS] = TEXT_LS,
    [LC] = TEXT_LC,
    [DP] = TEXT_DP,
    [DM] = TEXT_DM,
};

typedef enum {
  GENERAL,
  ASSIGNMENT,
  PERMISSION,
  REMUNERATION,
  DEFAULT = NUMBER_DEFAULT
} Topic;

static char *const TOPIC_NAMES[] = {[GENERAL] = TEXT_GENERAL,
                                    [ASSIGNMENT] = TEXT_ASSIGNMENT,
                                    [PERMISSION] = TEXT_PERMISSION,
                                    [REMUNERATION] = TEXT_REMUNERATION,
                                    [DEFAULT] = QUESTION};

static const float TOPIC_RATE[] = {
    [GENERAL] = NUMBER_TOPIC_RATE_GENERAL,
    [ASSIGNMENT] = NUMBER_TOPIC_RATE_ASSIGNMENT,
    [PERMISSION] = NUMBER_TOPIC_RATE_PERMISSION,
    [REMUNERATION] = NUMBER_TOPIC_RATE_REMUNERATION};

typedef struct {
  Form_type request;
  char *name;
  char *nif;
  Topic topic;
  float amount;
  Timestamp *opening;
  Timestamp *start;
  float total;
  Timestamp *end;
  Timestamp *closure;
  char *signature;
} LS_form;

typedef enum { ITEM_A, ITEM_B, ITEM_C } Item;

static const float ITEM_RATE[] = {[ITEM_A] = NUMBER_ITEM_RATE_ITEM_A,
                                  [ITEM_B] = NUMBER_ITEM_RATE_ITEM_B,
                                  [ITEM_C] = NUMBER_ITEM_RATE_ITEM_C};

typedef struct {
  Form_type request;
  char *company;
  char *cif;
  float amount_A;
  float amount_B;
  float amount_C;
  Timestamp *opening;
  Timestamp *start;
  float total;
  Timestamp *end;
  Timestamp *closure;
  char *signature;
} LC_form;

typedef enum { OWN, TRANSPORT, ENERGY, FOOD, OTHERS, EMPTY = NUMBER_EMPTY } Top;

static char *const TOP_NAMES[] = {
    [OWN] = TEXT_OWN,   [TRANSPORT] = TEXT_TRANSPORT, [ENERGY] = TEXT_ENERGY,
    [FOOD] = TEXT_FOOD, [OTHERS] = TEXT_OTHERS,       [DEFAULT] = QUESTION};

static const float TOP_RATE[] = {
    [OWN] = NUMBER_TOP_RATE_OWN,       [TRANSPORT] = NUMBER_TOP_RATE_TRANSPORT,
    [ENERGY] = NUMBER_TOP_RATE_ENERGY, [FOOD] = NUMBER_TOP_RATE_FOOD,
    [OTHERS] = NUMBER_TOP_RATE_OTHERS, [DEFAULT] = NUMBER_TOP_RATE_DEFAULT};

typedef struct Operation Operation;
struct Operation {
  Top top;
  float amount;
  Operation *following;
};

typedef struct {
  Form_type request;
  char *name;
  char *nif;
  Operation *operation;
  Timestamp *opening;
  Timestamp *start;
  float total;
  Timestamp *end;
  Timestamp *closure;
  char *signature;
} DP_form;

typedef enum { NGO, FPS, SME, GOVERNMENT, OTHER } Type_of_customer;

static char *const TYPE_OF_CUSTOMER_NAMES[] = {
    [NGO] = TEXT_NGO,     [FPS] = TEXT_FPS,
    [SME] = TEXT_SME,     [GOVERNMENT] = TEXT_GOVERNMENT,
    [OTHER] = TEXT_OTHER, [DEFAULT] = QUESTION};

static const float TYPE_OF_CUSTOMER_RATE[] = {
    [NGO] = NUMBER_TYPE_OF_CUSTOMER_RATE_NGO,
    [FPS] = NUMBER_TYPE_OF_CUSTOMER_RATE_FPS,
    [SME] = NUMBER_TYPE_OF_CUSTOMER_RATE_SME,
    [GOVERNMENT] = NUMBER_TYPE_OF_CUSTOMER_RATE_GOVERNMENT,
    [OTHER] = NUMBER_TYPE_OF_CUSTOMER_RATE_OTHER,
    [DEFAULT] = NUMBER_TYPE_OF_CUSTOMER_RATE_DEFAULT};

typedef struct Customer Customer;
struct Customer {
  char *ncustomer;
  Type_of_customer tcustomer;
  float amount;
  Customer *following;
};

typedef struct {
  Form_type request;
  char *company;
  char *cif;
  Customer *customer;
  Timestamp *opening;
  Timestamp *start;
  float total;
  Timestamp *end;
  Timestamp *closure;
  char *signature;
} DM_form;

typedef union {
  LS_form *ls_form;
  LC_form *lc_form;
  DP_form *dp_form;
  DM_form *dm_form;
} Form;

typedef struct {
  char *token;
  char *content;
} Token_content;

typedef enum { OPENING, START, END, CLOSURE } Timestamp_type;

Timestamp *Create_empty_Timestamp();
LS_form *Create_empty_LS_form();
LC_form *Create_empty_LC_form();
Operation *Create_empty_Operation();
Customer *Create_empty_Customer();
DP_form *Create_empty_DP_form();
DM_form *Create_empty_DM_form();
Form Create_empty_form(Form_type form_type);
Token_content *Create_empty_Token_content();

void Free_Timestamp(Timestamp *timestamp);
void Free_LS_form(LS_form *form);
void Free_LC_form(LC_form *form);
void Free_Operation_and_following(Operation *operation);
void Free_Customer_and_following(Customer *customer);
void Free_DP_form(DP_form *form);
void Free_DM_form(DM_form *form);
void Free_form(Form form);
void Free_Token_content(Token_content *token_content);

void Seal(Timestamp *timestamp);
void Seal_form(Form form, Timestamp_type type);
void Sign_form(Form form, char *signature);

void Add_Operation_to_DP_form(DP_form *form, Operation *operation);
void Add_Customer_to_DM_form(DM_form *form, Customer *customer);

void Print_Timestamp(FILE *file, char *name, Timestamp *timestamp);
void Print_LS_form(FILE *file, LS_form *form);
void Print_LC_form(FILE *file, LC_form *form);
void Print_Operation(FILE *file, Operation *operation);
void Print_Operation_and_following(FILE *file, Operation *operation);
void Print_DP_form(FILE *file, DP_form *form);
void Print_Customer(FILE *file, Customer *customer);
void Print_Customer_and_following(FILE *file, Customer *customer);
void Print_DM_form(FILE *file, DM_form *form);
void Print_form(FILE *file, Form form);
void Print_final_form(Form form);

void Print_save_and_free_form(Form form);
void Seal_print_save_and_free_form(Form form, Timestamp_type timestamp_type);

Topic Get_topic_from_string(char *string);
Top Get_top_from_string(char *string);
Type_of_customer Get_type_of_customer_from_string(char *string);
void Get_timestamp_from_string(Timestamp *timestamp, char *string);
Operation *Get_operation_from_string(char *string);
Customer *Get_customer_from_string(char *string);

#endif
