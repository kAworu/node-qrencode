{
    "targets": [
        {
            "target_name": "node-qrencode-encoder",
            "sources": [
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
