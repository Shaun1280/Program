//operating system 
const os= require('os');

//Platform
console.log(os.platform());

//Cpu  Arch itecture
console.log(os.arch());

//Cpu Core Info
console.log(os.cpus());

//Free memory
console.log(os.freemem()/(1024*1024*1024));

//Total memory
console.log(os.totalmem()/*/(1024*1024*1024)*/);

//Home directory
console.log(os.homedir());

//UPtime
console.log(os.uptime()/3600/24+'Day');
