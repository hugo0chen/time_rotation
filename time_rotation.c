// 任务结构
typedef struct _TASK_COMPONENTS
{
    uint8 Run;                  // 程序运行标记：0-不运行，1运行
    uint8 Timer;                // 计时器
    uint8 ItvTime;              // 任务运行间隔时间
    void (*TaskHook)(void);    // 要运行的任务函数
} TASK_COMPONENTS;       // 任务定义

static TASK_COMPONENTS TaskComps[] = 
{
    {0, 60, 60, TaskDisplayClock},     // 显示时钟
    {0, 20, 20, TaskKeySan},           // 按键扫描
    {0, 30, 30, TaskDispStatus},       // 显示工作状态

     // 这里添加你的任务。。。。
};

/**************************************************************************************
* Variable definition                            
**************************************************************************************/

typedef enum _TASK_LIST
{
    TAST_DISP_CLOCK,            // 显示时钟
    TAST_KEY_SAN,             // 按键扫描
    TASK_DISP_WS,             // 工作状态显示
     // 这里添加你的任务。。。。
     TASKS_MAX                                           // 总的可供分配的定时任务数目
} TASK_LIST;

/**************************************************************************************
* FunctionName   : TaskRemarks()
* Description    : 任务标志处理
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskRemarks(void)
{
    uint8 i;

    for (i=0; i<TASKS_MAX; i++)          // 逐个任务时间处理
    {
         if (TaskComps[i].Timer)          // 时间不为0
        {
            TaskComps[i].Timer--;         // 减去一个节拍
            if (TaskComps[i].Timer == 0)       // 时间减完了
            {
                 TaskComps[i].Timer = TaskComps[i].ItvTime;       // 恢复计时器值，从新下一次
                 TaskComps[i].Run = 1;           // 任务可以运行
            }
        }
   }
}

/**************************************************************************************
* FunctionName   : TaskProcess()
* Description    : 任务处理
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskProcess(void)
{
    uint8 i;

    for (i=0; i<TASKS_MAX; i++)           // 逐个任务时间处理
    {
         if (TaskComps[i].Run)           // 时间不为0
        {
             TaskComps[i].TaskHook();         // 运行任务
             TaskComps[i].Run = 0;          // 标志清0
        }
    }   
}



/**************************************************************************************
* FunctionName   : TaskDisplayClock()
* Description    : 显示任务

* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskDisplayClock(void)
{

 

}

/**************************************************************************************
* FunctionName   : TaskKeySan()
* Description    : 扫描任务
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskKeySan(void)
{


}

/**************************************************************************************
* FunctionName   : TaskDispStatus()
* Description    : 工作状态显示
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskDispStatus(void)
{


}
// 这里添加其他任务。。。。。。。。。

/**************************************************************************************
* FunctionName   : main()
* Description    : 主函数
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
int main(void) 
{ 
    InitSys();                  // 初始化

    while (1)
    {
        TaskProcess();             // 任务处理
    }
}

/**************************************************************************************
* FunctionName : TimerInterrupt()
* Description : 定时中断服务函数
* EntryParameter : None
* ReturnValue : None
**************************************************************************************/
void TimerInterrupt(void)
{
    TaskRemarks( );
}