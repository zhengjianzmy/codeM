#include <iostream>
#include <cstdio>
#include <iomanip>
double count_love(int n, int m, int k, int *a, int *b, int *ans);
int divideNtoKpartAndPrintAllConditions(int n, int k, int start, int *condition, int index);
double divideNtoKpart(int n, int k, int *condition, int index, int on, int om, int ok, int *a, int *b);
int *reSort(int *ans);
using namespace std;
#define Max 100
#define INT_MIN 0x80000000
int parts;
int times = 0;
static double love;
static int *max_love;

int main(){

    int n,m,k = 0;
    love = -10000;
    
    parts = k;
    scanf("%d",&n);
    scanf("%d",&m);
    scanf("%d",&k);
    int *a = new int[k];
    int *b = new int[k];
    int *ans = new int[k];
    max_love = new int[k];

    for(int i = 0; i < k; i++){
        scanf("%d",&a[i]);
        scanf("%d",&b[i]);
        max_love[i] = 0;
    }

    int conditions[k];
    divideNtoKpart(n, k, conditions, 0, n, m, k, a, b);

    for(int i = 0; i < k; i++){
        if(i == k-1){
            cout << max_love[i];
        }
        else{
            cout << max_love[i] << " ";
        }
    }
    cout << endl;
    return 0;
}


double divideNtoKpart(int n, int k, int *condition, int index, int on, int om, int ok, int *a, int *b){   
    if(index == ok-1){
        condition[index] = n;
        double temp = count_love(on, om, ok, a, b, condition);
        if(temp >= love){
            cout << "love1 = " << love << endl;
            love = temp;
            for(int i = 0; i < ok; i++){
                cout << max_love[i];
            }
            cout << endl;
            for(int i = 0; i < ok; i++){
                max_love[i] = condition[i];
            }
            //max_love = condition;
            for(int i = 0; i < ok; i++){
                cout << max_love[i];
            }
            cout << endl;
            cout << "love1 = " << love << endl;
        }
        return 1;
    }
    if(n == 0){
        for (int m = index; m < ok; m++){
            condition[m] = 0;
        }
        double temp = count_love(on, om, ok, a, b, condition);
        if(temp >= love){
            cout << "love2 = " << love << endl;
            love = temp;
            for(int i = 0; i < ok; i++){
                cout << max_love[i];
            }
            cout << endl;
            for(int i = 0; i < ok; i++){
                max_love[i] = condition[i];
            }            
            //max_love = condition;
            for(int i = 0; i < ok; i++){
                cout << max_love[i];
            }
            cout << endl;
            cout << "love2 = " << love << endl;     
        }
        return 1;
    }
    for(int i = n; i >= 0; i--){
        condition[index] = i;
        divideNtoKpart(n-i, k-1, condition, index+1, on, om, ok, a, b);
    }
    return 1;
}

double count_love(int n, int m, int k, int *a, int *b, int *ans){
    double like = 0;
    for(int i = 0; i < k; i++) {
        like += double(a[i]*ans[i]*m)/double(n);
    }
    for(int i = 0; i < k; i++) {
        like += double(b[i]*ans[i]*(n-m))/double(n);
    }
    return like;
}
