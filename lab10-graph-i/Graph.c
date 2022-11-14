#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"
#include "Graph.h"

TGraphL *createGraphAdjList(int numberOfNodes)
{
	// TODO: 1
	TGraphL *adjList = malloc(sizeof(TGraphL));
	adjList->nn = numberOfNodes;
	adjList->adl = malloc(numberOfNodes * sizeof(TNode));
	for (int i = 0; i < numberOfNodes; ++i)
	{
		adjList->adl[i] = NULL;
	}
	return adjList;
}

void addEdgeList(TGraphL *graph, int v1, int v2)
{
	// TODO: 1
	ATNode n1 = malloc(sizeof(ATNode));
	ATNode n2 = malloc(sizeof(ATNode));
	n1->v = v1;
	n2->v = v2;
	n1->next = graph->adl[v2];
	graph->adl[v2] = n1;
	n2->next = graph->adl[v1];
	graph->adl[v1] = n2;
}

void dfsRecHelper(TGraphL *graph, int *visited, List *path, int s)
{
	// TODO: 2
	visited[s] = 1;
	enqueue(path, s);
	ATNode aux = graph->adl[s];
	while (aux != NULL)
	{
		if (visited[aux->v] == 0)
		{
			dfsRecHelper(graph, visited, path, aux->v);
		}
		aux = aux->next;
	}
}

List *dfsRecursive(TGraphL *graph, int s)
{
	// TODO 2
	List *list = createList();
	int *visited = calloc(graph->nn, sizeof(int));
	dfsRecHelper(graph, visited, list, s);
	return list;
}

List *bfs(TGraphL *graph, int s)
{
	// TODO: 3
	int *visited = calloc(graph->nn, sizeof(int));
	Queue *q = createQueue();
	List *list = createList();
	enqueue(q, s);
	enqueue(list, s);
	visited[s] = 1;
	while (isListEmpty(q) == 0)
	{
		int v = front(q);
		dequeue(q);
		ATNode aux = graph->adl[v];
		while (aux != NULL)
		{
			if (visited[aux->v] == 0)
			{
				enqueue(q, aux->v);
				visited[aux->v] = 1;
				enqueue(list, aux->v);
			}

			aux = aux->next;
		}
	}

	return list;
}

void destroyGraphAdjList(TGraphL *graph)
{
	// TODO: 4
}

void removeEdgeList(TGraphL *graph, int v1, int v2)
{
	TNode *it = graph->adl[v1];
	TNode *prev = NULL;
	while (it != NULL && it->v != v2)
	{
		prev = it;
		it = it->next;
	}

	if (it == NULL)
		return;

	if (prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while (it != NULL && it->v != v1)
	{
		prev = it;
		it = it->next;
	}
	if (it == NULL)
		return;
	if (prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL *graph, int v)
{
	for (int i = 0; i < graph->nn; i++)
	{
		removeEdgeList(graph, v, i);
	}
}
