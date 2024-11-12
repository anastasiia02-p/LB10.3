#include "pch.h"
#include "CppUnitTest.h"
#include "../LB10.3/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// Ініціалізація
			const int N = 2;
			Note notes[N] = {
				{"Ivanov", "Ivan", "123456789", {12, 10, 1995}},
				{"Petrov", "Petro", "987654321", {15, 8, 1998}}
			};

			// Виклик функції
			int index = SearchByPhoneNumber(notes, N, "123456789");

			// Перевірка
			Assert::AreEqual(0, index, L"Індекс не співпадає з очікуваним для наявного запису.");
		

		}
	};
}
