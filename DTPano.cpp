// -*- c-basic-offset: 4 -*-

/** @file pto_gen.cpp
 *
 *  @brief program to generate a pto file from given image files
 *
 *  @author T. Modes
 *
 */

/*  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this software. If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <fstream>
#include <getopt.h>
#include <vigra/imageinfo.hxx>
#include <panodata/Panorama.h>
#include <panodata/StandardImageVariableGroups.h>
#include <panodata/OptimizerSwitches.h>
#include <algorithms/basic/CalculateMeanExposure.h>
#include "hugin_utils/alphanum.h"
#include <lensdb/LensDB.h>

#include "DTPano.h"


int get_street_info(std::string dir)   //dir = ROOT_DIR
{
    DIR *Dp;
    //文件目录结构体
    struct dirent *enty;
    //详细文件信息结构体
    struct stat statbuf;

    //打开指定的目录，获得目录指针
    if(NULL == (Dp = opendir(dir.c_str())))
    {
        LOG_ERR("%s, can not open dir:%s\n", __func__, dir.c_str());
        return 0;
    }

    //切换到这个目录
    chdir(dir.c_str());

    //遍历这个目录下的所有文件
    while(NULL != (enty = readdir(Dp) ))
    {
        //通过文件名，得到详细文件信息
        lstat(enty->d_name,&statbuf);
        //判断是不是目录
        if(S_ISDIR(statbuf.st_mode))
        {
            //是目录
            //当前目录和上一目录过滤掉
            if(0 == strcmp(".",enty->d_name) ||
                          0 == strcmp("..",enty->d_name))
            {
                continue;
            }

            LOG_DBG("%s, vecStreetList:%s\n", __func__, enty->d_name);
            vecStreetList.push_back(enty->d_name);
        }
        else
        {
            //是文件
            continue;
        }
    }

    //切换到上一及目录
    //chdir("..");
    //关闭文件指针
    closedir(Dp);

    return 0;
}

//判断是否每组图像是否完整
bool is_whole_pic_check(std::string dir, std::string picname)
{
    int i = 0;
    char num[64] = {0};

    while(i < CAM_NUM){
        sprintf(num, "%d/%s", i, picname.c_str()); //将100转为16进制表示的字符串
        std::string picstr = dir + num;

        //if (access(picstr.c_str(), R_OK) != 0){
        if (!hugin_utils::FileExists(picstr)){
            LOG_ERR("%s, No enough pics, discard!\n", __func__);
            return false;
        }
        i++;
    }
    LOG_ERR("%s, Good batch!\n", __func__);
    return true;
}

//获取文件夹0中的文件名
int pic_traversal(std::string dir)
{
    DIR *Dp;
    //文件目录结构体
    struct dirent *enty;
    //详细文件信息结构体
    struct stat statbuf;

    //打开指定的目录，获得目录指针
    if(NULL == (Dp = opendir(dir.c_str())))
    {
        LOG_ERR("%s, can not open dir:%s\n", __func__, dir.c_str());
        return 0;
    }

    //切换到这个目录
    chdir(dir.c_str());

    //遍历这个目录下的所有文件
    while(NULL != (enty = readdir(Dp) ))
    {
        //通过文件名，得到详细文件信息
        lstat(enty->d_name,&statbuf);
        //判断是不是目录
        if(S_ISDIR(statbuf.st_mode))
        {
            //是目录
            //当前目录和上一目录过滤掉
            if(0 == strcmp(".",enty->d_name) ||
                          0 == strcmp("..",enty->d_name))
            {
                continue;
            }
        }
        else
        {
            //是文件
            LOG_DBG("%s, vec0PictureList:%s, ", __func__, enty->d_name);
            vec0PictureList.push_back(enty->d_name);
        }
    }
    LOG_DBG("\n");

    //关闭文件指针
    closedir(Dp);

    return 0;
}

int OnLoadImages(std::string filename)
{

}


//----------main func-----------//
int main()
{
    HuginBase::Panorama pano;
    std::string streetName;//street路径
    ///std::string output;//.pto的输出路径
    std::string output = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/PTO/0.pto";//.pto的输出路径
    //int cam_count = 0;

    get_street_info(ROOT_DIR);

    //遍历所有的街道
    for(size_t street_cnt = 0; street_cnt < vecStreetList.size(); street_cnt++)
    {
        std::cout << "Reading " << vecStreetList[street_cnt] << "..." << std::endl;

        //每条街道的0文件夹的照片
        std::string _path_0;
        _path_0 = ROOT_DIR + vecStreetList[street_cnt] + "/" + "0" + "/";
        pic_traversal(_path_0); //得到vec0PictureList

        //load Image, 获取file0中每张照片的名称
        for(size_t picture0_cnt = 0; picture0_cnt < vec0PictureList.size(); picture0_cnt++)
        {
            //逐个获取每个batch的image
            for(size_t camera_cnt = 0; camera_cnt < CAM_NUM; camera_cnt++)
            {
                std::string input;
                char num[64] = {0};

                sprintf(num, "%d", camera_cnt);
                //input = ROOT_DIR + vecStreetList[street_cnt] + "/" + num + "/";
                input = ROOT_DIR + vecStreetList[street_cnt] + "/";

                //查看即将放进batch的文件是否完整
                if (camera_cnt == 0)
                {
                    if (!is_whole_pic_check(input,vec0PictureList[picture0_cnt])){
                        break;
                    }
                }
                input = input + num + "/" + vec0PictureList[picture0_cnt];
                //input = media/montafan/FE98E29998E25027/EDSDK_File/DTPano/gaoxinsilu/0/xxx.jpg

                //added
                if(hugin_utils::FileExists(input))
                {
                    if(vigra::isImage(input.c_str()))
                    {
                        vecFileList.push_back(input);
                        LOG_DBG("%s\n", input.c_str());
                    }
                }
            }
            printf("\n");
        }

        //temp,生成pto
        {
            for(size_t i=0; i<vecFileList.size(); i++){
                HuginBase::SrcPanoImage srcImage;
                srcImage.setFilename(vecFileList[i]);

                try
                {
                    vigra::ImageImportInfo info(vecFileList[i].c_str());
                    if(info.width()==0 || info.height()==0)
                    {
                        std::cerr << "ERROR: Could not decode image " << vecFileList[i] << std::endl
                             << "Skipping this image." << std::endl << std::endl;
                        continue;
                    }
                    srcImage.setSize(info.size());
                    // check for black/white images
                    const std::string pixelType=info.getPixelType();
                    if (pixelType == "BILEVEL")
                    {
                        std::cerr << "ERROR: Image " << vecFileList[i] << " is a black/white images." << std::endl
                            << "       This is not supported. Convert to grayscale image and try again." << std::endl
                            << "       Skipping this image." << std::endl;
                        continue;
                    }
                    if((pixelType=="UINT8") || (pixelType=="UINT16") || (pixelType=="INT16"))
                    {
                        srcImage.setResponseType(HuginBase::SrcPanoImage::RESPONSE_EMOR);
                    }
                    else
                    {
                        srcImage.setResponseType(HuginBase::SrcPanoImage::RESPONSE_LINEAR);
                    };
                }
                catch(std::exception& e)
                {
                    std::cerr << "ERROR: caught exception: " << e.what() << std::endl;
                    std::cerr << "Could not read image information for file " << vecFileList[i] << std::endl;
                    std::cerr << "Skipping this image." << std::endl << std::endl;
                    continue;
                };

                srcImage.readEXIF();
                bool fovOk=srcImage.applyEXIFValues();
                {
                    srcImage.setProjection((HuginBase::BaseSrcPanoImage::Projection)3); // 3=HuginBase::SrcPanoImage::FULL_FRAME_FISHEYE
                }

                pano.addImage(srcImage);
            }

            if(pano.getNrOfImages()==0)
            {
                std::cerr << "Adding images to project files failed." << std::endl;
                HuginBase::LensDB::LensDB::Clean();
                return 1;
            };

            //write output
            HuginBase::UIntSet imgs;
            fill_set(imgs,0, pano.getNrOfImages()-1);

            //double m_focalLength = 1.3f;
            //pano.UpdateFocalLength(imgs, m_focalLength); //
/*
            std::ofstream script(output.c_str());
            //pano.printPanoramaScript(script, pano.getOptimizeVector(), pano.getOptions(), imgs, false, hugin_utils::getPathPrefix(output));
            pano.printPanoramaScript(script, pano.getOptimizeVector(), pano.getOptions(), imgs, false);
            script.close();
*/
            std::cout << std::endl << "Written output to " << output << std::endl;
            ExecCmd();
        }
        //temp end

        //遍历一个街道结束,清除该街道的vec0PictureList
        std::vector<std::string>().swap(vec0PictureList);

    }

}
