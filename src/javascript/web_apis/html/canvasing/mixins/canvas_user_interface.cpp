#include "canvas_user_interface.hpp"

#include "html/detail/focus_internals.hpp"

#include <qpainter.h>


auto html::canvasing::mixins::canvas_user_interface::draw_if_focus_needed(
        dom::nodes::element* element)
        -> void
{
    return_if (!html::detail::is_focused(element));

    // TODO
}
