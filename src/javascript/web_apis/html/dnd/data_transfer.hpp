#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_HPP

#include "dom_object.hpp"
namespace html::dnd {class data_transfer;}

namespace dom::nodes {class element;}
namespace html::dnd {class data_transfer_item;}


class html::dnd::data_transfer
        : public virtual dom_object
{
public constructors:
    data_transfer();

public js_methods:
    auto set_drag_image(dom::nodes::element* element, const ext::number<long>& x, const ext::number<long>& y) -> void;

public js_properties:
    ext::property<ext::string> drop_effect;
    ext::property<ext::string> effect_allowed;
    ext::property<std::unique_ptr<ext::vector<data_transfer*>>> items;

private cpp_properties:
    ranges::any_view<ext::string> types_array;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_HPP
