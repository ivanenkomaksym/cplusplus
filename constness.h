#ifndef CONSTNESS
#define CONSTNESS

#include <string>

class TextBlock
{
public:
    explicit TextBlock(std::string str)
        : text(str)
    {}

    const char &operator[] (std::size_t position) const // operator[] for const objects
    {
        return text[position];
    }
    char &operator[] (std::size_t position)             // operator[] for non-const objects
    {
        //return text[position];
        return
          const_cast<char&>(                         // cast away const on op[]'s return type;
            static_cast<const TextBlock&>(*this)     // add const to *this's type;
               [position]                            // call const version of op[]
          );

    }

private:
    std::string text;
};


void print(const TextBlock& ctb)    // in this function, ctb is const
{
    std::cout << ctb[0];            // calls const TextBlock::operator[]
}

void constness()
{
    TextBlock tb("Hello");
    std::cout << tb[0];     // calls non-const

    const TextBlock ctb("World");
    std::cout << ctb[0];    // calls const TextBlock::operator[]
}

#endif // CONSTNESS

