//Graph Coloring Problem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};
 
struct AdjList {
    int color;
    struct AdjListNode* head;
};
 
struct Graph {
    int V;
    struct AdjList* array;
};
 
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode= (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
 
    int i;
    for (i = 0; i < V; ++i){
        graph->array[i].head = NULL;
        graph->array[i].color = 0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
 
    struct AdjListNode* temp = NULL;
    struct AdjListNode* newNode = newAdjListNode(dest);
    int isExist = 0;
    
    temp = graph->array[src].head;
    while(temp){
    	if(temp->dest==dest){isExist = 1;}
    	temp = temp->next;
	}
	
    if(graph->array[src].head != NULL && isExist==1){
    	isExist=1;	
	}
    

    else{
    	if (graph->array[src].head == NULL) {
	        graph->array[src].head = newNode;
	    }
	    else {
	        temp = graph->array[src].head;
	        while (temp->next != NULL) {
	            temp = temp->next;
	        }
	        temp->next = newNode;
	    } 
	
	    newNode = newAdjListNode(src);
	    if (graph->array[dest].head == NULL) {
	        graph->array[dest].head = newNode;
	    }
	    else {
	        temp = graph->array[dest].head;
	        while (temp->next != NULL) {
	            temp = temp->next;
	        }
	        temp->next = newNode;
	    }
	}
    
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v) {
        struct AdjListNode* temp = graph->array[v].head;
        printf("\n Vertex %d\n head ", v+1);
        while (temp) {
            printf("-> %d", 1+temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}
int coloringAlgorithm(struct Graph* graph){
    int colorValue = 0;
    int chromaticNumber = 0;
    int i;
    int k;
    struct AdjListNode* temp;
    
    int results[graph->V];
    for(i=0; i<graph->V; ++i){ results[i]=-1;}
    results[0]=0;
    
    int isColored[graph->V];
    for(i=0; i<graph->V; ++i){ isColored[i]=0;}
    
    
    for(k=1; k<graph->V; ++k){
        temp = graph->array[k].head;
        while(temp){
            if(results[temp->dest]!=-1){ isColored[results[temp->dest]]=1; }
            temp = temp->next;
        }
        colorValue = 0;
        while(colorValue<graph->V){
            if(isColored[colorValue]==0){break;}
            colorValue+=1;
        }
        results[k] = colorValue;
        
        for(i=0; i<graph->V; ++i){ isColored[i]=0;}
    }
    
    for(i=0;i<graph->V;++i){
        printf("%d ",results[i]);
        if(results[i]>chromaticNumber){chromaticNumber = results[i];}
    }
    
    return chromaticNumber;
}
 
int main()
{
    FILE* file;
    char fileName[100];
    printf("Please enter the name of the input file :\n");
	scanf("%s", fileName);
	file = fopen(fileName, "r");
    int srcVer;
    int destVer;
    int totalVer;
    int totalEdge;
    char inst[5];
    int chromaticNumber;
    
    struct Graph* graph;
    while(!feof(file)){
        fscanf(file,"%s %d %d",inst,&srcVer,&destVer);
        if(strcmp(inst,"p")==0){
            totalEdge = destVer;
            totalVer = srcVer;
            graph = createGraph(totalVer);
            continue;
        }
        addEdge(graph, srcVer-1, destVer-1);
    }
    //printGraph(graph);
    
    chromaticNumber = coloringAlgorithm(graph);
    printf("\n%d", chromaticNumber);
    fclose(file);
    scanf("\n%d", &chromaticNumber);
    return 0;
}
