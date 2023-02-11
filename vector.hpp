#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <memory>
#include <stdexcept>

#include "algorithm.hpp"
#include "iterator_funcs.hpp"
#include "iterator_random.hpp"
#include "iterator_reverse.hpp"
#include "iterator_traits.hpp"
#include "type_traits.hpp"

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {
 public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename Alloc::reference reference;
  typedef typename Alloc::const_reference const_reference;
  typedef typename Alloc::pointer pointer;
  typedef typename Alloc::const_pointer const_pointer;
  typedef ft::random_access_iterator<pointer> iterator;
  typedef ft::random_access_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

 protected:
  std::allocator<T> _alloc;
  pointer _data;
  size_type _capacity;
  size_type _size;

 public:
  explicit vector(const allocator_type& alloc = allocator_type()) {
  _alloc = alloc;
  _data = NULL;
  _size = 0;
  _capacity = 0;
};

  explicit vector(size_type n,
                  const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type()) {
  _alloc = alloc;
  _data = NULL;
  _size = 0;
  _capacity = 0;
  if (n > max_size()) {
    throw std::length_error("length_error");
  }
  _data = _alloc.allocate(n);
  if (_data == NULL) {
    throw std::bad_alloc();
  }
  for (size_t i = 0; i < n; i++) {
    _alloc.construct(_data + i, val);
    _size++;
  }
  _capacity = n;
};

  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type()) {
  _alloc = alloc;
  _data = NULL;
  _size = 0;
  _capacity = 0;
  typedef typename ft::is_integral<InputIterator>::type Integral;
  initialize_dispatch(first, last, Integral());
};

  template <typename Integer>
  void initialize_dispatch(Integer n, Integer value, true_type) {
  _data = _alloc.allocate(n);
  if (_data == NULL) {
    throw std::bad_alloc();
  }
  for (Integer i = 0; i < n; i++) {
    _alloc.construct(_data + i, value);
    _size++;
  }
  _capacity = n;
};

  template <typename InputIterator>
  void initialize_dispatch(InputIterator first, InputIterator last, false_type) {
  _size = ft::distance(first, last);
  _capacity = _size;
  _data = _alloc.allocate(_size);
  if (_data == NULL) {
    throw std::bad_alloc();
  }
  std::uninitialized_copy(first, last, _data);
};

  vector(const vector& x) {
  _alloc = x._alloc;
  _data = NULL;
  _size = 0;
  _capacity = 0;
  *this = x;
};

  ~vector(void) {
  for (size_type i = 0; i < _size; i++) {
    _alloc.destroy(_data + i);
  }
  if (_capacity > 0) {
    _alloc.deallocate(_data, _size);
  }
  _size = 0;
  _capacity = 0;
};

  vector& operator=(const vector& x) {
  if (*this != x) {
    for (size_t i = 0; i < _size; i++) {
      _alloc.destroy(&_data[i]);
    }
    if (_capacity > 0) {
      _alloc.deallocate(_data, _size);
    }
    _size = x.size();
    _capacity = x.capacity();
    _data = _alloc.allocate(_capacity);
    for (size_t i = 0; i < _size; i++) {
      _alloc.construct(&_data[i], x._data[i]);
    }
  }
  return (*this);
};

  iterator begin(void) {
  return (iterator(_data));
};

  const_iterator begin(void) const {
  return (const_iterator(_data));
};

  iterator end(void) {
  return (iterator(_data + _size));
};

  T* data() {
	  return _data;
};

  const T* data() const {
	  return _data;
};

  const_iterator end(void) const {
  return (const_iterator(_data + _size));
};

  reverse_iterator rbegin(void) {
  return (reverse_iterator(end()));
};

  const_reverse_iterator rbegin(void) const {
  return (const_reverse_iterator(end()));
};

  reverse_iterator rend(void) {
  return (reverse_iterator(begin()));
};

  const_reverse_iterator rend(void) const {
  return (const_reverse_iterator(begin()));
};

  size_type size(void) const {
  return (_size);
};

  size_type max_size(void) const {
  return (_alloc.max_size());
};

  void resize(size_type n, value_type val = value_type()) {
  while (n < _size) {
    pop_back();
  }
  if (n > _capacity) {
    reserve(n);
  }
  while (n > _size) {
    push_back(val);
  }
};

  size_type capacity(void) const {
  return (_capacity);
};

  bool empty(void) const {
  return (begin() == end());
};

  void reserve(size_type n) {
  if (n > _capacity) {
    if (n > max_size()) {
      throw std::length_error("length_error");
    }
    pointer tmp = _alloc.allocate(n);
    if (tmp == NULL) {
      throw std::bad_alloc();
    }
    for (size_t i = 0; i < _size; i++) {
      _alloc.construct(tmp + i, _data[i]);
      _alloc.destroy(_data + i);
    }
    _alloc.deallocate(_data, _capacity);
    _data = tmp;
    _capacity = n;
  }
};

  reference operator[](size_type n) {
  return (*(begin() + n));
};

  const_reference operator[](size_type n) const {
  return (*(begin() + n));
};

  reference at(size_type n) {
  if (n < 0 || n >= _size) {
    throw std::out_of_range("out_of_range");
  }
  return (*(begin() + n));
};

  const_reference at(size_type n) const {
  if (n < 0 || n >= _size) {
    throw std::out_of_range("out_of_range");
  }
  return (*(begin() + n));
};

  reference front(void) {
  return (*begin());
};

  const_reference front(void) const {
  return (*begin());
};

  reference back(void) {
  return (*(end() - 1));
};

  const_reference back(void) const {
  return (*(end() - 1));
};

  template <class InputIterator>
  void assign(InputIterator first, InputIterator last) {
  typedef typename ft::is_integral<InputIterator>::type Integral;
  assign_dispatch(first, last, Integral());
};

  template <typename Integer>
  void assign_dispatch(Integer n, Integer val, true_type) {
  for (size_t i = 0; i < _size; i++) {
    _alloc.destroy(&_data[i]);
  }
  _alloc.deallocate(_data, _capacity);
  if (static_cast<size_type>(n) > _capacity) {
    _capacity = n;
  }
  _data = _alloc.allocate(n);
  if (_data == NULL) {
    throw std::bad_alloc();
  }
  _size = n;
  for (size_t i = 0; i < _size; i++) {
    _alloc.construct(&_data[i], val);
  }
};

  template <typename InputIterator>
  void assign_dispatch(InputIterator first, InputIterator last, false_type) {
  for (size_t i = 0; i < _size; i++) {
    _alloc.destroy(&_data[i]);
  }
  _alloc.deallocate(_data, _capacity);
  if (static_cast<size_type>(ft::distance(first, last)) > _capacity) {
    _capacity = ft::distance(first, last);
  }
  _data = _alloc.allocate(_capacity);
  if (_data == NULL) {
    throw std::bad_alloc();
  }
  _size = ft::distance(first, last);
  std::uninitialized_copy(first, last, _data);
};

  void push_back(const value_type& val) {
  if (_size + 1 > _capacity) {
    _capacity ? _capacity *= 2 : _capacity++;
    pointer tmp = _alloc.allocate(_capacity);
    if (tmp == NULL) {
      throw std::bad_alloc();
    }
    for (size_t i = 0; i < _size; i++) {
      _alloc.construct(tmp + i, _data[i]);
      _alloc.destroy(_data + i);
    }
    _alloc.deallocate(_data, _capacity);
    _data = tmp;
  }
  _alloc.construct(_data + _size, val);
  _size++;
};

  void pop_back(void) {
  if (_size) {
    _alloc.destroy(_data + _size - 1);
    _size--;
  }
};

  iterator insert(iterator position, const value_type& val) {
  size_type distance = ft::distance(begin(), position);
  if (_capacity == 0) {
    reserve(1);
    _alloc.construct(&_data[distance], val);
    _size++;
    return (iterator(&_data[distance]));
  }
  if (_capacity < (_size + 1)) {
    reserve(_capacity * 2);
  }
  if (position == end()) {
    push_back(val);
    return (iterator(&_data[distance]));
  }
  if (ft::is_integral<value_type>::value) {
    std::copy_backward(&_data[distance], &_data[_size], &_data[_size + 1]);
  } else {
    for (size_t i = _size; i > distance; i--) {
      _alloc.construct(&_data[i], _data[i - 1]);
      _alloc.destroy(&_data[i - 1]);
    }
  }
  _alloc.construct(&_data[distance], val);
  _size++;
  return (iterator(&_data[distance]));
};

  void insert(iterator position, size_type n, const value_type& val) {
  size_type distance = ft::distance(begin(), position);
  if (_capacity == 0) {
    reserve(n);
    _size = n;
    for (size_t i = 0; i < n; i++)
      _alloc.construct(&_data[distance + i], val);
    return;
  }
  if (_capacity < (_size + n)) {
    reserve(_capacity * 2);
  }
  for (size_t i = 0; i < n; i++) {
    insert(begin() + distance, val);
  }
};

  template <class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
  typedef typename ft::is_integral<InputIterator>::type Integral;
  insert_dispatch(position, first, last, Integral());
};

  template <class Integer>
  void insert_dispatch(iterator position,
                       size_type n, const Integer& val, true_type) {
  size_type distance = ft::distance(begin(), position);
  if (_capacity == 0) {
    reserve(n);
    _size = n;
    for (size_t i = 0; i < n; i++)
      _alloc.construct(&_data[distance + i], val);
    return;
  }
  if (_capacity < (_size + n)) {
    reserve(_capacity * 2);
  }
  for (size_t i = 0; i < n; i++) {
    insert(begin() + distance, val);
  }
};

  template <class InputIterator>
  void insert_dispatch(iterator position,
                       InputIterator first, InputIterator last, false_type) {
  size_type distance = ft::distance(begin(), position);
  size_type n = ft::distance(first, last);
  if (_capacity == 0) {
    reserve(n);
    _size = n;
    for (size_t i = 0; i < n; i++) {
      _alloc.construct(&_data[distance + i], *first);
      first++;
    }
    return;
  }
  if (_capacity < (_size + n)) {
    reserve(_capacity * 2);
  }
  for (size_t i = 0; i < n; i++) {
    last--;
    insert(begin() + distance, *last);
  }
};

  iterator erase(iterator position) {
  if (position + 1 != end()) {
    std::copy(position.base() + 1, end().base(), position.base());
  }
  --_size;
  if (!ft::is_integral<value_type>::value) {
    _alloc.destroy(_data + _size);
  }
  return (position);
};

  iterator erase(iterator first, iterator last) {
  iterator it(std::copy(last.base(), end().base(), first.base()));
  if (!ft::is_integral<value_type>::value) {
    while (it != end()) {
      _alloc.destroy(it.base());
      ++it;
    }
  }
  _size -= (last - first);
  return (first);
};

  void swap(vector& x) {
  pointer tmp_data = x._data;
  size_type tmp_capacity = x._capacity;
  size_type tmp_size = x._size;

  x._data = _data;
  x._capacity = _capacity;
  x._size = _size;

  _data = tmp_data;
  _capacity = tmp_capacity;
  _size = tmp_size;
};

  void clear(void) {
  erase(begin(), end());
};

  allocator_type get_allocator(void) const {
  return (_alloc);
};
};

template <class T, class Alloc>
inline bool operator==(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
  return ((x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin())));
}

template <class T, class Alloc>
inline bool operator!=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
  return (!(x == y));
}

template <class T, class Alloc>
inline bool operator<(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
  return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
}

template <class T, class Alloc>
inline bool operator<=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
  return (!(y < x));
}

template <class T, class Alloc>
inline bool operator>(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
  return (y < x);
}

template <class T, class Alloc>
inline bool operator>=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
  return (!(x < y));
}

template <class T, class Alloc>
void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
  x.swap(y);
}

}

#endif
