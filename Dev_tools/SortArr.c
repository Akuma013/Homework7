#include <stdio.h>
#include <stdlib.h>


void sortArray(int *arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);


    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    sortArray(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    
    //free(arr);

    return 0;
}
