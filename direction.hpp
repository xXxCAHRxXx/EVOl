#ifndef DIRECTION_HPP
#define DIRECTION_HPP

/*
    UpLeft    = 0
    UpRight   = 1
    Right     = 2
    DownRight = 3
    DownLeft  = 4
    Left      = 5
*/

class Direction
{
public:
    Direction();
    ~Direction();

    Direction& operator++();
    Direction operator++(int);

    Direction& operator--();
    Direction operator--(int);

    const int getX() const;
    const int getY() const;

private:
    int direct;
};

#endif // !DIRECTION_HPP
