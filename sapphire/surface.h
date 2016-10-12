#ifndef SURFACE_H
#define SURFACE_H

#include <nan.h>
#include <node.h>
#include <node_object_wrap.h>

#include "rengine.h"

extern rengine::Backend *backend_instance;

class Sapphire : public rengine::StandardSurface
{
public:
    Sapphire();
    rengine::Node *update(rengine::Node *root) override;
    rengine::Node *m_root;
};


class Surface : public Nan::ObjectWrap
{
public:
    static void Init(v8::Local<v8::Object> exports);

private:
    explicit Surface();
    ~Surface();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void Show(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void Hide(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void Width(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void Height(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void Append(const v8::FunctionCallbackInfo<v8::Value>& info);
    static v8::Persistent<v8::Function> constructor;
    Sapphire *m_surface;
};

#endif // SURFACE_H

