#include "ls.h"
#include <stdbool.h>
#include <stdio.h>
#include "globals.h"
#include "enums.h"
#include "structures.h"

#define NULL (void *)0

int decode_switches(int argc, char **argv)
{
  char *time_style_option = NULL;

  /* These variables are false or -1 unless a switch says otherwise.  */
  bool kibibytes_specified = false;
  int format_opt = -1;
  int hide_control_chars_opt = -1;
  int quoting_style_opt = -1;
  int sort_opt = -1;
  long tabsize_opt = -1;
  long width_opt = -1;
}
