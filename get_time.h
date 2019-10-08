/*  get_time() 用来辅助计算命令的耗时     */
/*    使用方法：放置与要计算的语句前后两端     */
/*  将所得的时间相减，即为所耗时间。单位为微秒 */


#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h> 


long get_time()
{
    struct timeval tv;
    
    
    gettimeofday(&tv,nullptr);

    long res  = tv.tv_sec * 1000000 + tv.tv_usec ;

    return res;
}
