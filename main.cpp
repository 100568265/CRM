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
//    //����Ա��
//    worker = new Employee(1,"����",1);
//    worker->showInfo();
//    delete worker;
//    //���Ծ���
//    worker = new Manager(2,"����",2);
//    worker->showInfo();
//    delete worker;
//    //�����ϰ�
//    worker = new Boss(3,"Elon Musk",3);
//    worker->showInfo();
//    delete worker;



    WorkerManager wm;
    int choice = 0; //�����洢�û���ѡ��
    while(true)
    {
        wm.showMenu();
        cout << "����������ѡ��: " << endl;
        cin >> choice;
        switch (choice)
        {
            case 0:     //�˳�ϵͳ
                wm.ExitSystem();
                break;
            case 1:     //����ְ��
                wm.Add_Emp();
                break;
            case 2:     //��ʾְ��
                wm.Show_Emp();
                break;
            case 3:     //ɾ��ְ��
                wm.Del_Emp();
                break;
            case 4:     //�޸�ְ��
                wm.Mod_Emp();
                break;
            case 5:     //����ְ��
                wm.Find_Emp();
                break;
            case 6:     //����ְ��
                wm.Sort_Emp();
                break;
            case 7:     //����ļ�
                wm.Clean_File();
                break;
            default:
                system("cls");  //�����Ĳ���
                break;

        }
    }
    return 0;
}