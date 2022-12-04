#ifndef SBROWSER2_SRC_EXT_MACROS_CONSTRUCTORS_HPP
#define SBROWSER2_SRC_EXT_MACROS_CONSTRUCTORS_HPP

#define DISALLOW_COPY(type)     \
    type(const type&) = delete; \
    auto operator=(const type&) -> type& = delete

#define ALLOW_COPY(type)               \
    type(const type&) = default; \
    auto operator=(const type&) -> type& = default

#define ALLOW_MOVE(type)             \
    type(type&&) noexcept = default; \
    auto operator=(type&&) noexcept -> type& = delete


#endif //SBROWSER2_SRC_EXT_MACROS_CONSTRUCTORS_HPP
