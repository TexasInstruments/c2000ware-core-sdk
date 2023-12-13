var clbToolPath = process.argv.slice(2)[0];
var outputFolderPath = process.argv.slice(2)[1];
var dotFilePath = process.argv.slice(2)[2];

var fs = require('fs');
const Viz = require(clbToolPath + '/dot_file_libraries/viz.js');
const { Module, render } = require(clbToolPath + '/dot_file_libraries/full.render.js');

let viz = new Viz({ Module, render });

htmlHead = '<!doctype html>\n<html lang="en">\n' + 
    '\n<meta charset="utf-8">\n<title>CLB Configuration Diagram</title>\n' + 
    '<style type="text/css">* {font-family:arial, sans-serif;}</style>\n' + 
    '\n\n<h1>CLB Tile Configuration</h1>\n' + 
    '' + 
    '\n\n'

fs.readFile(dotFilePath,'utf8', function read(err, data) {
    if (err) {
    	console.log("No CLB dot file!");
        //throw err;
    }
    else {
    	createDiagrams(data);
	}
});

function createDiagrams(content)
{
  viz.renderString(content)
    .then(result => {
      fs.writeFile(outputFolderPath + '/clb.svg', result, function (err) {
      if (err) throw err;
      console.log('CLB block diagram SVG was created!');
    });
    fs.writeFile(outputFolderPath + '/clb.html', htmlHead + result, function (err) {
      if (err) throw err;
      console.log('CLB block diagram HTML was created!');
    });
    })
    .catch(error => {
      viz = new Viz({ Module, render });
      console.error(error);
    });
}