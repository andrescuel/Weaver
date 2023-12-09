//
// Created by camil on 07/12/2023.
//

#include "List.h"

template<typename T>
List<T>:: List(): head(nullptr), count(0){
}

template<typename T>
List<T>:: ~List(){
    Node<T>* del = head;
    while (head){
        head = head->next;
        delete del;
        del = head;
    }
}

template<typename T>
Node<T>* List<T>::makeNode(const T &value) {
    Node<T>* temp = new Node<T>;
    temp->data = value;
    temp->next = 0;
    return temp;
}

template<typename T>
void List<T>::insert(int pos, const T &value) {
    if(pos < 0 || pos>count){
        cout << "Error! The position is out of range." << endl;
        return;
    }
    Node<T>* add = makeNode(value);
    if(pos == 0){
        add->next = head;
        head = add;
    }else{
        Node<T>* cur = head;
        for(int i=0; i<pos-1; i++){
            cur = cur->next;
        }
        add->next = cur->next;
        cur->next = add;
    }
    count++;
}

template<typename T>
void List<T>::erase(int pos) {
    if(pos < 0 || pos>count){
        cout << "Error! The position is out of range." << endl;
        return;
    }
    if(pos == 0){
        Node<T>* del = head;
        head = head->next;
        delete del;
    }else{
        Node<T>* cur = head;
        for(int i=0; i<pos-1; i++){
            cur = cur->next;
        }
        Node<T>* del = cur->next;
        cur->next = del->next;
        delete del;
    }
    count--;
}

template<typename T>
T& List<T>::get(int pos) const{
    if(pos < 0 || pos>count-1){
        cout << "Error! The position is out of range." << endl;
        assert(false);
    }
    if(pos == 0){
        return head->data;
    }else{
        Node<T>* cur = head;
        for(int i=0; i<pos; i++){
            cur = cur->next;
        }
        return cur->data;
    }
}

template<typename T>
void List<T>::print() const{
    if(count == 0){
        cout << "List is empty." << endl;
        return;
    }
    Node<T>* cur = head;
    while(cur){
        cout << cur->data;
        cur = cur->next;
    }
}

template<typename T>
int List<T>::size() const {
    return count;
}

template<typename T>
Node<T> *List<T>::search(const T &value) {
    Node<T>* cur = head;
    while(cur){
        if(cur->data == value) return cur;
        cur = cur->next;
    }
    return nullptr;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(nullptr);
}

template<typename T>
typename List<T>::ConstIterator List<T>::cbegin() const {
    return ConstIterator(head);
}

template<typename T>
typename List<T>::ConstIterator List<T>::cend() const {
    return ConstIterator(nullptr);
}

template class Node<string>;
template class List<string>;