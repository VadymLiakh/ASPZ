#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 100000

int compare_ints(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int is_sorted(int arr[], size_t size) {
    for (size_t i = 1; i < size; i++) {
        if (arr[i-1] > arr[i]) return 0;
    }
    return 1;
}

void fill_random(int arr[], size_t size) {
    for (size_t i = 0; i < size; i++)
        arr[i] = rand() % 100000;
}

void fill_sorted(int arr[], size_t size) {
    for (size_t i = 0; i < size; i++)
        arr[i] = i;
}

void fill_reverse(int arr[], size_t size) {
    for (size_t i = 0; i < size; i++)
        arr[i] = size - i;
}

void fill_duplicates(int arr[], size_t size) {
    for (size_t i = 0; i < size; i++)
        arr[i] = 42;  // Одне і те саме число
}

void test_case(const char *label, void (*fill)(int*, size_t)) {
    int *arr = malloc(SIZE * sizeof(int));
    if (!arr) {
        perror("malloc");
        exit(1);
    }

    fill(arr, SIZE);

    clock_t start = clock();
    qsort(arr, SIZE, sizeof(int), compare_ints);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%-20s: %6.3f сек. — %s\n", label, time_taken,
           is_sorted(arr, SIZE) ? "OK" : "NOT SORTED");

    free(arr);
}

int main() {
    srand((unsigned)time(NULL));

    printf("Тестуємо qsort на різних типах вхідних даних:\n\n");

    test_case("Випадкові числа", fill_random);
    test_case("Вже відсортований", fill_sorted);
    test_case("Зворотній порядок", fill_reverse);
    test_case("Багато дублікатів", fill_duplicates);

    return 0;
}
