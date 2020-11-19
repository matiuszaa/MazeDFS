#include <limits.h>

#include "graph.h"

int dijsktra_search(int vertices, float **graph, int start, int *distance, int *path)     
{
    int i, j, shortest;

    if (start >= vertices)
        return -1;

    for (i = 0; i < vertices; ++i)
    {
        graph[i][i] = VERTEX_NOT_USED;
        distance[i] = INT_MAX;
        path[i] = -1;
    }

    distance[start] = 0;
    graph[start][start] = VERTEX_USED;

    /* Checking every vertex of array */
    for (i = 0; i < vertices; ++i)
    {
        shortest = 0;

        /* Go past through used vertices */
        while (graph[shortest][shortest] != VERTEX_NOT_USED)
            ++shortest;

        /* Find lowest sum of weights available */
        for (j = shortest + 1; j < vertices; ++j)
            if (distance[shortest] > distance[j] && graph[j][j] == VERTEX_NOT_USED)
                shortest = j;   

        /* Modify shortest paths to neighbours */
        for (j = 0; j < vertices; ++j)
        {
            if (graph[shortest][j] == NO_EDGE || j == shortest)
                continue;
            
            if (distance[j] > graph[shortest][j] + distance[shortest])
            {
                distance[j] = graph[shortest][j] + distance[shortest];
                path[j] = shortest;
            }
        }

        graph[shortest][shortest] = VERTEX_USED;            
    }

    return 0;
}
