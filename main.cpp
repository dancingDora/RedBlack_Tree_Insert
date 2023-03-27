#include <iostream>
#include "rbtree.h"

using namespace std;

#include <fstream>
int main() {
    //init
        ifstream fin("./test.data");
        ofstream fout("./test.data");

        RedBlackTree rbt;



    {//generate test and input
      rbt.insert(1);
      rbt.insert(2);
      rbt.insert(3);
      rbt.insert(4);
      rbt.insert(5);
      rbt.insert(6);
      rbt.insert(7);
      rbt.insert(8);
    }

    {//output
        cout << rbt.search(1) << endl;
        cout << rbt.search(2) << endl;
        cout << rbt.search(3) << endl;
        cout << rbt.search(4) << endl;
        cout << rbt.search(1) << endl;
        cout << rbt.search(6) << endl;
        cout << rbt.search(7) << endl;
        cout << rbt.search(8) << endl;
        cout << rbt.search(5) << endl;
    }
}