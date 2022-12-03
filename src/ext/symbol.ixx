export module ext.symbol;
import ext.string;
import std.core;


_EXT_BEGIN
    export class symbol
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
