#include "RandomUtil.h"

#include<ctime>

RandomUtil::RandomUtil()
{
    generator.seed(std::time(0));
}

int RandomUtil::getRandom(int a, int b)
{   
    val = std::uniform_int_distribution<uint32_t>(a, b);
    return val(generator);
}
