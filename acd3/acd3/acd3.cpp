#include <iostream>
#include <cmath>
using namespace std;
class Sorter {//абстрактний клас
public:
    virtual void sort(double* arr, int size) = 0;
};

class MergeSorter : public Sorter {
public:
    void sort(double* arr, int size) {
        mergeSort(arr, 0, size - 1);
    }
private:
    void mergeSort(double* arr, int left, int right) {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
    void merge(double* arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        double* L = new double[n1];
        double* R = new double[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] >= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
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

        delete[] L;
        delete[] R;
    }
};

void printArray(double* arr, int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    double n;
    cout << "Введіть кількість елементів прогресії: ";
    cin >> n;
    if (n <= 10 || n >= 1000) {
        cout << "Некоректне значення N" << endl;
        return 1;
    }
    double* A = new double[n];
    cout << "Введіть перший елемент прогресії: ";
    cin >> A[0];
    cout << "Введіть знаменник прогресії: ";
    double r;
    cin >> r;
    for (int i = 1; i < n; i++) {
        A[i] = A[i - 1] * r;
    }
    cout << "Елементи прогресії: ";
    printArray(A, n);
    cout << "" << endl;
    // екземпляр конкретного сортувальника
    MergeSorter mergeSorter;

    mergeSorter.sort(A, n);

    cout << "Відсортовані елементи прогресії: ";
    printArray(A, n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }

    cout << "Сума прогресії: " << sum << endl;
    delete[] A;
    return 0;
}
