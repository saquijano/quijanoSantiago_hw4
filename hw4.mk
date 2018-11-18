Resultados_hw4.pdf: traye45.pdf iniciales.pdf resultados_hw4.tex
	pdflatex Resultados_hw4.tex

traye45.pdf: 45grad.txt  Plots_hw4.py
	python3 Plots_hw4.py

resultados_hw4.tex: traye45.pdf

45grad.txt: ODE.cpp
	g++ ODE.cpp -o ODE.out
	./ODE.out

iniciales.pdf: iniciales.txt Plots_hw4.py
	python3 Plots_hw4.py

iniciales.txt: PDE.cpp
	g++ PDE.cpp -o PDE.out
	./PDE.out
clean:
	rm *.txt
	rm *.pdf
