#include <iostream>
#include "my_string.h"
using namespace std;


int main() {
    MyString a1 = "meow ";
    string s = "meow";
    
    a1 +=s;
    cout << a1 << " " << a1.length() << " " << a1.capacity() << endl;
    a1 += " meow";
    cout << a1 << " " << a1.length() << " " << a1.capacity() << endl;
    a1 += a1;
    cout << a1 << " " << a1.length() << " " << a1.capacity() << endl;
    
    return 0;
}


