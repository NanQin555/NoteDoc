#include <iostream>
#include <vector>
using namespace std;
void HeapAdjust(vector<int>& arr, int start, int end) {
    int dad = start;
    int son = dad*2+1;
    while(son<=end) {
        if(son+1<=end && arr[son] < arr[son+1]) 
            son++;
        if(arr[dad] > arr[son]) 
            return;
        else {
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad*2+1;
        }
    }
    
}
void HeapSort(vector<int>& arr, int len) {
    for(int i=len/2-1; i>=0; i--) {
        HeapAdjust(arr, i, len-1);
    }
    for(int i=len-1; i>0; i--) {
        swap(arr[0], arr[i]);
        HeapAdjust(arr, 0, i-1);
    }
}

int main() {
    vector<int> arr = {2,1,6,4,3,8,34,12,55,1,21};
    HeapSort(arr, arr.size());

    for(auto v: arr) {
        cout << v << " ";
    }
    return 0;
}