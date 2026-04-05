/*
===================================================================
  IMPLEMENTASI ALGORITMA SORTING - C++
  Algoritma: 1. Bubble Sort, 2. Selection Sort, 3. Insertion Sort,
             4. Quick Sort, 5. Merge Sort
===================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

 /* ─── UTILITY ─── */

const string DIVIDER(60, '=');
const string THIN(60, '-');

void printArray(const vector<int>& arr, const string& label = "") {
    if (!label.empty())
        cout << "  " << left << setw(25) << label;
    else
        cout << "  ";
    cout << "[ ";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

void printArrayRange(const vector<int>& arr, int lo, int hi) {
    cout << "[ ";
    for (int i = lo; i <= hi; i++) {
        cout << arr[i];
        if (i < hi) cout << ", ";
    }
    cout << " ]";
}

 /* ─── 1. BUBBLE SORT ─── */

vector<int> bubbleSort(vector<int> arr) {
    cout << "\n" << DIVIDER << "\n";
    cout << "  BUBBLE SORT\n";
    cout << DIVIDER << "\n";

    int n = arr.size();
    int iteration = 0;

    printArray(arr, "Data Awal :");
    cout << THIN << "\n";

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            iteration++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
            cout << "  Pass " << i+1 << ", Step " << j+1
                 << " (iterasi " << setw(3) << iteration << "): ";
            printArrayRange(arr, 0, n-1);
            cout << "  <- bandingkan indeks " << j << " & " << j+1 << "\n";
        }
        if (!swapped) {
            cout << "  [Tidak ada pertukaran pada pass " << i+1
                 << ", berhenti lebih awal]\n";
            break;
        }
        cout << "  Setelah Pass " << i+1 << "    : ";
        printArrayRange(arr, 0, n-1);
        cout << "\n\n";
    }

    cout << THIN << "\n";
    cout << "  Total iterasi : " << iteration << "\n";
    printArray(arr, "Hasil Sorting :");
    return arr;
}

 /* ─── 2. SELECTION SORT ─── */

vector<int> selectionSort(vector<int> arr) {
    cout << "\n" << DIVIDER << "\n";
    cout << "  SELECTION SORT\n";
    cout << DIVIDER << "\n";

    int n = arr.size();
    int iteration = 0;

    printArray(arr, "Data Awal :");
    cout << THIN << "\n";

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            iteration++;
            if (arr[j] < arr[minIdx]) minIdx = j;
            cout << "  Pass " << i+1 << ", Step " << setw(2) << j-i
                 << " (iterasi " << setw(3) << iteration << "): "
                 << "bandingkan indeks " << i << "(" << arr[i] << ") dengan "
                 << j << "(" << arr[j] << ")  -> min sementara = a["
                 << minIdx << "]=" << arr[minIdx] << "\n";
        }
        if (minIdx != i) {
            cout << "  Tukar a[" << i << "]=" << arr[minIdx]
                 << " <-> a[" << minIdx << "]=" << arr[i] << "\n";
            swap(arr[i], arr[minIdx]);
        } else {
            cout << "  Tidak ada pertukaran (a[" << i << "]="
                 << arr[i] << " sudah minimum)\n";
        }
        cout << "  Setelah Pass " << i+1 << "    : ";
        printArrayRange(arr, 0, n-1);
        cout << "\n\n";
    }

    cout << THIN << "\n";
    cout << "  Total iterasi : " << iteration << "\n";
    printArray(arr, "Hasil Sorting :");
    return arr;
}

 /* ─── 3. INSERTION SORT ─── */

vector<int> insertionSort(vector<int> arr) {
    cout << "\n" << DIVIDER << "\n";
    cout << "  INSERTION SORT\n";
    cout << DIVIDER << "\n";

    int n = arr.size();
    int iteration = 0;

    printArray(arr, "Data Awal :");
    cout << THIN << "\n";

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        cout << "  Pass " << i << ": ambil kunci = " << key << "\n";
        while (j >= 0 && arr[j] > key) {
            iteration++;
            arr[j + 1] = arr[j];
            cout << "    iterasi " << setw(3) << iteration
                 << ": geser a[" << j << "]=" << arr[j+1] << " ke kanan -> ";
            printArrayRange(arr, 0, n-1);
            cout << "\n";
            j--;
        }
        iteration++;
        arr[j + 1] = key;
        cout << "    iterasi " << setw(3) << iteration
             << ": sisipkan " << key << " di posisi " << j+1 << "  -> ";
        printArrayRange(arr, 0, n-1);
        cout << "\n\n";
    }

    cout << THIN << "\n";
    cout << "  Total iterasi : " << iteration << "\n";
    printArray(arr, "Hasil Sorting :");
    return arr;
}

 /* ─── 4. QUICK SORT ─── */

int qs_iter = 0;

