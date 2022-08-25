#include "html_hyperlink_element_utils.hpp"

#include "javascript/environment/reflection.hpp"

#include "html/detail/html_element_internals.hpp"
#include "html/detail/miscellaneous_internals.hpp"
#include "url/_typedefs.hpp"
#include "url/detail/url_internals.hpp"


html::mixins::html_hyperlink_element_utils::html_hyperlink_element_utils()
{
    bind_get(origin);
    bind_get(href);
    bind_get(protocol);
    bind_get(username);
    bind_get(password);
    bind_get(host);
    bind_get(hostname);
    bind_get(port);
    bind_get(pathname);
    bind_get(search);
    bind_get(hash);

    bind_set(href);
    bind_set(protocol);
    bind_set(username);
    bind_set(password);
    bind_set(host);
    bind_set(hostname);
    bind_set(port);
    bind_set(pathname);
    bind_set(search);
    bind_set(hash);

    bind_del(href);
}


auto html::mixins::html_hyperlink_element_utils::get_origin()
        const -> decltype(this->origin)::value_t
{
    detail::reinitialize_url(this);
    return !m_url ? "" : detail::serialize_url(ext::get<ext::string>(url::detail::origin(m_url)));
}


auto html::mixins::html_hyperlink_element_utils::get_href()
        const -> decltype(this->href)::value_t
{
    html::detail::reinitialize_url(this);

    JS_REALM_GET_RELEVANT(this)
    return_if(!m_url && !reflect_has_attribute_value(this, "href", this_relevant)) "";
    return_if(!m_url) href();
    return detail::serialize_url(m_url);
}


auto html::mixins::html_hyperlink_element_utils::get_protocol()
        const -> decltype(this->protocol)::value_t
{
    detail::reinitialize_url(this);
    return !m_url ? ":" : m_url.scheme() + ":";
}


auto html::mixins::html_hyperlink_element_utils::get_username()
        const -> decltype(this->username)::value_t
{
    detail::reinitialize_url(this);
    return !m_url ? "" : m_url.username();
}


auto html::mixins::html_hyperlink_element_utils::get_password()
        const -> decltype(this->password)::value_t
{
    detail::reinitialize_url(this);
    return !m_url ? "" : m_url.password();
}

auto html::mixins::html_hyperlink_element_utils::get_host()
        const -> decltype(this->host)::value_t
{
    detail::reinitialize_url(this);
    return_if(!m_url || m_url.host().empty()) "";
    return_if(m_url.port().empty()) url::detail::serialize_host(m_url.host());
    return url::detail::serialize_host(m_url.host()) + ":" + url::detail::serialize_port(m_url.port());
}


auto html::mixins::html_hyperlink_element_utils::get_hostname()
        const -> decltype(this->hostname)::value_t
{
    detail::reinitialize_url(this);
    return !m_url || m_url.host().empty() ? "" : url::detail::serialize_host(m_url.host());
}


auto html::mixins::html_hyperlink_element_utils::get_port()
        const -> decltype(this->port)::value_t
{
    detail::reinitialize_url(this);
    return !m_url || m_url.port().empty() ? "" : url::detail::serialize_port(m_url.port());
}


auto html::mixins::html_hyperlink_element_utils::get_pathname()
        const -> decltype(this->pathname)::value_t
{
    detail::reinitialize_url(this);
    return !m_url || m_url ? "" : url::detail::serialize_path(m_url);
}


auto html::mixins::html_hyperlink_element_utils::set_href(
        const ext::string& val)
        -> void
{
    guard_property(href);
    *href = val;
    detail::set_url(this);
}


auto html::mixins::html_hyperlink_element_utils::set_protocol(
        const ext::string& val)
        -> void
{
    detail::reinitialize_url(this);
    return_if(!m_url);
    url::detail::basic_url_parser(ext::string{val} + ":", m_url, url::detail::state_override_t::SCHEME_START_STATE);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_username(
        const ext::string& val)
        -> void
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::cannot_have_username_password_port(url));
    url::detail::set_username(m_url, val);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_password(
        const ext::string& val)
        -> void
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::cannot_have_username_password_port(url));
    url::detail::set_password(m_url, val);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_host(
        const ext::string& val)
        -> void
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::has_opaque_path());
    url::detail::basic_url_parser(val, m_url, url::detail::state_override_t::HOST_STATE);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_hostname(
        const ext::string& val)
        -> void
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::has_opaque_path());
    url::detail::basic_url_parser(val, m_url, url::detail::state_override_t::HOSTNAME_STATE);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_port(
        const ext::string& val)
        -> void
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::cannot_have_username_password_port(url));
    url::detail::basic_url_parser(val, m_url, url::detail::state_override_t::PORT_STATE); // TODO port == null special case
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_pathname(
        const ext::string& val)
        -> void
{
    detail::reinitialize_url(this);
    return_if(!m_url || url::detail::has_opaque_path());
    url::detail::basic_url_parsre(val, m_url, url::detail::state_override_t::PATH_STATE);
    detail::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::del_href()
        -> void
{
    guard_property(href);
    *href = "";
    detail::set_url(this);
}
