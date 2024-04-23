#include <stdio.h>
#include <omp.h>

void parallelOddEvenSort(int arr[], int n) {
    int phase, i, temp;
    for (phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
            // Even phase
            #pragma omp parallel for private(i, temp) shared(arr)
            for (i = 1; i < n; i += 2) {
                if (arr[i - 1] > arr[i]) {
                    temp = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = temp;
                }
            }
        } else {
            // Odd phase
            #pragma omp parallel for private(i, temp) shared(arr)
            for (i = 1; i < n - 1; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Unsorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Parallel version using odd-even transposition sort
    double start_time = omp_get_wtime(); // Start timing
    parallelOddEvenSort(arr, n);
    double end_time = omp_get_wtime(); // End timing
    printf("Sorted array (parallel odd-even): \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Time taken (parallel odd-even): %f seconds\n", end_time - start_time);

    return 0;
}

