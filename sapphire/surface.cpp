#include "surface.h"
#include "rectangle.h"

using namespace v8;

Persistent<Function> Surface::constructor;

Sapphire::Sapphire()
{
    m_root = rengine::Node::create();
}

rengine::Node *Sapphire::update(rengine::Node *root)
{
    requestRender();
    return m_root;
}

Surface::Surface()
    : m_surface(new Sapphire)
{
    std::cerr << "Surface constructor" << std::endl;
}

Surface::~Surface()
{
    delete m_surface;
}

void Surface::Init(Local<Object> exports)
{
    Isolate *isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "Surface"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "show", Show);
    NODE_SET_PROTOTYPE_METHOD(tpl, "hide", Hide);
    NODE_SET_PROTOTYPE_METHOD(tpl, "append", Append);

    Local<ObjectTemplate> ptpl = tpl->PrototypeTemplate();
    ptpl->SetAccessor(String::NewFromUtf8(isolate, "width"), Width);
    ptpl->SetAccessor(String::NewFromUtf8(isolate, "height"), Height);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "Surface"), tpl->GetFunction());
}

void Surface::New(const FunctionCallbackInfo<Value>& info)
{
    Isolate *isolate = info.GetIsolate();

    if (info.IsConstructCall()) {
        // Invoked as constructor: `new Surface(...)`
        Surface *obj = new Surface();
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        // Invoked as plain function `Surface(...)`, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = { info[0] };
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Object> result =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
        info.GetReturnValue().Set(result);
    }
}

void Surface::Show(const FunctionCallbackInfo<Value>& info)
{
    Surface *obj = ObjectWrap::Unwrap<Surface>(info.This());
    obj->m_surface->show();
}

void Surface::Hide(const FunctionCallbackInfo<Value>& info)
{
    Surface *obj = ObjectWrap::Unwrap<Surface>(info.This());
    obj->m_surface->hide();
}

void Surface::Width(Local<String>, const PropertyCallbackInfo<Value>& info)
{
    Surface *obj = ObjectWrap::Unwrap<Surface>(info.This());
    Isolate *isolate = info.GetIsolate();

    info.GetReturnValue().Set(Number::New(isolate, obj->m_surface->size().x));
}

void Surface::Height(Local<String>, const PropertyCallbackInfo<Value>& info)
{
    Surface *obj = ObjectWrap::Unwrap<Surface>(info.This());
    Isolate *isolate = info.GetIsolate();

    info.GetReturnValue().Set(Number::New(isolate, obj->m_surface->size().y));
}

void Surface::Append(const FunctionCallbackInfo<Value>& info)
{
    Surface *obj = ObjectWrap::Unwrap<Surface>(info.This());
    Isolate *isolate = info.GetIsolate();

    if (info.Length() < 1 || !info[0]->IsObject()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Append requires a Node.")));
        return;
    }

    Local<Object> v8rect = info[0]->ToObject();
    Rectangle *r = Nan::ObjectWrap::Unwrap<Rectangle>(v8rect);
    std::cerr << "Appending JS rectangle " << r << std::endl;

    // XXX: don't do this here, but in JS.
    rengine::vec2 sz = obj->m_surface->size();

    int rw = 100;
    int rh = 20;
    int w = sz.x - rw;
    int h = sz.y - rh;

    rengine::RectangleNode *rect = r->m_node;
    rengine::vec4 color((rand() % 100)/100.0,
               (rand() % 100)/100.0,
               (rand() % 100)/100.0,
               0.9);
    rect->setGeometry(rengine::rect2d::fromXywh(rand() % w, rand() % h, rw, rh));
    rect->setColor(color);

    obj->m_surface->m_root->append(r->m_node);
}


