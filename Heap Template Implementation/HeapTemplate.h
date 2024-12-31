// Alexander Potiagalov (301586871)
// Nov 8th, 2024
#pragma once 
#include <stdexcept>
#include <iostream>
using std::cout;
using std::endl;
using std::runtime_error;

template <class T>
class HeapT {
public:
    // HEAPT METHODS
    HeapT(int x); // Constructor
    HeapT(const HeapT& other); // Copy Constructor
    ~HeapT(); // Destructor
    HeapT& operator=(const HeapT& other); // Overloaded Assignment Operator
    void insert(T val); // Insert
    T remove(); // Remove
    T peek() const; // Peek
    HeapT merge(const HeapT& other) const; // Merge
    int size() const; // Size
private:
    int n;
	int capacity;
	T* arr;
	// HEAPT HERLPER FUNCTIONS
	void copyHelper(const HeapT& other); 
	void BubbleUp(int i);
	void BubbleDown(int i);
};

// HEAPT IMPLEMENTATIONS
// Constructor
template <class T>
HeapT<T>::HeapT(int x)
{
    capacity = x;
    n = 0;
    arr = new T[capacity];
}

// Copy Constructor
template <class T>
HeapT<T>::HeapT(const HeapT& other)
{
    copyHelper(other);
}

// Copy Destructor
template <class T>
HeapT<T>::~HeapT()
{
    delete[] arr;
}

// Overloaded assignment operator
template <class T>
HeapT<T>& HeapT<T>::operator=(const HeapT& other)
{
    if (this != &other){
        delete[] arr;
        copyHelper(other);
    }
    return *this;
}

// Insert
template <class T>
void HeapT<T>::insert(T val) 
{
    if (n == capacity){
        throw runtime_error("Heap is Full");
    }
    arr[n] = val;
    BubbleUp(n);
    n++;
}

// Remove
template <class T>
T HeapT<T>::remove()
{
    if (n == 0){
        throw runtime_error("Heap is Empty");
    }
    T removedroot = arr[0];
    arr[0] = arr[n-1];
    n--;
    BubbleDown(0);
    return removedroot;
}

// Peek
template <class T>
T HeapT<T>::peek() const 
{
    if (n == 0) {
        throw runtime_error("Heap is Empty");
    }
    return arr[0];
}

// Merge
template <class T>
HeapT<T> HeapT<T>::merge(const HeapT& other) const 
{
    HeapT<T> mergedHeap(capacity + other.capacity);
    for (int i = 0; i < n; i++) {
        mergedHeap.insert(arr[i]);
    }
    for (int i = 0; i < other.n; i++) {
        mergedHeap.insert(other.arr[i]);
    }
    return mergedHeap;
}


// Size
template <class T>
int HeapT<T>::size() const 
{
    return n;
}

// HELPER FUNCTIONS
// Copy Helper
template <class T>
void HeapT<T>::copyHelper(const HeapT& other)
{
    n = other.n;
    capacity = other.capacity;
    arr = new T[capacity];
    for (int i = 0; i < n; i++){
        arr[i] = other.arr[i];
    }
}

// Bubble Up
template <class T>
void HeapT<T>::BubbleUp(int i)
{
    int parent = (i - 1) / 2;
    if (i > 0 && arr[i] < arr[parent]){
        T temp = arr[i];
        arr[i] = arr[parent];
        arr[parent] = temp;
        BubbleUp(parent);
    }
    // no else – implicit base case
}

// Bubble Down
template <class T>
void HeapT<T>::BubbleDown(int i)
{
    int parent = i;
    int childleft = 2*i + 1;
    int childright = 2*i + 2;
    if (childleft < n && arr[parent] > arr[childleft]) {
        parent = childleft;
    }
    if (childright < n && arr[parent] > arr[childright]) {
        parent = childright;
    }
    if (parent != i) {
        T temp = arr[i];
        arr[i] = arr[parent];
        arr[parent] = temp;
        BubbleDown(parent);
    }
}

