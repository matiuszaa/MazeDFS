#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"

int main(int argc, char **argv)
{
    int vertex;
    int start;
    int p_w = 0;
    int p_e = 0;
    float matrix[100][100];
    int i, j;
    float distance[100];
    float wages[100];
    int path[100];
    int end;

    if(argc == 1)
    {
        printf("Did you insert a file?");
        return -1;
    }

    FILE *in = fopen(argv[1], "r");
    printf("give me starting vertex");
    scanf("%d", &start);
    printf("give me exit vertex");
    scanf("%d", &end);
    srand( time ( NULL ));
    fscanf(in,"%d", &vertex);

    if(vertex > 100)
        printf("Too much vertices(no more than 100)");
        return -1;

    printf("%d\n",vertex);

    for(i = 0; i < vertex; ++i)
        wages[i] = (float)rand() / RAND_MAX * 10;
    
    for (i = 0; i < vertex; ++i)
        for (j = 0; j < vertex; ++j)
        {
            matrix[i][j] = NO_EDGE;
        }

    while (fscanf(in,"%d %d",&p_w,&p_e) == 2)
    {
        matrix[p_w][p_e] = (wages[p_w] + wages[p_e]) /2; 
        matrix[p_e][p_w] = matrix[p_w][p_e];
    }

    for (i = 0; i < vertex; ++i)
    {
        for (j = 0; j < vertex; ++j)
            printf("%.1lf  ", matrix[i][j]);
        printf("\n");
    }

    i = dijsktra_search (vertex, matrix, start, distance,  path);
    
    if (i!=0)
        printf("ERROR in dijkstra_search");

    while(path[end]!=-1)
    {
        printf("%d-",path[end]);
        end=path[end];
    }
    return 0;
}
