#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 81

void read_csv(char* file_name, int adj[N][N]);
void nearest_insertion_algorithm(int adj[N][N], int starting_node, int tour[N+1]);
void matrixPrint(int matrix[][N], int rows, int cols);

int main() {
    int adj[N][N];
    int i;
    int starting_node = 5; // Because Ankara is the 6th city, it corresponds to index 5

    // Reads distances from the CSV converted from the second page of an Excel table
    read_csv("Distance.csv", adj);
    matrixPrint(adj, N, N);
    int tour[N+1];

    // Applies the nearest insertion algorithm
    nearest_insertion_algorithm(adj, starting_node, tour);

    int distance = 0;
    printf("Hamiltonian cycle starting from Ankara (06):\n");
    for (i = 0; i <= N; i++) {
        // Print the Hamiltonian cycle
        printf("%d ", tour[i]+1);
        if (i > 0) {
            // While printing the Hamiltonian cycle, also add the distance value between cities to the 'distance' variable
            distance += adj[tour[i-1]][tour[i]];
        }
    }
    // Print the distance
    printf("\nTotal distance traveled: %d\n", distance);

    return 0;
}

void read_csv(char* file_name, int adj[N][N]) {
    FILE *fp;
    char line[1024];
    char *token;
    int row, col;

    // File opening check
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("File cannot be opened\n");
        return;
    }

    // Skip the first line as it contains city names
    fgets(line, 1024, fp);
    printf(line);
    
    // Get values from the CSV file and fill the adjacency matrix
    for (row = 0; row < N; row++) {
        fgets(line, 1024, fp);

        // Skip the first 3 columns as they are not distance values
        // Use 3 strtok functions to skip each column.
        token = strtok(line, ";");
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");

        // Get the distance value, convert the string element from the CSV to an integer using atoi, and place it in the 'adj' matrix
        for (col = 0; col < N; col++) {
            token = strtok(NULL, ";");
            int value = atoi(token);
            adj[row][col] = value;
        }
    }

    // Close the file
    fclose(fp);
}

void nearest_insertion_algorithm(int adj[N][N], int starting_node, int tour[N+1]) {
    int visited[N] = {0};
    visited[starting_node] = 1;
    tour[0] = starting_node;
	int i, j, k;
    // Find the closest unvisited city to the current tour and add it to the tour
    for (i = 1; i <= N; i++) {
        int min_distance = 9999;
        int min_index = -1;

        // Check all cities
        for (j = 0; j < N; j++) {
            // If the city is visited, skip and continue with the loop
            if (visited[j]) continue;

            // Calculate the distance from the current tour's last city to city 'j' and from city 'j' to the starting city
            int distance = adj[tour[i-1]][j] + adj[j][starting_node];

            // If it's a shorter distance, update 'min_distance'
            if (distance < min_distance) {
                min_distance = distance;
                min_index = j;

                int next_node_index = i;
                // Find the best position for city 'j' in the current tour
                for (k = i; k > 0; k--) {
                    // Calculate the change in distance if city 'j' is inserted between positions k-1 and k in the tour
                    if (adj[tour[k-1]][j] + adj[j][tour[k]] - adj[tour[k-1]][tour[k]] < min_distance) {
                        min_distance = adj[tour[k-1]][j] + adj[j][tour[k]] - adj[tour[k-1]][tour[k]];
                        next_node_index = k;
                    }
                }

                // Insert city 'j' into the tour at the best position found
                tour[i] = j;
                
                // Shift all elements in the 'tour' array from position i to 'next_node_index' one place to the right
                for (k = i; k > next_node_index; k--) {
                    tour[k] = tour[k-1];
                }

                tour[next_node_index] = j;
            }
        }

        visited[min_index] = 1;
    }

    tour[N] = starting_node;
}

void matrixPrint(int matrix[][N], int rows, int cols) {
	int i,j;
    for ( i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
