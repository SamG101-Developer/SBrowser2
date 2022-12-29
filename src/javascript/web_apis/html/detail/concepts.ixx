module;
#include "ext/macros/pimpl.hpp"


export module apis.html.concepts;

import apis.dom.types;
import apis.html.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_CONCEPTS(html)
{
    template <typename T>
    concept form_associated = requires
    {
        requires ext::inherit<T, html_element>;
        {T::get_form} -> ext::type_is<html_form_element*>;
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
        {T::get_labels} -> ext::type_is<ext::vector<dom::node*>>;
    };

    template <typename T>
    concept focusable_area = requires
    {
        requires ext::inherit<T, dom::element>; // TODO || ...

        // TODO
        //  dom::nodes::element*
        //  shapes of <area> element
        //  non-[disabled/inert] sub-widgets being rendered
        //  scrollable regions og elements being rendered and non-inert
        //  Document's viewport
        //  any part of an element
    };

    template <typename T>
    concept is_serializable = requires (T* t)
    {
        {t->_serialize  (ext::map<ext::string, ext::any>(), ext::boolean())} -> ext::type_is<void>;
        {t->_deserialize(ext::map<ext::string, ext::any>(), ext::boolean())} -> ext::type_is<T*  >;
    };
}
