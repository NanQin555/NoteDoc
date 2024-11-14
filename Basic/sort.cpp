#include <iostream>
#include <vector>
using namespace std;

int part(int left, int right, vector<int>& arr) {
    int pivot = arr[left];
    while(left < right) {
        while(left < right && arr[right] >= pivot) right--;
        arr[left] = arr[right];
        while(left < right && arr[left] <= pivot) left++;
        arr[right] = arr[left];
    }
    arr[left] = pivot;
    return left;
}
void sort(int left, int right, vector<int>& arr) {
    if(left < right) {
        int pos = part(left, right ,arr);
        sort(left, pos-1, arr);
        sort(pos+1, right, arr);
    }
    return;
}
int main() {
    vector<int> arr = {2,1,6,4,3,8,34,12,55,1,21};

    sort(0, arr.size(), arr);

    for(auto v: arr) {
        cout << v << " ";
    }
    return 0;
}