#include "cowl_internals.hpp"

#include "webappsec_cowl/label.hpp"
#include "webappsec_cowl/label_private.hpp"


auto webappsec::detail::is_empty_label(
        cowl::label* label)
        -> ext::boolean
{
    return label->d_func()->label_set.size() == 1 && label->d_func()->label_set[0].empty();
}
