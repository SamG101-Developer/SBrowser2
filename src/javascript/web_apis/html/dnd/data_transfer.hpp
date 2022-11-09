#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_HPP

#include "dom_object.hpp"
namespace html::dnd {class data_transfer;}
namespace html::dnd {class data_transfer_private;}

#include INCLUDE_INNER_TYPES(html)
#include "ext/span.hpp"
namespace dom::nodes {class element;}
namespace html::dnd {class data_transfer_item;}


class html::dnd::data_transfer
        : public virtual dom_object
{
public friends:
    friend class data_transfer_item;

public constructors:
    data_transfer();
    MAKE_PIMPL(data_transfer);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto set_drag_image(dom::nodes::element* element, ext::number<long> x, ext::number<long> y) -> void;

private js_properties:
    DEFINE_GETTER(drop_effect, detail::drop_effect_t);
    DEFINE_GETTER(effect_allowed, detail::effect_allowed_t);
    DEFINE_GETTER(items, ext::vector_span<data_transfer_item*>); // TODO : check type (...*)

    DEFINE_SETTER(drop_effect, detail::drop_effect_t);
    DEFINE_SETTER(effect_allowed, detail::effect_allowed_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_HPP
