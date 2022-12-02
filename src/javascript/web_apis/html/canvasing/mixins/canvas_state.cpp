#include "canvas_state.hpp"

#include "ext/casting.ixx"

#include "html/detail/canvas_internals.hpp"
#include "html/elements/html_canvas_element.hpp"
#include "html/canvasing/image_bitmap.hpp"
#include "html/canvasing/canvas_rendering_context_2d.hpp"

#include <QtGui/QColor>


auto html::canvasing::mixins::canvas_state::save()
    -> void
{
    // Save a copy of the current state (so future mutations to the current state don't change the saved context) to the
    // stack of contexts.
    m_drawing_state_stack.push(std::make_unique<detail::drawing_state_t>(auto{*m_current_drawing_state}));
}


auto html::canvasing::mixins::canvas_state::restore()
        -> void
{
    // Don't do anything if the stack of contexts is empty -- there is nothing to restore if thihs condition is met.
    return_if (m_drawing_state_stack.empty());

    // Get the resotred from the top of the stack of contexts, set it to the current drawing state (the copy aassignment
    // operator will handle the QPainterPath changes), and pop the context from the stakc of contexts.
    decltype(auto) restored_state = m_drawing_state_stack.top();
    m_current_drawing_state = std::move(restored_state);
    m_drawing_state_stack.pop();
}


auto html::canvasing::mixins::canvas_state::reset()
        -> void
{
    // Cross-cast the mixin back into it's rendering context base type, fill the bitmap with a transparent black colour,
    // clear teh default path, and clear the stack of contexts (wipes saved contexts too).
    decltype(auto) base_context = ext::cross_cast<canvas_rendering_context_2d*>(this);
    base_context->canvas()->m_bitmap->m_bitmap_data.fill(QColor{0, 0, 0, 0});
    base_context->m_current_default_path.clear();
    base_context->m_drawing_state_stack.clear();

    // Reset the bitmap
    m_current_drawing_state->bitmap->width = 0;
    m_current_drawing_state->bitmap->height = 0;
}


auto html::canvasing::mixins::canvas_state::is_context_lost()
        -> ext::boolean
{
    // Return if the context has been lost yet or not.
    return m_context_lost;
}
