#include "malloc.h"

void add_block_to_list(t_mem_chunk **dst, t_mem_chunk *src)
{
    if (!*dst || (unsigned long)(*dst) > (unsigned long)src)
    {
        if (*dst)
            (*dst)->prev = src;
        src->next = *dst;
        *dst = src;
    }
    else
    {
        t_mem_chunk *curr = *dst;
        
        while (curr->next && (unsigned long)curr->next < (unsigned long)src) {
            curr = curr->next;   
        }
        if (curr->next)
            curr->next->prev = src;
        src->next = curr->next;
        curr->next = src;
        src->prev = curr;
    }
}

void remove_block_from_list(t_mem_chunk **rb)
{
    if ((*rb)->next)
        (*rb)->next->prev = (*rb)->prev;
    if ((*rb)->prev)
        (*rb)->prev->next = (*rb)->next;
    (*rb)->next = NULL;
    (*rb)->prev = NULL;
    if (!(*rb)->next && !(*rb)->prev)
        *rb = NULL;
}