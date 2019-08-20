#ifndef C_I2C2_H_
#define C_I2C2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// Range: Latitude: 37.xxxxxx - 38.xxxxxx
// Range: Longitude: -122.xxxxxx - -121.xxxxxx
typedef struct{
    float latitude; 
    float longitude;
}gps_t; 

float dist_between_two_points(gps_t src, gps_t dest);
float get_radians(float degree);
float find_min(float x, float y);
int return_closest_node(gps_t source, gps_t array[]);
void dijkstra_dy(int graph[][16], int src, int dest, int return_waypoints[], int array_size);
int isMarked(int v, int markedVertices[], int markedVerticesIdx);
void reverseArray(int arr[], int start, int end); 


//Geekforgeeks Solution
// int dijkstra(int graph[][10], int src);
// int minDistance(int dist[], bool sptSet[]);
// void printPath(int parent[], int j);
// void printSolution(int dist[], int parent[]);

#ifdef __cplusplus
}

#endif
#endif /* C_I2C2_H_ */






