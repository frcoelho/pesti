/***
	This program is under GPL Licence
	Project: "C-Code energy estimation of embedded systems"
	Coordinator: Prof. Dr. Raimundo Barreto - UFAM
	Co-Coordinator: Prof. Dr. Meuse Nogueira - CEFET (PE)

	Author: Carlos Mar, Master student of Federal University of Amazonas (UFAM)
	E-mail: carlos.augusto.mar@gmail.com / caam@dcc.ufam.edu.br
	History:
	2007-14-1: version 0.1 implemented
*/

#include <control-flow-graph.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

xmlNode *getElement(xmlNode *, const char *);
char *getAttr(xmlNode *, const char *);
char *getAttrStr(xmlNode *, const char *);
char getAttrChr(xmlNode *, const char *);
int getAttrInt(xmlNode *, const char *);
double getAttrDbl(xmlNode *, const char *);
void *createNode(xmlNode *);
void addBlock(xmlNode *);
void loadNodes(xmlNode *);
void listNodes(tblock *, double);
void freeNodes(tblock *);
tblock *searchBlock(tblock *, const char *);
void buildGraphFromEdges(xmlNode *);
void loadCfg(char *);
//void runCfg(tblock *, tblock *, unsigned int , double , double );
void runCfg(tblock *, unsigned int , double , double, double);
double randNumber(double, double);
tblock *runCase(tblock *, double );
tblock *runBranch(tbranch_node *, double *, double *);
tblock *runLoop(tloop_node *, double *, double *);
void addSample(double, double);
double sumEnergy(void);
double calculateMean(double);
double calculateSn(double , double);
double getT(unsigned int , double);
int stopSimulation(double , double , double);
void dumpStatistics(const char *);
void freeSample(void);


