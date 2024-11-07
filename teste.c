#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void mergeSort(int arr[], int esq, int dir);
void quickSort(int arr[], int baixo, int alto);
void heapSort(int arr[], int n);
void calculaTempo(clock_t inicio, clock_t fim);
void randomizaArray(int arr[], int n);
void merge(int arr[], int esq, int meio, int dir);
int partition(int arr[], int low, int high);
void heapify(int arr[], int n, int i);

int main() {
    clock_t inicio, fim;
    int metodo, tamanho;

    printf("Digite o tamanho do array:\n");
    scanf("%d", &tamanho);

    int arr[tamanho];
    randomizaArray(arr, tamanho);

    printf("Digite o metodo de ordenacao desejado:\n");
    printf("1 - Selection Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Bubble Sort\n");
    printf("4 - Merge Sort\n");
    printf("5 - Quick Sort\n");
    printf("6 - Heap Sort\n");
    scanf("%d", &metodo);

    if (metodo < 1 || metodo > 6) {
        printf("Metodo invalido!\n");
        return 1;
    }

    int arr2[tamanho];
    for (int i = 0; i < tamanho; i++) {
        arr2[i] = arr[i];
    }

    inicio = clock();

    if (metodo == 1) {
        selectionSort(arr2, tamanho);
        printf("Tempo de execução do selectionSort:\n");
    } else if (metodo == 2) {
        insertionSort(arr2, tamanho);
        printf("Tempo de execução do insertionSort:\n");
    } else if (metodo == 3) {
        bubbleSort(arr2, tamanho);
        printf("Tempo de execução do bubbleSort:\n");
    } else if (metodo == 4) {
        mergeSort(arr2, 0, tamanho - 1);
        printf("Tempo de execução do mergeSort:\n");
    } else if (metodo == 5) {
        quickSort(arr2, 0, tamanho - 1);
        printf("Tempo de execução do quickSort:\n");
    } else if (metodo == 6) {
        heapSort(arr2, tamanho);
        printf("Tempo de execução do heapSort:\n");
    }

    fim = clock();
    calculaTempo(inicio, fim);

    return 0;
}

void randomizaArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n) {
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

void merge(int arr[], int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[esq + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;

        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);

        merge(arr, esq, meio, dir);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void calculaTempo(clock_t inicio, clock_t fim) {
    double tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("%f segundos\n", tempo_cpu);
}
