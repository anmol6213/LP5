#include<iostream>
#include<omp.h>
using namespace std;
int main()
{
    cout<<endl;
    cout<<"Enter the number of elements in the vector: ";
    int nvec;
    cin>>nvec;

    int vec[nvec] = {0};

    for(int i=0; i<nvec; i++) vec[i] = rand()%10;
    cout<<endl;

    cout<<"Vector: ";
    for(int i=0; i<nvec; i++) cout<<vec[i]<<" ";
    cout<<endl;

    cout<<endl;
    cout<<"Enter the number of rows in the matrix: ";
    int rows;
    cin>>rows;

    int mat[rows][nvec];
    for(int i=0; i<rows; i++) for(int j=0; j<nvec; j++) mat[i][j] = rand()%10;
    cout<<endl;

    cout<<"Matrix: "<<endl;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<nvec; j++) cout<<mat[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    cout<<"Multiplication: "<<endl;
    int rvec[nvec];

    #pragma omp parallel for
    for(int i=0; i<rows; i++)
    {
        rvec[i] = 0;
        int arr[nvec] = {0};

        #pragma omp parallel for
        for(int j=0; j<nvec; j++) arr[j] = mat[i][j] * vec[j];

        int sum = 0;

        #pragma omp parallel for reduction(+: sum)
        for(int k = 0; k < nvec; k++) sum += arr[k];

        rvec[i] = sum;
    }

    for(int i=0; i<nvec; i++) cout<<rvec[i]<<" ";
    cout<<endl;
    
    return 0;
}