#include "url_search_params.hpp"
#include "ext/functional.ixx"
#include "ext/pair.ixx"
#include "url_search_params_private.hpp"

#include "url/detail/application_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/to_container.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/action/push_back.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/action/sort.hpp>


url::url_search_params::url_search_params(ext::vector<ext::pair<ext::string, ext::string>>&& init)
{
    INIT_PIMPL(url_search_params);
    ACCESS_PIMPL(url_search_params);
    d->list.replace(std::move(init));
}


url::url_search_params::url_search_params(ext::map<ext::string, ext::string>&& init)
{
    INIT_PIMPL(url_search_params);
    ACCESS_PIMPL(url_search_params);
    d->list = std::move(init);
}


url::url_search_params::url_search_params(ext::string_view init)
{
    INIT_PIMPL(url_search_params);
    ACCESS_PIMPL(url_search_params);
    d->list = detail::application_x_www_form_urlencoded_string_parser(init.starts_with('?') ? init.substr(1) : init);
}


url::url_search_params::operator ext::string() const
{
    ACCESS_PIMPL(url_search_params);
    return detail::application_x_www_form_urlencoded_serializer(d->list);
}


auto url::url_search_params::append(ext::string&& name, ext::string&& value) -> void
{
    ACCESS_PIMPL(url_search_params);
    d->list |= ranges::actions::push_back(ext::make_pair(std::move(name), std::move(value)));
    detail::update_url_search_params(this);
}


auto url::url_search_params::delete_(ext::string&& name) -> void
{
    ACCESS_PIMPL(url_search_params);
    d->list |= ranges::actions::remove(std::move(name));
    detail::update_url_search_params(this);
}


auto url::url_search_params::get(ext::string&& name) -> ext::string
{
    ACCESS_PIMPL(url_search_params);
    return d->list.contains(name) ? d->list[std::move(name)] : u"";
}


auto url::url_search_params::get_all(ext::string&& name) -> ext::vector<ext::string>
{
    ACCESS_PIMPL(url_search_params);
    return d->list.values()
            | ranges::views::filter(BIND_BACK(ext::pair_key_matches, std::move(name)))
            | ranges::to<ext::vector<ext::string>>();
}


auto url::url_search_params::has(ext::string&& name) -> ext::boolean
{
    ACCESS_PIMPL(url_search_params);
    return d->list.contains(std::move(name));
}


auto url::url_search_params::set(ext::string&& name, ext::string&& value) -> void
{
    ACCESS_PIMPL(url_search_params);
    // TODO
    detail::update_url_search_params(this);
}


auto url::url_search_params::sort() -> void
{
    ACCESS_PIMPL(url_search_params);
    d->list |= ranges::actions::sort(ext::cmp::le);
    detail::update_url_search_params(this);
}
