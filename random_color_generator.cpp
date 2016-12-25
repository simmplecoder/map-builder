#include "random_color_generator.h"

QColor random_color_generator::operator()()
{
    return QColor(dist(engine), dist(engine), dist(engine));
}

std::pair<std::mt19937, std::uniform_int_distribution<char>>
random_color_generator::getDetails()
{
    return {engine, dist};
}
