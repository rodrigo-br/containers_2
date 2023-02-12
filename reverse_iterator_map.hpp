#ifndef RB_TREE_ITERATOR_REVERSE_H
#define RB_TREE_ITERATOR_REVERSE_H

#include "./iterator_traits.hpp"
#include "./RBT_Node.hpp"

namespace ft {

template <typename Iterator>
#define TRAITS iterator_traits<Iterator>
class rbt_reverse_iterator
		: public TRAITS, public iterator<typename TRAITS::iterator_category,
						typename TRAITS::value_type,
						typename TRAITS::difference_type,
						typename TRAITS::pointer,
						typename TRAITS::reference> {
 public:
	typedef Iterator							iterator_type;
	IMPORT_TRAIT(iterator_category);
	IMPORT_TRAIT(value_type);
	IMPORT_TRAIT(difference_type);
	IMPORT_TRAIT(pointer);
	IMPORT_TRAIT(reference);
	typedef RBT_Node<value_type>				Tree_Node;
	typedef Tree_Node*							Node_ptr;
	typedef const Tree_Node*					Const_node_ptr;

 protected:
	Node_ptr														node;

 public:
	rbt_reverse_iterator(void) : node(NULL) {}

	explicit rbt_reverse_iterator(Node_ptr _node) : node(_node) {}

	explicit rbt_reverse_iterator(iterator_type x) : node(x.base()) {}

	rbt_reverse_iterator(const rbt_reverse_iterator& x) : node(x.node) {}

	template <typename Iter>
	rbt_reverse_iterator(const rbt_reverse_iterator<Iter>& x) : node(x.base()) {}

	~rbt_reverse_iterator(void) {}

	template <typename Iter>
	rbt_reverse_iterator& operator=(const rbt_reverse_iterator<Iter>& x) {
		node = x.base();
		return (*this);
	}

	Node_ptr base(void) const {
		return (node);
	}

	reference operator*(void) const {
		Node_ptr tmp = Tree_Node::predecessor(node);
		return (tmp->data);
	}

	rbt_reverse_iterator& operator++(void) {
		node = Tree_Node::predecessor(node);
		return (*this);
	}

	rbt_reverse_iterator operator++(int) {
		Node_ptr tmp = node;
		node = Tree_Node::predecessor(node);
		return (rbt_reverse_iterator(tmp));
	}

	rbt_reverse_iterator& operator--(void) {
		node = Tree_Node::successor(node);
		return (*this);
	}

	rbt_reverse_iterator operator--(int) {
		Node_ptr tmp = node;
		node = Tree_Node::successor(node);
		return (rbt_reverse_iterator(tmp));
	}

	pointer operator->(void) const {
		return (&(this->operator*()));
	}
	#undef TRAITS
};

template <typename IteratorL, typename IteratorR>
inline bool operator==(const rbt_reverse_iterator<IteratorL>& x,
											 const rbt_reverse_iterator<IteratorR>& y) {
	return (x.base() == y.base());
}

template <typename Iterator>
inline bool operator==(const rbt_reverse_iterator<Iterator>& x,
											 const rbt_reverse_iterator<Iterator>& y) {
	return (x.base() == y.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const rbt_reverse_iterator<IteratorL>& x,
											 const rbt_reverse_iterator<IteratorR>& y) {
	return (!(x == y));
}

template <typename Iterator>
inline bool operator!=(const rbt_reverse_iterator<Iterator>& x,
											 const rbt_reverse_iterator<Iterator>& y) {
	return (!(x == y));
}

}

#endif
