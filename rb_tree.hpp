#ifndef RB_TREE_H
#define RB_TREE_H

#include <memory>

#include "./Container.hpp"
#include "./algorithm.hpp"
#include "./bidirectional_iterator.hpp"
#include "./reverse_iterator_map.hpp"
#include "./rb_tree_node.hpp"

namespace ft {
#define CONTAINER Container<Val, Alloc>
template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Val> >
class Rb_tree : public CONTAINER {
	typedef typename Alloc::template rebind<_Rb_tree_node<Val> >::other Node_allocator;

 public:
	typedef _Rb_tree_node<Val>								Rb_tree_node;
	typedef Rb_tree_node*									Node_ptr;
	typedef const Rb_tree_node*								Const_node_ptr;

 public:
	typedef Key 											key_type;
	typedef Compare 										key_compare;
	IMPORT_TYPE(value_type);
	IMPORT_TYPE(pointer);
	IMPORT_TYPE(const_pointer);
	IMPORT_TYPE(reference);
	IMPORT_TYPE(const_reference);
	IMPORT_TYPE(size_type);
	IMPORT_TYPE(difference_type);
	typedef Node_allocator 									allocator_type;
	typedef ft::rb_tree_iterator<pointer> 					iterator;
	typedef ft::rb_tree_iterator<const_pointer> 			const_iterator;
	typedef ft::rb_tree_reverse_iterator<iterator> 			reverse_iterator;
	typedef ft::rb_tree_reverse_iterator<const_iterator>	const_reverse_iterator;

 public:
	explicit Rb_tree(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) {
		_alloc = alloc;
		TNULL = _alloc.allocate(1);
		_alloc.construct(TNULL, create_node(value_type(), BLACK));
		root = TNULL;
		_size = 0;
		_comp = comp;
	};

	Rb_tree(const Rb_tree& src) {
		_alloc = src._alloc;
		TNULL = _alloc.allocate(1);
		_alloc.construct(TNULL, create_node(value_type(), BLACK));
		root = TNULL;
		copy_rb_tree(src.root);
		_size = src._size;
		_comp = src._comp;
	};

	Rb_tree& operator=(const Rb_tree& rhs) {
		if (this != &rhs) {
			this->~Rb_tree();
			_alloc = rhs._alloc;
			TNULL = _alloc.allocate(1);
			_alloc.construct(TNULL, create_node(value_type(), BLACK));
			root = TNULL;
			copy_rb_tree(rhs.root);
			_size = rhs._size;
			_comp = rhs._comp;
		}
		return (*this);
	};

	~Rb_tree(void) {
		destructor_helper(root);
		_alloc.destroy(TNULL);
		_alloc.deallocate(TNULL, 1);
		_size = 0;
	};

	iterator begin(void) {
		return (iterator(minimum(root)));
	};

	const_iterator begin(void) const {
		return (const_iterator(minimum(root)));
	};

	iterator end(void) {
		return (iterator(TNULL));
	};

	const_iterator end(void) const {
		return (const_iterator(TNULL));
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

	bool empty(void) const {
		return (_size == 0);
	};

	size_type size(void) const {
		return (_size);
	};

	size_type max_size(void) const {
		return (_alloc.max_size());
	};

	void swap(Rb_tree& x) {
		allocator_type tmp_alloc = x._alloc;
		Node_ptr tmp_root = x.root;
		Node_ptr tmp_TNULL = x.TNULL;
		size_type tmp_size = x._size;
		key_compare tmp_comp = x._comp;

		x._alloc = _alloc;
		x.root = root;
		x.TNULL = TNULL;
		x._size = _size;
		x._comp = _comp;

		_alloc = tmp_alloc;
		root = tmp_root;
		TNULL = tmp_TNULL;
		_size = tmp_size;
		_comp = tmp_comp;
	};

	void clear(void) {
		destructor_helper(root);
		root = TNULL;
		_size = 0;
	};

	key_compare key_comp(void) const {
		return (_comp);
	};

	iterator lower_bound(const key_type& k) {
		Node_ptr x = root;
		Node_ptr y = TNULL;

		while (x != TNULL)
			if (!_comp(KeyOfValue()(x->data), k))
				y = x, x = x->left;
			else
				x = x->right;

		return (iterator(y));
	};

	const_iterator lower_bound(const key_type& k) const {
		Node_ptr x = root;
		Node_ptr y = TNULL;

		while (x != TNULL)
			if (!_comp(KeyOfValue()(x->data), k))
				y = x, x = x->left;
			else
				x = x->right;

		return (const_iterator(y));
	};

	iterator upper_bound(const key_type& k) {
		Node_ptr x = root;
		Node_ptr y = TNULL;

		while (x != TNULL)
			if (_comp(k, KeyOfValue()(x->data)))
				y = x, x = x->left;
			else
				x = x->right;

		return (iterator(y));
	};

	const_iterator upper_bound(const key_type& k) const {
		Node_ptr x = root;
		Node_ptr y = TNULL;

		while (x != TNULL)
			if (_comp(k, KeyOfValue()(x->data)))
				y = x, x = x->left;
			else
				x = x->right;

		return (const_iterator(y));
	};

	allocator_type get_allocator(void) const {
		return (_alloc);
	};

	Node_ptr search(Key k) const {
		return (search_helper(root, k));
	};

	Node_ptr search(Key k, Node_ptr _root) const {
		return (search_helper(_root, k));
	};

	Node_ptr minimum(Node_ptr node) const {
		return (Rb_tree_node::minimum(node));
	};

	Node_ptr maximum(Node_ptr node) const {
		return (Rb_tree_node::maximum(node));
	};

	Node_ptr successor(Node_ptr x) const {
		return (Rb_tree_node::successor(x));
	};

	Node_ptr predecessor(Node_ptr x) const {
		return (Rb_tree_node::predecessor(x));
	};

	void insert(value_type data) {
		Node_ptr z = search(KeyOfValue()(data));
		if (z != TNULL) {
			erase_node_helper(z);
		}
		insert_node_helper(data);
	};

	void insert(value_type data, Node_ptr _root) {
		Node_ptr z = search(KeyOfValue()(data), _root);
		if (z != TNULL) {
			erase_node_helper(z);
		}
		insert_node_helper(data);
	};

	iterator insert_unique(value_type data)
		{
			return(insert_node_helper(data));
		};

	void erase(Key key)
		{
			Node_ptr z = search(key);
			if (z == TNULL) {
				return;
			}
			erase_node_helper(z);
		};

	Node_ptr get_root(void)
		{
		return (root);
		};

	private:
		allocator_type							_alloc;
		Node_ptr								root;
		Node_ptr								TNULL;
		size_type								_size;
		key_compare								_comp;

	void left_rotate(Node_ptr x) {
		Node_ptr y;

		y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}

		y->parent = x->parent;
		if (x->parent == TNULL) {
			root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}

		y->left = x;
		x->parent = y;
	};

