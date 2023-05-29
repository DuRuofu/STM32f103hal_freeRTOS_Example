
#ifndef FREERTOS_CONFIG_H__
#define FREERTOS_CONFIG_H__

/*
 * ���ڱ��ļ������ϸ˵���ɲο���https://blog.csdn.net/zhzht19861011/article/details/50134883#
 */

// ����Ϊ1ʹ����ռʽ��Ϊ0ʹ��ʱ��Ƭ��ת���ȡ�
#define configUSE_PREEMPTION                    1

// ����Ϊ1ʹ�ܵ͹���ticklessģʽ��Ϊ0����ϵͳ���ģ�tick���ж�һֱ���С�
#define configUSE_TICKLESS_IDLE                 0

// ϵͳʱ����Ƶ
#define configCPU_CLOCK_HZ                      72000000

// ϵͳ�����жϵ�Ƶ�ʣ���1s���жϵĴ���������Ϊ1000����һ���1000���жϣ�ϵͳ���ľ���1s��
#define configTICK_RATE_HZ                      1000

// ����������ȼ�������STM32��˵���Ҫ����32
#define configMAX_PRIORITIES                    32

// ������Сջ��С
#define configMINIMAL_STACK_SIZE                64

// FreeRTOR�ѿռ��С
#define configTOTAL_HEAP_SIZE                   8192

// ����������󳤶�
#define configMAX_TASK_NAME_LEN                 16

// ϵͳ���ļ������ı������ͣ�������portTickType�Ǳ�ʾ16λ��������32λ������
#define configUSE_16_BIT_TICKS                  0

// ����Ϊ1����������ȣ�Ϊ0������(ʱ��Ƭ�ľ����ó�CPUʹ��Ȩ)���ò�����ռʽ��ʽ�²���Ч
#define configIDLE_SHOULD_YIELD                 1

// �����Ƿ�ʹ�û�����
#define configUSE_MUTEXES                       1

// �����Ƿ�ʹ�õݹ黥����
#define configUSE_RECURSIVE_MUTEXES             0

// �����Ƿ�ʹ�ü����ź���
#define configUSE_COUNTING_SEMAPHORES           0

// ���ÿ��Լ�¼�Ķ��к��ź����������Ŀ
#define configQUEUE_REGISTRY_SIZE               10

// �Ƿ�ʹ�ÿ��й��Ӻ���
#define configUSE_IDLE_HOOK                     0

// �Ƿ�ʹ��TICK��હ��Ӻ���
#define configUSE_TICK_HOOK                     0

// �Ƿ�ʹ��ջ������
#define configCHECK_FOR_STACK_OVERFLOW          0

// �Ƿ�ʹ���ڴ�����ʧ�ܹ��Ӻ���
#define configUSE_MALLOC_FAILED_HOOK            0

// �Ƿ�ʹ�������ʱ��
#define configUSE_TIMERS                        1

// ���������ʱ������/�ػ����̵����ȼ�
#define configTIMER_TASK_PRIORITY               3

// ���������ʱ��������еĳ���
#define configTIMER_QUEUE_LENGTH                10

// ���������ʱ������/�ػ���������Ķ�ջ���
#define configTIMER_TASK_STACK_DEPTH            configMINIMAL_STACK_SIZE

// STM32��������ȼ�
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   15

// �ܹ����жϷ������а�ȫ����FreeRTOS API���ж�������ȼ�
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 1

#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << 4 )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << 4 )


// �����¶�������Ϊ1�԰���API������������Ϊ0�ų�API����
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


