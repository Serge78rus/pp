/*
 * options.h
 *
 *  Created on: 3 нояб. 2015 г.
 *      Author: serge78rus
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <string>
#include <vector>

class Options {
private:
	bool verb;
	int infcnt;
	std::string test, test1, begin, end, prefix, suffix, incdir, outfile;
  std::vector<std::string> infiles;
public:
	Options(int argc, char *argv[]);
	bool getVerb() {return verb;}
	int getInfcnt() {return infcnt;}
	std::string &getBegin() {return begin;}
	std::string &getEnd() {return end;}
	std::string &getPrefix() {return prefix;}
	std::string &getSuffix() {return suffix;}
	std::string &getIncdir() {return incdir;}
	std::string &getOutfile() {return outfile;}
	std::string &getInfile(int idx) {return infiles[idx];}
};

#endif /* OPTIONS_H_ */
