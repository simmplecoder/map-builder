#ifndef RANDOM_COLOR_GENERATOR_H
#define RANDOM_COLOR_GENERATOR_H

#include <QColor>
#include <random>
#include <utility>

class random_color_generator
{
    std::mt19937 engine;
    std::uniform_int_distribution<char> dist;
public:
    QColor operator()();

    std::pair<std::mt19937, std::uniform_int_distribution<char>> getDetails();
};

#endif // RANDOM_COLOR_GENERATOR_H
