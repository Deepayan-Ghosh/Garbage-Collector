/*

    Implementation of GCIterator, mainly consists of the operators that should work with an iterator

*/

#include <iostream>
#include "GCIterator.h"

using namespace std;
template <typename T>
T * GCIterator<T>::operator->()
{
    return ptr;
}

template <typename T>
T& GCIterator<T>::operator *()
{
    return *ptr;
}

template <typename T>
GCIterator<T> GCIterator<T>::operator++()
{
    ptr++;
    return *this;
}

template <typename T>
GCIterator<T> GCIterator<T>::operator--()
{
    ptr--;
    return *this;
}

template <typename T>
GCIterator<T> GCIterator<T>::operator++(int offset)
{
    T * temp=ptr;
    ptr++;
    return GCIterator<T>(temp,start,end);
}

template <typename T>
GCIterator<T> GCIterator<T>::operator--(int offset)
{
    T * temp=ptr;
    ptr--;
    return GCIterator<T>(temp,start,end);
}

template <typename T>
T& GCIterator<T>::operator [](int index)
{
    return ptr[index];
}

template <typename T>
bool GCIterator<T>::operator ==(GCIterator <T> ob)
{
    return ptr==ob.ptr;
}

template <typename T>
bool GCIterator<T>::operator !=(GCIterator <T> ob)
{
    return ptr!=ob.ptr;
}

template <typename T>
bool GCIterator<T>::operator >(GCIterator <T> ob)
{
    return ptr>ob.ptr;
}

template <typename T>
bool GCIterator<T>::operator >=(GCIterator <T> ob)
{
    return ptr>=ob.ptr;
}

template <typename T>
bool GCIterator<T>::operator <(GCIterator <T> ob)
{
    return ptr<ob.ptr;
}

template <typename T>
bool GCIterator<T>::operator <=(GCIterator <T> ob)
{
    return ptr<=ob.ptr;
}

template <typename T> 
GCIterator<T> GCIterator<T>::operator +(int n)
{
    ptr=ptr+n;
    return *this;
}

template <typename T> 
GCIterator<T> GCIterator<T>::operator -(int n)
{
    ptr=ptr-n;
    return *this;
}

template <typename T> 
int GCIterator<T>::operator -(GCIterator <T> ob)
{
    return ptr-ob.ptr;
}