#include "namespace_internals.hpp"

#include "ext/initializer_list.ixx"
#include "ext/ranges.hpp"

#include "javascript/environment/realms.hpp"

#include "dom/detail/exception_internals.hpp"

#include <range/v3/algorithm/contains.hpp>

using namespace std::string_view_literals;


auto dom::detail::validate_and_extract(
        const ext::string_view namespace_,
        const ext::string_view qualified_name)
        -> ext::tuple<ext::string, ext::string>
{
    auto a = ext::initializer_list{u"hello world", u"aaa", u"123"};


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
    // TODO : rework so that `(ext::string)` conversion is not required
    return adjust ? lower
            ? string | ranges::views::lowercase | ranges::to<ext::string>()
            : string | ranges::views::uppercase | ranges::to<ext::string>()
            : std::move(string);
}
