#include <nan.h>
#include <node.h>
#include <node_object_wrap.h>
#include <string.h>

#include <tensorflow/c/c_api.h>
#include <tensorflow/core/platform/logging.h>

#include "cc/core/graph.h"
#include "cc/core/session.h"
#include "cc/framework/tensor.h"
#include "cc/framework/tensor_shape.h"
#include "cc/framework/ops.h"
#include "cc/framework/scope.h"

#include "cc/framework/ops/constant.h"

namespace nodejs_tf {

using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Version(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  const char *version = TF_Version();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, version));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "version", Version);
  Graph::Init(exports);
  Operation::Init(exports);
  Session::Init(exports);
  Tensor::Init(exports);
  TensorShape::Init(exports);
  Scope::Init(exports);

  //operations
  Constant::Init(exports);
}

NODE_MODULE(tensorflow, init)

}
