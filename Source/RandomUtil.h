#pragma once

#include<random>

class RandomUtil
{
private:
	std::mt19937 generator;
	std::uniform_int_distribution<uint32_t> val;
public:
	RandomUtil();
	int getRandom(int a, int b);
};

