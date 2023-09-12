const fs = require('fs');
const path = require('path');

// //Create a folder
// fs.mkdir(path.join(__dirname, 'test'), {}, err => {
//     if (err) throw err;
//     console.log('Folder created...');
// });  //ctrl+/

// //Create and writr to file
// fs.writeFile(
//     path.join(__dirname, 'test', 'hello.txt'),
//     'Hello world! ',
//     err => {
//         if (err) throw err;
//         console.log('File writen to...');

//         //File append
//         fs.appendFile(
//             path.join(__dirname, 'test', 'hello.txt'),
//             'I love node.js!',
//             err => {
//                 if (err) throw err;
//                 console.log('File writen to...');
//             }
//         );
//         ////File append
//     }
// );

// //Read file
// fs.readFile(
//     path.join(__dirname, 'test','hello.txt'), 
//     'utf8', 
//     (err,data) => {
//         if (err) throw err;
//         console.log(data);
//     }
// ); 

//Rename file
fs.rename(
    path.join(__dirname, 'test','hello.txt'), //initial txt
    path.join(__dirname, 'test','helloworld.txt'), //target txt
    (err) => {
        if (err) throw err;
        console.log('File renamed...');
    }
); 
