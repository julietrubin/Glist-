/* glist_test.c - a simple glist test program */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "glist.h"

/* Output:

$ ./glist_test
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
[0.00, 2.00, 4.00, 6.00, 8.00, 10.00, 12.00, 14.00, 16.00, 18.00]
["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
[[0, 1, 2, 3, 4, 5, 6, 7, 8, 9], [0.00, 2.00, 4.00, 6.00, 8.00, 10.00, 12.00, 14.00, 16.00, 18.00], ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]]

*/

int main(void)
{
    struct gnode *n1;
    struct glist *l1, *l2, *l3, *l4;
    int i;

    /* contruct a list of ints */
    
    l1 = glist_new();

    for (i = 0; i < 10; i++) {
        n1 = gnode_new();
        gnode_set_int(n1, i);
        glist_add(l1, n1);
    }
    
    glist_print(l1);
    printf("\n");

    /* construct a list of doubles */

    l2 = glist_new();
    
    for (i = 0; i < 10; i++) {
        n1 = gnode_new();
        gnode_set_double(n1, (double) i * 2);
        glist_add(l2, n1);
    }
    
    glist_print(l2);
    printf("\n");

    /* construct a list of strings */

    l3 = glist_new();
    
    for (i = 0; i < 10; i++) {
        char *numstr[] = {"zero", "one", "two", "three", "four", "five", "six", "seven",
            "eight", "nine"};
        n1 = gnode_new();
        gnode_set_str(n1, numstr[i]);
        glist_add(l3, n1);
    }
    
    glist_print(l3);
    printf("\n");

    /* construct a list of lists */

    l4 = glist_new();
    
    for (i = 0; i < 3; i++) {
        struct glist *lists[] = {l1, l2, l3};
        n1 = gnode_new();
        gnode_set_list(n1, lists[i]);
        glist_add(l4, n1);
    }

    glist_print(l4);
    printf("\n");

    return 0;
}
