#include "Huffman.h"

Node* create_huffman_tree(Map<char, int>& freq)
{
	Priority_queue queue(freq);
	int queue_size = queue.cur_size();
	for (int i = 0; i < queue_size - 1; ++i)
	{
		Node* left_node = queue.extract_min();
		Node* right_node = queue.extract_min();
		Node* new_node = new Node('\0', left_node->freq + right_node->freq, left_node, right_node);
		queue.insert(new_node);
	}
	return queue.extract_min();
}


std::string encode(std::string input_string, Map<char, std::string>& codes)
{
	std::string encode_string = "";
	for (char c : input_string) encode_string += codes.find(c, "err");
	return encode_string;
}

std::string decode(std::string encoded_string, Node* huffman_tree)
{
	Node* cur_node = huffman_tree;
	std::string decoded_string = "";
	for (char c : encoded_string)
	{
		if (c == '0') cur_node = cur_node->left;
		else if (c == '1') cur_node = cur_node->right;
		if (cur_node->left == nullptr && cur_node->right == nullptr)
		{
			decoded_string += cur_node->c;
			cur_node = huffman_tree;
		}
	}
	return decoded_string;
}

void create_huffman_codes_map(Map<char, std::string>& codes, Node* root, std::string str)
{
	if (root == nullptr) return;
	if (root->c != '\0') codes.insert(root->c, str);
	create_huffman_codes_map(codes, root->left, str + "0");
	create_huffman_codes_map(codes, root->right, str + "1");
}

