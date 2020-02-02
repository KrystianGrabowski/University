var http = require('http');

var server =
    http.createServer(
    (req, res) => {
        res.end(`hello world ${new Date()}`);
    });
server.listen(3000);
console.log('started');