#ifndef RB_TREE_NODE_H
#define RB_TREE_NODE_H

namespace ft {

enum Rb_tree_color {
	RED = true,
	BLACK = false
};

template <typename T>
struct RBT_Node {
	typedef RBT_Node<T>			Tree_Node;
	typedef Tree_Node*		Node_ptr;
	typedef const Tree_Node*	Const_node_ptr;

	explicit RBT_Node(const T& _data, Node_ptr _root, Node_ptr _leaf,
							Node_ptr _parent = NULL,
							Node_ptr _left = NULL,
							Node_ptr _right = NULL,
							Rb_tree_color _color = BLACK)
	: data(_data), root(_root), leaf(_leaf), parent(_parent), left(_left), right(_right), color(_color)
		{}

	T						data;
	Node_ptr				root;
	Node_ptr				leaf;
	Node_ptr				parent;
	Node_ptr				left;
	Node_ptr				right;
	Rb_tree_color			color;

	static Node_ptr get_root(Node_ptr node) {
		return (node->leaf->root);
	}

	static Node_ptr minimum(Node_ptr node) {
		while (node->left != node->leaf) {
			node = node->left;
		}
		return (node);
	}

	static Node_ptr maximum(Node_ptr node) {
		while (node->right != node->leaf) {
			node = node->right;
		}
		return (node);
	}

	static Node_ptr successor(Node_ptr x) {
		if (x == x->leaf) {
			return (maximum(get_root(x)));
		}
		if (x->right != x->leaf) {
			return (minimum(x->right));
		}
		Node_ptr y = x->parent;
		while (y != y->leaf && x == y->right) {
			x = y;
			y = y->parent;
		}
		return (y);
	}

	static Node_ptr predecessor(Node_ptr x) {
		if (x == x->leaf) {
			return (maximum(get_root(x)));
		}
		if (x->left != x->leaf) {
			return (maximum(x->left));
		}
		Node_ptr y = x->parent;
		while (y != y->leaf && x == y->left) {
			x = y;
			y = y->parent;
		}
		return (y);
	}
};

}

#endif
