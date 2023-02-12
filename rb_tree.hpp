#ifndef RB_TREE_H
#define RB_TREE_H

#include <memory>

#include "./Container.hpp"
#include "./algorithm.hpp"
#include "./bidirectional_iterator.hpp"
#include "./reverse_iterator_map.hpp"
#include "./RBT_Node.hpp"

namespace ft {
#define CONTAINER Container<Val, Alloc>
template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Val> >
class Rb_tree : public CONTAINER {
private:
	typedef typename Alloc::template rebind<RBT_Node<Val> >::other Node_allocator;

public:
	IMPORT_TYPE(value_type);
	IMPORT_TYPE(pointer);
	IMPORT_TYPE(const_pointer);
	IMPORT_TYPE(reference);
	IMPORT_TYPE(const_reference);
	IMPORT_TYPE(size_type);
	IMPORT_TYPE(difference_type);
	typedef RBT_Node<Val>								Tree_Node;
	typedef Tree_Node*									Node_ptr;
	typedef const Tree_Node*							Const_node_ptr;
	typedef Key 										key_type;
	typedef Compare 									key_compare;
	typedef Node_allocator 								allocator_type;
	typedef ft::bidirectional_iterator<pointer> 		iterator;
	typedef ft::bidirectional_iterator<const_pointer> 	const_iterator;
	typedef ft::rbt_reverse_iterator<iterator> 			reverse_iterator;
	typedef ft::rbt_reverse_iterator<const_iterator>	const_reverse_iterator;

private:
		Node_ptr								_root;
		allocator_type							_alloc;
		Node_ptr								_dummy;
		size_type								_size;
		key_compare								_comp;

	static Color getColor(Const_node_ptr x)
	{
		return (x == NULL ? BLACK : x->color);
	};

	static void setColor(Node_ptr x, Color c)
	{
		if (x != NULL)
			x->color = c;
	};

	static bool isRed(Const_node_ptr x)
	{
		return (getColor(x) == RED);
	};

	static bool isBlack(Const_node_ptr x)
	{
		return (getColor(x) == BLACK);
	};

	static bool isNullOrBlack(Const_node_ptr x)
	{
		return (x == NULL || isBlack(x));
	};

 public:

 /*****************************************************************************\
 * 					CONSTRUCTORS / DESTRUCTOR								   *
 \*****************************************************************************/

