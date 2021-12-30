#include <iostream>
#include <ctime>
#include "xmemory.h"
#include "vector.h"

using namespace std;

// myAllocator test 
int main() {
    rs::vector<int> v[10001];
    long long begin = clock();
    for (int i = 0; i < 10001; i++) {
        v[i].data = (int *)myalloc::alloc().allocate(sizeof(int)*(rand() % 1000));
    } 
    long long  end = clock();
    long long t = 1000 * (end - begin) / CLOCKS_PER_SEC;
    cout << "100001 vector alloc time: " << t << "(ms)" << endl << endl;

    long long begin1 = clock();
    int cnt = 1000;
    while (cnt--) {
        int ind = rand() % 10000;
        int *p = v[ind].data;
        int old_size = sizeof(v[ind].data);
        v[ind].data = (int *)myalloc::alloc().reallocate(p, old_size, rand() % 1000);
    }
    long long  end1 = clock();
    long long t1 = 1000 * (end1 - begin1) / CLOCKS_PER_SEC;
    cout << "1000 vector change size time: " << t1 << "(ms)" << endl << endl;

    long long begin2 = clock();
    for (int i = 0; i < 10001; i++) {
        int *p = v[i].data;
        int size = sizeof(v[i].data);
        myalloc::alloc().deallocate(p, size);
    } 
    long long  end2 = clock();
    long long t2 = 1000 * (end2 - begin2) / CLOCKS_PER_SEC;
    cout << "10001 vector dealloc time: " << t2 << "(ms)" << endl;
    return 0;
}
