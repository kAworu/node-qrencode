/*
 * node-qrencode-encoder.cc - QR Code encoder
 */

#include "node-qrencode-encoder.h"

using Nan::Callback;
using Nan::CopyBuffer;
using Nan::Error;
using Nan::New;
using Nan::Null;
using Nan::Set;
using Nan::ThrowError;
using Nan::ThrowTypeError;


/* ctor */
NodeQREncodeEncoder::NodeQREncodeEncoder(Callback *callback):
	AsyncWorker(callback)
{ }


/* dtor */
NodeQREncodeEncoder::~NodeQREncodeEncoder()
{
	// TODO
}


// Executed inside the worker-thread.
// It is not safe to access V8, or V8 data structures here, so
// everything we need for input and output should go on `this`.
void
NodeQREncodeEncoder::Execute()
{
	// TODO
}


// Executed when the async work is complete this function will be run
// inside the main event loop so it is safe to use V8 again
void
NodeQREncodeEncoder::HandleOKCallback()
{
	return CallbackError("unimplemented");
	// TODO
}


// call `callback` with an Error containing msg.
void
NodeQREncodeEncoder::CallbackError(const char *msg)
{
	v8::Local<v8::Value> argv[] = {
		Error(msg),
	};
	callback->Call(1, argv);
}
