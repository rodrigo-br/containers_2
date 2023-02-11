#ifndef MAP_H
#define MAP_H

#define MAP_TEMPLATE typename Key,		 \
										 typename T,			 \
										 typename Compare, \
										 typename Alloc

#define MAP_CLASS map<Key, T, Compare, Alloc>

#include <functional>
#include <memory>

#include "./rb_tree.hpp"
#include "./utility.hpp"

namespace ft {

template <class Key,
					class T,
					class Compare = std::less<Key>,
					class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
	template <typename P>
	struct _Select1st {
		Key operator()(const P& x) const {
			return (x.first);
		}
	};

 public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair<const Key, T> value_type;
	typedef Compare key_compare;
	typedef typename Alloc::reference reference;
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::const_pointer const_pointer;

	class value_compare
			: public std::binary_function<value_type, value_type, bool> {
		friend class map<Key, T, Compare, Alloc>;

	 protected:
		Compare comp;

		explicit value_compare(Compare c) : comp(c) {}

	 public:
		bool operator()(const value_type& x, const value_type& y) const {
			return (comp(x.first, y.first));
		}
	};

 private:
	typedef Rb_tree<key_type, value_type,
									_Select1st<value_type>, key_compare, Alloc>
			Rb_tree_type;

	Rb_tree_type _rb_tree;

 public:
	typedef typename Rb_tree_type::allocator_type allocator_type;
	typedef typename Rb_tree_type::iterator iterator;
	typedef typename Rb_tree_type::const_iterator const_iterator;
	typedef typename Rb_tree_type::reverse_iterator reverse_iterator;
	typedef typename Rb_tree_type::const_reverse_iterator const_reverse_iterator;
	typedef typename Rb_tree_type::size_type size_type;
	typedef typename Rb_tree_type::difference_type difference_type;

	explicit map(const key_compare& comp = key_compare(),
							 const allocator_type& alloc = allocator_type())
				 : _rb_tree(comp, alloc) {};

	template <class InputIterator>
	map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: _rb_tree(comp, alloc) {
	while (first != last) {
		insert(*first);
		++first;
	}
};

	map(const map& x) : _rb_tree(x._rb_tree) {};

	~map(void) {
	clear();
};

	map& operator=(const map& x) {
	_rb_tree = x._rb_tree;
	return (*this);
};

	iterator begin(void) {
	return (_rb_tree.begin());
};

	const_iterator begin(void) const {
	return (_rb_tree.begin());
};

	iterator end(void) {
	return (_rb_tree.end());
};

	const_iterator end(void) const {
	return (_rb_tree.end());
};

	reverse_iterator rbegin(void) {
	return (_rb_tree.rbegin());
};

	const_reverse_iterator rbegin(void) const {
	return (_rb_tree.rbegin());
};

	reverse_iterator rend(void) {
	return (_rb_tree.rend());
};

	const_reverse_iterator rend(void) const {
	return (_rb_tree.rend());
};

	bool empty(void) const {
	return (_rb_tree.empty());
};

	size_type size(void) const {
	return (_rb_tree.size());
};

	size_type max_size(void) const {
	return (_rb_tree.max_size());
};

	mapped_type& operator[](const key_type& k) {
	iterator x = insert(begin(), ft::make_pair(k, mapped_type()));
	return (x->second);
};

	ft::pair<iterator, bool> insert(const value_type& val) {
	iterator x = find(val.first);
	if (x != end()) {
		return (ft::make_pair(x, false));
	} else {
		iterator y = _rb_tree.insert_unique(val);
		return (ft::make_pair(y, true));
	}
};

	iterator insert(iterator position, const value_type& val) {
	iterator x = find(val.first);
	if (x != end()) {
		return (x);
	} else {
		_rb_tree.insert(val, position.base());
		iterator y = find(val.first);
		return (y);
	}
};

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
	while (first != last) {
		insert(*first);
		++first;
	}
};

	void erase(iterator position) {
	_rb_tree.erase(position->first);
};

	size_type erase(const key_type& k) {
	if (find(k) != end()) {
		_rb_tree.erase(k);
		return (1);
	}
	return (0);
};

	void erase(iterator first, iterator last) {
	iterator it;
	while (first != last) {
		it = first;
		++first;
		_rb_tree.erase(it->first);
	}
};

	void swap(map& x) {
	_rb_tree.swap(x._rb_tree);
};

	void clear(void) {
	_rb_tree.clear();
};

	T& at( const Key& key ) {
	iterator it = find(key);
	return it->second;
};

	const T& at( const Key& key ) const {
	const_iterator it = find(key);
	return it->second;
};;

	key_compare key_comp(void) const {
	return (_rb_tree.key_comp());
};

	value_compare value_comp(void) const {
	return (value_compare(_rb_tree.key_comp()));
};

	iterator find(const key_type& k) {
	iterator it(_rb_tree.search(k));
	return (it);
};

	const_iterator find(const key_type& k) const {
	const_iterator it(_rb_tree.search(k));
	return (it);
};

	size_type count(const key_type& k) const {
	const_iterator it = find(k);
	if (it != end()) {
		return (1);
	}
	return (0);
};

	iterator lower_bound(const key_type& k) {
	return (_rb_tree.lower_bound(k));
};

	const_iterator lower_bound(const key_type& k) const {
	return (_rb_tree.lower_bound(k));
};

	iterator upper_bound(const key_type& k) {
	return (_rb_tree.upper_bound(k));
};

	const_iterator upper_bound(const key_type& k) const {
	return (_rb_tree.upper_bound(k));
};

	ft::pair<iterator, iterator> equal_range(const key_type& k) {
	iterator lowerBound = lower_bound(k);
	iterator upperBound = upper_bound(k);
	return (ft::make_pair(lowerBound, upperBound));
};

	ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
	const_iterator lowerBound = lower_bound(k);
	const_iterator upperBound = upper_bound(k);
	return (ft::make_pair(lowerBound, upperBound));
};

	allocator_type get_allocator(void) const {
	return (_rb_tree.get_allocator());
};

	template <typename K1, typename T1, typename C1, typename A1>
	friend bool
	operator==(const map<K1, T1, C1, A1>&,
						 const map<K1, T1, C1, A1>&);

	template <typename K1, typename T1, typename C1, typename A1>
	friend bool
	operator<(const map<K1, T1, C1, A1>&,
						const map<K1, T1, C1, A1>&);
};

template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc>& lhs,
								map<Key, T, Compare, Alloc>& rhs) {
	lhs.swap(rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc>& lhs,
								const map<Key, T, Compare, Alloc>& rhs) {
	return (lhs._rb_tree == rhs._rb_tree);
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
								const map<Key, T, Compare, Alloc>& rhs) {
	return (!(lhs == rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs,
							 const map<Key, T, Compare, Alloc>& rhs) {
	return (lhs._rb_tree < rhs._rb_tree);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
								const map<Key, T, Compare, Alloc>& rhs) {
	return (!(rhs < lhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& lhs,
							 const map<Key, T, Compare, Alloc>& rhs) {
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
								const map<Key, T, Compare, Alloc>& rhs) {
	return (!(lhs < rhs));
}

};
#endif
