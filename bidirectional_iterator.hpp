#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "./iterator_traits.hpp"
#include "./RBT_Node.hpp"

namespace ft {

template <typename Iterator>
class rb_tree_iterator : public iterator<std::bidirectional_iterator_tag, Iterator> {
 public:
	typedef Iterator 											iterator_type;
	typedef typename iterator_traits<Iterator>::value_type		value_type;
	typedef typename iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename iterator_traits<Iterator>::pointer			pointer;
	typedef typename iterator_traits<Iterator>::reference		reference;

	typedef RBT_Node<value_type>								Tree_Node;
	typedef Tree_Node*											Node_ptr;
	typedef const Tree_Node*									Const_node_ptr;

 protected:
	Node_ptr													node;

 public:
	rb_tree_iterator(void) : node(NULL) {}

	explicit rb_tree_iterator(Node_ptr _node) : node(_node) {}

	template <typename Iter>
	rb_tree_iterator(const rb_tree_iterator<Iter>& i) : node(i.base()) {}

	~rb_tree_iterator(void) {}

	template <typename Iter>
	rb_tree_iterator& operator=(const rb_tree_iterator<Iter>& i) {
		node = i.base();
		return (*this);
	}

	Node_ptr base(void) const {
		return (node);
	}

	reference operator*(void) const {
		return (node->data);
	}

	rb_tree_iterator& operator++(void) {
		node = Tree_Node::successor(node);
		return (*this);
	}

	rb_tree_iterator operator++(int) {
		Node_ptr tmp = node;
		node = Tree_Node::successor(node);
		return (rb_tree_iterator(tmp));
	}

	rb_tree_iterator& operator--(void) {
		node = Tree_Node::predecessor(node);
		return (*this);
	}

	rb_tree_iterator operator--(int) {
		Node_ptr tmp = node;
		node = Tree_Node::predecessor(node);
		return (rb_tree_iterator(tmp));
	}

	pointer operator->(void) const {
		return (&(operator*()));
	}
};

template <typename IteratorL, typename IteratorR>
inline bool operator==(const rb_tree_iterator<IteratorL>& lhs,
											 const rb_tree_iterator<IteratorR>& rhs) {
	return (lhs.base() == rhs.base());
}

template <typename Iterator>
inline bool operator==(const rb_tree_iterator<Iterator>& lhs,
											 const rb_tree_iterator<Iterator>& rhs) {
	return (lhs.base() == rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const rb_tree_iterator<IteratorL>& lhs,
											 const rb_tree_iterator<IteratorR>& rhs) {
	return (lhs.base() != rhs.base());
}

template <typename Iterator>
inline bool operator!=(const rb_tree_iterator<Iterator>& lhs,
											 const rb_tree_iterator<Iterator>& rhs) {
	return (lhs.base() != rhs.base());
}

}

#endif
