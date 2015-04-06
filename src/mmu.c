#include <stdio.h>
#include "mmu.h"

// operation system properties
#define MAIN_MEMORY_SIZE    512 * 1024 * 1024              // 512 MB
#define PAGE_SIZE           4096                           //   4 KB
#define PHYSICAL_PAGE_COUNT (MAIN_MEMORY_SIZE / PAGE_SIZE)
#define SWAP_SIZE           1024 * 1024 * 1024             //   1 GB

virtual_page_t g_virtual_page_table [PHYSICAL_PAGE_COUNT];


process_t
create_process (int pid, size_t virtual_pages)
{
  process_t p;
  p.pages = (virtual_page_t *) malloc(virtual_pages);
  p.pid = pid;
  return p;
}


physical_page_t
read_virtual_page (virtual_page_t *page)
{
  if (!page->P)
    {
      page->physical_page = pageFault(page);
      page->P = true;
    }
  page->R = true;
  printf ("Virtual page %x read.", page->address);
  return page->physical_page;
}


physical_page_t
modify_virtual_page (virtual_page_t *page)
{
  if (!page->P)
    {
      page->physical_page = pageFault(page);
      page->P = true;
    }
  page->R = true;
  page->M = true;
  printf ("Virtual page %x modified.", page->address);
  return page->physical_page;
}


physical_page_t
pageFault (virtual_page_t *page)
{
  printf ("Page fault at virtual page: %x\n", page->address);
  return demandPage();
}


physical_page_t
demandPage ()
{
    for (unsigned int i; i < PHYSICAL_PAGE_COUNT; i ++)
    {
        if (~g_virtual_page_table[i]->R & ~g_virtual_page_table[i]->M)
    }
}

physical_page_t
replace_page_NRU ()
{
    for (int )
}
