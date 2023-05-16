#include "workerManager.h"


WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open("..//empFile.txt",ios::in);    //���ļ�

    //case 1:�ļ�������
    if(!ifs.is_open())
    {
        std::cout << "�ļ�������" <<std::endl;
        //��ʼ������
        //��ʼ����¼����
        this->m_EmpNum = 0;
        //��ʼ������ָ��
        this->m_EmpArray = nullptr;
        //��ʼ���ļ��Ƿ�Ϊ��
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //case 2:�ļ����ڣ�����û������
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        std::cout << "�ļ�Ϊ��" <<std::endl;
        //��ʼ������
        //��ʼ����¼����
        this->m_EmpNum = 0;
        //��ʼ������ָ��
        this->m_EmpArray = nullptr;
        //��ʼ���ļ��Ƿ�Ϊ��
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //case 3:�ļ���Ϊ��
    int num = this->Get_EmpNum();
    std::cout << "ְ������Ϊ: " << num <<std::endl;
    this->m_EmpNum = num;
    //���ٿռ�
    this->m_EmpArray = new Worker*[this->m_EmpNum];
    //���ļ��е����ݴ��뵽������
    this->Init_Emp();
    for(int i=0;i<this->m_EmpNum;i++)
    {
        std::cout << "ְ�����: " << this->m_EmpArray[i]->m_Id
                    << "ְ������: " << this->m_EmpArray[i]->m_Name
                    << "���ű��: " << this->m_EmpArray[i]->m_DeptId
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
    cout << "****************��ӭʹ��ְ������ϵͳ*******************" << endl;
    cout << "******************0.�˳��������**********************" << endl;
    cout << "******************1.����ְ����Ϣ**********************" << endl;
    cout << "******************2.��ʾְ����Ϣ**********************" << endl;
    cout << "******************3.ɾ��ְ����Ϣ**********************" << endl;
    cout << "******************4.�޸�ְ����Ϣ**********************" << endl;
    cout << "******************5.����ְ����Ϣ**********************" << endl;
    cout << "******************6.���ձ������**********************" << endl;
    cout << "******************7.��������ĵ�**********************" << endl;
    cout << "****************************************************" << endl;
    cout << endl;
}

void WorkerManager::ExitSystem()
{
    cout << "��ӭ�´�ʹ��" <<endl;
    exit(0);
}

//���ְ��
void WorkerManager::Add_Emp()
{
    std::cout << "���������ְ������: " << std::endl;
    int addNum = 0;     //�����û�����������
    cin >> addNum;
    if(addNum > 0)
    {
        //��������¿ռ��С
        int newSize = this->m_EmpNum + addNum;  //�¿ռ����� = ԭ����¼����+��������
        //�����¿ռ�
        Worker **newSpace = new Worker*[newSize];
        //��ԭ���ռ������ݿ������¿ռ���
        if(this->m_EmpArray!=NULL)
        {
            for(int i=0;i<this->m_EmpNum;i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }
        //�������������
        for(int i=0;i<addNum;i++)
        {
            int id;         //ְ�����
            string name;    //ְ������
            int dSelect;    //����ѡ��
            std::cout << "������� " << i+1 << " ����ְ����� " << std::endl;
            cin >> id;
            std::cout << "������� " << i+1 << " ����ְ������ " << std::endl;
            cin >> name;
            std::cout << "������� " << i+1 << " ����ְ����λ " << std::endl;
            std::cout <<  "1.��ְͨ��" << std::endl;
            std::cout <<  "2.����" << std::endl;
            std::cout <<  "3.�ϰ�" << std::endl;
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
            //������ְ��ְ�𣬱��浽������
            newSpace[this->m_EmpNum+i] = worker;
        }
        //�ͷ�ԭ�еĿռ�
        delete[] this->m_EmpArray;
        //�����¿ռ�ָ��
        this->m_EmpArray = newSpace;
        //�����µ�ְ������
        this->m_EmpNum = newSize;
        //����ְ���ļ���Ϊ�ձ�־
        this->m_FileIsEmpty = false;
        //�ɹ���Ӻ󣬱��浽�ļ���
        this->Save();
        //��ʾ��ӳɹ�
        std::cout << "�ɹ����" << addNum << "����ְ��" <<std::endl;
    }
    else
    {
        std::cout << "������������" <<std::endl;
    }
    //��������� �����ص��ϼ�Ŀ¼
    system("pause");
    system("cls");
}

//�����ļ�
void WorkerManager::Save()
{
    ofstream ofs;
    ofs.open("..//empFile.txt",ios::out);    //������ķ�ʽ�����ļ�(д�ļ�)
    //��ÿ���˵�����д�뵽�ļ���
    for(int i=0;i<this->m_EmpNum;i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << std::endl;
    }
    //�ر��ļ�
    ofs.close();
}

//ͳ���ļ�������
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
        num++;  //ͳ�������ı���
    }
    return num;
}

