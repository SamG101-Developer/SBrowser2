#include "namespace_internals.hpp"

#include "ext/ranges.hpp"
#include "dom/detail/exception_internals.hpp"

#include <range/v3/algorithm/contains.hpp>

using namespace std::string_view_literals;


auto dom::detail::namespace_internals::validate_and_extract(
        ext::string_view namespace_,
        ext::string_view qualified_name)
        -> std::tuple<ext::string, ext::string>
{
    // validate the name, and initialize the prefix to the empty string, and the local name defaults to the qualified
    // name - if there is no prefix, then the local name is the whole qualified name
    validate(qualified_name);
    ext::string prefix, local_name = qualified_name;

    // if there is a colon in the qualified name, then there is a prefix and a local name contained in the qualified
    // name, so split the qualified name on the colon, and set the prefix and local name to the first 2 results
    if (ranges::contains(qualified_name, ':'))
    {
        auto split_on_colon = qualified_name | ranges::views::split_string(':');
        prefix     = *split_on_colon.begin();
        local_name = *std::next(split_on_colon.begin());
    }


    // perform some checks on the prefix, namespace and qualified names, to make sure everything is valid, such as the
    // namespace and prefix can't both be empty, and certain variables have to conform to certain constraints,
    // especially concerning xml / xmlns prefixing

    exception_internals::throw_v8_exception_formatted<NAMESPACE_ERR>(
            [prefix, namespace_] {return prefix.empty() && namespace_.empty();},
            "Prefix and namespace must not both be empty");

    exception_internals::throw_v8_exception_formatted<NAMESPACE_ERR>(
            [prefix, namespace_] {return prefix == "xml" && namespace_ == namespace_internals::XML;},
            "Prefix and namespace must match (xml prefix)");

    exception_internals::throw_v8_exception_formatted<NAMESPACE_ERR>(
            [prefix, namespace_, qualified_name] {return (prefix == "xmlns" || qualified_name == "xmlns") && namespace_ != namespace_internals::XMLNS;},
            "Prefix / qualified_name and namespace must match (xmlns prefix / qualified_name)");

    exception_internals::throw_v8_exception_formatted<NAMESPACE_ERR>(
            [prefix, namespace_, qualified_name] {return (prefix != "xmlns" && qualified_name != "xmlns") && namespace_ == namespace_internals::XMLNS;},
            "prefix / qualified_name and namespace must match (xmlns prefix / qualified_name)");

    // return the prefix and local name - namespace_ and qualified name don't change, so they can be got from wherever
    // the function was called from
    return {prefix, local_name};
}


auto dom::detail::namespace_internals::html_adjust_string(
        ext::string_view string,
        ext::boolean_view adjust,
        ext::boolean_view lower)
        -> ext::string
{
    // TODO : rework so that `(ext::string)` conversion is not required
    return adjust ? lower
            ? string | ranges::views::lowercase() | ranges::to<ext::string>()
            : string | ranges::views::uppercase() | ranges::to<ext::string>()
            : (ext::string)string;
}
