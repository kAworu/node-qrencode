{
    "targets": [
        {
            "target_name": "node-qrencode",
            "sources": [
                "src/node-qrencode.cc",
                "src/node-qrencode-encoder.cc"
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")",
            ],
            "libraries": [
                "-lqrencode"
            ],
        },
    ]
}
