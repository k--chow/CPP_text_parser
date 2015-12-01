//get all CAPS based on 3 capital letters
//save all the categories to the prefix
//save to hashmap, if multiple use linkedlist
//also save each to array, if duplicated, dont add
//run through array of prefixes, run through each of its categories through linked list
//match it to new file - save each link to new hashmap of prefixes
//run for loop - else if for each prefix - output its linkedlist of crap

//ignore all spaces parse
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

void getPrefixes(string& line, std::map<string, vector<string> >& prefixes)
{
    int itr= 0;
        int pCount = 0;
        int tCount = 0;
        string pref = "";
        string p;
        string type = "";
        //bool pFound = false;
        bool tFound = false;
        for(itr = 0; itr<line.size(); itr++)
        {
            if (line[itr] == '>' && !tFound)
            {
                //possible type
                int tItr = itr;
                tItr++;
                while (line[tItr] != '<')
                {
                    if (!isspace(line[tItr]))
                    {
                    type+=line[tItr];
                    }
                    tItr++;
                }

                if (tItr-itr > 4)
                {
                    tFound = true;
                    //cout << "t Found!" << endl;
                }
                else
                {
                    type = "";
                    //cout << "t Not found!" << endl;
                }
            }

            if(isupper(line[itr]))//append to pref
            {
                pCount++;
                pref+=line[itr];
                if (pCount == 3)
                {
                    p = pref;
                    //cout << "Found p!" << endl;
                }
            }
            else
            {
                pCount = 0;
                pref="";
            }




            if (tFound)
            {
                //cout << "Found" << endl;
                //prefixes.insert(pair<string, string>(p, type));
                prefixes[p].push_back(type);
                break;
            }
        }

}

void getLinks(string& line, std::map<string, string>& links)
{
    int itr = 0;
    string type="";
    string link="";
    //find type - before =
    while(line[itr] != '=')
    {
        if (!isspace(line[itr]))
        {
            type+=line[itr];
        }
        itr++;
    }
    itr++; //get rid of =
    while(itr < line.size())
    {
        if (!isspace(line[itr]))
        {
            link+=line[itr];
        }
        itr++;
    }
    //cout << type << " " << link << endl;
    //save type to link
    links.insert(pair<string, string>(type, link));

}


int main(int argc, char* argv[])
{
    ifstream test;
    string fileName = "file1.txt";
    string fileTwo = "file2.txt";
    test.open(fileName.c_str());
    string line;
    std::map<string, vector<string> > prefixes; //prefix to type
    std::map<string, string> links;//type to link
    std::map<string, vector<string> > preLink; //prefix to link
    //multimap vs vector
    while(std::getline(test, line))
    {
        //cout << line << endl;
        getPrefixes(line, prefixes);

    }
    //cout << "hi" << endl;
    /*
    map<string, vector<string> >::const_iterator itr;
    for (itr = prefixes.begin(); itr != prefixes.end(); itr++)
    {
        cout << "Key: " << itr->first;
        cout << " Value: ";
        for(vector<string>::const_iterator vitr = itr->second.begin(); vitr != itr->second.end(); vitr++)
        {
            cout << *vitr << ", ";
        }
        cout << endl;
    }*/
    test.close();
    //run through the prefixes of each
    test.open(fileTwo.c_str());
    while (std::getline(test, line))
    {
        getLinks(line, links);
    }
    test.close();

    //everything is there
    map<string, vector<string> >::const_iterator itr;
    for (itr = prefixes.begin(); itr != prefixes.end(); itr++)
    {
        cout << "else if(prefix== '" << itr->first << "') {" << endl;
        cout << "return '" ;
        for(vector<string>::const_iterator vitr = itr->second.begin(); vitr != itr->second.end(); vitr++)
        {
            //cout << *vitr << ", ";
            //running through itr(prefix) vitrs(types) match to link
            //save prefix to link
            if (links.find(*vitr) != links.end())
            {
                if (vitr+1 != itr->second.end())
                {

                cout << links[*vitr] << " ";
                }
                else
                {
                    cout << links[*vitr];
                }
                preLink[itr->first].push_back(links[*vitr]);
            }
        }
        cout << "';" << endl;
        cout << "}" << endl;
    }
    return 0;
}

