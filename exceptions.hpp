#ifndef DICTIONARY_EXCEPTIONS_HPP
#define DICTIONARY_EXCEPTIONS_HPP

#include <exception>

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

class WrongOperator : public std::exception
{
public:
  WrongOperator() : reason("Wrong Operator") {}
  const char* what() const noexcept override { return reason; }
private:
  const char* reason;
};

class WrongPostfixNotation : public std::exception
{
public:
  WrongPostfixNotation() : reason("Wrong Postfix Notation") {}
  const char* what() const noexcept override { return reason; }
private:
  const char* reason;
};

class DivisionByZero : public std::exception
{
public:
  DivisionByZero() : reason("Division By Zero") {}
  const char* what() const noexcept override { return reason; }
private:
  const char* reason;
};
#endif
