#ifndef SBROWSER2_ABORT_CONTROLLER_HPP
#define SBROWSER2_ABORT_CONTROLLER_HPP

#include "dom_object.hpp"
namespace dom::abort {class abort_controller;}
namespace dom::abort {class abort_controller_private;}

namespace dom::abort {class abort_signal;}


class dom::abort::abort_controller
        : public virtual dom_object
{
public constructors:
    abort_controller();
    MAKE_PIMPL(abort_controller);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto abort(const ext::any& reason) const -> void;

private js_properties:
    DEFINE_GETTER(signal, abort_signal*);
};


#endif //SBROWSER2_ABORT_CONTROLLER_HPP
