var util = require("util");

var chai       = require("chai");
var underscore = require("underscore");
var expect     = chai.expect;

var qrencode = require("../index.js");

// QR-code versions.
var qr_versions = underscore.range(1, 40);
// QR-code ECC levels.
var qr_ecc_levels = {
    ECC_LEVEL_M: "M",
    ECC_LEVEL_L: "L",
    ECC_LEVEL_H: "H",
    ECC_LEVEL_Q: "Q",
};
// QR-code encoding modes.
var qr_enc_modes = {
    MODE_NUMERIC: "NUMERIC",
    MODE_ALNUM:   "ALNUM",
    MODE_BYTE:    "BYTE",
    MODE_KANJI:   "KANJI",
};

describe("constants", function () {
    describe("QR-code versions", function () {
        it("should set VERSION_MIN to 1", function () {
            expect(qrencode.constants.VERSION_MIN).to.exist.and.to.eql(1);
        });
        it("should set VERSION_MAX to 40", function () {
            expect(qrencode.constants.VERSION_MAX).to.exist.and.to.eql(40);
        });
    });

    describe("QR-code ECC levels", function () {
        underscore.each(qr_ecc_levels, function (value, key) {
            it("should set " + key + " to " + value, function () {
                expect(qrencode.constants[key]).to.exist.and.to.eql(value);
            });
        });
    });

    describe("QR-code encoding modes", function () {
        underscore.each(qr_enc_modes, function (value, key) {
            it("should set " + key + " to " + value, function () {
                expect(qrencode.constants[key]).to.exist.and.to.eql(value);
            });
        });
    });
});

describe("encode()", function () {
    it.skip("should be implemented", function (done) {
        qrencode.encode("A brief note", function (err) {
            expect(err).to.not.exist;
            return done();
        });
    });
});
