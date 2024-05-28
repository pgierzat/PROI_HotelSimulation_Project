#ifndef CHECK_EMPTY_HPP
#define CHECK_EMPTY_HPP

#include <string>
#include <stdexcept>

template<typename T>
void check_empty(const T& x, const std::string& err_msg)
{
    if (x.empty())
        throw std::invalid_argument(err_msg);
}


#endif
