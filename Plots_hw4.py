import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D


##ODE
dato45=np.genfromtxt("45grad.txt")

x=dato45[:,0]
y=dato45[:,1]
vx=dato45[:,2]
vy=dato45[:,3]


aux1=10
valor45=0
for j in range(1000,len(x)):
	if(abs(y[j])<aux1):
		aux1=y[j]
		valor45=x[j]


plt.figure()
plt.plot(x,y,label="45")
plt.title("Trayectoria a 45°")
plt.ylabel("y (m)")
plt.xlabel("x (m)")
plt.legend()
plt.ylim(0,5)
plt.savefig("traye45.pdf")



eudato45=np.genfromtxt("eu45grad.txt")
### probe con euler, da igual pero es mas estable
##tengo algun error que hace que las velocidades bajen y vuelvan a subir
eux=eudato45[:,0]
euy=eudato45[:,1]
euvx=eudato45[:,2]
euvy=eudato45[:,3]

angulosx=["x10","x20","x30","x40","x50","x60","x70"]
angulosy=["y10","y20","y30","y40","y50","y60","y70"]
ang=[10,20,30,40,50,60,70]



todosAng=np.genfromtxt("todosAngu.txt")

N=int(np.shape(todosAng)[0]/len(angulosx))

plt.figure()
for i in range(len(angulosx)):
	angulosx[i]=todosAng[i*N:(i+1)*N,0]
	angulosy[i]=todosAng[i*N:(i+1)*N,1]
	plt.plot(angulosx[i],angulosy[i],label=10*(i+1))
plt.plot(x,y,label="45")
plt.ylim(0,5)
plt.title("Trayectorias del proyectil a diferentes angulos")
plt.ylabel("y (m)")
plt.xlabel("x (m)")
plt.legend()
plt.savefig("trayecTodas.pdf")


valorMax=np.linspace(10,100,7)

#con esta funcion saque los valores maximos en x, los inserte en c++
for i in range(len(angulosx)):
	aux=100
	for j in range(1000,N):
		if(abs(angulosy[i][j])<aux):
			aux=angulosy[i][j]
			valorMax[i]=angulosx[i][j]

###inicia PDE

#iniciales de fijos

## como graficar en 3d lo saque de https://www.youtube.com/watch?v=N5k05yuEw-0

iniciales=np.genfromtxt("iniciales.txt",delimiter=",")
dis=np.shape(iniciales)
yo=np.linspace(0,50,dis[0])
xo=np.linspace(0,50,dis[1])
xo, yo=np.meshgrid(xo,yo)
fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,iniciales)

plt.title("Condiciones iniciales")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
ax.set_zlim(0,100)
plt.savefig("iniciales.pdf")


#iniciales libres
inicialesLib=np.genfromtxt("inicialesLib.txt",delimiter=",")

