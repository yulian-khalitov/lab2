#pragma once
#include <string>
#include <vector>
#include <iostream>

template<class T_key, class T_val>
class Map {
	enum color { RED, BLACK };
	struct Node {
		T_key key;
		T_val value;
		color col;
		Node* p;
		Node* left;
		Node* right;
		Node(color col) : col{ col } {}
		Node(T_key key, T_val value, color col = RED) : key{ key }, value{ value },
			p{ nil }, left{ nil }, right{ nil }, col{ col } {}
	};
	Node* root;
	inline static int size = 0;
	inline static Node* nil = new Node(BLACK);
	void left_rotate(Node*);
	void right_rotate(Node*);
	void insert_fixup(Node*);
	auto minimum(Node*);
	void transplant(Node*, Node*);
	void remove_fixup(Node*);
	void clear_subtree(Node*);
	void get_keys_subtree(Node*, std::vector<T_key>&);
	void get_values_subtree(Node*, std::vector<T_val>&);
	void print_subtree(Node*);
public:
	Map() : root{ nil } {}
	void insert(T_key, T_val);
	void remove(T_key);
	T_val find(T_key, T_val);
	void clear();
	std::vector<T_key> get_keys();
	std::vector<T_val> get_values();
	void print();
	int node_count();
};

template <class T_key, class T_val>
void Map<T_key, T_val>::left_rotate(Node* node)
{
	Node* node_right = node->right;
	node->right = node_right->left;
	if (node_right->left != nil) node_right->left->p = node;
	node_right->p = node->p;
	if (node->p == nil) root = node_right;
	else if (node == node->p->left) node->p->left = node_right;
	else node->p->right = node_right;
	node_right->left = node;
	node->p = node_right;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::right_rotate(Node * node)
{
	Node* node_left = node->left;
	node->left = node_left->right;
	if (node_left->right != nil) node_left->right->p = node;
	node_left->p = node->p;
	if (node->p == nil) root = node_left;
	else if (node == node->p->left) node->p->left = node_left;
	else node->p->right = node_left;
	node_left->right = node;
	node->p = node_left;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::insert_fixup(Node * node)
{
	Node* node_uncle;
	while (node->p->col == RED)
	{
		if (node->p == node->p->p->left)
		{
			node_uncle = node->p->p->right;
			if (node_uncle->col == RED)
			{
				node->p->col = BLACK;
				node_uncle->col = BLACK;
				node->p->p->col = RED;
				node = node->p->p;
			}
			else {
				if (node == node->p->right) {
					node = node->p;
					left_rotate(node);
				}
				node->p->col = BLACK;
				node->p->p->col = RED;
				right_rotate(node->p->p);
			}
		}
		else
		{
			node_uncle = node->p->p->left;
			if (node_uncle->col == RED)
			{
				node->p->col = BLACK;
				node_uncle->col = BLACK;
				node->p->p->col = RED;
				node = node->p->p;
			}
			else
			{
				if (node == node->p->left) {
					node = node->p;
					right_rotate(node);
				}
				node->p->col = BLACK;
				node->p->p->col = RED;
				left_rotate(node->p->p);
			}
		}
	}
	root->col = BLACK;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::insert(T_key key, T_val val)
{
	Node* cur_node_p = nil;
	Node* cur_node = root;
	while (cur_node != nil && cur_node->key != key)
	{
		cur_node_p = cur_node;
		if (key < cur_node->key) cur_node = cur_node->left;
		else cur_node = cur_node->right;
	}
	if (cur_node == nil)
	{
		Node* insert_node = new Node(key, val);
		insert_node->p = cur_node_p;
		if (cur_node_p == nil) root = insert_node;
		else if (insert_node->key < cur_node_p->key) cur_node_p->left = insert_node;
		else cur_node_p->right = insert_node;
		insert_fixup(insert_node);
		++size;
	}
	else cur_node->value = val;
}

template <class T_key, class T_val>
auto Map<T_key, T_val>::minimum(Node* node)
{
	while (node->left != nil) node = node->left;
	return node;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::transplant(Node* old_node, Node* new_node)
{
	if (old_node->p == nil) root = new_node;
	else if (old_node == old_node->p->left) old_node->p->left = new_node;
	else old_node->p->right = new_node;
	new_node->p = old_node->p;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::remove_fixup(Node* node)
{
	while (node != root && node->col == BLACK)
	{
		if (node == node->p->left)
		{
			Node* node_sibling = node->p->right;
			if (node_sibling->col == RED)
			{
				node_sibling->col = BLACK;
				node->p->col = RED;
				left_rotate(node->p);
				node_sibling = node->p->right;
			}
			if (node_sibling->left->col == BLACK && node_sibling->right->col == BLACK)
			{
				node_sibling->col = RED;
				node = node->p;
			}
			else
			{
				if (node_sibling->right->col == BLACK)
				{
					node_sibling->left->col = BLACK;
					node_sibling->col = RED;
					right_rotate(node_sibling);
					node_sibling = node->p->right;
				}
				node_sibling->col = node->p->col;
				node->p->col = BLACK;
				node_sibling->right->col = BLACK;
				left_rotate(node->p);
				node = root;
			}
		}
		else
		{
			Node* node_sibling = node->p->left;
			if (node_sibling->col == RED)
			{
				node_sibling->col = BLACK;
				node->p->col = RED;
				right_rotate(node->p);
				node_sibling = node->p->left;
			}
			if (node_sibling->right->col == BLACK && node_sibling->left->col == BLACK)
			{
				node_sibling->col = RED;
				node = node->p;
			}
			else
			{
				if (node_sibling->left->col == BLACK)
				{
					node_sibling->right->col = BLACK;
					node_sibling->col = RED;
					left_rotate(node_sibling);
					node_sibling = node->p->left;
				}
				node_sibling->col = node->p->col;
				node->p->col = BLACK;
				node_sibling->left->col = BLACK;
				right_rotate(node->p);
				node = root;
			}
		}
	}
	node->col = BLACK;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::remove(T_key key)
{
	Node* remove_node = root;
	while (remove_node != nil && remove_node->key != key)
	{
		if (key < remove_node->key) remove_node = remove_node->left;
		else remove_node = remove_node->right;
	}
	if (remove_node == nil) throw std::out_of_range{ "remove element out of range" };
	Node * fixup_node;
	/*тут будем хранить цвет либо удаяемого узла,
	либо узла следуюшего за удаляемым в порядке центрированного обхода*/
	color help_node_orig_color = remove_node->col;
	if (remove_node->left == nil)
	{
		fixup_node = remove_node->right;
		transplant(remove_node, remove_node->right);
	}
	else if (remove_node->right == nil)
	{
		fixup_node = remove_node->left;
		transplant(remove_node, remove_node->left);
	}
	else
	{
		Node* inorder_next = minimum(remove_node->right);
		help_node_orig_color = inorder_next->col;
		fixup_node = inorder_next->right;
		if (inorder_next->p == remove_node)
		{
			fixup_node->p = inorder_next;
		}
		else
		{
			transplant(inorder_next, inorder_next->right);
			inorder_next->right = remove_node->right;
			inorder_next->right->p = inorder_next;
		}
		transplant(remove_node, inorder_next);
		inorder_next->left = remove_node->left;
		inorder_next->left->p = inorder_next;
		inorder_next->col = remove_node->col;
	}
	if (help_node_orig_color == BLACK) remove_fixup(fixup_node);
}

template <class T_key, class T_val>
T_val Map<T_key, T_val>::find(T_key key, T_val nil_value)
{
	Node* node = root;
	while (node != nil)
	{
		if (key == node->key) return node->value;
		else if (key < node->key) node = node->left;
		else node = node->right;
	}
	return nil_value;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::clear_subtree(Node* node)
{
	if (node != nil)
	{
		clear_subtree(node->left);
		clear_subtree(node->right);
		delete node;
	}
}

template <class T_key, class T_val>
void Map<T_key, T_val>::clear()
{
	clear_subtree(root);
	root = nil;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::get_keys_subtree(Node* node, std::vector<T_key>& v)
{
	if (node != nil)
	{
		get_keys_subtree(node->left, v);
		v.push_back(node->key);
		get_keys_subtree(node->right, v);
	}
}

template <class T_key, class T_val>
std::vector<T_key> Map<T_key, T_val>::get_keys()
{
	std::vector<T_key> v;
	get_keys_subtree(root, v);
	return v;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::get_values_subtree(Node* node, std::vector<T_val>& v)
{
	if (node != nil)
	{
		get_values_subtree(node->left, v);
		v.push_back(node->value);
		get_values_subtree(node->right, v);
	}
}

template <class T_key, class T_val>
std::vector<T_val> Map<T_key, T_val>::get_values()
{
	std::vector<T_val> v;
	get_values_subtree(root, v);
	return v;
}

template <class T_key, class T_val>
void Map<T_key, T_val>::print_subtree(Node * node)
{
	if (node != nil)
	{
		print_subtree(node->left);
		std::cout << "(" << node->key << ": " << node->value << ")" << std::endl;
		print_subtree(node->right);
	}
}

template <class T_key, class T_val>
void Map<T_key, T_val>::print()
{
	print_subtree(root);
}

template<class T_key, class T_val>
int Map<T_key, T_val>::node_count()
{
	return size;
}
