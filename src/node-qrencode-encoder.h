#ifndef NODE_QRENCODE_ENCODER_H
#define NODE_QRENCODE_ENCODER_H
/*
 * node-qrencode-encoder.h - QR Code encoder
 */

#include <nan.h>


class NodeQREncodeEncoder: public Nan::AsyncWorker
{
	public:

	/* ctor */
	NodeQREncodeEncoder(Nan::Callback *callback);

	/* dtor */
	~NodeQREncodeEncoder();

	// Executed inside the worker-thread.
	// It is not safe to access V8, or V8 data structures here, so
	// everything we need for input and output should go on `this`.
	void Execute();

	// Executed when the async work is complete this function will be run
	// inside the main event loop so it is safe to use V8 again
	void HandleOKCallback();

	private:

	// call `callback` with an Error containing msg.
	void CallbackError(const char *msg);
};

#endif /* ndef NODE_QRENCODE_ENCODER_H */
