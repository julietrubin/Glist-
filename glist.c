#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glist.h"
#include <assert.h>
#include <stdarg.h>



/*returns allocated memory for a gnode*/
struct gnode *gnode_new(void) {
	struct gnode *new_gnode;
	new_gnode = (struct gnode *) malloc(sizeof(struct gnode));
	assert(new_gnode != NULL);
	
	return new_gnode;
}

/*returns allocated memory for a glist with glist_head and glist_tail initialized*/
struct glist *glist_new(void) {
	struct glist *new_glist;
	new_glist = (struct glist *) malloc(sizeof(struct glist));
	assert(new_glist != NULL);
	
	glist_head(new_glist)->type = SEN;
	glist_tail(new_glist)->type = SEN;
	
	glist_head(new_glist)->next = glist_tail(new_glist);
	glist_tail(new_glist)->prev = glist_head(new_glist);
	glist_head(new_glist)->prev = NULL;
	glist_tail(new_glist)->next = NULL;

	return new_glist;
}

/*create a new list using varargs to contruct the elements of the list*/
struct glist *glist_new_init(enum gtypes arg1, ...) {
    va_list ap;
    enum gtypes t;
    struct glist *l;
    struct gnode *n;

    l = glist_new();

    va_start(ap, arg1);
    t = arg1; 
    while (t != SEN) {
        n = gnode_new();
        switch (t) {
            case INT:
                gnode_set_int(n, va_arg(ap, int));
                break;
            case DBL:
                gnode_set_double(n, va_arg(ap, double));
                break;
            case STR:
                gnode_set_str(n, va_arg(ap, char *));
                break;
            case LST:
                gnode_set_list(n, va_arg(ap, struct glist *));
                break;
        }
        glist_add(l, n);
        t = va_arg(ap, enum gtypes);       
    }
    va_end(ap);
    
    return l;
}


/*recursive free gnode and free glist fuctions*/
void gnode_free(struct gnode *n){
	assert(n != NULL);
	switch (gnode_get_type(n)) {
		case STR:
			free(gnode_get_str(n));
			break;
		case LST: 
			glist_free(gnode_get_list(n));
			break;
	}
	free(n);
}

void glist_free(struct glist *l) {
	assert(l != NULL);
	struct gnode *walker;
	struct gnode *temp;
	
	walker = glist_front(l);
	while(is_not_SEN(walker)) {
		temp = next(walker);
		glist_remove(walker);
		gnode_free(walker);
		walker = temp;
	}
	free(l);
}


/*recursive gnode print and glist print fuctions
glist_println is a formated glist_print function*/
void gnode_print(struct gnode *n) {
	assert(n != NULL);

	switch(gnode_get_type(n)) {
		case STR:
			printf("\"%s\"", gnode_get_str(n));
			break;
		case INT:
			printf("%d", gnode_get_int(n));
			break;
		case DBL:
			printf("%f", gnode_get_double(n));
			break;
		case LST:
			glist_print(gnode_get_list(n));
			break;
		case SEN:
			printf("error: trying to print SEN gnode");
			break;
	}
}

void glist_print(struct glist *l) {
	assert(l != NULL);
	struct gnode *walker;
	printf("[");
	
	for (walker = glist_front(l); walker != glist_back(l); walker = next(walker)) {
		gnode_print(walker);
		printf(", ");
	}
	gnode_print(walker);
	printf("]");
} 

void glist_println(char *name, struct glist *l) {
    printf("%s = ", name);
    glist_print(l);
    printf("\n");
}


/*recursive gnode copy and glist copy functions*/
struct gnode *gnode_copy(struct gnode *n) {
	assert(n != NULL);
	struct gnode *copy_gnode;
	copy_gnode = gnode_new();

	switch(gnode_get_type(n)) {
		case INT:
			gnode_set_int(copy_gnode, gnode_get_int(n));
			break;
		case DBL:
			gnode_set_double(copy_gnode, gnode_get_double(n));
			break;
		case STR:
			gnode_set_str(copy_gnode, gnode_get_str(n));
			break;
		case LST: 
			gnode_set_list(copy_gnode, glist_copy(gnode_get_list(n)));
			break;
	}
	return copy_gnode;
}

struct glist *glist_copy(struct glist *l) {
	assert(l != NULL);
	
	struct glist *copy_glist;
	copy_glist = glist_new();
	
	struct gnode *walker;
	
	for (walker = glist_front(l); is_not_SEN(walker); walker = next(walker))
		glist_add(copy_glist, gnode_copy(walker));

	return copy_glist;
}


