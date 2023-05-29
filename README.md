# 开发记录
### 说明：

1. 本文档由DuRuofu撰写，由DuRuofu负责解释及执行。

### 修订历史：

|  文档名称  |  版本  |  作者  |      时间      |   备注   |
| ---- | ---- | ------------ | ------ |
| STM32F1系列移植freertos |v1.0.0| DuRuofu | 2023-05-29 | 首次建立 |

# STM32F1系列移植freertos

## 以STM32F103ZET6为例：

### 1. 准备空白工程
这里使用STM32cudemx生成示例代码（点灯代码）：
![](attachments/Pasted%20image%2020230529182242.png)
生成代码如下：
![](attachments/Pasted%20image%2020230529182408.png)
![](attachments/Pasted%20image%2020230529182424.png)
#### 注意事项：

由于[FreeRTOS](https://so.csdn.net/so/search?q=FreeRTOS&spm=1001.2101.3001.7020)使用系统嘀嗒定时器当作心跳，HAL库也使用了这个定时器当作超时计数用，FreeRTOS和HAL库不能同时使用SysTick定时器，所在在这里将HAL库的定时器改为其他的定时器，这里改成了定时器4：
![](attachments/Pasted%20image%2020230529202102.png)

配置中断，注意这里一定要选择组4，也就是全部为抢占优先级：
![](attachments/Pasted%20image%2020230529202123.png)
### 2. 准备freertos源码
去freertos官网下载源码：https://www.freertos.org/zh-cn-cmn-s/a00104.html
![](attachments/Pasted%20image%2020230529183846.png)
内容如下：
![](attachments/Pasted%20image%2020230529184132.png)
![](attachments/Pasted%20image%2020230529184333.png)
![](attachments/Pasted%20image%2020230529184422.png)
![](attachments/Pasted%20image%2020230529184457.png)
![](attachments/Pasted%20image%2020230529184524.png)
![](attachments/Pasted%20image%2020230529184734.png)
### 3.进行代码裁剪：
删除不必要的文件：
**portable文件夹：**
![](attachments/Pasted%20image%2020230529185245.png)
![](attachments/Pasted%20image%2020230529185516.png)
**MemMang文件夹：**
![](attachments/Pasted%20image%2020230529185416.png)
![](attachments/Pasted%20image%2020230529185501.png)
### 4. 将文件添加到工程：

在项目里新建文件夹：根目录/Middlewares /FreeRTOS
![](attachments/Pasted%20image%2020230529185926.png)
将 FreeRTOS  内核源码的 Source 文件夹下的所有文件添加到工程的 FreeRTOS 文件夹中
![](attachments/Pasted%20image%2020230529190714.png)

在工程分组里添加新的分组，分 别 为 Middlewares/FreeRTOS_CORE 和  Middlewares/FreeRTOS_PORT，如下图所示：
![](attachments/Pasted%20image%2020230529190427.png)
Middlewares/FreeRTOS_CORE 分组用于存放 FreeRTOS 的内核 C 源码文件， 将 FreeRTOS 目录下所有的 FreeRTOS 的内核 C 源文件添加到  Middlewares/FreeRTOS_CORE 分组中。  

Middlewares/FreeRTOS_PORT 分组用于存放 FreeRTOS 内核的移植文件，需要添加两个文件到这个分组，分别为 heap_x.c 和 port.c。
首先是 heap_x.c， 在路径 FreeRTOS/portable/MemMang 下有五个 C 源文件，这五个 C 源文  件对应了五种 FreeRTOS 提供的内存管理算法，读者在进行 FreeRTOS 移植的时候可以根据需  求选择合适的方法，具体这五种内存管理的算法，在后续 FreeRTOS 内存管理章节会具体分析，  这里就先使用 heap_4.c，将 heap_4.c 添加到 Middlewares/FreeRTOS_PORT 分组中。  
接着是 port.c， port.c 是 FreeRTOS 这个软件与 MCU 这个硬件连接的桥梁，因此对于 STM32 系列不同的开发板，所使用的 port.c 文件是不同的。 port.c 文件的路径在  FreeRTOS/portable/RVDS 下。进入到 FreeRTOS/portable/RVDS，可以看到 FreeRTOS 针对不同  的 MCU 提供了不同的 port.c 文件，具体STM32 系列开发板与不同 port.c 的对应关 系如下表所示：
![](attachments/Pasted%20image%2020230529190854.png)
将所有 FreeRTOS 相关的所需文件添加到工程后，如下图所示：
![](attachments/Pasted%20image%2020230529191013.png)

### 5.添加头文件路径

![](attachments/Pasted%20image%2020230529191219.png)

### 6.添加并修改 FreeRTOSConfig.h 文件
FreeRTOSConfig.h 是 FreeRTOS 操作系统的配置文件， FreeRTOS 操作系统是可裁剪的，用  户可以根据需求对 FreeRTOS 进行裁剪，裁剪掉不需要用到的 FreeRTOS 功能.

新建空白的FreeRTOSConfig.h到core/inc文件夹；
![](attachments/Pasted%20image%2020230529192131.png)

**修改FreeRTOSConfig.h**：
添加代码：

```

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




```

### 7.修改 stm32f1xx_it.c文件

打开`stm32f1xx_it.c`文件，在头部添加FreeRTOS的三个函数导入：
```c
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vPortSVCHandler(void);
```
![](attachments/Pasted%20image%2020230529201451.png)
在函数`SVC_Handler`中添加函数调用：
![](attachments/Pasted%20image%2020230529201504.png)
在函数`PendSV_Handler`中添加函数调用：
![](attachments/Pasted%20image%2020230529201514.png)
在函数`SysTick_Handler`中添加函数调用：
![](attachments/Pasted%20image%2020230529201526.png)


### 8.建立工程进行测试
main.c里添加头文件：
```c
#include "FreeRTOSConfig.h" 
#include "FreeRTOS.h" 
#include "task.h"
```
新建两个点灯任务：

```c
void LED1Tesk(void *p)
{
    while(1)
    {
        //功能
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
        vTaskDelay(1000);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET); 
        vTaskDelay(1000);
	}
}

void LED2Tesk(void *p)
{
    while(1)
    {
        //功能
        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);
        vTaskDelay(500);
        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET); 
        vTaskDelay(500);
	}
}
```
开启任务：
![](attachments/Pasted%20image%2020230529201902.png)
两个灯交替闪烁，移植成功！

总结：移植FreeRTOS还是相对简单的，主要是配置文件`FreeRTOSConfig.h`的配置，每个宏定义所代表的意思需要好好查阅！

# 参考链接

FreeRTOS之在STM32F103移植
https://blog.csdn.net/m0_37895576/article/details/120435482

STM32CubeMX | STM32使用HAL库手动移植FreeRTOS10.4.1
https://blog.csdn.net/qq153471503/article/details/108999523