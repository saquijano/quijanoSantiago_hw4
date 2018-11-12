resultados_hw4.pdf: ode1.pdf ode2.pdf pde1.pdf resultados_hw4.tex
	pdflatex resultados.tex

ode1.pdf: datosOde.dat Plots_hw4.py
	python3 Plots_hw4.py

ode2.pdf: datosOde.dat Plots_hw4.py
	python3 Plots_hw4.py

datosOde.dat: ODE.cpp
	g++ ODE.cpp -o ODE.out
	./ODE.out>>datosOde.dat

pde.pdf: datosPDE.dat Plots_hw4.py
	python3 Plots_hw4.py

datosPde.dat: PDE.cpp
	g++ PDE.cpp -o PDE.out
	./PDE.out>>datosPde.dat
