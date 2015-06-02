#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "os.h"

// process behavior
#define INITIAL_PROCESS_COUNT                     5
#define MIN_WORKING_SET_PAGES                     5
#define MIN_EXTERNAL_PAGES                       10
#define WORKING_SET_INCREMENT                     5
#define READ_PROBABILITY                          0.5
#define LOCAL_ACCESS_PROBABILITY                  0.9
#define VOLUNTARY_CONTEXT_SWITCHING_PROBABILITY   0.1
#define INVOLUNTARY_CONTEXT_SWITCHING_TIMER_TICS  16
#define CLEAR_STATISTICS_TIMER_TICS               4

const unsigned int PAGE_ITERATIONS = 10;
const unsigned int RANDOM_MAX_VALUE = 100;

char 
random_boolean(float true_probability)
{
  return rand() % RANDOM_MAX_VALUE >= true_probability * RANDOM_MAX_VALUE;
}

/*
 * Program simulates the work of mmu, that uses NRU algorithm for page faults handling.
 */
int 
main (int argc, char *argv[])
{
  srand (time(NULL)); // init randomizer
  load_RAM ();

  for (int i = 0; i < INITIAL_PROCESS_COUNT; ++i)
    {
      create_process (i, i * WORKING_SET_INCREMENT + MIN_WORKING_SET_PAGES + MIN_EXTERNAL_PAGES);
    }

  // tics before involuntary context switching
  // involuntary context switching on the 1st iteration
  unsigned int tics = INVOLUNTARY_CONTEXT_SWITCHING_TIMER_TICS;
  pid_t pid;
  for (int i = 0; i < 10000; ++i)
    {
      ++tics;
      if (tics >= INVOLUNTARY_CONTEXT_SWITCHING_TIMER_TICS || random_boolean(VOLUNTARY_CONTEXT_SWITCHING_PROBABILITY))
        {
          pid =  rand() % INITIAL_PROCESS_COUNT;
          switch_context(pid);
          tics = 0;
        }
      if (tics >= CLEAR_STATISTICS_TIMER_TICS)
        {
          resetBitR ();
        }

      // random address choice
      size_t num = random_boolean (LOCAL_ACCESS_PROBABILITY) ?
                   rand() % (pid * WORKING_SET_INCREMENT + MIN_WORKING_SET_PAGES) :
                   rand() % (MIN_EXTERNAL_PAGES) + pid * WORKING_SET_INCREMENT + MIN_WORKING_SET_PAGES;
      virtual_address_t addr = num * PAGE_SIZE + rand() % PAGE_SIZE;

      if (random_boolean(READ_PROBABILITY)) 
	{
	   printf("Read from physical address %lu\n", read_virtual_page(addr));
	}
      else
        { 
          printf("Write to physical address %lu\n", modify_virtual_page(addr));
        }
    }
  return 0;
}
