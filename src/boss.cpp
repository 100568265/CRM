#include "boss.h"


//���캯��
Boss::Boss(int id,std::string name, int did)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}
//��ʾ������Ϣ
void Boss::showInfo()
{
    std::cout << "ְ�����: " <<this->m_Id
              <<"\tְ������: " << this->m_Name
              << "\t��λ: " <<this->getDeptName()
              << "\t��λְ��: ����˾���е�����" << std::endl;
}
//��ȡ��λ����
std::string Boss::getDeptName()
{
    return std::string("�ܲ�");
}

