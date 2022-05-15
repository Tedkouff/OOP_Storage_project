#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include<exception>

template <typename T>
class Vector {
private:
    T* arr;
    int storage;
    int count;

    void copyVectors(const Vector& rhs);
    void addToCount();
public:
    Vector();                               // constructor
    Vector(int);                            // constructor with parameter
    Vector(const Vector& rhs);              // copy constructor
    Vector& operator=(const Vector& rhs);   // copy assignment operator
    ~Vector();                              // destructor

    void add(const T& element);                      // добавя най-отзад елемент към вектора (push_back)
    int getStorage() const;                          // функция за достъп
    int size() const;                                // функция за достъп
    void print() const;                              // извежда елементите на вектора
    void pushAtIndex(const T& element, int index);   // присвоява нова стойност на елемент на позиция index
    void removeAtIndex(int i);                       // премахва елемент на позиция index (намалява големината с 1)
    void clear();                                    // изчиства заделената памет
    void deleteVector();                             // изтрива вектора
    void allocateMemory(int index);                  // заделя посочено количество памет за вектора

    bool operator==(const Vector<T>& other) const;   // оператор, проверяващ дали два вектора са еднакви
    T& operator[](int) const;                        // оператор, достъпващ елемент на позиция
};


template <typename T>
void Vector<T>::copyVectors(const Vector& rhs) {
    arr = new(std::nothrow) T[rhs.storage];
    if (arr == nullptr) {
        throw std::runtime_error("No memory for vector!(Vector<T>::copyVectors())");
    }
    for (int i = 0; i < rhs.storage; i++) {
        arr[i] = rhs.arr[i];
    }
    storage = rhs.storage;
    count = rhs.count;
}

template <typename T>
void Vector<T>::deleteVector() {
    delete[] arr;
}

template <typename T>
Vector<T>::Vector() {
    arr = new(std::nothrow) T[1];
    if (arr == nullptr) {
        throw std::runtime_error("No memory for vector!(default constructor)");
    }
    storage = 1;
    count = 0;
}

template <typename T>
Vector<T>::Vector(int index) {
    arr = new(std::nothrow) T[index + 1];
    if (arr == nullptr) {
        throw std::runtime_error("No memory for vector!(constructor(int)");
    }
    storage = index + 1;
    count = 0;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhs) {
    copyVectors(rhs);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
    if (this == &rhs) return *this;
    deleteVector();
    copyVectors(rhs);
    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    deleteVector();
}

template <typename T>
void Vector<T>::add(const T& element) {
    if (storage == count) {
        T* temp = new(std::nothrow) T[2 * storage];
        if (temp == nullptr) {
            throw std::runtime_error("No memory for vector!(Vector<T>::add())");
            return;
        }
        for (int i = 0; i < storage; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        storage *= 2;
        arr = temp;
    }
    arr[count] = element;
    count++;
}

template <typename T>
void Vector<T>::pushAtIndex(const T& element, int index) {
    arr[index] = element;
}

template <typename T>
void Vector<T>::removeAtIndex(int i) {
    if (i<0 || i>count) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }

    Vector<T> tempVector(count - 1);
    int br = 0;
    for (int j = 0; j < i; j++) {
        tempVector[br] = arr[j];
        br++;
        tempVector.addToCount();
    }
    for (int j = i + 1; j < count; j++) {
        tempVector[br] = arr[j];
        br++;
        tempVector.addToCount();
    }

    *this = tempVector;
}

template <typename T>
int Vector<T>::getStorage() const {
    return storage;
}

template <typename T>
int Vector<T>::size() const {
    return count;
}

template <typename T>
void Vector<T>::print() const {
    for (int i = 0; i < count; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
    if (count != other.count) return false;
    for (int i = 0; i < count; i++) {
        if (arr[i] != other.arr[i]) return false;
    }
    return true;
}

template <typename T>
T& Vector<T>::operator[](int i) const {
    return arr[i];
}

template <typename T>
void Vector<T>::clear() {
    delete[] arr;
    arr = new(std::nothrow) T[1];
    if (arr == nullptr) {
        throw std::runtime_error("No memory for vector!(Vector<T>::clear())");
    }
    storage = 1;
    count = 0;
}

template <typename T>
void Vector<T>::allocateMemory(int index) {
    arr = new(std::nothrow) T[index + 1];
    if (arr == nullptr) {
        throw std::runtime_error("No memory for vector!(Vector<T>::allocateMemory())");
    }
    storage = index + 1;
    count = 0;
}

template <typename T>
void Vector<T>::addToCount() {
    count++;
}

#endif // VECTOR_H