#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <mutex>

class Object
{
public:
    enum class Type
    {
        Wall,
        Bot,
        Food,
        Poison,
        Emptiness
    };

    Object(Type aType);
    Type getType() const;
    void lock();
    void unlock();

private:
    Type myType;
    std::mutex mtx;
};

#endif // !OBJECT_HPP
