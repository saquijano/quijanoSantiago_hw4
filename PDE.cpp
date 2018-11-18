#include<iostream>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;
int main()
{	
	double k=1.62;
	double Cp=820;
	double rho=0.00000271;
	
	int N=100;
	double n=100.0;
	double dx=50.0/n;
	double dy=dx;
	double disx=0;
	double disy=0;
	double centro=(n*dx)/2.0;
	//double dt=(dx*0.5)/nu;
	double dt=0.00003;
	double nu=(k*dt)/(dx*dx*Cp*rho); //condicion se saco del libro, sin esto estaba fallando muuuucho
	//double cons=(nu*dt)/(dx);
	double pasa[N][N];
	double futu[N][N];
	double ver=0;
	double hor=0;
	double ver1=0;
	double hor1=0;
	double prom=0;
	cout<<","<<nu<<","<<dx<<endl;
	int saltos=30000;
	double prome[saltos];
	//condiciones iniciales

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			disx=((i*dx)-centro)*((i*dx)-centro);
			disy=((j*dy)-centro)*((j*dy)-centro);
			if(sqrt(disx+disy)<5)
			{
				pasa[i][j]=100;
			}
			else
			{
				pasa[i][j]=10;
			}
		}
	}

	// cerrado
	ofstream iniciales;
	iniciales.open("iniciales.txt");
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			iniciales<<pasa[i][j]<<",";
			if(j==(N-1))
			{
				iniciales<<pasa[i][j]<<endl;
			}
		}
	}
	iniciales.close();
	
	double tiempo=0;
	int z=0;
	//limites cerrados
while(tiempo<(saltos*dt))
{
	double prom=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			disx=((i*dx)-centro)*((i*dx)-centro);
			disy=((j*dy)-centro)*((j*dy)-centro);
			if(i==0||i==(N-1)||j==0||j==(N-1))
			{
				pasa[i][j]=10;
				futu[i][j]=pasa[i][j];
			}
			else if(sqrt(disx+disy)<5)
			{
				pasa[i][j]=100;
				futu[i][j]=pasa[i][j];
			}
			else
			{
				hor=(pasa[i+1][j]+pasa[i-1][j]-2.0*pasa[i][j]);
				ver=(pasa[i][j+1]+pasa[i][j-1]-2.0*pasa[i][j]);
				futu[i][j]=pasa[i][j]+nu*(hor+ver);
			}
		}
	}
	
	
	//doy paso en el tiempo
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{	
			prom=prom+pasa[i][j];
			pasa[i][j]=futu[i][j];
		}
	}
	
	prome[z]=(prom/(n*n));
	//cout<<prome[z]<<endl;
	tiempo=tiempo+dt;
	z=z+1;
	if (z==2500)
	{
		ofstream cerradas1;
		cerradas1.open("cerradas1.txt");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				cerradas1<<pasa[i][j]<<", ";
				if(j==(N-1))
				{
					cerradas1<<pasa[i][j]<<endl;
				}
			}
		}
		cerradas1.close();
	}

	if (z==(saltos-5))
	{
		ofstream cerradas2;
		cerradas2.open("cerradas2.txt");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				cerradas2<<pasa[i][j]<<", ";
				if(j==(N-1))
				{
					cerradas2<<pasa[i][j]<<endl;
				}
			}
		}
		cerradas2.close();
	}
}
	ofstream promFijos;
	promFijos.open("promFijos.txt");
		for(int i=0;i<saltos;i++)
		{
			promFijos<<prome[i]<<endl;
		}
		promFijos.close();
//-------------------------------------------------------------------------------------
	// extremos libres
	//regreso a situacion original
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			disx=((i*dx)-centro)*((i*dx)-centro);
			disy=((j*dy)-centro)*((j*dy)-centro);
			if(sqrt(disx+disy)<5)
			{
				pasa[i][j]=100;
			}
			else
			{
				pasa[i][j]=10;
			}
		}
	}

	tiempo=0;
	z=0;
