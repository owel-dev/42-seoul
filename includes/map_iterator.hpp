#ifndef FT_CONTAINERS_MAP_ITERATOR_HPP
#define FT_CONTAINERS_MAP_ITERATOR_HPP
//#include "map.hpp"
namespace ft
{

// * iterator
template<class Iterator>
class map_iterator
{
  public:
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::node_pointer node_pointer;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::size_type size_type;
  typedef typename Iterator::iterator_category iterator_category;

  private:
  Iterator _it;

  public:
  map_iterator() {}

  map_iterator(const Iterator x) : _it(x) {}

  ~map_iterator() {}


  map_iterator &operator=(const map_iterator &x) {
    _it = x._it;
    return (*this);
  }

  reference operator*() const { return *_it; }

  pointer operator->() const {
    return &(*_it);
  }

  map_iterator &operator++() {
    ++_it;
    return *this;
  }

  map_iterator operator++(int) {
    map_iterator temp(*this);
    ++(*this);
    return temp;
  }

  map_iterator &operator--() {
    --_it;
    return *this;
  }

  map_iterator operator--(int) {
    map_iterator temp(*this);
    --(*this);
    return temp;
  }

  bool operator==(const map_iterator &x) const {
    return this->_it == x._it;
  }

  bool operator!=(const map_iterator &x) const {
    return this->_it != x._it;
  }
  template <class, class, class, class> friend class map;
  template <class> friend class map_const_iterator;

};

// * const_iterator
template<class Iterator>
class map_const_iterator
{
  public:
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::node_pointer node_pointer;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::size_type size_type;
  typedef const value_type *pointer;
  typedef const value_type &reference;
  typedef typename Iterator::iterator_category iterator_category;
  typedef ft::map_iterator<typename  Iterator::non_const_iterator> non_const_iterator;

  private:
  Iterator _it;

  public:
  map_const_iterator() {}

  map_const_iterator(const Iterator x) : _it(x) {}

  map_const_iterator(non_const_iterator x) : _it(x._it) {}

  ~map_const_iterator() {}

  map_const_iterator &operator=(const map_const_iterator &x) {
    _it = x._it;
    return (*this);
  }

  reference operator*() const { return *_it; }

  pointer operator->() const {
    return &(*_it);
  }

  map_const_iterator &operator++() {
    ++_it;
    return *this;
  }

  map_const_iterator operator++(int) {
    map_const_iterator temp(*this);
    ++(*this);
    return temp;
  }

  map_const_iterator &operator--() {
    --_it;
    return *this;
  }

  map_const_iterator operator--(int) {
    map_const_iterator temp(*this);
    --(*this);
    return temp;
  }

  bool operator==(const map_const_iterator &x) const {
    return this->_it == x._it;
  }

  bool operator!=(const map_const_iterator &x) const {
    return this->_it != x._it;
  }

  template <class, class, class, class> friend class map;
};

}


#endif //FT_CONTAINERS_MAP_ITERATOR_HPP

