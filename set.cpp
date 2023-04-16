#include "set.hpp"

// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ******************************************************** */

// Default constructor
Set::Set() : head(new Node(0, nullptr) )
{

}

// Constructor for creating a set from an int
Set::Set(int v): head{ new Node(0, nullptr) }
{
    // ADD CODE
    insert(head, v);
}
void Set::insert(Node* p, int v) {
    Node* newNode = new Node(v, p->next);
    p->next = newNode;
}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements  
Set::Set(const std::vector<int>& V) : head{ new Node(0, nullptr) } 
{     



    // ADD CODE
     for (int i = 0; i < V.size(); ++i) {

        Node* p = head; 

        while ((p->next != nullptr) && (V.at(i)> (p->next->value))) {
            p = p->next; 
        }
        if (p->next == nullptr || V.at(i) < (p->next->value)) {
            insert(p, V.at(i));
        }
        
        
    }
   
   
     
}


// copy constructor
Set::Set(const Set& source) : head{ new Node(0, nullptr) }
{
    // ADD CODE
    Node* p1 = source.head->next; // node to copy
    Node* p2 = head;

    while (p1 != nullptr) {
        insert(p2, p1->value);
        p1 = p1->next;
        p2 = p2->next;
    }
}

// Assignment operator: copy-and-swap idiom
Set& Set::operator=(Set s) {
    // ADD CODE
    //Set R(s);
    std::swap(head, s.head);
    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {
    // ADD CODE
    Node* p = head;

    while (p != nullptr) {
        head = p->next;
        delete p;
        p = head;
    }
}


// Return number of elements in the set
std::size_t Set::cardinality() const 
{   
    int howMany = 0;

    Node* p = head->next;

    while (p != nullptr) {
        ++howMany;
        p = p->next;
    }

    return howMany;
    // ADD CODE

    
}

// Test if set is empty
bool Set::empty() const {
    // ADD CODE
    if (head->next == nullptr) {
        return true;
    }
    else {
        return false;
    }

// delete if needed
}

// Test if x is an element of the set
bool Set::member(int x) const {
    // ADD CODE
    Node* p = head->next;

    while ((p != nullptr) && (p->value != x)) {
        p = p->next;
    }

    if (p == nullptr) {
        return false;
    }
    else {
        return true;
    }

}

bool Set::operator<=(const Set& b) const {
    // ADD CODE
    Node* p = head->next;

    while (p != nullptr) {
        if (!(b.member(p->value))) {
            return false;
        }
        p = p->next;
    }

    return true;

}

bool Set::operator==(const Set& b) const {
    // ADD CODE
    if (*this <= b) {
        if (b <= *this) return true; 
    }
    return false;
 // delete if needed
}

bool Set::operator!=(const Set& b) const {
    // ADD CODE
    //if (*this == b) return false; 
    return !(*this == b);

   
}

bool Set::operator<(const Set& b) const {
    // ADD CODE
    if (*this <= (b)) {
        if (!(b <= *this)) return true; 
    }
    return false;


}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
    // ADD CODE
    Set T{ b };

    Node* pt = T.head;
    Node* p = this->head->next;

    while (p != nullptr) {

        while ((pt->next != nullptr) && (p->value > pt->next->value)) {
            pt = pt->next;
        }

        if (T.member(p->value)) { 
            p = p->next;
        }
        else { 
            T.insert(pt, p->value);
        }
    }
    return T;

  // delete if needed
}

// Set intersection
Set Set::operator*(const Set& b) const {
    // ADD CODE
    Set T{};

    Node* pt = T.head;
    Node* p = head->next; 

    while (p != nullptr) {
        if (b.member(p->value)) {
            T.insert(pt, p->value);
            pt = pt->next; 
        }
        p = p->next; 
    }
    return T;

    // delete if needed
}

// Set difference
Set Set::operator-(const Set& b) const {
    // ADD CODE
    Set T{};

    Node* pt = T.head; 
    Node* p = head->next; 

    while (p != nullptr) {
        if (!(b.member(p->value))) { 
            T.insert(pt, p->value);
            pt = pt->next; 
        }
        p = p->next; 
    }
    return T;

 // delete if needed
}

// set difference with set {x}
Set Set::operator-(int x) const {
    // ADD CODE
    Set R(x); 
    Set T = this->operator-(R); 
         return T;
 
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/


