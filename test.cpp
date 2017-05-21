/*

    A test program that uses Garbage Collection. The program creates a circular linked list.
    Simple pointers are replaced with GCPtr and the type is passed as template parameter.
    To use Garbage Collection, include the header GC.h
    To see the GC log, use #define GC_LOG
        The Log is shown at every step when a GCPtr goes out of scope
    The user can explicitly call the printList() function anywhere in the program to see the current status
        e,g:    GCPtr <int>::printList()    OR GCPtr <float>::printList()
    For user defined types, when using GC_LOG, the user-defined type definition must overload the << operator to enable
    cout in printList() to print the contents of the user-defined type

    compile using:              g++ -o main GCNode.cpp GCPtr.cpp <your_program.cpp>
                                ./main

*/



#include <iostream>
#define GC_LOG
#include "GC.h"


using namespace std;

struct Node{
    int data;
    GCPtr <Node> next;
    Node(int data)
    {
        this->data=data;
        next=NULL;
    }
    friend ostream &operator<<( ostream &output, 
         const Node &D ) { 
         output << "data : " << D.data;
         return output;            
      }
    static GCPtr<Node> addNode(int data,GCPtr <Node> &start)
    {
        if(start==NULL)
        {
            start=new Node(data);
            start->next=start;
        }
        else
        {   
            GCPtr <Node> temp=start;
            cout<<"inside function\n";
            GCPtr<Node>::printList();
            while(temp->next!=start)
                temp=temp->next;
            temp->next=new Node(data);
            temp->next->next=start;
        }   
        return start; 
    }
};

int main()
{
    int * a=new int[10];
    //cout<<sizeof(a)<<endl;

    /*GCPtr <int,10> p;
    GCPtr <int,10> q=p;
    p=a;*/
    GCPtr<Node> start=NULL;
    start=Node::addNode(1,start);
    start=Node::addNode(2,start);
    start=Node::addNode(3,start);

    return 0;
}