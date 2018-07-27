#include "Stitch.h"


int ExecBatchStitching()
{

}

int ExecDoStitching()
{
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

int ExecDoStitchingwithArgs(std::string OutputName, std::string PTOPath)
{
    std::string hugin_stitch_project_cmd = "/usr/local/bin/hugin_stitch_project";
    hugin_stitch_project_cmd = hugin_stitch_project_cmd + " " + "-o" + " " + OutputName + " " + PTOPath;
    system(hugin_stitch_project_cmd.c_str());

    return 0;
}

int ExecDoBatchStitchingwithArgs(std::string OutputName, std::string PTOPath)
{
    std::string hugin_stitch_project_cmd = "/usr/local/bin/PTBatcherGUI";
    hugin_stitch_project_cmd = hugin_stitch_project_cmd + " " + "-b -v" + " " + PTOPath + " " + OutputName;
    system(hugin_stitch_project_cmd.c_str());

    return 0;
}
