#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "graph.h"

int main(int argc, char **argv)
{
    int vertex, start_index, start, end, p_w, p_e, i, j; // T1*8
    float* distance = NULL; //T2*2
    float *weights = NULL;  
    float **matrix;         //T3
    int *path = NULL;       // T4

    if(argc == 1)  //T5(cały if)
    {
        printf("No filename given\n"); 
        return -1;
    }

    FILE *maze;    //T6

    if ((maze = fopen(argv[1], "r")) == NULL)    //T7(cały if)
    {
        printf("No such file: %s\n", argv[1]);
        return -1;
    }

    printf("Set start vertex: ");
    scanf("%d", &start);
    start_index = start;
    printf("Set stop vertex: ");
    scanf("%d", &end);

    fscanf(maze,"%d", &vertex);
    printf("%d", vertex);

    printf("Number of vertices: %d\n",vertex);

    matrix = (float **)malloc( sizeof(float*) * vertex);

    for (i = 0; i < vertex; ++i)    //T8 * vertex
    {
        matrix[i] = (float *)malloc(sizeof(float*) * vertex); //T9 *vertex
        distance = (float *)malloc(sizeof(float) * vertex); //T10 *vertex
        weights = (float *)malloc(sizeof(float) * vertex); //T11* vertex
        path = (int *)malloc(sizeof(int) * vertex);  // T12* vertex
    }

    srand(time(NULL));

    for(i = 0; i < vertex; ++i)  //T13 *vertex
        weights[i] = (float)rand() / RAND_MAX * 10;

    for (i = 0; i < vertex; ++i) //T14 *vertex
         for (j = 0; j < vertex; ++j) //T14 *vertex *vertex
            matrix[i][j] = NO_EDGE; //T15 *vertex *vertex

    while (fscanf(maze,"%d %d",&p_w,&p_e) == 2)   //T16 * możliwe przejscia/2
    {
        matrix[p_w][p_e] = (weights[p_w] + weights[p_e])/2; //T17 * możliwe przejscia/2
        matrix[p_e][p_w] = matrix[p_w][p_e]; //T18 * możliwe przejscia/2
    }

    free(weights);                                 //T19

    for (i = 0; i < vertex; ++i)                //T20 *vertex
    {
        for (j = 0; j < vertex; ++j)            //T21 * vertex * vertex
            printf("%.1lf  ", matrix[i][j]);    //T22 * vertex * vertex
        printf("\n");                           //T23 *vertex
    }

    i = dijkstra_search(vertex, matrix, start, distance,  path);  //O(vertex^2) 

    if (i != 0) { //T48
        printf("Error in dijkstra_search"); //T49
        for (i = 0; i < vertex; ++i) //T50 * vertex
            free(matrix[i]); //T51 * vertex

        free(matrix);// T52
        free(distance);// T53
        free(path); //T 54
        fclose(maze); //T55
        return -1; // T56
    }

    printf("Distance: %f\n", distance[end]);  //T57
    printf("Shortest path from end to start: \n%d", end); //T58

    while (path[end] != -1) //W najgorszym wypadku vertex *T59
     {
        printf("-%d",path[end]);// T60 *vertex
        end = path[end]; // T61 *vertex
    }
    if (start_index != end) // T62 
    {
        system("cls"); // T63 
        printf("This maze doesn't have exit\n"); // T64 
    }
    printf("\n"); // T65

    for (i = 0; i < vertex; ++i) // T66 *vertex
        free(matrix[i]); // T67 *vertex

    free(matrix); // T68
    free(distance); // T69
    free(path);// T70

    fclose(maze);// T71

    return 0; //T 72
}
// Tutaj także największa złożoność to vertex ^2 więc tylko taką rozpatrujemy, ale musimy jeszcze doliczyc złozoność od innego czynnika
// O(vertex^2(T21+T22+T14+T15)+ liczbaprzejsc(krawędzi)/2(T16+T17+T18)+O(vertex^2)(z funkcji)) == O(vertex^2 + liczbaprzejsc)