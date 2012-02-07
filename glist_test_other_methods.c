/* glist_test.c - a simple glist test program */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "glist.h"

int main(void) {
	struct gnode *n1;
    struct glist *l1;
    int i;

    /* contruct a list of ints */
    
    l1 = glist_new();

    for (i = 0; i < 10; i++) {
        n1 = gnode_new();
        gnode_set_int(n1, i);
        glist_add(l1, n1);
    }
    
     printf("test: glist_print using l1\n");
    glist_print(l1);

    
    printf("\ntest: transversing list using next relation\n");
    struct gnode *temp;
	for (temp = glist_front(l1); gnode_get_type(temp) != SEN; temp = next(temp)) {
		gnode_print(temp);
	}
	
	printf("\ntest: transversing list using prev relation\n");
	for (temp = glist_back(l1); gnode_get_type(temp) != SEN; temp = prev(temp)) {
		gnode_print(temp);
	}
	
	printf("\ntest: glist_reverse using l1\n");
  
    glist_print(glist_reverse(l1));
    
	printf("\ntest: glist_copy using l1\n");
	glist_print(glist_copy(l1));
	
	printf("\ntest: glist_head using l1\n");
	gnode_print(glist_head(l1));

	printf("\ntest: glist_tail using l1\n");
	gnode_print(glist_tail(l1));
	
	
	printf("\ntest: glist_front using l1\n");
	gnode_print(glist_front(l1));
	
	printf("\ntest: glist_back using l1\n");
	gnode_print(glist_back(l1));

	printf("\ntest: glist_insert using l1\n");
	n1 = gnode_new();
    gnode_set_int(n1, 100);
	glist_insert(l1, n1, 2);
	glist_print(l1);
	
	printf("\ntest: glist_find using altered l1\n");
	printf("%d", glist_find(l1, n1));
	
	printf("\ntest: glist_remove using altered l1\n");
	glist_remove(n1);
	glist_print(l1);
	
	printf("\ntest: glist_length\n");
	printf("%d", glist_length(l1));
	
	printf("\ntest: glist_sort\n");
	glist_print(glist_sort(l1));
	
	gnode_print(glist_max(l1, INT));
	
	gnode_print(glist_min(l1, INT));
	
}
