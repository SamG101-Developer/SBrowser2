#ifndef SBROWSER2_ABORTING_INTERNALS_HPP
#define SBROWSER2_ABORTING_INTERNALS_HPP


#include INCLUDE_INNER_TYPES(dom)
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



#endif //SBROWSER2_ABORTING_INTERNALS_HPP
