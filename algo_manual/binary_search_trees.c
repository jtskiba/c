
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Skiena section 3.1.2, page 68

Problem: Implementation of binary search trees

Binary tree nodes have left and right pointer fields, an (optional) parent pointer,
and a data field.

*/
typedef struct tree{
	int item;
	struct tree *left;
	struct tree *right;
	struct tree *parent;
} tree;


tree *search_tree(tree *t, int x){
	
	if (t == NULL) return(NULL);
	
	if (t->item == x)
		return(t);
	if (t->item < x)
		return(search_tree(t->left, x));
	else
		return(search_tree(t->right, x));
}

tree *my_find_minimum(tree *t){
	tree *min; //temp
	min = t;	
	if (t==NULL) return(min);
	
	if (((t->left)->item) < (min->item))
		my_find_minimum(t->left);
}

tree *find_minimum(tree *t){
	tree *min; //temp
	if (t==NULL) return(NULL);
	min = t;	
	while (min->left != NULL)
		min = min->left;
	return(min);
}

void insert_tree(tree **t, int item, tree *parent){
	tree *p;
	
	if (*t == NULL){
		p = malloc(sizeof(tree));
		p->item = item;
		p->left = p->right = NULL;
		p->parent = parent;
		*t = p;
		return;
	}
	
	if (((*t)->item) > item)
		insert_tree(&((*t)->left), item, *t);
	else
		insert_tree(&((*t)->right), item, *t);
		
}

void process_tree(int item){
	printf(">%d",item);
}

void traverse_tree(tree *t){
	if (t != NULL){
		traverse_tree(t->left);
		process_tree(t->item);
		traverse_tree(t->right);
	}
}

int main(void){
	
	tree *my_tree;
	tree *parent;
	my_tree = NULL;
	
	insert_tree(&my_tree, 5, my_tree);
	
	parent = my_tree;
	//parent = search_tree(my_tree, 5);
	insert_tree(&my_tree, 7, parent);
	insert_tree(&my_tree, 2, parent);
	
	//parent = search_tree(my_tree, 2);
	insert_tree(&my_tree, 1, parent);
	insert_tree(&my_tree, 3, parent);
	
	//parent = search_tree(my_tree, 7);
	insert_tree(&my_tree, 9, parent);

	//parent = search_tree(my_tree, 7);
	insert_tree(&my_tree, 10, parent);

	
	traverse_tree(my_tree);
	
	return 0;
}