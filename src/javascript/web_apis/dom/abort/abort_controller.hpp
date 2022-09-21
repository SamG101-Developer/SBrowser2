#ifndef SBROWSER2_ABORT_CONTROLLER_HPP
#define SBROWSER2_ABORT_CONTROLLER_HPP

#include "dom_object.hpp"
namespace dom::abort {class abort_controller;}

namespace dom::abort {class abort_signal;}


class dom::abort::abort_controller
        : public virtual dom_object
{
public constructors:
    abort_controller();

public js_methods:
    auto abort(const ext::any& reason) const -> void;

public js_properties:
    ext::property<std::unique_ptr<abort_signal>> signal;

public cpp_members:
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_ABORT_CONTROLLER_HPP
