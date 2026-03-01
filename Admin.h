#ifndef ADMIN_H
#define ADMIN_H

#include "Forms.h"

float Calculate_total_LS_form(LS_form *form);
float Calculate_total_LC_form(LC_form *form);
float Calculate_total_DP_form(DP_form *form);
float Calculate_total_DM_form(DM_form *form);

void Calculate_total(Form form);

void Set_tabs_print_admin();

void End_admin();
void Handler_admin(int signal);
void Admin();

#endif