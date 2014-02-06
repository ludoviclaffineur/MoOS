TicTacToe = function(io){

	var selectable = [];
	var nbrx = 2;
	var originPosY = 60;
	var grid = new iio.Grid(0,originPosY,nbrx,2,40).setStrokeStyle('black');
	//var grid = io.addObj(gridInCanvas);
	grid.draw(io.context);
	/*var cell1 = new iio.Text( '', 40, 42+originPosY).setFont('15px Consolas')
              .setTextAlign('center')
              .setFillStyle('black');*/
    var circles = new iio.Circle(40,40+originPosY,10).setFillStyle('white').setStrokeStyle('white');
    var InputName = new iio.Text( '', 40, originPosY -3).setFont('15px Consolas')
              .setTextAlign('left')
              .setFillStyle('black');

    InputName.rotate(-Math.PI/5);
    var OutputName = new iio.Text( '', 80+3, originPosY + 43).setFont('15px Consolas')
              .setTextAlign('left')
              .setFillStyle('black');


    circles.addObj(new iio.Text('').setFont('15px Consolas')
              .setTextAlign('center')
              .setFillStyle('black'));
    circles.draw(io.context);
	//cell1.draw(io.context);
	var xTurn = true;
	selectable[0]=io.addObj(circles);
	//selectable[1]=io.addObj(InputName);
	//selectable[2]=io.addObj(OutputName);
	//io.context.clearRect(0,0,io.width,io.height);
	//io.context.stroke();
	io.canvas.addEventListener('mousedown', function(event){
		io.draw();
		//grid.C++;

    	var name = getInputs();
    	grid.C = name.length + 1;
    	InputName.text = name[0].firstChild.nodeValue;
		document.getElementById('firstname').value=name[0].firstChild.nodeValue;
		var lname = getOutputs();
		grid.R = lname.length + 1;
		document.getElementById('lastname').value=lname[0].firstChild.nodeValue;
		OutputName.text = lname[0].firstChild.nodeValue;
		var mail = getCells()[0].children[2].firstChild.nodeValue;
		//document.getElementById('email').value=mail.firstChild;
		//alert(mail);
		circles.objs[0].text = mail;
		grid.draw(io.context);
		circles.draw(io.context);
		//cell1.draw(io.context);
		InputName.draw(io.context);
		OutputName.draw(io.context);
		for (var i = selectable.length - 1; i >= 0; i--) {
			if(selectable[i].contains(io.getEventPosition(event))){
				document.getElementById('email').value='HJK';
			}
		};
	});
};