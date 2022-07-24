#ifndef SBROWSER2_WINDOW_HPP
#define SBROWSER2_WINDOW_HPP

#include "dom/nodes/event_target.hpp"
namespace dom::nodes {class window;}

namespace dom::nodes {class document;}


class dom::nodes::window final
        : public event_target
{
public js_properties:
    ext::property<std::unique_ptr<document>> document;
};


#endif //SBROWSER2_WINDOW_HPP
