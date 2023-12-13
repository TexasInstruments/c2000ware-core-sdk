var dotLibPath = process.argv.slice(2)[0];
var outputFolderPath = process.argv.slice(2)[1];
var dotFilePath = process.argv.slice(2)[2];
var outFileName = process.argv.slice(2)[3];
var engine = process.argv.slice(2)[4];
var fs = require('fs');
var path = require('path');

const Viz = require(dotLibPath + '/dot_file_libraries/viz.js');
const { Module, render } = require(dotLibPath + '/dot_file_libraries/full.render.js');

let viz = new Viz({ Module, render });

htmlHead = '<!doctype html>\n<html lang="en">\n' + 
    '\n<meta charset="utf-8">\n<title>' + outFileName + ' Configuration Diagram</title>\n' + 
    '<style type="text/css">* {font-family:arial, sans-serif;}</style>\n' + 
    '\n\n<h1>' + outFileName + ' Configuration Diagram</h1>\n' + 
    '' + 
    '\n\n'

console.log("Output file: " + outFileName);

fs.readFile(dotFilePath,'utf8', function read(err, data) {
    if (err) {
    	console.log("No input file!");
        //throw err;
    }
    else {
    	createDiagrams(data);
	}
});

function createDiagrams(content)
{
  viz.renderString(content, {engine: engine})
    .then(result => {
      fs.writeFile(outputFolderPath + '/' + outFileName + '.svg', result, function (err) {
      if (err) throw err;
      console.log('Block diagram SVG was created!');
    });
    fs.writeFile(outputFolderPath + '/' + outFileName + '.html', htmlHead + result, function (err) {
      if (err) throw err;
      console.log('Block diagram HTML was created!');
    });
    })
    .catch(error => {
      viz = new Viz({ Module, render });
      console.error(error);
    });
}