#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_HPP

#include "dom_object.hpp"
namespace contact_picker {class contacts_manager;}

#include "ext/promise.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(contact_picker)


class contact_picker::contacts_manager
        : public virtual dom_object
{
public constructors:
    contacts_manager();

public js_methods:
    auto get_properties() -> ext::promise<ext::vector<detail::contact_property_t>>;
    auto select(ext::vector<detail::contact_property_t*>& properties, detail::contacts_select_options_t&& options = {}) -> ext::promise<ext::vector<detail::contact_info_t>>;

private cpp_members:
    MAKE_PIMPL(contacts_manager);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_HPP
