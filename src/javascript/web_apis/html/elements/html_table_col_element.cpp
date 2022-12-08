#include "html_table_col_element.hpp"
#include "html_table_col_element_private.hpp"




auto html::elements::html_table_col_element::get_span() const -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_table_col_element);
        return d->span;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_col_element::set_span(ext::number<ulong> new_span) -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_table_col_element);
        return d->span = new_span;
    CE_REACTIONS_METHOD_EXE
}
