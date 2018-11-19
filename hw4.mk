Resultados_hw4.pdf: resultados_hw4.tex 
	pdflatex Resultados_hw4.tex

resultados_hw4.tex: Plots_hw4.py 45grad.txt iniciales.txt
	python3 Plots_hw4.py

45grad.txt: ODE.cpp
	g++ ODE.cpp -o ODE.out
	./ODE.out

iniciales.txt: PDE.cpp	
	g++ PDE.cpp -o PDE.out
	./PDE.out
clean:
	rm *.out
	rm *.txt
	rm *.pdf
	rm *.log
	rm *.aux
