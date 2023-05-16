#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using namespace std;

int main()
{
//    Worker *worker = nullptr;
//    //测试员工
//    worker = new Employee(1,"张三",1);
//    worker->showInfo();
//    delete worker;
//    //测试经理
//    worker = new Manager(2,"李四",2);
//    worker->showInfo();
//    delete worker;
//    //测试老板
//    worker = new Boss(3,"Elon Musk",3);
//    worker->showInfo();
//    delete worker;



    WorkerManager wm;
    int choice = 0; //用来存储用户的选项
    while(true)
    {
        wm.showMenu();
        cout << "请输入您的选择: " << endl;
        cin >> choice;
        switch (choice)
        {
            case 0:     //退出系统
                wm.ExitSystem();
                break;
            case 1:     //增加职工
                wm.Add_Emp();
                break;
            case 2:     //显示职工
                wm.Show_Emp();
                break;
            case 3:     //删除职工
                wm.Del_Emp();
                break;
            case 4:     //修改职工
                wm.Mod_Emp();
                break;
            case 5:     //查找职工
                wm.Find_Emp();
                break;
            case 6:     //排序职工
                wm.Sort_Emp();
                break;
            case 7:     //清空文件
                wm.Clean_File();
                break;
            default:
                system("cls");  //清屏的操作
                break;

        }
    }
    return 0;
}