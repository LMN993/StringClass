#include <iostream>
#include "my_string.h"
using namespace std;



int main() {
    MyString a1 = "meow ";
    string s = "meow";
    MyString a3 = a1 +s;
    cout << a3 << " " << a3.length() << " " << a3.capacity() << endl;
    
    return 0;
}


