#include "label.hpp"
#include "label_private.hpp"

#include "ext/hashing.ixx"




#include "webappsec_cowl/_typedefs.hpp"
#include "webappsec_cowl/detail/cowl_internals.hpp"
#include "webappsec_cowl/label.hpp"
#include "webappsec_cowl/label_private.hpp"

#include <range/v3/action/push_back.hpp>
#include <range/v3/view/set_algorithm.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/to_container.hpp>


webappsec::cowl::label::label(
        detail::principal_t&& principal)
{
    INIT_PIMPL(label);
    ACCESS_PIMPL(label);

    d->label_set = {{std::move(principal)}};

    using enum v8_primitive_error_t;
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [principal = std::move(principal)] mutable {return !detail::is_principal(std::move(principal));},
            u8"Argument must be a principle (origin/unique/application)");
}


auto webappsec::cowl::label::equals(label* other) -> ext::boolean
{
    return detail::are_labels_equivalent(this, other);
}


auto webappsec::cowl::label::subsumes(label* other, privilege* priv) -> ext::boolean
{
    decltype(auto) label = priv ? and_(priv->as_label()).get() : this;
    return detail::label_subsumes(label, other);
}


auto webappsec::cowl::label::and_(webappsec::cowl::label* other) const -> std::unique_ptr<label>
{
    ACCESS_PIMPL(const label);
    auto new_label = std::make_unique<label>();
    new_label->d_func()->label_set = ranges::views::set_union(d->label_set, other->d_func()->label_set);
    return new_label;
}


auto webappsec::cowl::label::and_(ext::string&& other) const -> std::unique_ptr<label>
{
    ACCESS_PIMPL(const label);
    auto new_label = std::make_unique<label>();
    new_label->d_func()->label_set = ranges::views::set_union(d->label_set, detail::label_set_t{{std::move(other)}});
    return new_label;
}


auto webappsec::cowl::label::or_(webappsec::cowl::label* other) const -> std::unique_ptr<label>
{
    ACCESS_PIMPL(const label);
    auto new_label = std::make_unique<label>();
    new_label->d_func()->label_set = d->label_set
            | ranges::views::transform(BIND_BACK(ranges::views::set_union, other->d_func()->label_set | ranges::views::join))
            | ranges::to<detail::label_set_t>();
    return new_label;
}


auto webappsec::cowl::label::or_(ext::string&& other) const -> std::unique_ptr<label>
{
    ACCESS_PIMPL(const label);
    auto new_label = std::make_unique<label>();
    new_label->d_func()->label_set = d->label_set
            | ranges::views::transform(BIND_BACK(ranges::views::set_union, detail::disjunction_set_t{std::move(other)}))
            | ranges::to<detail::label_set_t>();
    return new_label;
}


webappsec::cowl::label::operator ext::string() const
{
    ACCESS_PIMPL(const label);
    return_if (d->label_set.empty()) u"'none'";

    auto result = ext::string{};
    for (decltype(auto) disjunction_set: d->label_set)
    {
        result += !result.empty() ? u" AND " : u"";
        result += disjunction_set.size() > 1 ? u"( " : u"";

        auto inner_or = ext::string{};
        for (decltype(auto) element: disjunction_set)
            inner_or += (!inner_or.empty() ? u" OR " : u"") + element;

        result += inner_or;
        result += disjunction_set.size() > 1 ? u" )" : u"";
    }

    return result;
}
