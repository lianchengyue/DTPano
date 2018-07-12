#ifndef DTPANO_H
#define DTPANO_H

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include "Align.h"
#include "Stitch.h"

#define CAM_NUM 3

#if 1
#define CONFIG_FUNC_DEBUG
#ifdef CONFIG_FUNC_DEBUG
#define LOG_ERR(fmt,args...) printf(fmt,##args)
#define LOG_DBG(fmt,args...) printf(fmt,##args)
#else
#define LOG_ERR(fmt,args...) printf(fmt,##args)
#define LOG_DBG(fmt,args...)
#endif
#endif

std::vector<std::string> vecStreetList;//街道信息 //need not swap
std::vector<std::string> vec0PictureList;//0文件夹中的图片信息 //done
std::vector<std::string> vecFileList; //每个batch的输入文件名 //not swap
std::string ROOT_DIR = "/media/montafan/FE98E29998E25027/EDSDK_File/DTPano/";


HuginBase::Panorama pano;
//HuginBase::Panorama &pano;

std::string getPrefix(std::string name);

//获取所拍片的街道信息
int get_street_info(std::string dir);
//判断是否每组图像是否完整
bool is_whole_pic_check(std::string dir, std::string picname);
//获取文件夹0中的文件名
int pic_traversal(std::string dir);
//加载每个batch的图片
int OnLoadImages(std::string filename);

#endif // DTPANO_H
