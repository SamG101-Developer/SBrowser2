#ifndef SBROWSER2_ANNOTATIONS_HPP
#define SBROWSER2_ANNOTATIONS_HPP

#define JS_BLOCK_ENTER {
#define JS_BLOCK_EXIT }

#define JS_EXCEPTION_HANDLER v8::TryCatch _js_exception_handler{v8::Isolate::GetCurrent()}
#define JS_EXCEPTION_HAS_THROWN _js_exception_handler.HasCaught()
#define JS_EXCEPTION_MESSAGE _js_exception_handler.Message()->Get()
#define JS_EXCEPTION_RETHROW _js_exception_handler.ReThrow();

#endif //SBROWSER2_ANNOTATIONS_HPP
