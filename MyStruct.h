#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>

class MyStruct
{
	public:
		std::vector<int> fields;
		std::vector<std::mutex> mtx;
		MyStruct(int m);

		int get(int i);
		void set(int i, int value);
		std::string to_string();
};

