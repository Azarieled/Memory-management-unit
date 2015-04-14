#ifndef MMU_H
#define MMU_H

#include <stdint.h>
#include "processor.h"

// mmu propeties
#define PAGE_NUMBER_BITS 12
#define MAX_PROCESS_NUMBER 1024 * 1024

void
resetBitR();

page_num_t
pageFault (page_t *page);

/*
 * Function is called during pageFault handling.
 */
page_num_t
demand_page ();

/*
 * Function is called when there are no free memory to satisfy
 */
page_num_t
replace_page ();

/*
 * NRU page replacement algorithm.
 * In worst case 3*n complexity.
 * Need to be optimized.
 */
page_num_t
NRU ();

#endif // MMU_H

