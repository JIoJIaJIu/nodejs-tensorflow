import * as _ from 'lodash'

import * as tf_ from 'tensorflow.node'

import Tensor from '../framework/tensor'

/**
 * Based on python [object](https://www.tensorflow.org/api_docs/python/tf/Session)
 */
class Session {
  private _self: any;

  constructor() {
    this._self = new tf_.Session();
  }

  /**
   * @param {Object} fetches
   *  - key: String
   *  - value: Tensor
   */
  run(fetches: object) {
    let list = this._self.run(fetches);

    return _.map(list, t_ => { Tensor.wrap(t_); });
  }
}

export default Session
