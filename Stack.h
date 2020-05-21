#ifndef DICTIONARY_STACK_HPP
#define DICTIONARY_STACK_HPP

template <class T>
class Stack
{
public:
  virtual      ~Stack() = default;
  virtual void	push(const T& e) = 0;
  virtual T	    pop() = 0;
  virtual T&    top() = 0;
  virtual bool	isEmpty() = 0;
};

class StackOverflow : public std::exception
{
public:
  StackOverflow() : reason("Stack Overflow") {}
  const char* what() const noexcept override { return reason; }
private:
  const char* reason;
};

class StackUnderflow : public std::exception
{
public:
  StackUnderflow() : reason("Stack Underflow") {}
  const char* what() const noexcept override { return reason; }
private:
  const char* reason;
};

class WrongStackSize : public std::exception
{
public:
  WrongStackSize() : reason("Wrong Stack Size") {}
  const char* what() const noexcept override { return reason; }
private:
  const char* reason;
};

#endif
