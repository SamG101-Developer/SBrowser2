#include "dnd_internals.hpp"

#include INCLUDE_INNER_TYPES(html)


html::detail::drag_data_store_t::drag_data_store_t()
        : drag_data_store_item_list{}
        , drag_data_store_default_feedback{u8""}
        , drag_data_store_image_bitmap{nullptr}
        , drag_data_store_hot_spot_coordinate{}
        , drag_data_store_mode{drag_data_store_mode_t::PROTECTED}
        , drag_data_store_allowed_effects_state{u8"uninitialized"}
{
}
