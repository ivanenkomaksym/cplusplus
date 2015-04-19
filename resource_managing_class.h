#ifndef RESOURCE_MANAGING_CLASS_H
#define RESOURCE_MANAGING_CLASS_H

#include<string>
#include<vector>

class Person
{
public:
    Person(std::string name)
        : m_name(new std::string(name))
    {}

    //Person(const Person &) = delete;
    Person(Person &&) = default;
    ~Person() {}

    void printName() { std::cout << *m_name << std::endl; }

private:
    //std::string *m_name;
    std::unique_ptr<std::string> m_name;
};

void resource_managing_class()
{
    std::vector<Person> persons;
    // persons.push_back(Person("George"));
    // persons.front().printName(); // crash
    persons.emplace_back("George"); // construct the object in place
    persons.front().printName();
    Person p("Lucy");
    persons.push_back(std::move(p));
    persons.back().printName();
}

#endif // RESOURCE_MANAGING_CLASS_H