	explicit Rb_tree(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _dummy(_alloc.allocate(1)), _size(0), _comp(comp) {
		_alloc.construct(_dummy, create_node(value_type(), BLACK));
		_root = _dummy;
	};

	Rb_tree(const Rb_tree& x) : _alloc(x._alloc), _dummy(_alloc.allocate(1)), _comp(x._comp), _size(x._size) {
		_alloc.construct(_dummy, create_node(value_type(), BLACK));
		_root = _dummy;
		copy(x._root);
	};

	Rb_tree& operator=(const Rb_tree& rhs) {
		if (this != &rhs) {
			this->~Rb_tree();
			_alloc = rhs._alloc;
			_dummy = _alloc.allocate(1);
			_alloc.construct(_dummy, create_node(value_type(), BLACK));
			_root = _dummy;
			copy(rhs._root);
			_size = rhs._size;
			_comp = rhs._comp;
		}
		return (*this);
	};

	~Rb_tree(void) {
		_clear(_root);
		_alloc.destroy(_dummy);
		_alloc.deallocate(_dummy, 1);
		_size = 0;
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
		if (this == &x)
			return;
		if (_alloc == x._alloc)
		{
			std::swap(_root, x._root);
			std::swap(_dummy, x._dummy);
			std::swap(_alloc, x._alloc);
			std::swap(_size, x._size);
			std::swap(_comp, x._comp);
		}
		else
		{
			std::swap(*this, x);
		}
	};

	void clear(void) {
		_clear(_root);
		_root = _dummy;
		_size = 0;
	};

	key_compare key_comp(void) const {
		return (_comp);
	};

	iterator lower_bound(const key_type& k) {
		Node_ptr ptr = _root;
		Node_ptr res = NULL;
		while (ptr != NULL)
		{
			if (_comp(k, KeyOfValue()(ptr->data)))
			{
				res = ptr;
				ptr = ptr->left;
			}
			else if (_comp(KeyOfValue()(ptr->data), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return iterator(ptr);
			}
		}
		return iterator(res);
	};

	const_iterator lower_bound(const key_type& k) const {
		Node_ptr ptr = _root;
		Node_ptr res = NULL;
		while (ptr != NULL)
		{
			if (_comp(k, KeyOfValue()(ptr->data)))
			{
				res = ptr;
				ptr = ptr->left;
			}
			else if (_comp(KeyOfValue()(ptr->data), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return const_iterator(ptr);
			}
		}
		return const_iterator(res);
	};

	iterator upper_bound(const key_type& k) {
		Node_ptr ptr = _root;
		Node_ptr res = NULL;
		while (ptr != NULL)
		{
			if (_comp(k, KeyOfValue()(ptr->data)))
			{
				res = ptr;
				ptr = ptr->left;
			}
			else if (_comp(KeyOfValue()(ptr->data), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return iterator(ptr->right);
			}
		}
		return iterator(res);
	};

	const_iterator upper_bound(const key_type& k) const {
		Node_ptr ptr = _root;
		Node_ptr res = NULL;
		while (ptr != NULL)
		{
			if (_comp(k, KeyOfValue()(ptr->data)))
			{
				res = ptr;
				ptr = ptr->left;
			}
			else if (_comp(KeyOfValue()(ptr->data), k))
			{
				ptr = ptr->right;
			}
			else
			{
				return const_iterator(ptr->right);
			}
		}
		return const_iterator(res);
	};

	allocator_type get_allocator(void) const { return (_alloc); };

	Node_ptr find(Key k) const { return (_find(_root, k)); };

	Node_ptr find(Key k, Node_ptr root) const { return (_find(root, k)); };

	Node_ptr minimum(Node_ptr node) const { return (Tree_Node::minimum(node)); };

	Node_ptr maximum(Node_ptr node) const { return (Tree_Node::maximum(node)); };

	Node_ptr successor(Node_ptr x) const { return (Tree_Node::successor(x)); };

	Node_ptr predecessor(Node_ptr x) const { return (Tree_Node::predecessor(x)); };

	void insert(value_type data) {
		Node_ptr z = find(KeyOfValue()(data));
		if (z != _dummy) {
			_erase(z);
		}
		_insert(data);
	};

	void insert(value_type data, Node_ptr root) {
		Node_ptr z = find(KeyOfValue()(data), root);
		if (z != _dummy) {
			_erase(z);
		}
		_insert(data);
	};

	iterator insert_unique(value_type data) { return(_insert(data)); };

	void erase(Key key)
	{
		Node_ptr z = find(key);
		if (z == _dummy) {
			return;
		}
		_erase(z);
	};
	
	iterator begin(void) { return (iterator(minimum(_root))); };

	const_iterator begin(void) const { return (const_iterator(minimum(_root))); };

	iterator end(void) { return (iterator(_dummy)); };

	const_iterator end(void) const {
		return (const_iterator(_dummy));
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

	Node_ptr getroot(void)
		{
		return (_root);
		};

	private:

	Node_ptr &getRefNode(Node_ptr x)
	{
		if (x == _root)
			return _root;
		Node_ptr parent = x->parent;

		return (parent->left == x ? parent->left : parent->right);
	};

	void rotateLeft(Node_ptr n) {
		Node_ptr &rp = this->getRefNode(n);

		rp = n->right;
		n->right = rp->left;
		rp->left = n;
		if (n->right != NULL)
			n->right->parent = n;
		rp->parent = n->parent;
		n->parent = rp;
	};

	void rotateRight(Node_ptr m) {
		Node_ptr &rp = this->getRefNode(m);

		rp = m->left;
		m->left = rp->right;
		rp->right = m;
		if (m->left != NULL)
			m->left->parent = m;
		rp->parent = m->parent;
		m->parent = rp;
	};

	void _clear(Node_ptr node) {
		if (node != _dummy) {
			_clear(node->left);
			_clear(node->right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}
	};

	Node_ptr _find(Node_ptr node, Key key) const {
		if (node == _dummy || (!_comp(key, KeyOfValue()(node->data)) &&
			!_comp(KeyOfValue()(node->data), key))) {
			return (node);
		}
		if (_comp(key, KeyOfValue()(node->data))) {
			return (_find(node->left, key));
		} else {
			return (_find(node->right, key));
		}
	};

	iterator _insert(value_type data) {
		Node_ptr x = _root;
		Node_ptr y = _dummy;
		Node_ptr z = _alloc.allocate(1);
		_alloc.construct(z, create_node(data, RED));

		while (x != _dummy) {
			y = x;
			if (_comp(KeyOfValue()(z->data), KeyOfValue()(x->data))) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		z->parent = y;
		if (y == _dummy) {
			_root = z;
		} else if (_comp(KeyOfValue()(z->data), KeyOfValue()(y->data))) {
			y->left = z;
		} else {
			y->right = z;
			z->left = _dummy;
			z->right = _dummy;
			setColor(z, RED);
		}
		insert_fix(z);
		_dummy->root = _root;
		_size++;

		return(iterator(z));
	};

	void erase_fix(Node_ptr x) {
		Node_ptr w;

		while (x != _root && isNullOrBlack(x)) {
			if (x == x->parent->left) {
				w = x->parent->right;

				if (isRed(w)) {
					setColor(w, BLACK);
					setColor(x->parent, RED);
					rotateLeft(x->parent);
					w = x->parent->right;
				}
				if (isNullOrBlack(w->left) && isNullOrBlack(w->right)) {
					setColor(w, RED);
					x = x->parent;
				} else {
					if (isNullOrBlack(w->right)) {
						setColor(w->left, BLACK);
						setColor(w, RED);
						rotateRight(w);
						w = x->parent->right;
					}
					setColor(w, getColor(x->parent));
					setColor(x->parent, BLACK);
					setColor(w->right, BLACK);
					rotateLeft(x->parent);
					x = _root;
				}
			} else {
				w = x->parent->left;

				if (isRed(w)) {
					setColor(w, BLACK);
					setColor(x->parent, RED);
					rotateRight(x->parent);
					w = x->parent->left;
				}
				if (isNullOrBlack(w->right) && isNullOrBlack(w->left)) {
					setColor(w, RED);
					x = x->parent;
				} else {
					if (isBlack(w->left)) {
						setColor(w->right, BLACK);
						setColor(w, RED);
						rotateLeft(w);
						w = x->parent->left;
					}
					setColor(w, getColor(x->parent));
					setColor(x->parent, BLACK);
					setColor(w->left, BLACK);
					rotateRight(x->parent);
					x = _root;
				}
			}
		}
		setColor(x, BLACK);
	};

	void transplant(Node_ptr u, Node_ptr v) {
		if (u->parent == _dummy) {
			_root = v;
		} else if (u == u->parent->left) {
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	};

	void _erase(Node_ptr z) {
		Node_ptr x, y;
		Color y_original_color;

		y = z;
		y_original_color = getColor(y);
		if (z->left == _dummy) {
			x = z->right;
			transplant(z, z->right);
		} else if (z->right == _dummy) {
			x = z->left;
			transplant(z, z->left);
		} else {
			y = minimum(z->right);
			y_original_color = getColor(y);
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
			setColor(y, getColor(z));
		}

		_alloc.destroy(z);
		_alloc.deallocate(z, 1);

		if (y_original_color == BLACK) {
			erase_fix(x);
		}
		_dummy->root = _root;
		_size--;
	};

	void insert_fix(Node_ptr z) {
		Node_ptr y;

		while (isRed(z->parent)) {
			if (z->parent == z->parent->parent->left) {
				y = z->parent->parent->right;
				if (isRed(y)) {
					setColor(z->parent, BLACK);
					setColor(y, BLACK);
					setColor(z->parent->parent, RED);
					z = z->parent->parent;
				} else {
					if (z == z->parent->right) {
						z = z->parent;
						rotateLeft(z);
					}
					setColor(z->parent, BLACK);
					setColor(z->parent->parent, RED);
					rotateRight(z->parent->parent);
				}
			} else {
				y = z->parent->parent->left;
				if (isRed(y)) {
					setColor(z->parent, BLACK);
					setColor(y, BLACK);
					setColor(z->parent->parent, RED);
					z = z->parent->parent;
				} else {
					if (z == z->parent->left) {
						z = z->parent;
						rotateRight(z);
					}
					setColor(z->parent, BLACK);
					setColor(z->parent->parent, RED);
					rotateLeft(z->parent->parent);
				}
			}
		}
		setColor(_root, BLACK);
	};

	void copy(Node_ptr node) {
		if (node != node->leaf) {
			insert_unique(node->data);
			copy(node->left);
			copy(node->right);
		}
	};

	Tree_Node create_node(value_type data, Color color) {
		return (Tree_Node(data, _root, _dummy, _dummy, _dummy, _dummy, color));
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
