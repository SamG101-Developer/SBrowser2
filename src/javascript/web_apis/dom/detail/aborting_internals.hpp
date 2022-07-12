#ifndef SBROWSER2_ABORTING_INTERNALS_HPP
#define SBROWSER2_ABORTING_INTERNALS_HPP

#include "ext/any.hpp"
namespace dom::abort {class abort_signal;}


namespace dom::detail::aborting_internals
{
    auto signal_abort(
            abort::abort_signal* signal,
            ext::any_view reason)
            -> void;

    auto follow_signal(
            abort::abort_signal* following_signal,
            abort::abort_signal* parent_signal)
            -> void;
}



#endif //SBROWSER2_ABORTING_INTERNALS_HPP
