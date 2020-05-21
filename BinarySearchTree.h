#ifndef DICTIONARY_BINARYTREESEARCH_HPP
#define DICTIONARY_BINARYTREESEARCH_HPP

#include <string>
#include "List.h"
#include "StackList.h"
#include <algorithm>

bool isEnglishWord(std::string word);
bool isRussianWord(std::string word);

template <class T>
class BinaryTreeSearch
{
  class Node
  {
  public:
    Node() = default;
    Node(const T& word);
    void printNode(std::ostream& out) const;
    bool splitInsert(const T& line);
    T         word_;
    Node*     left_;
    Node*     right_;
    List<T>*  translations_;
  };
  Node* root_;
public:
            BinaryTreeSearch();
  explicit  BinaryTreeSearch(unsigned int size);
            ~BinaryTreeSearch();
  Node*     createOrderedTree(int begin, int end);
  bool      insert(std::istream& in);
  bool      insert(const T& word, const T& translation);
  Node*     search(const T& word) const;
  Node*     successor(const T& word, Node* parent)const;
  bool      deleteWord(const T& word);
  void      print(std::ostream& out)                const;
  void      print(std::ostream& out, const T& word) const;
  void      clear(Node* node);
};

template<class T>
BinaryTreeSearch<T>::Node::Node(const T& word) :
  word_(word),
  left_(nullptr),
  right_(nullptr),
  translations_(new List<T>)
{}

template<class T>
void BinaryTreeSearch<T>::Node::printNode(std::ostream& out) const
{
  if(this)
  {
    left_->printNode(out);
    out << word_ << " - ";
    translations_->print(out);
    out << "\n";
    right_->printNode(out);
  }
}

template <class T>
bool BinaryTreeSearch<T>::Node::splitInsert(const T& line)
{
  bool result = true;
  auto pos = line.find(" - ");

  if(pos != std::string::npos)
  {
    std::string word = line.substr(0, pos);
    std::string translations = line.substr(pos + 3);
    word_ = word;
    result = translations_->splitInsert(translations);
  }
  return result;
}

template<class T>
BinaryTreeSearch<T>::BinaryTreeSearch() :
  root_(nullptr)
{}

template<class T>
BinaryTreeSearch<T>::BinaryTreeSearch(unsigned int size)
{
  root_ = createOrderedTree(1, size);
}

template <class T>
BinaryTreeSearch<T>::~BinaryTreeSearch()
{
  clear(root_);
}

template<class T>
typename BinaryTreeSearch<T>::Node* BinaryTreeSearch<T>::createOrderedTree(int begin, int end)
{
  if(begin > end)
    return nullptr;

  int mid = begin + (end - begin) / 2;
  Node* temp = new Node;
  temp->translations_ = new List<T>;

  temp->left_ = createOrderedTree(begin, mid - 1);
  temp->right_ = createOrderedTree(mid + 1, end);
  return temp;
}

template<class T>
bool BinaryTreeSearch<T>::insert(std::istream& in)
{
  bool result = true;
  StackList<Node*> stack;
  Node* temp = root_;

  while((temp || !stack.isEmpty()) && !in.eof())
  {
    if(temp)
    {
      stack.push(temp);
      temp = temp->left_;
    }
    else
    {
      temp = stack.pop();

      std::string line;
      std::getline(in, line);
      result = temp->splitInsert(line);

      temp = temp->right_;
    }
  }
  return result;
}

template<class T>
bool BinaryTreeSearch<T>::insert(const T& word, const T& translations)
{
  if(!isEnglishWord(word))
  {
    std::cout << "\nThe entered word " << word << " is not an english word\n ";
    return false;
  }
  if(!isRussianWord(translations))
  {
    std::cout << "\nThe entered translations " << translations << " are not russian words\n";
    return false;
  }
  bool result = true;
  if(!root_)
  {
    root_ = new Node(word);
    result = root_->translations_->splitInsert(translations);
    return result;
  }

  Node* temp = root_;
  Node* parent = nullptr;

  while(temp)
  {
    parent = temp;

    if(word < temp->word_)
    {
      temp = temp->left_;
    }
    else if(word > temp->word_)
    {
      temp = temp->right_;
    }
    else
    {
      std::cout << word << " has been already inserted. and has these translations: \n";
      temp->translations_->print(std::cout);
      std::cout << "\nWould you like to add your translations to this word? (y/n)\n";
      std::string answer;
      std::cin >> answer;
      if(answer == "y" || answer == "yes" || answer == "Y" || answer == "Yes")
        break;
      return !result;
    }
  }
  if(word < parent->word_)
  {
    parent->left_ = new Node(word);
    result = parent->left_->translations_->splitInsert(translations);
  }
  else if(word > parent->word_)
  {
    parent->right_ = new Node(word);
    result = parent->right_->translations_->splitInsert(translations);
  }
  if(word == parent->word_)
  {
    result = parent->translations_->splitInsert(translations);
  }
  return result;
}

