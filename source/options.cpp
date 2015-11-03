/*
 * options.cpp
 *
 *  Created on: 3 нояб. 2015 г.
 *      Author: serge78rus
 */

/*
 * options.cpp
 *
 *  Created on: 19 янв. 2015 г.
 *      Author: serge78rus
 */

#include <iostream>

using namespace std;

#include "options.h"

Options::Options(int argc, char *argv[])
{
	verb = false;
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'b')
				begin = argv[i] + 2;
			else if (argv[i][1] == 'e')
				end = argv[i] + 2;
			else if (argv[i][1] == 'p')
				prefix = argv[i] + 2;
			else if (argv[i][1] == 's')
				suffix = argv[i] + 2;
			else if (argv[i][1] == 'i')
				incdir = argv[i] + 2;
			else if (argv[i][1] == 'o')
				outfile = argv[i] + 2;
			else if (argv[i][1] == 'v')
				verb = true;
		} else
			infiles.insert(infiles.end(), argv[i]);
	}

	infcnt = infiles.size();
  if (!infcnt)
   	throw string("No files specified");
  if (!incdir.empty())
   	if (incdir[incdir.length()] != '/')
   		incdir += "/";

  if (verb) {
  	cout << "\n"
    		<< "Preprocess parametrs:" << "\n"
    		<< "begin: " << begin << "\n"
    		<< "end: " << end << "\n"
    		<< "prefix: " << prefix << "\n"
    		<< "suffix: " << suffix << "\n"
    		<< "incdir: " << incdir << "\n"
    		<< "outfile: " << outfile << "\n"
    		<< "files:" << "\n";
  	for (int i = 0; i < infcnt; ++i)
  		cout << infiles[i] << "\n";
  	cout << endl;
  }
}



