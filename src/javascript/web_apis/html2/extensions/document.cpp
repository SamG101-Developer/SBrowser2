module apis.dom.document;


auto dom::document::get_location() const -> html::other::location*
{
    auto e = js::env::env::relevant(this);
    return detail::is_document_fully_active(this)
           ? e.cpp.global<dom::window*>()->d_func()->location.get()
           : nullptr;
}


auto dom::document::get_domain() const -> ext::string
{
    ACCESS_PIMPL(const document);
    decltype(auto) effective_domain = html::detail::effective_domain(*d->origin);
    return effective_domain.has_value() ? url::detail::url_serializer(*effective_domain) : u"";
}


auto dom::document::set_domain(ext::string new_domain) -> ext::string
{
    ACCESS_PIMPL(document);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [d] {return !d->browsing_context;},
            u8"Must have a browsing context");

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [d] {return d->active_sandboxing_set & html::detail::sandboxing_flag_set_t::DOCUMENT_DOMAIN;},
            u8"Sandboxing prevents domain from being set");

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [this] {return html::detail::allowed_to_use(this, u"document-domain");},
            u8"Document not allowed to use document-domain feature");

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [d] {return !html::detail::effective_domain(*d->origin).has_value();},
            u8"Document must have an effective domain");

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [d, &new_domain] {return !html::detail::is_registerable_domain_suffix_or_equal_to(new_domain, *html::detail::effective_domain(*d->origin));},
            u8"The new domain must be a registerable domain or equal to Document's origin");

    auto e = js::env::env::surrounding(this);
    return_if (false) u""; // TODO : Agent->AgentCluster->IsOriginKeyed()

    using namespace ext::literals;
    return d->origin->domain = std::move(new_domain);
}


auto dom::document::get_referrer() const -> ext::string_view
{
    ACCESS_PIMPL(const document);
    return d->referrer;
}


auto dom::document::get_cookie() const -> ext::string
{
    ACCESS_PIMPL(const document);
    using enum dom::detail::dom_exception_error_t;

    // if this Document is cookie averse, then it is not in the correct condition to return the value of the cookie, so
    // return the empty string instead.
    return_if (html::detail::is_cookie_averse_document(this)) u"";

    // if the origin of this Document is opaque, then throw a security error, because the security of the cookie cannot
    // be guaranteed, despite the Document not being cookie averse
    detail::throw_v8_exception<SECURITY_ERR>(
            [d] {return html::detail::is_opaque_origin(*d->origin);},
            u8"Can not get the cookie of a Document whose origin is opaque");

    // return the true value of the cookie
    return html::detail::cookie_string(*d->url, u8"non-HTTP", &encoding::detail::decode_without_bom);
}


auto dom::document::get_last_modified() const -> ext::string
{
    ACCESS_PIMPL(const document);

    // get the string epoch time (eg "1563566272"), and convert it to a 'long long' number type. convert this into a c++
    // time object with a strict format, push this into a stream, and finally return the string that the
    // std::stringstream holds.
    std::time_t decimal_time = std::stoll(*d->last_modified);
    auto formatted_time = ext::string_stream{} << std::put_time(std::localtime(&decimal_time), u"%m/%d/%Y %H:%M:%S");
    return formatted_time.str();
}


auto dom::document::get_ready_state() const -> html::detail::document_readiness_state_t
{
    ACCESS_PIMPL(const document);
    return d->current_readiness_state;
}



auto dom::document::get_title() const -> ext::string
{
    // the title element is either the first SVGTitleElement of the document element, if the document element is an
    // SvgElement. otherwise it is the first HTMLTitleElement of this document
    decltype(auto) title_element = dynamic_cast<svg::elements::svg_element*>(detail::document_element(this))
                                   ? ranges::front(detail::document_element(this)->d_func()->child_nodes
                                                   | ranges::views::transform(&std::unique_ptr<dom::node>::get)
                                                   | ranges::views::cast<svg::elements::svg_title_element*>)

                                   : ranges::front(detail::document_element(this)->d_func()->child_nodes
                                                   | ranges::views::transform(&std::unique_ptr<dom::node>::get)
                                                   | ranges::views::cast<html::detail::html_title_element*>);

    // the value of the xxxTitleElement is the child text content of it, with the ascii whitespace stripped and
    // collapsed from the string
    auto value = detail::child_text_content(title_element);
    return infra::detail::strip_and_collapse_ascii_whitespace(std::move(value));
}


