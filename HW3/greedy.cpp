//Aim: Number of scaler multiplications in Matrix chain multiplication using greedy approach
//Kushagr Gupta (kgupta7)    Rayan Dasoriya(rdasori)


#include<iostream>
using namespace std;

long int GreedyMatrixChainOrder(long int a[], long int m, long int n)
{
    if(n-m<=1)
        return 0;
    long int min_val = a[m] * a[m + 1] * a[n];
	long int min_i = m + 1;
    for (long int k = m + 1; k < n; k++) {
        if (a[m] * a[k] * a[n] < min_val) {
            min_val = a[m] * a[k] * a[n];
            min_i = k;
        }
    }
	return min_val + GreedyMatrixChainOrder(a, m, min_i) + GreedyMatrixChainOrder(a, min_i, n);
}

int main()
{
    long int i = 0;
    long int n;
    cin>>n;
    n+=1;
    long int a[n];
    for(i = 0;i<n;i++)
        cin>>a[i];
    cout<< GreedyMatrixChainOrder(a, 0,n-1)<<"\n";
    return 0;
}
