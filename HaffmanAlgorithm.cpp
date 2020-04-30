#include "HaffmanAlgorithm.h"

HaffmanTree::HaffmanTree(std::string symbols)
{
	if (symbols.length() == 0)
		throw std::out_of_range("String is empty!");
	
	else
	{
		Map <char, int> frequencies;
		root = nullptr;
		for (size_t i = 0; i < symbols.length(); i++) //counts frequency of each symbol and stores them in a map
		{
			if (!frequencies.contains(symbols[i]))
				frequencies.insert(symbols[i], 1); 

			else 
				frequencies.update(symbols[i], frequencies.find(symbols[i]) + 1);
		}
		BuildTree(frequencies.get_size(),  frequencies);
	}
}

void HaffmanTree::BuildTree(int lenght, Map<char, int> frequencies)
{
	Node* HaffmanLeaf = new Node[lenght];
	Node * SummLeaf = new Node[lenght-1]; //array, where'd be stored sums of frequencies
	
	
	Iterator<char, int> *iter = frequencies.create_iter();
	//writing a symbol-frequency pair to an array of structures
	for (int i = 0; i<lenght; i++) 
	{
		if (iter->has_next())
		{
			HaffmanLeaf[i].symbol = iter->next_key();
			HaffmanLeaf[i].amount = iter->next_data();
			
		}
	}
	delete iter;
	int countLeaf = 0, countSum = 0;
	freqQuickSort(HaffmanLeaf, lenght); //sorting an array from smallest to largest amount 
	//puts in all summ leaves the biggest amount+1
	for (int i = 0; i < lenght - 1; i++)
	{
		SummLeaf[i].amount = HaffmanLeaf[lenght].amount+1;
	}
	for (int i = 0; i < lenght-1; i++)
	{
		
		//selesting 2 elements with the lowest frequency

		//there're 3 possible cases:
		//case 1: both smallest elements are in 1 array(HaffmanLeaf)
		
		if (HaffmanLeaf[countLeaf].amount + HaffmanLeaf[countLeaf + 1].amount <= HaffmanLeaf[countLeaf].amount + SummLeaf[countSum].amount
			&& HaffmanLeaf[countLeaf].amount + HaffmanLeaf[countLeaf + 1].amount <= SummLeaf[countSum].amount + SummLeaf[countSum + 1].amount)
		{
			SummLeaf[i].amount = HaffmanLeaf[countLeaf].amount + HaffmanLeaf[countLeaf + 1].amount;
			SummLeaf[i].left = &HaffmanLeaf[countLeaf];
			SummLeaf[i].right = &HaffmanLeaf[countLeaf + 1];
			countLeaf += 2;
		}
		//case 2: one of the smallest elements is in the 1 array(HaffmanLeaf), the other is in 2 array (SummLeaf)
		else if(HaffmanLeaf[countLeaf].amount + SummLeaf[countSum].amount <= HaffmanLeaf[countLeaf].amount + HaffmanLeaf[countLeaf + 1].amount
			&& HaffmanLeaf[countLeaf].amount + SummLeaf[countSum].amount <= SummLeaf[countSum].amount + SummLeaf[countSum + 1].amount)
		{
			SummLeaf[i].amount = HaffmanLeaf[countLeaf].amount + SummLeaf[countSum].amount;
			SummLeaf[i].right = &HaffmanLeaf[countLeaf];
			SummLeaf[i].left = &SummLeaf[countSum];
			countLeaf++;
			countSum++;
		}
		//case 3: both of the smallest elements're in the 2 array (SummLeaf)
		else if (SummLeaf[countSum].amount + SummLeaf[countSum + 1].amount <= HaffmanLeaf[countLeaf].amount + HaffmanLeaf[countLeaf + 1].amount 
			&& SummLeaf[countSum].amount + SummLeaf[countSum + 1].amount <= HaffmanLeaf[countLeaf].amount + SummLeaf[countSum].amount)
		{
			
			SummLeaf[i].amount = SummLeaf[countSum].amount + SummLeaf[countSum + 1].amount;
			SummLeaf[i].left = &SummLeaf[countSum];
			SummLeaf[i].right = &SummLeaf[countSum + 1];
			countSum += 2;
		}
	}
	root = &SummLeaf[lenght-2]; //putting a root-pointer to the last SummLeaf


	std::string code;
	Create(code_table, decode_table, root, code);
	std::cout<<std::endl;
	//prints codes and freqs table
	PrintFreq(HaffmanLeaf, lenght);
}

void HaffmanTree::freqQuickSort(Node* array, size_t lenght) //common QuickSort algorithm
{
	int left = 0, right = lenght - 1; //left and right borders of array
	size_t middle = array[lenght / 2].amount;

	while (left <= right)
	{
		while (array[left].amount < middle)
			left++;
		while (array[right].amount > middle)
			right--;

		if (left <= right)
		{
			if (array[left].amount != array[right].amount)
				std::swap(array[left], array[right]);
			left++;
			right--;
		}

	} 
	
	if (right >0)
		freqQuickSort(array, right + 1);
	if (left < lenght)
		freqQuickSort(&array[left], lenght - left);
}

void HaffmanTree::Create(Map<char, std::string>& code_table, Map<std::string, char>& decode_table, Node* current, std::string& code_str)
{
	if (current != nullptr)
	{
		if (current->left == nullptr && current->right == nullptr) //current is a leaf
		{
			code_table.insert(current->symbol, code_str);
			decode_table.insert(code_str, current->symbol);
		}
		//going left - adding 1 to the code, going right - adding 0 to the code

		code_str.push_back('0');
		Create(code_table, decode_table, current->left, code_str);
		code_str.push_back('1');
		Create(code_table, decode_table, current->right, code_str);
	}
	if (!code_str.empty())
		code_str.pop_back();
	
}


void HaffmanTree::PrintFreq(Node* start, int lenght)
{
	for (int i = 0; i < lenght; i++)
	{
		std::cout << "Symbol: " << start[i].symbol << " Frequency: " << start[i].amount<<" ";
		std::cout<< " Code: " << code_table.find(start[i].symbol) << std::endl;
	}
}

 std::string HaffmanTree::getCode(std::string &original)
{
	 if (code_table.get_size()== 0)
		 throw std::logic_error("Code table is empty");
	 std::string code;
	 //separating each code with space
	for (auto symbol :original)
	{
		code += code_table.find(symbol);
		code += " ";
	}
	code.pop_back();

	return code;
}
 float HaffmanTree::Compression(std::string original, std::string encoded)
 {
	 float Percentage = float(encoded.length()) / float(original.length() * 8) * 100;
	 return round(Percentage * 10) / 10;
 }

 std::string HaffmanTree::getText(const std::string &encoded_str, HaffmanTree &tree)
{
	if (tree.decode_table.get_size() == 0)
		throw std::logic_error("Decode table is empty");
	std::string  code, decode;

	
	//filling code string with each code
	for (auto number : encoded_str)
	{
		if (number == '1' || number == '0')
			code += number;
		else if (number == ' ')
		{
			if (!tree.decode_table.contains(code))
				throw std::invalid_argument("Haffman tree is wrong!");
			decode += decode_table.find(code); //searches each code in the Haffman Tree and returns its symbol
			code.clear();
		}
		
		else 
			throw std::invalid_argument("Wrong format of the encoded text!");
	}

	if (!tree.decode_table.contains(code))
		throw std::invalid_argument("Haffman tree is wrong!");
	decode += decode_table.find(code);
	code.clear();
	
	return decode;
}