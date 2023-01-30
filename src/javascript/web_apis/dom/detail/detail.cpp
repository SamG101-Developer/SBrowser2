module;
#include "ext/macros.hpp"
#include <utility>
#include <tuplet/tuple.hpp>
#include <range/v3/to_container.hpp>


module apis.dom.detail;
import apis.dom.types;

import ext.core;

import js.env.realms;


auto dom::detail::validate_and_extract(
        ext::string_view namespace_,
        ext::string_view qualified_name)
        -> ext::tuple<ext::string, ext::string>
{
    // Validate the name, and initialize the prefix to the empty string, and the local name defaults to the qualified
    // name. f there is no prefix, then the local name is the whole qualified name.
    validate(qualified_name);
    auto local_name = ext::string{qualified_name.data()};
    auto prefix = ext::string{};

    // If there is a colon in the qualified name, then there is a prefix and local name contained in the qualified name,
    // so split the qualified name on the colon, and set the prefix and local name to the results. TODO : 2+ colons?
    if (auto split_on_colon = qualified_name | ranges::views::split_string(':'); split_on_colon.size() >= 1)
        ext::tie(prefix, local_name) = ext::make_tuple(*split_on_colon.begin(), *split_on_colon.end());


    // Perform some checks on the prefix, namespace and qualified names, to make sure everything is valid, such as the
    // namespace and prefix can't both be empty, and certain variables have to conform to certain constraints,
    // especially concerning xml / xmlns prefixing.
    using enum dom::detail::dom_exception_error_t;
    using namespace namespaces;
    auto e = js::env::env::current();

    throw_v8_exception<NAMESPACE_ERR>(
            [prefix, namespace_] {return prefix.empty() && namespace_.empty();},
            u8"Prefix and namespace must not both be empty", e);

    throw_v8_exception<NAMESPACE_ERR>(
            [prefix, namespace_] {return prefix == u"xml" && namespace_ == XML;},
            u8"Prefix and namespace must match (xml prefix)", e);

    throw_v8_exception<NAMESPACE_ERR>(
            [prefix, namespace_, qualified_name] {return (prefix == u"xmlns" || qualified_name == u"xmlns") && namespace_ != XMLNS;},
            u8"Prefix / qualified_name and namespace must match (xmlns prefix / qualified_name)", e);

    throw_v8_exception<NAMESPACE_ERR>(
            [prefix, namespace_, qualified_name] {return (prefix != u"xmlns" && qualified_name != u"xmlns") && namespace_ == XMLNS;},
            u8"prefix / qualified_name and namespace must match (xmlns prefix / qualified_name)", e);

    // Return the prefix and local name - namespace_ and qualified name don't change, so they can be got from wherever
    // the function was called from
    return {prefix, local_name};
}


auto dom::detail::html_adjust_string(
        ext::string&& string,
        ext::boolean adjust,
        ext::boolean lower)
        -> ext::string
{
    return adjust ? lower
            ? string | ranges::views::lowercase | ranges::to<ext::string>()
            : string | ranges::views::uppercase | ranges::to<ext::string>()
            : std::move(string);
}



auto dom::detail::flatten_more(ext::map<ext::string, ext::any>&& options) -> ext::map<ext::string, ext::any>
{
    // Return {capture: true} if the options is a bool value, otherwise the map already being held in the variant
    // object. This just acts as a normalizer to get the "capture" value in map form.
    return std::move(options);
}


auto dom::detail::flatten_more(ext::boolean options) -> ext::map<ext::string, ext::any>
{
    // Return {capture: true} if the options is a bool value, otherwise the map already being held in the variant
    // object. This just acts as a normalizer to get the "capture" value in map form.
    return {{u"capture", options}};
}


