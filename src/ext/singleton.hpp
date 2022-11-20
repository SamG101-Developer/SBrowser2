#ifndef SBROWSER2_SRC_EXT_SINGLETON_HPP
#define SBROWSER2_SRC_EXT_SINGLETON_HPP

#include "ext/boolean.hpp"
#include <exception>


_EXT_BEGIN
    class singleton;
_EXT_END


class ext::singleton
{
public:
    singleton()
    {
        if (instance_exists) throw std::exception{"Can only create one instance of a class inheriting the Singleton class"};
        instance_exists = true;
    }

private:
    static inline ext::boolean instance_exists = false;
};


#endif //SBROWSER2_SRC_EXT_SINGLETON_HPP
