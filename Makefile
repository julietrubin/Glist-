all: glist_test glist_test_more glist_test_other_methods hist

glist_test : glist_test.c glist.c glist.h
	gcc -g -o glist_test glist_test.c glist.c -lm

glist_test_more : glist_test_more.c glist.c glist.h
	gcc -g -o glist_test_more glist_test_more.c glist.c -lm


glist_test_other_methods : glist_test_other_methods.c glist.c glist.h
	gcc -g -o glist_test_other_methods glist_test_other_methods.c glist.c -lm
	
	
hist : hist.c glist.c glist.h
	gcc -g -o hist hist.c glist.c -lm


clean :
	/bin/rm -rf glist_test glist_test_more hist *.dSYM
	
