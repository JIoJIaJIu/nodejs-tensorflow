#include <iostream>

#include "session.h"

//TODO
#include <tensorflow/cc/framework/scope.h>
#include <tensorflow/core/graph/node_builder.h>
//TODO: hack
#include <tensorflow/cc/ops/const_op.h>

namespace nodejs_tf {


using v8::Array;
using v8::Handle;
using v8::Local;
using v8::Object;
using v8::Value;

NAN_MODULE_INIT(Session::Init) {
  auto fn = Nan::New<v8::FunctionTemplate>(Session::New);
  auto fn_name = Nan::New("Session").ToLocalChecked();

  fn->InstanceTemplate()->SetInternalFieldCount(1);
  fn->SetClassName(fn_name);

  Nan::SetPrototypeMethod(fn, "run", run);

  Nan::Set(target, fn_name, fn->GetFunction());
}

NAN_METHOD(Session::New) {
  printf("cc: Session::New\n");

  Session *session = new Session();
  session->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

Session::Session() {
  tensorflow::SessionOptions options;

  scope = new Scope();
}

Session::~Session() {
}

NAN_METHOD(Session::run) {
  printf("cc: Session::run\n");
  Session* session = Nan::ObjectWrap::Unwrap<Session>(info.Holder());

  auto results = session->run(session, info);
  info.GetReturnValue().Set(results);
}

v8::Local<v8::Array> Session::run(Session* _, Nan::NAN_METHOD_ARGS_TYPE info) {
  v8::Local<v8::Object> obj = info[0]->ToObject();
  tensorflow::ClientSession::FeedType feeds = get_feeds(obj);
  std::vector<tensorflow::Tensor> tensors;
  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  return results;
}

tensorflow::ClientSession::FeedType Session::get_feeds(v8::Local<v8::Object> obj) {
  // typedef std::unordered_map<Output, Input::Initializer, OutputHash> FeedType;
  tensorflow::ClientSession::FeedType feeds;
  v8::Local<v8::Array> keys = obj->GetOwnPropertyNames();
  for (unsigned int i = 0; i < keys->Length(); i++) {
    // TODO: wrap in template/macro
    v8::Local<v8::String> name = keys->Get(i)->ToString();
    v8::Local<v8::Object> js_tensor = obj->Get(name)->ToObject();

    v8::Local<v8::String> key = Nan::New("_self").ToLocalChecked();
    v8::Local<v8::Object> node_tensor = js_tensor->Get(key)->ToObject();
    // TODO:
    //./third-party/tensorflow/tensorflow/core/lib/core/refcount.h:82] Check failed: ref_.load() >= 1 (0 vs. 1)
    Tensor* tensor = Nan::ObjectWrap::Unwrap<Tensor>(node_tensor);

    std::string tensor_name = *v8::String::Utf8Value(name);
    tensorflow::Tensor tensor_ = *tensor->self;

    tensorflow::Input::Initializer input(tensor_);
    tensorflow::Operation op(nullptr);
    tensorflow::Output output(op, 0);

    tensorflow::Scope scope = this->scope->self();
    auto op_name = scope.GetUniqueNameForOp("Temporary");

    tensorflow::NodeBuilder::NodeOut node_out = tensorflow::ops::AsNodeOut(scope, input);
    tensorflow::NodeBuilder node_builder = tensorflow::NodeBuilder(op_name, "Cast");


    std::pair<tensorflow::Output, tensorflow::Input::Initializer> pair = std::make_pair(output, input);
    feeds.insert(pair);
  }

  return feeds;
}


std::vector<tensorflow::Output> get_fetch_outputs(v8::Local<v8::Object> obj) {
  std::vector<tensorflow::Output> fetch_outputs;
  v8::Local<v8::Array> keys = obj->GetOwnPropertyNames();
  for (unsigned int i = 0; i < keys->Length(); i++) {
    v8::Local<v8::String> name = keys->Get(i)->ToString();
    v8::Local<v8::Object> js_tensor = obj->Get(name)->ToObject();

    v8::Local<v8::String> key = Nan::New("_self").ToLocalChecked();
    v8::Local<v8::Object> node_tensor = js_tensor->Get(key)->ToObject();
  }

  return fetch_outputs;
}

}
