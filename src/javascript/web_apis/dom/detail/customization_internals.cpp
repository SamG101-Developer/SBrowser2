#include "customization_internals.hpp"

#include "javascript/interop/annotations.hpp"
#include "javascript/ecma/7_absract_operations/7_2_testing_and_comparison_operations.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/detail/shadow_internals.hpp"

#include "dom/nodes/attr.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/element.hpp"
#include "dom/other/dom_implementation.hpp"

#include "html/elements/html_unknown_element.hpp"

#include <range/v3/algorithm/contains.hpp>


template <typename T>
auto dom::detail::customization_internals::element_interface(
        ext::string_view local_name,
        ext::string_view namespace_)
        -> std::unique_ptr<T>
{
    using namespace namespace_internals;

    if (namespace_ == HTML)
    {
        string_switch(local_name.data())
        {
            string_default:
                return is_valid_custom_element_name(local_name)
                        ? std::make_unique<html::elements::html_element>()
                        : std::make_unique<html::elements::html_unknown_element>();
        }
    }

    return std::make_unique<nodes::element>();
}


auto dom::detail::customization_internals::create_an_element(
        nodes::document* document,
        ext::string_view local_name,
        ext::string_view namespace_,
        ext::string_view prefix,
        ext::string_view is,
        ext::boolean_view synchronous_custom_elements_flag)
        -> nodes::element*
{
    // create a result pointer to store the created element, and a definition struct holding private information about
    // the custom element (like an PIMPL without the pointer - uses a lookup table / dictionary instead)
    nodes::element* result = nullptr;
    auto* definition = lookup_custom_element_definition(document, namespace_, local_name, is);

    // case for when there is a valid definition for the parameters, and the definition's name is the same as the
    // definition's local name (JavaScript: ... extends ...)
    if (definition && definition->name == definition->local_name)
    {
        // try to upgrade the element to the correct interface stored in the definition (ie a HTMLElement is created in
        // place of the Element class - pointer casting allows this) synchronously
        if (synchronous_custom_elements_flag)
        {
            JS_EXCEPTION_HANDLER;
            result = element_interface(local_name, namespace_).get();
            result->namespace_uri = detail::namespace_internals::HTML;
            result->prefix = prefix;
            result->local_name = local_name;
            result->owner_document = document;
            result->m_custom_element_state = UNDEFINED;
            result->m_custom_element_definition = nullptr;
            result->m_is = is;

            upgrade_element(definition, result);

            // if there is an exception in the upgrading, then report it to the console, and set the custom element
            // state to the 'FAILED' state
            if (JS_EXCEPTION_HAS_THROWN)
            {
                console::reporting::report_exception(JS_EXCEPTION_MESSAGE);
                result->m_custom_element_state = FAILED;
            }
        }

            // the upgrade reaction isn't do be executed synchronously, so enqueue the information required to cause the
            // upgrade reaction asynchronously
        else
        {
            result = element_interface(local_name, namespace_).get();
            result->namespace_uri = detail::namespace_internals::HTML;
            result->prefix = prefix;
            result->local_name = local_name;
            result->owner_document = document;
            result->m_custom_element_state = UNDEFINED;
            result->m_custom_element_definition = nullptr;
            result->m_is = is;

            enqueue_custom_element_upgrade_reaction(result, definition);
        }
    }

        // case for when there is a valid definition for the parameters, but the definition's name is not the same as the
        // definition's local name
    else if (definition)
    {
        // try to upgrade the element to the correct interface stored in the definition  synchronously
        if (synchronous_custom_elements_flag)
        {
            // invoke the constructor of the definition to generate the element (catching any javascript exception
            // thrown in the process
            JS_EXCEPTION_HANDLER;
            result = definition->constructor();

            // there must be a custom element state and a custom element definition present, as well as a html namespace
            // set to the element
            assert(result->m_custom_element_state != NONE && result->m_custom_element_definition);
            assert(result->namespace_uri() == namespace_internals::HTML);

            exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                    [&result] {return !result->attributes->empty();},
                    "A custom element must have an empty 'attributes' list while being created",
                    {"The 'attribute' list might have been mutated from another thread / asynchronously"},
                    {"Check for any threads that are accessing objects' attributes"},
                    P("Element being created", result));

            exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                    [&result] {return !result->child_nodes->empty();},
                    "A custom element must have an empty 'child_nodes' list while being created",
                    {"The 'child_nodes' list might have been mutated from another thread / asynchronously"},
                    {"Check for any threads that are accessing objects; child nodes"},
                    P("Element being created", result));

            exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                    [&result] {return result->parent_node();},
                    "A custom element must have null 'parent_node' while being created",
                    {
                            "The 'parent_node' might have been initialized from another thread / asynchronously",
                            "General asynchronous tree manipulation"
                    },
                    {"Check for any threads modifying the DOM tree"},
                    P("Element being created", result), P("Parent node", result->parent_node()));

            exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                    [&result] {return result->owner_document();},
                    "A custom element must have an 'owner_document' initialized to the 'document' parameter",
                    {""}, {""},
                    P("Element's owner_document", result->owner_document()), P("Document parameter", document));

            exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                    [result, local_name] {return result->local_name() != local_name;},
                    "A custom element's 'local_name' must match the 'local_name' parameter",
                    {""}, {""},
                    P("Element's local_name", result->local_name()), P("Local name parameter", local_name));

            // set the result's 'prefix', and empty the 'is' attribute
            result->prefix = prefix;
            result->m_is = "";

            // if a javascript exception has been thrown, report the exception, and create a HTMLUnknownElement as the
            // result, with a FAILED 'custom_element_state'
            if (JS_EXCEPTION_HAS_THROWN)
            {
                console::reporting::report_exception(JS_EXCEPTION_MESSAGE);

                result = std::make_unique<html::elements::html_unknown_element>().get();
                result->namespace_uri = namespace_internals::HTML;
                result->prefix = prefix;
                result->local_name = local_name;
                result->owner_document = document;
                result->m_custom_element_definition = nullptr;
                result->m_custom_element_state = FAILED;
                result->m_is = "";
            }
        }

            // the upgrade reaction isn't do be executed synchronously, so enqueue the information required to cause the
            // upgrade reaction asynchronously
        else
        {
            result = std::make_unique<html::elements::html_element>().get();
            result->namespace_uri = namespace_internals::HTML;
            result->prefix = prefix;
            result->local_name = local_name;
            result->owner_document = document;
            result->m_custom_element_definition = nullptr;
            result->m_custom_element_state = UNDEFINED;
            result->m_is = "";

            enqueue_custom_element_upgrade_reaction(result, definition);
        }
    }

        // case for when there is no valid definition for the parameters (ie normal element like HTMLButtonElement)
    else
    {
        result = element_interface(local_name, namespace_).get();
        result->namespace_uri = namespace_;
        result->prefix = prefix;
        result->local_name = local_name;
        result->owner_document = document;
        result->m_custom_element_definition = nullptr;
        result->m_custom_element_state = UNCUSTOMIZED;
        result->m_is = "";

        // custom element state is undefined if the element is HTML and the local name is custom / there is an is value;
        // this is because there is a valid custom ame, but no definition for it
        if (namespace_ == namespace_internals::HTML && is_valid_custom_element_name(local_name) || is)
            result->m_custom_element_state = UNDEFINED;
    }
}


