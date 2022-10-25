#include "svg_abstract_animatable.hpp"
#include "svg_abstract_animatable_private.hpp"


template <typename T>
svg::types::svg_abstract_animatable<T>::svg_abstract_animatable()
{
    INIT_PIMPL_TEMPLATED(svg_abstract_animatable, T);
}


template <typename T>
auto svg::types::svg_abstract_animatable<T>::get_base_val() const -> T
{
    ACCESS_PIMPL_TEMPLATED(const svg_abstract_animatable, T);
    return d->base_value;
}


template <typename T>
auto svg::types::svg_abstract_animatable<T>::get_anim_val() const -> T
{
    ACCESS_PIMPL_TEMPLATED(const svg_abstract_animatable, T);
    return d->anim_value;
}


template <typename T>
auto svg::types::svg_abstract_animatable<T>::set_base_val(T new_base_val) -> T
{
    ACCESS_PIMPL_TEMPLATED(svg_abstract_animatable, T);
    return d->anim_value = new_base_val;
}


template <typename T>
auto svg::types::svg_abstract_animatable<T>::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<svg_abstract_animatable<T>>{isolate}
        .template inherit<dom_object>()
        .template property("baseVal", &svg_abstract_animatable<T>::get_base_val)
        .template property("animVal", &svg_abstract_animatable<T>::get_anim_val)
        .auto_wrap_objects();

    return std::move(conversion);
}
