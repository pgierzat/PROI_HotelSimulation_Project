#ifndef WEAK_MULTIPLE_OWN_SYSTEM_OBSERVER_HPP
#define WEAK_MULTIPLE_OWN_SYSTEM_OBSERVER_HPP


template<typename T>
class WeakMultipleOwnSystemObserver
{
    public:
        virtual ~WeakMultipleOwnSystemObserver() {};
        virtual void notify_realloc(const T& new_obj) = 0;
        virtual void notify_erase(const std::string& erased_id) noexcept = 0;
        virtual std::vector<const std::string*> get_ids() const noexcept = 0;
        virtual bool has_id(const std::string&) const noexcept = 0;
};


#endif
