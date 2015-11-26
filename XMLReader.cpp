#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "convert.h"

using namespace rapidxml;
using namespace std;

int writeToTxt(string outName);
double* calcAverage (vector<xml_node<> > artNode_vec);

int main()
{
  /*  ofstream myFile;
  file<> xmlFile("BuenasNoches1.xml");
  xml_document<> doc;
  doc.parse<0>(xmlFile.data());*/
  //  writeToTxt("BuenasNoches1");
  writeToTxt("BuenasNoches2");
  writeToTxt("BuenasNoches3");
  writeToTxt("BuenosDias1");
  writeToTxt("BuenosDias2");
  writeToTxt("BuenosDias3");
  writeToTxt("BuenasTardes1");
  writeToTxt("BuenasTardes2");
  writeToTxt("BuenasTardes3");
  return 0;
}

int writeToTxt(string outName)
{

  int mScnds= 100;
  cout << "================================================================================";
  cout << "\nWriting to file = " << outName;
  file<> xmlFile((("GesturesXML/"+outName)+".xml").c_str());
  xml_document<> doc;
  doc.parse<0>(xmlFile.data());
  
  
  xml_node<> *pRoot = doc.first_node();
  //  cout << "Root node has value = " << pRoot->name();
  ofstream myFile;
  myFile.open((("txtFiles/"+outName)+".txt").c_str()); 
  myFile << "9 20 3\n";
  myFile << "\n";
  int i = 0;
  int movsPerMs = 0;
  double lastTime = 0;
  double startTime = 0;
  vector<xml_node<> > artNode_vec;
  for (xml_node<> *pNode = pRoot->first_node(); pNode; pNode=pNode->next_sibling())
    {
      //      cout << "\n Entering node "<< pNode->name();
      xml_attribute<> *attr= pNode->first_attribute();
      lastTime = convertToDouble(attr->value());
      if (i==0)
	{
	  startTime = convertToDouble(attr->value());
	}
      if (convertToDouble(attr->value()) <= lastTime + mScnds)
	{
	  double *crdAveragesArr =calcAverage(artNode_vec);
	   artNode_vec.clear();
	  
	  /*	  for (xml_node<> *artNode = movNode->first_node(); artNode; artNode = artNode->next_sibling())
	    {
	      //	      cout << "\n Entering node "<< artNode->name() << "value = " <<artNode->value();
	      //	      myFile << artNode->value() << "\t";
	      
	      }*/

	}
      for (xml_node<> *movNode = pNode->first_node(); movNode; movNode= movNode->next_sibling())
	{
	  artNode_vec.push_back(*movNode);
	  i++;
	  //	  cout << "\n Entering node "<< movNode->name();

	}
      //      cout << pNode->value()<< "\n";
      
    }
  myFile << "\n 1 0 0";
  myFile.close();
  cout << "================================================================================";
  cout << "\n writed to file = " << outName << i <<" coordinates";
  return 0;
}


double* calcAverage (vector<xml_node<> > artNode_vec)
{
  double sums[] ={0.0,0.0,0.0}; // index 0 = x, 1 = y , 2 = z


  for (int i =0; i<= artNode_vec.size();i++)
    {
      int j= 0;
      for (xml_node<> *coordNode = artNode_vec[i].first_node(); coordNode ; coordNode = coordNode->next_sibling())
	{
	  sums[j] += convertToDouble(coordNode->value());
	    j++;
	}

    }
  double result[] = {(double)sums[0]/artNode_vec.size(),(double)sums[1]/artNode_vec.size(),(double)sums[2]/artNode_vec.size()};
  return result;
}
