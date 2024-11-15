#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 *  默认拷贝构造函数是浅拷贝
 */
class A {
private:
    int* a;
    string* name;
public:
    // 普通构造函数
    A(int* _a, string* _name): a(_a), name(_name) {}    
    // 拷贝构造函数 
    A(const A& entity): a(new int(*entity.a)), name(new string(*entity.name)) {};
    // 拷贝赋值操作
    A& operator= (const A& entity) {
        if(this != &entity) {
            delete a;
            delete name;
            a = entity.a;
            name = entity.name;
        }
        return *this;
    }
    // 移动构造函数
    A(A&& entity) noexcept: a(entity.a), name(entity.name) {
        entity.a = nullptr;
        entity.name = nullptr;
    }
    // 移动赋值操作
    A& operator= (A&& entity) noexcept {
        if(this != &entity) {
            delete a;
            delete name;
            a = entity.a;
            name = entity.name;
            entity.a = nullptr;
            entity.name = nullptr;
        }
        return *this;
    }
};

int main() {

    return 0;
}