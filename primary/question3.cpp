#include <iostream>
#include <cstdio>
#include <iomanip>
#include <ostream>

using namespace std;

int main(){

    int n,m = 0;

    double *ans = new double[16];
    double *p1 = new double[16];
    double *p2 = new double[16];
    double *p3 = new double[16];
    double *p4 = new double[16];

    double F[16][16];  

    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            //cin >> F[i][j];
            scanf("%lf", &F[i][j]);
            //cout << F[i][j] << endl;
        }

    }
    for(int i = 0; i < 16; i++){
        p1[i] = (i%2 == 0)?F[i][i+1]:F[i][i-1];
    }
    for(int i = 0; i < 16; i++){
        if((i%4) < 2){
            if(i%2 == 0){
                p2[i] = p1[i]*(p1[i+2]*F[i][i+2] + p1[i+3]*F[i][i+3]);
            }
            else{
                p2[i] = p1[i]*(p1[i+1]*F[i][i+1] + p1[i+2]*F[i][i+2]);
            }
        }
        else{
            if(i%2 == 0){
                p2[i] = p1[i]*(p1[i-2]*F[i][i-2] + p1[i-1]*F[i][i-1]);
            }
            else{
                p2[i] = p1[i]*(p1[i-3]*F[i][i-3] + p1[i-2]*F[i][i-2]);
            }
        }
    }
    for(int i = 0; i < 16; i++){
        if(i == 0 || i == 1 || i == 2 || i == 3){
            p3[i] = p2[i]*(p2[4]*F[i][4] + p2[5]*F[i][5] + p2[6]*F[i][6] + p2[7]*F[i][7]);
        }
        else if(i == 4 || i == 5 || i == 6 || i == 7){
            p3[i] = p2[i]*(p2[0]*F[i][0] + p2[1]*F[i][1] + p2[2]*F[i][2] + p2[3]*F[i][3]);
        }
        else if(i == 8 || i == 9 || i == 10 || i == 11){
            p3[i] = p2[i]*(p2[12]*F[i][12] + p2[13]*F[i][13] + p2[14]*F[i][14] + p2[15]*F[i][15]);
        }
        else if(i == 12 || i == 13 || i == 14 || i == 15){
            p3[i] = p2[i]*(p2[8]*F[i][8] + p2[9]*F[i][9] + p2[10]*F[i][10] + p2[11]*F[i][11]);
        }
    }
    for(int i = 0; i < 16; i++){
        if(i/8 == 0){
            p4[i] = 0;
            for(int j = 8; j < 16; j++){
                p4[i] = p4[i] + p3[i]*(p3[j]*F[i][j]);
            }
        }
        else{
            p4[i] = 0;
            for(int j = 0; j < 8; j++){
                p4[i] = p4[i] + p3[i]*(p3[j]*F[i][j]);
            }
        }
    }

    for(int i = 0; i < 16; i++){
        if(i == 15){
            cout << p4[i];
        }
        else{
            cout << p4[i] << " ";
        }
    }
    cout << endl;
    return 0;
}
