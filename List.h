#ifndef DICTIONARY_LIST_HPP
#define DICTIONARY_LIST_HPP

#include <sstream>
#include <algorithm>

template <class T>
class List
{
public:
  List() = default;
  List(List<T>&& other)noexcept;
  ~List();
  List<T>& operator=(List<T>&& other)noexcept;
  void insertHead(T data);
  void insertTail(T data);
  bool insert(T data);
  bool splitInsert(T data);
  void print(std::ostream& out);
private:
  class Node
  {
  public:
    explicit Node(T data, Node* next) :
      data_(data),
      next_(next)
    {}
    T data_;
    Node* next_;
  };
  Node* head_;
  Node* tail_;
};

template <class T>
List<T>::List(List<T>&& other) noexcept :
  head_(other.head_),
  tail_(other.tail_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template <class T>
List<T>::~List()
{
  while(head_)
  {
    Node* temp = head_;
    head_ = head_->next_;
    delete temp;
  }
}

template <class T>
List<T>& List<T>::operator=(List<T>&& other) noexcept
{
  if(this == &other)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    return *this;
  }
  List<T> copy(std::move(other));
  std::swap(head_, copy.head_);
  std::swap(head_, copy.head_);
  return *this;
}

template <class T>
void List<T>::insertHead(T data)
{
  if(!head_)
  {
    head_ = new Node(data, nullptr);
    tail_ = head_;
    return;
  }
  head_ = new Node(data, head_);
}

template <class T>
void List<T>::insertTail(T data)
{
  if(!tail_)
  {
    tail_ = new Node(data, nullptr);
    head_ = tail_;
    return;
  }
  tail_->next_ = new Node(data, nullptr);
}

template <class T>
bool List<T>::insert(T data)
{
  if(!head_)
  {
    insertHead(data);
    return true;
  }
  Node* current = head_;

  while(current)
  {
    if(data > current->data_)
    {
      if(current == tail_)
      {
        insertTail(data);
        return true;
      }
      current = current->next_;
    }
    if(data < current->data_)
    {
      std::swap(current->data_, data);
      if(!current->next_)
      {
        current->next_ = new Node(data, current->next_);
        tail_ = current->next_;
      }
      else
      {
        current->next_ = new Node(data, current->next_);
      }
      return true;
    }
    if(data == current->data_)
    {
      return false;
    }
  }
  return false;
}

template <class T>
bool List<T>::splitInsert(T line)
{
  bool result;
  size_t countTranslations = 0;
  size_t countRepeatedTranslations = 0;
  std::stringstream strin(line);
  std::string item;
  const char delim = ';';

  while(std::getline(strin, item, delim))
  {
    result = insert(item);
    countTranslations++;
    if(!result)
    {
      countRepeatedTranslations++;
    }
  }
  if(countTranslations == countRepeatedTranslations)
  {
    std::cout << "All added translations have already been inserted.\n";
    return false;
  }
  return true;
}

template <class T>
void List<T>::print(std::ostream& out)
{
  if(!head_)
  {
    out << "No translations available";
    return;
  }
  Node* temp = head_;

  while(temp)
  {
    out << temp->data_;
    if(temp->next_)
    {
      out << "; ";
    }
    temp = temp->next_;
  }
}

#endif
