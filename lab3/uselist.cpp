// demoes list template usage
// Due 9/13/2024
// Erik Wood

#include <iostream>
#include "list.hpp" // list template
#include <cassert>
#include <string>

using std::cout; using std::endl;
using std::string;
/*
int main(){
   node<int> *head, *currentPtr;

   // 
   // integer list manipulation
   // 

   // first node
   head =new node<int>;
   head->setData(1);


   currentPtr=new node<int>;  // second node
   currentPtr->setData(2);

   head->setNext(currentPtr); // list contains two nodes

   cout << head->getData() << " "; // printing head node

   // deallocating head node
   currentPtr=head;
   head=head->getNext();
   delete currentPtr;

   // printing and deallocating the last element
   cout << head->getData() << endl;
   delete head;


   // 
   // character list manipulation
   // 
   
   // allocating head node
   node<char> *charHead = new node<char>;
   node<char> *current = charHead;
   current->setData('A');

   // creating list
   for(char letter = 'B'; letter <= 'Z'; ++letter){
      node<char> *const newNode = new node<char>;
      newNode->setData(letter);
      current->setNext(newNode);
      current = newNode;
   }


   for(current = charHead;  current != nullptr; current=current->getNext())
     cout << current->getData() << ' ';
   cout << endl;
}
*/

int main(){

    // manipulating integers
   Collection<int> cone, emptyCol;
   cout << "Integer collection: ";
   cout << "adding 1 ";  cone.add(1);
   assert(cone.last() == 1);
   cout << "adding 2 ";  cone.add(2);
   assert(cone.last() == 2);
   cout << "adding 3 ";  cone.add(3);
   assert(cone.last() == 3);
   cout << "adding duplicate 2 "; cone.add(2);
   assert(cone.last() == 2);
   cout << endl;
   
   cone.print();

   cout << "removing 2 " ; cone.remove(2);
   cout << endl;;

   cone.print();

   assert(cone.last() == 3);
   assert(equal(cone, cone));
   cone.remove(3);
   cone.remove(1);
   
   assert(equal(cone, emptyCol));
   // uncomment when you debugged the code above
   

   // manipulating strings
   string sa[] = {"yellow", "orange", "green", "blue"};
   Collection<string> ctwo;

   cout << "adding an array of strings " << endl;
   for(auto s : sa){
      ctwo.add(s);
   }

   cout << "String collection: ";
   ctwo.print();


   // manipulating character collections

   // individal collections
   Collection<char> a2g, h2n, o2u;
   cout << "Populating individual character collections" << endl;
   for(char c='a'; c <='g'; ++c) {
      a2g.add(c);
      assert(a2g.last() == c);
   }
   for(char c='h'; c <='n'; ++c) h2n.add(c);
   for(char c='o'; c <='u'; ++c) o2u.add(c);

   
   assert(!equal(a2g, h2n));

   // collection of collections
   Collection<Collection<char>> cpile;

   cout << "Adding individual collections " << endl;
   cpile.add(a2g);
   assert(equal(cpile.last(), a2g));
   cpile.add(h2n);
   assert(equal(cpile.last(), h2n));
   cpile.add(o2u);
   assert(equal(cpile.last(), o2u));

   // printing characters from last collection added
   cout << "Last added character collection: ";
   cpile.last().print();
   
}

template <typename T>
Collection<T>::Collection(){
   head = nullptr;
   tail = nullptr;
   size = 0;
}

template <typename T>
void Collection<T>::add(T data){
   node<T>* newNode = new node<T>();
   newNode->setData(data);
   newNode->setNext(nullptr);

   if(size == 0){
      this->head = newNode;
      this->tail = newNode;
   } else {
      this->tail->setNext(newNode);
      this->tail = newNode;
   }
   size++;
}

template <typename T>
void Collection<T>::remove(T data){
   if(size == 0){
      return; // empty list
   }

   while(head != nullptr && head->getData() == data){ // casees where data needs to be removed at the head node
      node<T>* temp = head;
      head = head->getNext();
      delete temp;
      size--;
   }

   if(size == 0){ // check if the list is now empty after the while loop above
      this->tail == nullptr;
   } else {
      node<T>* curr = this->head;
      node<T>* prev = nullptr;

      while(curr != nullptr){
         if(curr->getData() == data){
            prev->setNext(curr->getNext()); // assigns current's next to prev's next
            if(curr == tail){ // checking to assigning tail if we are at the end of the list
               tail = prev;
            }
            node<T>* temp = curr; // assigns curr the temp to delete it
            curr = curr->getNext();
            delete temp;
            size--; 
         }  else { // if current's data != the argument data then we will +1 the iterator to go throught the tree
            prev = curr; 
            curr = curr->getNext(); 
         }
      }
   }
}

template <typename T>
T Collection<T>::last() const {
   if(size == 0){ // protects aginst trying to get last when there is an empty list
      throw std::runtime_error("Collection has nothing in it.");
   }

   return tail->getData();
}

template <typename T>
void Collection<T>::print() const {
   node<T>* curr = head;
   while(curr != nullptr){
      std::cout << curr->getData() << " ";
      curr = curr->getNext(); // increment the curr pointer to the next node
   }
   std::cout << std::endl;
}

template <typename U>
bool equal(const Collection<U>& c1, const Collection<U>& c2){
   if(c1.size != c2.size){
      return false;
   }

   node<U>* n1 = c1.head;
   node<U>* n2 = c2.head;

   while(n1 != nullptr) {
      if(n1->getData() != n2->getData()){
         return false;
      }
      n1 = n1->getNext();
      n2 = n2->getNext();
   }
   return true;
}

