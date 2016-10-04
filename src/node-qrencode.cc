/*
 * node-qrencode.cc - glue for Node.js
 */

#include <nan.h>

#include "node-qrencode-encoder.h"

using Nan::AsyncQueueWorker;
using Nan::Callback;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

// async access to NodeQREncodeEncoder
NAN_METHOD(NodeQREncodeEncodeAsync) {
	Callback *callback = new Callback(info[0].As<v8::Function>());
	AsyncQueueWorker(new NodeQREncodeEncoder(callback));
}


// export stuff to NodeJS
NAN_MODULE_INIT(NodeQREncodeInit) {
	v8::Local<v8::Object> constants = New<v8::Object>();

	// QR-code versions.
	Set(constants, New("VERSION_MIN").ToLocalChecked(), New( 1));
	Set(constants, New("VERSION_MAX").ToLocalChecked(), New(40));

	// QR-code ECC levels.
	Set(constants, New("ECC_LEVEL_M").ToLocalChecked(), New("M").ToLocalChecked());
	Set(constants, New("ECC_LEVEL_L").ToLocalChecked(), New("L").ToLocalChecked());
	Set(constants, New("ECC_LEVEL_H").ToLocalChecked(), New("H").ToLocalChecked());
	Set(constants, New("ECC_LEVEL_Q").ToLocalChecked(), New("Q").ToLocalChecked());

	// QR-code encoding modes.
	Set(constants, New("MODE_NUMERIC").ToLocalChecked(),
	    New("NUMERIC").ToLocalChecked());
	Set(constants, New("MODE_ALNUM").ToLocalChecked(),
	    New("ALNUM").ToLocalChecked());
	Set(constants, New("MODE_BYTE").ToLocalChecked(),
	    New("BYTE").ToLocalChecked());
	Set(constants, New("MODE_KANJI").ToLocalChecked(),
	    New("KANJI").ToLocalChecked());

	// exported stuff
	Set(target, New("constants").ToLocalChecked(), constants);
	Set(target, New("encode").ToLocalChecked(),
	    GetFunction(New<v8::FunctionTemplate>(NodeQREncodeEncodeAsync)).ToLocalChecked());
}


NODE_MODULE(node_qrencode, NodeQREncodeInit)
