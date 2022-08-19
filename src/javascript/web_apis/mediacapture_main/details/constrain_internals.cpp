#include "constrain_internals.hpp"

#include "ext/threading.hpp"

#include "dom/detail/observer_internals.hpp"
#include "mediacapture_main/mixins/constrainable.hpp"
#include "mediacapture_main/other/overconstrained_error.hpp"

#include <range/v3/algorithm/permutation.hpp>
#include <range/v3/view/transform.hpp>


auto mediacapture::detail::apply_constrains_template_algorithm(
        main::mixins::constrainable* object,
        constraints_t&& new_constraints)
        -> std::promise<void>
{
    // create the promise object, and create a thread pool with 1 thread in (wil only need the 1 extra thread for this
    // method
    std::promise<void> promise;
    ext::thread_pool pool{1};

    // push the new task into the thread-pool, so that it is executed in a new thread; this is why only 1 thread is
    // needed, as this task will only be executed once. move the 'new_constraints' into the lambda, and mark the lambda
    // as mutable, because the moved 'new_constraints will be moved again into a nested lambda
    pool.template push_task([object, &promise, new_constraints = std::move(new_constraints)] mutable
    {
        // get the failed constraints and the successful settings objects
        auto failed_constraint = apply_constrains_algorithm(object);
        auto successful_settings = object->s_settings;

        // queue a microtask that handles setting the promise value
        dom::detail::queue_microtask(
                [object, &promise, failed_constraint = std::move(failed_constraint),
                        successful_settings = std::move(successful_settings),
                        new_constraints = std::move(new_constraints)] mutable
                {
                    // if there is a failed constraint, then set the exception in the promise to an
                    // OverconstrainedError, with the 'failed_constraint' as the given constraint
                    return_if (!failed_constraint.empty())
                        promise.set_exception(main::other::overconstrained_error{std::move(failed_constraint), "Constraint failed"});

                    // set the [[constraints]] and [[settings]] internal slots to the values captured in the lambda, and
                    // set the value of the promise (resolve it)
                    object->s_constraints = std::move(new_constraints);
                    object->s_settings = std::move(successful_settings);
                    promise.set_value();
                });
    });

    // return the promise
    return promise;
}


auto mediacapture::detail::apply_constrains_algorithm(
        main::mixins::constrainable* object,
        constraints_t&& new_constraints)
        -> ext::string
{
    auto successful_settings = select_settings(object, std::move(new_constraints));
    // TODO

    object->s_constraints = std::move(new_constraints);
    object->s_settings = std::move(successful_settings);
    return "";
}
