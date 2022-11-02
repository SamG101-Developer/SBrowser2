#include "html_source_element.hpp"
#include "html_source_element_private.hpp"

#include "dom/detail/customization_internals.hpp"


html::elements::html_source_element::html_source_element()
{
    INIT_PIMPL(html_source_element);
    ACCESS_PIMPL(html_source_element);
    
    d->insertion_steps = []
    {
        /* TODO : HTMLMediaElement parent handling
         * TODO : HTMLPictureElement stuff */
    };

    d->remove_steps = [](dom::nodes::node* old_parent)
    {
        /* TODO : HTMLPictureElement stuff */
    };

    HTML_CONSTRUCTOR
}


auto html::elements::html_source_element::get_src() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_source_element);
        return d->src;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::get_type() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_source_element);
        return d->type;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::get_srcset() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_source_element);
        return d->srcset;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::get_sizes() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_source_element);
        return d->sizes;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::get_media() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_source_element);
        return d->media;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::get_width() const -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_source_element);
        return d->width;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::get_height() const -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_source_element);
        return d->height;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::set_src(ext::string new_src) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_source_element);
        return d->src = std::move(new_src);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::set_type(ext::string new_type) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_source_element);
        return d->type = std::move(new_type);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::set_srcset(ext::string new_srcset) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_source_element);
        return d->srcset = std::move(new_srcset);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::set_sizes(ext::string new_sizes) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_source_element);
        return d->sizes = std::move(new_sizes);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::set_media(ext::string new_media) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_source_element);
        return d->media = std::move(new_media);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::set_width(ext::number<ulong> new_width) -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_source_element);
        return d->width = new_width;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::set_height(ext::number<ulong> new_height) -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_source_element);
        return d->height = new_height;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_source_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_source_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .property("src", &html_source_element::get_src, &html_source_element::set_src)
        .property("type", &html_source_element::get_type, &html_source_element::set_src)
        .property("srcset", &html_source_element::get_srcset, &html_source_element::set_src)
        .property("sizes", &html_source_element::get_sizes, &html_source_element::set_src)
        .property("media", &html_source_element::get_media, &html_source_element::set_src)
        .property("width", &html_source_element::get_width, &html_source_element::set_src)
        .property("height", &html_source_element::get_height, &html_source_element::set_src)
        .auto_wrap_objects();
    
    return std::move(conversion);
}

