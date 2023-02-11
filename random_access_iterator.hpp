#ifndef RANDOM_ACCESS_ITERATOR_H
#define RANDOM_ACCESS_ITERATOR_H

#include "./iterator_traits.hpp"

namespace ft {

template <typename Iterator>
class random_access_iterator : public iterator<std::random_access_iterator_tag, Iterator> {
 protected:
	Iterator														current;

 public:
	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

 public:
	random_access_iterator(void) : current(NULL) {}
	explicit random_access_iterator(const Iterator& i) : current(i) {}
	random_access_iterator(const random_access_iterator& i) : current(i.base()) {}
	template <typename Iter>
	random_access_iterator(const random_access_iterator<Iter>& i) : current(i.base()) {}
	~random_access_iterator(void) {}

	template <typename Iter>
	random_access_iterator& operator=(const random_access_iterator<Iter>& i) {
		current = i.base();
		return (*this);
	}

	const Iterator& base(void) const {
		return (current);
	}

	reference operator*(void) const {
		return (*current);
	}

	random_access_iterator operator+(const difference_type& n) const {
		return (random_access_iterator(current + n));
	}

	random_access_iterator& operator++(void) {
		++current;
		return (*this);
	}

	random_access_iterator operator++(int) {
		return (random_access_iterator(current++));
	}

	random_access_iterator& operator+=(const difference_type& n) {
		current += n;
		return (*this);
	}

	random_access_iterator operator-(const difference_type& n) const {
		return (random_access_iterator(current - n));
	}

	random_access_iterator& operator--(void) {
		--current;
		return (*this);
	}

	random_access_iterator operator--(int) {
		return (random_access_iterator(current--));
	}

	random_access_iterator& operator-=(const difference_type& n) {
		current -= n;
		return (*this);
	}

	pointer operator->(void) const {
		return (current);
	}

	reference operator[](const difference_type& n) const {
		return (current[n]);
	}
};

template <typename IteratorL, typename IteratorR>
inline bool operator==(const random_access_iterator<IteratorL>& lhs,
						const random_access_iterator<IteratorR>& rhs) {
	return (lhs.base() == rhs.base());
}

template <typename Iterator>
inline bool operator==(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
	return (lhs.base() == rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const random_access_iterator<IteratorL>& lhs,
						const random_access_iterator<IteratorR>& rhs) {
	return (lhs.base() != rhs.base());
}

template <typename Iterator>
inline bool operator!=(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
	return (lhs.base() != rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator<(const random_access_iterator<IteratorL>& lhs,
						const random_access_iterator<IteratorR>& rhs) {
	return (lhs.base() < rhs.base());
}

template <typename Iterator>
inline bool operator<(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
	return (lhs.base() < rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator<=(const random_access_iterator<IteratorL>& lhs,
						const random_access_iterator<IteratorR>& rhs) {
	return (lhs.base() <= rhs.base());
}

template <typename Iterator>
inline bool operator<=(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
	return (lhs.base() <= rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator>(const random_access_iterator<IteratorL>& lhs,
						const random_access_iterator<IteratorR>& rhs) {
	return (lhs.base() > rhs.base());
}

template <typename Iterator>
inline bool operator>(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
	return (lhs.base() > rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator>=(const random_access_iterator<IteratorL>& lhs,
						const random_access_iterator<IteratorR>& rhs) {
	return (lhs.base() >= rhs.base());
}

template <typename Iterator>
inline bool operator>=(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
	return (lhs.base() >= rhs.base());
}

template <typename Iterator>
inline random_access_iterator<Iterator>
operator+(typename random_access_iterator<Iterator>::difference_type n,
			const random_access_iterator<Iterator>& i) {
	return (random_access_iterator<Iterator>(i.base() + n));
}

template <typename IteratorL, typename IteratorR>
inline typename random_access_iterator<IteratorL>::difference_type
operator-(const random_access_iterator<IteratorL>& lhs,
					const random_access_iterator<IteratorR>& rhs) {
	return (lhs.base() - rhs.base());
}

};

#endif
