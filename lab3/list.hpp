// node class tempate used to contruct lists
// Erik Wood
// Due 9/13/2024

#ifndef LIST_HPP_
#define LIST_HPP_

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
public:

  node(): next_(nullptr) {} // defualt constructor

  // functions can be inlined
  T getData() const {return data_;}
  void setData(const T& data){data_ = data;}

  // or can be defined outside
  node<T>* getNext() const;
  void setNext(node<T> *const);

private:
  T data_;
  node<T> *next_;
};

//
// member functions for node
//
template <typename T>
node<T>* node<T>::getNext() const {
  return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next){
   next_=next;
}

template <typename T>
class Collection{
  public:
    Collection();
    void add   (T data);
    void remove(T data);
    T    last  () const;
    void print () const;

    template <typename U>
    friend bool equal(const Collection<U>& c1, const Collection<U>& c2);

  private:
    node<T> *head;
    node<T> *tail;
    int size;
};

#endif // LIST_HPP_