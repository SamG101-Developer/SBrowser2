#include "html_hyperlink_element_utils.hpp"

#include <utility>
#include "html_hyperlink_element_utils_private.hpp"

#include "javascript/environment/reflection.hpp"

#include "dom/detail/customization_internals.hpp"

#include "html/detail/html_element_internals.hpp"
#include "html/detail/miscellaneous_internals.hpp"

#include "url/_typedefs.hpp"
#include "url/detail/url_internals.hpp"


html::mixins::html_hyperlink_element_utils::html_hyperlink_element_utils()
{
    INIT_PIMPL(html_hyperlink_element_utils);
}


html::mixins::html_hyperlink_element_utils::~html_hyperlink_element_utils()
{
    ACCESS_PIMPL(html_hyperlink_element_utils);
    d->href.clear();
    detail::set_url(this);
}


auto html::mixins::html_hyperlink_element_utils::get_origin() const -> ext::string
{
    ACCESS_PIMPL(const html_hyperlink_element_utils);
    detail::reinitialize_url(this);
    return !d->url ? u"" : detail::serialize_url(url::detail::origin(*d->url));
}


auto html::mixins::html_hyperlink_element_utils::get_href() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        html::detail::reinitialize_url(this);

        return_if(!d->url && d->href.empty()) u"";
        return_if(!d->url) d->href;
        return detail::serialize_url(*d->url);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::get_protocol() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return !d->url ? u":" : d->url->scheme + u":";
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::get_username() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return !d->url ? u"" : d->url->username;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::get_password() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return !d->url ? u"" : d->url->password;
    CE_REACTIONS_METHOD_EXE
}

auto html::mixins::html_hyperlink_element_utils::get_host() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if(!d->url || d->url->host.empty()) u"";
        return_if(d->url->port.empty()) url::detail::serialize_host(d->url->host);
        return url::detail::serialize_host(d->url->host) + u":" + url::detail::serialize_port(d->url->port);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::get_hostname() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return !d->url || d->url->host.empty() ? u"" : url::detail::serialize_host(d->url->host);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::get_port() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return !d->url || d->url->port.empty() ? u"" : url::detail::serialize_port(d->url->port);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::get_pathname() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return !d->url ? u"" : url::detail::serialize_path(*d->url);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::get_search() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if (!d->url || d->url->query.empty()) u"";
        return u"?" + d->url->query;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::get_hash() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if (!d->url || d->url->fragment.empty()) u"";
        return u"#" + d->url->fragment;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::set_href(ext::string new_href) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_hyperlink_element_utils);
        d->href = std::move(new_href);
        detail::set_url(this);
        return d->href;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::set_protocol(ext::string new_protocol) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if(!d->url) u"";
        url::detail::basic_url_parser(std::move(new_protocol) + u":", *d->url, url::detail::state_override_t::SCHEME_START_STATE);
        detail::update_href(this);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::set_username(ext::string new_username) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if(!d->url || url::detail::url_cannot_have_username_password_port(*d->url)) u"";
        url::detail::set_username(*d->url, std::move(new_username));
        detail::update_href(this);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::set_password(ext::string new_password) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if(!d->url || url::detail::url_cannot_have_username_password_port(*d->url)) u"";
        url::detail::set_password(*d->url, std::move(new_password));
        detail::update_href(this);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::set_host(ext::string new_host) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if(!d->url || url::detail::url_has_opaque_path(*d->url)) u"";
        url::detail::basic_url_parser(std::move(new_host), *d->url, url::detail::state_override_t::HOST_STATE);
        detail::update_href(this);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::set_hostname(ext::string new_hostname) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if(!d->url || url::detail::url_has_opaque_path(*d->url)) u"";
        url::detail::basic_url_parser(std::move(new_hostname), *d->url, url::detail::state_override_t::HOSTNAME_STATE);
        detail::update_href(this);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::set_port(ext::string new_port) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if(!d->url || url::detail::url_cannot_have_username_password_port(*d->url)) u"";
        url::detail::basic_url_parser(std::move(new_port), *d->url, url::detail::state_override_t::PORT_STATE); // TODO port == null special case
        detail::update_href(this);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::set_pathname(ext::string new_pathname) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_hyperlink_element_utils);
        detail::reinitialize_url(this);
        return_if(!d->url || url::detail::url_has_opaque_path(*d->url)) u"";
        url::detail::basic_url_parser(std::move(new_pathname), *d->url, url::detail::state_override_t::PATH_STATE);
        detail::update_href(this);
    CE_REACTIONS_METHOD_EXE
}
