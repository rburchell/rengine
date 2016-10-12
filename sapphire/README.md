# building

Assuming you have a working rengine development environment already...

* brew install node npm
* npm install -g node-gyp
* node-gyp configure
* node-gyp build
* node test.js

# TODO

* Figure out how to inherit from something inheriting Nan::ObjectWrap. We need
  to do this to offer a "class Node : public Nan::ObjectWrap" that offers append,
  etc methods, and then inherit Rectangle from it or something...

  Looks like we need to keep Persistent\<FunctionTemplate\> for Node's prototype,
  and use FunctionTemplate::Inherit() on it for Rectangle etc -- see
  http://stackoverflow.com/questions/15394176/implementing-inheritance-in-node-js-bindings
* Surface's render method should walk the JS node tree and populate rengine
  with its nodes. But does this make sense with how react's API wants us to
  work?

  Assuming it does: we need two node trees here, JSNode (JSRectangle, etc) --
  equivilent to QtQuick's items. For each frame, Surface will be responsible for
  walking the "item" tree from the root down, creating nodes as it goes (virtual
  Node *render() or something)?

  In the longer run, this may also free us up to untie JS events from windowing
  events (different threads), should we so desire...
