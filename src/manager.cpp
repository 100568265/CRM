#include "manager.h"


//���캯��
Manager::Manager(int id,std::string name, int did)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}
//��ʾ������Ϣ
void Manager::showInfo()
{
    std::cout << "ְ�����: " <<this->m_Id
              <<"\tְ������: " << this->m_Name
              << "\t��λ: " <<this->getDeptName()
              << "\t��λְ��: ����ϰ彻��������,�����·��������ͨԱ��" << std::endl;
}
//��ȡ��λ����
std::string Manager::getDeptName()
{
    return std::string("����");
}
