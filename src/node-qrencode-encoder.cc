/*
 * node-qrencode-encoder.cc - QR Code encoder
 */

#include <map>
#include <sstream>

#include <nan.h>
#include <qrencode.h>


using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::Error;
using Nan::Get;
using Nan::GetFunction;
using Nan::New;
using Nan::Null;
using Nan::Set;
using Nan::Utf8String;


class NodeQREncodeEncoder: public AsyncWorker
{
	public:

	static const std::map<std::string, QRencodeMode> string2QRencodeMode()
	{
		const std::map<std::string, QRencodeMode> map = {
			{"NUMERIC", QR_MODE_NUM},
			{"ALNUM",   QR_MODE_AN},
			{"BYTE",    QR_MODE_8},
			{"KANJI",   QR_MODE_KANJI},
		};
		return map;
	}

	static const std::map<std::string, QRecLevel> string2QRecLevel()
	{
		const std::map<std::string, QRecLevel> map = {
			{"L", QR_ECLEVEL_L},
			{"M", QR_ECLEVEL_M},
			{"Q", QR_ECLEVEL_Q},
			{"H", QR_ECLEVEL_H},
		};
		return map;
	}

	/* ctor */
	NodeQREncodeEncoder(Callback *callback, const uint8_t *data, size_t
		    datalen, uint32_t version, QRencodeMode mode, QRecLevel ecc_level):
	    AsyncWorker(callback),
            data_(data),
            datalen_(datalen),
            version_(version),
            mode_(mode),
            ecc_level_(ecc_level)
	{ }

	/* dtor */
	~NodeQREncodeEncoder()
	{
		// TODO
	}

	// Executed inside the worker-thread.
	// It is not safe to access V8, or V8 data structures here, so
	// everything we need for input and output should go on `this`.
	void Execute()
	{
		// TODO
	}

	// Executed when the async work is complete this function will be run
	// inside the main event loop so it is safe to use V8 again
	void HandleOKCallback()
	{
		std::ostringstream oss;
		oss << "version=" << version_  << " mode=" << mode_ << " ecc_level=" << ecc_level_;
		return CallbackError(oss.str().c_str());
		// TODO
	}


	protected:

        /* the data to encode */
	const uint8_t *data_;
	size_t datalen_;
	/* encoding options */
	uint32_t version_;
	QRencodeMode mode_;
	QRecLevel ecc_level_;

	// call `callback` with an Error containing msg.
	void CallbackError(const char *msg)
	{
		v8::Local<v8::Value> argv[] = {
			Error(msg),
		};
		callback->Call(1, argv);
	}
};


// async access to NodeQREncodeEncoder
NAN_METHOD(NodeQREncodeEncodeAsync) {
	/*
	 * we're called with (buffer, options, callback) from our module so we
	 * don't need to check the arguments.
	 */
	uint8_t *data  = (uint8_t *)node::Buffer::Data(info[0]);
	size_t datalen = node::Buffer::Length(info[0]);
	v8::Local<v8::Object> options = Nan::To<v8::Object>(info[1]).ToLocalChecked();
	Callback *callback = new Callback(info[2].As<v8::Function>());

	// extract the options
	uint32_t version = Nan::To<uint32_t>(Get(options,
	    New("version").ToLocalChecked()).ToLocalChecked()).FromJust();
	QRencodeMode mode = NodeQREncodeEncoder::string2QRencodeMode().find(
	    *Utf8String(Get(options, New("mode").ToLocalChecked()).ToLocalChecked())
	)->second;
	QRecLevel ecc_level = NodeQREncodeEncoder::string2QRecLevel().find(
	    *Utf8String(Get(options, New("ecc_level").ToLocalChecked()).ToLocalChecked())
	)->second;
	AsyncQueueWorker(
	    new NodeQREncodeEncoder(callback, data, datalen, version, mode, ecc_level)
	);
}


// export stuff to NodeJS
NAN_MODULE_INIT(NodeQREncodeInit) {
	Set(target, New("encode").ToLocalChecked(),
	    GetFunction(New<v8::FunctionTemplate>(NodeQREncodeEncodeAsync)).ToLocalChecked());
}

NODE_MODULE(node_qrencode_encoder, NodeQREncodeInit)
