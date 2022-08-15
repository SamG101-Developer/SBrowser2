#include "abstract_readable_stream_controller.hpp"


streams::readable::abstract_readable_stream_controller::abstract_readable_stream_controller()
{
    bind_get(desired_size);
}
