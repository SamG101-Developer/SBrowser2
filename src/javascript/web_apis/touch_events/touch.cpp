#include "touch.hpp"


touch_events::touch::touch(
        ext::map<ext::string, ext::any>&& options)
        : SET_PROPERTY_FROM_OPTIONS(options, identifier, "")
        , SET_PROPERTY_FROM_OPTIONS(options, target, nullptr)
        , SET_PROPERTY_FROM_OPTIONS(options, screen_x, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(options, screen_y, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(options, client_x, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(options, client_y, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(options, page_x, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(options, page_y, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(options, radius_x, 0.0f)
        , SET_PROPERTY_FROM_OPTIONS(options, radius_y, 0.0f)
        , SET_PROPERTY_FROM_OPTIONS(options, rotation_angle, 0.0f)
        , SET_PROPERTY_FROM_OPTIONS(options, force, 0.0f)
        , SET_PROPERTY_FROM_OPTIONS(options, altitude_angle, 0.0f)
        , SET_PROPERTY_FROM_OPTIONS(options, azimuth_angle, 0.0f)
        , SET_PROPERTY_FROM_OPTIONS(options, touch_type, detail::touch_type_t::DIRECT)
{}
