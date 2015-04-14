#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "mmu.h"

// process behavior
#define INITIAL_PROCESS_COUNT        5
#define MIN_WORKING_SET_PAGES        5
#define MIN_EXTERNAL_PAGES           10
#define WORKING_SET_INCREMENT        5
#define READ_PROBABILITY             0.5
#define LOCAL_ACCESS_PROBABILITY     0.9

#define RANDOM_MAX_VALUE 100

bool random_boolean(float true_probability)
{
  return rand() % RANDOM_MAX_VALUE >= true_probability * RANDOM_MAX_VALUE;
}

/*
 * Program simulates the work of mmu, that uses NRU algorithm for page faults handling.
 */
int main (int argc, char *argv[])
{
  srand (time(NULL)); // init randomizer
  for (int i = 0; i < INITIAL_PROCESS_COUNT; ++i)
    {
      create_process (i, i * WORKING_SET_INCREMENT + MIN_WORKING_SET_PAGES + MIN_EXTERNAL_PAGES);
    }

  for (int i = 0; i < 15; ++i) {
      pid_t pid =  rand() % INITIAL_PROCESS_COUNT;
      size_t num;

      // rand page
      if (random_boolean(LOCAL_ACCESS_PROBABILITY))
        {
          num = rand() % (MIN_WORKING_SET_PAGES + pid * WORKING_SET_INCREMENT);
        }
      else
        {
          num = rand() % MIN_EXTERNAL_PAGES + (MIN_WORKING_SET_PAGES + pid * WORKING_SET_INCREMENT);
        }

      // rand operation
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

