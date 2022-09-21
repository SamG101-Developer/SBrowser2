#ifndef SBROWSER2_SRC_EXT_PIMPL_HPP
#define SBROWSER2_SRC_EXT_PIMPL_HPP

#include <memory>

#define MAKE_PIMPL(c) \
private:              \
    std::unique_ptr<detail:: c ## _t> d_ptr;

#define MAKE_PIMPL_PROTECTED(c) \
protected:                       \
    std::unique_ptr<detail:: c ## _t> d_ptr;

#define MAKE_PIMPL_QT(c) \
private:                 \
    std::unique_ptr<c> d_ptr

#define MAKE_PIMPL_QT_PROTECTED(c) \
protected:                         \
    std::unique_ptr<c> d_ptr


#define INIT_PIMPL \
        d_ptr{std::make_unique<decltype(d_ptr)::element_type>()}


#endif //SBROWSER2_SRC_EXT_PIMPL_HPP
