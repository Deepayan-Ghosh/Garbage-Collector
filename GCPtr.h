/*

    This simple garbage collector is based on reference count algorithm.

    GCPtr maintains a static list of wrapped-up pointers for each type that is, for int pointers it maintains seperate list,
    and for float pointers, seperate. It is a generalised garbage-collecting pointer which is used to implement GC.
    Each time a new instance of GCPtr is created, it is first checked whether the address to which the GCPtr will be made 
    to point already exists in the list or not, if it exists then the reference count is incremented else a new GCNode 
    wrapper is made. Similarly each time a GCPtr goes out of scope the collect() method is called.

    The collect method checks through all the references whose reference count is 0, and removes them.
    
    Drawback of reference-count GC is circular references. In this case, it has been overcome by calling a function 
    exitAtEnd() while termination of program, which makes the reference count of all remaining pointers to zero and 
    calling collect() one last time.

*/
#ifndef GCPTR_H                                 //include guard
#define GCPTR_H

#include <iostream> 
#include <list>         
#include "GCNode.h"
using namespace std;

template <typename T,int size=0>           //generic class GCPtr simulates a GC enabled pointer
class GCPtr
{
    static list <GCNode<T> > gclist;      //a static list is maintained and each new pointer is wrapped in GCNode instance and pushed into list
    T * currAddr;                         //stores memory address of block where the GCPtr is currently pointing
    unsigned int arraySize;               //arraySize stores size if allocated memory is array, else defaults to 0  
    bool isArray;
    static bool firstNode;                //tracks whether the GCPtr is first or not
    typename list <GCNode<T> >::iterator findNode(T * addr);
    public:
            GCPtr(T * addr=NULL);        
            GCPtr(const GCPtr &ob);
            ~GCPtr();
            static bool collect();
            T * operator=(T * ptr);
            GCPtr &operator=(GCPtr &ob);
            T &operator *();
            T *operator ->();
            T &operator[](int i);
            operator T*();
            GCIterator<T> begin();
            GCIterator<T> end();
            static int listSize();
            static void printList();
            static void exitAtEnd();
};

//global declaration of static variables

template <typename T, int size>
list<GCNode<T> > GCPtr <T,size>::gclist;

template <typename T,int size>
bool GCPtr <T,size>::firstNode=true;
#endif