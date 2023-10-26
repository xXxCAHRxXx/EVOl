#include "object.hpp"

Object::Object(Type aType) : myType(aType)
{
}

Object::Type
Object::getType() const
{
    return myType;
}

void
Object::lock()
{
    mtx.lock();
}

void
Object::unlock()
{
    mtx.unlock();
}
