#include "data_transfer_item.hpp"
#include "data_transfer_item_private.hpp"


#include "file_api/file.hpp"

#include "html/_typedefs.hpp"
#include "html/detail/dnd_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "html/dnd/data_transfer.hpp"
#include "html/dnd/data_transfer_private.hpp"


auto html::dnd::data_transfer_item::get_as_string(
        ext::optional<html::dnd::data_transfer_item::function_string_callback_t> callback)
        const -> ext::string
{
    ACCESS_PIMPL(const data_transfer_item);
    return_if (!callback.has_value() || (*callback).empty()) u"";
    return_if (d->data_transfer->d_func()->drag_data_store->drag_data_store_mode == detail::drag_data_store_mode_t::PROTECTED) u"";
    return_if (d->data_transfer->d_func()->drag_data_store->drag_data_store_item_list[0]->drag_data_item_kind == detail::drag_data_item_kind_t::TEXT) u""; // TODO ...[0]?

    dom::detail::queue_task(html::detail::dom_manipulation_task_source, /* TODO : correct source? */
            [d, callback = *callback]
            {callback(d->data_transfer->d_func()->drag_data_store->drag_data_store_item_list[0]->data);}); // TODO : ...[0]?
}


auto html::dnd::data_transfer_item::get_as_file()
        const -> ext::optional<file_api::file>
{
    ACCESS_PIMPL(const data_transfer_item);
    return_if (d->data_transfer->d_func()->drag_data_store->drag_data_store_mode == detail::drag_data_store_mode_t::PROTECTED) ext::nullopt;
    return_if (d->data_transfer->d_func()->drag_data_store->drag_data_store_item_list[0]->drag_data_item_kind == detail::drag_data_item_kind_t::FILE) ext::nullopt; // TODO ...[0]?

    return file_api::file{d->data_transfer->d_func()->drag_data_store->drag_data_store_item_list[0]->data, u""}; // TODO : ...[0]?; {...} -> vector?; 2nd arg to File CTor
}


auto html::dnd::data_transfer_item::get_type() const -> ext::string_view
{
    ACCESS_PIMPL(const data_transfer_item);
    return_if (!d->data_transfer->d_func()->drag_data_store) u"";
    return d->data_transfer->d_func()->drag_data_store->drag_data_store_item_list[0]->drag_data_item_type_string; // TODO: ...[0]?
}


auto html::dnd::data_transfer_item::get_kind() const -> detail::drag_data_item_kind_t
{
    ACCESS_PIMPL(const data_transfer_item);
    return_if (!d->data_transfer->d_func()->drag_data_store) detail::drag_data_item_kind_t::_;
    return d->data_transfer->d_func()->drag_data_store->drag_data_store_item_list[0]->drag_data_item_kind; // TODO: ...[0]?
}
