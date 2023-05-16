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
    int num = this->Get_EmpNum();
    std::cout << "职工人数为: " << num <<std::endl;
    this->m_EmpNum = num;
    //开辟空间
    this->m_EmpArray = new Worker*[this->m_EmpNum];
    //将文件中的数据存入到数组中
    this->Init_Emp();
    for(int i=0;i<this->m_EmpNum;i++)
    {
        std::cout << "职工编号: " << this->m_EmpArray[i]->m_Id
                    << "职工姓名: " << this->m_EmpArray[i]->m_Name
                    << "部门编号: " << this->m_EmpArray[i]->m_DeptId
                    << std::endl;
    }

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
    ofs.open("..//empFile.txt",ios::out);    //用输出的方式来打开文件(写文件)
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

//统计文件中人数
int WorkerManager::Get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    int id;
    std::string name;
    int did;
    int num = 0;
    while(ifs>>id && ifs>>name && ifs>>did)
    {
        num++;  //统计人数的变量
    }
    return num;
}

//初始化员工
void WorkerManager::Init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    int id;
    std::string name;
    int did;
    int index = 0;
    while(ifs>>id && ifs>>name && ifs>>did)
    {
        Worker *worker = NULL;
        if(did==1)  //普通职工
        {
            worker = new Employee(id,name,did);
        }
        else if(did==2) //经理
        {
            worker = new Manager(id,name,did);
        }
        else if(did==3) //老板
        {
            worker = new Boss(id,name,did);
        }
        this->m_EmpArray[index++] =worker;
    }
    ifs.close();
}

//展示职工信息
void WorkerManager::Show_Emp()
{
    //判断文件是否为空
    if(this->m_FileIsEmpty)
    {
        std::cout << "文件不存在或记录为空" << std::endl;
    }
    else
    {
        for(int i=0;i<m_EmpNum;i++)
        {
            //利用多态来调用程序接口
            this->m_EmpArray[i]->showInfo();
        }
    }
    //按任意键清屏
    system("pause");
    system("cls");
}

//判断职工是否存在,若存在返回职工在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
    int index = -1;
    for(int i=0;i<this->m_EmpNum;i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            //找到职工了
            index = i;
            break;
        }
    }
    return index;
}

