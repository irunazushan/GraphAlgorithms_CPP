#include "s21_stack.h"

template <typename Type>
Stack<Type>::Stack() noexcept
    : size_(static_cast<size_type>(0)), top_node_(nullptr) {}

template <typename Type>
Stack<Type>::Stack(std::initializer_list<value_type> const& items) : Stack() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename Type>
Stack<Type>::Stack(const Stack& other) : Stack() {
  Node* runner = other.top_node_;

  Stack<Type> tmp_Stack;
  while (runner != nullptr) {
    tmp_Stack.push(runner->value_);
    runner = runner->next_node_;
  }

  runner = tmp_Stack.top_node_;
  while (runner != nullptr) {
    this->push(runner->value_);
    runner = runner->next_node_;
  }

  size_ = other.size_;
}

template <typename Type>
Stack<Type>::Stack(Stack&& other) noexcept : Stack() {
  this->~Stack();

  this->size_ = other.size_;
  this->top_node_ = other.top_node_;
  other.size_ = static_cast<size_type>(0);
  other.top_node_ = nullptr;
}

template <typename Type>
Stack<Type>::~Stack() noexcept {
  while (top_node_ != nullptr) {
    pop();
  }
}

template <typename Type>
inline Stack<Type>& Stack<Type>::operator=(const Stack& other) {
  if (this == &other) {
    return *this;
  }

  this->~Stack();

  Node* runner = other.top_node_;

  Stack<Type> tmp_Stack;
  while (runner != nullptr) {
    tmp_Stack.push(runner->value_);
    runner = runner->next_node_;
  }

  runner = tmp_Stack.top_node_;
  while (runner != nullptr) {
    this->push(runner->value_);
    runner = runner->next_node_;
  }

  size_ = other.size_;

  return *this;
}

template <typename Type>
inline Stack<Type>& Stack<Type>::operator=(Stack&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  this->~Stack();

  this->size_ = other.size_;
  this->top_node_ = other.top_node_;
  other.size_ = static_cast<size_type>(0);
  other.top_node_ = nullptr;

  return *this;
}

template <typename Type>
typename Stack<Type>::const_reference Stack<Type>::top() const {
  if (top_node_ == nullptr) {
    throw std::out_of_range("Stack is empty");
  }
  return static_cast<const_reference>(top_node_->value_);
}

template <typename Type>
inline bool Stack<Type>::empty() const noexcept {
  return size_ == static_cast<size_type>(0) ? true : false;
}

template <typename Type>
typename Stack<Type>::size_type Stack<Type>::size() const noexcept {
  return size_;
}

template <typename Type>
void Stack<Type>::push(const_reference value) {
  Node* new_node = new Node;
  new_node->value_ = value;
  new_node->next_node_ = top_node_;
  top_node_ = new_node;
  ++size_;
}

template <typename Type>
void Stack<Type>::pop() noexcept {
  if (size_ != 0) {
    Node* tmp_node = top_node_;
    top_node_ = top_node_->next_node_;
    --size_;
    delete tmp_node;
  }
}

template <typename Type>
inline void Stack<Type>::swap(Stack& other) noexcept {
  Stack<Type> tmp_Stack;
  tmp_Stack = other;
  other = *this;
  *this = tmp_Stack;
}

template <typename Type>
template <typename... Args>
inline void Stack<Type>::insert_many_front(Args&&... args) {
  for (auto arg : {std::forward<Args>(args)...}) {
    push(arg);
  }
}

template class Stack<int>;