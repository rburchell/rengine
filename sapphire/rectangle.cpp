#include "rectangle.h"

using namespace v8;

Persistent<Function> Rectangle::constructor;

Rectangle::Rectangle()
   : m_node(rengine::RectangleNode::create())
{
    std::cerr << "Rectangle constructor" << this << std::endl;
}

Rectangle::~Rectangle()
{
}

void Rectangle::Init(Local<Object> exports)
{
    Isolate *isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "Rectangle"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    /*
    NODE_SET_PROTOTYPE_METHOD(tpl, "show", Show);
    NODE_SET_PROTOTYPE_METHOD(tpl, "hide", Hide);
    NODE_SET_PROTOTYPE_METHOD(tpl, "width", Width);
    NODE_SET_PROTOTYPE_METHOD(tpl, "height", Height);
    NODE_SET_PROTOTYPE_METHOD(tpl, "append", Append);
    */

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "Rectangle"), tpl->GetFunction());
}

void Rectangle::New(const FunctionCallbackInfo<Value>& info)
{
    Isolate *isolate = info.GetIsolate();

    if (info.IsConstructCall()) {
        // Invoked as constructor: `new Rectangle(...)`
        Rectangle *obj = new Rectangle();
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        // Invoked as plain function `Rectangle(...)`, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = { info[0] };
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Object> result =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
        info.GetReturnValue().Set(result);
    }
}

