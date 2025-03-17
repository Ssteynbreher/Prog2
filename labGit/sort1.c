#include <stdio.h>

void sort(int arr[], int n) {
  // Простая сортировка
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main() {
  int a[] = {4, 2, 0, 5}; // Добавлено несколько чисел
  int n = sizeof(a) / sizeof(a[0]);
  sort(a, n);
  printf("Sorted array: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
  return 0;
}
