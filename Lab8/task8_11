#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int value;
} Item;

int compare_items(const void *a, const void *b) {
    const Item *ia = (const Item *)a;
    const Item *ib = (const Item *)b;
    return ia->value - ib->value;
}

void quicksort(Item *arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[right].value;
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j].value <= pivot) {
            i++;
            Item temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Item temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;

    quicksort(arr, left, i);
    quicksort(arr, i + 2, right);
}

void print_array(const char *label, Item *arr, int n) {
    printf("%s:\n", label);
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Value: %d\n", arr[i].id, arr[i].value);
    }
    printf("\n");
}

int main() {
    Item original[] = {
        {1, 5},
        {2, 3},
        {3, 5},
        {4, 3},
        {5, 2},
        {6, 5}
    };
    int n = sizeof(original) / sizeof(original[0]);

    // Копії масивів
    Item system_sorted[n], custom_sorted[n];
    memcpy(system_sorted, original, sizeof(original));
    memcpy(custom_sorted, original, sizeof(original));

    // Системне qsort (може бути нестабільним)
    qsort(system_sorted, n, sizeof(Item), compare_items);

    // Власний нестабільний quicksort
    quicksort(custom_sorted, 0, n - 1);

    // Вивід
    print_array("Original", original, n);
    print_array("System qsort", system_sorted, n);
    print_array("Custom quicksort", custom_sorted, n);

    return 0;
}
