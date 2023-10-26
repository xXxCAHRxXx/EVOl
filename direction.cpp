#include "direction.hpp"

Direction::Direction() : direct(0)
{
}

Direction::~Direction()
{
}

Direction&
Direction::operator++()
{
    ++direct;
    if (direct > 5)
    {
        direct = 0;
    }
    return *this;
}

Direction
Direction::operator++(int)
{
    Direction temp = *this;
    ++*this;
    return temp;
}

Direction&
Direction::operator--()
{
    --direct;
    if (direct < 0)
    {
        direct = 5;
    }
    return *this;
}

Direction
Direction::operator--(int)
{
    Direction temp = *this;
    --*this;
    return temp;
}

const int
Direction::getX() const
{
    switch (direct)
    {
        case 0:
            return -1;
            break;
        case 1:
            return -1;
            break;
        case 2:
            return 0;
            break;
        case 3:
            return 1;
            break;
        case 4:
            return 1;
            break;
        case 5:
            return 0;
            break;
    }
}

const int
Direction::getY() const
{
    switch (direct)
    {
        case 0:
            return -1;
            break;
        case 1:
            return 0;
            break;
        case 2:
            return 1;
            break;
        case 3:
            return 0;
            break;
        case 4:
            return -1;
            break;
        case 5:
            return -1;
            break;
    }
}
