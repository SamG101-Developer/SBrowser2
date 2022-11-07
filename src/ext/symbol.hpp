#ifndef SBROWSER2_SRC_EXT_SYMBOL_HPP
#define SBROWSER2_SRC_EXT_SYMBOL_HPP

#include "ext/string.hpp"


_EXT_BEGIN
    class symbol
    {
    public:
        symbol(ext::string&& key): m_key(std::move(key)) {};
        symbol(const symbol&) = delete;
        symbol(symbol&&) noexcept = delete;
        auto operator=(const symbol&) = delete;
        auto operator=(symbol&&) noexcept = delete;
        auto operator==(const symbol&) = delete;
    private:
        ext::string m_key;
    };
_EXT_END


#endif //SBROWSER2_SRC_EXT_SYMBOL_HPP
