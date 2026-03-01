#ifndef BOXOFFICER_H
#define BOXOFFICER_H

#include "Forms.h"

char *Ask_User(char *message);
char *Ask_User_String(char *message);
float Ask_User_Float(char *message);
Topic Ask_User_Topic(char *message);
Top Ask_User_Top(char *message);
Type_of_customer Ask_User_Type_of_customer(char *message);

void Ask_LS_form();
void Ask_LC_form();
void Ask_Clients(DM_form *form);
void Ask_Operations(DP_form *form);
void Ask_DP_form();
void Ask_DM_form();
void Ask_form(Form_type form_type);

void Ask_request();

void End_boxofficer();
void Handler_boxofficer(int signal);
void Boxofficer();

#endif