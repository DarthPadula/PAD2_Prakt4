/* 
 * File:   mylist.cpp
 * Author: max
 *
 * Created on 20. November 2017, 16:52
 */

#include <cstdlib>
#include <iostream>
#include "mylist.hpp"
#include <stdexcept>
#include <string>

using namespace std;

void error(string s){
    throw runtime_error{s};
}

int main() {
    try{
    myList<int> list1;
    myList<int>::myIterator it{}; //Erzeugen eines myIterator Objekts
    list1.push_back(100); //Wert hinter den letzten Knoten speichern
    list1.push_back(9); //Wert hinter den letzten Knoten speichern
    list1.print(); //Ausgeben aller Knoten
    list1.ins(90,list1.findnode(100)); //Speichern eines Wertes hinter einen zu findenenden Knoten
    list1.print();
    list1.ins(80,list1.findnode(90));
    list1.print();
    list1.rem(list1.findnode(90)); //Löschen des Knotens mit dem value-Wert 90
    list1.print();
    it = list1.find(80,list1.begin(),list1.end()); //Finde den Knoten mit val = 80
    if(it != list1.end()) cout << "found: " << *it << endl; //Wenn ein Knoten entsprechend der Suche gefunden wurde, ausgeben
    list1.insert(9999,it); //Speichern eines Wertes hinter den gefundenen Knoten
    list1.print();
    list1.remove(it); //Löschen des oben gefundenen Knotens
    list1.print();
    return 0;
    }catch(exception &e){
        cerr << e.what() << endl;
        return -2;
    }catch(...){
        cerr << "\nUnknown Exception\n" << endl;
    return -1;
    }
}

