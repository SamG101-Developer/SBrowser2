module;
#include "ext/macros/macros.hpp"
#include <function2/function2.hpp>
#include <tuplet/tuple.hpp>

export module apis.dom.detail;
import apis.dom.types;
import apis.html.types;
import ext.core;
import js.env.realms;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(dom)
{
    namespace namespaces
    {
        /* [DOM] */
        inline constexpr const ext::string::value_type* HTML = u"http://www.w3.org/1999/xhtml";
        inline constexpr const ext::string::value_type* MATHML = u"http://www.w3.org/1998/Math/MathML";
        inline constexpr const ext::string::value_type* SVG = u"http://www.w3.org/2000/svg";
        inline constexpr const ext::string::value_type* XLINK = u"http://www.w3.org/1999/xlink";
        inline constexpr const ext::string::value_type* XML = u"http://www.w3.org/XML/1998/namespace";
        inline constexpr const ext::string::value_type* XMLNS = u"http://www.w3.org/2000/xmlns/";
        inline constexpr const ext::string::value_type* NONE = u"";

        /* [N3] */
        inline constexpr const ext::string::value_type* DC = u"http://purl.org/dc/elements/1.1/";
        inline constexpr const ext::string::value_type* FOAF = u"http://xmlns.com/foaf/0.1/";
        inline constexpr const ext::string::value_type* EX = u"http://www.example.org/#";
        inline constexpr const ext::string::value_type* I18N = u"https://www.w3.org/ns/i18n#";
        inline constexpr const ext::string::value_type* RDF = u"http://www.w3.org/1999/02/22-rdf-syntax-ns#";
        inline constexpr const ext::string::value_type* RDFS = u"http://www.w3.org/2000/01/rdf-schema#";
        inline constexpr const ext::string::value_type* XSD = u"http://www.w3.org/2001/XMLSchema#";
    }

    // Validation checks
    auto validate(ext::string_view qualified_name) -> void;
    auto validate_and_extract(ext::string_view namespace_, ext::string_view qualified_name) -> ext::tuple<ext::string, ext::string>;
    auto html_adjust_string(ext::string&& string, ext::boolean adjust, ext::boolean lower = true) -> ext::string;
    
    // Exception throwing
    template <v8_primitive_error_t T>
    auto throw_v8_exception(ext::unique_function<auto() -> bool>&& condition, ext::u8string&& message, js::env::env& e) -> void;
    template <dom_exception_error_t T>
    auto throw_v8_exception(ext::unique_function<auto() -> bool>&& condition, ext::u8string&& message, js::env::env& e) -> void;
    auto throw_v8_exception(dom::dom_exception&& exception) -> void;

    // Map intrinsics
    auto flatten_more(ext::map<ext::string, ext::any>&& options) -> ext::map<ext::string, ext::any>;
    auto flatten_more(ext::boolean options) -> ext::map<ext::string, ext::any>;
    auto flatten(event_listener_options_t&& options) -> ext::boolean;

    // Nodes
    template <ext::inherit<node> T>
    auto clone(T* node, document* document = nullptr, ext::boolean deep = false) -> std::unique_ptr<T>;
    auto handle_attributes_changes(attr* attribute, class element* owner_element, ext::string_view old_value, ext::string_view new_value) -> void;
    auto set_existing_attribute_value(attr* attribute, ext::string&& value) -> void;

    // Events
    template <ext::inherit<event> T=event>
    auto fire_event(ext::string&& e, dom::event_target* target, ext::map<ext::string, ext::any>&& init = {}) -> ext::boolean;
    auto retarget(const event_target* target, const event_target* other) -> event_target*;

    // Queuing tasks
    auto notify_mutation_observers() -> void;
    
    auto queue_mutation_record(mutation_type_t type, node* target, ext::string_view name, ext::string_view namespace_, ext::string_view old_value, ext::span<node*> added_nodes, ext::vector_span<node*> removed_nodes, node* previous_sibling, node* next_sibling) -> void;
    auto queue_tree_mutation_record(node* target, ext::span<node*> added_nodes, ext::span<node*> removed_nodes, node* previous_sibling, node* next_sibling) -> void;
    auto queue_mutation_observer_microtask() -> void;
    template <typename F> auto queue_microtask(F&& steps, v8::Isolate* event_loop = nullptr, document* document = nullptr) -> void;
    template <ext::callable F> auto queue_task(html::detail::task_queue_t& task_source, F&& steps, v8::Isolate* event_loop = nullptr, document* document = nullptr) -> void;
    template <ext::callable F> auto queue_global_task(html::detail::task_queue_t& task_source, v8::Local<v8::Object> global_object, F&& steps) -> void;
    template <ext::callable F> auto queue_element_task(html::detail::task_queue_t& task_source, html::html_element* element, F&& steps) -> void;
    template <ext::callable F> auto queue_media_element_task(html::html_media_element* element, F&& steps) -> void;
}
