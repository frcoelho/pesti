fl = open("table_t.txt", "ra")
flres = open("matriz.txt", "wa")

lines = fl.readlines()

for line in lines:
	lstr = line.strip().split("\t")[1:]
	lmatrix= "{"
	for elem in lstr:
		lmatrix = lmatrix + elem + ","

	lmatrix = lmatrix[0:len(lmatrix)-1] + "} ,"
	flres.write(lmatrix)
	flres.write("\n")

fl.close()
flres.close()
	
