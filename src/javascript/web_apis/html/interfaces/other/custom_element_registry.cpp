#include "custom_element_registry.hpp"
#include "custom_element_registry_private.hpp"





#include "javascript/interop/manual_primitive_conversions/convert_string.hpp"













auto html::other::custom_element_registry::define(
        ext::string_view name,
        detail::custom_element_constructor_t&& constructor,
        detail::element_definition_options_t&& options)
        -> void
{
    ACCESS_PIMPL(custom_element_registry);
    auto e = js::env::env::relevant(this);
    using enum v8_primitive_error_t;
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&e, &constructor] {return !v8pp::to_v8(e.js.agent(), constructor)->IsConstructor();},
            u8"Must be a valid constructor");

    dom::detail::throw_v8_exception<SYNTAX_ERR>(
            [name] {return !dom::detail::is_valid_custom_element_name(name);},
            u8"Must be a valid custom element name");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d, name] {return ranges::contains(d->custom_element_definitions | ranges::views::transform_to_attr(&dom::detail::custom_element_definition_t::name, ext::deref), name);},
            u8"Name already exists");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d, constructor] {return ranges::contains(d->custom_element_definitions | ranges::views::transform_to_attr(&dom::detail::custom_element_definition_t::constructor, ext::deref), constructor);},
            u8"Constructor already exists");

    decltype(auto) local_name = name;
    decltype(auto) extends = options[u"extends"].to<ext::string>();
    if (!extends.empty())
    {
        dom::detail::throw_v8_exception<SYNTAX_ERR>(
                [name] {return dom::detail::is_valid_custom_element_name(name);},
                u8"Cannot extend from a valid custom element name");

        // TODO : element_interface() check
        local_name = std::move(extends);
    }

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->element_definition_is_running;},
            u8"Cannot define a name/constructor whilst another name/constructor is being defined");

    d->element_definition_is_running = true;
    auto form_associated = ext::boolean::FALSE_();
    auto disable_internals = ext::boolean::FALSE_();
    auto disable_shadow = ext::boolean::FALSE_();
    auto observed_attributes = ext::vector<ext::string>();

    JS_EXCEPTION_HANDLER;
    using namespace ext::literals;
    decltype(auto) v8_constructor = v8pp::to_v8(e.js.agent(), constructor);
    decltype(auto) v8_prototype = v8_constructor->GetPrototype();

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [v8_prototype] {return !v8_prototype->IsObject();},
            u8"Must be a valid constructor");

    auto lifecycle_callbacks = ext::map<ext::string, dom::detail::lifecycle_callback_t>{};

    for (auto callback_name: {u"connectedCallback", u"disconnectedCallback", u"adoptedCallback", u"attributeChangedCallback"})
    {
        auto callback_value = v8_prototype.As<v8::Object>()->Get(e.js.realm(), v8pp::to_v8(e.js.agent(), callback_name)).ToLocalChecked();
        auto callback = v8pp::from_v8<dom::detail::lifecycle_callback_t>(e.js.agent(), callback_value);
        lifecycle_callbacks.try_emplace(callback_name, std::move(callback));
        JS_EXCEPTION_RETHROW_IF_HAS_THROWN;
    }

    if (!lifecycle_callbacks[u"attributeChangedCallback"].empty())
    {
        auto observed_attributes_iterable = v8_constructor->Get(e.js.realm(), v8pp::to_v8(e.js.agent(), u"observedAttributes"_s16)).ToLocalChecked();
        observed_attributes = v8pp::from_v8<ext::vector<ext::string>>(e.js.agent(), observed_attributes_iterable);
        JS_EXCEPTION_RETHROW_IF_HAS_THROWN;
    }

    auto disabled_features_iterable = v8_constructor->Get(e.js.realm(), v8pp::to_v8(e.js.agent(), u"disabledFeatures"_s16)).ToLocalChecked();
    auto disabled_features = v8pp::from_v8<ext::vector<ext::string>>(e.js.agent(), disabled_features_iterable);
    JS_EXCEPTION_RETHROW_IF_HAS_THROWN;

    disable_internals = ranges::contains(disabled_features, u"internals");
    disable_shadow = ranges::contains(disabled_features, u"shadow");
    JS_EXCEPTION_RETHROW_IF_HAS_THROWN;

    auto form_associated_value = v8_constructor->Get(e.js.realm(), v8pp::to_v8(e.js.agent(), u"formAssociated"_s16)).ToLocalChecked();
    form_associated = v8pp::from_v8<ext::boolean>(e.js.agent(), form_associated_value);
    JS_EXCEPTION_RETHROW_IF_HAS_THROWN;

    for (auto callback_name: {u"formAssociatedCallback", u"formResetCallback", u"formDisabledCallback", u"formStateRestoreCallback"})
    {
        auto callback_value = v8_prototype.As<v8::Object>()->Get(e.js.realm(), v8pp::to_v8(e.js.agent(), callback_name)).ToLocalChecked();
        auto callback = v8pp::from_v8<dom::detail::lifecycle_callback_t>(e.js.agent(), callback_value);
        lifecycle_callbacks.try_emplace(callback_name, std::move(callback));
        JS_EXCEPTION_RETHROW_IF_HAS_THROWN;
    }

    // TODO : exception.Finally()
    d->element_definition_is_running = false;
    JS_EXCEPTION_RETHROW_IF_HAS_THROWN;

    decltype(auto) definition = std::make_unique<dom::detail::custom_element_definition_t>(
            name, local_name,
            std::move(constructor), std::move(observed_attributes), std::move(lifecycle_callbacks),
            form_associated, disabled_features, disable_shadow);

    d->custom_element_definitions.emplace(definition);

    decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document;
    dom::detail::shadow_including_descendants(document)
            | ranges::views::cast<dom::nodes::element*>
            | ranges::views::filter_eq(&dom::nodes::element_private::namespace_, dom::detail::HTML, ext::get_pimpl)
            | ranges::views::filter_eq(&dom::nodes::element_private::local_name, local_name, ext::get_pimpl)
            | ranges::views::filter([extends](dom::nodes::element* child) {return extends.empty() || child->d_func()->is == extends;})
            | ranges::views::for_each(BIND_BACK(&dom::detail::enqueue_custom_element_upgrade_reaction, definition));

    if (d->when_defined_promise_map.contains(name))
    {
        d->when_defined_promise_map[name].resolve(std::move(constructor));
        d->when_defined_promise_map |= ranges::actions::remove(name);
    }
}


auto html::other::custom_element_registry::get(
        ext::string_view name)
        -> ext::optional<detail::custom_element_constructor_t>
{
    ACCESS_PIMPL(const custom_element_registry);
    return d->when_defined_promise_map.contains(name)
            ? d->when_defined_promise_map[name]
            : ext::nullopt;
}


auto html::other::custom_element_registry::when_defined(
        ext::string_view name)
        -> ext::promise<detail::custom_element_constructor_t>
{
    ACCESS_PIMPL(custom_element_registry);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_SYNTAX_ERROR>(
            [name] {return !dom::detail::is_valid_custom_element_name(name);},
            u8"Must be a valid custom element name");

    return d->when_defined_promise_map.try_emplace(name, ext::promise<detail::custom_element_constructor_t>{}).first->second;
}


auto html::other::custom_element_registry::upgrade(dom::nodes::node* root) -> void
{
    dom::detail::shadow_including_descendants(root)
            | ranges::views::for_each(&dom::detail::try_to_upgrade_element);
}
