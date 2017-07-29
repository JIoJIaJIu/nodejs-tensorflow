#ifndef NODEJS_TF_TENSOR_H
#define NODEJS_TF_TENSOR_H

#include <nan.h>

#include <tensorflow/c/c_api.h>

#include <tensorflow/core/framework/tensor.h>
#include <tensorflow/core/framework/tensor_shape.h>
#include <tensorflow/core/framework/types.h>

#include "tensor_shape.h"

namespace nodejs_tf {

class Tensor: public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
    Tensor(tensorflow::Tensor& tensor);
    ~Tensor();

    tensorflow::Tensor* self;
  private:
    static NAN_METHOD(New);
    static NAN_METHOD(shape);

    Tensor(tensorflow::DataType dtype, const tensorflow::TensorShape& shape);
    Tensor(TF_DataType dtype, int64_t dims, int num_dims, size_t len);
    Tensor(TF_DataType dtype, int64_t dims, int num_dims, size_t len, void* data);
    static void ToString(const v8::FunctionCallbackInfo<v8::Value>& args);
};

}
#endif
