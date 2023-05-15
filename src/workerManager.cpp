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
    ofs.open("..//empFile.txt",ios::app);    //������ķ�ʽ�����ļ�(д�ļ�)
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