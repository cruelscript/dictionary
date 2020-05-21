#ifndef DICTIONARY_STACKLIST_H
#define DICTIONARY_STACKLIST_H

#include "Stack.h"

template <class T>
class StackList : public Stack<T>
{
public:
  StackList();
  virtual ~StackList();
  void	   push(const T& e) override;
  T	       pop()            override;
  T&       top()            override;
  bool	   isEmpty()        override;
private:
  class Node
  {
  public:
    Node(const T& data, Node* next) :
      data_(data), next_(next)
    {}
    T    data_;
    Node* next_;
  };
  Node* top_;
};

template <class T>
StackList<T>::StackList() : top_(nullptr)
{}

template<class T>
StackList<T>::~StackList()
{
  Node* temp;

  while (top_)
  {
    temp = top_;
    top_ = top_->next_;
    delete temp;
  }
  top_ = nullptr;
}

template<class T>
void StackList<T>::push(const T& e)
{
  Node* temp = new Node(e, top_);
  top_ = temp;
}

template<class T>
T StackList<T>::pop()
{
  if (isEmpty())
    throw StackUnderflow();
 
  T data = top_->data_;
  Node* temp = top_;
  top_ = top_->next_;
  delete temp;
  return data;
}

template <class T>
T& StackList<T>::top()
{
  return top_->data_;
}

template <class T>
bool StackList<T>::isEmpty()
{
  return !top_;
}
#endif
