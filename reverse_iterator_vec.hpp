#ifndef ITERATOR_REVERSE_H
#define ITERATOR_REVERSE_H

#include "./iterator_traits.hpp"

namespace ft {

template <typename Iterator>
#define TRAITS iterator_traits<Iterator>
class reverse_iterator
		: public TRAITS, public iterator<typename TRAITS::iterator_category,
							typename TRAITS::value_type,
							typename TRAITS::difference_type,
							typename TRAITS::pointer,
							typename TRAITS::reference> {
 protected:
	Iterator			current;

 public:
	typedef Iterator	iterator_type;
	IMPORT_TRAIT(iterator_category);
	IMPORT_TRAIT(value_type);
	IMPORT_TRAIT(difference_type);
	IMPORT_TRAIT(pointer);
	IMPORT_TRAIT(reference);

 public:
	reverse_iterator(void) : current(NULL) {}
	explicit reverse_iterator(iterator_type x) : current(x) {}
	reverse_iterator(const reverse_iterator& x) : current(x.current) {}
	template <typename Iter>
	reverse_iterator(const reverse_iterator<Iter>& x) : current(x.base()) {}
	~reverse_iterator(void) {}

	template <typename Iter>
	reverse_iterator& operator=(const reverse_iterator<Iter>& x) {
		current = x.base();
		return (*this);
	}

	iterator_type base(void) const {
		return (current);
	}

	reference operator*(void) const {
		Iterator tmp = current;
		return (*--tmp);
	}

	reverse_iterator operator+(difference_type n) const {
		return (reverse_iterator(current - n));
	}

	reverse_iterator& operator++(void) {
		--current;
		return (*this);
	}

	reverse_iterator operator++(int) {
		reverse_iterator tmp = *this;
		--current;
		return (tmp);
	}

	reverse_iterator& operator+=(difference_type n) {
		current -= n;
		return (*this);
	}

	reverse_iterator operator-(difference_type n) const {
		return (reverse_iterator(current + n));
	}

	reverse_iterator& operator--(void) {
		++current;
		return (*this);
	}

	reverse_iterator operator--(int) {
		reverse_iterator tmp = *this;
		++current;
		return (tmp);
	}

	reverse_iterator& operator-=(difference_type n) {
		current += n;
		return (*this);
	}

	pointer operator->(void) const {
		return (&(this->operator*()));
	}

	reference operator[](difference_type n) const {
		return (*(*this + n));
	}
	#undef TRAITS
};

template <typename IteratorL, typename IteratorR>
inline bool operator==(const reverse_iterator<IteratorL>& x,
						const reverse_iterator<IteratorR>& y) {
	return (x.base() == y.base());
}

template <typename Iterator>
inline bool operator==(const reverse_iterator<Iterator>& x,
						const reverse_iterator<Iterator>& y) {
	return (x.base() == y.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const reverse_iterator<IteratorL>& x,
						const reverse_iterator<IteratorR>& y) {
	return (!(x == y));
}

template <typename Iterator>
inline bool operator!=(const reverse_iterator<Iterator>& x,
						const reverse_iterator<Iterator>& y) {
	return (!(x == y));
}

template <typename IteratorL, typename IteratorR>
inline bool operator<(const reverse_iterator<IteratorL>& x,
						const reverse_iterator<IteratorR>& y) {
	return (y.base() < x.base());
}

template <typename Iterator>
inline bool operator<(const reverse_iterator<Iterator>& x,
						const reverse_iterator<Iterator>& y) {
	return (y.base() < x.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator<=(const reverse_iterator<IteratorL>& x,
											 const reverse_iterator<IteratorR>& y) {
	return (!(y < x));
}

template <typename Iterator>
inline bool operator<=(const reverse_iterator<Iterator>& x,
						const reverse_iterator<Iterator>& y) {
	return (!(y < x));
}

template <typename IteratorL, typename IteratorR>
inline bool operator>(const reverse_iterator<IteratorL>& x,
						const reverse_iterator<IteratorR>& y) {
	return (y < x);
}

template <typename Iterator>
inline bool operator>(const reverse_iterator<Iterator>& x,
						const reverse_iterator<Iterator>& y) {
	return (y < x);
}

template <typename IteratorL, typename IteratorR>
inline bool operator>=(const reverse_iterator<IteratorL>& x,
						const reverse_iterator<IteratorR>& y) {
	return (!(x < y));
}

template <typename Iterator>
inline bool operator>=(const reverse_iterator<Iterator>& x,
						const reverse_iterator<Iterator>& y) {
	return (!(x < y));
}

template <typename Iterator>
inline reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& x) {
	return (reverse_iterator<Iterator>(x.base() - n));
}

template <typename IteratorL, typename IteratorR>
inline typename reverse_iterator<IteratorL>::difference_type
operator-(const reverse_iterator<IteratorL>& lhs,
			const reverse_iterator<IteratorR>& rhs) {
	return (rhs.base() - lhs.base());
}

};

#endif
