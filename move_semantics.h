#ifndef MOVE_SEMANTICS_H
#define MOVE_SEMANTICS_H

#include <memory>

class HugeVector
{
public:
    explicit HugeVector(int size, double value)
    {
        this->size = size;
        this->array = new double[size];
        for (int i = 0; i < size; i++)
            this->array[i] = value;
    }

    ~HugeVector() { delete array; }

    HugeVector(const HugeVector &rhs)   // copy ctor
    {
        size = rhs.size;
        array = new double[size];
        for (int i = 0; i < size; i++)
            array[i] = rhs.array[i];
    }

    HugeVector(HugeVector &&rhs)        // move ctor
    {
        size = rhs.size;
        array = rhs.array;
        rhs.array = nullptr;
    }

    HugeVector &operator = (const HugeVector &rhs)     // assignment operator
    {
        size = rhs.size;
        delete array;
        array = new double [size];
        for (int i = 0; i < size; i++)
            array[i] = rhs.array[i];

        return *this;
    }

    HugeVector &operator = (HugeVector &&rhs)     // move assignment operator
    {
        size = rhs.size;
        delete array;
        array = rhs.array;
        rhs.array = nullptr;

        return *this;
    }

private:
    int size;
    double *array;
};

void foo_by_ref(HugeVector &v)
{
    return;
}

void foo_by_value(HugeVector v)
{
    return;
}

void foo(HugeVector &v)
{
    return;
}

void foo(HugeVector &&v)
{
    return;
}

HugeVector getVector(int size, int value)
{
    return HugeVector(size, value);
}

// --- Perfect forwarding ---
template <typename T>
void relay(T &&arg)     // universal reference
{
    foo(std::forward<T>(arg));
}

void move_semantics()
{
    auto reusable = getVector(5000, 1.0);

    foo_by_ref(reusable);               // call no ctor
    foo_by_value(reusable);             // call copy ctor
    foo_by_value(std::move(reusable));  // call move ctor

    relay(getVector(5000, 1.0));    // T = int&& => T&& = int&& && = int&&; call foo(T&&)
    relay(reusable);                // T = int&  => T&& = int&  && = int&;  call foo(T&)
}

#endif // MOVE_SEMANTICS_H
