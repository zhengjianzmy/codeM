#include <iostream>
#include <cstdio>
#include <iomanip>
#include <ostream>
void Merge(double arr[], double reg[], int start, int end);
void MergeSort(double arr[], const int len);
void quickSort(double array[], int left, int right);
using namespace std;

int main(){

    int n,m,k,C = 0;

    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);
    scanf("%d", &C);

    int *tmp_w = new int[m];
    double *w = new double[m];
    int *max_s = new int[m];
    double sum_w = 0;
    int flag_i = 0;
    int flag_j = 0;
    double *point = new double[n];
    double *tmp_point = new double[n];
    int *success = new int[n];


    int score[n][m];  

    for(int i = 0; i < m; i++){
        scanf("%d", &tmp_w[i]);
        sum_w += tmp_w[i];
    }

    for(int i = 0; i < m; i++){
        w[i] = double(tmp_w[i] / sum_w);
        max_s[i] = -1;
    }

    for(int i = 0; i < n; i++){
        success[i] = 0;
        for(int j = 0; j < m; j++){
            scanf("%d", &score[i][j]);
            if(score[i][j] == -1){
                flag_i = i;
                flag_j = j;
            }
        }
    }



    for(int s = 0; s <= C; s++){

        score[flag_i][flag_j] = s;

        for(int j = 0; j < m; j++){
            max_s[j] = -1;
            for(int i = 0; i < n; i++){
                if(score[i][j] > max_s[j]){
                    max_s[j] = score[i][j];
                }
            }
        }
        for(int i = 0; i < n; i++){
            point[i] = 0;
            for(int j = 0; j < m; j++){
                if(max_s[j] > 0){
                    point[i] += double(score[i][j])/double(max_s[j])*w[j];
                }
            }
            tmp_point[i] = point[i];
        }

        quickSort(point, 0, n-1);
        double k_score = point[n-k];

        int flag_k = 0;
        if(n > k){
            flag_k = (k_score == point[n-k-1]);
        }

        for(int i = 0; i < n; i++){
            if(tmp_point[i] > k_score || (tmp_point[i] == k_score && flag_k == 0)){
                success[i] += 1;
            }
            else if(tmp_point[i] == k_score && flag_k == 1){
                success[i] += 0;
            }
            else{
                success[i] -= 1;
            }
        }

    }

    for(int i = 0; i < n; i++){
        if(success[i] == C+1){
            cout << 1 << endl;
        }
        else if(success[i] == -(C+1)){
            cout << 2 << endl;
        }
        else{
            cout << 3 << endl;
        }
    }
    
    return 0;
}

void quickSort(double array[], int left, int right){
	if (left > right){
		return;
	}
	int i, j;
    double temp;
	i = left;
	j = right;
	//以最左边的数作为基准数
	temp = array[left];
	while (i != j){
		//先从右边开始找小于temp的元素  注意等号
		while (array[j] >= temp && i < j) {
			j--;
		}
		//再从左边开始找大于temp的元素
		while (array[i] <= temp && i < j){
			i++;
		}
		//左右哨兵均找到满足要求的数后，交换这两个数
		if (i < j){
			double change = array[i];
			array[i] = array[j];
			array[j] = change;
		}
	}
	//i==j  将基准数归位，此时基准数左边的数均小于基准数，右边的数均大于基准数
	array[left] = array[j];
	array[j] = temp;
	
	//然后递归处理基准左边未排序的数，和基准右边的数
	quickSort(array, left, i-1);
	quickSort(array, i + 1, right);

}

void Merge(double arr[], double reg[], int start, int end) {
    if (start >= end){
        return;
    }
    int len = end - start, mid = (len >> 1) + start;

    //分成两部分
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    //然后合并
    Merge(arr, reg, start1, end1);
    Merge(arr, reg, start2, end2);


    int k = start;
    //两个序列一一比较,哪的序列的元素小就放进reg序列里面,然后位置+1再与另一个序列原来位置的元素比较
    //如此反复,可以把两个有序的序列合并成一个有序的序列
    while (start1 <= end1 && start2 <= end2){
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    }
    //然后这里是分情况,如果arr2序列的已经全部都放进reg序列了然后跳出了循环
    //那就表示arr序列还有更大的元素(一个或多个)没有放进reg序列,所以这一步就是接着放
    while (start1 <= end1){
        reg[k++] = arr[start1++];
    }
    //这一步和上面一样
    while (start2 <= end2){
        reg[k++] = arr[start2++];
    }
    //把已经有序的reg序列放回arr序列中
    for (k = start; k <= end; k++){
        arr[k] = reg[k];
    }
}

void MergeSort(double arr[], const int len) {
    //创建一个同样长度的序列,用于临时存放
    double reg[len];
    Merge(arr, reg, 0, len - 1);
}