int partitionQS(vector<int>& arr, int low, int high, int depth) {
    int pivot = arr[high];
    int i = low - 1;
    string indent(depth * 2, ' ');
    cout << "  " << indent << "Pivot = " << pivot << "  subarray = ";
    printArrayRange(arr, low, high);
    cout << "\n";

    for (int j = low; j < high; j++) {
        qs_iter++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            cout << "  " << indent << "  iterasi " << setw(3) << qs_iter
                 << ": a[" << i << "] <-> a[" << j << "]  -> ";
            printArrayRange(arr, low, high);
            cout << "\n";
        } else {
            cout << "  " << indent << "  iterasi " << setw(3) << qs_iter
                 << ": lewati a[" << j << "]=" << arr[j]
                 << " (> pivot " << pivot << ")\n";
        }
        qs_iter++;
    }
    swap(arr[i + 1], arr[high]);
    cout << "  " << indent << "  Letakkan pivot " << pivot
         << " di posisi " << i+1 << "  -> ";
    printArrayRange(arr, low, high);
    cout << "\n";
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high, int depth = 0) {
    if (low < high) {
        string indent(depth * 2, ' ');
        int pi = partitionQS(arr, low, high, depth);
        cout << "  " << indent << "Rekursif kiri  [" << low << ".." << pi-1 << "]: ";
        printArrayRange(arr, low, pi-1);
        cout << "\n";
        quickSortHelper(arr, low, pi - 1, depth + 1);
        cout << "  " << indent << "Rekursif kanan [" << pi+1 << ".." << high << "]: ";
        printArrayRange(arr, pi+1, high);
        cout << "\n";
        quickSortHelper(arr, pi + 1, high, depth + 1);
    }
}

vector<int> quickSort(vector<int> arr) {
    cout << "\n" << DIVIDER << "\n";
    cout << "  QUICK SORT\n";
    cout << DIVIDER << "\n";
    qs_iter = 0;

    printArray(arr, "Data Awal :");
    cout << THIN << "\n";

    quickSortHelper(arr, 0, arr.size() - 1);

    cout << THIN << "\n";
    cout << "  Total iterasi : " << qs_iter << "\n";
    printArray(arr, "Hasil Sorting :");
    return arr;
}

/* ─── 5. MERGE SORT ─── */

int ms_iter = 0;

void mergeArrays(vector<int>& arr, int left, int mid, int right, int depth) {
    string indent(depth * 2, ' ');
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    cout << "  " << indent << "Gabung: [ ";
    for (size_t i = 0; i < L.size(); i++) { cout << L[i]; if (i < L.size()-1) cout << ", "; }
    cout << " ] + [ ";
    for (size_t i = 0; i < R.size(); i++) { cout << R[i]; if (i < R.size()-1) cout << ", "; }
    cout << " ]\n";

    int i = 0, j = 0, k = left;
    while (i < (int)L.size() && j < (int)R.size()) {
        ms_iter++;
        if (L[i] <= R[j]) { arr[k++] = L[i++]; }
        else               { arr[k++] = R[j++]; }
    }
    while (i < (int)L.size()) arr[k++] = L[i++];
    while (j < (int)R.size()) arr[k++] = R[j++];

    cout << "  " << indent << "Hasil : ";
    printArrayRange(arr, left, right);
    cout << "\n";
}

void mergeSortHelper(vector<int>& arr, int left, int right, int depth = 0) {
    if (left < right) {
        string indent(depth * 2, ' ');
        int mid = (left + right) / 2;
        cout << "  " << indent << "Bagi [" << left << ".." << right
             << "] -> [" << left << ".." << mid
             << "] | [" << mid+1 << ".." << right << "]\n";
        mergeSortHelper(arr, left, mid, depth + 1);
        mergeSortHelper(arr, mid + 1, right, depth + 1);
        mergeArrays(arr, left, mid, right, depth);
    }
}

vector<int> mergeSort(vector<int> arr) {
    cout << "\n" << DIVIDER << "\n";
    cout << "  MERGE SORT\n";
    cout << DIVIDER << "\n";
    ms_iter = 0;

    printArray(arr, "Data Awal :");
    cout << THIN << "\n";

    mergeSortHelper(arr, 0, arr.size() - 1);

    cout << THIN << "\n";
    cout << "  Total iterasi : " << ms_iter << "\n";
    printArray(arr, "Hasil Sorting :");
    return arr;
}

/* ─── MAIN ─── */

int main() {
    cout << DIVIDER << "\n";
    cout << "  PROGRAM SORTING ALGORITHM - C++\n";
    cout << DIVIDER << "\n";

    int n;
    cout << "\n  Masukkan jumlah data : ";
    cin >> n;

    vector<int> data(n);
    cout << "  Masukkan " << n << " data : ";
    for (int i = 0; i < n; i++) cin >> data[i];

    cout << "\n  Data yang akan di-sort : ";
    printArrayRange(data, 0, n-1);
    cout << "\n";

    cout << "\n" << DIVIDER << "\n";
    cout << "  Pilih Algoritma Sorting:\n";
    cout << "  1. Bubble Sort\n";
    cout << "  2. Selection Sort\n";
    cout << "  3. Insertion Sort\n";
    cout << "  4. Quick Sort\n";
    cout << "  5. Merge Sort\n";
    cout << "  6. Semua Algoritma\n";
    cout << DIVIDER << "\n";
    cout << "  Masukkan pilihan (1-6) : ";

    int pilihan;
    cin >> pilihan;

    switch (pilihan) {
        case 1: bubbleSort(data);    break;
        case 2: selectionSort(data); break;
        case 3: insertionSort(data); break;
        case 4: quickSort(data);     break;
        case 5: mergeSort(data);     break;
        case 6:
            bubbleSort(data);
            selectionSort(data);
            insertionSort(data);
            quickSort(data);
            mergeSort(data);
            break;
        default:
            cout << "  Pilihan tidak valid.\n";
    }

    cout << "\n" << DIVIDER << "\n";
    cout << "  Program selesai.\n";
    cout << DIVIDER << "\n";

    return 0;
}
