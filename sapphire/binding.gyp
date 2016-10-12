{
    "targets": [
        {
            "target_name": "sapphire",
            "include_dirs": [
                "../include/",
                "../3rdparty/",
                "<!@(pkg-config sdl2 --cflags-only-I | sed s/-I//g)",
                "<!(node -e \"require('nan')\")",
             ],
            "sources": [
                "addon.cpp",
                "surface.cpp",
                "rectangle.cpp",
            ],
            "defines": [
                "RENGINE_OPENGL_DESKTOP", 
                "RENGINE_BACKEND_SDL"
            ],
            "cflags": [
#                "-std=c++11",
                "!@(pkg-config --cflags sdl2)",
            ],
            "libraries": [
                "<!@(pkg-config sdl2 --libs)",
            ],
             "xcode_settings": {
        'MACOSX_DEPLOYMENT_TARGET': '10.9',

        'OTHER_CFLAGS': [
          "-std=c++11",
          "-stdlib=libc++"
        ],
#                 'MACOSX_DEPLOYMENT_TARGET': '10.10',
#                 'OTHER_LDFLAGS': ['-stdlib=libc++'],
#                'OTHER_CFLAGS': [
#                    "-stdlib=libc++"
#                ]
            }
        }
    ]
}
