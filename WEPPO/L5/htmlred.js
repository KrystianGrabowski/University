var fs = require('fs');
var http = require('http');
(async function () {
    var html = await fs.promises.readFile('test.html', 'utf-8');
    var server = http.createServer(
    (req, res) => {
        res.setHeader('Content-type', 'text/html', 'charset=utf-8');
        res.end(html);
    });
    server.listen(4000);
    console.log('started');
})(); 