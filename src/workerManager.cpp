#include "workerManager.h"


WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open("..//empFile.txt",ios::in);    //读文件

    //case 1:文件不存在
    if(!ifs.is_open())
    {
        std::cout << "文件不存在" <<std::endl;
        //初始化属性
        //初始化记录人数
        this->m_EmpNum = 0;
        //初始化数组指针
        this->m_EmpArray = nullptr;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //case 2:文件存在，并且没有数据
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        std::cout << "文件为空" <<std::endl;
        //初始化属性
        //初始化记录人数
        this->m_EmpNum = 0;
        //初始化数组指针
        this->m_EmpArray = nullptr;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //case 3:文件不为空

}

WorkerManager::~WorkerManager()
{
    if(this->m_EmpArray!= nullptr)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = nullptr;
    }
}

void WorkerManager::showMenu()
{
    cout << "****************************************************" << endl;
    cout << "****************欢迎使用职工管理系统*******************" << endl;
    cout << "******************0.退出管理程序**********************" << endl;
    cout << "******************1.增加职工信息**********************" << endl;
    cout << "******************2.显示职工信息**********************" << endl;
    cout << "******************3.删除职工信息**********************" << endl;
    cout << "******************4.修改职工信息**********************" << endl;
    cout << "******************5.查找职工信息**********************" << endl;
    cout << "******************6.按照编号排序**********************" << endl;
    cout << "******************7.清空所有文档**********************" << endl;
    cout << "****************************************************" << endl;
    cout << endl;
}

void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" <<endl;
    exit(0);
}

//添加职工
void WorkerManager::Add_Emp()
{
    std::cout << "请输入添加职工数量: " << std::endl;
    int addNum = 0;     //保存用户的输入数量
    cin >> addNum;
    if(addNum > 0)
    {
        //计算添加新空间大小
        int newSize = this->m_EmpNum + addNum;  //新空间人数 = 原来记录人数+新增人数
        //开辟新空间
        Worker **newSpace = new Worker*[newSize];
        //将原来空间下数据拷贝到新空间下
        if(this->m_EmpArray!=NULL)
        {
            for(int i=0;i<this->m_EmpNum;i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }
        //批量添加新数据
        for(int i=0;i<addNum;i++)
        {
            int id;         //职工编号
            string name;    //职工姓名
            int dSelect;    //部门选择
            std::cout << "请输入第 " << i+1 << " 个新职工编号 " << std::endl;
            cin >> id;
            std::cout << "请输入第 " << i+1 << " 个新职工姓名 " << std::endl;
            cin >> name;
            std::cout << "请输入第 " << i+1 << " 个新职工岗位 " << std::endl;
            std::cout <<  "1.普通职工" << std::endl;
            std::cout <<  "2.经理" << std::endl;
            std::cout <<  "3.老板" << std::endl;
            cin >> dSelect;
            Worker *worker = NULL;
            switch (dSelect)
            {
                case 1:
                    worker  = new Employee(id,name,1);
                    break;
                case 2:
                    worker  = new Manager(id,name,2);
                    break;
                case 3:
                    worker  = new Boss(id,name,3);
                    break;
                default:
                    break;
            }
            //将创建职工职责，保存到数组中
            newSpace[this->m_EmpNum+i] = worker;
        }
        //释放原有的空间
        delete[] this->m_EmpArray;
        //更改新空间指向
        this->m_EmpArray = newSpace;
        //更新新的职工人数
        this->m_EmpNum = newSize;
        //更新职工文件不为空标志
        this->m_FileIsEmpty = false;
        //成功添加后，保存到文件中
        this->Save();
        //提示添加成功
        std::cout << "成功添加" << addNum << "名新职工" <<std::endl;
    }
    else
    {
        std::cout << "输入数据有误" <<std::endl;
    }
    //按任意键后 清屏回到上级目录
    system("pause");
    system("cls");
}

//保存文件
void WorkerManager::Save()
{
    ofstream ofs;
    ofs.open("..//empFile.txt",ios::app);    //用输出的方式来打开文件(写文件)
    //将每个人的数据写入到文件中
    for(int i=0;i<this->m_EmpNum;i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << std::endl;
    }
    //关闭文件
    ofs.close();
}