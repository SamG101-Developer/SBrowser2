module;
#include <v8-forward.h>


export module js.ecma._262._7._3;

export namespace js::ecma
{
    /* 7.3.02 */ auto Get(v8::Local<v8::Object> O, v8::Local<v8::Value> P) -> v8::Local<v8::Value>;
    /* 7.3.03 */ auto GetV(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>;
    /* 7.3.05 */ auto CreateDataProperty(v8::Local<v8::Object> O, v8::Local<v8::String> P, v8::Local<v8::Value> V);
    /* 7.3.11 */ auto GetMethod(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>;
    /* 7.3.14 */ template <typename ...Args> auto Call(v8::Local<v8::Value> F, v8::Local<v8::Value> V, Args&&... arguments) -> v8::Local<v8::Value>;
}
