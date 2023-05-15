#pragma once
#include <iostream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

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


    //退出系统
    void ExitSystem();
};