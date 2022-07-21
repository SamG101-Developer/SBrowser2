#include "html_hyperlink_element_utils.hpp"

#include "javascript/environment/reflection.hpp"

#include "html/detail/html_element_internals.hpp"
#include "html/detail/miscellaneous_internals.hpp"


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
        const -> ext::string
{
    detail::html_element_internals::reinitialize_url(this);
    return !m_url ? "" : detail::miscellaneous_internals::serialize_url(url::detail::url_internals::origin(m_url));
}


auto html::mixins::html_hyperlink_element_utils::get_href()
        const -> ext::string
{
    html::detail::html_element_internals::reinitialize_url(this);

    JS_REALM_GET_RELEVANT(this)
    return_if(!m_url && !reflect_has_attribute_value(this, "href", this_relevant)) "";
    return_if(!m_url) href();
    return detail::miscellaneous_internals::serialize_url(m_url);
}


auto html::mixins::html_hyperlink_element_utils::get_protocol()
        const -> ext::string
{
    detail::html_element_internals::reinitialize_url(this);
    return !m_url ? ":" : m_url.scheme() + ":";
}


auto html::mixins::html_hyperlink_element_utils::get_username()
        const -> ext::string
{
    detail::html_element_internals::reinitialize_url(this);
    return !m_url ? "" : m_url.username();
}


auto html::mixins::html_hyperlink_element_utils::get_password()
        const -> ext::string
{
    detail::html_element_internals::reinitialize_url(this);
    return !m_url ? "" : m_url.password();
}

auto html::mixins::html_hyperlink_element_utils::get_host()
        const -> ext::string
{
    detail::html_element_internals::reinitialize_url(this);
    return_if(!m_url || m_url.host().empty()) "";
    return_if(m_url.port().empty()) url::detail::url_internals::serialize_host(m_url.host());
    return url::detail::url_internals::serialize_host(m_url.host()) + ":" + url::detail:url_internals::serialize_port(m_url.port());
}


auto html::mixins::html_hyperlink_element_utils::get_hostname()
        const -> ext::string
{
    detail::html_element_internals::reinitialize_url(this);
    return !m_url || m_url.host().empty() ? "" : url::detail::url_internals::serialize_host(m_url.host());
}


auto html::mixins::html_hyperlink_element_utils::get_port()
        const -> ext::string
{
    detail::html_element_internals::reinitialize_url(this);
    return !m_url || m_url.port().empty() ? "" : url::detail::url_internals::serialize_port(m_url.port());
}


auto html::mixins::html_hyperlink_element_utils::get_pathname()
        const -> ext::string
{
    detail::html_element_internals::reinitialize_url(this);
    return !m_url || m_url ? "" : url::detail::url_internals::serialize_path(m_url);
}


auto html::mixins::html_hyperlink_element_utils::set_href(
        ext::string_view val)
        -> void
{
    property_guard(href);
    *href = val;
    detail::html_element_internals::set_url(this);
}


auto html::mixins::html_hyperlink_element_utils::set_protocol(
        ext::string_view val)
        -> void
{
    detail::html_element_internals::reinitialize_url(this);
    return_if(!m_url);
    url::detail::url_internals::basic_url_parse(ext::string{val} + ":", m_url, SCHEME_START_STATE);
    detail::html_element_internals::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_username(
        ext::string_view val)
        -> void
{
    detail::html_element_internals::reinitialize_url(this);
    return_if(!m_url || url::detail::url_internals::cannot_have_username_password_port(url));
    url::detail::url_internals::set_username(m_url, val);
    detail::html_element_internals::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_password(
        ext::string_view val)
        -> void
{
    detail::html_element_internals::reinitialize_url(this);
    return_if(!m_url || url::detail::url_internals::cannot_have_username_password_port(url));
    url::detail::url_internals::set_password(m_url, val);
    detail::html_element_internals::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_host(
        ext::string_view val)
        -> void
{
    detail::html_element_internals::reinitialize_url(this);
    return_if(!m_url || url::detail::url_internals::has_opaque_path());
    url::detail::url_internals::basic_url_parse(val, m_url, HOST_STATE);
    detail::html_element_internals::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_hostname(
        ext::string_view val)
        -> void
{
    detail::html_element_internals::reinitialize_url(this);
    return_if(!m_url || url::detail::url_internals::has_opaque_path());
    url::detail::url_internals::basic_url_parse(val, m_url, HOSTNAME_STATE);
    detail::html_element_internals::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_port(
        ext::string_view val)
        -> void
{
    detail::html_element_internals::reinitialize_url(this);
    return_if(!m_url || url::detail::url_internals::cannot_have_username_password_port(url));
    url::detail::url_internals::basic_url_parse(val, m_url, PORT_STATE); // TODO port == null special case
    detail::html_element_internals::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::set_pathname(
        ext::string_view val)
        -> void
{
    detail::html_element_internals::reinitialize_url(this);
    return_if(!m_url || url::detail::url_internals::has_opaque_path());
    url::detail::url_internals::basic_url_parse(val, m_url, PATH_STATE);
    detail::html_element_internals::update_href(this);
}


auto html::mixins::html_hyperlink_element_utils::del_href()
        -> void
{
    property_guard(href);
    *href = "";
    detail::html_element_internals::set_url(this);
}
