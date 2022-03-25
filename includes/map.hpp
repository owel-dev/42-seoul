#ifndef MAP_HPP
#define MAP_HPP

#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>

#include "RBTree.hpp"

namespace ft
{

template <class Key,                                            // map::key_type
          class T,                                              // map::mapped_type
          class Compare = std::less<Key>,                       // map::key_compare
          class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
          >
class map
{
  public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef typename ft::pair<key_type, mapped_type> value_type;
    typedef Compare key_compare;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    // typedef const ft::map_iterator<value_type> const_iterator;
    typedef ft::rb_tree<value_type> tree_type;
    typedef ft::rb_tree_iterator<value_type> iterator;
    // typedef ft::reverse_iterator<iterator> reverse_iterator;
    // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef long difference_type;
    typedef unsigned long size_type;

  private:
    allocator_type _alloc;
    key_compare _comp;
    tree_type _tree;

  public:
    /*
     * basic
     */
    //? comp: 정렬 방식, 오름차순 or 내림차순, 디폴트는 less(오름차순).
    explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
        : _alloc(alloc), _comp(comp), _tree(tree_type())
    {
    }

    //? map클래스의 value_type에 맞는 Pair 반복자만 사용 가능, 해당 범위의
    //? 요소들을 요소로 가짐.
    // template <class InputIterator> map(InputIterator first,
    // InputIterator last,
    //     const key_compare& comp = key_compare(),
    //     const allocator_type& alloc = allocator_type()) {}

    // map(const map& x) {}

    // ~map() {}

    // map& operator=(const map& x) {}

    /*
     * iterator
     */

    //? 가장 작은 key값의 반복자를 반환
    iterator begin()
    {
        return iterator(_tree.begin());
    }

    // const_iterator begin() const {}

    iterator end()
    {
        return iterator(_tree.end());
    }

    // const_iterator end() const {}

    // reverse_iterator rbegin() {}

    // const_reverse_iterator rbegin() const {}

    // reverse_iterator rend() {}

    // const_reverse_iterator rend() const {}

    /*
     * capacity
     */

    // bool empty() const {}

    // size_type size() const {}

    // size_type max_size() const {}

    /*
     * access
     */

    //? 인자와 동일한 key에 매핑된 value의 reference를 반환한다. 만약 동일한 key가
    //? 없을 경우, key를 컨테이너의 요소에 추가한 후(사이즈가 1 증가한다.) 매핑된
    //? value의 reference를 반환한다.
    // mapped_type& operator[](const key_type& k) {}

    /*
     * modifiers
     */

    //? pair요소를 하나 삽입한다. 기존에 존재하는 요소와 key가 중복될 경우
    //? 삽입하지 않는다.
    void insert(const value_type &val)
    {
        _tree.insert_value(val);
    }

    // iterator insert(iterator position, const value_type& val) {}

    //? first부터 last까지(last미포함) 범위의 요소가 추가된다.
    // template <class InputIterator>
    // void insert(InputIterator first, InputIterator last) {}

    //? 해당 반복자의 요소를 삭제한다.
    // void erase(iterator position) {}

    //? 해당 키와 동일한 요소를 삭제한다.
    // size_type erase(const key_type& k) {}

    //? 해당 범위의 요소를 삭제한다.
    // void erase(iterator first, iterator last) {}

    //? 두 맵끼리 트리를 교환한다.
    // void swap(map& x) {}

    //? 모든 요소를 제거하고(할당해제) 사이즈를 0으로 만든다.
    // void clear() {}

    /*
     * observers
     */

    //? 컨테이너의 비교객체를 반환한다. like less()
    // key_compare key_comp() const;

    //? 컨테이너의 비교객체를 반환한다. (사용자 정의)
    // value_compare value_comp() const;

    /*
     * operations
     */

    //? 해당 키와 같은 요소를 발견하면 반복자, 아니면 end의 반복자.
    // iterator find(const key_type& k);

    //? 위와 동일
    // const_iterator find(const key_type& k) const;

    //? 해당 키와 같은 요소를 발견하면 1, 아니면 0을 반환한다.
    // size_type count(const key_type& k) const;

    //? k보다 크거나 같은 첫 요소의 반복자를 반환
    // iterator lower_bound(const key_type& k);

    // const_iterator lower_bound(const key_type& k) const;

    //? k보다 큰 첫 요소의 반복자를 반환
    // iterator upper_bound(const key_type& k);

    // const_iterator upper_bound(const key_type& k) const;

    //? pair의 pair를 반환, 반환할 pair의 first는 lower_bound, second는
    //? upper_bound
    // pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

    // pair<iterator, iterator> equal_range(const key_type& k);

    /*
     * allocator
     */
    // allocator_type get_allocator() const;
};
} // namespace ft

#endif