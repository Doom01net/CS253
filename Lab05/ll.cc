#include "ll.h" 
#include <cstdlib>

LinkedList::LinkedList(): m_pHead(nullptr) {
}



bool LinkedList::insert(unsigned uiData) {
    Link* new_link = new Link;			// Get a new node.

    new_link->initialize(uiData, m_pHead); // Fill it with data.
    m_pHead = new_link;			// Put it at the head.

    return true;				// Indicate success.
}

void LinkedList::print(){
    // Link *nod = m_pHead;
    while(!m_pHead){
        cout 
    }
}
bool LinkedList::remove(unsigned &pData) {
    
    if (!m_pHead)				// Empty list?
	    return false;			// Indicate failure.
    
    Link *temp = m_pHead;			// Point to the first node.
    m_pHead = m_pHead->m_pNext;	// Remove the first node. this.heap
    pData = temp->m_uiData;			// Obtain first node’s data.
    delete(temp);
    return true;				// Indicate success.
}
