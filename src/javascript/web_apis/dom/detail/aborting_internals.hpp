#ifndef SBROWSER2_ABORTING_INTERNALS_HPP
#define SBROWSER2_ABORTING_INTERNALS_HPP

#include "ext/any.hpp"
#include USE_INNER_TYPES(dom)
namespace dom::abort {class abort_signal;}


namespace dom::detail
{
    auto signal_abort(
            abort::abort_signal* signal,
            const ext::any& reason)
            -> void;

    auto follow_signal(
            abort::abort_signal* following_signal,
            abort::abort_signal* parent_signal)
            -> void;
}


struct dom::detail::abort_signal_t
{
    abort_signal_callbacks_t m_abort_algorithms;
};



#endif //SBROWSER2_ABORTING_INTERNALS_HPP