auto dom::detail::customization_internals::upgrade_element(
        custom_element_definition* definition,
        nodes::element* element)
        -> void
{
    // if the element is in the UNDEFINED or UNCUSTOMIZED custom element state, then return early
    auto non_upgradable_states = {UNDEFINED, UNCUSTOMIZED};
    if (ranges::contains(non_upgradable_states, element->m_custom_element_state)) return;

    // set the custom element definition, and default the custom element state to FAILED
    element->m_custom_element_definition = definition;
    element->m_custom_element_state = FAILED;

    // enqueue a callback reaction for each attribute in the element being upgraded, to call the
    // "attributeChangedCallback"
    for (nodes::attr* attribute: *element->attributes())
        enqueue_custom_element_callback_reaction(element, "attributeChangedCallback", attribute->local_name(), "", attribute->value(), attribute->namespace_uri());

    // if the element is connected, enqueue a callback reaction for the element to call the "connectedCallback" callback
    if (shadow_internals::is_connected(element))
        enqueue_custom_element_callback_reaction(element, "connectedCallback");

    // push the element onto the definition's construction stack
    definition->construction_stack.push_back(element);

    JS_EXCEPTION_HANDLER;
    exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [definition, element] {return definition->disable_shadow && element->shadow_root_node();},
            "An element being upgraded can not have a 'shadow_root' is not null, but the definition's 'disable_shadow'"
            "is true (can not have a 'shadow_root' set if definition forbids it)",
            {"Element has been attached to a shadow tree", "Element's definition has 'disable_shadow' set to true by accident"},
            {"Remove element's 'shadow_root' node", "Set element's definition's 'disable_shadow' to false"},
            P("Element being upgraded", element), P("Element's 'shadow_root'", element->shadow_root_node()));

    // the element is now PRECUSTOMIZED ie it's ready for customization now, so set the construct_result to the result
    // of invoking the constructor
    element->m_custom_element_state = PRECUSTOMIZED;
    auto* construct_result = definition->constructor();

    JS_BLOCK_ENTER // throw an error if 'construction_result' is the same object as 'element'
    auto* isolate = v8::Isolate::GetCurrent();
    if (javascript::ecma::SameValue(v8pp::to_v8(isolate, construct_result), v8pp::to_v8(isolate, element)))
        exception_internals::throw_v8_exception<V8_TYPE_ERROR>();
    JS_BLOCK_EXIT

    // pop the element off the definition's construction stack
    definition->construction_stack.pop_back();

    // if an error in JavaScript has occurred, nullify the custom element state, empty the custom element reaction
    // queue, and
    if (JS_EXCEPTION_HAS_THROWN)
    {
        element->m_custom_element_state = NONE;
        element->m_custom_element_reaction_queue = {};
        JS_EXCEPTION_RETHROW
    }

    // handle form associated elements (the form owner has to be reset if the element upgrades, and enqueue a custom
    // element reaction to call the "formAssociatedCallback" callback. If the form associated element is disabled, then
    // enqueue a custom element callback reaction to call the "formDisabledCallback" callback
    if (html::detail::form_internals::is_form_assiciated(element))
        // TODO : reset form owner
        // TODO : enqueue custom element callback reaction for "formAssociatedCallback)
        // TODO : if element is disabled:
        // TODO :   - enqueue_custom_element_callback_reaction(element, "formDisabledCallback", true);
        ;
}


auto dom::detail::customization_internals::try_to_upgrade_element(
        nodes::element* element)
        -> void
{
    // get the definition of the element, and only if it exists, enqueue a custom element upgrade reaction for the
    // element and its definition
    auto* definition = lookup_custom_element_definition(element->owner_document(), element->namespace_uri(), element->local_name(), element->m_is);
    if (definition)
        enqueue_custom_element_upgrade_reaction(element, definition);
}


auto dom::detail::customization_internals::lookup_custom_element_definition(
        nodes::document* document,
        ext::string_view namespace_,
        ext::string_view local_name,
        ext::string_view is)
        -> custom_element_definition*
{
    if (namespace_ != namespace_internals::HTML || !document->m_browsing_context)
        return nullptr;

    // TODO : get the CustomElementRegistry object in the relevant global object
    // TODO : 2 different cases, filter a matching object from the registry entries

    return nullptr;
}

