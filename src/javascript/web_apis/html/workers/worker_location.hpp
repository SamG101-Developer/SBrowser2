#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_LOCATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_LOCATION_HPP

// Inheritance Includes & This Class

namespace html::workers {class worker_location;}
namespace html::workers {class worker_location_private;}

// Other Includes & Forward Declarations


class html::workers::worker_location
        : public dom_object
{
public constructors:
    worker_location();
    MAKE_PIMPL(worker_location);
    MAKE_V8_AVAILABLE;

public js_properties:
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
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_LOCATION_HPP
