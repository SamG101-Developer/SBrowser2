#include "label.hpp"

#include "ext/hashing.hpp"
#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(webappsec_cowl)

#include "dom/detail/exception_internals.hpp"

#include "webappsec_cowl/detail/cowl_internals.hpp"

#include <range/v3/view/set_algorithm.hpp>
#include <range/v3/to_container.hpp>



webappsec::cowl::label::label(
        detail::principal_t&& principal)
        : m_label_set{detail::disjunction_set_t{std::move(principal)}}
{
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [principal = std::move(principal)] mutable {return !detail::is_principal(std::move(principal));},
            "Argument must be a principle (origin/unique/application)");
}


auto webappsec::cowl::label::equals(
        label* other)
        -> ext::boolean
{
    return detail::are_labels_equivalent(this, other);
}


auto webappsec::cowl::label::subsumes(
        label* other,
        privelege* priv)
        -> ext::boolean
{
    decltype(auto) label = priv ? and_(priv->as_label()) : this;
    return detail::label_subsumes(label, other);
}


auto webappsec::cowl::label::and_(
        ext::variant<label*, ext::string> other)
        -> label
{
    auto new_label = ext::holds_alternative<label*>(other)
            ? auto{*ext::get<label*>(other)}
            : auto{ext::get<ext::string>(other)};

    new_label.m_label_set = new_label.m_label_set
            | ranges::views::set_intersection(m_label_set)
            | ranges::to<decltype(m_label_set)>;
}


auto webappsec::cowl::label::or_(
        ext::variant<label*, ext::string> other)
        -> label
{
    auto new_label = ext::holds_alternative<label*>(other)
            ? auto{*ext::get<label*>(other)}
            : auto{ext::get<ext::string>(other)};

    new_label.m_label_set = new_label.m_label_set
            | ranges::views::set_union(m_label_set)
            | ranges::to<decltype(m_label_set)>;
}


auto webappsec::cowl::label::to_json()
        const -> ext::string
{
    return_if (m_label_set.empty()) "'none'";

    auto result = ext::string{};
    for (decltype(auto) disjunction_set: m_label_set)
    {
        result += !result.empty() ? " AND " : "";
        result += disjunction_set.size() > 1 ? "( " : "";

        auto inner_or = ext::string{};
        for (decltype(auto) element: disjunction_set)
            inner_or += (!inner_or.empty() ? " OR " : "") + element;

        result += inner_or;
        result += disjunction_set.size() > 1 ? " )" : "";
    }

    return result;
}
