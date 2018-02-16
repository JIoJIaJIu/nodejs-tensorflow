import * as _ from 'lodash'
import * as protobuf from 'protobufjs'

import * as tensorShapeProto from '../../third-party/tensorflow/tensorflow/core/framework/tensor_shape.proto';

import * as tf_ from 'tensorflow.node'
/**
 * Built similar python [TensorShape](https://www.tensorflow.org/api_docs/python/tf/TensorShape)
 */
class TensorShape {
  private _self: any;

  static create(shape?: number[] | TensorShape): TensorShape {
    if (!shape) {
      return new TensorShape();
    } else if (_.isArray(shape)) {
      return new TensorShape(shape);
    }

    return shape;
  }

  /**
   * @param {Array} data
   */
  constructor(data?: number[]) {
    let builder = protobuf.loadJson(tensorShapeProto);
    let Proto = builder.build("tensorflow.TensorShapeProto");
    let proto = new Proto();

    _.forEach(data, size => {
      proto.set({dim: {size: size}});
    })
    this._self = new tf_.TensorShape(proto.toArrayBuffer());
  }

  /**
   * Returns TensorShape as an Array
   */
  asList(): number[] {
    throw new Error("Not implemented");
  }

  get dims(): TensorDimension[] {
    throw new Error("Not implemented");
  }

  get ndims() {
    throw new Error("Not implemented");
  }

  toString = (): string => {
    throw new Error("Not implemented");
  }
}

/**
 * Tensor dimension class
 */
class TensorDimension {
  private _power = 0;

  constructor(power?: any) {
    this._power = _.toNumber(power) || 0;
  }

  /**
   * Returns cardinality(power) of dimension
   */
  get power() {
    return this._power;
  }

  toString = (): string => {
    return `Dimension(${this.power})`;
  }
}


export default TensorShape
