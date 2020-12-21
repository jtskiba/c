#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

// below is borrowed from geeksforgeeks.org (I tried myself first, then used their more optimal/correct approach)
struct AdjListNode{
	int dest;
	struct AdjListNode* next;
};

struct AdjList{
	struct AdjListNode* head;
};

struct Graph{
	int V;
	int V_used;
	struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest){
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int V){
	
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
	graph->V = V;
	graph->V_used = 0;
	graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
	int i;
	for (i=0; i<V; i++){
		graph->array[i].head = NULL;
	}
	return graph;
}	

int findAdjListLength(struct AdjListNode* l){
	int i = 0;
	while (l != NULL){
		i++;
		l = l->next;
	}
	return(i);
		
		
}

void addEdge(struct Graph* graph, int src, int dest){
	struct AdjListNode* newNode = newAdjListNode(dest);
	
	if(dest != src){
		if (graph->array[src].head == NULL)
			graph->V_used = graph->V_used + 1;
		if (graph->array[dest].head == NULL)
			graph->V_used = graph->V_used + 1;
		newNode->next = graph->array[src].head;
		graph->array[src].head = newNode;
		
		newNode = newAdjListNode(src);
		newNode->next = graph->array[dest].head;
		graph->array[dest].head = newNode;
	}
	else{
		if (graph->array[src].head == NULL)
			graph->V_used = graph->V_used + 1;
		newNode->next = graph->array[src].head;
		graph->array[src].head = newNode;
		
	}
}	


void addEdgeSide(struct Graph* graph, int src, int dest){
	
	struct AdjListNode* newNode = newAdjListNode(dest);
	
	if (graph->array[src].head == NULL)
		graph->V_used = graph->V_used + 1;
	
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
	
	//newNode = newAdjListNode(src);
	//newNode->next = graph->array[dest].head;
	//graph->array[dest].head = newNode;
}	


void removeEdge(struct Graph* graph, int src, int dest){
	int i, j, k;
	int list_size, value;
	struct AdjListNode *node, *prev_node;
	
	i = 1;
	node = graph->array[src].head;
	prev_node = graph->array[src].head;
	value = node->dest;
	list_size = findAdjListLength(node);
	while ((value != dest)){			
		prev_node = node;
		node = node->next;
		value = node->dest;
		i++;
	} 
	if (value == dest)
		prev_node->next = node->next;
	if (i == 1)
		graph->array[src].head = node->next;
	
	/*
	if ((graph->array[src].head == NULL) && (graph->V_used > 0))
		graph->V_used = graph->V_used - 1;
	*/
	
	////////////////////
	
	i = 1;
	node = graph->array[dest].head;
	prev_node = graph->array[dest].head;
	value = node->dest;
	list_size = findAdjListLength(node);
	while ((value != src)){	
		prev_node = node;
		node = node->next;
		value = node->dest;
		i++;
	} 
	if (value == src){
		//printf("------\n");
		prev_node->next = node->next;
	}
	if (i == 1)
		graph->array[dest].head = node->next;
	
	/*
	if ((graph->array[dest].head == NULL) && (graph->V_used > 0))
		graph->V_used = graph->V_used - 1;
	*/
	
}	

void removeSelfLoops(struct Graph* graph, int dest){
	//struct AdjListNode* newNode = newAdjListNode(dest);
	int i, j, k;
	int list_size, value;
	struct AdjListNode *node, *prev_node;

	i = 1;
	node = graph->array[dest].head;
	prev_node = graph->array[dest].head;
	value = node->dest;
	list_size = findAdjListLength(node);
	//printf("--------value = %d, list size = %d\n", value, list_size);
	
	while ((i <= list_size)){ // || (node->next != NULL)){
		if (value == dest){
			if (i == 1){
				graph->array[dest].head = node->next;
				i--; //in case not only i=1 is self ref, but also i=2 and then even perhaps i=3 etc..
				list_size--; //as above
			}
			else{
				prev_node->next = node->next;
				
			}
		}
		else{
			prev_node = node;
		}
	
		if (i != list_size){
			node = node->next;
			value = node->dest;			
		}
		i++;
		
		
	}
	
	// update V_used in case by removing an edge, any of the vertices are removed
	if ((graph->array[dest].head == NULL) && (graph->V_used > 0))
		graph->V_used = graph->V_used - 1;
	
	
}	

void removeAllEdges(struct Graph* graph, int src){
	
	if (graph->array[src].head != NULL){
		graph->array[src].head = NULL;
		//graph->V_used = graph->V_used - 1;
	}
}


void mergeVs(struct Graph* graph, int src, struct AdjListNode* list){
//void mergeVs(struct AdjListNode* v1, struct AdjListNode* v2){	
	
	if (list != NULL){
		struct AdjListNode* newNode = newAdjListNode(list->dest);
		newNode->next = graph->array[src].head;
		graph->array[src].head = newNode;
	
		if (list->next != NULL)
			mergeVs(graph, src, list->next);
		else
			graph->V_used = graph->V_used - 1;
	}
	else{
		graph->V_used = graph->V_used - 1; //if we remove the only edge in step1 removeEdg, then merging the list will be empty but we still want to V_used--
	}
	//addEdgeSide(graph, v1, (graph->array[v2].head)){
	
	
}
void updateNode(struct AdjListNode* node, int from, int to){
	if (node->dest == from)
		node->dest = to;
	if (node->next != NULL)
		updateNode(node->next, from, to);
}

