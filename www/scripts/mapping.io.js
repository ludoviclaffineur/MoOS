mapping = function(io){

	var nbrx = 1;
	var nbry = 1;
	originPosY = 100;
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
    document.getElementById('myForm').style.display = "none"

	initText.draw(io.context);

  	init();
	//cell1.draw(io.context);
	io.canvas.addEventListener('mousedown', function(event){
		var found = false;
		for (var i = Circles.length - 1; i >= 0; i--) {
				
			if(Circles[i].contains(io.getEventPosition(event))){
				document.getElementById('myForm').style.display = "block";
				document.getElementById('coeff').value = Circles[i].objs[0].text;
				var indice =Math.floor(i/InputNames.length);
				document.getElementById('output').value = OutputNames[indice].objs[0].text;
				document.getElementById('input').value = InputNames[i%InputNames.length].text;
				found = true;

			}
			
		}
		for (var i = OutputNames.length - 1; i >= 0; i--) {
			if(OutputNames[i].contains(io.getEventPosition(event))){
				getOutput(OutputNames[i].objs[0].text);
				var dc = document.getElementById('preamble').children[4];
				while( dc.hasChildNodes() ){
   			 		dc.removeChild(dc.lastChild);
				}

				var f = document.createElement("form");
				f.setAttribute('method',"post");
				f.setAttribute('action',"submit.php");

				var i = document.createElement("input"); //input element, text
				i.setAttribute('type',"text");
				i.setAttribute('name',"username");

				var s = document.createElement("input"); //input element, Submit button
				s.setAttribute('type',"button");
				s.setAttribute('onClick', "updateOutput()");
				s.setAttribute('value',"Submit");

				f.appendChild(i);
				f.appendChild(s);

//and some more input elements here
//and dont forget to add a submit button

				var dc = document.getElementById('preamble').children[4]; //output Form
				dc.appendChild(i);
				dc.appendChild(s);
			}
		};
		if (!found){
				document.getElementById('myForm').style.display = "none";
		}
		

	});
};



function init(){
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
		OutputNames[i] = new iio.Rect(43+(InputNames.length*40), originPosY +43 + (40*i), 80,20).setFillStyle('white').setStrokeStyle('white');
		OutputNames[i].addObj(new iio.Text( Ouputs[i].firstChild.nodeValue, 43+(InputNames.length*40), originPosY +43 + (40*i)).setFont('15px Consolas')
        	.setTextAlign('left')
            .setFillStyle('black'));
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
	refreshGraph();
	isInitialized=true;
}
