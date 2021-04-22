#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Node {
    struct Node *next;
    int CLASS_ID;
    double *points;
} Node;

typedef struct Neighbor {
    struct Neighbor *next;
    int CLASS_ID;
    double distance;
    double *points;
} Neighbor;

void add_node (double *points, int CLASS_ID, Node **head) {
    Node* newNode = malloc(sizeof(struct Node));
    newNode->CLASS_ID = CLASS_ID;
    newNode->points = points;
    newNode->next = *head;
    *head = newNode;
}

void print_node_list(Node *head, int size) {
    Node *ptr = head;
    int k = 1;
    while (ptr != NULL) {
        printf("\n---------------\n");
        printf("\nNode %d:\n\n", k);
        for(int i = 0; i < size; i++){
            printf("Point %d: %f\n", i + 1, ptr->points[i]);
        }
        printf("Class: %d\n", ptr->CLASS_ID);
        k++;
        ptr = ptr->next;
    }
}

void add_neighbor (double *points, int CLASS_ID, double distance, Neighbor **head){
    Neighbor *new_neighbor = malloc(sizeof(Neighbor));
    new_neighbor->CLASS_ID = CLASS_ID;
    new_neighbor->points = points;
    new_neighbor->distance = distance;
    new_neighbor->next = *head;
    *head = new_neighbor;
}

void print_neighbors(Neighbor *head){
    Neighbor *ptr = head;
    while (ptr != NULL) {
        printf("\n---------------\n");
        printf("Distance: %f\n", ptr->distance);
        printf("Class: %d\n", ptr->CLASS_ID);
        ptr = ptr->next;
    }
}

void free_neighbors(Neighbor **head){
    Neighbor *current = *head;
    while(current != NULL){
        Neighbor *next_neighbor = current->next;
        free(current);
        current = next_neighbor;
    }
}

// Insertion sort for neighbors linked list
void sort_neighbors(Neighbor **head){
    Neighbor *sorted_neighbors = NULL;
    Neighbor *current_neighbor = *head; 

    while(current_neighbor != NULL){
		Neighbor *next_neighbor = current_neighbor->next;
		
		Neighbor *neighbor_being_inserted = NULL;

		if(sorted_neighbors == NULL || sorted_neighbors->distance >= current_neighbor->distance){
		    current_neighbor->next = sorted_neighbors;
		    sorted_neighbors = current_neighbor;
		} else {
			neighbor_being_inserted = sorted_neighbors;
			while(neighbor_being_inserted->next != NULL && neighbor_being_inserted->next->distance < current_neighbor->distance){
				neighbor_being_inserted = neighbor_being_inserted->next;
			}
			current_neighbor->next = neighbor_being_inserted->next;
			neighbor_being_inserted->next = current_neighbor;
		}

		current_neighbor = next_neighbor;
	}

	*head = sorted_neighbors;
}

// Calculate euclidian distance between two vectors
double calculate_distance(double* vector_one, double* vector_two, int vectorSize){
    double distance = 0;
    double sum = 0;

    for(int i = 0; i < vectorSize; i++){
        double difference  = vector_one[i] - vector_two[i];
        sum += pow(difference, 2);
    }
    distance = sqrt(sum);
    return distance;
}

Neighbor *get_neighbors(double *point_to_be_mapped, int vector_size, Node *head) {
    Node *current_node = head;
    Neighbor *neighbors_list = NULL;

    while(current_node != NULL){
        double distance = calculate_distance(point_to_be_mapped, current_node->points, vector_size);
        add_neighbor(current_node->points, current_node->CLASS_ID, distance, &neighbors_list);
        current_node = current_node->next;
    }

    return neighbors_list;
}

Neighbor *get_k_nearest_neighbors(int k, Neighbor *head){
    int counter = 0;

    Neighbor *k_neighbors = NULL;
    Neighbor *current = head;

    while(counter < k && current != NULL){
        Neighbor *new_neighbor = malloc(sizeof(Neighbor));

        new_neighbor->CLASS_ID = current->CLASS_ID;
        new_neighbor->distance = current->distance;
        new_neighbor->points = current->points;

        new_neighbor->next = k_neighbors;
        k_neighbors = new_neighbor;

        counter++;
        current = current->next;
    }

    return k_neighbors;
}

void sort(double *arr, int n) {
    for (int i = 0; i < n; i++) {
        double smallest = arr[i];
        for (int j = i+1 ; j < n; j++) {
            if (arr[j] < smallest) {
                smallest = arr[j];
                arr[j] = arr[i];
                arr[i] = smallest;
            }
        }
    }
}

int KNN(struct Node* head, int k, int size, double* points) {
    Neighbor *neighbors = get_neighbors(points, size, head);
    sort_neighbors(&neighbors);
    Neighbor *kNeighbors = get_k_nearest_neighbors(k, neighbors);

    double ids[k];

    for (int i = 0; i < k; i++) {
        ids[i] = 0;
    }

    Neighbor *ptr = kNeighbors;
    int i = 0;
    while (ptr != NULL) {
        ids[i] = ptr->CLASS_ID;
        i++;
        ptr = ptr->next;
    }

    sort(ids, k);

    int CLASS_ID = ids[0];
    int largest_occ = 0;
    
    for (int i = 1; i < k; i++) {
        int occ = 1;
        while (ids[i] == ids[i-1] && i < k) {
            occ++;
            i++;
        }
        if (occ > largest_occ) {
            largest_occ = occ;
            CLASS_ID = ids[i-1];
        }
    }

    free_neighbors(&neighbors);
    free_neighbors(&kNeighbors);
    return CLASS_ID;
}