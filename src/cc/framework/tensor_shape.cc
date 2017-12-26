#include "tensor_shape.h"

namespace nodejs_tf {

using v8::ArrayBuffer;
using v8::External;
using v8::FunctionTemplate;
using v8::Local;

TensorShape::TensorShape(tensorflow::TensorShapeProto& tsp): Nan::ObjectWrap() {
  tensorflow::TensorShape::IsValid(tsp);
  this->self = new tensorflow::TensorShape(tsp);
}

TensorShape::~TensorShape() {
}

NAN_CONSTRUCTOR(TensorShape::constructor);

NAN_MODULE_INIT(TensorShape::Init) {
  Nan::HandleScope scope;

  printf("cc: TensorShape::Init\n");
  auto fn = Nan::New<FunctionTemplate>(TensorShape::New);
  auto fn_name = Nan::New("TensorShape").ToLocalChecked();

  fn->InstanceTemplate()->SetInternalFieldCount(2);
  printf("field_count: %d\n", fn->InstanceTemplate()->InternalFieldCount());
  fn->SetClassName(fn_name);

  constructor.Reset(fn);
  Nan::Set(target, fn_name, fn->GetFunction());
}

NAN_NEW(TensorShape::New) {
  Nan::HandleScope scope;

  printf("cc: TensorShape::New\n");
  if (!info[0]->IsArrayBuffer()) {
    Nan::ThrowError("Argument should be ArrayBuffer for ProtoBuf");
    return;
  }

  std::stringstream ss;
  v8::ArrayBuffer::Contents ext = info[0].As<ArrayBuffer>()->Externalize();
  ss.write(static_cast<char *>(ext.Data()), ext.ByteLength());
  tensorflow::TensorShapeProto* tsp = new tensorflow::TensorShapeProto();
  tsp->ParseFromIstream(&ss);

  auto tensor_shape = new TensorShape(*tsp);
  tensor_shape->Wrap(info.Holder());

  info.GetReturnValue().Set(info.Holder());
}

}
