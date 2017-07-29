#ifndef NODEJS_TF_SESSION_H
#define NODEJS_TF_SESSION_H

#include <nan.h>

#include <tensorflow/core/public/session.h>
#include <tensorflow/cc/framework/scope.h>

#include <tensorflow/cc/client/client_session.h>

#include "../framework/tensor.h"
#include "../framework/scope.h"

namespace nodejs_tf {

using v8::Local;
using v8::Object;
using v8::Value;

class Session: public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
  private:
    static NAN_METHOD(run);

    Session();
    ~Session();
    v8::Local<v8::Array> run(Session* self, Nan::NAN_METHOD_ARGS_TYPE info);
    tensorflow::ClientSession::FeedType get_feeds(v8::Local<v8::Object> obj);

    tensorflow::ClientSession* self;
    Scope* scope;
};

std::vector<tensorflow::Output> get_fetch_outputs(v8::Local<v8::Object> obj);

}

#endif
