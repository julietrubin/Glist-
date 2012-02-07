/* hist.c - generate a histogram given a file with a list of doubles */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "glist.h"
#include <stdarg.h>
#include <math.h>


/* read a file containing a list of doubles */
struct glist *read_file_doubles(char *filename) {
    struct glist *l;
    struct gnode *n;
    FILE *f;
    double fval;
    f = fopen(filename, "r");
    assert(f != NULL);
    
    l = glist_new();

    while (fscanf(f, "%lf\n", &fval) != EOF) {
        n = gnode_new();
        gnode_set_double(n, fval);
        glist_add(l, n);
    }
    return l;
}

int bin_length(double bincount, double max_bincount, double maxbar) {
	return round((bincount/ max_bincount) * maxbar); 
}

int bincount(struct glist *l, double start_of_bin, double end_bin) {
	struct gnode *walker;
	struct gnode *temp;
	double gnode_value;
	int bin_count;
	
	bin_count = 0;
	for (walker = glist_front(l); is_not_SEN(walker); walker = temp) {
		gnode_value = gnode_get_double(walker);
		if (gnode_value >= end_bin)
			return bin_count;
		else if (gnode_value >= start_of_bin) {
			bin_count++;
			temp = next(walker);
			glist_remove(walker);
		}
	}
	return bin_count;
}



int get_decimal_places(double start, double binsize) {
	if (start - floor(start) >= .01 || binsize - floor(binsize) >= .01)
		return 2;
	else
		return 0;
		
}

int get_total_number_places(double end, int decimal_places) {
	if (decimal_places > 0)	
		return log10(end) + 2 + decimal_places;
	else
		return log10(end) + 1;
}

void print_histogram(struct glist *l, double start, double end, double binsize, int maxbar) {
	assert(l != NULL);
	assert(start >= 0);
	assert(end >= start + binsize);
	assert(maxbar > 0);
	assert(binsize > 0);
	
	double max_bincount;
	int number_of_hashes;
	double end_bin;
	int total_number_places;
	int decimal_places;
	int i;
	
	max_bincount = glist_length(l);
	decimal_places = get_decimal_places(start, binsize);
	total_number_places = get_total_number_places(end, decimal_places) ;
	glist_sort(l);
	for(end_bin = binsize; end_bin <= end; 
		start += binsize, end_bin += binsize) {

		
		printf("[%*.*f, %*.*f]", total_number_places, decimal_places, start, 
			total_number_places, decimal_places, end_bin);
			
						
		number_of_hashes = bin_length(bincount(l, start, end_bin),
		 	max_bincount, maxbar); 
		for (i = 0; i < number_of_hashes; i++)
			printf("#");
		printf("\n");
	}	
}

int main(int argc, char *argv[]) {
    struct glist *l;
    double start;
    double end;
    double binsize;
    double maxbar;
    char *filename;

    if (argc != 6) {
        printf("Usage: hist <start> <end> <binsize> <maxbar> <filename>\n");
        exit(1);
    }
    
    start = atof(argv[1]);
    end = atof(argv[2]);
    binsize = atof(argv[3]);
    maxbar = atof(argv[4]);
    filename = argv[5];
    
     l = read_file_doubles(filename);
    
   // glist_println("l", l);
    
	print_histogram(l, start, end, binsize, maxbar);

    return 0;
}
