#include <stdio.h>
#include <stdlib.h>

/*
#define N_LEAF 0
#define N_INTERNAL 1

*/
/*
p.298 3.9.2 Unions
Implement a binary tree data structure
where each leaf node has two double data values and each internal node has
pointers to two children but no data.
*/



struct node_s{
	struct node_s *left;
	struct node_s *right;
	double data[2];
};

union node_u{
	struct {
		union node_u *left;
		union node_u *right;
	} internal;
	double data[2];
};

/*
With the above node_u encoding, however, there is no way to determine whether a given
node is a leaf or an internal node. A common method is to introduce an enumerated
type defining the different possible choices for the union, and then create a
structure containing a tag field and the union
*/

typedef enum {N_LEAF, N_INTERNAL} nodetype_t;

struct node_t {
	nodetype_t type;
	union{
		struct {
			struct node_t *left;
			struct node_t *right;
		} internal;
		double data[2];
	} info;
};


int main(void){
	short *s;
	
	/*
	union node_u *test;
	union node_u *test_left;
	union node_u *test_right;
	
	
	test->data[0] = 2.0;
	test->data[1] = 3.0;
	test->internal.left = test_left;
	test->internal.right = test_right;
	*/

	printf("%d\n",sizeof(*s));
	
	return 0;
}
