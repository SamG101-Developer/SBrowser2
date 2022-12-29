#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_TEXT_METRICS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_TEXT_METRICS_HPP


namespace html::canvasing {class text_metrics;}


class html::canvasing::text_metrics
        : virtual public dom_object
{
public constructors:
    DOM_CTORS(text_metrics);
    text_metrics() = default;

private js_properties:
    ext::property<ext::number<double>> width;
    ext::property<ext::number<double>> actual_bounding_box_left;
    ext::property<ext::number<double>> actual_bounding_box_right;
    
    ext::property<ext::number<double>> font_bounding_box_ascent;
    ext::property<ext::number<double>> font_bounding_box_descent;
    ext::property<ext::number<double>> actual_bounding_box_ascent;
    ext::property<ext::number<double>> actual_bounding_box_descent;
    ext::property<ext::number<double>> em_height_ascent;
    ext::property<ext::number<double>> em_height_descent;
    ext::property<ext::number<double>> hanging_baseline;
    ext::property<ext::number<double>> alphabetic_baseline;
    ext::property<ext::number<double>> ideographic_baseline;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_TEXT_METRICS_HPP
