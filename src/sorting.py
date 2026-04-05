"""
===================================================================
  IMPLEMENTASI ALGORITMA SORTING - PYTHON
  Algoritma: 1. Bubble Sort, 2. Selection Sort, 3. Insertion Sort,
             4. Quick Sort, 5. Merge Sort
===================================================================
"""

import copy

DIVIDER = "=" * 60
THIN    = "-" * 60


def print_array(arr, highlight=None, label=""):
    """Cetak array dengan highlight indeks tertentu."""
    result = []
    for i, val in enumerate(arr):
        if highlight and i in highlight:
            result.append(f"[{val}]")
        else:
            result.append(f" {val} ")
    line = "  ".join(result)
    if label:
        print(f"  {label:<25} {line}")
    else:
        print(f"  {line}")


#===================
# 1. BUBBLE SORT ||
#===================

def bubble_sort(arr):
    print(f"\n{DIVIDER}")
    print("  BUBBLE SORT")
    print(DIVIDER)
    a = arr[:]
    n = len(a)
    iteration = 0

    print(f"  Data Awal  : {a}")
    print(THIN)

    for i in range(n - 1):
        swapped = False
        for j in range(n - 1 - i):
            iteration += 1
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                swapped = True
            print(f"  Pass {i+1}, Step {j+1} (iterasi {iteration:>3}): {a}  "
                  f"← bandingkan indeks {j} & {j+1}")
        if not swapped:
            print(f"  [Tidak ada pertukaran pada pass {i+1}, berhenti lebih awal]")
            break
        print(f"  Setelah Pass {i+1}     : {a}")
        print()

    print(THIN)
    print(f"  Total iterasi : {iteration}")
    print(f"  Hasil Sorting : {a}")
    return a

#=====================
# 2. SELECTION SORT ||
#=====================

def selection_sort(arr):
    print(f"\n{DIVIDER}")
    print("  SELECTION SORT")
    print(DIVIDER)
    a = arr[:]
    n = len(a)
    iteration = 0

    print(f"  Data Awal  : {a}")
    print(THIN)

    for i in range(n - 1):
        min_idx = i
        for j in range(i + 1, n):
            iteration += 1
            if a[j] < a[min_idx]:
                min_idx = j
            print(f"  Pass {i+1}, Step {j-i:>2} (iterasi {iteration:>3}): "
                  f"bandingkan indeks {i}({a[i]}) dengan {j}({a[j]})  "
                  f"→ min sementara = a[{min_idx}]={a[min_idx]}")

        if min_idx != i:
            a[i], a[min_idx] = a[min_idx], a[i]
            print(f"  Tukar a[{i}]={a[i]} ↔ a[{min_idx}]={a[min_idx]}")
        else:
            print(f"  Tidak ada pertukaran (a[{i}]={a[i]} sudah minimum)")
        print(f"  Setelah Pass {i+1}     : {a}")
        print()

    print(THIN)
    print(f"  Total iterasi : {iteration}")
    print(f"  Hasil Sorting : {a}")
    return a

#=====================
# 3. INSERTION SORT ||
#=====================

def insertion_sort(arr):
    print(f"\n{DIVIDER}")
    print("  INSERTION SORT")
    print(DIVIDER)
    a = arr[:]
    n = len(a)
    iteration = 0

    print(f"  Data Awal  : {a}")
    print(THIN)

    for i in range(1, n):
        key = a[i]
        j = i - 1
        print(f"  Pass {i}: ambil kunci = {key}")
        while j >= 0 and a[j] > key:
            iteration += 1
            a[j + 1] = a[j]
            print(f"    iterasi {iteration:>3}: geser a[{j}]={a[j+1]} ke kanan → {a}")
            j -= 1
        iteration += 1
        a[j + 1] = key
        print(f"    iterasi {iteration:>3}: sisipkan {key} di posisi {j+1}  → {a}")
        print()

    print(THIN)
    print(f"  Total iterasi : {iteration}")
    print(f"  Hasil Sorting : {a}")
    return a

#=================
# 4. QUICK SORT ||
#=================

_qs_iter = [0]

def _partition(a, low, high, depth):
    pivot = a[high]
    i = low - 1
    print(f"  {'  ' * depth}Pivot = {pivot}  subarray = {a[low:high+1]}")
    for j in range(low, high):
        _qs_iter[0] += 1
        if a[j] <= pivot:
            i += 1
            a[i], a[j] = a[j], a[i]
            print(f"  {'  ' * depth}  iterasi {_qs_iter[0]:>3}: a[{i}]↔a[{j}]  → {a[low:high+1]}")
        else:
            print(f"  {'  ' * depth}  iterasi {_qs_iter[0]:>3}: lewati a[{j}]={a[j]} (> pivot {pivot})")
        _qs_iter[0] += 1
    a[i + 1], a[high] = a[high], a[i + 1]
    print(f"  {'  ' * depth}  Letakkan pivot {pivot} di posisi {i+1}  → {a[low:high+1]}")
    return i + 1

