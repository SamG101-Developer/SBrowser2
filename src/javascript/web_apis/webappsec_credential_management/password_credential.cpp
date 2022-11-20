#include "password_credential.hpp"
#include "password_credential_private.hpp"

#include <ext/ranges.hpp>

#include "html/_concepts.hpp"
#include "html/elements/html_form_element.hpp"
#include "html/elements/html_form_element_private.hpp"

#include "dom/detail/tree_internals.hpp"
#include "webappsec_credential_management/_typedefs.hpp"
#include "xhr/form_data.hpp"

#include "ext/pimpl.hpp"


webappsec::credential_management::password_credential::password_credential(
        const html::elements::html_form_element* form)
{
    auto e = js::env::env::current();

    auto data = detail::password_credential_data_t{};
    auto form_data = xhr::form_data{form};
    auto new_password_observed = ext::boolean::FALSE_();
    data.try_emplace(u"origin", e.cpp.settings()->origin.get());

    auto elements = dom::detail::descendants(dom::detail::root(reinterpret_cast<const dom::nodes::node*>(form))) // TODO : remove (...node*)
            | ranges::views::cast<html::elements::html_element*>
            | ranges::views::filter([]<typename T>(T) {return html::concepts::submittable_elements<T>;});
            // TODO | ranges::views::filter([form]<html::concepts::submittable_elements T>(T* element) {return element->d_func()->form_owner == form;});

    for (decltype(auto) field: elements)
    {
        auto autocomplete = ext::string{};
        JS_BLOCK_ENTER
            auto v8_field = v8pp::to_v8(e.js.agent(), field);
            auto has_autocomplete_attribute = v8_field->Has(e.js.realm(), v8::String::NewFromUtf8Literal(e.js.agent(), "autocomplete")).FromJust();
            auto name_attribute = v8_field->Get(e.js.realm(), v8::String::NewFromUtf8Literal(e.js.agent(), "name")).ToLocalChecked();
            auto name = v8pp::from_v8<ext::string>(e.js.agent(), name_attribute);

            continue_if (!has_autocomplete_attribute);
            continue_if (!form_data.has(std::move(name)));
            auto autocomplete_attribute = v8_field->Get(e.js.realm(), v8::String::NewFromUtf8Literal(e.js.agent(), "autocomplete")).ToLocalChecked();
            autocomplete = v8pp::from_v8<ext::string>(e.js.agent(), autocomplete_attribute);
        JS_BLOCK_EXIT

        // TODO
    }
}
