#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

int main(){

    int n,m = 0;
    int sum_a = 0;
    double sum_a_f = 0;
    double ans = 0;

    scanf("%d",&n);
    scanf("%d",&m);
    int *a = new int[n];
    int *flag = new int[n];
    int *b = new int[m];
    int *c = new int[m];
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
        scanf("%d",&flag[i]);
        sum_a += a[i];
        sum_a_f += (a[i]-flag[i]*0.2*a[i]);
    }
    ans = sum_a_f;
    for(int i = 0; i < m; i++){
        scanf("%d",&b[i]);
        scanf("%d",&c[i]);
        if(sum_a >= b[i]){
            ans = min(ans, double(sum_a - c[i]));
        }
    }
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}