/*glist_isequal checks if two glist are equal
by checking that all corresponding gnodes
 are equal*/
bool gnode_isequal(struct gnode *n1, struct gnode *n2) {
	assert (n1 != NULL);
	assert (n2 != NULL);
	
	if (gnode_get_type(n1) != gnode_get_type(n2))
		return false;
		
	switch (gnode_get_type(n1)) {
		case INT:
			return (gnode_get_int(n1) == gnode_get_int(n2));
			break;
		case DBL:
			return (gnode_get_double(n1) == gnode_get_double(n2));
			break;
		case STR:
			return ((strcmp(gnode_get_str(n1), gnode_get_str(n2)))
					 == 0 );
			break;
		case LST:
			return (glist_isequal(gnode_get_list(n1), gnode_get_list(n2)));
		}
}

bool glist_isequal(struct glist *l1, struct glist *l2) {
	assert (l1 != NULL);
	assert (l2 != NULL);
	
	if (glist_length(l1) != glist_length(l2))
		return false;
	
	struct gnode *walker;
	struct gnode *walker2;
	for (walker = glist_front(l1), walker2 = glist_front(l2);
		is_not_SEN(walker); walker = next(walker), walker2 = next(walker2)) {
			if (!gnode_isequal(walker, walker2))
				return false;
	}
	return true;
}


/* other gnode functions */
struct gnode *next(struct gnode *n) {
	assert (n != NULL);
	return n->next;
}

struct gnode *prev(struct gnode *n) {
	assert (n != NULL);
	return n->prev;
}

bool is_not_SEN(struct gnode *n) {
	assert (n != NULL);
	return (gnode_get_type(n) != SEN);
}

/* initializes str val and type in gnode */
void gnode_set_str(struct gnode *n, char *s) {
	assert(n != NULL);
	assert(s != NULL);
	char *str;
	str = (char *) malloc((strlen(s) + 1));
	assert(str != NULL);
	strcpy(str, s);
	n->val.s = str;
	n->type = STR;
}

/* initializes int val and type in gnode */
void gnode_set_int(struct gnode *n, int d) {
	assert(n != NULL);
	n->val.d = d;
	n->type = INT;
}

/* initializes double val and type in gnode */
void gnode_set_double(struct gnode *n, double f) {
	assert(n != NULL);
	n->val.f = f;
	n->type = DBL;
}

/* initializes list val and type in gnode */
void gnode_set_list(struct gnode *n, struct glist *l) {
	assert(n != NULL);
	assert(l != NULL);
	n->val.l = l;
	n->type = LST;
}

/* returns type of gnode */
enum gtypes gnode_get_type(struct gnode *n) {
	assert(n != NULL);
	return n->type;
}

/* returns value of an str gnode */
char *gnode_get_str(struct gnode *n) {
	assert(n != NULL);
	assert(gnode_get_type(n) == STR);
	return n->val.s;
}

/* returns value of a int gnode */
int gnode_get_int(struct gnode *n) {
	assert(n != NULL);
	assert(gnode_get_type(n) == INT);
	return n->val.d;
}

/* returns value of a double gnode */
double gnode_get_double(struct gnode *n) {
	assert(n != NULL);
	assert(gnode_get_type(n) == DBL);
	return n->val.f;
}

/* returns value of a list gnode */
struct glist *gnode_get_list(struct gnode *n) {
	assert(n != NULL);
	assert(gnode_get_type(n) == LST);
	return n->val.l;
}




/*other glist functions*/
/* returns glist_head gnode */
struct gnode *glist_head(struct glist *l) {
	assert(l != NULL);
	return &l->head;
}

/* returns glist_tail gnode */
struct gnode *glist_tail(struct glist *l) {
	assert(l != NULL);
	return &l->tail;
}

/* returns glist_front gnode */
struct gnode *glist_front(struct glist *l){
	assert(l != NULL);
	return next(glist_head(l));
}

/* returns glist_back gnode */
struct gnode *glist_back(struct glist *l) {
	assert(l != NULL);
	return prev(glist_tail(l));
}

/*inserts gnode at index in glist */
void glist_insert(struct glist *l, struct gnode *n, int index) {
	assert(l != NULL);
	assert(n != NULL);
	assert(index >= 0);
	assert(index <= glist_length(l));
	
	struct gnode *walker;
	int count = 0;
	for (walker = glist_front(l); is_not_SEN(walker); walker = next(walker)) {
		if (count == index) {
			n->next = walker;
			n->prev = prev(walker);
			prev(walker)->next = n;
			walker->prev = n;
		}
		count++;
	}
}

