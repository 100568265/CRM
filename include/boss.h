#pragma once
#include <iostream>
#include "worker.h"

//老板类
class Boss : public Worker
{
public:
    //重写父类纯虚函数

    //构造函数
    Boss(int id,std::string name, int did);
    //显示个人信息
    virtual void showInfo();
    //获取岗位名称
    virtual std::string getDeptName();
};