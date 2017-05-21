/*

    The main use of IteGCIterator is to enable you to cycle through
    the elements of a dynamically allocated array (if any). User can obtain GCIterator 
    from GCPtr by calling either begin( ) or end( ) if GCptr. It behaves similar to their counterparts 
    as in STL. All pointers have been overloaded to simulate the behavior of iterator in STL.

*/


#ifndef GCITER_H
#define GCITER_H

#include <iostream>

template <typename T>
class GCIterator
{
    T * ptr;
    T * start;
    T * end;
    int size;

    public:
            GCIterator()
            {
                ptr=start=end=NULL;
                size=0;
            }

            GCIterator(T * addr,T * s, T * e)
            {
                ptr=addr;
                start=s;
                end=e;
                size=end-start;
            }
            T& operator*(); 
            T* operator->();
            GCIterator<T> operator ++();
            GCIterator<T> operator --();
            GCIterator<T> operator ++(int offset);
            GCIterator<T> operator --(int offset);
            T& operator [](int index);
            bool operator ==(GCIterator <T> ob);
            bool operator !=(GCIterator <T> ob);
            bool operator >(GCIterator <T> ob);
            bool operator >=(GCIterator <T> ob);
            bool operator <(GCIterator <T> ob);
            bool operator <=(GCIterator <T> ob);
            GCIterator<T> operator +(int n);
            GCIterator<T> operator -(int n);
            int operator -(GCIterator <T> ob);
};
#endif