/*

    Implementation of GCPtr.h

*/

#include <iostream>
#include "GCIterator.h"
#include <stdlib.h>
#include "GCPtr.h"

using namespace std;


//constructor for the case when a GCPtr is being instantiated with value addr, which defaults to NULL
//e.g:          GCPtr <int> p(new int(10))

template <typename T,int size>
GCPtr<T,size>:: GCPtr(T * addr)
{
    if(firstNode)
        atexit(exitAtEnd);          //registers exitAtEnd() to be called during exiting of main method
    firstNode=false;
    typename list<GCNode<T> >::iterator p=findNode(addr);
    if(p!=gclist.end())
        p->refCount++;
    else
    {
        GCNode<T> obj(addr,size);
        gclist.push_front(obj);
    }
    currAddr=addr;
    arraySize=size;
    if(size>0)
        isArray=true;
    else
        isArray=false;
}

//copy contructor for the case when a GCPtr is being constructed from existing GCPtr instance
//e,g:          GCPtr <int> q=p;


template <typename T,int size>
GCPtr<T,size>:: GCPtr(const GCPtr &ob)
{
    typename list<GCNode<T> >::iterator p;
    p=findNode(ob.currAddr);
    p->refCount++;
    
    currAddr=ob.currAddr;
    arraySize=ob.arraySize;
    if(arraySize>0)
        isArray=true;
    else
        isArray=false;
}

//Destructor: called when a GCPtr instance goes out of scope. Does the main garbage collection by calling collect()

template <typename T,int size>
GCPtr<T,size>:: ~GCPtr()
{
    #ifdef GC_LOG
    cout<<"\nwhile desctructing, that is, going out of scope, before collection:"<<endl;
    printList();
    #endif

    typename list<GCNode<T> >::iterator p;
    p=findNode(currAddr);
    
    if(p->refCount)
        p->refCount--;
    
  
    collect();

    #ifdef GC_LOG
    cout<<"\nwhile desctructing, that is, going out of scope,after collection"<<endl;
    printList();
    #endif
}

//  collect(): responsible for sweeping or freeing the memory whose reference count drops to zero, that is,
//  they become unreachable (since they are not being refered)

template <typename T,int size>
bool GCPtr<T,size>::collect()
{
    bool freed=false;
     
    typename list<GCNode<T> >::iterator p;

    do
    {
        for(p=gclist.begin();p != gclist.end(); p++)
        {
            if(p->refCount > 0)
                continue;
            
            freed=true;

            gclist.remove(*p);
            if(p->actualPtr)
            {
                if(p->isArray)
                {
                    delete[] p->actualPtr;
                }
                else
                {
                    delete p->actualPtr;
                }
            }
            break;
        }
    }while(p!=gclist.end());

    return freed;
}

//if the allocated memory is an array then to iterate over that array an iterator is used
//begin() returns a GCIterator to the beginning of allocated array, while end() returns to the end

template <typename T,int size>
GCIterator<T> GCPtr<T,size>::begin()
{
    int _size;
    if(isArray) 
        _size = arraySize;
    else 
        _size = 1;
    return GCIterator<T>(currAddr, currAddr, currAddr + _size);
}

template <typename T,int size>
GCIterator<T> GCPtr<T,size>::end()
{
     int _size;
    if(isArray) 
        _size = arraySize;
    else 
        _size = 1;
    return GCIterator<T>(currAddr+_size, currAddr, currAddr + _size);
}

// during collection or instantiation of new GCPtr, it becomes necessary to check whether the new memory being
// allocated is already present in list or not. For this purpose, findNode() is used which iterates through all 
// GCNode instances in the list, check their actualPtr and if it matches it returns a list<GCNode<T> >::iterator

template <typename T,int size>
typename list<GCNode<T> >::iterator GCPtr<T,size>::findNode(T * addr)
{
    typename list<GCNode<T> >::iterator p;
    for(p=gclist.begin();p!=gclist.end();p++)
    {
        if(p->actualPtr==addr)
            return p;
    }
    return p;
}

//overloading the operators, for simulating behaviors of original pointers
//e.g:  GCPtr <int> p=new int(10);
//      cout<<*p<<endl;                 //must print 10, so * operator is overloaded

template <typename T,int size>
T * GCPtr<T,size>::operator=(T * ptr)           //assignment operator: GCPtr <int> p; p=new int(10)
{
    typename list<GCNode<T> >::iterator p;

    p=findNode(currAddr);
    p->refCount--;

    p=findNode(ptr);
    if(p!=gclist.end())
        p->refCount++;
    else
    {
        GCNode<T> obj(ptr,size);
        gclist.push_front(obj);
    }

    currAddr=ptr;
    return ptr;
}

template <typename T,int size>
GCPtr<T,size>& GCPtr<T,size>::operator=(GCPtr &ptr) //GCPtr<int> p; p=new int(10); GCPtr <int> q; q=p;
{
    typename list<GCNode<T> >::iterator p;

    p=findNode(currAddr);
    p->refCount--;

    p=findNode(ptr.currAddr);
    p->refCount++;
  
    currAddr=ptr.currAddr;
    return ptr;
}

template <typename T,int size>
T & GCPtr<T,size>::operator *()                     //derefernces a GCPtr to give actual value
{
    return *currAddr;
}

template <typename T,int size>
T * GCPtr<T,size>::operator ->()                    //returns address of currently pointed memory
{
    return currAddr;
}

template <typename T,int size>
T & GCPtr<T,size>::operator [](int i)               //to enable subscripting of GCPtr pointers
{
    return currAddr[i];
}

template <typename T, int size>
GCPtr<T,size>::operator T*()
{
    return currAddr;
}

//returns size of list that is the number of memory locations currently in memory (recheable, unreachable both)

template <typename T,int size>
int GCPtr<T,size>::listSize()
{
    return gclist.size();
}

//prints the list in a format like {address, reference count, value at location, arraySize(if any else zero)}

template <typename T,int size>
void GCPtr<T,size>::printList()
{
        cout<<"List size:"<<listSize()<<endl;
        typename list<GCNode<T> >::iterator p;
        cout<<"[ ";
        if(gclist.begin()==gclist.end())
        {
            cout<<"Empty ]"<<endl;
            return;
        }
        else
        {
            for(p=gclist.begin();p!=gclist.end();p++)
            {
                if(p->actualPtr)
                    cout<<"{ "<<p->actualPtr<<","<<p->refCount<<","<<*(p->actualPtr)<<","<<p->arraySize<<" }, ";
                else
                    cout<<"{ NULL"<<","<<p->refCount<<" }";
            }
            cout<<" ]"<<endl<<endl<<endl;
        }
}

//the function which is called to get rid of pointers that are not freed during lifetime of program
//like circular references, by setting all existing pointers' refCount to zero and then calling collect()

template <typename T,int size>
void GCPtr<T,size>::exitAtEnd()
{
    #ifdef GC_LOG
    cout<<"while exiting the program\n";
    printList();
    #endif

    if(listSize()==0)
        return;
   
    typename list<GCNode<T> >::iterator p;

    for(p=gclist.begin();p!=gclist.end();p++)
    {
        p->refCount=0;
    }
    collect();
}