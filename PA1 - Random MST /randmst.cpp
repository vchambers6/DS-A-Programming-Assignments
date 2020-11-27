#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <random>
#include <time.h>
#include <limits>
#include <stdio.h>
#include <string.h>
#include<ctime>
using namespace std; 

struct Point{
	float x, y, z, a; 
	bool visited; 
	float weight; 
}; 

float distance(float x1, float y1, float z1, float a1, float x2, float y2, float z2, float a2){
	return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) + pow(z2 - z1, 2) + pow(a2 - a1, 2)* 1.0); 
}

float prim(int n, int d) { 
	// Array of vertices  
	struct Point arr[n]; 
	
	// Initializes array
	for(int i = 0; i < n; i++) {
		arr[i].visited = false; 
		// Weight initialized to overestimate of max edge length 
		arr[i]. weight = 50.0;
		arr[i].x = 0.0;
		arr[i].y = 0.0; 
		arr[i].z = 0.0; 
		arr[i].a = 0.0; 
		// Initializes coordinates for higher dimensions 
		if (d >= 2) {
			arr[i].x = (float)rand() / RAND_MAX;
			arr[i].y = (float)rand() / RAND_MAX;
			if (d >= 3) {
				arr[i].z = (float)rand() / RAND_MAX;
				if (d == 4) {
					arr[i].a = (float)rand() / RAND_MAX;
				}
			}
		}
		
	}

	int edges; 
	float total;  
	// Smallest initialized to overestimated bound
	float smallest = 20.0; 
	// Saves and updates index of smallest node 
	int smallest_index;
	// "Node in question" -- node being explored -- starts at 0th node
	int niq = 0; 
	float dist; 
	while (edges < n) {
		arr[niq].visited = true; 
		for(int i = 0; i < n ; i ++){
			// Checks if vertex has been visited
			if (arr[i].visited == false) {
				if (d == 0) {
					// Edge weight calculated for 0 dimension
					dist = (float)rand() / RAND_MAX; 
				}
				else {
					// Edge weight calculated for higher dimensions
					dist = distance(arr[i].x, arr[i].y, arr[i].z, arr[i].a, 
					arr[niq].x, arr[niq].y, arr[niq].z, arr[niq].a); 
				}
				// Updates edge weight to minimum distance
				if (dist < arr[i].weight)
					arr[i].weight = dist; 
				else 
					dist = arr[i].weight; 
				// Finds smallest edge from node in question
				if (dist < smallest || smallest == 20.0) {
					smallest = dist;
					smallest_index = i; 
				}  		
			} 
		} 
		niq = smallest_index; 		 
		edges++; 
		// Add smallest edge to MST 
		if (smallest != 20.0) {
			total = total + smallest;
			smallest = 20.0; 
		}		
	}
	//cout << "time spent: " << end_time - start_time << "\n" << "total " << total << "\n";
	cout << "WEIGHT MST: " << total << "\n"; 
	return total; 
} 



int main(int argc, char *argv[]) {
	srand(time(NULL));

	int n, t, d; 
	
    n = atoi(argv[2]);
    t = atoi(argv[3]);
    d = atoi(argv[4]); 

    float sum; 
    
    std::time_t start_time = std::time(0); 
    for (int p = 0; p < t; p++){
    	float * a = (float *) malloc(sizeof(float));
    	*a = prim(n ,d); 
    	sum = sum + *a; 
    	free(a); 
    }
    std::time_t end_time = std::time(0);

    float time = (float) (end_time - start_time) / 5.0; 
    
    cout << "AVG WEIGHT: " << sum/5.0 << "\n" << "AVG TIME: " << time << "\n"; 
    
	return 0; 
}