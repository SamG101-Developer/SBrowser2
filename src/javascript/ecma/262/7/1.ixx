module;
#include <v8-forward.h>


export module js.ecma._262._7._1;
import ext.assertion;

export namespace js::ecma
{
    enum ConversionHint {kDefault, kString, kNumber, kNone};
    /* [7.1.01.00] */ auto ToPrimitive(v8::Local<v8::Value> input, ConversionHint hint = kNone) -> v8::Local<v8::Value>;
    /* [7.1.01.01] */ auto OrdinaryToPrimitive(v8::Local<v8::Object> O, ConversionHint hint) -> v8::Local<v8::Value>;
    /* [7.1.02.00] */ auto ToBoolean(v8::Local<v8::Value> argument) -> v8::Local<v8::Boolean>;
    /* [7.1.03.00] */ auto ToNumeric(v8::Local<v8::Value> argument) -> v8::Local<v8::Primitive>;
    /* [7.1.04.00] */ auto ToNumber(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.04.01] */ auto StringToNumber(v8::Local<v8::String> string) -> v8::Local<v8::Number>;
    /* [7.1.04.02] */ auto StringNumericValue() -> v8::Local<v8::Number>;
    /* [7.1.04.03] */ auto RoundMVResult(v8::Local<v8::Number> n) -> v8::Local<v8::Number>;
    /* [7.1.05.00] */ auto ToIntegerOrInfinity(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.06.00] */ auto ToInt32(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.07.00] */ auto ToUint32(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.08.00] */ auto ToInt16(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.09.00] */ auto ToUint16(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.10.00] */ auto ToInt8(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.11.00] */ auto ToUint8(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.12.00] */ auto ToUint8Clamped(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.13.00] */ auto ToBigInt(v8::Local<v8::Value> argument) -> v8::Local<v8::BigInt>;
    /* [7.1.14.00] */ auto StringToBigInt(v8::Local<v8::String> string) -> v8::Local<v8::BigInt>;
    /* [7.1.15.00] */ auto ToBigInt64(v8::Local<v8::Value> argument) -> v8::Local<v8::BigInt>;
    /* [7.1.16.00] */ auto ToBigUint64(v8::Local<v8::Value> argument) -> v8::Local<v8::BigInt>;
    /* [7.1.17.00] */ auto ToString(v8::Local<v8::Value> argument) -> v8::Local<v8::String>;
    /* [7.1.18.00] */ auto ToObject(v8::Local<v8::Value> argument) -> v8::Local<v8::Object>;
    /* [7.1.19.00] */ auto ToPropertyKey(v8::Local<v8::Value> argument) -> v8::Local<v8::String>;
    /* [7.1.20.00] */ auto ToLength(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
    /* [7.1.21.00] */ auto ToCanonicalNumericIndexString(v8::Local<v8::Value> argument) -> v8::Local<v8::Value>;
    /* [7.1.22.00] */ auto ToIndex(v8::Local<v8::Value> argument) -> v8::Local<v8::Number>;
}
