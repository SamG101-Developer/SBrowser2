module apis.file_api.detail;



auto file_api::detail::get_stream(
        file_api::blob* blob_object)
        -> streams::readable::readable_stream
{
    streams::readable::readable_stream stream;
    streams::detail::setup(&stream);
    // TODO
}


auto file_api::detail::process_blob_parts(
        ext::vector<detail::blob_part_t>&& parts,
        ext::map<ext::string, ext::any>&& options)
        -> ext::string
{
    ext::string bytes;

    for (decltype(auto) element: parts)
    {
        if (ext::holds_alternative<ext::string>(element))
        {
            decltype(auto) string = ext::get<ext::string>(element);
            if (options[u"endings"].to<endings_t>() == endings_t::NATIVE)
                string = convert_line_endings_to_native(string);
            bytes += string;
        }

        else if (ext::holds_alternative<ext::array_buffer>(element))
        {
            auto e = js::env::env::current();
            decltype(auto) buffer = ext::get<ext::array_buffer>(element);
            bytes += web_idl::detail::get_copy_of_bytes_in_buffer_source(buffer, e.js.realm());
        }

        else if (ext::holds_alternative<blob*>(element))
        {
            decltype(auto) buffer = ext::get<blob*>(element);
            bytes += buffer->d_func()->byte_sequence();
        }
    }

    return bytes;
}


auto file_api::detail::convert_line_endings_to_native(
        ext::string_view input)
        -> ext::string
{
    auto string = ext::string{input};
    auto native_line_ending = char(0x000a); // TODO

    decltype(auto) position = string.begin();
    auto result = infra::detail::collect_code_points_not_matching(string, position, char(0x000a), char(0x000d));

    while (position != string.end())
    {
        if (*position == 0x000d)
        {
            result += native_line_ending;
            ranges::advance(position, 1);
            ranges::advance(position, position != string.end() && *position == 0x000a);
        }

        else if (*position == 0x000a)
        {
            result += native_line_ending;
            ranges::advance(position, 1);
        }

        result += infra::detail::collect_code_points_not_matching(string, position, char(0x000a), char(0x000d));
    }

    return result;
}


auto file_api::detail::read_operation(
        file_reader* file_reader,
        blob* blob,
        ext::string_view optional_encoding_name)
-> ext::promise<ext::string>
{
    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [file_reader] {return file_reader->ready_state() == file_reader->LOADING;},
            "File is already loading");

    file_reader->ready_state = file_reader->LOADING;
    file_reader->result = "";
    file_reader->error = nullptr;

    auto stream = get_stream(blob);
    auto reader = streams::detail::get_reader(&stream);
    auto chunk_promise = streams::detail::read_chunk(&stream, &reader);
    auto is_first_chunk = ext::boolean::TRUE_();

    GO [file_reader, &is_first_chunk]
    {
        while (true)
        {
            while (!chunk_promise.is_resolved() || chunk_promise.is_rejected) continue;
            if (is_first_chunk && chunk_promise.is_resolved)
                dom::detail::queue_task(
                        html::detail::file_reading_task_source,
                        ext::bind_front{fire_progress_event, "loadstart", file_reader});

            is_first_chunk = false;
            // TODO : streams API needs finishing first
        }
    };
}

