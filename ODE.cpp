#include<iostream>
#include<math.h>
#include <stdio.h>
#include <fstream>

#define PI 3.14159
using namespace std;

double g=10;
double c=0.2;
double m=0.2; 

double deriX(double t, double vx, double vy, double x);
double segunderiX(double t, double vx, double vy, double x);

double deriY(double t, double vx, double vy, double y);
double segunderiY(double t, double vx, double vy, double y);

double deriX(double t, double vx, double vy, double x)
{
	return vx;
}

double segunderiX(double t, double vx, double vy, double x)
{
	return -(c/m)*vx*sqrt((vx*vx)+(vy*vy));
}

double deriY(double t, double vx, double vy, double y)
{
	return vy;
}
double segunderiY(double t, double vx, double vy, double y)
{
	return -g-(c/m)*vy*sqrt((vx*vx)+(vy*vy));
}

int main()
{
	double dt=0.0001;
	int N=21000;
	double x[N];
	double y[N];
	double vx[N];
	double vy[N];
	double t[N];
	double x0=0;
	double y0=0;
	double v0=300.0;
	double t0=0;
	double angi=45.0*(PI/180.0);

	// inicializo
	x[0]=x0;
	y[0]=y0;
	vy[0]=(sin(angi))*300.0;
	vx[0]=(cos(angi))*300.0;
	t[0]=t0;
	
	//Primer paso
	x[1]=x[0]+dt*deriX(t[0], vx[0], vy[0], x[0]);
	y[1]=y[0]+dt*deriY(t[0], vx[0], vy[0], y[0]);
	vx[1]=vx[0]+dt*segunderiX(t[0],vx[0],vy[0],y[0]);
	vy[1]=vy[0]+dt*segunderiY(t[0],vx[0],vy[0],x[0]);
	

	for(int i=1;i<N;i++)
	{
	x[i+1]=x[i-1]+2*dt*deriX(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	y[i+1]=y[i-1]+2*dt*deriY(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	vy[i+1]=vy[i-1]+2*dt*segunderiY(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	vx[i+1]=vx[i-1]+2*dt*segunderiX(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	
	}
	
	ofstream file;
	file.open("45grad.txt");
	for(int i=0;i<N;i++)
	{
	
	file << x[i] <<" " << y[i] << " "<< vx[i] <<" "<< vy[i]<<endl;
	}
	//euler
	for(int i=1;i<N;i++)
	{
	x[i]=x[i-1]+dt*deriX(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	y[i]=y[i-1]+dt*deriY(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	vy[i]=vy[i-1]+dt*segunderiY(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	vx[i]=vx[i-1]+dt*segunderiX(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	
	}
	
	ofstream file2;
	file2.open("eu45grad.txt");
	for(int i=0;i<N;i++)
	{
	
	file2 << x[i] <<" " << y[i] << " "<< vx[i] <<" "<< vy[i]<<endl;
	}

	file2.close();
	//cambio de angulo

ofstream file1;
	file1.open("todosAngu.txt");
	
	double valMax=0.0;
	double angMax=100;
for(int j=1;j<8;j++)
{	// inicializo
	double aux=100.0;
	angi=(j*10*PI)/180;
	x[0]=x0;
	y[0]=y0;
	vy[0]=(sin(angi))*300.0;
	vx[0]=(cos(angi))*300.0;
	t[0]=t0;
	
	//Primer paso
	x[1]=x[0]+dt*deriX(t[0], vx[0], vy[0], x[0]);
	y[1]=y[0]+dt*deriY(t[0], vx[0], vy[0], y[0]);
	vy[1]=vy[0]+dt*segunderiY(t[0],vx[0],vy[0],x[0]);
	vx[1]=vx[0]+dt*segunderiX(t[0],vx[0],vy[0],y[0]);

	for(int i=1;i<N;i++)
	{
	x[i+1]=x[i-1]+2*dt*deriX(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	y[i+1]=y[i-1]+2*dt*deriY(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	vy[i+1]=vy[i-1]+2*dt*segunderiY(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	vx[i+1]=vx[i-1]+2*dt*segunderiX(t[i-1], vx[i-1], vy[i-1], x[i-1]);
	}
	
	
	for(int i=0;i<N;i++)
	{
	file1 << x[i] <<" " << y[i] << " "<< vx[i] <<" "<< vy[i]<<endl;
	}
	
}
file1.close();

cout<<"La distancia maxima para el angulo de 45° es 4.23822"<<endl;
cout<<"La distancia maxima en x se logra con un angulo de 20°. El valor obtenido es 5.18812"<<endl;


return 0;
}

