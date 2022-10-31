#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_DETAIL_CONSTRUCTION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_DETAIL_CONSTRUCTION_INTERNALS_HPP

#include "ext/keywords.hpp"
#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)
namespace html::elements {class html_anchor_element;}
namespace html::elements {class html_html_element;}
namespace html::elements {class html_area_element;}
namespace html::elements {class html_audio_element;}
namespace html::elements {class html_base_element;}
namespace html::elements {class html_quote_element;}
namespace html::elements {class html_body_element;}
namespace html::elements {class html_br_element;}
namespace html::elements {class html_button_element;}
namespace html::elements {class html_canvas_element;}
namespace html::elements {class html_table_caption_element;}
namespace html::elements {class html_table_col_element;}
namespace html::elements {class html_data_element;}
namespace html::elements {class html_data_list_element;}
namespace html::elements {class html_mod_element;}
namespace html::elements {class html_details_element;}
namespace html::elements {class html_dialog_element;}
namespace html::elements {class html_div_element;}
namespace html::elements {class html_dlist_element;}
namespace html::elements {class html_embed_element;}
namespace html::elements {class html_field_set_element;}
namespace html::elements {class html_form_element;}
namespace html::elements {class html_heading_element;}
namespace html::elements {class html_head_element;}
namespace html::elements {class html_hr_element;}
namespace html::elements {class html_html_element;}
namespace html::elements {class html_iframe_element;}
namespace html::elements {class html_image_element;}
namespace html::elements {class html_input_element;}
namespace html::elements {class html_label_element;}
namespace html::elements {class html_legend_element;}
namespace html::elements {class html_li_element;}
namespace html::elements {class html_link_element;}
namespace html::elements {class html_map_element;}
namespace html::elements {class html_element;}
namespace html::elements {class html_menu_element;}
namespace html::elements {class html_meta_element;}
namespace html::elements {class html_meter_element;}
namespace html::elements {class html_object_element;}
namespace html::elements {class html_olist_element;}
namespace html::elements {class html_opt_group_element;}
namespace html::elements {class html_option_element;}
namespace html::elements {class html_output_element;}
namespace html::elements {class html_paragraph_element;}
namespace html::elements {class html_picture_element;}
namespace html::elements {class html_pre_element;}
namespace html::elements {class html_progress_element;}
namespace html::elements {class html_script_element;}
namespace html::elements {class html_select_element;}
namespace html::elements {class html_slot_element;}
namespace html::elements {class html_source_element;}
namespace html::elements {class html_span_element;}
namespace html::elements {class html_style_element;}
namespace html::elements {class html_table_element;}
namespace html::elements {class html_table_section_element;}
namespace html::elements {class html_table_cell_element;}
namespace html::elements {class html_template_element;}
namespace html::elements {class html_text_area_element;}
namespace html::elements {class html_time_element;}
namespace html::elements {class html_title_element;}
namespace html::elements {class html_table_row_element;}
namespace html::elements {class html_track_element;}
namespace html::elements {class html_ulist_element;}
namespace html::elements {class html_video_element;}


