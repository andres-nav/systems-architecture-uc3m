#include "Admin.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "Heads.h"
#include "Tools.h"

Form form_admin;

float Calculate_total_LS_form(LS_form *form) {
  float tmp = Calcualte_number_rated(form->amount, TOPIC_RATE[form->topic]);
  return (tmp);
}

float Calculate_total_LC_form(LC_form *form) {
  float tmp = 0;
  tmp += Calcualte_number_rated(form->amount_A, ITEM_RATE[ITEM_A]);
  tmp += Calcualte_number_rated(form->amount_B, ITEM_RATE[ITEM_B]);
  tmp += Calcualte_number_rated(form->amount_C, ITEM_RATE[ITEM_C]);

  return (tmp);
}

float Calculate_total_DP_form(DP_form *form) {
  float tmp = 0;
  Operation *operation = form->operation;

  while (operation) {
    tmp += Calcualte_number_rated(operation->amount, TOP_RATE[operation->top]);

    operation = operation->following;
  }

  return (tmp);
}

float Calculate_total_DM_form(DM_form *form) {
  float tmp = 0;
  Customer *customer = form->customer;

  while (customer) {
    tmp += Calcualte_number_rated(customer->amount,
                                  TYPE_OF_CUSTOMER_RATE[customer->tcustomer]);

    customer = customer->following;
  }

  return (tmp);
}

void Calculate_total(Form form) {
  if (form.ls_form->request == LS) {
    form.ls_form->total = Calculate_total_LS_form(form.ls_form);
  } else if (form.lc_form->request == LC) {
    form.lc_form->total = Calculate_total_LC_form(form.lc_form);
  } else if (form.dp_form->request == DP) {
    form.dp_form->total = Calculate_total_DP_form(form.dp_form);
  } else if (form.dm_form->request == DM) {
    form.dm_form->total = Calculate_total_DM_form(form.dm_form);
  }
}

void End_admin() {
  Free_form(form_admin);
  exit(EXIT_SUCCESS);
}

void Handler_admin(int signal) {
  if (signal == SIGINT) {
    End_admin();
  }
}

void Admin() {
  form_admin.ls_form = NULL;
  signal(SIGINT, Handler_admin);

  form_admin = Read_print_pid_and_form(NULL, TRUE);

  Calculate_total(form_admin);
  Pause_random();

  Print_save_and_free_form(form_admin);
}