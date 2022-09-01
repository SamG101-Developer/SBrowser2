#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__CONCEPTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__CONCEPTS_HPP

#include "ext/concepts.hpp"
#include "ext/property.hpp"
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}
namespace html::elements {class html_element;}
namespace html::elements {class html_form_element;}


namespace html::concepts
{
    template <typename T>
    concept form_associated = requires
    {
        requires inherit<T, elements::html_element>;
        {T::form} -> std::same_as<ext::property<elements::html_form_element*>&>;
    };

    template <typename T>
    concept listed_elements = requires
    {
        requires form_associated<T>;
    };

    template <typename T>
    concept submittable_elements = requires
    {
        requires form_associated<T>;
    };

    template <typename T>
    concept resettable_elements = requires
    {
        requires form_associated<T>;
    };

    template <typename T>
    concept autocapitalize_inheriting_elements = requires
    {
        requires form_associated<T>;
    };

    template <typename T>
    concept labelable_elements = requires
    {
        requires form_associated<T>;
        {T::labels} -> std::same_as<ext::property<std::unique_ptr<ext::vector<dom::nodes::node*>>>&>;
    };

    template <typename T>
    concept focusable_area = requires
    {
        requires inherit<T, dom::nodes::element>; // TODO || ...

        // TODO
        //  dom::nodes::element*
        //  shapes of <area> element
        //  non-[disabled/inert] sub-widgets being rendered
        //  scrollable regions og elements being rendered and non-inert
        //  Document's viewport
        //  any part of an element
    };
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__CONCEPTS_HPP
