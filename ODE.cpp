#include <iostream>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159
using namespace std;

double g=10;
double c=0.2;
double m=0.2;
double dt=0.01;


double deri(double t,double x, double v);
//double dydx(double x,double y);
double segundaDeri(double t,double x,double v);
//void metodo(double *x, double *y, double h);
double leap();

double deri(double t, double x, double v)
{
	return sqrt(c)*v;
}

double segunDeri(double t, double x, double v)
{
	return -g-(pow(v,3)/abs(v));
}


int main()
{
	int N=10000;
	double xar[N];
	double v[N];
	double yar[N];
	double x0=0;
	double y0=0;
	double v0=300.0;
	double ang0=(45*PI/180);
	
	xar[0]=x0;
	yar[0]=y0;
	v[0]=300.0;

	//primer paso euler 

for(int i=0;i<100;i++){
	if(i==0)
	{
		xar[0]=0.0;
		yar[0]=0.0;
		v[0]=300.0;
	}
	xar[i]=xar[i-1]+dt*cos(ang0)*abs(deri(dt,xar[i-1],v[i-1]));
	/*yar[i]=yar[i-1]+dt*cos(ang0)*deri(dt,x0,v0)+dt*dt*segunDeri(dt,xar[i-1],v[i-1]);
	v[i]=v[i-1]+dt*segunDeri(dt,xar[i-1],v[i-1]);
cout<<xar[i]<<","<<yar[i]<<","<<v[i]<<endl;
	*/cout<<xar[0]<<","<<yar[0]<<","<<v[0]<<endl;
}
/*
for(int i=1;i<100-1;i++){
	xar[1]=xar[0]+dt*cos(ang0)*abs(deri(dt,x0,v0));
	yar[1]=yar[0]+dt*cos(ang0)*deri(dt,x0,v0)+dt*dt*segunDeri(dt,y0,v0);
	v[1]=v[0]+dt*segunDeri(dt,x0,v0);
cout<<xar[0]<<","<<yar[0]<<","<<v[0]<<endl;
	cout<<xar[1]<<","<<yar[1]<<","<<v[1]<<endl;
}
	//primer paso velo
	
	cout<<xar[0]<<","<<yar[0]<<","<<v[0]<<endl;
	cout<<xar[1]<<","<<yar[1]<<","<<v[1]<<endl;

	//todo lo demas con leap
	/*for(int i=1;i<100-1;i++)
	{
			xar[i+1]=xar[i-1]+2*dt*cos(ang0)*abs(deri(i*dt,xar[i],v[i]));

			yar[i+1]=yar[i-1]+2*dt*cos(ang0)*deri(i*dt,yar[i],v[i])+dt*dt*segunDeri(dt,xar[i],v[i]);

			v[i+1]=v[i-1]+v[i]+dt*segunDeri(dt,xar[i],v[i]);
		cout<<xar[i]<<","<<yar[i]<<","<<v[i]<<endl;
	}*/
	



return 0;
}
