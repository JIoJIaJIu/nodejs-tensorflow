#include "./constant.h"

namespace nodejs_tf {

NAN_MODULE_INIT(Constant::Init) {
  printf("cc::Constant::Init\n");

  auto fn = Nan::New<v8::FunctionTemplate>(Constant::New);
  auto fn_name = Nan::New("Constant").ToLocalChecked();

  fn->InstanceTemplate()->SetInternalFieldCount(1);
  fn->SetClassName(fn_name);

  Nan::Set(target, fn_name, fn->GetFunction());
}

NAN_METHOD(Constant::New) {
  printf("cc::Constant::New\n");

  if (!info.IsConstructCall()) {
    Nan::ThrowError("Wrong invokation, should be constructor call");
    return;
  }

  Constant* constant = new Constant();
  constant->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

Constant::Constant() {
  printf("Create Constant\n");
  //this->self = new tensorflow::Operation();
}

Constant::~Constant() {
}

}
