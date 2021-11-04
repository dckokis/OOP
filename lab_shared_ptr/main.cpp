#include <iostream>
#include "SharedPTR.hpp"
using namespace std;
class T{
public:
    ~T(){
        cout << "~T()" << endl;
    }
};


int main() {
    SharedPTR<T> a(new T[10]);
    shared_ptr<T[]> b(new T[10]);
    return 0;
}
