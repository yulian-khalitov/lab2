#pragma once
#include "Map.h"

struct Node
{
	char c;
	int freq;
	Node* left;
	Node* right;
	Node(char c, int freq) : c{ c }, freq{ freq }, left{ nullptr }, right{ nullptr } {}
	Node(char c, int freq, Node* left, Node* right) : c{ c }, freq { freq }, left{ left }, right{ right } {}
};

class Priority_queue 
{
	Node** data;
	const int MAX_SIZE;
	int size;
	int left(int);
	int right(int);
	int parent(int);
	void up(int);
	void down(int);
public:
	Priority_queue(Map<char, int>&);
	Node* extract_min();
	void insert(Node*);
	int cur_size();
};