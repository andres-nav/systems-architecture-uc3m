#include "Chief.h"

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include "Admin.h"
#include "Forms.h"
#include "Heads.h"
#include "Tools.h"

Form form_chief;

void End_chief() {
  Free_form(form_chief);
  exit(EXIT_SUCCESS);
}

void Handler_chief(int signal) {
  if (signal == SIGINT) {
    End_chief();
  }
}

void Chief() {
  form_chief.ls_form = NULL;
  signal(SIGINT, Handler_chief);
  
  form_chief = Read_print_pid_and_form(TEXT_TITLE_CHIEF, TRUE);

  Pause_random();
  Seal_print_save_and_free_form(form_chief, START);
  form_chief.ls_form = NULL;

  Create_process_and_wait(Admin, NUMBER_TABS_ADMIN);

  form_chief = Read_print_pid_and_form(NULL, FALSE);

  Sign_form(form_chief, SIGNATURE_CHIEF);  
  Pause_random();

  Seal_print_save_and_free_form(form_chief, END);
  form_chief.ls_form = NULL;
}