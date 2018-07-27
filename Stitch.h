#ifndef STITCH_H
#define STITCH_H

#include <string>
#include <unistd.h>


int ExecBatchStitching();

int ExecDoStitching();
int ExecDoStitchingwithArgs(std::string OutputName, std::string PTOPath);
int ExecDoBatchStitchingwithArgs(std::string OutputName, std::string PTOPath);

#endif // STITCH_H
