#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "../lab2sem4/Map.h"
#include "../lab2sem4/Huffman.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace lab2sem4tests
{
	TEST_CLASS(lab2sem4tests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string input_string = "Anybody can sympathise with the sufferings of a friend, but it requires a very fine nature to sympathise with a friend's success. Oscar Wilde";
			Map<char, int> freq;
			for (char c : input_string) freq.insert(c, freq.find(c, 0) + 1);
			auto huffman_tree = create_huffman_tree(freq);
			Map<char, string> codes;
			create_huffman_codes_map(codes, huffman_tree, "");
			string encoded_string = encode(input_string, codes);
			string decoded_string = decode(encoded_string, huffman_tree);
			Assert::IsTrue(input_string == decoded_string);
		}
		TEST_METHOD(TestMethod2)
		{
			string input_string = "An enemy can partly ruin a man, but it takes a good-natured injudicious friend to complete the thing and make it perfect. Mark Twain";
			Map<char, int> freq;
			for (char c : input_string) freq.insert(c, freq.find(c, 0) + 1);
			auto huffman_tree = create_huffman_tree(freq);
			Map<char, string> codes;
			create_huffman_codes_map(codes, huffman_tree, "");
			string encoded_string = encode(input_string, codes);
			string decoded_string = decode(encoded_string, huffman_tree);
			Assert::IsTrue(input_string == decoded_string);
		}
		TEST_METHOD(TestMethod3)
		{
			string input_string = "A friend is a second self. Aristotle";
			Map<char, int> freq;
			for (char c : input_string) freq.insert(c, freq.find(c, 0) + 1);
			auto huffman_tree = create_huffman_tree(freq);
			Map<char, string> codes;
			create_huffman_codes_map(codes, huffman_tree, "");
			string encoded_string = encode(input_string, codes);
			string decoded_string = decode(encoded_string, huffman_tree);
			Assert::IsTrue(input_string == decoded_string);
		}

	};
}
