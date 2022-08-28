#include "animation_internals.hpp"

#include "css/css_animation_worklet/animation_worklet_global_scope.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/action/remove.hpp>


auto css::detail::is_stateful_animator(
        const detail::animator_definition_t& animator)
        -> ext::boolean
{
    return animator.stateful_flag;
}


auto css::detail::is_stateful_animator_instance(
        const detail::animator_instance_t& animator_instance)
        -> ext::boolean
{
    return animator_instance.animator_definition->stateful_flag;
}


auto css::detail::run_animators(
        css_animation_worklet::animation_worklet_global_scope* scope)
        -> void
{
    for (auto* animator: scope->m_animator_instance_set)
    {
        decltype(auto) animator_name = animator->animator_name;
        return_if (!scope->m_animator_definitions.contains(animator_name));
        return_if (!animator->frame_requested_flag /* TODO || ... */);
        decltype(auto) definition = scope->m_animator_definitions[std::move(animator_name)];

        definition->animate_function(animator->animator_current_time, animator->effect);
    }

    if (ranges::any_of(scope->m_animator_instance_set, [](animator_instance_t* instance) {return instance->sync_requested_flag;}))
        sync_local_times_to_document(scope);
}


auto css::detail::remove_animator_instance(
        const css::detail::animator_instance_t& animator_instance,
        css_animation_worklet::animation_worklet_global_scope* scope)
        -> void
{
    scope->m_animator_instance_set |= ranges::actions::remove(animator_instance);
}
