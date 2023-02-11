#ifndef RB_TREE_ITERATOR_REVERSE_H
#define RB_TREE_ITERATOR_REVERSE_H

#include "./iterator_traits.hpp"
#include "./rb_tree_node.hpp"

namespace ft {

template <typename Iterator>
class rb_tree_reverse_iterator
		: public iterator<typename iterator_traits<Iterator>::iterator_category,
											typename iterator_traits<Iterator>::value_type,
											typename iterator_traits<Iterator>::difference_type,
											typename iterator_traits<Iterator>::pointer,
											typename iterator_traits<Iterator>::reference> {
 public:
	typedef Iterator iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;

	typedef _Rb_tree_node<value_type> Rb_tree_node;
	typedef Rb_tree_node* Node_ptr;
	typedef const Rb_tree_node* Const_node_ptr;

 protected:
	Node_ptr node;

 public:
	rb_tree_reverse_iterator(void) : node(NULL) {}

	explicit rb_tree_reverse_iterator(Node_ptr _node) : node(_node) {}

	explicit rb_tree_reverse_iterator(iterator_type x) : node(x.base()) {}

	rb_tree_reverse_iterator(const rb_tree_reverse_iterator& x) : node(x.node) {}

	template <typename Iter>
	rb_tree_reverse_iterator(const rb_tree_reverse_iterator<Iter>& x) : node(x.base()) {}

	~rb_tree_reverse_iterator(void) {}

	template <typename Iter>
	rb_tree_reverse_iterator& operator=(const rb_tree_reverse_iterator<Iter>& x) {
		node = x.base();
		return (*this);
	}

	Node_ptr base(void) const {
		return (node);
	}

	reference operator*(void) const {
		Node_ptr tmp = Rb_tree_node::predecessor(node);
		return (tmp->data);
	}

	rb_tree_reverse_iterator& operator++(void) {
		node = Rb_tree_node::predecessor(node);
		return (*this);
	}

	rb_tree_reverse_iterator operator++(int) {
		Node_ptr tmp = node;
		node = Rb_tree_node::predecessor(node);
		return (rb_tree_reverse_iterator(tmp));
	}

	rb_tree_reverse_iterator& operator--(void) {
		node = Rb_tree_node::successor(node);
		return (*this);
	}

	rb_tree_reverse_iterator operator--(int) {
		Node_ptr tmp = node;
		node = Rb_tree_node::successor(node);
		return (rb_tree_reverse_iterator(tmp));
	}

	pointer operator->(void) const {
		return (&(this->operator*()));
	}
};

template <typename IteratorL, typename IteratorR>
inline bool operator==(const rb_tree_reverse_iterator<IteratorL>& x,
											 const rb_tree_reverse_iterator<IteratorR>& y) {
	return (x.base() == y.base());
}

template <typename Iterator>
inline bool operator==(const rb_tree_reverse_iterator<Iterator>& x,
											 const rb_tree_reverse_iterator<Iterator>& y) {
	return (x.base() == y.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const rb_tree_reverse_iterator<IteratorL>& x,
											 const rb_tree_reverse_iterator<IteratorR>& y) {
	return (!(x == y));
}

template <typename Iterator>
inline bool operator!=(const rb_tree_reverse_iterator<Iterator>& x,
											 const rb_tree_reverse_iterator<Iterator>& y) {
	return (!(x == y));
}

}

#endif
