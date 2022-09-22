#ifndef SBROWSER2_SRC_EXT_PIMPL_HPP
#define SBROWSER2_SRC_EXT_PIMPL_HPP

#include <memory>
#include "ext/keywords.hpp"


#define MAKE_PIMPL(c) \
protected:              \
    std::unique_ptr<c ## _private> d_ptr

#define DECLARE_PRIVATE_CLASS(ns, c) \
    namespace ns {class c ## _private;}\

#define DEFINE_PRIVATE_CLASS(ns, c) \
    DECLARE_PRIVATE_CLASS(ns, c);   \
    struct ns:: c ## _private

#define INIT_PIMPL \
        d_ptr{std::make_unique<decltype(d_ptr)::element_type>()}


#endif //SBROWSER2_SRC_EXT_PIMPL_HPP
