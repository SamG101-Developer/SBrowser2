#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_SERIALIZABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_SERIALIZABLE_HPP

#include "dom_object.hpp"
namespace html::mixins {class serializable;}


class html::mixins::serializable
        : public virtual dom_object
{
protected cpp_methods:
    virtual auto m_serialize  (ext::map<ext::string, ext::any>& serialized, ext::boolean&& for_storage) -> ext::string   = 0;
    virtual auto m_deserialize(ext::map<ext::string, ext::any>& serialized, ext::boolean&& for_storage) -> serializable* = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_SERIALIZABLE_HPP
