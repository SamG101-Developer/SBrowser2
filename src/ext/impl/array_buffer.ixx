module;
#include "ext/macros/namespaces.hpp"
#include <v8-forward.h>


export module ext.js:array_buffer;
import ext.core;


_EXT_BEGIN
    export struct array_buffer {using v8_constructor = v8::ArrayBuffer;};
    export struct array_buffer_view {using v8_constructor = v8::ArrayBufferView;};
    export struct data_view : array_buffer_view {using v8_constructor = v8::DataView;};
    export struct int8_array : array_buffer_view {using v8_constructor = v8::Int8Array;};
    export struct int16_array : array_buffer_view {using v8_constructor = v8::Int16Array;};
    export struct int32_array : array_buffer_view {using v8_constructor = v8::Int32Array;};
    export struct uint8_array : array_buffer_view {using v8_constructor = v8::Uint8Array;};
    export struct uint16_array : array_buffer_view {using v8_constructor = v8::Uint16Array;};
    export struct uint32_array : array_buffer_view {using v8_constructor = v8::Uint32Array;};
    export struct uint8_clamped_array : array_buffer_view {using v8_constructor = v8::Uint8ClampedArray;};
    export struct bigint64_array : array_buffer_view {using v8_constructor = v8::BigInt64Array;};
    export struct biguint64_array : array_buffer_view {using v8_constructor = v8::BigUint64Array;};
    export struct float32_array : array_buffer_view {using v8_constructor = v8::Float32Array;};
    export struct float64_array : array_buffer_view {using v8_constructor = v8::Float64Array;};
    export using buffer_source = _EXT variant<array_buffer, array_buffer_view>;
_EXT_END
