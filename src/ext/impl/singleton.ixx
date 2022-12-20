module;
#include "ext/macros/namespaces.hpp"
#include <exception>


export module ext.mixins:singleton;
import ext.core;


_EXT_BEGIN
    export template <typename T>
    class singleton;
_EXT_END


template <typename T>
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
