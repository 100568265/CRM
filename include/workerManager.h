#pragma once
#include <iostream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#define FILENAME "..//empFile.txt"
#include <fstream>


using namespace std;

class WorkerManager{
public:
    //记录职工人数
    int m_EmpNum;
    //职工数组指针
    Worker ** m_EmpArray;
    //标志文件是否为空
    bool m_FileIsEmpty;

    WorkerManager();
    ~WorkerManager();
    void showMenu();
    //添加职工
    void Add_Emp();
    //保存文件
    void Save();
    //统计文件中人数
    int Get_EmpNum();
    //初始化员工
    void Init_Emp();
    //退出系统
    void ExitSystem();
    //展示职工信息
    void Show_Emp();
    //删除职工
    void Del_Emp();
    //判断职工是否存在,若存在返回职工在数组中的位置，不存在返回-1
    int IsExist(int id);
    //修改职工
    void Mod_Emp();
    //查找职工
    void Find_Emp();
    //排序
    void Sort_Emp();
    //清空文件
    void Clean_File();
};