def abre_arquivo(caminho):
	fin = open(caminho, "ra") # ra = read-only + ascii
	return fin.readlines ()


def build_powerC_tab(lines):
	elem = None
	tabC = {}
	for line in lines:
		if len(line.strip()) > 0:
			elem = line.split()	
			tabC[elem[0]] = int(elem[1])

	return tabC


linhas = abre_arquivo("powerC.mod")

tabC = build_powerC_tab(linhas)

print tabC
