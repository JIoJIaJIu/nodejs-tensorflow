# Build Tensorflow

Dependencies:
* `bazel >=v0.5.1`

Steps:
* `git submodule --init update`
* `cd third-party/tensorflow`
* `./configure`
* `bazel build --output_base=./deps //tensorflow:libtensorflow.so`

[Install Tensorflow from sources](https://www.tensorflow.org/install/install_sources)
