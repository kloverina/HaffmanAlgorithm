#include "pch.h"
#include "CppUnitTest.h"
#include <exception>
#include "../HaffmanAlgoritm/HaffmanAlgorithm.h"
#include "../HaffmanAlgoritm/HaffmanAlgorithm.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Haffman_test
{
	TEST_CLASS(Haffman_test)
	{
	public:
		
		TEST_METHOD(Exeption_empty_string)
		{
			std::string text;
			try
			{
				HaffmanTree Tree(text);
			}
			catch(std::out_of_range error)
			{
				Assert::AreEqual(error.what(), "String is empty!");
			}
		}
		TEST_METHOD(GetCode_and_GetText_test)
		{
			std::string text("Это бессмысленная надпись");
			HaffmanTree Tree(text);
			std::string code = Tree.getCode(text);

			Assert::AreEqual(text, Tree.getText(code, Tree));
		}

	};
}
