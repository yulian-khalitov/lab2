#include "Priority_queue.h"

int Priority_queue::left(int i)
{
	return 2 * i + 1;
}

int Priority_queue::right(int i)
{
	return 2 * i + 2;
}

int Priority_queue::parent(int i)
{
	return (i - 1) / 2;
}

void Priority_queue::up(int i)
{
	while (i != 0 && data[i]->freq < data[parent(i)]->freq)
	{
		std::swap(data[i], data[parent(i)]);
		i = parent(i);
	}
}

void Priority_queue::down(int i)
{
	int l = left(i);
	int r = right(i);
	int least = i;
	if (l < size && data[l]->freq < data[i]->freq) least = l;
	if (r < size && data[r]->freq < data[least]->freq) least = r;
	if (i != least)
	{
		std::swap(data[i], data[least]);
		down(least);
	}
}

Priority_queue::Priority_queue(Map<char, int>& map) : MAX_SIZE{ map.node_count() }, size{ MAX_SIZE }
{
	std::vector<char> char_vec = map.get_keys();
	std::vector<int> freq_vec = map.get_values();
	data = new Node * [size];
	for (int i = 0; i < size; ++i) data[i] = new Node(char_vec[i], freq_vec[i]);
	for (int i = size / 2 - 1; i >= 0; --i) down(i);
}

Node* Priority_queue::extract_min()
{
	if (size <= 0) throw "nothing to extract";
	Node * min = data[0];
	data[0] = data[size - 1];
	--size;
	down(0);
	return min;
}

void Priority_queue::insert(Node* node)
{
	if (size + 1 > MAX_SIZE) throw "the queue is full";
	data[size++] = node;
	up(size - 1);
}

int Priority_queue::cur_size()
{
	return size;
}