auto dom::document::get_dir() const -> html::detail::directionality_t
{
    ACCESS_PIMPL(const document);

    // if the 'document_element' exists, and is a HTMLElement based object, then forward its 'dir' attribute value as
    // the Document's 'dir' attribute value, otherwise the empty string
    decltype(auto) html_document_element = d->html_element();
    return html_document_element ? html_document_element->d_func()->dir : html::detail::directionality_t::_;
}


auto dom::document::get_body() const -> html::elements::html_body_element*
{
    ACCESS_PIMPL(const document);

    // the body element is the first child of the HTMLHtmlElement that is a HTMLBodyElement; if there are no body
    // elements, then return nullptr - this is handled by returning a deference of the begin pointer
    return ranges::front(d->html_element->d_func()->child_nodes
                         | ranges::views::transform(&std::unique_ptr<dom::node>::get)
                         | ranges::views::cast<html::elements::html_body_element*>);
}


auto dom::document::get_head() const -> html::elements::html_head_element*
{
    ACCESS_PIMPL(const document);

    // the head element is  the first child of the HTMLHtmlElement that is a HTMLHeadElement; if there are no head
    // elements, then return nullptr - this is handled by returning a deference of the begin pointer
    return ranges::front(d->html_element->d_func()->child_nodes
                         | ranges::views::transform(&std::unique_ptr<dom::node>::get)
                         | ranges::views::cast<html::elements::html_head_element*>);
}


auto dom::document::get_images() const -> ranges::any_helpful_view<html::elements::html_image_element*>
{
    // the HTMLImageElements in this Document are all the HTMLImageElements that are descendants of this Document (live
    // collection)
    return detail::descendants(this) | ranges::views::cast<html::elements::html_image_element*>;
}


auto dom::document::get_links() const -> ranges::any_helpful_view<html::elements::html_element*>
{
    using enum ranges::filter_compare_t;

    // the HTMLLinkElements in this Document are all the HTMLLinkElements that are descendants of this Document (live
    // collection), and have their href attribute set
    decltype(auto) link_elements = detail::descendants(this)
                                   | ranges::views::cast<html::elements::html_link_element*>
                                   | ranges::views::filter_eq<NE>(html::elements::html_link_element_private::href, u"", ext::get_pimpl);

    decltype(auto) area_elements = detail::descendants(this)
                                   | ranges::views::cast<html::elements::html_area_element*>
                                   | ranges::views::filter_eq<NE>(html::elements::html_area_element_private::href, u"", ext::get_pimpl);

    return ranges::views::concat(link_elements, area_elements);
}


auto dom::document::get_forms() const -> ranges::any_helpful_view<html::elements::html_form_element*>
{
    // the HTMLFormElements in this Document are all the HTMLFormElements that are descendants of this Document (live
    // collection)
    return detail::descendants(this) | ranges::views::cast<html::elements::html_form_element*>;
}


auto dom::document::get_scripts() const -> ranges::any_helpful_view<html::elements::html_script_element*>
{
    // the HTMLScriptElements in this Document are all the HTMLScriptElements that are descendants of this Document
    // (live collection)
    return detail::descendants(this) | ranges::views::cast<html::elements::html_script_element*>();
}


auto dom::document::get_current_script() const -> html::detail::html_or_svg_image_element_t
{
    ACCESS_PIMPL(const document);
    return d->current_script;
}


auto dom::document::get_default_view() const -> window_proxy*
{
    ACCESS_PIMPL(const document);
    return_if (!d->browsing_context.get()) nullptr;
    return d->browsing_context->window_proxy;
}


auto dom::document::get_design_mode() const -> ext::boolean
{
    ACCESS_PIMPL(const document);
    return d->design_mode_enabled;
}


auto dom::document::set_cookie(ext::string new_cookie) -> ext::string
{
    ACCESS_PIMPL(document);
    using enum dom::detail::dom_exception_error_t;

    // if this Document is cookie averse, then it is not in the correct condition to return the value of the cookie, so
    // return the empty string instead.
    return_if (html::detail::is_cookie_averse_document(this)) u"";

    // if the origin of this Document is opaque, then throw a security error, because the security of the cookie cannot
    // be guaranteed, despite the Document not being cookie averse
    detail::throw_v8_exception<SECURITY_ERR>(
            [d] {return html::detail::is_opaque_origin(*d->origin);},
            u8"Can not get the cookie of a Document whose origin is opaque");

    // set the true value of the cookie t the new cookie value passed in as a parameter
    return html::detail::receive_set_cookie_string(this, std::move(new_cookie), &encoding::detail::utf8_encode);
}


