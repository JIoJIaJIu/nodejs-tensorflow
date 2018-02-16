import {should} from 'chai'

import {MArray} from '../../src/framework/tensor'

import {Array2D, Array3D} from './matrixes'

describe('Unit uint8 Tensor', function () {

  describe.skip('2D Marray', function () {
    let marray;

    beforeEach(function () {
      marray = new MArray(Array2D, 'uint8', [3, 4]);
      should();
    });

    it('Iterate 2D MArray', function () {
      marray[0].should.to.equal(1);
      marray[1].should.to.equal(2);
      marray[2].should.to.equal(3);
      marray[3].should.to.equal(4);

      marray[4].should.to.equal(1);
      marray[5].should.to.equal(2);
      marray[6].should.to.equal(3);
      marray[7].should.to.equal(4);

      marray[8].should.to.equal(3);
      marray[9].should.to.equal(5);
      marray[10].should.to.equal(7);
      marray[11].should.to.equal(9);
    });

    it('Check buffer', function () {
      marray.buffer.should.be.an('arraybuffer');
      marray.buffer.byteLength.should.equal(12);
    });
  });

  describe.skip('3D Marray', function () {
    let marray;

    beforeEach(function () {
      marray = new MArray(Array3D, 'uint8', [2, 2, 3]);
      should();
    });

    it('Iterate 3D MArray', function () {
      marray[0].should.to.equal(1);
      marray[1].should.to.equal(2);
      marray[2].should.to.equal(3);
      marray[3].should.to.equal(11.1);
      marray[4].should.to.equal(12);
      marray[5].should.to.equal(13);

      marray[6].should.to.equal(1);
      marray[7].should.to.equal(2);
      marray[8].should.to.equal(3);
      marray[9].should.to.equal(11);
      marray[10].should.to.equal(12);
      marray[11].should.to.equal(13);
    });

    it('Check buffer', function () {
      marray.buffer.should.be.an('arraybuffer');
      marray.buffer.byteLength.should.equal(12);
    });
  });
});
