#include "animation_worklet_global_scope.hpp"

#include "javascript/environment/realms_2.hpp"

#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(css/css_animation_worklet)

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/document.hpp"

#include "css/css_animation_worklet/detail/animation_internals.hpp"

#include "html/detail/task_internals.hpp"

#include <v8-function.h>
#include <v8-object.h>
#include <v8pp/convert.hpp>


css::css_animation_worklet::animation_worklet_global_scope::animation_worklet_global_scope()
        : INIT_PIMPL
{}


auto css::css_animation_worklet::animation_worklet_global_scope::register_animator(
        ext::string&& name,
        detail::animator_instance_constructor_t&& animator)
        -> void
{
    JS_REALM_GET_CURRENT;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [name = std::move(name)] {return false /* TODO */;},
            "Name must be '<indent>'");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this, &name] mutable {return m_animator_definitions.contains(name);},
            "Name must not already exist");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&animator, current_agent] mutable {return !v8pp::to_v8(current_agent, animator)->IsConstructor();},
            "Animator must be a constructor");

    JS_BLOCK_ENTER
        auto constructor = v8pp::to_v8(v8::Isolate::GetCurrent(), animator);
        auto prototype = constructor->GetPrototype();
        JS_EXCEPTION_HANDLER;

        auto animate_func_value = prototype.As<v8::Object>()->Get(current_realm, v8pp::to_v8(current_agent, "animate")).ToLocalChecked();
        auto animate_func = animate_func_value.As<v8::Function>();
        if (JS_EXCEPTION_HAS_THROWN) {JS_EXCEPTION_RETHROW; return;}

        auto state_func_value = prototype.As<v8::Object>()->Get(current_realm, v8pp::to_v8(current_agent, "state")).ToLocalChecked();
        auto state_func = state_func_value.As<v8::Function>();
        auto stateful = ext::boolean::TRUE_();
        if (JS_EXCEPTION_HAS_NOT_THROWN)
        {
            state_func = v8::Function::New(current_realm);
            stateful = false;
        }

        detail::animator_definition_t definition
        {
            .name = name,
            .class_constructor = animator,
            .animate_function = v8pp::from_v8<ext::function<void()>>(current_agent, animate_func_value),
            .state_function = v8pp::from_v8<ext::function<void()>>(current_agent, state_func_value),
            .stateful_flag = stateful
        };

        m_animator_definitions.emplace(std::move(name), std::move(definition));

        dom::detail::queue_task(html::detail::dom_manipulation_task_source,
                [current_global_object, &stateful, name = std::move(name)]
                {
                    decltype(auto) associated_document = javascript::environment::realms_2::get<dom::nodes::document*>(current_global_object, "$AssociatedDocument");
                    detail::document_animator_definition_t document_definition {.stateful_flag = stateful};

                    if (associated_document->m_document_animator_definitions().contains(name))
                    {
                        auto existing_document_definition = associated_document->m_document_animator_definitions()[std::move(name)];
                        return_if (existing_document_definition.invalid);

                        if (existing_document_definition.stateful_flag != document_definition.stateful_flag)
                            associated_document->m_document_animator_definitions()[std::move(name)].invalid = true; // TODO : log an error
                    }

                    else
                    {
                        associated_document->m_document_animator_definitions()[std::move(name)] = std::move(document_definition);
                    }
                }
                );
    JS_BLOCK_EXIT
}
