#include <stdio.h>
#include <stdlib.h>
#include "mmu.h"

// operation system properties
#define MAIN_MEMORY_SIZE    512 * 1024 * 1024              // 512 Mb
#define PAGE_SIZE           4096                           //   4 Kb
#define PHYSICAL_PAGE_COUNT (MAIN_MEMORY_SIZE / PAGE_SIZE)
#define SWAP_SIZE 1073741824

// process behavior
#define INITIAL_PROCESS_COUNT 5
#define WORKING_SET_PAGES 40

// probability
#define READ_PROBABILITY            0.5
#define WRITE_PROBABILITY           0.5
#define LOCAL_ACCESS_PROBABILITY    0.9
#define EXTERNAL_ACCESS_PROBABILITY 0.9




int main (void/*int argc, char *argv[]*/)
{
  //printf ("%d", sizeof (size_t));
  int processCount = 0;
  process_t *processes = (process_t *) malloc (INITIAL_PROCESS_COUNT);
  for ( ; processCount < INITIAL_PROCESS_COUNT; ++processCount)
    {
      processes[processCount] = create_process (processCount, WORKING_SET_PAGES);
    }

  return 0;
}

