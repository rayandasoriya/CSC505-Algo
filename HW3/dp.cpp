//Aim: Number of scaler multiplications in Matrix chain multiplication using dynamic approach
//Kushagr Gupta (kgupta7)    Rayan Dasoriya(rdasori)

#include<iostream>
#include<limits.h>
using namespace std;

long long int DynamicMatrixChainOrder(long int p[], long int n) 
{ 
    long long int *cost = new long long int [n*n]; 

    for (long int l = 0; l < n; l++) {
			for (long int start = 0; start < n - l; start++) {
				if (l <= 1)
					*(cost+(start*n) + start + l) = 0;
				else 
				{
					*(cost+(start*n) + start + l) = LLONG_MAX;
					for (long int k = start + 1; k < start + l; k++) {
						long long int temp = (p[start] * p[k] * p[start + l]) + *(cost+(start*n)+k) + *(cost+(k*n)+start + l);
						*(cost+(start*n) + start + l) = *(cost+(start*n) + start + l)<temp?*(cost+(start*n) + start + l):temp;
					}
				}
			}
		}
    return cost[n-1]; 
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
    cout<< DynamicMatrixChainOrder(a, n)<<"\n";
    return 0;
}
