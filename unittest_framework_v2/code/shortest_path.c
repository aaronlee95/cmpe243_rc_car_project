#include "shortest_path.h"
#include "math.h"
#include <limits.h>
#include <stdio.h>
#define M_PI           3.14159265358979323846
#define MAX            10
#define INF            9999.0
#define SIZE           10
#define V              16

float get_radians(float degree)
{
    float radian;
    radian = degree * (M_PI/180);
    return radian;
}

// float dist_between_two_points(gps_t src, gps_t dest)
float dist_between_two_points(gps_t src, gps_t dest)
{
    // Returns distance in kilometers
    float R, d_long, d_lat, distance, a, b; 
    R = 6371.0;                     // Radius of Earth in km

    d_lat = get_radians(dest.latitude - src.latitude);
    d_long = get_radians(dest.longitude - src.longitude);

    a = pow((sin(d_lat/2)),2) + cos(get_radians(src.latitude)) * cos(get_radians(dest.latitude)) * pow((sin(d_long/2)), 2);
    b = 2 * atan2(sqrt(a), sqrt(1-a));

    distance = R * b;
    return distance;
}

int return_closest_node(gps_t source, gps_t array[])
{
    float dist;
    float MIN = INF;
    int node = 100;
    for(int i = 0; i < MAX; i++)
    {
        if((array[i].latitude > 36) && (array[i].longitude < -120)) 
        {
            dist = dist_between_two_points(source, array[i]);
            if(dist < MIN)
            {
                node = i;
                MIN = dist;
            }
        }
    }
    printf("MIN: %f, NODE: %i\n", MIN, node);
    return node;
}

float find_min(float x, float y)
{
    if(x < y)
    {
        return x;
    }
    return y;
}


int isMarked(int v, int markedVertices[], int markedVerticesIdx) {

  int i = 0;
  for (i = 0; i < markedVerticesIdx; i++) {
    if (v == markedVertices[i]) {
      return 1;
    }
  }

  return 0;
}

// void dijkstra_dy(int graph[V][V], int src, int dest, int return_waypoints[]) 
void dijkstra_dy(int graph[V][V], int src, int dest, int return_waypoints[], int array_size) 
{
    if(dest <= V)
    {
        //variables
        int x , tmpX, min, currVertex, edgeWt = 0, destValue = 0, markedValue = 0, wtTableR = 0, markedVerticesIdx = 0;

        /**
         * array containing vertices in the shortest path
         */
        int shortest_path[V] = {-1};
        int node_index = 0;
      
        /**
         * this table will hold the weight
         */
        int weightTable[V][V];
        for (int r = 0; r < V; r++) 
        {
            for (x = 0; x < V; x++) 
            {
                weightTable[r][x] = INF;
            }
        }
        weightTable[wtTableR++][src] = 0;

        /**
         * vertices that are marked
         */
        int markedVertices[V] = {-1};
        markedVertices[markedVerticesIdx++] = src;
        currVertex = src;

        /**
         * find shortest path
         */
        while(currVertex != dest) 
        {
            /**
             * copy marked values to the next row of weightTable
             */
            for (int i = 0; i < markedVerticesIdx; i++) 
            {
                x = markedVertices[i];
                weightTable[wtTableR][x] = weightTable[wtTableR - 1][x];
            }

            /**
             * find the weight from the current vertex to all the other
             * vertices that are directly connected and not yet marked
             */
            for (x = 0; x < V; x++) 
            {
                if (x != currVertex && !isMarked(x, markedVertices, markedVerticesIdx)) 
                {
                    edgeWt = graph[currVertex][x];
                    destValue = weightTable[wtTableR - 1][x];
                    markedValue = weightTable[wtTableR][currVertex];

                    min = find_min(destValue, markedValue + edgeWt);

                    weightTable[wtTableR][x] = min;
                }
            }

            /**
             * find minimum unmarked vertices in current row
             */
            min = INF;
            for (x = 0; x < V; x++) 
            {
                if (!isMarked(x, markedVertices, markedVerticesIdx)) 
                {
                    if (weightTable[wtTableR][x] < min) 
                    {
                        min = weightTable[wtTableR][x];
                        tmpX = x;
                    }
                }
            }

            /**
             * found a new vertex for marking
             */
            markedVertices[markedVerticesIdx++] = tmpX;
            currVertex = tmpX;

            /**
             * variables update
             */
            wtTableR++;
        }
        
        /**
        * compute shortest path vertices
        */
        x = dest;
        shortest_path[node_index++] = x;
        markedValue = weightTable[wtTableR - 1][dest];
        for (int r = wtTableR - 2; r >= 0; r--) 
        {
            if (weightTable[r][x] != markedValue) 
            {
                x = markedVertices[r];
                markedValue = weightTable[r][x];
                shortest_path[node_index++] = x;
            }
        }   

        /**
         * display the weight and shortest path
         */
        printf("node index: %i\n", node_index);
        printf("Shortest Path between %d and %d\n", src, dest);
        for (int i = node_index - 1; i >= 0; i--) 
        {
            printf("%d", shortest_path[i]);
            
            return_waypoints[i] = shortest_path[i];
            if (i > 0) 
            {
                printf(" --> ");
            }
        }
        reverseArray(return_waypoints, 0, node_index -1);
       
        for(int i = node_index; i < array_size; i++)
        {
            return_waypoints[i] = dest;
        }

        printf("\n");
        printf("Weight of the path: %d\n", weightTable[wtTableR - 1][dest]);
    }
    // return -1;
}

void reverseArray(int arr[], int start, int end)
{
    while(start < end)
    {
        int temp = arr[start]; 
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// void main(){
//     gps_t shortest_route[10];
//     // Generate weight of each edge

//     gps_t cur_location, dest;
//     int cur_closest_node, dest_closest_node;
//     // cur_location = get_location();
//     dest_closest_node = get_closest_node(dest.latitude, dest.longitude);
//     cur_closest_node = get_closest_node(cur_location.latitude, cur_location.longitude);

//     // shortest_path = djkistra(array[V][V], cur_closest_node, dest_closest_node);
//     // create full path: cur_closest_node + shortest_path + dest_closest_node
//     // pass all nodes to localaize controller -> RETURN shortest_route[10]

// }

// 1. Get current location: latitude and longitude 
// 2. Get destination     : latitude and longitude 

// 3. Iterate through the array and find the shortest path between two coordinates: 
//     - If true: store difference in variable and store index in variable. Then, iterate to the next index
//     - if false: iterate to the next index
// 4. 