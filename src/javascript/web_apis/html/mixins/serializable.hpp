#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_SERIALIZABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_SERIALIZABLE_HPP


#define MAKE_SERIALIZABLE \
    auto _serialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> void; \
    auto _deserialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> self_t*;


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_SERIALIZABLE_HPP
