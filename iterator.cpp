#include "iterator.hpp"
#include <iostream>
#include <memory>
using namespace std;

class Node {
public:
    int data = 0;
    Node *prev = nullptr;
    Node *next = nullptr;
    
    Node(int data = 0, Node * prev = nullptr, Node * next = nullptr)
        : data{data}, prev{prev}, next{next}{}
    ~Node(){ delete next; }
};

// ctor
List::Iterator::Iterator(Node *p): p{p}{}
// ctor (this will be call for the last iterator)
List::Iterator::Iterator(bool theEnd, Node *p): theEnd{theEnd}, p{p}{} 
int & List::Iterator::operator*() const{ return p->data; }

List::Iterator & List::Iterator::operator++() 
{   
    // if already at the end
    if (this->theEnd) return *this;
    
    // if next is the end
    if (p->next != nullptr){ theEnd = true; return *this; }
    
    // otherwise
    p = p->next;
    return *this;
}

List::Iterator & List::Iterator::operator--()
{
    // check if the node is the begin
    if (p->prev == nullptr) return *this;
    p = p->prev;
    return *this;
}

List::Iterator & List::Iterator::operator+=(int i)
{
    for (int j=0; j<i; j++) ++(*this);
    return *this;
}

List::Iterator & List::Iterator::operator-=(int i)
{
    for (int j=0; j<i; j++) --(*this);
    return *this;
}

bool List::Iterator::operator >= ( const Iterator & other ) const
{
    Node *current = this->p;

    while (current){
        if (current == other.p) return true;
        // check if the node is in front of current
        current = current->prev;        
    }   
    return false;
}

bool List::Iterator::operator <= ( const Iterator & other ) const
{
    Node *current = this->p;

    while (current){
        if (current == other.p) return true;
        // check if the node is behaved current
        current = current->next;
    }
    return false;
}

bool List::Iterator::operator == ( const Iterator & other ) const
{ return (this->p == other.p); }
bool List::Iterator::operator != ( const Iterator & other ) const
{ return (this->p != other.p); }

List::Iterator List::begin(){ return Iterator(this->thelist); }

List::Iterator List::end()
{
    Node * current = this->thelist;
    while (current){
        if (current->next == nullptr) break;
    }
    return Iterator(true, current);
}

List::Iterator List::at(int i)
{
    Node * current = this->thelist;
    for (int j=0; j<i; j++){
        current = current->next;
    }
    return Iterator(current);
}

int & List::ith(int i){ return ((this->at(i)).p)->data; }

// assume ith node is in theList
void List::remove(int i){
    Node * prevNode = nullptr;
    Node * currNode = this->thelist;
    Node * nextNode = nullptr;

    for (int j=0; j<i; i++){
        if (currNode == nullptr) return;
        prevNode = currNode;
        currNode = currNode->next;
    }
    
    if (!currNode) return;
    nextNode = currNode->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    delete currNode;
    return;
}                                                       

void List::remove(Iterator it)
{
    Node * prevNode = it.p->prev;
    Node * currNode = it.p;
    Node * nextNode = it.p->next;
    
    if (!currNode) return;
    if (!prevNode){
        this->thelist = nextNode;
        delete currNode;
        return;
    }

    nextNode = currNode->next;
    nextNode->prev = prevNode;
    prevNode->next = nextNode;
    delete currNode;
    return;
}

int List::size(){
    int counter = 0;
    Node * currNode = this->thelist;
    while (currNode){
        counter++;
        currNode = currNode->next;
    }
    return counter;
}

int & List::operator[](int i)
{
    Node * currNode = this->thelist; 
    for (int j=0; j<i; j++){
        currNode = currNode->next;
    }
    return currNode->data;
}

List::~List(){ delete thelist; }