void changeDest(struct Graph* graph, int from, int to){
	int i;
	for (i = 1; i < graph->V; i++){
		if (graph->array[i].head != NULL){
			updateNode(graph->array[i].head, from, to);
		}
			
	}
}


void printGraph(struct Graph* graph){
	int v;
	for (v=0; v<(graph->V); v++){
		struct AdjListNode* currentNode = graph->array[v].head;
		printf("\n Adjacency list of vertex %d\n head", v);
		while (currentNode) {
			printf("-> %d", currentNode->dest);
			currentNode = currentNode->next;
		}
		printf("\n");
	}
}

void printMyGraph(struct Graph* graph){
	int v;
	printf("\n Adjacency list of vertices:\n");
	for (v=0; v<(graph->V); v++){
		struct AdjListNode* currentNode = graph->array[v].head;
		printf("%d:", v);
		while (currentNode) {
			printf(">%d", currentNode->dest);
			currentNode = currentNode->next;
		}
		printf("\n");
	}
}

int randint1toN(int n){
	//srand(time(NULL));
	return((rand() % n) + 1); 
}

int findDestByIndex(struct AdjListNode* l, int i){
	int j = 1;
	while ( j != i){
		j++;
		l = l->next;
	}
	return(l->dest);
}


int pickVsrc(struct Graph* graph){
	int i = 1;
	int nonempty = 0;
	int V = graph->V;
	int V_used = graph->V_used;
	int randomNo = randint1toN(V_used);
	
	//printf("radomNo = %d\n", randomNo);
	for(i = 1; i<V; i++){
		if (graph->array[i].head != NULL)
			nonempty++;
		if (nonempty == randomNo)
			return i; 
	}
	return -1;
	
}

int countCuts(struct Graph* graph){
	int i = 1;
	int nonempty = 0;
	int first = 1;
	int first_vertex;
	int first_length;
	
	for(i = 1; i<graph->V; i++){
		if (graph->array[i].head != NULL)
			nonempty = 1;
		if (nonempty == first){
			first_vertex = i;
			return findAdjListLength(graph->array[first_vertex].head); 
		}
	}
		
	return -1;
	
}


int pickVdest(struct Graph* graph, int src){
	int index_val;
	int length = findAdjListLength(graph->array[src].head);
	int randomNo = randint1toN(length);
	//printf("RadomNoArray = %d\n", randomNo);
	index_val = findDestByIndex(graph->array[src].head, randomNo);
	return index_val;
}

int KargersMinCut(struct Graph* graph){
	int src, dest;
	int i, n, min, glob_min, total_it;
	n = graph->V;
	glob_min = INT_MAX;
	total_it = (n * (((int)log((double)n))+1));
	//printf("total int = %d\n", total_it);
	
	for (i=0;i<total_it;i++){
	
		while (graph->V_used > 2){
			src = pickVsrc(graph);
			//src = 3;
			//printf("src=%d ", src);
			dest = pickVdest(graph, src);
			//dest = 2;
			//printf("dest=%d ", dest);
			
			//step1 - remove edge
			removeEdge(graph, src, dest);
			//printf("V_used = %d\n",graph->V_used);
			
			//step2 - merge vertices
			mergeVs(graph, src, graph->array[dest].head);
			//printf("V_used = %d\n",graph->V_used);
			
			//step3 - remove all edges from dest
			removeAllEdges(graph, dest);
			//printf("V_used = %d\n",graph->V_used);
			
			//step4 - change refs to dest to src (as dest no longer exists and is merged to src)
			changeDest(graph, dest, src);
			//printf("V_used = %d\n",graph->V_used);
			
			//step5 - remove any self loops (i.e. src being linked to src)
			removeSelfLoops(graph, src);
			
			//for(i = 1; i<graph->V; i++){
			//	if (graph->array[i].head != NULL)
			//		removeSelfLoops(graph, i);
			//}
			//printf("V_used = %d\n",graph->V_used);
		}
		
		min = countCuts(graph);
		if (min < glob_min)
			glob_min = min;
	}
	
	/*
	for(i = 1; i<graph->V; i++){
		if (graph->array[i].head != NULL)
			removeSelfLoops(graph, i);
	}
	*/
	
	
	
	
	/*
	////////////////////// edge 2
	
		src = 3;
		printf("my pick src=%d ", src);
		dest = 1;
		printf("my pick dest=%d ", dest);
		
		//step1 - remove edge
		removeEdge(graph, src, dest);
		//printf("V_used = %d\n",graph->V_used);
		
		//step2 - merge vertices
		mergeVs(graph, src, graph->array[dest].head);
		//printf("V_used = %d\n",graph->V_used);
		
		//step3 - remove all edges from dest
		removeAllEdges(graph, dest);
		//printf("V_used = %d\n",graph->V_used);
		
		//step4 - change refs to dest to src (as dest no longer exists and is merged to src)
		changeDest(graph, dest, src);
		//printf("V_used = %d\n",graph->V_used);
		
		//step5 - remove any self loops (i.e. src being linked to src)
		removeSelfLoops(graph, src);
		printf("V_used = %d\n",graph->V_used);

		
		////////////////////// edge 3
	
		src = 3;
		printf("my pick src=%d ", src);
		dest = 6;
		printf("my pick dest=%d ", dest);
		
		//step1 - remove edge
		removeEdge(graph, src, dest);
		//printf("V_used = %d\n",graph->V_used);
		
		//step2 - merge vertices
		mergeVs(graph, src, graph->array[dest].head);
		//printf("V_used = %d\n",graph->V_used);
		
		//step3 - remove all edges from dest
		removeAllEdges(graph, dest);
		//printf("V_used = %d\n",graph->V_used);
		
		//step4 - change refs to dest to src (as dest no longer exists and is merged to src)
		changeDest(graph, dest, src);
		//printf("V_used = %d\n",graph->V_used);
		
		//step5 - remove any self loops (i.e. src being linked to src)
		removeSelfLoops(graph, src);
		printf("V_used = %d\n",graph->V_used);
	*/
	
	//printf("here\n");
	return glob_min;
}
		

