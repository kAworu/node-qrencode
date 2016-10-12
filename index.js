"use strict";

var encoder = require('bindings')('node-qrencode-encoder.node');

module.exports = {
    constants: {
        // QR-code versions.
        VERSION_MIN:  1,
        VERSION_MAX: 40,
        // QR-code ECC levels.
        ECC_LEVEL_M: "M",
        ECC_LEVEL_L: "L",
        ECC_LEVEL_H: "H",
        ECC_LEVEL_Q: "Q",
        // QR-code encoding modes.
        MODE_NUMERIC: "NUMERIC",
        MODE_ALNUM:   "ALNUM",
        MODE_BYTE:    "BYTE",
        MODE_KANJI:   "KANJI",
    },
    encode: function (data, options, callback) {
        if ('undefined' === typeof callback) {
            callback = options;
            options = {};
        }
        // TODO validate options here, choose some defaults.
        options = {version: 1, ecc_level: "Q", mode: "BYTE"};
        return encoder.encode(Buffer.from(data), options, callback);
    },
};
