mapping = function(io){

	var nbrx = 1;
	var nbry = 1;
	var originPosY = 100;
	context = io.context;
	oio = io;
	// init io.rmvObj
	grid = new iio.Grid(0,originPosY,nbrx,nbry,40).setStrokeStyle('black');
	grid.draw(io.context);
    var circles = new iio.Circle(40,40+originPosY,10).setFillStyle('white').setStrokeStyle('white');
    var initText = new iio.Text( 'Click to refresh', 40, originPosY -3).setFont('15px Consolas')
              .setTextAlign('left')
              .setFillStyle('black');

   
    OutputNames = [];
    InputNames = [];
    Circles = [];


	initText.draw(io.context);

  
	//cell1.draw(io.context);
	var isInitialized = false;
	io.canvas.addEventListener('mousedown', function(event){
		if(isInitialized==false){

			var Inputs = getInputs();
    		grid.C = Inputs.length + 1;
    		for (var i = Inputs.length - 1; i >= 0; i--) {
    			InputNames[i] = new iio.Text( Inputs[i].firstChild.nodeValue, 40+(i*40), originPosY -3).setFont('15px Consolas')
              		.setTextAlign('left')
              		.setFillStyle('black');
              	InputNames[i].rotate(-Math.PI/5);
    		};
    		
			//document.getElementById('firstname').value=name[0].firstChild.nodeValue;
			var Ouputs = getOutputs();
			grid.R = Ouputs.length + 1;
			//document.getElementById('lastname').value=lname[0].firstChild.nodeValue;
			for (var i = Ouputs.length - 1; i >= 0; i--) {
				OutputNames[i] = new iio.Text( Ouputs[i].firstChild.nodeValue, 43+(InputNames.length*40), originPosY +43 + (40*i)).setFont('15px Consolas')
              		.setTextAlign('left')
              		.setFillStyle('black');
			};
			//OutputName.text = Ouputs[0].firstChild.nodeValue;
			var Cells = getCells();

			for (var i = Cells.length - 1; i >= 0; i--) {
				var cInputName = Cells[i].children[0].firstChild.nodeValue;
				var cOuputName = Cells[i].children[1].firstChild.nodeValue;

				var cInputId = idFromInputName(InputNames, cInputName);
				var cOutputId = idFromOutputName(OutputNames, cOuputName);


				Circles[cOutputId*InputNames.length+cInputId] = new iio.Circle(40*cInputId+40,43+originPosY + (40*cOutputId),15).setFillStyle('white').setStrokeStyle('white');
				Circles[cOutputId*InputNames.length+cInputId].addObj(new iio.Text(Cells[i].children[2].firstChild.nodeValue)
					.setFont('15px Consolas')
              		.setTextAlign('center')
              		.setFillStyle('black'));
				//Circles[i].addObj(cInputId);
				//Circles[i].addObj(cOutputId);
			};
			document.getElementById('ttt').width = grid.C * 40 + 100;
			document.getElementById('ttt').height = grid.R * 40 + 120;
			var CellsNames = Cells[0].children[2].firstChild.nodeValue;

			io.draw();
			grid.draw(io.context);
			//cell1.draw(io.context);
			for (var i = Inputs.length - 1; i >= 0; i--) {
    			InputNames[i].draw(io.context);
    		};
			//InputName.draw(io.context);
			for (var i = Ouputs.length - 1; i >= 0; i--) {
				OutputNames[i].draw(io.context);
			}
			for (var i = Cells.length - 1; i >= 0; i--) {
				Circles[i].draw(io.context);
			};
			isInitialized=true;
		}
		else{
			for (var i = Circles.length - 1; i >= 0; i--) {
				if(Circles[i].contains(io.getEventPosition(event))){
					document.getElementById('coeff').value = Circles[i].objs[0].text;
					var indice =Math.floor(i/InputNames.length);
					document.getElementById('output').value = OutputNames[indice].text;
					document.getElementById('input').value = InputNames[i%InputNames.length].text;
				}
			};
		}
		

	});
};
