#include "ProcessControl.h"

void showLine(){
    printf("**************************\n");
}

int main(int argc, const char * argv[]) {
    
    //����(����)����(ͷ��㲻������Ϣ)
    PCB *running_list = (PCB *)malloc(sizeof(PCB));
    running_list->next = NULL;
    
    //��������(ͷ��㲻������Ϣ)
    PCB *block_list = (PCB *)malloc(sizeof(PCB));
    block_list->next = NULL;
    
    //��ǰ���е��߳�����
    int storage_number = 0;
    
    int choose = 1;
    while (choose) {
        //չʾ�˵�
        showLine();
        printf("*     ������ʾϵͳ      *\n");
        showLine();
        printf("1.�����µĽ���  2.�鿴���н���\n");
        printf("3.����ĳ������  4.ɱ�����н���\n");
        printf("5.����ĳ������  6.�˳�����   \n");
        showLine();
             
        printf("��ѡ��(1~6):\n");
        scanf("%d",&choose);
             
        switch (choose) {
            case 1:
                //�����µĽ���
                create(running_list, block_list, &storage_number);
                break;
            case 2:
                //�鿴���н���
                show_running(running_list);
                break;
            case 3:
                //����ĳ������
                change(running_list, block_list, &storage_number);
                break;
            case 4:
                //ɱ�����н���
                killed(running_list, &storage_number);
                break;
            case 5:
                //����ĳ������
                wake_up(running_list, block_list, &storage_number);
                break;
            case 6:
                return 0;
            default:
                printf("û�����ѡ��!\n");
                break;
        } 
    }
    return 0;
}
