var express=require('express')
//var ejs = require('ejs')
var fs =require('fs')
var app=express()
var bodyParser=require('body-parser')

var SerialPort= require('serialport')
	
var serial = new SerialPort("/dev/ttyACM1",{
	baudRate: 115200,
	dataBits :8,
	parity : 'none',
	stopBits: 1,
	flowControl: false,
	parser: new SerialPort.parsers.Readline("\n")
});
//app.set("view engine", "ejs");
app.use(express.static('/home/pi/Desktop/HomeTask'))
function getRandomInt(min, max) { //min ~ max 사이의 임의의 정수 반환
    return Math.floor(Math.random() * (max - min)) + min;
}
var random_number = getRandomInt(0,1000)
var cameraOptions={
	width: 600,
	height: 420,
	mode: 'photo',
	awb:'off',
	encoding:'jpg',
	output:'images/camera'+random_number+'.jpg',
	q:50,
	timeout:100,
	timelapse:0,
	nopreview: true,
	th: '0:0:0'
}
var camera=new require('raspicam')(cameraOptions)
//camera.stop();
//camera.start();
//camera.stop();
camera.on("exit", function(){
	camera.stop()
	console.log("camera stop")
	//res.redirect('/main')
	//camera.start()
})
camera.on('read',function(){})

//	serial.write('l#new#\n',function(err,data){
//		if(err){
//			console.log('err: '+err.message)
//		}
//		else{
//			//console.log('f written')
//			console.log('msg written: '+data)
//		}
//	})
//})
serial.on('error',function(err){
	console.log('err on read: ',err.message)
})


serial.on('open',function(){
	console.log('serial open')
})
port=3000
//app.use(express.static('/home/pi/Desktop/HomeTask/images'))
app.use(bodyParser.urlencoded({
	extended:false
}))
app.locals.pretty=true
app.set('views','./view_file')
app.set('view engine','pug')
app.listen(port,() => {
	console.log("Server has been started")
})


app.get("/",function(req,res){
	res.redirect('/main')
})


app.get('/main',function(req,res){
	
	fs.readFile('main.html','utf8',function(err,data){
		if(err){
			console.log(err)
		}
		else{
			res.send(data)
		}
	})
	//res.render('main',{image:'camera'+random_number+'.jpg'})
})
//app.post('/main',function(req,res){
//	res.send(req.body.lcd)
//})


app.post('/shot',function(req,res){
	random_number = 0
	cameraOptions={
		width: 600,
		height: 420,
		mode: 'photo',
		awb:'off',
		encoding:'jpg',
		output:'images/camera'+random_number+'.jpg',
		q:50,
		timeout:1,
		timelapse:0,
		nopreview: true,
		th: '0:0:0'
	}
	camera=new require('raspicam')(cameraOptions)
	camera.start()
	str = 'p%'
	serial.write(str,function(err,data){
			if(err){
				console.log(err)

			}	
			else{
				console.log('write data: '+data)
			}	
	})
	res.redirect('/main')
})
app.post('/seg',function(req,res){
	var str='s%'+req.body.seg+'%'
	serial.write(str,function(err,data){
		if(err){
			console.log(err)
		}
		else{
			console.log('write data: '+data)
		}
	})
})
app.post('/lcd',function(req,res){
	//res.send(req.body.lcd)
	var str='l%'+req.body.lcd+'%'
	serial.write(str,function(err,data){
		if(err){
			console.log(err)

		}
		else{
			console.log('write data: '+data)
		}	
	})
})

app.get('/imgs',function(req,res){
	fs.readFile('/home/pi/Desktop/HomeTask/images/camera'+random_number+'.jpg',function(err,data){
		res.writeHead(200,{'Content-Type': 'text/html'});
		res.end(data);
	//fs.readFile('CameraResult.html','utf8',function(err,data){
		//if(err){
		//	console.log(err)
	//	}
	//	else{
	//		res.send(data)
	//	}
	});
});




serial.on('error',function(err){
	console.log('err on read: ',err.message)
})

