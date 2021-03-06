#include "Align.h"


int ExecQueue(std::string cmd)
{
    return 0;
}

int ExecCmd()
{
    std::queue<std::string> cmd;

    char *line1[5] = {0};
    //line1[0] = "icpfind";
    //line1[1] = "-o";
    //line1[2] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";
    //line1[3] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";

    system("/usr/local/bin/icpfind -o /media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto /media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto");
 ///   if(execv("/usr/local/bin/icpfind", line1)<0)
    {
        printf("line1 failed\n");
    }

    char *line2[5] = {0};
    line2[0] = "cpclean";
    line2[1] = "-o";
    line2[2] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";
    line2[3] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";

    system("/usr/local/bin/cpclean -o /media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto /media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto");
///    if(execv("/usr/local/bin/cpclean", line2)<0)
    {
        printf("line2 failed\n");
    }

    char *line3[4] = {0};
    line3[0] = "linefind";;
    line3[1] = "--output=/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";
    line3[2] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";

    system("/usr/local/bin/linefind --output=/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto --output=/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto");
///    if(execv("/usr/local/bin/linefind", line3)<0)
    {
        printf("line3 failed\n");
    }

    char *line4[3] = {0};
    line4[0] = "checkpto";
    line4[1] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";

    system("/usr/local/bin/checkpto /media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto");
///    if(execv("/usr/local/bin/checkpto", line4)<0)
    {
        printf("line4 failed\n");
    }

    //add:  # specify variables that should be optimized
    char *line5[9] = {0};
    line5[0] = "autooptimiser";
    line5[1] = "-a";
    line5[2] = "-m";
    line5[3] = "-l";
    line5[4] = "-s";
    line5[5] = "-o";
    line5[6] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";
    line5[7] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";

    system("/usr/local/bin/autooptimiser -a -m -l -s -o /media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto /media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto");
///    if(execv("/usr/local/bin/autooptimiser", line5)<0)
    {
        printf("line5 failed\n");
    }

    char *line6[7] = {0};
    line6[0] = "pano_modify";
    line6[1] = "--canvas=70%";
    line6[2] = "--crop=AUTO";
    line6[3] = "--output=/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";
    line6[4] = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";

    system("/usr/local/bin/pano_modify --canvas=70% --crop=AUTO --output=/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto /media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto");
///    if(execv("/usr/local/bin/pano_modify", line6)<0)
    {
        printf("line6 failed\n");
    }

    return 0;
}

int ExecCmdwithArgs(std::string PTOPath)
{
    std::string icpfind_cmd = "/usr/local/bin/icpfind";
    icpfind_cmd = icpfind_cmd + " " + "-o" + " " + PTOPath + " " + PTOPath;
    system(icpfind_cmd.c_str());

    std::string cpclean_cmd = "/usr/local/bin/cpclean";
    cpclean_cmd = cpclean_cmd + " " + "-o" + " " + PTOPath + " " + PTOPath;
    system(cpclean_cmd.c_str());

    std::string linefind_cmd = "/usr/local/bin/linefind";
    linefind_cmd = linefind_cmd + " " + "--output=" + PTOPath + " " + PTOPath;
    system(linefind_cmd.c_str());

    std::string checkpto_cmd = "/usr/local/bin/checkpto";
    checkpto_cmd = checkpto_cmd + " "  + PTOPath;
    system(checkpto_cmd.c_str());

    //add:  # specify variables that should be optimized
    std::string autooptimiser_cmd = "/usr/local/bin/autooptimiser";
    autooptimiser_cmd = autooptimiser_cmd + " " + "-a -m -l -s -o" + " " + PTOPath + " " + PTOPath;
    system(autooptimiser_cmd.c_str());

    //last step
    std::string pano_modify_cmd = "/usr/local/bin/pano_modify";
    pano_modify_cmd = pano_modify_cmd + " " + "--canvas=70% --crop=AUTO" + " " + "--output=" + PTOPath + " " + PTOPath;
    system(pano_modify_cmd.c_str());

    return 0;
}
