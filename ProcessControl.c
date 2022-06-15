#include "ProcessControl.h"

//�����µĽ���
void create(PCB *running_list,PCB *block_list,int *size){
    if (*size >= MAX_SIZE) {
        //�ڴ治�㣬�޷�����
        printf("�ڴ治�㣬�޷������µĽ���\n");
        return;
    }
    //����һ���ڴ���ƿ�Ŀռ�
    PCB *p = (PCB *)malloc(sizeof(PCB));
    assert(p != NULL);
	/*assert( int expression );assert�������Ϸ��ԣ�������ʽ expression ��ֵΪ�٣���Ϊ 0����
	��ô�����������׼������ stderr ��ӡһ��������Ϣ��Ȼ����ͨ������ abort ������ֹ�������У�
	����assert ���κ����á�*/
    
    //���øÿ��ƿ��idֵ
    int pid;
    printf("�������½��̵�pid:\n");
    scanf("%d",&pid);
    
    //�ж�pidֵ�Ƿ��ظ�
    if (exist_in_list(running_list, pid)) {
        printf("��ֵ�Ѵ���!\n");
        return;
    }
    if (exist_in_list(block_list, pid)) {
        printf("��ֵ�Ѵ���!\n");
        return;
    }
    //û�ظ�������
    p->pid = pid;
    
    //���øÿ��ƿ������ֵ
    printf("�������½��̵����ȼ�:\n");
    scanf("%d",&p->priority);
    printf("�������½��̵Ĵ�С:\n");
    scanf("%d",&p->size);
    printf("�������½��̵�����:\n");
    scanf("%s",p->content);
    p->state = process_type_running;
    p->next = NULL;
    
    //�������������
    PCB *s = running_list;
    while (s->next != NULL) {
        s = s->next;
    }
    s->next = p;
    
    //��������+1
    *size = *size + 1;
}

//�鿴���н���
void show_running(PCB *running_list){
    PCB *s = running_list->next;
    if (s == NULL) {
        printf("û���������еĽ���\n");
        return;
    }
    
    while (s != NULL) {
        printf("����id:%d\n",s->pid);
        printf("�������ȼ�:%d\n",s->priority);
        printf("���̴�С:%d\n",s->size);
        printf("��������:%s\n",s->content);
        printf("___________\n");
        
        s = s->next;
    }
}

//����ĳ������
void change(PCB *running_list,PCB *block_list,int *size){
    if (*size == 0) {
        printf("�޿ɻ����Ľ���\n");
        return;
    }
    
    int pid;
    printf("��������Ҫ�������̵�id:\n");
    scanf("%d",&pid);
    //�鿴���߳��Ƿ������ж����� 
    if (exist_in_list(running_list, pid)) {
        //���ڣ��ҵ����̵߳�λ�ã����ص���ǰһ�����ĵ�ַ�� 
        PCB *s = find(running_list, pid);
        //�޸��߳�״̬
        s->next->state = process_type_block;
        
        //�����̴߳�������������
        //Ѱ�Ҳ���λ��
        PCB *p = block_list;
        while (p->next != NULL) {
            p = p->next;
        }
        //����
        p->next = s->next;
        
        //�����̴߳Ӿ����������Ƴ�
        s->next = s->next->next;
        
        //�����̵߳�next����Ϊ��
        p->next->next = NULL;
        
        *size = *size - 1;
        printf("�ɹ�����\n");
    }else{
        printf("���̲߳����ڻ��Ѵ�������״̬\n");
    }
}

//ɱ�����н���
void killed(PCB *running_list,int *size){
    if (*size == 0) {
        printf("�޿�ɱ���Ľ���\n");
        return;
    }
    
    int pid;
    printf("������Ҫɱ���Ľ���id:\n");
    scanf("%d",&pid);
    //�жϸý����Ƿ����
    if (exist_in_list(running_list, pid)) {
        //����,�ҵ����̵߳�λ��(���ص���ǰһ�����ĵ�ַ�� 
        PCB *s = find(running_list, pid);
        //������̵߳ĵ�ַ�������ͷ�
        PCB *thisThread = s->next;
        //�����̴߳Ӿ��������Ƴ�
        s->next = s->next->next;
        *size = *size - 1;
        
        //ֱ���ͷŵ����߳�
        free(thisThread);
        printf("�ɹ�ɱ��\n");
    }else{
        printf("���̲߳����ڻ��Ѵ�������״̬\n");
    }
}

//����ĳ������
void wake_up(PCB *running_list,PCB *block_list,int *size){
    PCB *s = block_list;
    if (s->next == NULL) {
        printf("û�пɻ��ѵ��߳�\n");
        return;
    }
    
    int pid;
    printf("������Ҫ���ѵĽ���id:\n");
    scanf("%d",&pid);
    //�жϸý����Ƿ����
    if (exist_in_list(block_list, pid)) {
        //���ڣ����ҵ����̵߳�λ��(���ص���ǰһ�����ĵ�ַ�� 
        s = find(block_list, pid);
        //�޸��߳�״̬
        s->next->state = process_type_running;
        
        //�����̴߳������������
        //Ѱ�Ҳ���λ��(���һλ)
        PCB *p = running_list;
        while (p->next != NULL) {
            p = p->next;
        }
        //����
        p->next = s->next;
        
        //�����̴߳�����������ȡ��
        s->next = s->next->next;
        
        //�����̵߳�nextֵ����Ϊnull
        p->next->next = NULL;
        
        *size = *size + 1;
        printf("���ѳɹ�\n");
    }else{
        printf("���̲߳�����\n");
    }
}

//�ж��ڶ������Ƿ�����и�pidֵ�Ľ��� 0->������ 1->����
int exist_in_list(PCB *list,int pid){
    int result = 0;
    
    PCB *s = list->next;
    //����ִ��״̬������
    while (s != NULL) {
        if (s->pid == pid) {
            //���ڣ�ֱ�ӷ���
            result = 1;
            break;
        }
        s = s->next;
    }
    return result;
}

//ͨ��pidѰ�ҽ��̵�λ��(������ǰһ�����ĵ�ַ�� 
PCB *find(PCB *list,int pid){
    PCB *s = list;
    
    while (s->next != NULL) {
        if (s->next->pid == pid) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}
