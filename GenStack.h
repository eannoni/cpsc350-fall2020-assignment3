// GenStack header
#ifndef GENSTACK
#define GENSTACK

#include <iostream>

using namespace std;

template <typename T>
class GenStack {

    public:
        GenStack(); // default constructor
        GenStack(int maxSize); // overloaded constructor
        ~GenStack(); // destructor

        void push(T data);
        T pop();
        T peek();

        bool isFull();
        bool isEmpty();
        int getSize();

        void print();

        void resize();

    private:
        int top;
        int maxSize;
        T *arr;
};

#endif

// GenStack implementation

template <typename T>
GenStack<T>::GenStack() {
    arr = new T[128];
    maxSize = 128;
    top = -1;
}

template <typename T>
GenStack<T>::GenStack(int maxSize) {
    arr = new T[maxSize];
    this->maxSize = maxSize;
    top = -1;
}

template <typename T>
GenStack<T>::~GenStack() {
    delete[] arr;
}

template <typename T>
void GenStack<T>::push(T data) {
    if(isFull()) {
        resize();
    }
    arr[++top] = data;
}

template <typename T>
T GenStack<T>::pop() {
    if(!isEmpty()) {
        return arr[top--];
    }
    throw "Stack underflow exception!";
}

template <typename T>
T GenStack<T>::peek() {
    if(!isEmpty()) {
        return arr[top];
    }
    throw "Stack underflow exception!";
}

template <typename T>
bool GenStack<T>::isFull() {
    return (top >= maxSize - 1);
}

template <typename T>
bool GenStack<T>::isEmpty() {
    return (top < 0);
}

template <typename T>
int GenStack<T>::getSize() {
    return (top + 1);
}

template <typename T>
void GenStack<T>::print() {
    cout << "Stack: [ ";
    for(int i = 0; i <= top; ++i) {
        cout << arr[i] << " ";
    }
    for(int i = top + 1; i < maxSize; ++i) {
        cout << "_ ";
    }
    cout << "]" << endl;
}

template <typename T>
void GenStack<T>::resize() {
    maxSize *= 2;
    // create new temp array
    T *temp = new T[maxSize];
    // copy values to temp array
    for(int i = 0; i <= top; ++i) {
        temp[i] = arr[i];
    }
    // delete old array
    delete arr;
    // have old array point to temp
    arr = temp;
}
