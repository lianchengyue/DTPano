#include "Stitch.h"


int ExecBatchStitching()
{

}

int ExecDoStitching()
{
    std::string pto_str;
    std::string output_str;

    char *line0[5] = {0};
    line0[0] = "hugin_stitch_project";
    line0[1] = "-o";
    line0[2] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/output";
    line0[3] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";

    if(execv("/usr/local/bin/hugin_stitch_project", line0)<0)
    {
        printf("line1 failed\n");
    }

    return 0;
}
