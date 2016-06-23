// ����ṹ
typedef struct _TASK_COMPONENTS
{
    uint8 Run;                  // �������б�ǣ�0-�����У�1����
    uint8 Timer;                // ��ʱ��
    uint8 ItvTime;              // �������м��ʱ��
    void (*TaskHook)(void);    // Ҫ���е�������
} TASK_COMPONENTS;       // ������

static TASK_COMPONENTS TaskComps[] = 
{
    {0, 60, 60, TaskDisplayClock},     // ��ʾʱ��
    {0, 20, 20, TaskKeySan},           // ����ɨ��
    {0, 30, 30, TaskDispStatus},       // ��ʾ����״̬

     // �������������񡣡�����
};

/**************************************************************************************
* Variable definition                            
**************************************************************************************/

typedef enum _TASK_LIST
{
    TAST_DISP_CLOCK,            // ��ʾʱ��
    TAST_KEY_SAN,             // ����ɨ��
    TASK_DISP_WS,             // ����״̬��ʾ
     // �������������񡣡�����
     TASKS_MAX                                           // �ܵĿɹ�����Ķ�ʱ������Ŀ
} TASK_LIST;

/**************************************************************************************
* FunctionName   : TaskRemarks()
* Description    : �����־����
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskRemarks(void)
{
    uint8 i;

    for (i=0; i<TASKS_MAX; i++)          // �������ʱ�䴦��
    {
         if (TaskComps[i].Timer)          // ʱ�䲻Ϊ0
        {
            TaskComps[i].Timer--;         // ��ȥһ������
            if (TaskComps[i].Timer == 0)       // ʱ�������
            {
                 TaskComps[i].Timer = TaskComps[i].ItvTime;       // �ָ���ʱ��ֵ��������һ��
                 TaskComps[i].Run = 1;           // �����������
            }
        }
   }
}

/**************************************************************************************
* FunctionName   : TaskProcess()
* Description    : ������
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskProcess(void)
{
    uint8 i;

    for (i=0; i<TASKS_MAX; i++)           // �������ʱ�䴦��
    {
         if (TaskComps[i].Run)           // ʱ�䲻Ϊ0
        {
             TaskComps[i].TaskHook();         // ��������
             TaskComps[i].Run = 0;          // ��־��0
        }
    }   
}



/**************************************************************************************
* FunctionName   : TaskDisplayClock()
* Description    : ��ʾ����

* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskDisplayClock(void)
{

 

}

/**************************************************************************************
* FunctionName   : TaskKeySan()
* Description    : ɨ������
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskKeySan(void)
{


}

/**************************************************************************************
* FunctionName   : TaskDispStatus()
* Description    : ����״̬��ʾ
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskDispStatus(void)
{


}
// ��������������񡣡���������������

/**************************************************************************************
* FunctionName   : main()
* Description    : ������
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
int main(void) 
{ 
    InitSys();                  // ��ʼ��

    while (1)
    {
        TaskProcess();             // ������
    }
}

/**************************************************************************************
* FunctionName : TimerInterrupt()
* Description : ��ʱ�жϷ�����
* EntryParameter : None
* ReturnValue : None
**************************************************************************************/
void TimerInterrupt(void)
{
    TaskRemarks( );
}