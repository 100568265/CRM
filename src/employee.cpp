#include "employee.h"

//���캯��
Employee::Employee(int id,std::string name, int did)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}
//��ʾ������Ϣ
void Employee::showInfo()
{
    std::cout << "ְ�����: " <<this->m_Id
    <<"\tְ������: " << this->m_Name
    << "\t��λ: " <<this->getDeptName()
    << "\t��λְ��: ��ɾ�����������" << std::endl;
}

//��ȡ��λ����
std::string Employee::getDeptName()
{
    return std::string("Ա��");
}
