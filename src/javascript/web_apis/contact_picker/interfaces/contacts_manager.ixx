module;
#include "ext/macros.hpp"


export module apis.contact_picker.contacts_manager;
import apis.dom_object;

IMPORT_ALL_TYPES(contact_picker);


DEFINE_PUBLIC_CLASS(contact_picker, contacts_manager) final
        : public virtual dom_object
{
public typedefs:
    using contact_info_t = ext::map<ext::string, ext::any>;
    using contacts_select_options_t = ext::map<ext::string, ext::any>;

public constructors:
    contacts_manager();
    MAKE_PIMPL(contacts_manager);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_methods:
    auto get_properties() -> ext::promise<ext::vector<detail::contact_property_t>>;
    auto select(ext::vector_span<detail::contact_property_t*> properties, contacts_select_options_t&& options = {}) -> ext::promise<ext::vector<contact_info_t>>;
};
