#ifndef MAP_H
#define MAP_H

#include <functional>
#include <memory>

#include "./rb_tree.hpp"
#include "./utility.hpp"

namespace ft {
#define CONTAINER Container<ft::pair<const Key, T>, Alloc>
template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map : public CONTAINER {
	template <typename P>
	struct FirstOfPair {
		Key operator()(const P& x) const {
			return (x.first);
		}
	};

 public:
	IMPORT_TYPE(value_type);
	IMPORT_TYPE(reference);
	IMPORT_TYPE(const_reference);
	IMPORT_TYPE(pointer);
	IMPORT_TYPE(const_pointer);
	typedef Key								key_type;
	typedef T								mapped_type;
	typedef Compare							key_compare;

	class value_compare : public std::binary_function<value_type, value_type, bool> {
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
	typedef Rb_tree<key_type, value_type, FirstOfPair<value_type>, key_compare, Alloc>
															Tree_struct;
	Tree_struct												_rbtree;

 public:
	typedef typename Tree_struct::allocator_type			allocator_type;
	typedef typename Tree_struct::iterator					iterator;
	typedef typename Tree_struct::const_iterator			const_iterator;
	typedef typename Tree_struct::reverse_iterator			reverse_iterator;
	typedef typename Tree_struct::const_reverse_iterator	const_reverse_iterator;
	typedef typename Tree_struct::size_type					size_type;
	typedef typename Tree_struct::difference_type			difference_type;

	explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _rbtree(comp, alloc)
				{};

	template <class InputIterator>
	map(InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) : _rbtree(comp, alloc) {
		while (first != last) {
			insert(*first);
			++first;
		}
	};

	map(const map& x) : _rbtree(x._rbtree) {};

	~map(void) {
		clear();
	};

	map& operator=(const map& x) {
		_rbtree = x._rbtree;
		return (*this);
	};

	iterator begin(void) {
		return (_rbtree.begin());
	};

	const_iterator begin(void) const {
		return (_rbtree.begin());
	};

	iterator end(void) {
		return (_rbtree.end());
	};

	const_iterator end(void) const {
		return (_rbtree.end());
	};

	reverse_iterator rbegin(void) {
		return (_rbtree.rbegin());
	};

	const_reverse_iterator rbegin(void) const {
		return (_rbtree.rbegin());
	};

	reverse_iterator rend(void) {
		return (_rbtree.rend());
	};

	const_reverse_iterator rend(void) const {
		return (_rbtree.rend());
	};

	bool empty(void) const {
		return (_rbtree.empty());
	};

	size_type size(void) const {
		return (_rbtree.size());
	};

	size_type max_size(void) const {
		return (_rbtree.max_size());
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
			iterator y = _rbtree.insert_unique(val);
			return (ft::make_pair(y, true));
		}
	};

	iterator insert(iterator position, const value_type& val) {
		iterator x = find(val.first);
		if (x != end()) {
			return (x);
		} else {
			_rbtree.insert(val, position.base());
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
		_rbtree.erase(position->first);
	};

	size_type erase(const key_type& k) {
		if (find(k) != end()) {
			_rbtree.erase(k);
			return (1);
		}
		return (0);
	};

	void erase(iterator first, iterator last) {
		iterator it;
		while (first != last) {
			it = first;
			++first;
			_rbtree.erase(it->first);
		}
	};

	void swap(map& x) {
		_rbtree.swap(x._rbtree);
	};

	void clear(void) {
		_rbtree.clear();
	};

	T& at( const Key& key ) {
		iterator it = find(key);
		return it->second;
	};

	const T& at( const Key& key ) const {
		const_iterator it = find(key);
		return it->second;
	};

	key_compare key_comp(void) const {
		return (_rbtree.key_comp());
	};

	value_compare value_comp(void) const {
		return (value_compare(_rbtree.key_comp()));
	};

	iterator find(const key_type& k) {
		iterator it(_rbtree.search(k));
		return (it);
	};

	const_iterator find(const key_type& k) const {
		const_iterator it(_rbtree.search(k));
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
		return (_rbtree.lower_bound(k));
	};

	const_iterator lower_bound(const key_type& k) const {
		return (_rbtree.lower_bound(k));
	};

	iterator upper_bound(const key_type& k) {
		return (_rbtree.upper_bound(k));
	};

	const_iterator upper_bound(const key_type& k) const {
		return (_rbtree.upper_bound(k));
	};

	ft::pair<iterator, iterator> equal_range(const key_type& k) {
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	};

	ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	};

	allocator_type get_allocator(void) const {
		return (_rbtree.get_allocator());
	};

	template <typename K1, typename T1, typename C1, typename A1>
	friend bool
	operator==(const map<K1, T1, C1, A1>&, const map<K1, T1, C1, A1>&);

	template <typename K1, typename T1, typename C1, typename A1>
	friend bool
	operator<(const map<K1, T1, C1, A1>&, const map<K1, T1, C1, A1>&);
};
#undef CONTAINER

template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {
	lhs.swap(rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs) {
	return (lhs._rbtree == rhs._rbtree);
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs) {
	return (!(lhs == rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs) {
	return (lhs._rbtree < rhs._rbtree);
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
