import {expect} from 'chai';

import tf from '../src/index';

describe('Unit testing Tensor module', function () {
  describe('MArray', function () {
    xit('Create simple MArray', function () {
      let marray = new tf.MArray([1, 2], 'int', [2])
      expect(marray).to.exist;
    });

  });

  describe('Constant', function () {
    describe('Constant([0.1, 1], [2])', function () {
      let constant = {};

      beforeEach(function () {
        constant = new tf.Constant([0.1, 1], 'int8', [2])
      });

      it('Create simple', function () {
        expect(constant).to.exist;
      });
    });
  });
});
