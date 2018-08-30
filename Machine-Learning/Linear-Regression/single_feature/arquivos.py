def readtable(name):
	f = open(name, 'r')
	lines = f.readlines()
	result = []
	for x in lines:
		result.append(x)
	f.close()
	tabela = []
	for x in range(0,len(result)):
		mydata = list(filter(None, (result[x].strip()).split(" ") ))
		if (mydata):
			tabela.append(mydata)	
	return tabela

def grafico( a ):
	y=range(0,size(a))
	plot (y,a,"ro")
	xlabel('SAMPLE')
	ylabel('DATA')
	show()

def writefile(name,array):
	f = open(name, 'w')
	for item in array:
		f.write(str(item)+"\n")
	f.close()

def column(matrix, i):
    return [float(row[i]) for row in matrix]



