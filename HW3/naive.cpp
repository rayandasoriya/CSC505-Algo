//Aim: Number of scaler multiplications in Matrix chain multiplication using naive approach
//Kushagr Gupta (kgupta7)    Rayan Dasoriya(rdasori)

#include<iostream>
using namespace std;

int main()
{
    long int i = 0;
    long int n;
    cin>>n;
    n+=1;
    long int a[n];
    for(i = 0;i<n;i++)
        cin>>a[i];
    long int ans = 0;
    for(i=1;i<n-1;i++)
        ans += a[0]*a[i]*a[i+1];
    cout<<ans<<"\n";
    return 0;
}
