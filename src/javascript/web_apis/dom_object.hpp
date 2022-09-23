#ifndef SBROWSER2_DOM_OBJECT_HPP
#define SBROWSER2_DOM_OBJECT_HPP

#include "ext/any.hpp"
#include "ext/custom_operator.hpp"
#include "ext/functional.hpp"
#include "ext/keywords.hpp"
#include "ext/pimpl.hpp"
#include "ext/property.hpp"
#include "ext/slot.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"

#include <memory>
#include <v8-isolate.h>
#include <v8pp/class.hpp>

#include "dom_object_private.hpp"


#define DOM_CTORS(type)  \
    type();              \
    DISALLOW_COPY(type); \
    ALLOW_MOVE(type)


#define MAKE_V8_AVAILABLE \
public:                   \
    SELF_MACRO_DEFINE_SELF(self_t, private);\
    static auto to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>


#define MAKE_STRINGIFIER \
private:                  \
    operator ext::string() const


class dom_object
{
public constructors:
    dom_object();
    virtual ~dom_object() = default;
    MAKE_PIMPL(dom_object);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER {return "";}

private:
    std::unique_ptr<dom_object_private> d_ptr;
};


#endif //SBROWSER2_DOM_OBJECT_HPP
