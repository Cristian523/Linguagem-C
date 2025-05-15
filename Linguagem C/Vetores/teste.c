#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

int main() {
	tipo vetor[] = {5, 10, 2, 3, 12, 23, 11, 7, 1, 10, 0, 8, 18, 14, 10, 12, 1, -4, 15, 8, 7};
    //tipo vetor[] = {10, -5, 6, 2, 9, 17, -2, 19, -4, 2, 10, 13, 15, 7, 6};
    int n = 21;
    Vector array = vector_new_with_vet(vetor, n);
    //Vector array = vector_new_with_size(3);
    int elemento;
    vector_print(array);

    vector_sort(&array);
    
    /*
    scanf("%d", &elemento);
    while (elemento >= 0) {
        vector_insert_ordered(&array, elemento);
        scanf("%d", &elemento);
    }
    */

    vector_print(array);
    vector_free(&array);
    printf("\n");
}