def _quick_sort(a, low, high, depth=0):
    if low < high:
        pi = _partition(a, low, high, depth)
        print(f"  {'  ' * depth}Rekursif kiri  [{low}..{pi-1}]: {a[low:pi]}")
        _quick_sort(a, low, pi - 1, depth + 1)
        print(f"  {'  ' * depth}Rekursif kanan [{pi+1}..{high}]: {a[pi+1:high+1]}")
        _quick_sort(a, pi + 1, high, depth + 1)

def quick_sort(arr):
    print(f"\n{DIVIDER}")
    print("  QUICK SORT")
    print(DIVIDER)
    a = arr[:]
    _qs_iter[0] = 0

    print(f"  Data Awal  : {a}")
    print(THIN)

    _quick_sort(a, 0, len(a) - 1)

    print(THIN)
    print(f"  Total iterasi : {_qs_iter[0]}")
    print(f"  Hasil Sorting : {a}")
    return a

#=================
# 5. MERGE SORT ||
#=================

_ms_iter = [0]

def _merge(a, left, mid, right, depth):
    L = a[left:mid + 1]
    R = a[mid + 1:right + 1]
    i = j = 0
    k = left
    print(f"  {'  ' * depth}Gabung: {L} + {R}")
    while i < len(L) and j < len(R):
        _ms_iter[0] += 1
        if L[i] <= R[j]:
            a[k] = L[i]; i += 1
        else:
            a[k] = R[j]; j += 1
        k += 1
    while i < len(L):
        a[k] = L[i]; i += 1; k += 1
    while j < len(R):
        a[k] = R[j]; j += 1; k += 1
    print(f"  {'  ' * depth}Hasil : {a[left:right+1]}")

def _merge_sort(a, left, right, depth=0):
    if left < right:
        mid = (left + right) // 2
        print(f"  {'  ' * depth}Bagi [{left}..{right}] → [{left}..{mid}] | [{mid+1}..{right}]")
        _ms_sort_left  = a[left:mid + 1]
        _ms_sort_right = a[mid + 1:right + 1]
        _merge_sort(a, left, mid, depth + 1)
        _merge_sort(a, mid + 1, right, depth + 1)
        _merge(a, left, mid, right, depth)

def merge_sort(arr):
    print(f"\n{DIVIDER}")
    print("  MERGE SORT")
    print(DIVIDER)
    a = arr[:]
    _ms_iter[0] = 0

    print(f"  Data Awal  : {a}")
    print(THIN)

    _merge_sort(a, 0, len(a) - 1)

    print(THIN)
    print(f"  Total iterasi : {_ms_iter[0]}")
    print(f"  Hasil Sorting : {a}")
    return a

#========
# MAIN ||
#========

def main():
    print(DIVIDER)
    print("  PROGRAM SORTING ALGORITHM - PYTHON")
    print(DIVIDER)

    n = int(input("\n  Masukkan jumlah data : "))
    print(f"  Masukkan {n} data (pisahkan dengan spasi) : ", end="")
    data = list(map(int, input().split()))

    if len(data) != n:
        print(f"  [PERINGATAN] Anda memasukkan {len(data)} data, bukan {n}.")
        data = data[:n]

    print(f"\n  Data yang akan di-sort : {data}")

    print(f"\n{DIVIDER}")
    print("  Pilih Algoritma Sorting:")
    print("  1. Bubble Sort")
    print("  2. Selection Sort")
    print("  3. Insertion Sort")
    print("  4. Quick Sort")
    print("  5. Merge Sort")
    print("  6. Semua Algoritma")
    print(DIVIDER)

    pilihan = input("  Masukkan pilihan (1-6) : ").strip()

    algo_map = {
        "1": bubble_sort,
        "2": selection_sort,
        "3": insertion_sort,
        "4": quick_sort,
        "5": merge_sort,
    }

    if pilihan == "6":
        for fn in algo_map.values():
            fn(data)
    elif pilihan in algo_map:
        algo_map[pilihan](data)
    else:
        print("  Pilihan tidak valid.")

    print(f"\n{DIVIDER}")
    print("  Program selesai.")
    print(DIVIDER)


if __name__ == "__main__":
    main()
