#ifndef WEAK_OWN_SYSTEM_OBSERVER
#define WEAK_OWN_SYSTEM_OBSERVER

#include <string>


template<typename T>
class WeakOwnSystemObserver
{
    public:
        WeakOwnSystemObserver() = default;
        WeakOwnSystemObserver(const std::string& id);
        virtual ~WeakOwnSystemObserver() {};
        virtual void notify_realloc(const T& new_obj);
        virtual void notify_erase() noexcept;
        const std::string& get_id() const noexcept;
        void set_id(const std::string&);
    protected:
        std::string observed_id;
};


template<typename T>
WeakOwnSystemObserver<T>::WeakOwnSystemObserver(const std::string& id) : observed_id{id} {}

template<typename T>
void WeakOwnSystemObserver<T>::notify_realloc(const T& new_obj) {}

template<typename T>
void WeakOwnSystemObserver<T>::notify_erase() noexcept {}

template<typename T>
const std::string& WeakOwnSystemObserver<T>::get_id() const noexcept { return observed_id; }

template<typename T>
void WeakOwnSystemObserver<T>::set_id(const std::string& id) { observed_id = id; }


#endif
