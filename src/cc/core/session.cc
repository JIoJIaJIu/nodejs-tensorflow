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

  /*
  tensorflow::Session* out_session;
  TF_CHECK_OK(NewSession(options, &out_session));
  self = out_session;

  //TODO:
  tensorflow::GraphDef gdef;
  //root.WithDevice("/cpu:0");

  TF_CHECK_OK(scope->ToGraphDef(graph));
  TF_CHECK_OK(self->Create(&*graph));
  client_session = new tensorflow::ClientSession(*scope);


  TF_CHECK_OK(self->Create(&*graph));
  */

  scope = new Scope();
  //self = new tensorflow::ClientSession(*scope);
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
  printf("TF_SESSION [%s] length of feeds is %u\n", __TIME__, feeds.size());
  /*
  v8::Local<v8::Array> keys = param1->GetOwnPropertyNames();
  //auto arg1 = Handle<Array>::Cast(info[0]);

  std::vector<std::pair<std::string, tensorflow::Tensor>> inputs;
  std::vector<std::string> output_tensor_names;
  for (unsigned int i = 0; i < keys->Length(); i++) {
    v8::Local<v8::String> name = keys->Get(i)->ToString();
    // TODO: add checking
    v8::Local<v8::Object> js_tensor = param1->Get(name)->ToObject();

    v8::Local<v8::String> key = Nan::New("_self").ToLocalChecked();
    v8::Local<v8::Object> node_tensor = js_tensor->Get(key)->ToObject();
    // TODO:
    //./third-party/tensorflow/tensorflow/core/lib/core/refcount.h:82] Check failed: ref_.load() >= 1 (0 vs. 1)
    Tensor* tensor = Nan::ObjectWrap::Unwrap<Tensor>(node_tensor);

    std::string tensor_name = *v8::String::Utf8Value(name);
    tensorflow::Tensor tensor_ = *tensor->self;
    printf("%s\n", tensor_.DebugString().c_str());

    auto p = std::pair<std::string, tensorflow::Tensor>(tensor_name, tensor_);
    inputs.push_back(p);
    output_tensor_names.push_back(tensor_name);
  }
  */

  //npm ERR! There is likely additional logging output above.
  //
  // typedef std::unordered_map<Output, Input::Initializer, OutputHash> FeedType;
  //
  //npm ERR! There is likely additional logging output above.
  /*
  /// Evaluate the tensors in `fetch_outputs`. The values are returned as
  /// `Tensor` objects in `outputs`. The number and order of `outputs` will
  /// match `fetch_outputs`.
  Status Run(const std::vector<Output>& fetch_outputs,
             std::vector<Tensor>* outputs) const;

  /// Same as above, but use the mapping in `inputs` as feeds.
  Status Run(const FeedType& inputs, const std::vector<Output>& fetch_outputs,
             std::vector<Tensor>* outputs) const;

  /// Same as above. Additionally runs the operations ins `run_outputs`.
  Status Run(const FeedType& inputs, const std::vector<Output>& fetch_outputs,
             const std::vector<Operation>& run_outputs,
             std::vector<Tensor>* outputs) const;

  /// Use `run_options` to turn on performance profiling. `run_metadata`, if not
  /// null, is filled in with the profiling results.
  Status Run(const RunOptions& run_options, const FeedType& inputs,
             const std::vector<Output>& fetch_outputs,
             const std::vector<Operation>& run_outputs,
             std::vector<Tensor>* outputs, RunMetadata* run_metadata) const;
             */
  std::vector<tensorflow::Tensor> tensors;
  //TODO implement const std::vector<string>& output_tensor_names as 2nd arg
  //TODO implement const std::vector<string>& target_node_names as 3nd arg
  //TF_CHECK_OK(self->Run(feeds));
  /*
  TF_CHECK_OK(client_session->Run(inputs, output_tensor_names, {}, &tensors));
  printf("run %d %d\n", tensors.size(), output_tensor_names.size());
  */

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  /*
  for (unsigned int i = 0; i < tensors.size(); i++) {
    Tensor* t = new Tensor(tensors[i]);
    Local<v8::External>obj = Nan::New<v8::External>(t);
    results->Set(i, obj);
  }

  */
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

    // create node


    tensorflow::Input::Initializer input(tensor_);
    // tensorflow::Input input(tensor_);
    //printf("TF_SESSION [%s] node_id %s\n", __TIME__, input.node()->DebugString().c_str());
    //std::pair<tensorflow::Output, tensorflow::Input::Initializer> pair = std::make_pair(tensorflow::Output(), input);
    tensorflow::Operation op(nullptr);
    tensorflow::Output output(op, 0);

    tensorflow::Scope scope = this->scope->self();
    auto op_name = scope.GetUniqueNameForOp("Temporary");
    printf("TF_SESSION [%s] op_name %s\n", __TIME__, op_name.c_str());

    tensorflow::NodeBuilder::NodeOut node_out = tensorflow::ops::AsNodeOut(scope, input);
    tensorflow::NodeBuilder node_builder = tensorflow::NodeBuilder(op_name, "Cast");
    //tensorflow::Node* node = tensorflow::NodeBuilder::NodeOut().node;

    //printf("TF_SESSION [%s] node id %d\n", __TIME__, node->id());
    printf("TF_SESSION [%s] output hash %d\n", __TIME__, output.hash());

    std::pair<tensorflow::Output, tensorflow::Input::Initializer> pair = std::make_pair(output, input);
    feeds.insert(pair);
    printf("TF_SESSION [%s] feeds got %i pair\n", __TIME__, i);
  }

  printf("TF_SESSION [%s] feeds' size is %u\n", __TIME__, feeds.size());
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

    //fetch_outputs.insert(tensorflow::Output());
  }

  return fetch_outputs;
}


}
