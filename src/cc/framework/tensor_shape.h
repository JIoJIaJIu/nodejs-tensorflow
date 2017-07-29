#ifndef NODEJS_TF_TENSOR_SHAPE_H
#define NODEJS_TF_TENSOR_SHAPE_H

#include <nan.h>
#include <node.h>

#include "tensorflow/core/framework/tensor_shape.h"

namespace nodejs_tf {

class TensorShape: public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);

    tensorflow::TensorShape* self;
  private:
    TensorShape();
    ~TensorShape();
};

}

#endif
