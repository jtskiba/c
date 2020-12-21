
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Skiena section 3.1.2, page 68

Problem: Implementation of linked lists (dynamic allocation of memory)

*/

typedef struct list{
	int item;
	struct list *next;
} list;

list *search_list(list *l, int x){
	if (l == NULL) return(NULL);
	
	if (l->item == x)
		return(l);
	else 
		return(search_list(l->next, x));
}	

void insert_list(list **l, int x){
	list *p;
	p = malloc(sizeof(list));
	p->item = x;
	p->next = *l;
	*l = p;
}

list *predecessor_list(list *l, int x){
	
	if ((l == NULL) || (l->next == NULL)){
		printf("Error: predecessor function called on NULL list\n");
		return(NULL);
	}
	
	if (((l->next)->item) == x)
		return (l);
	else
		return(predecessor_list(l->next, x));
	
}

void delete_list(list **l, int x){
	list *p;
	list *pred;
	list *search_list(), *predecessor_list();

	p = search_list(*l, x);
	
	if (p != NULL){
		pred = predecessor_list(*l, x);
		if (pred == NULL)
			*l = p->next;
		else
			pred->next = p->next;
	free(p);
	}
	
	
}
	
void print_list(list *l){
	
	list *temp;
	temp = l;
	
	if(temp == NULL)
    {
        printf("No data found in the list.\n");
    }
		
	while (temp != NULL){
		printf(">%d", temp->item);
		temp = temp->next;
	}
}



int main(void){
	
	list *my_list, *dummy;
	my_list = NULL;
	
	insert_list(&my_list, 2);
	insert_list(&my_list, 4);
	insert_list(&my_list, 6);
	insert_list(&my_list, 8);
	
	print_list(my_list);
	
	dummy = search_list(my_list, 6);
	printf("\nsought for is %d\n",dummy->item);
	
	dummy = predecessor_list(my_list, 6);
	printf("predecessor is %d\n",dummy->item);
	
	printf("removing item = 4: ");
	delete_list(&my_list, 4);
	print_list(my_list);
	
	return 0;
}