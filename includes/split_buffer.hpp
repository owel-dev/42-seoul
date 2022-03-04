#ifndef SPLIT_BUFFER_HPP
#define SPLIT_BUFFER_HPP
#include <memory>

template <class T, class Allocator = std::allocator<T> >
class split_buffer {
  typedef Allocator allocator_type;
  typedef unsigned long size_type;
  typedef long diffrence;
  typedef T* pointer;

 private:
  allocator_type __alloc;
  pointer __first;
  pointer __begin;
  pointer __end;
  pointer __end_cap;

 public:
  split_buffer(size_type cap, size_type start,
               const allocator_type& alloc = allocator_type())
      : __alloc(alloc) {
    __first = cap != 0 ? __alloc.allocate(cap) : nullptr;
    __begin = __end = __first + start;
    __end_cap = __first + cap;
  }
  split_buffer(const split_buffer& obj);
  ~split_buffer();
  split_buffer& operator=(const split_buffer& obj);

  void construct_at_end(pointer _new_end, const value_type& val) {
    construct_transaction __ct(&__end, _new_end);
    for (; __ct._pos != __ct._end; ++__ct._pos) {
      __alloc.construct(__ct._pos, val);
    }
  }

  class construct_transaction {
   public:
    explicit construct_transaction(pointer* __p, size_type __n)
        : _pos(*__p), _end(*__p + __n), _dest(__p) {}
    ~construct_transaction() { *_dest = _pos; }
    pointer _pos;
    const pointer _end;

   private:
    pointer* _dest;
  }
};

#endif