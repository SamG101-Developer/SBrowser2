#include "mimetype_internals.hpp"



#include "infra/detail/infra_strings_internals.hpp"
#include "fetch/detail/http_internals.hpp"

#include "mimesniff/detail/token_internals.hpp"

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/range/operations.hpp>


auto mimesniff::detail::essence(
        const detail::mime_type_t& mime_type)
        -> ext::string
{
    return mime_type.type + char(0x002f) + mime_type.sub_type;
}


auto mimesniff::detail::parse_mime_type(
        ext::string input)
        -> ext::optional<mime_type_t>
{
    infra::detail::strip_leading_and_trailing_ascii_whitespace(input);
    auto position = input.begin();

    auto type = infra::detail::collect_code_points_not_matching(input, position, char(0x002f));
    return_if (type.empty() || !ranges::all_of(type, is_http_token_code_point)) ext::nullopt;
    return_if (position >= input.end()) ext::nullopt;
    ranges::advance(position, 1);

    auto subtype = infra::detail::collect_code_points_not_matching(input, position, char(0x003b));
    infra::detail::strip_trailing_ascii_whitespace(subtype);
    return_if (subtype.empty() || !ranges::all_of(subtype, is_http_token_code_point)) ext::nullopt;

    mime_type_t mime_type {.type = type, .sub_type = subtype};
    while (position < input.end())
    {
        ranges::advance(position, 1);
        infra::detail::collect_ascii_whitespace(input, position);

        auto parameter_name = infra::detail::collect_code_points_not_matching(input, position, char(0x003b), char(0x003d));
        if (position < input.end())
        {
            continue_if (*position == char(0x003b));
            ranges::advance(position, 1);
        }

        break_if (position >= input.end());

        ext::string parameter_value;
        if (*position == char(0x0022))
        {
            parameter_value = fetch::detail::collect_http_quoted_string(input, position, true);
            infra::detail::collect_code_points_not_matching(input, position, char(0x003b));
        }
        else
        {
            parameter_value = infra::detail::collect_code_points_not_matching(input, position, char(0x003b));
            infra::detail::strip_trailing_ascii_whitespace(parameter_value);
            continue_if (parameter_value.empty());
        }

        if (!parameter_name.empty()
                && ranges::all_of(parameter_name, is_http_quoted_string_token_code_point)
                && ranges::all_of(parameter_value, is_http_quoted_string_token_code_point)
                && !mime_type.parameters.contains(parameter_name))
            mime_type.parameters.emplace(std::move(parameter_name), std::move(parameter_value));
    }

    return mime_type;
}


auto mimesniff::detail::serialize_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::string
{
    auto serialization = essence(mime_type);
    for (auto [name, value]: mime_type.parameters)
    {
        serialization += char(0x003b);
        serialization += name;
        serialization += char(0x003d);

        if (!ranges::all_of(value, is_http_token_code_point))
        {
            value |= ranges::actions::replace(ext::string{char(0x0022)}, ext::string{char(0x0022)} + char(0x005c));
            value.insert(value.begin(), char(0x0022));
            value.push_back(char(0x0022));
        }

        serialization += value;
    }

    return serialization;
}


auto mimesniff::detail::is_image_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    return mime_type.type == "image";
}


auto mimesniff::detail::is_audio_or_video_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    auto audio_video_mime_types = {
            "audio", "video"};

    return ranges::contains(audio_video_mime_types, mime_type.type) || essence(mime_type) == "application/ogg";
}


auto mimesniff::detail::is_font_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    auto font_mime_type_essences = {
            "application/font-cff", "application/font-cff", "application/-sfnt", "application/ttf", "application/woff",
            "application/vnd.ms-fontobject", "application/vnd.ms-opentype"};

    return ranges::contains(font_mime_type_essences, essence(mime_type));
}


auto mimesniff::detail::is_zip_based_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    auto zip_mime_type_essences = {
            "application/zip"};

    return ranges::contains(zip_mime_type_essences, essence(mime_type)) || mime_type.sub_type.ends_with("+xml");
}


auto mimesniff::detail::is_archive_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    auto archive_mime_type_essences = {
            "application/x-rar-compressed", "application/zip", "application.x-gzip"};

    return ranges::contains(archive_mime_type_essences, essence(mime_type));
}


auto mimesniff::detail::is_xml_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    auto xml_mime_type_essences = {
            "text/xml", "application/xml"};

    return ranges::contains(xml_mime_type_essences, essence(mime_type));
}


auto mimesniff::detail::is_html_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    auto html_mime_type_essences = {
            "text/html"};

    return ranges::contains(html_mime_type_essences, essence(mime_type));
}


auto mimesniff::detail::is_scriptable_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    auto scriptable_mime_type_essence = {
            "application/pdf"};

    return is_xml_mime_type(mime_type) || is_html_mime_type(mime_type) || ranges::contains(scriptable_mime_type_essence, essence(mime_type));
}


auto mimesniff::detail::is_javascript_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    auto javascript_mime_type_essence = {
            "application/ecmascript", "application/javascript", "application/x-ecmascript", "application/x-javascript",
            "text/ecmascript", "text/javascript", "text/javascript1.0", "text/javascript1.1", "text/javascript1.2",
            "text/javascript1.3", "text/javascript1.4", "text/javascript1.5", "text/jscript", "text/livescript",
            "text/x-ecmascript" ,"text/x-javascript"};

    return ranges::contains(javascript_mime_type_essence, essence(mime_type));
}


auto mimesniff::detail::is_json_mime_type(
        const detail::mime_type_t& mime_type)
        -> ext::boolean
{
    auto json_mime_type_essence = {
            "application/json", "text/json"};

    return ranges::contains(json_mime_type_essence, essence(mime_type)) || mime_type.sub_type.ends_with("+json");
}
