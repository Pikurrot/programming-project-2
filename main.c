// PREGUNTES CLASSSE 11/05
// 1. same city loop
// 2. SAME CITY LOOP visited vector for not repeating cities (NOT SAVE COST,
// save binary vector with position 0 or 1 if visited!) (or maybe save vector
// with positions? my idea)
// 3. #ifdef compilation include large.h
//  dijkstra algorithm is more exhaustive, but doesn't work with medium and
//  large, we have to use HEURISTIC
//--- 5/18
// 4. ifdef
// hay q descubrir la cosa especial q se define en la compilacion, cuando se define el gcc para usar el ifdef
// delivery SUNDAY 28/05
//  ----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define USE_SMALL
#define USE_MEDIUM

#ifdef USE_SMALL
#include "small.h"
#endif
#ifdef USE_MEDIUM
#include "medium.h"
#else
#include "large.h"
#endif

/*
#define USE_HEADER 1

#if USE_HEADER == 1
#include "small.h"
#elif USE_HEADER == 2
#include "medium.h"
#elif USE_HEADER == 3
#include "large.h"
#endif
*/

// graph functions
void resetVisited();
int RouteSearch(struct RoadMap *first, struct RoadMap *last, int source_id, int dest_id);
void addToRoadMap(struct RoadMap *first, struct RoadMap *last, int city_id, int total_cost);
void printRoadMap(struct RoadMap *first, struct RoadMap *last);
void deleteAllRoadMap(struct RoadMap *first, struct RoadMap *last);

int visited[NUMBER_CITIES];


void resetVisited()
{
	// initialize the visited array with 0
	for (int i = 0; i < NUMBER_CITIES; i++)
	{
		visited[i] = 0;
	}
}

// Path searching
// must create partial queue before calling RouteSearch() (first and last), add source city to the queue at the beggining
// also, resetVisited() before calling RouteSearch()
int RouteSearch(struct RoadMap *first, struct RoadMap *last, int source_id, int dest_id)
{
	// returns the total cost of the calculated route. Meanwhile, adds the cities it visits to the queue
	int i, min_cost, cost, min_cost_id, total_cost;
	int *connections;
	total_cost = last->total_cost;

	// if there is a direct connection, it's chosen; else it chooses connection to city with lowest cost from current
	if (adjacency_matrix[source_id][dest_id] != 0)
	{
		// direct connection
		total_cost += adjacency_matrix[source_id][dest_id];
		addToRoadMap(first, last, dest_id, total_cost);
		return total_cost;
	}

	// search the city with minimum cost
	connections = adjacency_matrix[source_id];
	min_cost = connections[0];
	min_cost_id = 0;

	for (i = 1; i < NUMBER_CITIES; i++)
	{
		cost = connections[i];
		if ((min_cost == 0 || (cost > 0 && cost < min_cost)) && visited[i] == 0)
		{
			min_cost = cost;
			min_cost_id = i;
		}
	}
	total_cost += min_cost;
	visited[min_cost_id] = 1;
	addToRoadMap(first, last, min_cost_id, total_cost);

	return RouteSearch(first, last, min_cost_id, dest_id);
}

// Data structure functions
void addToRoadMap(struct RoadMap *first, struct RoadMap *last, int city_id, int total_cost)
{
	// add a new city to the queue
	struct RoadMap *link = malloc(sizeof(struct RoadMap));
	link->city_id = city_id;
	link->total_cost = total_cost;
	link->next = NULL;

	if (first == NULL)
	{
		first = last = link;
		return;
	}

	last->next = link;
	last = link;
}

void printRoadMap(struct RoadMap *first, struct RoadMap *last)
{
	// will print the current status of the stack
	struct RoadMap *current = first;

	while (current != NULL)
	{
		printf("%s-", citiesInfo[current->city_id].city_name);
		current = current->next;
	}

	printf("\n");
}

void deleteAllRoadMap(struct RoadMap *first, struct RoadMap *last)
{
	// will delete only once all the cities from the stack (before progam finishes its execution)
	if (first == NULL)
	{
		// printf("Queue is empty, nothing to remove");
		return;
	}

	// remove the one element
	if (first->next == NULL)
	{
		free(first);
		first = last = NULL;
		// printf("List is empty now");
	}

	while (first != NULL) // top != NULL;
	{
		struct RoadMap *temp = first->next;
		free(first);
		first = temp;
	}
	// printf("List empty");

	// struct RoadMap *temp = first;
	// first = first->next;
	// free(temp);
	// WHILE ALTERNATIU
}

int main(int argc, char **argv)
{
	int option;

	// Check that argument is correct
	if (argc != 2)
	{
		printf("Invalid number of arguments");
		return -1;
	}

	option = atoi(argv[1]);

	if (option < 1 || option > 3)
	{
		printf("Yor must enter an integer (from 1-3)");
		return -1;
	}

	resetVisited();

	// Treat every option
	switch (option)
	{
	case 1:
		resetVisited();
		struct RoadMap link = {2, 0, NULL};
		struct RoadMap *first = &link;
		struct RoadMap *last = first;
		RouteSearch(first, last, 2, 5);
		printRoadMap(first, last);
		deleteAllRoadMap(first, last);
		printRoadMap(first, last);
		break;
	case 2:
		break;
	case 3:
		break;
	}

	return 0;
}
