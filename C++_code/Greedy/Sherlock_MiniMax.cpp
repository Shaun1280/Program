#include <bits/stdc++.h>
using namespace std;
const long long m=1e9+7;
int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
        int p,q;
        cin>>p>>q;
    sort(arr.begin(),arr.end());
    if(arr[0]>q)
    {
        cout<<p;
        return 0;
    }
    else if(arr[n-1]<p)
    {
        cout<<q;
        return 0;
    }
    else
    {
    int ans=-1,num=-1;
    if(arr[0]>p)
        if(ans<arr[0]-p)
        {
            ans=arr[0]-p;
            num=p;
        }
    if(arr[n-1]<q)
        if(ans<q-arr[n-1])
        {
            ans=q-arr[n-1];
            num=q;
        }
    for(int i=0;i<n-1;i++)
    {
        int mid=(arr[i]+arr[i+1])/2;
        if(mid<=q && mid>=p && (mid-arr[i])>ans)
        {
            ans=mid-arr[i];
            num=mid;
        }
        else if(mid>q)
        {
            if(q-arr[i]>ans)
            {
                ans=q-arr[i];
                num=q;
            }
        }
        else if(mid<p)
        {
            if(arr[i+1]-p>ans)
            {
                ans=arr[i+1]-p;
                num=p;
            }
        }
    }
    cout<<num;
    }
}