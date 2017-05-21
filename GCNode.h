/*

    This class encapsulates or acts as a wrapper for the originial pointer, and associates a counter with each pointer,
    which counts the number of references, at any point of time in the program, referring to the same memory space as 
    the current wrapped memory space.

    GCNODE_H is a preprocessor directive which acts as include-guard for this particular file

*/
#ifndef GCNODE_H
#define GCNODE_H

#include <iostream>
using namespace std;

template <typename T> class GCNode              //templated class to wrap generic pointer
{
    public: T * actualPtr;                      //actual pointer which points to allocated space
    int refCount;                               //counts the number of references pointing to current memory block
    bool isArray;                               //isArray is true, when actualPtr points to an arraySize
    int arraySize;                              //if allocated space is array, then this holds the arraysize

    public:
            GCNode(T * actualPtr,unsigned int size=0);  //constructor for wrapper-pointer, arraysize defaults to zero
            bool operator ==(const GCNode<T> &ob);      //overload is necessary for being added to the list maintained by the GC
};
#endif