auto dom::detail::element_interface(ext::string_view name, ext::string_view namespace_) -> std::unique_ptr<node>
{
    if (namespace_ == dom::detail::namespaces::HTML) string_switch(name)
    {
        string_case("a"): return std::make_unique<html::html_anchor_element>();
        string_case("abbr"): return std::make_unique<html::html_element>();
        string_case("address"): return std::make_unique<html::html_element>();
        string_case("area"): return std::make_unique<html::html_area_element>();
        string_case("article"): return std::make_unique<html::html_element>();
        string_case("aside"): return std::make_unique<html::html_element>();
        string_case("audio"): return std::make_unique<html::html_audio_element>();
        string_case("b"): return std::make_unique<html::html_element>();
        string_case("base"): return std::make_unique<html::html_base_element>();
        string_case("bdi"): return std::make_unique<html::html_element>();
        string_case("bdo"): return std::make_unique<html::html_element>();
        string_case("blockquote"): return std::make_unique<html::html_quote_element>();
        string_case("body"): return std::make_unique<html::html_body_element>();
        string_case("br"): return std::make_unique<html::html_br_element>();
        string_case("button"): return std::make_unique<html::html_button_element>();
        string_case("canvas"): return std::make_unique<html::html_canvas_element>();
        string_case("caption"): return std::make_unique<html::html_table_caption_element>();
        string_case("cite"): return std::make_unique<html::html_element>();
        string_case("code"): return std::make_unique<html::html_element>();
        string_case("col"): return std::make_unique<html::html_table_col_element>();
        string_case("colgroup"): return std::make_unique<html::html_table_col_element>();
        string_case("data"): return std::make_unique<html::html_data_element>();
        string_case("datalist"): return std::make_unique<html::html_data_list_element>();
        string_case("dd"): return std::make_unique<html::html_element>();
        string_case("del"): return std::make_unique<html::html_mod_element>();
        string_case("details"): return std::make_unique<html::html_details_element>();
        string_case("dfn"): return std::make_unique<html::html_element>();
        string_case("dialog"): return std::make_unique<html::html_dialog_element>();
        string_case("div"): return std::make_unique<html::html_div_element>();
        string_case("dl"): return std::make_unique<html::html_dlist_element>();
        string_case("dt"): return std::make_unique<html::html_element>();
        string_case("em"): return std::make_unique<html::html_element>();
        string_case("embed"): return std::make_unique<html::html_embed_element>();
        string_case("fieldset"): return std::make_unique<html::html_field_set_element>();
        string_case("figcaption"): return std::make_unique<html::html_element>();
        string_case("figure"): return std::make_unique<html::html_element>();
        string_case("footer"): return std::make_unique<html::html_element>();
        string_case("form"): return std::make_unique<html::html_form_element>();
        string_case("h1"): return std::make_unique<html::html_heading_element>();
        string_case("h2"): return std::make_unique<html::html_heading_element>();
        string_case("h3"): return std::make_unique<html::html_heading_element>();
        string_case("h4"): return std::make_unique<html::html_heading_element>();
        string_case("h5"): return std::make_unique<html::html_heading_element>();
        string_case("h6"): return std::make_unique<html::html_heading_element>();
        string_case("head"): return std::make_unique<html::html_head_element>();
        string_case("header"): return std::make_unique<html::html_element>();
        string_case("hgroup"): return std::make_unique<html::html_element>();
        string_case("hr"): return std::make_unique<html::html_hr_element>();
        string_case("html"): return std::make_unique<html::html_html_element>();
        string_case("i"): return std::make_unique<html::html_element>();
        string_case("iframe"): return std::make_unique<html::html_iframe_element>();
        string_case("img"): return std::make_unique<html::html_image_element>();
        string_case("input"): return std::make_unique<html::html_input_element>();
        string_case("ins"): return std::make_unique<html::html_mod_element>();
        string_case("kbd"): return std::make_unique<html::html_element>();
        string_case("label"): return std::make_unique<html::html_label_element>();
        string_case("legend"): return std::make_unique<html::html_legend_element>();
        string_case("li"): return std::make_unique<html::html_li_element>();
        string_case("link"): return std::make_unique<html::html_link_element>();
        string_case("main"): return std::make_unique<html::html_element>();
        string_case("map"): return std::make_unique<html::html_map_element>();
        string_case("mark"): return std::make_unique<html::html_element>();
        string_case("meta"): return std::make_unique<html::html_meta_element>();
        string_case("meter"): return std::make_unique<html::html_meter_element>();
        string_case("menu"): return std::make_unique<html::html_menu_element>();
        string_case("nav"): return std::make_unique<html::html_element>();
        string_case("noscript"): return std::make_unique<html::html_element>();
        string_case("object"): return std::make_unique<html::html_object_element>();
        string_case("ol"): return std::make_unique<html::html_olist_element>();
        string_case("optgroup"): return std::make_unique<html::html_opt_group_element>();
        string_case("option"): return std::make_unique<html::html_option_element>();
        string_case("output"): return std::make_unique<html::html_output_element>();
        string_case("p"): return std::make_unique<html::html_paragraph_element>();
        string_case("picture"): return std::make_unique<html::html_picture_element>();
        string_case("pre"): return std::make_unique<html::html_pre_element>();
        string_case("progress"): return std::make_unique<html::html_progress_element>();
        string_case("q"): return std::make_unique<html::html_quote_element>();
        string_case("rp"): return std::make_unique<html::html_element>();
        string_case("rt"): return std::make_unique<html::html_element>();
        string_case("ruby"): return std::make_unique<html::html_element>();
        string_case("s"): return std::make_unique<html::html_element>();
        string_case("samp"): return std::make_unique<html::html_element>();
        string_case("script"): return std::make_unique<html::html_script_element>();
        string_case("section"): return std::make_unique<html::html_element>();
        string_case("select"): return std::make_unique<html::html_select_element>();
        string_case("slot"): return std::make_unique<html::html_slot_element>();
        string_case("small"): return std::make_unique<html::html_element>();
        string_case("source"): return std::make_unique<html::html_source_element>();
        string_case("span"): return std::make_unique<html::html_span_element>();
        string_case("strong"): return std::make_unique<html::html_element>();
        string_case("style"): return std::make_unique<html::html_style_element>();
        string_case("sub"): return std::make_unique<html::html_element>();
        string_case("summary"): return std::make_unique<html::html_element>();
        string_case("sup"): return std::make_unique<html::html_element>();
        string_case("table"): return std::make_unique<html::html_table_element>();
        string_case("tbody"): return std::make_unique<html::html_table_section_element>();
        string_case("td"): return std::make_unique<html::html_table_cell_element>();
        string_case("template"): return std::make_unique<html::html_template_element>();
        string_case("textarea"): return std::make_unique<html::html_text_area_element>();
        string_case("tfoot"): return std::make_unique<html::html_table_section_element>();
        string_case("th"): return std::make_unique<html::html_table_cell_element>();
        string_case("thead"): return std::make_unique<html::html_table_section_element>();
        string_case("time"): return std::make_unique<html::html_time_element>();
        string_case("title"): return std::make_unique<html::html_title_element>();
        string_case("tr"): return std::make_unique<html::html_table_row_element>();
        string_case("track"): return std::make_unique<html::html_track_element>();
        string_case("u"): return std::make_unique<html::html_element>();
        string_case("ul"): return std::make_unique<html::html_ulist_element>();
        string_case("var"): return std::make_unique<html::html_element>();
        string_case("video"): return std::make_unique<html::html_video_element>();
        string_case("wbr"): return std::make_unique<html::html_element>();
    }

    else if (dom::detail::is_valid_custom_name(name))
    {
        return std::make_unique<html::html_element>(name);
    }

    return std::make_unique<html::html_unknown_element>();
}


