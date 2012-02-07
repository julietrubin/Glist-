/* glist.c - Implementation of the general list interface */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "glist.h"

int main(void)
{
    struct gnode *n1;
    struct glist *l1, *l2, *l3, *l4;

    l1 = glist_new_init(INT, 1, DBL, 2.0, INT, 7, INT, 8, DBL, 9.0, SEN);
    glist_println("l1", l1);

    l2 = glist_new_init(STR, "A", 
                        LST, glist_new_init(INT, 1, INT, 2, INT, 3, SEN),
                        SEN);
    glist_println("l2", l2);

    l3 = glist_new_init(STR, "A", 
                        LST, glist_copy(l1),
                        SEN);
    glist_println("l3", l3);

    printf("reverse(l1)\n");
    glist_reverse(l1);
    glist_println("l1", l1);

    l4 = glist_new_init(INT, 10, INT, 2, INT, 7, INT, 8, INT, 1, 
                        INT, 9, INT, 5, INT, 4, INT, 3, INT, 6, SEN);

    glist_println("l4", l4);
    printf("sort(l4)\n");
    glist_sort(l4);
    glist_println("l4", l4);

    return 0;
}
