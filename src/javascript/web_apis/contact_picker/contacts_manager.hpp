#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_HPP

#include "dom_object.hpp"
namespace contact_picker {class contacts_manager;}

#include "ext/promise.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(contact_picker)


class contact_picker::contacts_manager
{
public constructors:
    DOM_CTORS(contacts_manager);
    contacts_manager() = default;

public js_methods:
    auto get_properties() -> ext::promise<ext::vector<detail::contact_property_t>>;
    auto select(ext::vector<detail::contact_property_t*>& properties, detail::contacts_select_options_t&& options = {}) -> ext::promise<ext::vector<detail::contact_info_t>>;

private cpp_properties:
    std::unique_ptr<detail::contact_source_t> m_contact_source;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_HPP