// auto dom::document::set_ready_state(
//         const ext::string& val)
//         -> void
// {
//     guard_property(ready_state);
//     *ready_state = val;
//
//     if (/* TODO : HTML parser association */ false)
//     {
//         JS_REALM_GET_RELEVANT(this);
//         auto now = hr_time::detail::current_hr_time(this_relevant_global_object);
//         if (val == "complete" && m_load_timing_info->dom_complete_time == 0)
//             m_load_timing_info->dom_complete_time = now;
//
//         if (val == "interactive" && m_load_timing_info->dom_interactive_time == 0)
//             m_load_timing_info->dom_interactive_time = now;
//     }
//
//     detail::fire_event("readystatechange", this);
// }


auto dom::document::set_title(ext::string new_title) -> ext::string
{
    ACCESS_PIMPL(document);
    decltype(auto) document_element = detail::document_element(this);

    // if the document element is an SvgTitleElement, handle the title updating steps for the SVG namespace
    if (dynamic_cast<svg::elements::svg_element*>(document_element))
    {
        // set the 'title_element' to the first child of the 'document_element's child node that is an SvgTitleElement;
        // if there is no such element, then create the element, and insert it as the first child of the
        // 'document_element' (call insert not pre_insert, because the newly created 'title_element' can't be the first
        // child when it has just been created)
        decltype(auto) title_element = ranges::front(document_element->d_func()->child_nodes
                                                     | ranges::views::transform(&std::unique_ptr<dom::node>::get)
                                                     | ranges::views::cast<svg::elements::svg_title_element*>);

        if (!title_element)
        {
            detail::insert(
                    detail::create_an_element(document_element->d_func()->node_document.get(), u"title", detail::SVG),
                    detail::document_element(this), document_element->d_func()->child_nodes.front().get());
            title_element = document_element->d_func()->child_nodes.front().get();
        }

        // replace all the text in the SvgTitleElement with the new title value 'val' parameter
        detail::string_replace_all(std::move(new_title), title_element);
    }

    else if (document_element->d_func()->namespace_uri == detail::HTML)
    {
        return_if(!d->title() && ! d->head()) u"";
        decltype(auto) title_element = d->title();

        if (!title_element)
        {
            detail::append(
                    detail::create_an_element(document_element->d_func()->node_document, u"title", detail::HTML),
                    d->head());
        }

        // replace all the text in the HtmlTitleElement with the new title value 'val' parameter
        detail::string_replace_all(std::move(new_title), title_element);
    }

    return u"";
}


auto dom::document::set_dir(html::detail::directionality_t new_dir) -> html::detail::directionality_t
{
    ACCESS_PIMPL(document);

    decltype(auto) html_document_element = d->html_element();
    return html_document_element ? html_document_element->d_func()->dir = std::move(new_dir) : html::detail::directionality_t::_;
}


auto dom::document::set_body(html::elements::html_body_element* new_body) -> html::elements::html_body_element*
{
    ACCESS_PIMPL(document);
    using enum dom::detail::dom_exception_error_t;

    // don't do anything id the new body value is the same as the current body, ie the first HTMLBodyElement of the
    // HTMLHtmlElement in this Document
    return_if (d->body_element() == new_body) new_body;

    // if there is a current HTMLBodyElement (and an implied 'document_element'), then replace it with the new
    // HTMLBodyElement
    if (new_body)
        return detail::replace(d->body_element(), d->body_element()->d_func()->parent_node.get(), new_body);

    // if there is no implied HTMLBodyElement, and no 'document_element', throw a hierarchy request error, because it's
    // not possible to append the HTMLBodyElement to a non-existent 'document_element'
    detail::throw_v8_exception<HIERARCHY_REQUEST_ERR>(
            [this] {return !detail::document_element(this);},
            u8"Document must have a document element, if a new HTMLBodyElement is being added to the Document");

    // append the HTMLBodyElement to this Document's 'document_element'
    detail::append(new_body, detail::document_element(this));
}


auto dom::document::set_design_mode(ext::boolean new_design_mode) -> ext::boolean
{
    ACCESS_PIMPL(document);

    if (new_design_mode && !d->design_mode_enabled)
    {
        d->design_mode_enabled = true;
        d->active_range->d_func()->start->node = this; // TODO : offset?
        d->active_range->d_func()->end->node = this; // TODO : offset?
        detail::focusing_steps(d->document_element());
    }
    else if (!new_design_mode)
        d->design_mode_enabled = false;
}
