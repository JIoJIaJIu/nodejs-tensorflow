#include "graph.h"

namespace nodejs_tf {

Graph::Graph() {
}

Graph::~Graph() {
}

NAN_MODULE_INIT(Graph::Init) {
  auto fn = Nan::New<v8::FunctionTemplate>(Graph::New);
  auto fn_name = Nan::New("Graph").ToLocalChecked();

  fn->InstanceTemplate()->SetInternalFieldCount(1);
  fn->SetClassName(fn_name);

  Nan::Set(target, fn_name, fn->GetFunction());
}

NAN_METHOD(Graph::New) {
  printf("cc: Graph::New\n");

  Graph *graph = new Graph();
  graph->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

}