/* adds gnode to last element of glist */
void glist_add(struct glist *l, struct gnode *n) {
	assert(l != NULL);
	assert(n != NULL);
	
	n->prev = glist_back(l);
	n->next = glist_tail(l);
	glist_back(l)->next = n;
	glist_tail(l)->prev = n;
}

/* removes gnode from the list it belongs to */
struct gnode *glist_remove(struct gnode *n) {
	assert(n != NULL);
	assert(next(n) != NULL);
	assert(prev(n) != NULL);
	
	prev(n)->next = next(n);
	next(n)->prev = prev(n);
	n->next = NULL;
	n->prev = NULL;
}

/* returns gnode at index in glist */
struct gnode *glist_getindex(struct glist *l, int i) {
	assert(l != NULL);
	assert(i >= 0 );
	assert(i < glist_length(l));
	
	struct gnode *walker;
	int count = 0;
	for (walker = glist_front(l); is_not_SEN(walker); walker = next(walker)) {
		if (count == i)
			return walker;
		count++;
	}
}

/* return index of gnode or -1 if not found */
int glist_find(struct glist *l, struct gnode *n) {
	assert(l != NULL);
	assert(n != NULL);
	int count = 0;
	struct gnode *walker;
	
		for (walker = glist_front(l); is_not_SEN(walker); walker = next(walker)) {
			if (gnode_isequal(n, walker) )
				return count;
			count++;
		}
	return -1;
}

/* return length of glist */
int glist_length(struct glist *l) {
	assert(l != NULL);
	int count = 0;
	struct gnode *walker;
	for (walker = glist_front(l); is_not_SEN(walker); walker = next(walker)) {
		count++;
	}
	return count;
}

struct glist *glist_reverse(struct glist *l) {
	assert(l != NULL);
	struct glist *reverse_glist;
	struct gnode *walker;
	reverse_glist = glist_new();

	for (walker = glist_back(l); is_not_SEN(walker); walker = prev(walker))
		glist_add(reverse_glist, gnode_copy(walker));
	
	glist_free(l);
	l = glist_copy(reverse_glist);
	glist_free(reverse_glist);
	return l;		
}

struct glist *glist_sort(struct glist *l) {
	assert(l != NULL);
	struct glist *sorted_glist;
	struct gnode *min;	
	enum gtypes type;
	int length;
	int i;
	
	length = glist_length(l);
	sorted_glist = glist_new();
	type = gnode_get_type(glist_front(l));
	assert(type != LST);
	assert(type != SEN);


	for (i = 0; i < length; i++) {
		min = glist_min(l, type);
		glist_add(sorted_glist, glist_remove(min));
	}
	
	glist_free(l);
	l = glist_copy(sorted_glist);
	glist_free(sorted_glist);
	return l;
}

struct gnode *glist_max(struct glist *l, enum gtypes type) {
	assert(l != NULL);
	assert(type != SEN);
	assert(type != LST);
	
	struct gnode *max;
	struct gnode *walker;
	max = glist_front(l);

	for (walker = next(glist_front(l)); is_not_SEN(walker); walker = next(walker)) {
		switch (type) {
			case INT: 
				if (gnode_get_int(walker) > gnode_get_int(max))
					max = walker;
				break;
			case DBL:
				if (gnode_get_double(walker) > gnode_get_double(max))
					max = walker;
				break;
			case STR:
				if (strcmp(gnode_get_str(walker), gnode_get_str(max)) > 0) 
					max = walker;
				break;
		}
	}
	return max;	
}

struct gnode *glist_min(struct glist *l, enum gtypes type) {
	assert(l != NULL);
	assert(type != SEN);
	assert(type != LST);
	
	struct gnode *min;
	struct gnode *walker;
	min = glist_front(l);

	for (walker = next(glist_front(l)); is_not_SEN(walker); walker = next(walker)) {
		switch (type) {
			case INT: 
				if (gnode_get_int(walker) < gnode_get_int(min))
					min = walker;
				break;
			case DBL:
				if (gnode_get_double(walker) < gnode_get_double(min))
					min = walker;
				break;
			case STR:
				if (strcmp(gnode_get_str(walker), gnode_get_str(min)) < 0) 
					min = walker;
				break;
		}
	}
	return min;	
}

struct glist *glist_concat(struct glist *l1, struct glist *l2) {
	assert(l1 != NULL);
	assert(l2 != NULL);
	
	struct gnode *walker;
	for (walker = glist_front(l2); is_not_SEN(walker); walker = next(walker)) {
		glist_add(l1, gnode_copy(walker));
	}
	return l1;
}
