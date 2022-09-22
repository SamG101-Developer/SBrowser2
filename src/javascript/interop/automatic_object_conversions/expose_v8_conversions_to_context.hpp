#ifndef SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP
#define SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP

#include <memory>

#include "javascript/environment/environment_module.hpp"
#include "javascript/environment/realms_2.hpp"

#include "javascript/interop/manual_primitive_conversions/convert_any.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_boolean.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_map.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_map_like.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_number.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_optional.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_property.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_set.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_vector.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_vector_like.hpp"

#include "accelerometer/accelerometer.hpp"
#include "accelerometer/gravity_sensor.hpp"
#include "accelerometer/linear_accelerometer.hpp"

#include "ambient_light/ambient_light_sensor.hpp"
#include "background_tasks/idle_deadline.hpp"
#include "battery/battery_manager.hpp"

#include "contact_picker/contact_address.hpp"
#include "contact_picker/contacts_manager.hpp"

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-persistent-handle.h>
#include <v8-primitive.h>

#include <v8pp/class.hpp>
#include <v8pp/module.hpp>

#define EXPOSE_CLASS_TO_MODULE(javascript_class_name, cpp_class_name) \
    auto v8_##javascript_class_name = cpp_class_name::to_v8(isolate); \
    v8_module.class_(#javascript_class_name, v8_##javascript_class_name)

namespace javascript::interop {auto expose(v8::Isolate* isolate, environment::module_t module_type) -> v8::Persistent<v8::Context>&;}


inline auto javascript::interop::expose(
        v8::Isolate* isolate,
        environment::module_t module_type)
        -> v8::Persistent<v8::Context>&
{
    // create the context objects and create a module for the classes ie the Window module
    v8pp::module v8_module{isolate};
    auto local_context = v8::Context::New(isolate);
    auto static persistent_context = v8::Persistent<v8::Context>{isolate, local_context};
    local_context->Enter();

    // different classes are exposed to different modules, and assign the module name TODO : secure contexts
    switch (module_type)
    {
        case (environment::module_t::WINDOW):
        {
            /* [ACCELEROMETER] */
            EXPOSE_CLASS_TO_MODULE(Accelerometer, accelerometer::accelerometer);
            EXPOSE_CLASS_TO_MODULE(GravitySensor, accelerometer::gravity_sensor);
            EXPOSE_CLASS_TO_MODULE(LinearAccelerometer, accelerometer::linear_accelerometer);

            /* [AMBIENT_LIGHT] */
            EXPOSE_CLASS_TO_MODULE(AmbientLight, ambient_light_sensor::ambient_light_sensor);

            /* [BACKGROUND_TASKS] */
            EXPOSE_CLASS_TO_MODULE(IdleDeadline, background_tasks::idle_deadline);

            /* [BATTERY_MANAGER] */
            EXPOSE_CLASS_TO_MODULE(BatteryManager, battery::battery_manager);

            /* [CONTACT_PICKER] */
            EXPOSE_CLASS_TO_MODULE(ContactAddress, contact_picker::contact_address);
            EXPOSE_CLASS_TO_MODULE(ContactsManager, contact_picker::contacts_manager);
        }

        case (environment::module_t::WORKER):
        {
        }

        case (environment::module_t::WORKLET):
        {
        }
    }

    return persistent_context;
}

#endif //SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP
