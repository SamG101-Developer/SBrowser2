#ifndef SBROWSER2_ABORT_CONTROLLER_HPP
#define SBROWSER2_ABORT_CONTROLLER_HPP

#include "dom_object.hpp"
namespace dom::abort {class abort_controller;}

#include "dom/abort/abort_controller_private.hpp"
namespace dom::abort {class abort_signal;}


class dom::abort::abort_controller
        : public virtual dom_object
{
public constructors:
    abort_controller();

public js_methods:
    auto abort(const ext::any& reason) const -> void;

public cpp_members:
    MAKE_PIMPL(abort_controller);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_GETTER(signal, abort_signal*) {return d_ptr->signal.get();}
};


#endif //SBROWSER2_ABORT_CONTROLLER_HPP
