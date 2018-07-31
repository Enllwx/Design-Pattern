#ifndef iterator_hpp
#define iterator_hpp

#include <iostream>

class Node;
class List {
    Node *thelist = nullptr;
public:
    /*==------------------ Nested class ------------------==*/
    class Iterator {
        bool theEnd = 0;
        Node * p = nullptr;
        explicit Iterator(Node *ptr);
        explicit Iterator(bool theEnd, Node *ptr);
    public:
        int & operator*() const;
        Iterator & operator++();
        Iterator & operator--();
        Iterator & operator+=(int i);
        Iterator & operator-=(int i);
        bool operator >= ( const Iterator & other ) const;
        bool operator <= ( const Iterator & other ) const;
        bool operator == ( const Iterator & other ) const;
        bool operator != ( const Iterator & other ) const;
        
        friend class List;
    };
    /*==----------------- -------------- -----------------==*/
    
    Iterator begin();
    Iterator end();
    Iterator at(int i);
    
    int & ith(int i);
    int size();
    void remove(int n);
    void remove(Iterator i);
    
    int & operator[](int i);
    ~List();
};


#endif /* iterator_hpp */
