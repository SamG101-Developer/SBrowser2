#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__CONCEPTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__CONCEPTS_HPP

#include "ext/any.hpp"
#include "ext/concepts.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}
namespace html::elements {class html_element;}
namespace html::elements {class html_form_element;}


namespace html::concepts
{
    template <typename T>
    concept form_associated = requires
    {
        requires ext::inherit<T, elements::html_element>;
        {T::get_form} -> ext::type_is<elements::html_form_element*>;
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
        {T::get_labels} -> ext::type_is<ext::vector<dom::nodes::node*>>;
    };

    template <typename T>
    concept focusable_area = requires
    {
        requires ext::inherit<T, dom::nodes::element>; // TODO || ...

        // TODO
        //  dom::nodes::element*
        //  shapes of <area> element
        //  non-[disabled/inert] sub-widgets being rendered
        //  scrollable regions og elements being rendered and non-inert
        //  Document's viewport
        //  any part of an element
    };

    template <typename T>
    concept is_serializable = requires
    {
        {T::_serialize  (std::declval<ext::map<ext::string, ext::any>>(), std::declval<ext::boolean>())} -> ext::type_is<void>;
        {T::_deserialize(std::declval<ext::map<ext::string, ext::any>>(), std::declval<ext::boolean>())} -> ext::type_is<T*  >;
    };
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__CONCEPTS_HPP
