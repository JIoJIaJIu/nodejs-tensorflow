#ifndef NODEJS_TF_TENSOR_SHAPE_H
#define NODEJS_TF_TENSOR_SHAPE_H

#include <node.h>

#include "../lib/nan.h"
#include "tensorflow/core/framework/tensor_shape.h"

namespace nodejs_tf {

class TensorShape: public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
    static NAN_NEW(New);

    tensorflow::TensorShape* self;
  private:
    TensorShape(tensorflow::TensorShapeProto& tsp);
    ~TensorShape();

    static NAN_CONSTRUCTOR(constructor);
};

}

#endif
