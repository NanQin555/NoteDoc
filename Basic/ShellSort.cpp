#include <iostream>
#include <vector>
using namespace std;


int main() {
    vector<int> test = {2,1,6,4,3,8,34,12,55,1,21};
    int j;
    for(int gap=test.size(); gap>0; gap/=2) {
        for(int i=gap; i<test.size(); i++) {
            int temp = test[i];
            for(j=i; j>=gap&&temp<test[j-gap]; j-=gap) {
                test[j] = test[j-gap];
            }
            test[j] = temp;
        }
    }
    for(auto v: test) {
        cout << v << " ";
    }
    return 0;
}