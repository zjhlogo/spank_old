/*!
 * \file main.cpp
 * \date 16-08-2011 20:28:08
 * 
 * 
 * \author ??
 */
#include <iostream>
#include <sstream>
#include "../L2DConvert/L2DConvert.h"

template<class out_type,class in_value>
out_type translate(const in_value & t)
{
	stringstream stream;
	stream<<t;
	out_type result;
	stream>>result;
	return result;
}

int main(int agrc, char** argv)
{
	char* pszXmlFileName =NULL;
	char* pszL2DFileName = NULL;
	uint nDefaultTile = 0;
	switch(agrc)
	{
	case 4:
		pszL2DFileName = argv[3];
		nDefaultTile = translate<int>(argv[2]);
		pszXmlFileName = argv[1];
		break;
	case 3:
		pszL2DFileName = "OUT.l2d";
		nDefaultTile = translate<int>(argv[2]);
		pszXmlFileName = argv[1];
		break;
	case 2:
		pszL2DFileName = "OUT.l2d";
		nDefaultTile = 0;
		pszXmlFileName = argv[1];
		break;
	case 1:
		cout<<"NO XML File"<<endl;
		break;
	}
	L2DConvert::GetInstance().CreateL2DFile(pszXmlFileName, nDefaultTile, pszL2DFileName);
	system("pause");
	
}
