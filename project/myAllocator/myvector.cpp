#include <iostream>
#include <vector>
using namespace std;


namespace rs {
template<typename T>
class vector {
public:
    vector(int n = 10);
    vector(const vector<T> &);
    vector(vector<T> &);
    T &operator[](int);
    const T &operator[](int) const;
    T &at(int);
    int size() const;
    bool empty();
    void push_back(const T &);
    void push_back(T &&);
    void clear();
    ~vector();
private:
    void inflate();
    int __size, __capacity;
    T *data;
};

template<typename T>
vector<T>::vector(int n) : __size(0), __capacity(n), data(nullptr) {
    data = (T *)malloc(sizeof(T) * __capacity);
}

template<typename T>
vector<T>::vector(const vector<T> &v) : __size(v.__size), __capacity(v.capacity) {
    data = (T *)malloc(sizeof(T) * __capacity);
    for (int i = 0; i < v.__size; i++) {
        new(data + i) T(v.data[i]);
    }
}

template<typename T>
vector<T>::vector(vector<T> &v) : __size(v.__size), __capacity(v.__capacity), data(v.data) {
    v.data = nullptr;
    __size = 0;
    __capacity = 0;
}

template<typename T>
T &vector<T>::operator[](int ind) {
    return data[ind];
}

template<typename T>
const T &vector<T>::operator[](int ind) const {
    return data[ind];
}
template<typename T>
int vector<T>::size() const { return __size; }

template<typename T>
bool vector<T>::empty() {
    return this->size() == 0;
}

template<typename T>
T &vector<T>::at(int index) {
    try {
        if (index < 0 || index >= this->__size) {
            throw(std::out_of_range());
        }
    }
    catch(...) {
        cout << "index is invalid!" << endl;
    }
    return this->data[index];
}

template<typename T>
void vector<T>::inflate() {
    int extra_size = this->__capacity;
    int *p;
    while (extra_size) {
        p = (int *)realloc(this->data, sizeof(int) * (extra_size + this->__size));
        if (p) break;
        extra_size >>= 1;
    }
    if (!extra_size) {
        cout << "expand fail" << endl;
        return ;
    }
    this->data = p;
    this->__capacity += extra_size;
    cout << "expand success!" << endl;
    return ;
}

template<typename T>
void vector<T>::push_back(const T &d) { 
    if (__size == __capacity) this->inflate();
    new(data + __size) T(d);
    __size += 1;
    return ;
}

template<typename T>
void vector<T>::push_back(T &&d) {
    new(data + __size) T(move(d));
    __size += 1;
    return ;
}

template<typename T>
void vector<T>::clear() {
    if (data) free(data);
    data = nullptr;
    __size = 0;
    __capacity = 0;
    return ;
}

template<typename T>
vector<T>::~vector() {
    this->clear();
}

}   // end of rs

ostream &operator<<(ostream &out, const rs::vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        out << v[i] << " ";
    }
    return out;
}

int main() {
    rs::vector<int> v;
    if (v.empty()) {
        cout << "v is empty!" << endl;
    }
    v.push_back(1);
    v.push_back(3);
    v.push_back(5);
    cout << v.size() << endl;
    cout << v << endl;
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);
    cout << v.size() << endl;
    cout << v << endl;
    v.clear();
    cout << "after clear, size = " << v.size() << endl;
    return 0;
}
