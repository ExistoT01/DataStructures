#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

void BubbleSort(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void QuickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right, key = a[left];
    while (i < j)
    {
        while (i < j && key <= a[j])
            j--;
        a[i] = a[j];
        while (i < j && key >= a[i])
            i++;
        a[j] = a[i];
    }
    a[i] = key;
    QuickSort(a, left, i - 1);
    QuickSort(a, i + 1, right);
}

int main()
{
    int *arr = new int[100000];
    int *arr_cp = new int[100000];

    int n;
    cout << "enter the amount:" << endl;
    cin >> n;

    //get random numbers
    srand(unsigned(time));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
        arr_cp[i] = arr[i];
    }

    //set the clock
    clock_t start, end;
    start = clock();

    //bubble sort
    BubbleSort(arr, n);

    end = clock();

    cout << "running time: " << (double)(end - start) / CLOCKS_PER_SEC << "s [BubbleSort]" << endl;

    // cout << "result:" << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;

    //quick sort
    start = clock();
    QuickSort(arr_cp, 0, n - 1);

    end = clock();

    cout << "running time: " << (double)(end - start) / CLOCKS_PER_SEC << "s [QuickSort]" << endl;

    // cout << "result:" << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     cout << arr_cp[i] << " ";
    // }
    // cout << endl;

    delete arr;
    delete arr_cp;

    return 0;
}