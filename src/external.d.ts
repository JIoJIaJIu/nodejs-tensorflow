declare module '*tensorflow.node' {
  const Constant: any;
  const Graph: any;
  const Operation: any; 
  const Scope: any;
  const Session: any;
  const Tensor: any;
  const TensorShape: any;
  const version: any;
  export {
    Constant,
    Graph,
    Operation,
    Session,
    Scope,
    Tensor,
    TensorShape,
    version
  }
}

declare module '*/types.proto' {
  const DataType: any;
  export {DataType};
}
