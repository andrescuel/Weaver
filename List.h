//
// Created by camil on 07/12/2023.
//

#ifndef WEAVER_LIST_H
#define WEAVER_LIST_H

#include <iostream>
#include <cassert>
using namespace std;

template<typename T>
struct Node{
    T data;
    Node<T>* next;
};

template<typename T>
class List {
private:
    Node<T>* head;
    int count;
    Node<T>* makeNode(const T& value);
public:
    // Clases iteradoras (wtf? structs dentro de clases)
    struct Iterator;
    struct ConstIterator;

    // Funciones iteradoras
    Iterator begin() const;
    Iterator end() const;

    // Funciones iteradores constantes
    ConstIterator cbegin() const;
    ConstIterator cend() const;

    List();
    ~List();
    void insert(int pos, const T& value);
    void erase(int pos);
    T& get(int pos) const;
    void print() const;
    int size() const;
    Node<T>* search(const T& value);
};

template<typename T>
struct List<T>::Iterator {
private:
    Node<T>* current;

public:
    Iterator(Node<T>* node) : current(node) {}

    T& operator*() const {
        return current->data;
    }

    typename List<T>::Iterator& operator++() {
        current = current->next;
        return *this;
    }

    bool operator!=(const typename List<T>::Iterator& other) const {
        return current != other.current;
    }
};

template<typename T>
struct List<T>::ConstIterator {
private:
    const Node<T>* current;

public:
    ConstIterator(const Node<T>* node) : current(node) {}

    const T& operator*() const {
        return current->data;
    }

    ConstIterator& operator++() {
        current = current->next;
        return *this;
    }

    bool operator!=(const ConstIterator& other) const {
        return current != other.current;
    }
};

#endif //WEAVER_LIST_H
