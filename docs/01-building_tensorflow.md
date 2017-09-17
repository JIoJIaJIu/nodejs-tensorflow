# Build Tensorflow

Dependencies:
* `bazel >=v0.5.1`

Steps:
* `git submodule --init update`
* `cd third-party/tensorflow`
* `./configure`
* `bazel build //tensorflow:libtensorflow_cc.so`

[Install Tensorflow from sources](https://www.tensorflow.org/install/install_sources)
