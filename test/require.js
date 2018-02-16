import {expect} from 'chai';

import tf from '../src/index';

describe('Requiring nodejs-tensorflow', function () {
  it('Should returns right version', function () {
    expect(tf.version()).equal('1.2.0-rc2');
  });

  it('Should create TensorShape without error', function () {
    let shape = new tf.TensorShape();
    expect(shape).to.exist;
  });
})
