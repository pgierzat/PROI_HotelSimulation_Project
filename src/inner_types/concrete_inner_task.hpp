#ifndef CONCRETE_INNER_TASK
#define CONCRETE_INNER_TASK

#include "inner_task.hpp"
#include "../utilities/concepts.hpp"

template<SupportedTask T>
class ConcreteInnerTask : public T, public InnerTask
{
    public:
        ConcreteInnerTask(const T&);
};


template<SupportedTask T>
ConcreteInnerTask<T>::ConcreteInnerTask(const T& t) : Task{t}, T{t}, InnerTask{t} {}


#endif
