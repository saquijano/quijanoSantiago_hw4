Resultados_hw4.pdf: resultados_hw4.tex
	pdflatex Resultados_hw4.tex

resultados_hw4.tex: Plots_hw4.py
	g++ PDE.cpp -o PDE.out
	./PDE.out
	g++ ODE.cpp -o ODE.out
	./ODE.out
	python3 Plots_hw4.py

clean:
	rm *.txt
	rm *.pdf
