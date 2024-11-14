# 直接插入排序

时间：O(n)~O(n^2) 平均O(n^2)

空间： O(1)

稳定
``` cpp
for(int i=1; i<size; i++) {
    if(arr[i] < arr[i-1]) {
        int temp = arr[i];
        for(int j=i-1; j>=0&temp<arr[j]; j--) {
            arr[j+1] = arr[j];
        }
        arr[j+1] = temp;
    }
    continue;
}
```

# 折半插入排序

时间：O(n)~O(n^2) 平均O(n^2)

空间： O(1)

稳定

与直接插入排序差不多，只是查找插入索引的方式为折半查找

# 希尔排序

时间：O(n)~O(n^2) 平均O(n^1.3)

空间： O(1)

不稳定

与直接插入排序差不多，先引入一个增量d=size/2下取整，将数据分为d组，对每组分别进行直接插入排序，然后d = d/2下取整，重复以上操作，直到d=1操作完成

``` cpp
for(int gap=test.size(); gap>0; gap/=2) {
    for(int i=gap; i<test.size(); i++) {
        int temp = test[i];
        for(j=i; j>=gap&&temp<test[j-gap]; j-=gap) {
            test[j] = test[j-gap];
        }
        test[j] = temp;
    }
}
```

# 快速排序

时间：O(n log n)~O(n^2) 平均 O(n log n)

空间： O(log n) ~ O(n) 根据选择划分的方法，是重新开一个数组还是原地挖坑法

不稳定

``` cpp
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
```

# 简单选择排序

时间：O(n^2)~O(n^2) 平均 O(n^2)

空间： O(1) 

不稳定

每次记录一个最小值，将最小值归位

# 堆排序

时间：O(n log n)~O(n log n) 平均 O(n log n)

空间： O(1) 

不稳定

建堆（小顶堆，大顶堆）

排序：反复将堆顶放到最后再向下调整新的堆顶

``` cpp
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
```