template <html::detail::local_name_t T>
struct dom::detail::element_interface
{using type = void;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::A>
{using type = html::elements::html_anchor_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::ABBR>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::ADDRESS>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::AREA>
{using type = html::elements::html_area_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::ARTICLE>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::ASIDE>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::AUDIO>
{using type = html::elements::html_audio_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::B>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::BASE>
{using type = html::elements::html_base_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::BDI>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::BDO>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::BLOCKQUOTE>
{using type = html::elements::html_quote_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::BODY>
{using type = html::elements::html_body_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::BR>
{using type = html::elements::html_br_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::BUTTON>
{using type = html::elements::html_button_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::CANVAS>
{using type = html::elements::html_canvas_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::CAPTION>
{using type = html::elements::html_table_caption_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::CITE>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::CODE>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::COL>
{using type = html::elements::html_table_col_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::COLGROUP>
{using type = html::elements::html_table_col_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DATA>
{using type = html::elements::html_data_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DATALIST>
{using type = html::elements::html_data_list_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DD>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DEL>
{using type = html::elements::html_mod_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DETAILS>
{using type = html::elements::html_details_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DFN>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DIALOG>
{using type = html::elements::html_dialog_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DIV>
{using type = html::elements::html_div_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DL>
{using type = html::elements::html_dlist_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::DT>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::EM>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::EMBED>
{using type = html::elements::html_embed_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::FIELDSET>
{using type = html::elements::html_field_set_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::FIGCAPTION>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::FIGURE>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::FOOTER>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::FORM>
{using type = html::elements::html_form_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::H1>
{using type = html::elements::html_heading_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::H2>
{using type = html::elements::html_heading_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::H3>
{using type = html::elements::html_heading_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::H4>
{using type = html::elements::html_heading_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::H5>
{using type = html::elements::html_heading_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::H6>
{using type = html::elements::html_heading_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::HEAD>
{using type = html::elements::html_head_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::HEADER>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::HGROUP>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::HR>
{using type = html::elements::html_hr_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::HTML>
{using type = html::elements::html_html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::I>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::IFRAME>
{using type = html::elements::html_iframe_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::IMG>
{using type = html::elements::html_image_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::INPUT>
{using type = html::elements::html_input_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::INS>
{using type = html::elements::html_mod_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::KBD>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::LABEL>
{using type = html::elements::html_label_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::LEGEND>
{using type = html::elements::html_legend_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::LI>
{using type = html::elements::html_li_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::LINK>
{using type = html::elements::html_link_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::MAIN>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::MAP>
{using type = html::elements::html_map_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::MARK>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::MENU>
{using type = html::elements::html_menu_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::META>
{using type = html::elements::html_meta_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::METER>
{using type = html::elements::html_meter_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::NAV>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::NOSCRIPT>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::OBJECT>
{using type = html::elements::html_object_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::OL>
{using type = html::elements::html_olist_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::OPTGROUP>
{using type = html::elements::html_opt_group_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::OPTION>
{using type = html::elements::html_option_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::OUTPUT>
{using type = html::elements::html_output_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::P>
{using type = html::elements::html_paragraph_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::PICTURE>
{using type = html::elements::html_picture_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::PRE>
{using type = html::elements::html_pre_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::PROGRESS>
{using type = html::elements::html_progress_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::Q>
{using type = html::elements::html_quote_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::RP>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::RT>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::RUBY>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::S>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SAMP>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SCRIPT>
{using type = html::elements::html_script_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SECTION>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SELECT>
{using type = html::elements::html_select_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SLOT>
{using type = html::elements::html_slot_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SMALL>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SOURCE>
{using type = html::elements::html_source_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SPAN>
{using type = html::elements::html_span_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::STRONG>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::STYLE>
{using type = html::elements::html_style_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SUB>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SUMMARY>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::SUP>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TABLE>
{using type = html::elements::html_table_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TBODY>
{using type = html::elements::html_table_section_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TD>
{using type = html::elements::html_table_cell_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TEMPLATE>
{using type = html::elements::html_template_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TEXTAREA>
{using type = html::elements::html_text_area_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TFOOT>
{using type = html::elements::html_table_section_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TH>
{using type = html::elements::html_table_cell_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::THEAD>
{using type = html::elements::html_table_section_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TIME>
{using type = html::elements::html_time_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TITLE>
{using type = html::elements::html_title_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TR>
{using type = html::elements::html_table_row_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::TRACK>
{using type = html::elements::html_track_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::U>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::UL>
{using type = html::elements::html_ulist_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::VAR>
{using type = html::elements::html_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::VIDEO>
{using type = html::elements::html_video_element;};


template <>
struct dom::detail::element_interface<html::detail::local_name_t::WBR>
{using type = html::elements::html_element;};


namespace dom::detail
{
    template <html::detail::local_name_t T>
    using element_interface_t = typename element_interface<T>::type;
}



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_DETAIL_CONSTRUCTION_INTERNALS_HPP
