#include <stdio.h>
#include "mmu.h"

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
      pageFault(page);
      page->P = true;
    }
  page->R = true;
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
  return page->physical_page;
}

physical_page_t
pageFault (virtual_page_t *page)
{
  printf ("Page fault at: %x\n", page->address);
}

void
run_mmu (process_t *processes, int processCount)
{
}
