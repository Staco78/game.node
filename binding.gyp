{
    "targets": [
        {
            "target_name": "binding",
            "sources": [
                "src/index.cpp",
                "src/window/window.cpp",
                "src/window/window.h",
                "src/structures/vector2.h",
                "src/structures/colors.h"
            ],
            "include_dirs": [
                "<(module_root_dir)/include",
                "<!(node -p \"require('node-addon-api').include_dir\")"
            ],
            "conditions": [
                [
                    "OS=='win'",
                    {
                        "libraries": [
                            "<(module_root_dir)/lib/sfml-graphics-d.lib",
                            "<(module_root_dir)/lib/sfml-window-d.lib",
                            "<(module_root_dir)/lib/sfml-system-d.lib"
                        ]
                    }
                ]
            ],
            "cflags!": [
                "-fno-exceptions"
            ],
            "cflags_cc!": [
                "-fno-exceptions"
            ],
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "MACOSX_DEPLOYMENT_TARGET": "10.7"
            },
            "msvs_settings": {
                "VCCLCompilerTool": {
                    "ExceptionHandling": 1
                }
            }
        }
    ]
}