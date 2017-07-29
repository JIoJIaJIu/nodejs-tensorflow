{
  'targets': [
    {
      'target_name': 'tensorflow',
      'sources': [
        'src/main.cc',
        'src/cc/core/graph.cc',
        'src/cc/core/session.cc',
        'src/cc/framework/tensor.cc',
        'src/cc/framework/tensor_shape.cc',
        'src/cc/framework/ops.cc',
        'src/cc/framework/scope.cc',

        'src/cc/framework/ops/constant.cc'
      ],

      'include_dirs': [
        '<!(node -e "require(\'nan\')")',
        'third-party/tensorflow',
        'third-party/tensorflow/deps/external/eigen_archive',
        'third-party/tensorflow/deps/external/protobuf/src',
        'third-party/tensorflow/deps/execroot/org_tensorflow/bazel-out/local-opt/genfiles',
        'third-party/tensorflow/deps/execroot/org_tensorflow/bazel-out/local-py3-opt/genfiles'
      ],

      'conditions': [
        ['OS=="linux"', {
          'libraries': [
            '<(module_root_dir)/lib/libtensorflow_cc.so'
          ],
          'cflags_cc!': ['-fno-rtti']
        }]
      ]
    }
  ]
}
