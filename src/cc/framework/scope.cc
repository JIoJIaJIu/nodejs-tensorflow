#include "./scope.h"

namespace nodejs_tf {

NAN_MODULE_INIT(Scope::Init) {
  printf("cc::Scope::Init\n");

  auto fn = Nan::New<v8::FunctionTemplate>(Scope::New);
  auto fn_name = Nan::New("Scope").ToLocalChecked();

  fn->InstanceTemplate()->SetInternalFieldCount(1);
  fn->SetClassName(fn_name);

  Nan::Set(target, fn_name, fn->GetFunction());
}

NAN_METHOD(Scope::New) {
  printf("cc::Scope::New\n");

  if (!info.IsConstructCall()) {
    Nan::ThrowError("Wrong invokation, should be constructor call");
    return;
  }

  Scope* scope = new Scope();
  scope->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

tensorflow::Scope& Scope::self() {
  return self_;
}

Scope::Scope() : self_(tensorflow::Scope::NewRootScope()) {} 
Scope::~Scope() {}

}
