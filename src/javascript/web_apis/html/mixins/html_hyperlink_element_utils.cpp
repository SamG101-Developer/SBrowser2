#include "html_hyperlink_element_utils.hpp"
#include "html_hyperlink_element_utils_private.hpp"

#include "javascript/environment/reflection.hpp"

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
    return !d->url ? "" : detail::serialize_url(url::detail::origin(*d->url));
}


auto html::mixins::html_hyperlink_element_utils::get_href() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
    ACCESS_PIMPL(const html_hyperlink_element_utils);
    html::detail::reinitialize_url(this);

    JS_REALM_GET_RELEVANT(this);
    return_if(!d->url && !reflect_has_attribute_value(this, u8"href", this_relevant)) u8"";
    return_if(!d->url) d->href;
    return detail::serialize_url(*d->url);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_hyperlink_element_utils::get_protocol() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
    ACCESS_PIMPL(const html_hyperlink_element_utils);
    detail::reinitialize_url(this);
    return !d->url ? u8":" : d->url->scheme + u8":";
}


auto html::mixins::html_hyperlink_element_utils::get_username() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
    ACCESS_PIMPL(const html_hyperlink_element_utils);
    detail::reinitialize_url(this);
    return !d->url ? u8"" : d->url->username;
}


auto html::mixins::html_hyperlink_element_utils::get_password() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
    ACCESS_PIMPL(const html_hyperlink_element_utils);
    detail::reinitialize_url(this);
    return !d->url ? u8"" : d->url->password;
}

auto html::mixins::html_hyperlink_element_utils::get_host() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
    ACCESS_PIMPL(const html_hyperlink_element_utils);
    detail::reinitialize_url(this);
    return_if(!d->url || d->url->host.empty()) u8"";
    return_if(d->url->port.empty()) url::detail::serialize_host(d->url->host);
    return url::detail::serialize_host(d->url->host) + u8":" + url::detail::serialize_port(d->url->port);
}


auto html::mixins::html_hyperlink_element_utils::get_hostname() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
    ACCESS_PIMPL(const html_hyperlink_element_utils);
    detail::reinitialize_url(this);
    return !d->url || d->url->host.empty() ? u8"" : url::detail::serialize_host(d->url->host);
}


auto html::mixins::html_hyperlink_element_utils::get_port() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
    ACCESS_PIMPL(const html_hyperlink_element_utils);
    detail::reinitialize_url(this);
    return !d->url || d->url->port.empty() ? u8"" : url::detail::serialize_port(d->url->port);
}


auto html::mixins::html_hyperlink_element_utils::get_pathname() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
    ACCESS_PIMPL(const html_hyperlink_element_utils);
    detail::reinitialize_url(this);
    return !d->url ? u8"" : url::detail::serialize_path(*d->url);
}


auto html::mixins::html_hyperlink_element_utils::set_href(ext::string new_href) -> ext::string
{
    guard_property(href);
    *href = val;
    detail::set_url(this);
}


auto html::mixins::html_hyperlink_element_utils::set_protocol(ext::string new_protocol) -> ext::string
{
    detail::reinitialize_url(this);
    return_if(!m_url);
    url::detail::basic_url_parser(ext::string{val} + ":", m_url, url::detail::state_override_t::SCHEME_START_STATE);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_username(ext::string new_username) -> ext::string
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::cannot_have_username_password_port(url));
    url::detail::set_username(m_url, val);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_password(ext::string new_password) -> ext::string
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::cannot_have_username_password_port(url));
    url::detail::set_password(m_url, val);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_host(ext::string new_host) -> ext::string
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::has_opaque_path());
    url::detail::basic_url_parser(val, m_url, url::detail::state_override_t::HOST_STATE);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_hostname(ext::string new_hostname) -> ext::string
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::has_opaque_path());
    url::detail::basic_url_parser(val, m_url, url::detail::state_override_t::HOSTNAME_STATE);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_port(ext::string new_port) -> ext::string
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::cannot_have_username_password_port(url));
    url::detail::basic_url_parser(val, m_url, url::detail::state_override_t::PORT_STATE); // TODO port == null special case
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_pathname(ext::string new_pathname) -> ext::string
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::has_opaque_path());
    url::detail::basic_url_parsre(val, m_url, url::detail::state_override_t::PATH_STATE);
    detail::update_href(this);
}
