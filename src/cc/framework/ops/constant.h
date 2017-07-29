#ifndef NODEJS_TF_OPS_CONTANT_H
#define NODEJS_TF_OPS_CONTANT_H

#include <nan.h>

#include <tensorflow/cc/ops/const_op.h>

namespace nodejs_tf {

class Constant: public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
  private:
    Constant();
    ~Constant();
};

}

#endif
