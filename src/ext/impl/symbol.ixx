module;
#include "ext/macros/namespaces.hpp"
#include <utility>


export module ext.js:symbol;
import :string;


_EXT_BEGIN
    export template <ext::string_like S = ext::string>
    class symbol;
_EXT_END


template <ext::string_like S>
class symbol
{
public:
    explicit symbol(ext::string&& key): m_key(std::move(key)) {};
    symbol(const symbol&) = delete;
    symbol(symbol&&) noexcept = delete;
    auto operator=(const symbol&) = delete;
    auto operator=(symbol&&) noexcept = delete;
    auto operator==(const symbol&) = delete;

private:
    S m_key;
};
