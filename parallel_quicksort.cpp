#include<iostream>
#include<bits/stdc++.h>
#include<iomanip>
#include<omp.h>
using namespace std;

void quicksort(int arr[], int st, int end)
{
    if(st < end)
    {
        int pivot = arr[end];
        int i = st-1;
        int j = st;

        for(int var = j; var<end; var++)
        {
            if(arr[var] < pivot)
            {
                i++;
                int temp = arr[i];
                arr[i] = arr[var];
                arr[var] = temp;
            }
        }

        // swap i+1 and end
        int temp = arr[i+1];
        arr[i+1] = arr[end];
        arr[end] = temp;

        i++;

        #pragma omp parallel sections
        {
            #pragma omp section
            quicksort(arr,st,i-1);

            #pragma omp section
            quicksort(arr,i+1,end);
        }
    
    }

}

int main()
{
    int n;
    cout<<"Enter the number of elements: "; 
    cin>>n;

    int arr[n] = {0};
    for(int i=0; i<n; i++) arr[i] = rand()%30;

    cout<<"Array: ";
    for(int i=0; i<n; i++) cout<<arr[i]<<" ";
    cout<<endl;


    quicksort(arr,0,n-1);

    cout<<"Sorted Array: ";
    for(int i=0; i<n; i++) cout<<arr[i]<<" ";
    return 0;
}