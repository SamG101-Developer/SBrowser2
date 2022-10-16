#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_ITEM_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_ITEM_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/memory.hpp"
namespace html::dnd {class data_transfer;}


DEFINE_PRIVATE_CLASS(html::dnd, data_transfer_item) : dom_object_private
{
    std::observer_ptr<data_transfer> data_transfer;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_ITEM_PRIVATE_HPP
