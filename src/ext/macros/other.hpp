#ifndef SBROWSER2_SRC_EXT_MACROS_OTHER_HPP
#define SBROWSER2_SRC_EXT_MACROS_OTHER_HPP


#define COMMA ,


#define MAKE_STRINGIFIER \
private:                 \
    operator ext::string() const


#define MAKE_SERIALIZABLE \
    auto _serialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> void; \
    auto _deserialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> this_t*;


#define MAKE_TRANSFERABLE(t) \
    t(const t& other);       \
    auto operator=(const t& other) -> decltype(auto);


#endif //SBROWSER2_SRC_EXT_MACROS_OTHER_HPP
