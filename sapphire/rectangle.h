#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <nan.h>
#include <node.h>
#include <node_object_wrap.h>

#include "rengine.h"

extern rengine::Backend *backend_instance;

class Rectangle : public Nan::ObjectWrap
{
public:
    static void Init(v8::Local<v8::Object> exports);

    rengine::RectangleNode *m_node;

private:
    explicit Rectangle();
    ~Rectangle();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& info);
    static v8::Persistent<v8::Function> constructor;
};

#endif // RECTANGLE_H

