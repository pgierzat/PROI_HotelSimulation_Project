#include <vector>
#include <ranges>
#include <memory>

template<typename T>
std::vector<const T*> vec_to_pvec(const std::vector<T>& vec)
{
    std::vector<const T*> pvec{};
    std::ranges::for_each(vec, [&](const T& elem){ pvec.push_back(&elem); });
    return pvec;
}

template<typename T>
std::vector<T*> vec_to_pvec(std::vector<T>& vec)
{
    std::vector<T*> pvec{};
    std::ranges::for_each(vec, [&](const T& elem){ pvec.push_back(&elem); });
    return pvec;
}

template<typename T>
std::vector<const T*> vec_to_pvec(const std::vector<std::unique_ptr<T>>& vec)
{
    std::vector<const T*> pvec{};
    std::ranges::for_each(vec, [&](const auto& elem){ pvec.push_back(elem.get()); });
    return pvec;
}

