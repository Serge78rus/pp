/*
 * main.cpp
 *
 *  Created on: 3 нояб. 2015 г.
 *      Author: serge78rus
 */

/*
 * main.cpp
 *
 *  Created on: 07 нояб. 2014 г.
 *      Author: serge78rus
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "options.h"

void usage();
string getFilePath(const string filename);
string getFileExt(const string filename);

int main(int argc, char *argv[]) {
	int ret = 0;
	try {

		Options opt(argc, argv);

    ofstream os;
    if (!opt.getOutfile().empty()) {
    	os.open(opt.getOutfile().c_str(), ios::out | ios::trunc);
    	if (!os)
    		throw "Can not open outfile " + opt.getOutfile();
    }
    ostream &out = opt.getOutfile().empty() ? cout : os;

    for (int i = 0; i < opt.getInfcnt(); ++i) {

    	if (opt.getVerb())
    		cout << "Processing file " + opt.getInfile(i) << endl;

    	string lb, le, path = getFilePath(opt.getInfile(i)),
    			e = getFileExt(opt.getInfile(i));

    	if (opt.getBegin().empty()) {
    		if (e == ".html" || e == ".xml")
	       	lb = "<!--#include";
	      else if (e == ".css" || e == ".js")
	       	lb = "/*#include";
	      else
	       	throw "Unknown file extension " + opt.getInfile(i);
      } else
      	 lb = opt.getBegin();

      if (opt.getEnd().empty()) {
        if (e == ".html" || e == ".xml")
        	le = "-->";
        else if (e == ".css" || e == ".js")
        	le = "*/";
        else
        	throw "Unknown file extension " + opt.getInfile(i);
      } else
      	le = opt.getEnd();

      int bl = lb.length();

      ifstream in(opt.getInfile(i).c_str());
     	if (!in)
     		throw "Can not open file " + opt.getInfile(i);

     	string s;

      while (getline(in, s)) {
      	size_t p = s.find_first_not_of(" \t\n");
      	if (p != string::npos) {
      		if (s.substr(p, bl) == lb) {

      			if (opt.getVerb())
           		cout << "Processing include in line "
            			<< s << endl;

      			int ep = s.find(le);
            if (!ep)
            	throw "End patern not found in line " + s;

            s = s.substr(bl + 1, ep - bl - 1);//.Trim();
            if (opt.getVerb())
            	cout << "Include directive: " << s << endl;
            int l = s.length();
            if (s[0] == '<' && s[l - 1] == '>')
            	s = opt.getIncdir() + s.substr(1, l - 2);
            else if (s[0] == '\"' && s[l - 1] == '\"')
            	s = path + s.substr(1, l - 2);
            else
            	throw "Invalid include directive " + s;

            ifstream in(s.c_str());
          	if (!in)
          		throw "Can not open include file " + s;
            if (opt.getVerb())
            	cout << "Include file: " << s << endl;
            if (!opt.getPrefix().empty())
            	out << opt.getPrefix() << '\n';
            while (getline(in, s))
            	out << s << '\n';
            if (!opt.getSuffix().empty())
            	out << opt.getSuffix() << '\n';
      		} else
      			out << s << '\n';
      	} else
      		out << s << '\n';
      }
    }
	} catch(string &e) {
		cerr << "Error: " << e << endl;
	    usage();
	    ret = 1;
	}
	return ret;
}

void usage() {
	cout << "Usage:" << '\n'
			<< "pp [-b<begin> -e<end> -p<prefix> -s<suffix> -i<incdir>"
			<< " -o<outfile> -v] file1...fileN" << endl;
}

string getFilePath(const string filename) {
	size_t p = filename.find_last_of('/');
	return p != string::npos ? filename.substr(0, p + 1) : "";
}

string getFileExt(const string filename) {
	size_t p = filename.find_last_of('.');
	return p > 0 && p != string::npos ?
			filename.substr(p, string::npos) : "";
}




