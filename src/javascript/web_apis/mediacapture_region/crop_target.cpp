#include "crop_target.hpp"
#include "crop_target_private.hpp"





mediacapture::region::crop_target::crop_target()
{
    INIT_PIMPL(crop_target);
}


auto mediacapture::region::crop_target::_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage) -> void
{
    ACCESS_PIMPL(crop_target);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<DATA_CLONE_ERR>([for_storage] {return for_storage;});
    serialized.insert_or_assign(u"$CropTargetElement", d->element.get());
}


auto mediacapture::region::crop_target::_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage) -> self_t*
{
    ACCESS_PIMPL(crop_target);
    d->element = serialized[u"$CropTargetElement"].to<dom::nodes::element*>();
    return this;
}
