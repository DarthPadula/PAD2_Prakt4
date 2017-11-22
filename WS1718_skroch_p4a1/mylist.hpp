/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mylist.h
 * Author: max
 *
 * Created on 20. November 2017, 16:54
 */

#ifndef MYLIST_H
#define MYLIST_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

template<class Elem>
struct myNode { //Knotenkonstrukt
    myNode<Elem>* pre;
    myNode<Elem>* suc;
    Elem val;
    explicit myNode(const Elem& v = Elem{},
    myNode<Elem>* p = nullptr,
            myNode<Elem>* s = nullptr)
    : pre{p}, suc{s}, val{v}
    {
    }
};

template<class Elem>
class myList {
public:
    myList()
    : first{myNode<Elem>{}}, last{myNode<Elem>{}}, sz{0}
    {
        first.suc = &last;
        last.pre = &first;
    }

    ~myList() {
        myNode<Elem>* dp{first.suc};
        myNode<Elem>* tmp{nullptr};
        while (dp != &last) { //Lösche alle vorhandenen Knoten
            tmp = dp->suc;
            delete dp;
            dp = tmp;
        }
    }
    void push_back(const Elem&); //Neuen Knoten am Ende der Liste einfügen
    void pop_back(); //Letzten Knoten der Liste löschen
    void print(); //Ausgabe aller vals aller Knoten
    void push_front(const Elem&); //Neuen Knoten am Anfang der Liste einfügen
    void pop_front(); //Ersten Knoten der Liste löschen
    void ins(const Elem&, myNode<Elem>*); //Füge neuen Knoten hinter übergebenen Knoten ein
    myNode<Elem>* findnode(const Elem&); //Finde Knoten mit val = Parameter
    void rem(myNode<Elem>*); //Löschen des übergebenen Knotens
    class myIterator; //Vorabdeklaration der Klasse myIterator
    myIterator begin(); //Startiterator
    myIterator end(); //Enditerator
    myIterator find(const Elem&, myIterator, myIterator); //Iteriere und finde Wert
    void insert(const Elem&, myIterator); //Neuen Wert/Knoten hinter den übergebenen myIterator einfügen
    void remove(myIterator); //Übergebenen Knoten löschen
private:
    long int sz; //Größe der Liste
    myNode<Elem> first; //Erster Knoten
    myNode<Elem> last; //Letzter Knoten
};

template<class Elem>
class myList<Elem>::myIterator { //Spezialisierung der Vorabdeklaration
public:
    myIterator();
    explicit myIterator(myNode<Elem>*);

    myNode<Elem>* get_curr() const { //Hilfsfunktion 
        return curr;
    }
    myIterator& operator++(); //"Inkrementierung" des Iterators
    myIterator& operator--(); //"Dekrementierung" des Iterators
    Elem& operator*(); //Überlade Multiplikator als Rückgabefunktion für val
    bool operator==(const myIterator&) const; //Vergleichsoperatorüberladung
    bool operator!=(const myIterator&) const; //Vergleichsoperatorüberladung
private:
    myNode<Elem>* curr; //der aktuelle Knoten
};

template<class Elem>
myList<Elem>::myIterator::myIterator() {
    curr = nullptr; //Initialisiere beim Standardkonstruktor mit NULL
    if(curr != nullptr){
        throw runtime_error{"Initialisierung mit NULL nicht erfolgreich! (myIterator())"};
    }
}

template<class Elem>
myList<Elem>::myIterator::myIterator(myNode<Elem>* p) {
    curr = p;
    if(curr != p){
        throw runtime_error{"Initialisierung mit übergebenem Knoten nicht erfolgreich! (myIterator(myNode<Elem>*))"};
    }
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
typename myList<Elem>::myIterator& myList<Elem>::myIterator::operator++() {
    curr = curr->suc;
    return *this;
}

template<class Elem>
typename myList<Elem>::myIterator& myList<Elem>::myIterator::operator--() {
    curr = curr->pre;
    return *this;
}

template<class Elem>
Elem& myList<Elem>::myIterator::operator*() {
    return curr->val;
}

template<class Elem>
typename myList<Elem>::myIterator myList<Elem>::begin() {
    return myIterator{first.suc};
}

template<class Elem>
typename myList<Elem>::myIterator myList<Elem>::end() {
    return myIterator{&last};
}

template<class Elem>
typename myList<Elem>::myIterator myList<Elem>::find(const Elem& v, myIterator p, myIterator q) {
    while ((p != q) && (*p != v)) ++p;
    return p;
}

template<class Elem>
void myList<Elem>::insert(const Elem& v, myIterator p) {
    ins(v, p.get_curr()); //Verwendung der myList<Elem>::ins Funktion
}

template<class Elem>
void myList<Elem>::remove(myIterator p) {
    rem(p.get_curr()); //Verwendung der myList<Elem>::rem Funktion
}

template<class Elem>
void myList<Elem>::push_back(const Elem& v) { //Neuen Knoten am Ende der Liste anhängen
    myNode<Elem>* nn{new myNode<Elem>
        {v}};
    nn->suc = &last;
    nn->pre = last.pre;
    last.pre->suc = nn;
    last.pre = nn;
    ++sz;
}

template<class Elem>
void myList<Elem>::pop_back() { //Letzten Knoten der Liste löschen
    myNode<Elem>* temp{last.pre};
    if (temp == &first) return; //Liste ist schon leer
    last.pre = last.pre->pre;
    last.pre->suc = &last;
    delete temp;
    --sz;
}

template<class Elem>
void myList<Elem>::print() { //Ausgabe aller vals aller Knoten
    myNode<Elem>* printer{first.suc};
    if (printer == &last) {
        cout << "Die Liste ist leer!" << endl;
    }
    while (printer != &last) {
        cout << printer->val << endl;
        printer = printer->suc;
    }
    cout << endl;
}

template<class Elem>
void myList<Elem>::push_front(const Elem& v) { //Neuen Knoten am Anfang der Liste einfügen
    myNode<Elem>* nn{new myNode<Elem>
        {v}};
    nn->pre = &first;
    nn->suc = first.suc;
    first.suc->pre = nn;
    first.suc = nn;
    ++sz;
}

template<class Elem>
void myList<Elem>::pop_front() { //Ersten Knoten der Liste löschen
    myNode<Elem>* temp{first.suc};
    if (temp == &first) return; //Liste ist schon leer
    first.suc = first.suc->suc;
    first.suc->pre = &first;
    delete temp;
    --sz;
}

template<class Elem>
void myList<Elem>::ins(const Elem& v, myNode<Elem>* p) { //Füge neuen Knoten hinter p ein
    myNode<Elem>* nn{new myNode<Elem>
        {v}};
    nn->pre = p;
    nn->suc = p->suc;
    nn->suc->pre = nn;
    p->suc = nn;
    ++sz;
}

template<class Elem>
void myList<Elem>::rem(myNode<Elem>* p) { //Lösche den Knoten p
    p->suc->pre = p->pre;
    p->pre->suc = p->suc;
    delete p;
    --sz;
}

template<class Elem>
myNode<Elem>* myList<Elem>::findnode(const Elem& v) { //Finde Knoten mit val = v;
    myNode<Elem>* iter{first.suc};
    for (int i = 0; i < sz; i++) {
        if (iter->val == v)
            return iter;
        iter = iter->suc;
    }
    throw runtime_error("Nothing found");
}

#endif /* MYLIST_H */