	void right_rotate(Node_ptr x) {
		Node_ptr y;

		y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}

		y->parent = x->parent;
		if (x->parent == TNULL) {
			root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}

		y->right = x;
		x->parent = y;
	};

	void destructor_helper(Node_ptr node) {
		if (node != TNULL) {
			destructor_helper(node->left);
			destructor_helper(node->right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}
	};

	Node_ptr search_helper(Node_ptr node, Key key) const {
		if (node == TNULL || (!_comp(key, KeyOfValue()(node->data)) &&
													!_comp(KeyOfValue()(node->data), key))) {
			return (node);
		}
		if (_comp(key, KeyOfValue()(node->data))) {
			return (search_helper(node->left, key));
		} else {
			return (search_helper(node->right, key));
		}
	};

	iterator insert_node_helper(value_type data) {
		Node_ptr x = root;
		Node_ptr y = TNULL;
		Node_ptr z = _alloc.allocate(1);
		_alloc.construct(z, create_node(data, RED));

		while (x != TNULL) {
			y = x;
			if (_comp(KeyOfValue()(z->data), KeyOfValue()(x->data))) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		z->parent = y;

		if (y == TNULL) {
			root = z;
		} else if (_comp(KeyOfValue()(z->data), KeyOfValue()(y->data))) {
			y->left = z;
		} else {
			y->right = z;
			z->left = TNULL;
			z->right = TNULL;
			z->color = RED;
		}

		insert_fix(z);
		TNULL->root = root;
		_size++;

		return(iterator(z));
	};

	void erase_fix(Node_ptr x) {
		Node_ptr w;

		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				w = x->parent->right;

				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					left_rotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						right_rotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					left_rotate(x->parent);
					x = root;
				}
			} else {
				w = x->parent->left;

				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					right_rotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else {
					if (w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						left_rotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					right_rotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	};

	void transplant(Node_ptr u, Node_ptr v) {
		if (u->parent == TNULL) {
			root = v;
		} else if (u == u->parent->left) {
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	};

	void erase_node_helper(Node_ptr z) {
		Node_ptr x, y;
		Rb_tree_color y_original_color;

		y = z;
		y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			transplant(z, z->right);
		} else if (z->right == TNULL) {
			x = z->left;
			transplant(z, z->left);
		} else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (z != z->right) {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			} else {
				x->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

		_alloc.destroy(z);
		_alloc.deallocate(z, 1);

		if (y_original_color == BLACK) {
			erase_fix(x);
		}
		TNULL->root = root;
		_size--;
	};

	void insert_fix(Node_ptr z) {
		Node_ptr y;

		while (z->parent->color == RED) {
			if (z->parent == z->parent->parent->left) {
				y = z->parent->parent->right;
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				} else {
					if (z == z->parent->right) {
						z = z->parent;
						left_rotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					right_rotate(z->parent->parent);
				}
			} else {
				y = z->parent->parent->left;
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				} else {
					if (z == z->parent->left) {
						z = z->parent;
						right_rotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					left_rotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	};

	void copy_rb_tree(Node_ptr node) {
		if (node != node->leaf) {
			insert_unique(node->data);
			copy_rb_tree(node->left);
			copy_rb_tree(node->right);
		}
	};

	Rb_tree_node create_node(value_type data, Rb_tree_color color) {
		return (Rb_tree_node(data, root, TNULL, TNULL, TNULL, TNULL, color));
	};
};
#undef CONTAINER

	template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
	inline bool operator==(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
							const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y) {
		return (x.size() == y.size() &&
						ft::equal(x.begin(), x.end(), y.begin()));
	}

	template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
	inline bool operator!=(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
							const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y) {
		return (!(x == y));
	}

	template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
	inline bool operator<(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
							const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y) {
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
	inline bool operator<=(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
							const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y) {
		return (!(y < x));
	}

	template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
	inline bool operator>(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
							const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y) {
		return (y < x);
	}

	template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
	inline bool operator>=(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
							const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y) {
		return (!(x < y));
	}

};
#endif
