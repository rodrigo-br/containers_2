#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "./iterator_traits.hpp"
#include "./RBT_Node.hpp"

namespace ft {

template <typename T>
#define TRAITS ft::iterator_traits<T>
class bidirectional_iterator : public TRAITS, public iterator<std::bidirectional_iterator_tag, T> {
 public:
	IMPORT_TRAIT(iterator_category);
	IMPORT_TRAIT(value_type);
	IMPORT_TRAIT(pointer);
	IMPORT_TRAIT(reference);
	IMPORT_TRAIT(difference_type);
	typedef T 								iterator_type;
	typedef RBT_Node<value_type>			Tree_Node;
	typedef Tree_Node*						Node_ptr;
	typedef const Tree_Node*				Const_node_ptr;

 protected:
	Node_ptr								node;

 public:
	bidirectional_iterator(void) : node(NULL) {}

	explicit bidirectional_iterator(Node_ptr _node) : node(_node) {}

	template <typename Iter>
	bidirectional_iterator(const bidirectional_iterator<Iter>& i) : node(i.base()) {}

	~bidirectional_iterator(void) {}

	template <typename Iter>
	bidirectional_iterator& operator=(const bidirectional_iterator<Iter>& i) {
		node = i.base();
		return (*this);
	}

	Node_ptr base(void) const {
		return (node);
	}

	reference operator*(void) const {
		return (node->data);
	}

	bidirectional_iterator& operator++(void) {
		node = Tree_Node::successor(node);
		return (*this);
	}

	bidirectional_iterator operator++(int) {
		Node_ptr tmp = node;
		node = Tree_Node::successor(node);
		return (bidirectional_iterator(tmp));
	}

	bidirectional_iterator& operator--(void) {
		node = Tree_Node::predecessor(node);
		return (*this);
	}

	bidirectional_iterator operator--(int) {
		Node_ptr tmp = node;
		node = Tree_Node::predecessor(node);
		return (bidirectional_iterator(tmp));
	}

	pointer operator->(void) const {
		return (&(operator*()));
	}
};

template <typename IteratorL, typename IteratorR>
inline bool operator==(const bidirectional_iterator<IteratorL>& lhs,
											 const bidirectional_iterator<IteratorR>& rhs) {
	return (lhs.base() == rhs.base());
}

template <typename Iterator>
inline bool operator==(const bidirectional_iterator<Iterator>& lhs,
											 const bidirectional_iterator<Iterator>& rhs) {
	return (lhs.base() == rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const bidirectional_iterator<IteratorL>& lhs,
											 const bidirectional_iterator<IteratorR>& rhs) {
	return (lhs.base() != rhs.base());
}

template <typename Iterator>
inline bool operator!=(const bidirectional_iterator<Iterator>& lhs,
											 const bidirectional_iterator<Iterator>& rhs) {
	return (lhs.base() != rhs.base());
}
#undef TRAITS
}

#endif
