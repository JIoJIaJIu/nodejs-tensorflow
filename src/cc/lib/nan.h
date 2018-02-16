#ifndef NODEJS_TF_NAN_H
#define NODEJS_TF_NAN_H

#include <nan.h>

#define NAN_CONSTRUCTOR(c) Nan::Persistent<v8::FunctionTemplate> c
#define NAN_NEW(n) void n(const Nan::FunctionCallbackInfo<v8::Value>& info)

#endif // NODEJS_TF_NAN_H
