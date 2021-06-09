#include <limits.h>
#include <stdio.h>

#include "graph.h"

int dijkstra_search(int vertices, float **graph, int start, float *distance, int *path)     
{
    int i, j, shortest; //T25*3

    if (start >= vertices) //T26
        return -1;   //T27

    for (i = 0; i < vertices; ++i)   //T28 *vertices
    {
        graph[i][i] = VERTEX_NOT_USED;  //T29 *vertices
        distance[i] = INT_MAX;  //T30 *vertices
        path[i] = -1;   //T31 *vertices
    }

    distance[start] = 0;   //T32

    /* Checking every vertex of array */
    for (i = 0; i < vertices; ++i)  // T33 * vertices
    {
        shortest = 0;   //T34 * vertices

        /* Go past through used vertices */
        while (graph[shortest][shortest] != VERTEX_NOT_USED)  // T35 * vertices* vertices
            ++shortest; //T36*vertices*vertices

        /* Find lowest sum of weights available */
        for (j = shortest + 1; j < vertices; ++j)  //T37 * vertices * vertices
            if (distance[shortest] > distance[j] && graph[j][j] == VERTEX_NOT_USED) //T38 * vertices *vertices
                shortest = j;   // T39 *vertices *vertices

        /* Modify shortest paths to neighbours */
        for (j = 0; j < vertices; ++j)  //T40 * vertices
        {   
            if (graph[shortest][j] == NO_EDGE || j == shortest)  //T41 * vertices *vertices
                continue; 
            
            if (distance[j] > graph[shortest][j] + distance[shortest]) //T43 * vertices * vertices
            {
                distance[j] = graph[shortest][j] + distance[shortest]; //T44 *vertices *vertices
                path[j] = shortest; //T45 *vertices *vertices
            }
        }

        graph[shortest][shortest] = VERTEX_USED;            // T46 *vertices
    }

    return 0;    //T47
}
// vertices = vertex
// Jak widzimy nie ma złożoności wyższego rzędu niż n^2 więc skupimy się tylko na takiej złożoności O(vertex^2(T44+T43+T41+T38+T37+T35+T36))
// = O(vertex^2)