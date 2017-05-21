/*

    implementation of functions GCNode.h

*/

#include <iostream>
#include "GCNode.h"
using namespace std;

template <typename T>
GCNode <T> ::GCNode(T * actualPtr,unsigned int size)    //constructor
{
        this->refCount=1;                               //refCount initialised to 1
        this->actualPtr=actualPtr;                      //actualPtr holds address of actual allocated memory
        arraySize=size;                                 //array size defaults to 0
        if(size==0)                                     //if size is zero, isArray is false
            isArray=false;
        else
            isArray=true;
}

template <typename T>
bool GCNode<T>::operator ==(const GCNode <T> &ob)       
{       
    return (this->actualPtr==ob.actualPtr);             //checks if both pointers points to same memory
}