#ifndef SBROWSER2_SRC_EXT_SLOT_HPP
#define SBROWSER2_SRC_EXT_SLOT_HPP

#include <utility>
namespace ext {template <typename T> class slot;}


template <typename T>
class ext::slot
{
public:
    slot() = default;
    ~slot() = default;

    slot(const slot&) = delete;
    slot(slot&&) noexcept = default;
    auto operator=(const slot&) -> slot& = delete;
    auto operator=(slot&&) noexcept -> slot& = default;

    auto operator=(const T& value) -> slot& {m_value = value; return *this;}
    auto operator=(T&& value) -> slot& {m_value = std::move(value); return *this;}
    auto operator()() -> T& {return m_value;}
    auto operator->() -> T& {return m_value;}

private:
    T m_value;
};


#endif //SBROWSER2_SRC_EXT_SLOT_HPP