#include "processor.h"
#include "mmu.h"

process_t g_process_table [MAX_PID]; //TODO smarter data structure with deleting process
page_t *g_page_table = NULL;
unsigned int g_page_table_size = 0;

int
create_process (pid_t pid, size_t virtual_pages)
{
  if (pid > MAX_PID)
    {
      return 1;
    }

  process_t *process = g_process_table + pid;
  if (process->created)
    {
      return -1;
    }

  process->pages = (page_t *) calloc (sizeof (page_t), virtual_pages);
  process->created = true;
  return 0;
}

int
switch_context (pid_t pid)
{
  if (pid > MAX_PID)
    {
      return 1;
    }

  process_t process = g_process_table[pid];
  if (!process.created)
    {
      return -1;
    }

  g_page_table = process.pages;
  return 0;
}

inline page_t *
get_page_table ()
{
  return g_page_table;
}

unsigned int get_page_table_size()
{

}

physical_address_t
read_virtual_page (virtual_address_t addr)
{
  page_t *p = &g_page_table [addr >> PAGE_NUMBER_BITS];

  if (!p->P)
    {
      printf ("Process %ld: page fault at virtual page: %lx\n", pid, addr);
      pageFault (p);
      p->P = true;
    }
  p->R = true;
  printf ("Process %ld: virtual page %lx read.\n", pid, addr);
  return p->physical_page;
}


physical_address_t
modify_virtual_page (virtual_address_t addr)
{
  page_t *p = &g_page_table [addr >> PAGE_NUMBER_BITS];

  if (!p->P)
    {
      printf ("Process %ld: page fault at virtual page: %lx\n", pid, addr);
      pageFault(p);
      p->P = true;
    }
  p->R = true;
  p->M = true;
  printf ("Process %ld: virtual page %lx modified.\n", pid, addr);
  return p->physical_page;
}
