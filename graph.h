#ifndef GRAPH_H
#define GRAPH_H

#define NO_EDGE -1
#define VERTEX_USED 1
#define VERTEX_NOT_USED 0

/**
 * Function finds the shortest paths from start to all vertices in graph. 
 * @param int vertices - number of all vertices in graph. 
 * @param float **graph - Represented as adjacency matrix.
 * @param int *distance - Array of the shortest paths from start.
 * @param int *path - Array of previous vertices.  
 * @return -1 if failed 0 if successful.
 */
int dijkstra_search(int vertices, float **graph, int start, int *distance, int *path); 

#endif
