#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "mmu.h"

#define RANDOM_MAX_VALUE 100

// process behavior
#define INITIAL_PROCESS_COUNT        5
#define WORKING_SET_PAGES_1          5
#define EXTERNAL_PAGES_1            10
#define WORKING_SET_INCREMENT        5
#define READ_PROBABILITY             0.5
#define LOCAL_ACCESS_PROBABILITY     0.9

bool random_boolean(float true_probability)
{
  return rand() % RANDOM_MAX_VALUE >= true_probability * RANDOM_MAX_VALUE;
}

int main (void/*int argc, char *argv[]*/)
{
  srand (time(NULL)); // init randomizator
  for (int i = 0; i < INITIAL_PROCESS_COUNT; ++i)
    {
      create_process_virtual_table (i, i * WORKING_SET_INCREMENT + WORKING_SET_PAGES_1 + EXTERNAL_PAGES_1);
    }
  for (int i = 0; i < INT_MAX; ++i) {
      pid_t pid =  i % INITIAL_PROCESS_COUNT;
      size_t num = i;                          //TODO randomize
      if (random_boolean(READ_PROBABILITY))
        {
          read_virtual_page(pid, num);
        }
      else
        {
          modify_virtual_page(pid, num);
        }
    }
  return 0;
}

