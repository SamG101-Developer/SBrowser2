#ifndef SBROWSER2_FORM_DATA_HPP
#define SBROWSER2_FORM_DATA_HPP

#include "dom_object.hpp"
namespace xhr {class form_data;}

#include "ext/vector.hpp"
namespace file_api {class blob;}
namespace file_api {class file;}
namespace html::elements {class html_form_element;}


class xhr::form_data
        : public web_apis::dom_object
{
public aliases:
    using form_data_entry_t = std::variant<ext::string_view, file_api::file*>;

public constructors:
    form_data(html::elements::html_form_element* form = nullptr);

public js_properties:
    auto append(ext::string_view name, ext::string_view value) -> void;
    auto append(ext::string_view name, file_api::blob* blob_object, ext::string_view file_name = "") -> void;
    auto set(ext::string_view name, ext::string_view value) -> void;
    auto set(ext::string_view name, file_api::blob* blob_object, ext::string_view file_name = "") -> void;
    auto get(ext::string_view name) -> form_data_entry_t;
    auto get_all(ext::string_view name) -> ext::vector<form_data_entry_t>;
    auto delete_(ext::string_view name) -> void;
    auto has(ext::string_view name) -> ext::boolean;
};


#endif //SBROWSER2_FORM_DATA_HPP
