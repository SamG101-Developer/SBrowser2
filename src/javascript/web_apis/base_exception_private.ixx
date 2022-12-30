export module apis.base_exception:p;
import apis.dom_object;
import ext.core;


export template <ext::type_is_enum T>
struct base_exception_private
        : virtual dom_object_private
{
    ext::u8string message;
    T code;
};
