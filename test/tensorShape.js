import {expect} from 'chai';

import tf from '../src/index';

describe('Unit testing TensorShape module', function () {
  describe.skip('Test simple TensorShape [1, 1]', function () {
    var shape;
    var data = [1, 1];

    beforeEach(function () {
      shape = new tf.TensorShape(data)
    })

    it('Create', function () {
      expect(shape).to.exist;
    });

    it('Check asList', function () {
      expect(shape.asList()).to.be.an('array');
      expect(shape.asList()).to.deep.equal(data);
    });
  });

  describe.skip('Test TensorShape as [3, 5, null, undefined, 10]', function () {
    var shape;
    var data = [3, 5, null, undefined, 10];

    beforeEach(function () {
      shape = new tf.TensorShape(data)
    })

    it('Create', function () {
      expect(shape).to.exist;
    });

    it('Check asList', function () {
      expect(shape.asList()).to.be.an('array');
      expect(shape.asList()).to.deep.equal([3, 5, 0, 0, 10]);
    });

    it('Check length', function () {
      expect(shape.length).to.equal(5);
    });
  });
});
