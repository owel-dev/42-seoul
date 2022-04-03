#ifndef VECTOR_REVERSE_ITERATOR_HPP
#define VECTOR_REVERSE_ITERATOR_HPP

#include "etc.hpp"

namespace ft
{
template<typename Iterator>
class reverse_iterator
{
  public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<Iterator>::iterator_category
          iterator_category;
  typedef typename ft::iterator_traits<Iterator>::value_type value_type;
  typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;
  typedef typename ft::iterator_traits<Iterator>::reference reference;

  private:
  Iterator _it;

  public:
  /*
   * 기본
   */
  reverse_iterator() {}

  explicit reverse_iterator(Iterator x) : _it(x) {}

  template<class Up>
  reverse_iterator(const reverse_iterator<Up> &u) : _it(u.base()) {}

  reverse_iterator &operator=(const reverse_iterator &u)
  {
    _it = u.base();
    return *this;
  }

  Iterator base() const { return _it; }

  /*
   * 관계
   */

  reference operator*() const
  {
    Iterator temp = _it;
    return *--temp;
  }

  pointer operator->() const { return &(operator*()); }

  reverse_iterator &operator++()
  {
    --_it;
    return *this;
  }

  reverse_iterator operator++(int)
  {
    reverse_iterator temp(*this);
    --_it;
    return temp;
  }

  reverse_iterator &operator--()
  {
    ++_it;
    return *this;
  }

  reverse_iterator operator--(int)
  {
    reverse_iterator temp(*this);
    ++_it;
    return temp;
  }

  reverse_iterator operator+(difference_type n) const
  {
    return reverse_iterator(_it - n);
  }

  reverse_iterator &operator+=(difference_type n)
  {
    _it -= n;
    return *this;
  }

  reverse_iterator operator-(difference_type n) const
  {
    return reverse_iterator(_it + n);
  }

  reverse_iterator &operator-=(difference_type n)
  {
    _it += n;
    return *this;
  }

  reference operator[](difference_type n) const { return *(*this + n); }

};  // namespace ft

//template<class Iterator>
//bool operator==(const reverse_iterator<Iterator> &lhs,
//                const reverse_iterator<Iterator> &rhs)
//{
//  return lhs.base() == rhs.base();
//}
template<class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1> &lhs,
                const reverse_iterator<Iterator2> &rhs)
{
  return lhs.base() == rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1> &lhs,
                const reverse_iterator<Iterator2> &rhs)
{
  return lhs.base() != rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1> &lhs,
               const reverse_iterator<Iterator2> &rhs)
{
  return lhs.base() > rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1> &lhs,
                const reverse_iterator<Iterator2> &rhs)
{
  return lhs.base() >= rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1> &lhs,
               const reverse_iterator<Iterator2> &rhs)
{
  return lhs.base() < rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1> &lhs,
                const reverse_iterator<Iterator2> &rhs)
{
  return lhs.base() <= rhs.base();
}

template<class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type
operator-(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
  return rhs.base() - lhs.base();
}

template<class Iterator>
reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type diff, const reverse_iterator<Iterator> &rhs)
{
  return reverse_iterator<Iterator>(rhs.base() - diff);
}


};  // namespace ft
#endif