while(tiempo<(saltos*dt))
{
	double prom=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			disx=((i*dx)-centro)*((i*dx)-centro);
			disy=((j*dy)-centro)*((j*dy)-centro);
			if(i==0)
			{
				pasa[i][j]=pasa[i+1][j];
				futu[i][j]=pasa[i][j];
			}
			else if(i==(N-1))
			{
				pasa[i][j]=pasa[i-1][j];
				futu[i][j]=pasa[i][j];
			}
			else if(j==0)
			{
				pasa[i][j]=pasa[i][j+1];
				futu[i][j]=pasa[i][j];
			}
			else if(j==(N-1))
			{
				pasa[i][j]=pasa[i][j-1];
				futu[i][j]=pasa[i][j];
			}
			else if(sqrt(disx+disy)<5)
			{
				pasa[i][j]=100;
				futu[i][j]=pasa[i][j];
			}
			else
			{
				hor=(pasa[i+1][j]+pasa[i-1][j]-2.0*pasa[i][j]);
				ver=(pasa[i][j+1]+pasa[i][j-1]-2.0*pasa[i][j]);
				futu[i][j]=pasa[i][j]+nu*(hor+ver);
			}
		}
	}
	
	//doy paso en el tiempo
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			prom=prom+pasa[i][j];
			pasa[i][j]=futu[i][j];
		}
	}
	prome[z]=prom/(n*n);
	cout<<prome[z]<<endl;
	tiempo=tiempo+dt;
	z=z+1;
	if (z==8000)
	{
		ofstream libres1;
		libres1.open("libres1.txt");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				libres1<<pasa[i][j]<<", ";
				if(j==(N-1))
				{
					libres1<<pasa[i][j]<<endl;
				}
			}
		}
		libres1.close();
	}

	if (z==(saltos-5))
	{
		ofstream libres2;
		libres2.open("libres2.txt");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				libres2<<pasa[i][j]<<", ";
				if(j==(N-1))
				{
					libres2<<pasa[i][j]<<endl;
				}
			}
		}
		libres2.close();
	}
}
/// guardo mis promedios en un txt
	ofstream promLibres;
		promLibres.open("promLibres.txt");
		for(int i=0;i<saltos;i++)
		{
			promLibres<<prome[i]<<endl;
		}
		promLibres.close();
//-------------------------------------------------------------------------------------
	//situacion periodica
	//regreso a situacion original
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			disx=((i*dx)-centro)*((i*dx)-centro);
			disy=((j*dy)-centro)*((j*dy)-centro);
			if(sqrt(disx+disy)<5)
			{
				pasa[i][j]=100;
			}
			else
			{
				pasa[i][j]=10;
			}
		}
	}

	tiempo=0;
	z=0;
while(tiempo<(saltos*dt))
{
	double prom=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			disx=((i*dx)-centro)*((i*dx)-centro);
			disy=((j*dy)-centro)*((j*dy)-centro);
			if(i==0)
			{
				pasa[i][j]=pasa[i+N-2][j];
				futu[i][j]=pasa[i][j];
			}
			else if(i==(N-1))
			{
				pasa[i][j]=pasa[i-N+2][j];
				futu[i][j]=pasa[i][j];
			}
			else if(j==0)
			{
				pasa[i][j]=pasa[i][j+N-2];
				futu[i][j]=pasa[i][j];
			}
			else if(j==(N-1))
			{
				pasa[i][j]=pasa[i][j-N+2];
				futu[i][j]=pasa[i][j];
			}
			else if(sqrt(disx+disy)<5)
			{
				pasa[i][j]=100;
				futu[i][j]=pasa[i][j];
			}
			else
			{
				hor=(pasa[i+1][j]+pasa[i-1][j]-2.0*pasa[i][j]);
				ver=(pasa[i][j+1]+pasa[i][j-1]-2.0*pasa[i][j]);
				futu[i][j]=pasa[i][j]+nu*(hor+ver);
			}
		}
	}
	
	//doy paso en el tiempo
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{	
			prom=prom+pasa[i][j];
			pasa[i][j]=futu[i][j];
		}
	}
	prome[z]=prom/(n*n);
	cout<<prome[z]<<endl;
	tiempo=tiempo+dt;
	z=z+1;
	if (z==8000)
	{
		ofstream periodica1;
		periodica1.open("periodica1.txt");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				periodica1<<pasa[i][j]<<", ";
				if(j==(N-1))
				{
					periodica1<<pasa[i][j]<<endl;
				}
			}
		}
		periodica1.close();
	}

	if (z==(saltos-5))
	{
		ofstream periodica2;
		periodica2.open("periodica2.txt");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				periodica2<<pasa[i][j]<<", ";
				if(j==(N-1))
				{
					periodica2<<pasa[i][j]<<endl;
				}
			}
		}
		periodica2.close();
	}
}
/// guardo mis promedios en un txt
	ofstream promPeriodica;
		promPeriodica.open("promPeriodica.txt");
		for(int i=0;i<saltos;i++)
		{
			promPeriodica<<prome[i]<<endl;
		}
		promPeriodica.close();
/*	
*/
return 0;
}
