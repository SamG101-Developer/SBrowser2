#include "text.hpp"

#include <web_apis/dom/detail/text_internals.hpp>

#include <QtWidgets/QVBoxLayout>


dom::nodes::text::text(
        ext::string_view new_data)
{
    bind_get(whole_text);
    bind_qt(data, m_rendered_widget, QLabel::setText);

    data = new_data;

    auto widget = QPointer<QLabel>{};
    widget->setLayout(new QVBoxLayout{});
    widget->hide();
    widget->setWordWrap(true);
    m_rendered_widget = widget;
}


auto dom::nodes::text::split_text(
        ext::number_view<ulong> offset)
        -> text*
{
    // split the text node at the index 'offset'
    return dom::detail::text_internals::split(this, offset);
}


auto dom::nodes::text::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<text>{isolate}
            .ctor<>()
            .ctor<ext::string_view>()
            .inherit<character_data>()
            .inherit<mixins::slottable<text>>()
            .function("splitText", &text::split_text)
            .var("wholeText", &text::whole_text, true)
            .auto_wrap_objects();
}
