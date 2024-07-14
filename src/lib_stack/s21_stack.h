#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <cstddef>
#include <new>
#include <stdexcept>

template <typename Type>

class Stack {
 public:
  using value_type = Type;
  using reference = Type&;
  using const_reference = const Type&;
  using size_type = size_t;

  Stack() noexcept;
  explicit Stack(std::initializer_list<value_type> const& items);
  Stack(const Stack& other);
  Stack(Stack&& other) noexcept;
  ~Stack() noexcept;

  inline Stack& operator=(const Stack& other);
  inline Stack& operator=(Stack&& other) noexcept;

  const_reference top() const;

  inline bool empty() const noexcept;
  size_type size() const noexcept;
  void push(const_reference value);
  void pop() noexcept;
  inline void swap(Stack& other) noexcept;

  template <typename... Args>
  inline void insert_many_front(Args&&... args);

 private:
  typedef struct Data {
    value_type value_;
    Data* next_node_;
  } Node;
  size_type size_;
  Node* top_node_;
};

#endif
