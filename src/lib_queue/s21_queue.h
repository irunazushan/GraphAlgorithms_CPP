#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <cstddef>
#include <new>
#include <stdexcept>

template <typename Type>

class Queue {
 public:
  using value_type = Type;
  using reference = Type&;
  using const_reference = const Type&;
  using size_type = size_t;

  Queue() noexcept;
  explicit Queue(std::initializer_list<value_type> const& items);
  Queue(const Queue& other);
  Queue(Queue&& other) noexcept;
  ~Queue() noexcept;

  inline Queue& operator=(const Queue& other);
  inline Queue& operator=(Queue&& other) noexcept;

  const_reference front() const;
  const_reference back() const;

  inline bool empty() const noexcept;
  size_type size() const noexcept;
  void push(const_reference value);
  void pop() noexcept;
  inline void swap(Queue& other) noexcept;

  template <typename... Args>
  inline void insert_many_back(Args&&... args);

 private:
  typedef struct Data {
    value_type value_;
    Data* next_node_;
  } Node;
  size_type size_;
  Node* front_node_;
  Node* back_node_;
};

#endif