int main(void){
	
	int V = 201;
	int temp;
	struct Graph* graph = createGraph(V);
	
	
	
	char line[1000], *p, *e;
	long v;
	int i = 0;
	FILE *file;
	file = fopen("kargerMinCut.txt", "r");
	if (file) {
		//fscanf(file, "%d ", &vertex);
		//printf(">%d\n", vertex);
		
		while (fgets(line, sizeof(line), file)){
			i = 1;
			p = line;
			//printf("%d ", i);
			for (p = line; ; p = e) {
				v = strtol(p, &e, 10); 
				if (p == e)
					break;
				//process v below
				if (i==1) 
					temp=v;
				else
					addEdgeSide(graph, temp, v);
				//printf("%d ", v);
				i++;
			}
			//printf("\n-----------------------------------------\n");
		}
		
		fclose(file);
	}
	
	/*
	
	addEdgeSide(graph, 200, 200);
	addEdgeSide(graph, 200, 200);
	addEdgeSide(graph, 200, 200);
	addEdgeSide(graph, 200, 200);
	addEdgeSide(graph, 200, 200);
	addEdgeSide(graph, 200, 9);
	addEdgeSide(graph, 200, 10);
	addEdgeSide(graph, 200, 200);
	addEdgeSide(graph, 200, 200);
	addEdgeSide(graph, 200, 11);
	addEdgeSide(graph, 200, 12);
	addEdgeSide(graph, 200, 13);
	addEdgeSide(graph, 200, 200);
	addEdgeSide(graph, 200, 200);
	addEdgeSide(graph, 200, 200);
	removeSelfLoops(graph, 200);
	printMyGraph(graph);
	*/
	
	/*
	addEdge(graph, 1, 2);
	addEdge(graph, 1, 3);
	addEdge(graph, 1, 5);
	addEdge(graph, 2, 6);
	addEdge(graph, 2, 3);
	addEdge(graph, 3, 4);
	addEdge(graph, 7, 4);
	*/
	
	//addEdge(graph, 197, 199);
	//addEdge(graph, 197, 200);
	//removeEdge(graph, 199, 197);
	//removeSelfLoops(graph, 197);
	
	//printf("Length: %d\n", findAdjListLength(graph->array[197].head));
	//printf("Length: %d\n", findAdjListLength(graph->array[199].head));
	
	//addEdge(graph, 193, 195);
	//removeEdge(graph, 193, 195);
	//removeAllEdges(graph, 199);
	//removeSelfLoops(graph, 200);
	//mergeVs(graph->array[199].head, graph->array[200].head);
	//mergeVs(graph, 199, graph->array[200].head);
	//changeDest(graph, 1, 33);
	//printMyGraph(graph);
	//printf("V_used = %d\n",graph->V_used);
	
	//removeEdge(graph, 197, 198);
	//mergeVs(graph, 197, graph->array[198].head);

	srand(time(NULL));
	temp = KargersMinCut(graph);
	//printMyGraph(graph);
	printf("global min cuts = %d\n", temp);



	//printf("V_used = %d\n",graph->V_used);
	
	//printf("Length: %d\n", findAdjListLength(graph->array[197].head));
	//printf("Length: %d\n", findAdjListLength(graph->array[199].head));
	//temp = randint1toN(findAdjListLength(graph->array[1].head));
	//printf("Random: %d\n", temp );
	//temp = findDestByIndex(graph->array[1].head, temp);
	//printf("Dest of Random: %d\n", temp );
	
	
	return 0;
}






