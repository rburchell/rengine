var sapphire = require("./build/Release/sapphire.node")

var s = new sapphire.Surface()
s.show()
console.log(s.width)
console.log(s.height)
s.append(new sapphire.Rectangle())
s.append(new sapphire.Rectangle())
s.append(new sapphire.Rectangle())
s.append(new sapphire.Rectangle())
setInterval(function() {
}, 1);
