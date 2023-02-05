#ifndef SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP
#define SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP

#include <memory>

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-persistent-handle.h>
#include <v8-primitive.h>

#include <v8pp/class.hpp>
#include <v8pp/module.hpp>


#define EXPOSE_CLASS_TO_MODULE(javascript_class_name, cpp_class_name)                 \
    auto v8_ ## javascript_class_name = cpp_class_name::_to_v8(module_type, isolate); \
    if (v8_ ## javascript_class_name[0_tag])                                          \
        v8_module.class_(#javascript_class_name, v8_ ## javascript_class_name[1_tag])

namespace js::interop {auto expose(v8::Isolate* isolate, env::module_t module_type) -> v8::Persistent<v8::Context>&;}


inline auto js::interop::expose(
        v8::Isolate* isolate,
        env::module_t module_type)
        -> v8::Persistent<v8::Context>&
{
    // create the context objects and create a module for the classes ie the Window module
    v8pp::module v8_module{isolate};
    auto local_context = v8::Context::New(isolate);
    auto static persistent_context = v8::Persistent<v8::Context>{isolate, local_context};
    local_context->Enter();

    using namespace ext::literals;

    // different classes are exposed to different modules, and assign the module name TODO : secure contexts
    /* [ACCELEROMETER] */
    EXPOSE_CLASS_TO_MODULE(Accelerometer, accelerometer::accelerometer);
    EXPOSE_CLASS_TO_MODULE(GravitySensor, accelerometer::gravity_sensor);
    EXPOSE_CLASS_TO_MODULE(LinearAccelerometer, accelerometer::linear_accelerometer);

    /* [AMBIENT-LIGHT] */
    EXPOSE_CLASS_TO_MODULE(AmbientLight, ambient_light_sensor::ambient_light_sensor);

    /* [BACKGROUND-TASKS] */
    EXPOSE_CLASS_TO_MODULE(IdleDeadline, background_tasks::idle_deadline);

    /* [BATTERY-MANAGER] */
    EXPOSE_CLASS_TO_MODULE(BatteryManager, battery::battery_manager);

    /* [CONSOLE] */
    // TODO : Use Console as a pre-built object

    /* [CONTACT-PICKER] */
    EXPOSE_CLASS_TO_MODULE(ContactAddress, contact_picker::contact_address);
    EXPOSE_CLASS_TO_MODULE(ContactsManager, contact_picker::contacts_manager);

    /* [DEVICE-ORIENTATION] */
    EXPOSE_CLASS_TO_MODULE(DeviceOrientationEvent, device_orientation::device_orientation_event);

    /* [DEVICE-POSTURE] */
    EXPOSE_CLASS_TO_MODULE(DevicePosture, device_posture::device_posture);

    /* [DOM] */
    EXPOSE_CLASS_TO_MODULE(AbortSignal, dom::abort::abort_signal);
    EXPOSE_CLASS_TO_MODULE(AbortController, dom::abort::abort_controller);
    EXPOSE_CLASS_TO_MODULE(Event, dom::events::event);
    EXPOSE_CLASS_TO_MODULE(CustomEvent, dom::events::custom_event);
    EXPOSE_CLASS_TO_MODULE(NodeFilter, dom::node_iterators::node_filter);
    EXPOSE_CLASS_TO_MODULE(NodeIterator, dom::node_iterators::node_iterator);
    EXPOSE_CLASS_TO_MODULE(TreeWalker, dom::node_iterators::tree_walker);
    EXPOSE_CLASS_TO_MODULE(MutationObserver, dom::mutations::mutation_observer);
    EXPOSE_CLASS_TO_MODULE(MutationRecord, dom::mutations::mutation_record);
    EXPOSE_CLASS_TO_MODULE(Attr, dom::nodes::attr);
    EXPOSE_CLASS_TO_MODULE(CDataSection, dom::nodes::attr);
    EXPOSE_CLASS_TO_MODULE(CharacterData, dom::nodes::character_data);
    EXPOSE_CLASS_TO_MODULE(Comment, dom::nodes::cdata_section);
    EXPOSE_CLASS_TO_MODULE(Document, dom::nodes::document);
    EXPOSE_CLASS_TO_MODULE(DocumentFragment, dom::nodes::document_fragment);
    EXPOSE_CLASS_TO_MODULE(DocumentType, dom::nodes::document_type);
    EXPOSE_CLASS_TO_MODULE(Element, dom::nodes::element);
    EXPOSE_CLASS_TO_MODULE(EventTarget, dom::nodes::event_target);
    EXPOSE_CLASS_TO_MODULE(Node, dom::nodes::node);
    EXPOSE_CLASS_TO_MODULE(ProcessingInstruction, dom::nodes::processing_instruction);
    EXPOSE_CLASS_TO_MODULE(ShadowRoot, dom::nodes::shadow_root);
    EXPOSE_CLASS_TO_MODULE(Text, dom::nodes::text);
    EXPOSE_CLASS_TO_MODULE(Window, dom::nodes::window);
    EXPOSE_CLASS_TO_MODULE(WindowProxy, dom::nodes::window_proxy);
    EXPOSE_CLASS_TO_MODULE(XMLDocument, dom::nodes::xml_document);
    EXPOSE_CLASS_TO_MODULE(DOMException, dom::other::dom_exception);
    EXPOSE_CLASS_TO_MODULE(DOMImplementation, dom::other::dom_implementation);
    EXPOSE_CLASS_TO_MODULE(AbstractRange, dom::node_ranges::abstract_range);
    EXPOSE_CLASS_TO_MODULE(StaticRange, dom::node_ranges::static_range);
    EXPOSE_CLASS_TO_MODULE(Range, dom::node_ranges::range);
    // TODO : XPATH, XSLT

    /* [EDIT-CONTEXT] */
    EXPOSE_CLASS_TO_MODULE(EditContext, edit_context::edit_context);
    EXPOSE_CLASS_TO_MODULE(TextFormat, edit_context::text_format);
    EXPOSE_CLASS_TO_MODULE(CharacterBoundsUpdateEvent, edit_context::events::character_bounds_update_event);
    EXPOSE_CLASS_TO_MODULE(TextFormatUpdateEvent, edit_context::events::text_format_update_event);
    EXPOSE_CLASS_TO_MODULE(TextUpdateEvent, edit_context::events::text_update_event);

    /* [ENCODING] */
    EXPOSE_CLASS_TO_MODULE(TextDecoder, encoding::text_decoder);
    EXPOSE_CLASS_TO_MODULE(TextDecoderStream, encoding::text_decoder_stream);
    EXPOSE_CLASS_TO_MODULE(TextEncoder, encoding::text_encoder);
    EXPOSE_CLASS_TO_MODULE(TextEncoderStream, encoding::text_encoder_stream);

    /* [EVENT-TIMING] */
    EXPOSE_CLASS_TO_MODULE(EventCounts, event_timing::event_counts);
    EXPOSE_CLASS_TO_MODULE(InteractionCounts, event_timing::interaction_counts);
    EXPOSE_CLASS_TO_MODULE(PerformanceEventTiming, event_timing::performance_event_timing);

    /* [FETCH] */
    EXPOSE_CLASS_TO_MODULE(Headers, fetch::headers);
    EXPOSE_CLASS_TO_MODULE(Request, fetch::request);
    EXPOSE_CLASS_TO_MODULE(Response, fetch::response);

    /* [FILE-API] */
    EXPOSE_CLASS_TO_MODULE(Blob, file_api::blob);
    EXPOSE_CLASS_TO_MODULE(File, file_api::file);
    EXPOSE_CLASS_TO_MODULE(FileReader, file_api::file_reader);
    EXPOSE_CLASS_TO_MODULE(FileReaderSync, file_api::file_reader_sync);

    // Register the module as the global object so that all the objects are accessible in the global naemspace, not
    // window.EventTarget for example. TODO : Check if this works.
    local_context->Global()->SetPrototype(local_context, v8_module.new_instance());

    return persistent_context;
}

#endif //SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP
