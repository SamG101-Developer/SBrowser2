#include "data_transfer.hpp"
#include "data_transfer_private.hpp"

#include "html/_typedefs.hpp"
#include "html/dnd/data_transfer_item.hpp"
#include "html/detail/dnd_internals.hpp"
#include "html/elements/html_image_element.hpp"

#include <range/v3/view/transform.hpp>


html::dnd::data_transfer::data_transfer()
{
    INIT_PIMPL(data_transfer);

    ACCESS_PIMPL(data_transfer);
    d->drag_data_store = std::make_unique<detail::drag_data_store_t>();
    d->drag_data_store->drag_data_store_item_list = {};
    d->drag_data_store->drag_data_store_mode = detail::drag_data_store_mode_t::READ_WRITE;
    d->drop_effect = detail::drop_effect_t::NONE;
    d->effect_allowed = detail::effect_allowed_t::NONE;
}


auto html::dnd::data_transfer::set_drag_image(
        dom::nodes::element* element,
        ext::number<long> x,
        ext::number<long> y)
        -> void
{
    ACCESS_PIMPL(data_transfer);
    return_if (d->drag_data_store == nullptr);
    return_if (d->drag_data_store->drag_data_store_mode != detail::drag_data_store_mode_t::READ_WRITE);

    decltype(auto) image_element = dom_cast<elements::html_image_element*>(element);
    d->drag_data_store->drag_data_store_image_bitmap = nullptr; // TODO
    d->drag_data_store->drag_data_store_hot_spot_coordinate.assign(x, y);
}


auto html::dnd::data_transfer::get_drop_effect() const -> detail::drop_effect_t
{
    ACCESS_PIMPL(const data_transfer);
    return d->drop_effect;
}


auto html::dnd::data_transfer::get_effect_allowed() const -> detail::effect_allowed_t
{
    ACCESS_PIMPL(const data_transfer);
    return d->effect_allowed;
}


auto html::dnd::data_transfer::get_items() const -> ext::vector_span<data_transfer_item*>
{
    ACCESS_PIMPL(const data_transfer);
    return d->items | ranges::views::transform(&std::unique_ptr<data_transfer_item>::get);
}


auto html::dnd::data_transfer::set_drop_effect(detail::drop_effect_t new_drop_effect) -> detail::drop_effect_t
{
    ACCESS_PIMPL(data_transfer);
    return d->drop_effect = new_drop_effect;
}


auto html::dnd::data_transfer::set_effect_allowed(detail::effect_allowed_t new_effect_allowed) -> detail::effect_allowed_t
{
    ACCESS_PIMPL(data_transfer);
    return d->effect_allowed = new_effect_allowed;
}
