
#ifndef FREERTOS_CONFIG_H__
#define FREERTOS_CONFIG_H__

/*
 * 关于本文件宏的详细说明可参考：https://blog.csdn.net/zhzht19861011/article/details/50134883#
 */

// 设置为1使用抢占式，为0使用时间片轮转调度。
#define configUSE_PREEMPTION                    1

// 设置为1使能低功耗tickless模式，为0保持系统节拍（tick）中断一直运行。
#define configUSE_TICKLESS_IDLE                 0

// 系统时钟主频
#define configCPU_CLOCK_HZ                      72000000

// 系统节拍中断的频率，即1s进中断的次数，配置为1000就是一秒进1000次中断，系统节拍就是1s。
#define configTICK_RATE_HZ                      1000

// 任务最大优先级，对于STM32来说最大不要超过32
#define configMAX_PRIORITIES                    32

// 任务最小栈大小
#define configMINIMAL_STACK_SIZE                64

// FreeRTOR堆空间大小
#define configTOTAL_HEAP_SIZE                   8192

// 任务名称最大长度
#define configMAX_TASK_NAME_LEN                 16

// 系统节拍计数器的变量类型，即定义portTickType是表示16位变量还是32位变量。
#define configUSE_16_BIT_TICKS                  0

// 设置为1允许任务调度，为0不允许(时间片耗尽才让出CPU使用权)，该参数抢占式方式下才生效
#define configIDLE_SHOULD_YIELD                 1

// 设置是否使用互斥量
#define configUSE_MUTEXES                       1

// 设置是否使用递归互斥量
#define configUSE_RECURSIVE_MUTEXES             0

// 设置是否使用计数信号量
#define configUSE_COUNTING_SEMAPHORES           0

// 设置可以记录的队列和信号量的最大数目
#define configQUEUE_REGISTRY_SIZE               10

// 是否使用空闲钩子函数
#define configUSE_IDLE_HOOK                     0

// 是否使用TICK嘀嗒钩子函数
#define configUSE_TICK_HOOK                     0

// 是否使用栈溢出检查
#define configCHECK_FOR_STACK_OVERFLOW          0

// 是否使用内存申请失败钩子函数
#define configUSE_MALLOC_FAILED_HOOK            0

// 是否使用软件定时器
#define configUSE_TIMERS                        1

// 设置软件定时器服务/守护进程的优先级
#define configTIMER_TASK_PRIORITY               3

// 设置软件定时器命令队列的长度
#define configTIMER_QUEUE_LENGTH                10

// 设置软件定时器服务/守护进程任务的堆栈深度
#define configTIMER_TASK_STACK_DEPTH            configMINIMAL_STACK_SIZE

// STM32的最低优先级
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   15

// 能够在中断服务函数中安全调用FreeRTOS API的中断最低优先级
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 1

#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << 4 )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << 4 )


// 将以下定义设置为1以包含API函数，或设置为0排除API函数
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_xResumeFromISR                  1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_xTimerGetTimerDaemonTaskHandle  0
#define INCLUDE_pcTaskGetTaskName               0
#define INCLUDE_eTaskGetState                   0
#define INCLUDE_xEventGroupSetBitFromISR        1
#define INCLUDE_xTimerPendFunctionCall          0

#endif  /* FREERTOS_CONFIG_H__ */


