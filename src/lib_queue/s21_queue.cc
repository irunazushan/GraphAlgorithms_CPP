#include "s21_queue.h"

template <typename Type>
Queue<Type>::Queue() noexcept
    : size_(static_cast<size_type>(0)),
      front_node_(nullptr),
      back_node_(nullptr) {}

template <typename Type>
Queue<Type>::Queue(std::initializer_list<value_type> const& items) : Queue() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename Type>
Queue<Type>::Queue(const Queue& other) : Queue() {
  Node* runner = other.back_node_;

  Queue<Type> tmp_Queue;
  while (runner != nullptr) {
    tmp_Queue.push(runner->value_);
    runner = runner->next_node_;
  }

  runner = tmp_Queue.back_node_;
  while (runner != nullptr) {
    this->push(runner->value_);
    runner = runner->next_node_;
  }

  size_ = other.size_;
}

template <typename Type>
Queue<Type>::Queue(Queue&& other) noexcept : Queue() {
  this->~Queue();

  this->size_ = other.size_;
  this->front_node_ = other.front_node_;
  this->back_node_ = other.back_node_;
  other.size_ = static_cast<size_type>(0);
  other.front_node_ = nullptr;
  other.back_node_ = nullptr;
}

template <typename Type>
Queue<Type>::~Queue() noexcept {
  while (front_node_ != nullptr) {
    pop();
  }
}

template <typename Type>
inline Queue<Type>& Queue<Type>::operator=(const Queue& other) {
  if (this == &other) {
    return *this;
  }

  this->~Queue();

  Node* runner = other.back_node_;

  Queue<Type> tmp_Queue;
  while (runner != nullptr) {
    tmp_Queue.push(runner->value_);
    runner = runner->next_node_;
  }

  runner = tmp_Queue.back_node_;
  while (runner != nullptr) {
    this->push(runner->value_);
    runner = runner->next_node_;
  }

  size_ = other.size_;

  return *this;
}

template <typename Type>
inline Queue<Type>& Queue<Type>::operator=(Queue&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  this->~Queue();

  this->size_ = other.size_;
  this->front_node_ = other.front_node_;
  this->back_node_ = other.back_node_;
  other.size_ = static_cast<size_type>(0);
  other.front_node_ = nullptr;
  other.back_node_ = nullptr;

  return *this;
}

template <typename Type>
typename Queue<Type>::const_reference Queue<Type>::front() const {
  if (front_node_ == nullptr) {
    throw std::out_of_range("Queue is empty");
  }
  return static_cast<const_reference>(front_node_->value_);
}

template <typename Type>
typename Queue<Type>::const_reference Queue<Type>::back() const {
  if (back_node_ == nullptr) {
    throw std::out_of_range("Queue is empty");
  }
  return static_cast<const_reference>(back_node_->value_);
}

template <typename Type>
inline bool Queue<Type>::empty() const noexcept {
  return size_ == static_cast<size_type>(0) ? true : false;
}

template <typename Type>
typename Queue<Type>::size_type Queue<Type>::size() const noexcept {
  return size_;
}

template <typename Type>
inline void Queue<Type>::push(const_reference value) {
  Node* new_node = new Node;
  new_node->value_ = value;
  new_node->next_node_ = back_node_;
  back_node_ = new_node;
  if (size_ == 0) {
    front_node_ = new_node;
  }
  ++size_;
}

template <typename Type>
void Queue<Type>::pop() noexcept {
  if (size_ != 0) {
    Node* runner = back_node_;
    while (runner != front_node_ && runner->next_node_ != front_node_) {
      runner = runner->next_node_;
    }

    if (runner == front_node_) {
      front_node_ = nullptr;
      back_node_ = nullptr;
      --size_;
      delete runner;
    } else {
      Node* tmp_node = runner->next_node_;
      front_node_ = runner;
      --size_;
      delete tmp_node;
    }
  }
}

template <typename Type>
inline void Queue<Type>::swap(Queue& other) noexcept {
  Queue<Type> tmp_Queue;
  tmp_Queue = other;
  other = *this;
  *this = tmp_Queue;
}

template <typename Type>
template <typename... Args>
inline void Queue<Type>::insert_many_back(Args&&... args) {
  for (auto arg : {std::forward<Args>(args)...}) {
    push(arg);
  }
}

template class Queue<int>;