//删除职工
void WorkerManager::Del_Emp()
{
    if(this->m_FileIsEmpty)
    {
        std::cout << "文件不存在或记录为空" << std::endl;
    }
    else
    {
        //按照职工编号删除
        std::cout << "请输入想要删除的职工编号: " <<std::endl;
        int id = 0;
        cin >> id;
        int index = this->IsExist(id);
        if(index !=-1)  //说明职工存在
        {
            for(int i = index;i<this->m_EmpNum-1;i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            this->m_EmpNum--;   //更新数组中记录的人员个数
            //同步更新到文件中
            this->Save();
            std::cout << "删除成功!" << std::endl;
        }
        else
        {
            std::cout << "未找到该职工，删除失败" << std::endl;
        }
    }
    //按任意键清屏
    system("pause");
    system("cls");
}

//修改职工
void WorkerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        std::cout << "文件不存在或记录为空" << std::endl;
    }
    else
    {
        std::cout << "请输入要修改的职工的编号: " << std::endl;
        int id;
        cin >> id;
        int ret = this->IsExist(id);
        if(ret != -1)
        {
            //查找到编号的职工
            delete this->m_EmpArray[ret];
            int newId = 0;
            std::string newName;
            int newDSelect = 0;
            std::cout << "查到: " << id << "号职工，请输入新职工号:" << std::endl;
            cin >> newId;
            std::cout << "请输入新的姓名: " << std::endl;
            cin >> newName;
            std::cout << "请输入新的岗位: " << std::endl;
            std::cout << "1.普通职工" <<std::endl;
            std::cout << "2.经理" <<std::endl;
            std::cout << "3.老板" <<std::endl;
            cin >> newDSelect;
            Worker *worker = nullptr;
            switch (newDSelect)
            {
                case 1:
                    worker = new Employee(newId,newName,newDSelect);
                    break;
                case 2:
                    worker = new Manager(newId,newName,newDSelect);
                    break;
                case 3:
                    worker = new Boss(newId,newName,newDSelect);
                    break;
                default:
                    break;
            }
            //更新数据到数组中
            this->m_EmpArray[ret] = worker;
            std::cout << "修改成功" <<std::endl;
            //保存到文件中
            this->Save();
        }
        else
        {
            std::cout << "修改失败，查无此人" <<std::endl;
        }
    }
    //按任意键清屏
    system("pause");
    system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        std::cout << "文件不存在或记录为空" <<std::endl;
    }
    else
    {
        std::cout << "输入查找的方式: " << std::endl;
        std::cout << "1.按照编号查找" << std::endl;
        std::cout << "2.按照姓名查找" << std::endl;
        int select = 0;
        cin >> select;
        if(select == 1)
        {
            //按照编号查
            int id;
            std::cout << "请输入查找的职工编号" <<std::endl;
            cin >> id;
            int ret = IsExist(id);
            if(ret!=-1)
            {
                //找到职工
                std::cout << "查找成功,该职工信息如下: " << std::endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                std::cout << "查找失败，查无此人" << std::endl;
            }
        }
        else if(select == 2)
        {
            //按照姓名查
            std::string name;
            std::cout << "请输入查找的职工姓名" <<std::endl;
            cin >> name;

            bool flag = false;  //加入是否查到的标志,默认未找到职工

            for(int i=0;i<m_EmpNum;i++)
            {
                if(this->m_EmpArray[i]->m_Name==name)
                {
                    std::cout << "查找成功，职工编号为:" << this->m_EmpArray[i]->m_Id
                                <<"号职工信息如下: " << std::endl;
                    //调用显示信息接口
                    this->m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if(!flag)
            {
                std::cout << "查找失败，查无此人" << std::endl;
            }
        }
        else
        {
            std::cout << "输入的选项有误" << std::endl;
        }
    }
    //按任意键清屏
    system("pause");
    system("cls");
}

//排序
void WorkerManager::Sort_Emp()
{
    if(this->m_FileIsEmpty)
    {
        std::cout << "文件不存在或记录为空" <<std::endl;
        system("pause");
        system("cls");
    }
    else
    {
        std::cout << "请选择排序方式: 1.升序，2.降序" << std::endl;

        int select = 0;
        cin >> select;
        //选择排序
        for(int i=0;i<m_EmpNum;i++)
        {
            int minOrMax = i;   //声明最小值或最大值下标
            for(int j = i+1;j<this->m_EmpNum;j++)
            {
                if(select==1)   //升序
                {
                    if(this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else    //降序
                {
                    if(this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
            }
            //判断一开始认定的最值是不是计算的最值，如果不是交换数据
            if(i != minOrMax)
            {
                Worker *temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
                this->m_EmpArray[minOrMax] = temp;
            }
        }
        std::cout << "排序成功！排序后的结果为: " <<std::endl;
        this->Show_Emp();   //展示所有的职工
    }
}

//清空文件
void WorkerManager::Clean_File()
{
    std::cout << "是否确认清空? 1.确认，2.返回" << std::endl;
    int select = 0;
    cin >> select;
    if(select==1)
    {
        //清空文件
        ofstream ofs(FILENAME,ios::trunc);  //删除文件后再重新创建
        ofs.close();
        if(this->m_EmpArray!= nullptr)
        {
            //删除堆区的每个职工对象
            for(int i=0;i<m_EmpNum;i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = nullptr;
            }
            //删除堆区的数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = nullptr;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        std::cout << "清空成功！" <<std::endl;
    }
    system("pause");
    system("cls");
}
