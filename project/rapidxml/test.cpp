//#include <string.h>
//#include <stdio.h>
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

    ifstream theFile("beerJournal.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)),
                        istreambuf_iterator<char>());
    buffer.push_back('\0');

    doc.parse<0>(&buffer[0]);

    root_node = doc.first_node("MyBeerJournal");

    for (xml_node<> *brewery_node = root_node->first_node("Brewery");
         brewery_node;
         brewery_node = brewery_node->next_sibling()) {
        printf("I have visited %s in %s. ",
               brewery_node->first_attribute("name")->value(),
               brewery_node->first_attribute("location")->value());

        for (xml_node<> *beer_node = brewery_node->first_node("Beer");
             beer_node;
             beer_node = beer_node->next_sibling()) {
            printf("On %s, I tried their %s which is a %s. ",
                   beer_node->first_attribute("dateSampled")->value(),
                   beer_node->first_attribute("name")->value(),
                   beer_node->first_attribute("description")->value());
            printf("I gave it the following review: %s", beer_node->value());
        }
        cout << endl;
    }
    return 0;
}
