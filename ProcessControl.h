#ifndef ProcessControl_h
#define ProcessControl_h
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//����ڴ�Ĵ�С
#define MAX_SIZE 20

//�߳�״̬������(����)  ����
enum process_type{
    process_type_running = 1000,
    process_type_block = -1000,
    process_type_ready = 500
};

//���̿��ƿ�ṹ��
typedef struct PCB_Type{
    //���̵�id
    int pid;
    //���̵����ȼ�
    int priority;
    //���̴�С��ִ��ʱ�䣩
    int size;
    //��������
    char content[20];
    //���̵�״̬  ִ��  ����
    int state;
    //��һ��Ҫִ�еĽ���
    struct PCB_Type *next;
}PCB;

//�����µĽ���
void create(PCB *running_list,PCB *block_list,int *size);
//�鿴���н���
void show_running(PCB *running_list);
//����ĳ������
void change(PCB *running_list,PCB *block_list,int *size);
//ɱ�����н���
void killed(PCB *running_list,int *size);
//����ĳ������
void wake_up(PCB *running_list,PCB *block_list,int *size);

//�ж��ڶ������Ƿ�����и�pidֵ�Ľ��� 0->������ 1->����
int exist_in_list(PCB *list,int pid);

//ͨ��pidѰ�ҽ��̵�λ��(������ǰһ�����ĵ�ַ
PCB *find(PCB *list,int pid);

#endif /* ProcessControl_h */

