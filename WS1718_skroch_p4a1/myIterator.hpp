/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myIterator.hpp
 * Author: max
 *
 * Created on 21. November 2017, 19:15
 */

#ifndef MYITERATOR_HPP
#define MYITERATOR_HPP


template<class Elem>
class myList<Elem>::myIterator {
public:
    myIterator();
    explicit myIterator(myNode<Elem>*);

    myNode<Elem>* get_curr() const {
        return curr;
    }
    myIterator& operator++();
    myIterator& operator--();
    Elem& operator*();
    bool operator==(const myIterator&) const;
    bool operator!=(const myIterator&) const;
private:
    myNode<Elem>* curr; //der aktuelle Knoten
};

template<class Elem>
myList<Elem>::myIterator::myIterator() {
    curr = nullptr;
}

template<class Elem>
myList<Elem>::myIterator::myIterator(myNode<Elem>* p) {
    curr = p;
}

template<class Elem>
bool myList<Elem>::myIterator::operator==(const myList<Elem>::myIterator& other) const {
    return curr == other.curr;
}

template<class Elem>
bool myList<Elem>::myIterator::operator!=(const myList<Elem>::myIterator& other) const {
    return curr != other.curr;
}

template<class Elem>
typename myList<Elem>::myIterator& myList<Elem>::myIterator::operator++(){
    curr = curr->suc;
    return *this;
}

template<class Elem>
typename myList<Elem>::myIterator& myList<Elem>::myIterator::operator--(){
    curr = curr->pre;
    return *this;
}

template<class Elem>
Elem& myList<Elem>::myIterator::operator*(){
    return curr->val;
}

template<class Elem>
typename myList<Elem>::myIterator myList<Elem>::begin(){
    return myIterator{first.suc};
}

template<class Elem>
typename myList<Elem>::myIterator myList<Elem>::end(){
    return myIterator{&last};
}

template<class Elem>
typename myList<Elem>::myIterator myList<Elem>::find(const Elem& v, myIterator p, myIterator q){
    while((p!=q) && (*p != v) ) ++p;
    return p;
}

template<class Elem>
void myList<Elem>::insert(const Elem& v, myIterator p){
    ins(v,p.get_curr());
}

template<class Elem>
void myList<Elem>::remove(myIterator p){
    rem(p.get_curr());
}

#endif /* MYITERATOR_HPP */

