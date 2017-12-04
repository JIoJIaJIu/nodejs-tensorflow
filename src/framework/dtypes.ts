import * as protobuf from 'protobufjs'

import * as typesProto from '../../third-party/tensorflow/tensorflow/core/framework/types.proto';

const builder = protobuf.loadJson(typesProto);
const Proto = builder.build("tensorflow.TypesProto");
const proto = new Proto();

class DataType {
  _alias: string | undefined;
  _value: object;

  static create(dtype: string | DataType) {
    if (dtype instanceof DataType)
      return dtype;

    return new DataType(dtype);
  }

  constructor(alias?: string) {
    switch (alias && alias.toLowerCase()) {
      case 'float':
        this._value = proto.DT_FLOAT.value;
        break;
      case 'double':
        this._value = proto.DT_DOUBLE.value;
        break;
      case 'int8':
        this._value = proto.DT_INT8.value;
        break;
      case 'int16':
        this._value = proto.DT_INT16.value;
        break;
      case 'int32':
        this._value = proto.DT_INT32.value;
        break;
      case 'int64':
        console.warn('Current filetype is not supported');
        this._value = proto.DT_INT64.value;
        break;
      case 'uint8':
        this._value = proto.DT_UINT8.value;
        break;
      case 'uint16':
        this._value = proto.DT_UINT16.value;
        break;
      default:
        this._value = proto.DT_INVALID.value;
    }

    this._alias = alias;
  }

  get value() {
    return this._value;
  }

  // TODO: needs implementation?
  convert(value: any) {
    return value;
  }

  getArrayBufferView() {
    switch (this._alias) {
      case 'float':
        return Float32Array;
      case 'double':
        return Float64Array;
      case 'int8':
        return Int8Array;
      case 'int16':
        return Int16Array;
      case 'int32':
        return Int32Array;
      case 'int64':
       //TODO
        console.warn('Current filetype is not supported');
        return Int32Array;
      case 'uint8':
        return Uint8Array;
      case 'uint16':
        return Uint16Array;
      default:
        //TODO DT_INVALID
        return Int8Array;
    }
  }
}

export const FLOAT = DataType.create('float');
export const DOUBLE = DataType.create('double');

export const INT8 = DataType.create('int8');
export const INT16 = DataType.create('int16');
export const INT32 = DataType.create('int32');
export const INT64 = DataType.create('int64');

export const UINT8 = DataType.create('uint8');
export const UINT16 = DataType.create('uint16');

export const STRING = DataType.create('string');

export default DataType
