#include <iostream>
#include <fstream>
#include <vector>
#include <rapidxml.h>

using namespace rapidxml;
using namespace std;


int main()
{
    xml_document<> doc;
    xml_node<> * root_node;

    ifstream theFile("impact51.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)),
                        istreambuf_iterator<char>());
    buffer.push_back('\0');

    doc.parse<0>(&buffer[0]);

    root_node = doc.first_node("annotation");
    cout << root_node->first_node("object")->first_node("bndbox")
        ->first_node("xmin")->value() << endl;

    /*
    for (xml_node<> *object_node = root_node->first_node("object");
         object_node;
         object_node = object_node->next_sibling()) {
        xml_node<> *bndbox_node = object_node->first_node("bndbox");
        int xmin = atoi(bndbox_node->first_node("xmin")->value());
        int xmax = atoi(bndbox_node->first_node("xmax")->value());
        int ymin = atoi(bndbox_node->first_node("ymin")->value());
        int ymax = atoi(bndbox_node->first_node("ymax")->value());

        cout << xmin << xmax << ymin << ymax << endl;
    }
    */
    return 0;
}

