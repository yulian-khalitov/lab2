#include <iostream>
#include <string>
#include "Map.h"
#include "Priority_queue.h"
#include "Huffman.h"

using namespace std;

int main()
{
	string input_string;
    cout << "Enter the string: ";
	getline(cin, input_string);

	Map<char, int> freq;
	for (char c : input_string) freq.insert(c, freq.find(c, 0) + 1);
	cout << "Frequency table: " << endl;
	freq.print();

	auto huffman_tree = create_huffman_tree(freq);
	Map<char, string> codes;
	create_huffman_codes_map(codes, huffman_tree, "");
	cout << "Huffman codes: " << endl;
	codes.print();

	string encoded_string = encode(input_string, codes);
	cout << "Encoded string: " << encoded_string << endl;
	string decoded_string = decode(encoded_string, huffman_tree);
	cout << "Decoded string: " << decoded_string << endl;
	int encoded_size = encoded_string.size();
	int decoded_size = decoded_string.size() * 8;
	double coef = (double)decoded_size / encoded_size;
	cout << "Input string size: " << decoded_size << endl;
	cout << "Encoded string size: " << encoded_size << endl;
	cout << "Compression coefficient: " << coef << endl;
}
