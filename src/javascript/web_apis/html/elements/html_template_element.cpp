#include "html_template_element.hpp"
#include "html_template_element_private.hpp"



#include "dom/detail/node_internals.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/document_fragment_private.hpp"

#include "html/detail/document_internals.hpp"

#include <range/v3/view/transform.hpp>


html::elements::html_template_element::html_template_element()
{
    INIT_PIMPL(html_template_element);
    ACCESS_PIMPL(html_template_element);

    d->adopting_steps =
            [d]
            {
        decltype(auto) document = detail::appropriate_template_contents_owner_document(d->node_document.get());
        dom::detail::adopt(d->template_contents.get(), document); // TODO : ownership
            };

    d->cloning_steps =
            [d](dom::nodes::node* clone, dom::nodes::document* document, ext::boolean deep)
            {
        return_if (!deep);
        auto copied_contents = d->template_contents->d_func()->child_nodes
                | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
                | ranges::views::transform(BIND_BACK(dom::detail::clone<dom::nodes::document_fragment>, d->template_contents->d_func()->node_document.get(), true));

        ext::apply(ext::make_tuple(copied_contents), &dom_cast<html_template_element*>(clone)->d_func()->template_contents->append);};

    decltype(auto) document = detail::appropriate_template_contents_owner_document(d->node_document.get());
    d->template_contents = std::make_unique<dom::nodes::document_fragment>();
    d->template_contents->d_func()->node_document = document;
    d->template_contents->d_func()->host = this;

    HTML_CONSTRUCTOR;
}


auto html::elements::html_template_element::get_content() const -> dom::nodes::document_fragment*
{
    ACCESS_PIMPL(const html_template_element);
    return d->template_contents.get();
}
