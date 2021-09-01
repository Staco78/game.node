{
    "targets": [
        {
            "target_name": "binding",
            "sources": [
                "<!@(node -p \"var fs=require('fs'),path=require('path'),walk=function(r){let t,e=[],n=null;try{t=fs.readdirSync(r)}catch(r){n=r.toString()}if(n)return n;var a=0;return function n(){var i=t[a++];if(!i)return e;let u=path.resolve(r,i);i=r+'/'+i;let c=fs.statSync(u);if(c&&c.isDirectory()){let r=walk(i);return e=e.concat(r),n()}return e.push(i),n()}()};walk('./src').join(' ');\")"
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