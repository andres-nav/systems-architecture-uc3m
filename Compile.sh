#!/bin/sh

if gcc -Wall -g -o P1 P1.c Forms.c Tools.c Heads.c Boxofficer.c Chief.c Admin.c; then
   if [ "$1" == "valgrind" ]; then
      valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./P1
   elif [ "$1" == "valgrind-less" ]; then
      valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./P1 | less 2>&1
   elif [ "$1" == "valgrind-log" ]; then
      valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./P1 >P1.log 2>&1
   elif [ "$1" != "debug" ]; then
      ./P1
   fi
fi
