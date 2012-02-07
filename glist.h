/* glist.h - generic list implementation */

#include<stdbool.h> 

enum gtypes {STR, INT, DBL, LST, SEN};

struct gnode {
    struct gnode *next;
    struct gnode *prev;
    union {
        char  *s;
        int    d;
        double f;
        struct glist *l;
    } val;
    enum gtypes type;    
};

struct glist {
    struct gnode head;
    struct gnode tail;
};

/*new gnode and new glist
glist_new_init creates both new gnodes and a new glist*/
struct gnode *gnode_new(void);
struct glist *glist_new(void);
struct glist *glist_new_init(enum gtypes arg1, ...);

/*recursive free gnode and free glist fuctions*/
void gnode_free(struct gnode *n);
void glist_free(struct glist *l);

/*recursive gnode print and glist print fuctions
glist_println is a formated glist_print function*/
void gnode_print(struct gnode *n);
void glist_print(struct glist *l);
void glist_println(char *name, struct glist *l);

/*recursive gnode copy and glist copy*/
struct gnode *gnode_copy(struct gnode *n);
struct glist *glist_copy(struct glist *l);

/*glist_isequal checks if two glist are equal
by checking that all corresponding gnodes
 are equal*/
bool gnode_isequal(struct gnode *n1, struct gnode *n2);
bool glist_isequal(struct glist *l1, struct glist *l2);

/* other gnode functions */
struct gnode *next(struct gnode *n);
struct gnode *prev(struct gnode *n);
bool is_not_SEN(struct gnode *n);
void gnode_set_str(struct gnode *n, char *s);
void gnode_set_int(struct gnode *n, int d);
void gnode_set_double(struct gnode *n, double f);
void gnode_set_list(struct gnode *n, struct glist *l);
enum gtypes gnode_get_type(struct gnode *n);
char *gnode_get_str(struct gnode *n);
int gnode_get_int(struct gnode *n);
double gnode_get_double(struct gnode *n);
struct glist *gnode_get_list(struct gnode *n);
bool gnode_isequal(struct gnode *n1, struct gnode *n2);

/* other glist functions */
struct gnode *glist_head(struct glist *l);
struct gnode *glist_tail(struct glist *l);
struct gnode *glist_front(struct glist *l);
struct gnode *glist_back(struct glist *l);
void glist_insert(struct glist *l, struct gnode *n, int index);
void glist_add(struct glist *l, struct gnode *n);
struct gnode *glist_remove(struct gnode *n);
struct gnode *glist_getindex(struct glist *l, int i);
int glist_find(struct glist *l, struct gnode *n);
int glist_length(struct glist *l);

/* high-level glist functions */
struct gnode *glist_max(struct glist *l, enum gtypes type);
struct gnode *glist_min(struct glist *l, enum gtypes type);
struct glist *glist_concat(struct glist *l1, struct glist *l2);
struct glist *glist_reverse(struct glist *l);
struct glist *glist_sort(struct glist *l);







