#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack {
 public:
  typedef Container container_type;
  typedef typename container_type::value_type value_type;
  typedef typename container_type::reference reference;
  typedef typename container_type::const_reference const_reference;
  typedef typename container_type::size_type size_type;

 protected:
  container_type c;

 public:
  explicit stack(const container_type& _c = container_type()) : c(_c) {}

  stack(const stack& q) : c(q.c) {}

  stack& operator=(const stack& q) {
    this->c = q.c;
    return *this;
  }

  ~stack() {}

  bool empty() const { return c.empty(); }

  size_type size() const { return c.size(); }

  value_type& top() { return c.back(); }

  const value_type& top() const { return c.back(); }

  void push(const value_type& val) { c.push_back(val); }

  void pop() { c.pop_back(); }

  template <class TT, class CC>
  friend bool operator==(const stack<TT, CC>& lhs,
                         const stack<TT, CC>& rhs);

  template <class TT, class CC>
  friend bool operator<(const stack<TT, CC>& lhs,
                        const stack<TT, CC>& rhs);
};
template <class T, class Container>
bool operator==(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
  return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator<=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(rhs < lhs);
}

template <class T, class Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
  return rhs < lhs;
}

template <class T, class Container>
bool operator>=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

#endif