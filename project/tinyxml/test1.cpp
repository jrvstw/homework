#include <iostream>
#include <fstream>
#include <string>
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;

int main()
{
    TiXmlDocument doc("impact51.xml");
    //doc.LoadFile();
    //string input = "../xml/impact51.xml";
    //TiXmlDocument xmlDoc(input.c_str());
    //TiXmlDocument xmlDoc("../xml/impact51.xml");
    //TiXmlDocument *xmlDoc = new TiXmlDocument();
    cout << "Hello!\n" << endl;
    return 0;
}

