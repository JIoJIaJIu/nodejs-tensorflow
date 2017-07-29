#ifndef NODEJS_TF_SCOPE_H
#define NODEJS_TF_SCOPE_H

#include <nan.h>

#include <tensorflow/cc/framework/scope.h>

namespace nodejs_tf {

class Scope: public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    Scope();
    tensorflow::Scope& self();
  private:
    ~Scope();

    tensorflow::Scope self_;
};

}

#endif
