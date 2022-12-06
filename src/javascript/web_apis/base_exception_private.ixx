export module apis._.base_exception_private;
import apis._.dom_object_private;
import ext.concepts;
import ext.string;


export template <ext::type_is_enum T>
struct base_exception_private
        : virtual dom_object_private
{
    ext::u8string message;
    T code;
};