//��ʼ��Ա��
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
        if(did==1)  //��ְͨ��
        {
            worker = new Employee(id,name,did);
        }
        else if(did==2) //����
        {
            worker = new Manager(id,name,did);
        }
        else if(did==3) //�ϰ�
        {
            worker = new Boss(id,name,did);
        }
        this->m_EmpArray[index++] =worker;
    }
    ifs.close();
}

//չʾְ����Ϣ
void WorkerManager::Show_Emp()
{
    //�ж��ļ��Ƿ�Ϊ��
    if(this->m_FileIsEmpty)
    {
        std::cout << "�ļ������ڻ��¼Ϊ��" << std::endl;
    }
    else
    {
        for(int i=0;i<m_EmpNum;i++)
        {
            //���ö�̬�����ó���ӿ�
            this->m_EmpArray[i]->showInfo();
        }
    }
    //�����������
    system("pause");
    system("cls");
}

//�ж�ְ���Ƿ����,�����ڷ���ְ���������е�λ�ã������ڷ���-1
int WorkerManager::IsExist(int id)
{
    int index = -1;
    for(int i=0;i<this->m_EmpNum;i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            //�ҵ�ְ����
            index = i;
            break;
        }
    }
    return index;
}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
    if(this->m_FileIsEmpty)
    {
        std::cout << "�ļ������ڻ��¼Ϊ��" << std::endl;
    }
    else
    {
        //����ְ�����ɾ��
        std::cout << "��������Ҫɾ����ְ�����: " <<std::endl;
        int id = 0;
        cin >> id;
        int index = this->IsExist(id);
        if(index !=-1)  //˵��ְ������
        {
            for(int i = index;i<this->m_EmpNum-1;i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            this->m_EmpNum--;   //���������м�¼����Ա����
            //ͬ�����µ��ļ���
            this->Save();
            std::cout << "ɾ���ɹ�!" << std::endl;
        }
        else
        {
            std::cout << "δ�ҵ���ְ����ɾ��ʧ��" << std::endl;
        }
    }
    //�����������
    system("pause");
    system("cls");
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        std::cout << "�ļ������ڻ��¼Ϊ��" << std::endl;
    }
    else
    {
        std::cout << "������Ҫ�޸ĵ�ְ���ı��: " << std::endl;
        int id;
        cin >> id;
        int ret = this->IsExist(id);
        if(ret != -1)
        {
            //���ҵ���ŵ�ְ��
            delete this->m_EmpArray[ret];
            int newId = 0;
            std::string newName;
            int newDSelect = 0;
            std::cout << "�鵽: " << id << "��ְ������������ְ����:" << std::endl;
            cin >> newId;
            std::cout << "�������µ�����: " << std::endl;
            cin >> newName;
            std::cout << "�������µĸ�λ: " << std::endl;
            std::cout << "1.��ְͨ��" <<std::endl;
            std::cout << "2.����" <<std::endl;
            std::cout << "3.�ϰ�" <<std::endl;
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
            //�������ݵ�������
            this->m_EmpArray[ret] = worker;
            std::cout << "�޸ĳɹ�" <<std::endl;
            //���浽�ļ���
            this->Save();
        }
        else
        {
            std::cout << "�޸�ʧ�ܣ����޴���" <<std::endl;
        }
    }
    //�����������
    system("pause");
    system("cls");
}

