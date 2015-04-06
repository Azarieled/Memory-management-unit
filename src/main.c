#include <stdio.h>
#include <stdlib.h>
#include "mmu.h"

// process behavior
#define INITIAL_PROCESS_COUNT 5
#define WORKING_SET_PAGES 40

// probability
#define READ_PROBABILITY            0.5
#define WRITE_PROBABILITY           0.5
#define LOCAL_ACCESS_PROBABILITY    0.9
#define EXTERNAL_ACCESS_PROBABILITY 0.9

void
run_mmu (process_t *processes, int processCount)
{

}

int main (void/*int argc, char *argv[]*/)
{
  int processCount = 0;
  process_t *processes = (process_t *) malloc (INITIAL_PROCESS_COUNT);
  for ( ; processCount < INITIAL_PROCESS_COUNT; ++processCount)
    {
      processes[processCount] = create_process (processCount, WORKING_SET_PAGES);
    }

  return 0;
}

