#include <iostream>
#include "rbtree.h"
#include "avltree.h"
#include "skiplist.h"

using namespace std;

#include <fstream>
#include <unordered_set>

unordered_set<int> table;
unordered_set<int> del;

int genRandomInt() {
    return rand() % 30000;
}

int genRandomDel(int n) {
    return rand() % n;
}

static inline uint64_t rdtsc() {
    uint32_t low, high;
    asm volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((uint64_t) high << 32) | low;
}

#include <time.h>

int n[] = {0, 100, 1000, 10000, 20000, 30000};

int main() {
    //init
    RedBlackTree rbt[6];
    AVL<int> avl[6];
    skipList<int> *skip[6];
    for (int i = 1; i <= 5; i++)
        skip[i] = new skipList<int>(22, 0);
    {//generate test
        int x, del10;
        ofstream fout("test1.txt");
        for (int cnt = 1; cnt <= 5; cnt++) {
            x = n[cnt];
            del10 = x / 10;
            srand(time(0));

            int a[x + 10];
            for (int i = 0; i < x; ++i) {
                int tmp = genRandomInt();
                while (table.find(tmp) != table.end())
                    tmp = genRandomInt();
                table.insert(tmp);
                a[i] = tmp;
            }

            for (auto it: table) {
                fout << "i " << it << endl;
            }

            for (int i = 0; i < del10; ++i) {
                int tmp = genRandomDel(x);
                while (del.find(tmp) != del.end())
                    tmp = genRandomDel(x);
                del.insert(tmp);
                fout << "s " << a[tmp] << endl;
            }
            table.clear();
            del.clear();
            fout << "q" << endl;
        }
    }
    uint64_t start, end;
    {//output rbt
        ifstream fin("test1.txt");
        char op;
        int cnt = 1, k;
        int insI = 0, srI = 0;
        start = rdtsc();
        while (fin >> op) {
            if (op == 'i') {
                fin >> k;
//                rbt[cnt].insert(k);
                rbt[cnt].insert(insI++);
            } else if (op == 's') {
                fin >> k;
//                rbt[cnt].search(k);
//                if (srI < insI)

//                    rbt[cnt].search(srI++);
            } else if (op == 'q') {
                end = rdtsc();
                cout << "RBT Case " << cnt << " : " << end - start << '\n';
                start = rdtsc();
//                cout << "RBT Case " << cnt << " : " << rbt[cnt].rTime << endl;
                cnt++;
                //TODO : c out what
            } else cerr << "wrong option.\n";
        }
        cout << '\n';
    }

    {//output avl
        ifstream fin("test1.txt");
        char op;
        int cnt = 1, k;
        int insI = 0, srI = 0;
        start = rdtsc();
        while (fin >> op) {
            if (op == 'i') {
                fin >> k;
//                avl[cnt].insert(k);
                avl[cnt].insert(insI++);
            } else if (op == 's') {
                fin >> k;
//                avl[cnt].search(k);
//                if (srI < insI - 10)
//                    avl[cnt].search(srI++);

            } else if (op == 'q') {
                end = rdtsc();
                cout << "AVL Tree Case " << cnt << " : " << end - start << '\n';
//                cout << "AVL Tree Case " << cnt << " : " << avl[cnt].rTime << endl;

                start = rdtsc();
                cnt++;
                //TODO : c out what
            } else cerr << "wrong option.\n";
        }
        cout << '\n';
    }

    {//output skiplist
        ifstream fin("test1.txt");
        char op;
        int cnt = 1, k = 0, forFind;
        int insI, srI;
        start = rdtsc();
        while (fin >> op) {
            if (op == 'i') {
                fin >> k;
                skip[cnt]->insert(insI, insI++);

            } else if (op == 's') {
                fin >> k;
//                skip[cnt]->find(srI++, forFind);
            } else if (op == 'q') {
                end = rdtsc();
                cout << "Skip List Case " << cnt << " : " << end - start << '\n';
                start = rdtsc();
                cnt++;
                //TODO : c out what
            } else cerr << "wrong option.\n";
        }
    }
}