template<class T>
typename BinaryTreeSearch<T>::Node* BinaryTreeSearch<T>::search(const T& word) const
{
  Node* temp = root_;

  while(temp && word != temp->word_)
  {
    if(word < temp->word_)
      temp = temp->left_;
    else temp = temp->right_;
  }
  return temp;
}

template <class T>
typename BinaryTreeSearch<T>::Node* BinaryTreeSearch<T>::successor(const T& word, Node* parent) const
{
  Node* current = root_;
  Node* next = nullptr;
  while(current)
  {
    parent = current;
    if(current->word_ > word)
    {
      next = current;
      current = current->left_;
    }
    else current = current->right_;
  }
  return next;
}

template<class T>
bool BinaryTreeSearch<T>::deleteWord(const T& word)
{
  if(!root_)
  {
    std::cout << "BinarySearchTree: Unable to delete anything from empty dictionary.";
    return false;
  }
  Node* parent = nullptr;
  Node* current = root_;

  while(current && current->word_ != word)
  {
    parent = current;
    if(word < current->word_)
    {
      current = current->left_;
    }
    else if(word > current->word_)
    {
      current = current->right_;
    }
  }
  if(!current)
  {
    std::cout << "BinarySearhTree: Word " << word << " is not in the dictionary.\n";
    return false;
  }
  if(!current->left_ && !current->right_)
  {

    if(!parent)
    {
      delete current;
      root_ = nullptr;
    }
    else if(parent->left_ == current)
    {
      delete current;
      parent->left_ = nullptr;
    }
    else if(parent->right_ == current)
    {
      delete current;
      parent->right_ = nullptr;
    }
  }
  else if(!current->left_ && current->right_)
  {
    std::swap(current->word_, current->right_->word_);
    std::swap(current->translations_, current->right_->translations_);
    delete current->right_;
    current->right_ = nullptr;
  }
  else if(current->left_ && !current->right_)
  {
    std::swap(current->word_, current->left_->word_);
    std::swap(current->translations_, current->left_->translations_);
    delete current->left_;
    current->left_ = nullptr;
  }
  else if(current->left_ && current->right_)
  {
    parent = nullptr;
    Node* next = successor(current->word_, parent);

    std::swap(current->word_, next->word_);
    std::swap(current->translations_, next->translations_);

    if(parent->left_ == next)
    {
      parent->left_ = next->right_;
      delete next;
    }
    if(parent->right_ == next)
    {
      parent->right_ = next->right_;
      delete next;
    }
  }
  return true;
}

template<class T>
void BinaryTreeSearch<T>::print(std::ostream& out) const
{
  root_->printNode(out);
}

template<class T>
void BinaryTreeSearch<T>::print(std::ostream& out, const T& word) const
{
  Node* node = search(word);

  if(!node)
  {
    out << "\nNo matches found for word: " << word << "\n";
    return;
  }
  out << "\n" << node->word_ << " - ";
  node->translations_->print(out);
  out << "\n";
}

template <class T>
void BinaryTreeSearch<T>::clear(Node* node)
{
  if(node)
  {
    clear(node->left_);
    clear(node->right_);
    delete node;
    node = nullptr;
  }
}

inline bool isEnglishWord(std::string word)
{
  std::transform(word.begin(), word.end(), word.begin(), tolower);
  for(size_t i = 0; i < word.size(); i++)
  {
    if(word[i] < 'A' || word[i] > 'z' || word[i] == ' ' || word[i] == '(' || word[i] == ')')
    {
      return false;
    }
  }
  return true;
}

inline bool isRussianWord(std::string word)
{
  std::transform(word.begin(), word.end(), word.begin(), tolower);
  for(size_t i = 0; i < word.size(); i++)
  {
    if(word[i] < 'А' || word[i] > 'я' || word[i] == ' ' || word[i] == '(' || word[i] == ')' || word[i] == ';')
    {
      return false;
    }
  }
  return true;
}
#endif
