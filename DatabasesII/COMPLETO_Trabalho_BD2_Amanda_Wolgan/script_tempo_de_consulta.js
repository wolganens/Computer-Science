//Precisa do NodeJS para executar o script, passar arquivo de saida do plano como parametro, ex:
//node script_tempo_de_consulta.js c1t1.txt
const fs = require('fs');
fs.readFile(process.argv[2], (err, data) => {
	if (err) throw err;	
	var array = data.toString().match(/Execution time: (\d+.\d+) ms/g);
	var i = 0 ;
	var total  = 0;

	Array.prototype.max = function() {
		return Math.max.apply(null, this);
	};

	Array.prototype.min = function() {
		return Math.min.apply(null, this);
	};
	
	for (i = 0 ; i < 100 ; i++){
		array[i] = (parseFloat(array[i].replace(/(Execution time:\s*)|(\s*ms(\s\t)*)/g, '')));				
	}

	var minVal = array.min();
	var maxVal = array.max()

	var n = array.length;
	for (i = 0 ; i < n ; i++){
		if(array[i] == minVal || array[i] == maxVal){
			array.splice(i, 1);
		}		
	}
	n = array.length;
	for (i = 0 ; i < n ; i++){
		total = (total * 10 + array[i] * 10)/10;
	}
	console.log((total/n).toFixed(3));
});
