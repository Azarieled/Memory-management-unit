#include <stdio.h>
#include "mmu.h"

process_t       g_process_table      [MAX_PROCESS_NUMBER]; //TODO smarter data structure with deleting process
unsigned int    g_process_count = 0;
virtual_page_t *g_present_page_table [PHYSICAL_PAGE_COUNT];

process_t *
get_process(pid_t pid)
{
  for (int i = 0; i < g_process_count; ++i)
    {
      if (g_process_table[i].pid == pid)
        {
          return g_process_table + i;
        }
    }
  return NULL;
}


bool
create_process_virtual_table (pid_t pid, size_t virtual_pages)
{
  if (get_process(pid) != NULL)
    {
      return false;
    }

  g_process_table[g_process_count].pages = (virtual_page_t *) malloc(virtual_pages);
  g_process_table[g_process_count].pid = pid;
  ++g_process_count;
  return true;      //TODO swap crash
}


physical_address_t
read_virtual_page (pid_t pid, size_t number)
{
  process_t *process = get_process (pid);       //TODO handle NULL
  virtual_page_t *p = &process->pages [number];

  if (!p->P)
    {
      pageFault (p);
      p->P = true;
    }
  p->R = true;
  printf ("Virtual page %llx read.\n", p->number);
  return p->physical_page;
}


physical_address_t
modify_virtual_page (pid_t pid, size_t number)
{
  process_t *process = get_process (pid);       //TODO handle NULL
  virtual_page_t *p = &process->pages [number];

  if (!p->P)
    {
      pageFault(p);
      p->P = true;
    }
  p->R = true;
  p->M = true;
  printf ("Virtual page %llx modified.\n", p->number);
  return p->physical_page;
}

void
resetBitR()
{
  for (unsigned int i = 0; i < PHYSICAL_PAGE_COUNT; i ++)
    {
      if (g_present_page_table[i] != NULL)
        {
          g_present_page_table[i]->R = 0;
        }
    }
}


physical_address_t
pageFault (virtual_page_t *page)
{
  printf ("Page fault at virtual page: %llx\n", page->number);

  // attempt to find free page
  for (unsigned int i = 0; i < PHYSICAL_PAGE_COUNT; i ++)
    {
      if (g_present_page_table[i] == NULL)
        {
          g_present_page_table[i] = page;
          return page->physical_page = i * PAGE_SIZE;
        }
    }

    return replace_page(); //TODO handle swap crash
}

physical_address_t
replace_page ()
{
  return NRU ();
}

physical_address_t
NRU ()
{
  unsigned int i;

  // class 0
  for (i = 0; i < PHYSICAL_PAGE_COUNT; i ++)
    {
      if (!g_present_page_table[i]->R & !g_present_page_table[i]->M)
        {
          return g_present_page_table[i]->physical_page;
        }
    }

  // class 1
  for (i = 0; i < PHYSICAL_PAGE_COUNT; i ++)
    {
      if (!g_present_page_table[i]->R & g_present_page_table[i]->M)
        {
          return g_present_page_table[i]->physical_page;
        }
    }

  // class 2
  for (i = 0; i < PHYSICAL_PAGE_COUNT; i ++)
    {
      if (g_present_page_table[i]->R & !g_present_page_table[i]->M)
        {
          return g_present_page_table[i]->physical_page;
        }
    }

  // if we reach here, - all pages are class 3
  return g_present_page_table[0]->physical_page;
}