//����ְ��
void WorkerManager::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        std::cout << "�ļ������ڻ��¼Ϊ��" <<std::endl;
    }
    else
    {
        std::cout << "������ҵķ�ʽ: " << std::endl;
        std::cout << "1.���ձ�Ų���" << std::endl;
        std::cout << "2.������������" << std::endl;
        int select = 0;
        cin >> select;
        if(select == 1)
        {
            //���ձ�Ų�
            int id;
            std::cout << "��������ҵ�ְ�����" <<std::endl;
            cin >> id;
            int ret = IsExist(id);
            if(ret!=-1)
            {
                //�ҵ�ְ��
                std::cout << "���ҳɹ�,��ְ����Ϣ����: " << std::endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                std::cout << "����ʧ�ܣ����޴���" << std::endl;
            }
        }
        else if(select == 2)
        {
            //����������
            std::string name;
            std::cout << "��������ҵ�ְ������" <<std::endl;
            cin >> name;

            bool flag = false;  //�����Ƿ�鵽�ı�־,Ĭ��δ�ҵ�ְ��

            for(int i=0;i<m_EmpNum;i++)
            {
                if(this->m_EmpArray[i]->m_Name==name)
                {
                    std::cout << "���ҳɹ���ְ�����Ϊ:" << this->m_EmpArray[i]->m_Id
                                <<"��ְ����Ϣ����: " << std::endl;
                    //������ʾ��Ϣ�ӿ�
                    this->m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if(!flag)
            {
                std::cout << "����ʧ�ܣ����޴���" << std::endl;
            }
        }
        else
        {
            std::cout << "�����ѡ������" << std::endl;
        }
    }
    //�����������
    system("pause");
    system("cls");
}

//����
void WorkerManager::Sort_Emp()
{
    if(this->m_FileIsEmpty)
    {
        std::cout << "�ļ������ڻ��¼Ϊ��" <<std::endl;
        system("pause");
        system("cls");
    }
    else
    {
        std::cout << "��ѡ������ʽ: 1.����2.����" << std::endl;

        int select = 0;
        cin >> select;
        //ѡ������
        for(int i=0;i<m_EmpNum;i++)
        {
            int minOrMax = i;   //������Сֵ�����ֵ�±�
            for(int j = i+1;j<this->m_EmpNum;j++)
            {
                if(select==1)   //����
                {
                    if(this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else    //����
                {
                    if(this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
            }
            //�ж�һ��ʼ�϶�����ֵ�ǲ��Ǽ������ֵ��������ǽ�������
            if(i != minOrMax)
            {
                Worker *temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
                this->m_EmpArray[minOrMax] = temp;
            }
        }
        std::cout << "����ɹ��������Ľ��Ϊ: " <<std::endl;
        this->Show_Emp();   //չʾ���е�ְ��
    }
}

//����ļ�
void WorkerManager::Clean_File()
{
    std::cout << "�Ƿ�ȷ�����? 1.ȷ�ϣ�2.����" << std::endl;
    int select = 0;
    cin >> select;
    if(select==1)
    {
        //����ļ�
        ofstream ofs(FILENAME,ios::trunc);  //ɾ���ļ��������´���
        ofs.close();
        if(this->m_EmpArray!= nullptr)
        {
            //ɾ��������ÿ��ְ������
            for(int i=0;i<m_EmpNum;i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = nullptr;
            }
            //ɾ������������ָ��
            delete[] this->m_EmpArray;
            this->m_EmpArray = nullptr;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        std::cout << "��ճɹ���" <<std::endl;
    }
    system("pause");
    system("cls");
}
