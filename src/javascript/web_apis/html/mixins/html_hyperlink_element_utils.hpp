#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP


namespace html::mixins {class html_hyperlink_element_utils;}
namespace html::mixins {class html_hyperlink_element_utils_private;}


class html::mixins::html_hyperlink_element_utils
        : public virtual dom_object
{
public constructors:
    html_hyperlink_element_utils();
    ~html_hyperlink_element_utils() override;
    MAKE_PIMPL(html_hyperlink_element_utils);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

private js_properties:
    DEFINE_GETTER(origin, ext::string);
    DEFINE_GETTER(href, ext::string);
    DEFINE_GETTER(protocol, ext::string);
    DEFINE_GETTER(username, ext::string);
    DEFINE_GETTER(password, ext::string);
    DEFINE_GETTER(host, ext::string);
    DEFINE_GETTER(hostname, ext::string);
    DEFINE_GETTER(port, ext::string);
    DEFINE_GETTER(pathname, ext::string);
    DEFINE_GETTER(search, ext::string);
    DEFINE_GETTER(hash, ext::string);

    DEFINE_SETTER(href, ext::string);
    DEFINE_SETTER(protocol, ext::string);
    DEFINE_SETTER(username, ext::string);
    DEFINE_SETTER(password, ext::string);
    DEFINE_SETTER(host, ext::string);
    DEFINE_SETTER(hostname, ext::string);
    DEFINE_SETTER(port, ext::string);
    DEFINE_SETTER(pathname, ext::string);
    DEFINE_SETTER(search, ext::string);
    DEFINE_SETTER(hash, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_HPP
