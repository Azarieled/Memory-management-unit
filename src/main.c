#include <stdio.h>
#include <stdlib.h>
#include "mmu.h"

// process behavior
#define INITIAL_PROCESS_COUNT        5
#define WORKING_SET_PAGES_1          5
#define EXTERNAL_PAGES_1            10
#define WORKING_SET_INCREMENT        5
#define READ_PROBABILITY             0.5
#define WRITE_PROBABILITY            0.5
#define LOCAL_ACCESS_PROBABILITY     0.9
#define EXTERNAL_ACCESS_PROBABILITY  0.9

int main (void/*int argc, char *argv[]*/)
{
  for (int i = 0; i < INITIAL_PROCESS_COUNT; ++i)
    {
      create_process_virtual_table (i, i * WORKING_SET_INCREMENT + WORKING_SET_PAGES_1 + EXTERNAL_PAGES_1);
    }
  for (int i = 0; i < INT_MAX; ++i) {
      pid_t pid =  i % INITIAL_PROCESS_COUNT;
      size_t num = i;                          //TODO randomize
      read_virtual_page(pid, num);
    }
  return 0;
}

