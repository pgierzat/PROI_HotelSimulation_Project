#ifndef INNER_TASK_HPP
#define INNER_TASK_HPP

#include "../tasks/task.hpp"

class InnerTask : public Task
{
    public:
        InnerTask(const Task&);
        WOSOw& get_wosow();
        WMOSOw& get_wmosow();
        WOSOr& get_wosor();
        WOSOg& get_wosog();
        const WOSOw& get_wosow() const noexcept;
        const WMOSOw& get_wmosow() const noexcept;
        const WOSOr& get_wosor() const noexcept;
        const WOSOg& get_wosog() const noexcept;
    private:
        using WOSOw = WeakOwnSystemObserver<Worker>;
        using WMOSOw = WeakMultipleOwnSystemObserver<Worker>;
        using WOSOr = WeakOwnSystemObserver<Room>;
        using WOSOg = WeakOwnSystemObserver<Guest>;
};


#endif
