import matplotlib.pylab as plt
import numpy as np
dt=0.1
t=np.linspace(0,10000*dt,10000)
ode=np.genfromtxt("datosOde.dat",delimiter=",")


plt.figure()
plt.plot(ode[:,0])
plt.savefig("ode1.pdf")
plt.show()
print(ode[:5,0])