dis=np.shape(inicialesLib)
yo=np.linspace(0,50,dis[0])
xo=np.linspace(0,50,dis[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,inicialesLib)

plt.title("Condiciones iniciales extremos libres")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
ax.set_zlim(0,100)
plt.savefig("inicialesLib.pdf")

#iniciales periodicos
inicialesPer=np.genfromtxt("inicialesPer.txt",delimiter=",")

dis=np.shape(inicialesPer)
yo=np.linspace(0,50,dis[0])
xo=np.linspace(0,50,dis[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,inicialesPer)

plt.title("Condiciones iniciales placa periodica")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
ax.set_zlim(0,100)
plt.savefig("inicialesPer.pdf")
##extremos fijos1
cerrada1=np.genfromtxt("cerradas1.txt",delimiter=",")
yo=np.linspace(0,50,np.shape(cerrada1)[0])
xo=np.linspace(0,50,np.shape(cerrada1)[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,cerrada1)
plt.title("Primer instante extremos fijos")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
ax.set_zlim(0,100)
plt.savefig("fijos1.pdf")


##extremos fijos2
cerrada2=np.genfromtxt("cerradas2.txt",delimiter=",")

yo=np.linspace(0,50,np.shape(cerrada2)[0])
xo=np.linspace(0,50,np.shape(cerrada2)[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,cerrada2)
ax.set_zlim(0,100)
plt.title("Segundo instante extremos fijos")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
plt.savefig("fijos2.pdf")


##extremos fijos final
cerradasFin=np.genfromtxt("cerradasFin.txt",delimiter=",")

yo=np.linspace(0,50,np.shape(cerradasFin)[0])
xo=np.linspace(0,50,np.shape(cerradasFin)[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,cerradasFin)
ax.set_zlim(0,100)
plt.title("Condicion final extremos fijos")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
plt.savefig("cerradasFin.pdf")
##extremos libres 1
libres1=np.genfromtxt("libres1.txt",delimiter=",")
yo=np.linspace(0,50,np.shape(libres1)[0])
xo=np.linspace(0,50,np.shape(libres1)[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,libres1)
ax.set_zlim(0,100)
plt.title("Primer instante extremos libres")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
plt.savefig("libres1.pdf")

##extremos libres2
libres2=np.genfromtxt("libres2.txt",delimiter=",")

yo=np.linspace(0,50,np.shape(libres2)[0])
xo=np.linspace(0,50,np.shape(libres2)[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,libres2)
ax.set_zlim(0,100)
plt.title("Segundo instante extremos libres")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
plt.savefig("libres2.pdf")

##extremos libres final
libresFin=np.genfromtxt("libresFin.txt",delimiter=",")

yo=np.linspace(0,50,np.shape(libresFin)[0])
xo=np.linspace(0,50,np.shape(libresFin)[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,libresFin)
ax.set_zlim(0,100)
plt.title("Condicion final extremos libres")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
plt.savefig("libresFin.pdf")

##extremos periodicos 1
periodica1=np.genfromtxt("periodica1.txt",delimiter=",")
yo=np.linspace(0,50,np.shape(periodica1)[0])
xo=np.linspace(0,50,np.shape(periodica1)[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,periodica1)

plt.title("Primer instante placa periodica")
ax.set_zlim(0,100)
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("T(C°)")
plt.savefig("periodica1.pdf")

##extremos periodicos 2
periodica2=np.genfromtxt("periodica2.txt",delimiter=",")

yo=np.linspace(0,50,np.shape(periodica2)[0])
xo=np.linspace(0,50,np.shape(periodica2)[1])
xo, yo=np.meshgrid(xo,yo)

fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,periodica2)

plt.title("Segundo instante placa periodica")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlim(0,100)
ax.set_zlabel("T(C°)")
plt.savefig("periodica2.pdf")

##condicion final placa periodica

periodicaFin=np.genfromtxt("periodicaFin.txt",delimiter=",")

yo=np.linspace(0,50,np.shape(periodicaFin)[0])
xo=np.linspace(0,50,np.shape(periodicaFin)[1])
xo, yo=np.meshgrid(xo,yo)
fig=plt.figure()
ax=fig.add_subplot(1,1,1, projection='3d')
ax.plot_wireframe(xo,yo,periodicaFin)

plt.title("Estado final placa periodica")
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlim(0,100)
ax.set_zlabel("T(C°)")
plt.savefig("periodicaFin.pdf")

#### graficas de los promedios de temperatura

promFijos=np.genfromtxt("promFijos.txt")
promLibres=np.genfromtxt("promLibres.txt")
promPeriodica=np.genfromtxt("promPeriodica.txt")
dt1=0.00003
tiem=np.linspace(0,dt1*len(promFijos),len(promFijos))

plt.figure()
plt.plot(tiem,promFijos,label="Extremos fijos")
plt.plot(tiem,promLibres,label="Extremos libres")
plt.plot(tiem,promPeriodica,label="Placa periodica")
plt.title("Temperatura promedio de la placa")
plt.legend()
plt.xlabel("t(seg)")
plt.ylabel("T(C°)")
plt.savefig("TempPromedio.pdf")
#plt.show()

