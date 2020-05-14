#pragma once
#include "Map.h"
#include "Priority_queue.h"

Node* create_huffman_tree(Map<char, int>&);
std::string encode(std::string, Map<char, std::string>&);
std::string decode(std::string, Node*);
void create_huffman_codes_map(Map<char, std::string>&, Node*, std::string);
