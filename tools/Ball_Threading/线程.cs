using System;
using System.Threading;
namespace ball
{
	/// <summary>
	/// 线程 的摘要说明。
	/// </summary>
	public class 线程
	{
		private static Thread 线程_绘图;
		private static Thread 线程_计时器;
		public static void 启动线程()
		{
			//第一次
			try
			{
				线程_计时器.ThreadState.ToString().Equals("Un星体ted, AbortRequested");
			}
			catch(System.NullReferenceException)
			{
				线程_计时器=new Thread(new ThreadStart(Thread_times));
				线程_计时器.Start();
				return;
			}	
			//等待终止
			while(!线程_计时器.ThreadState.ToString().Equals("Stopped"))
			{
				线程_计时器.Join(50);
			}
			线程_计时器=new Thread(new ThreadStart(Thread_times));
			线程_计时器.Start();
		}

		public static void 暂停线程()
		{
			线程_计时器.Abort();
		}
		private static void Thread_times()
		{
			while(true)
			{
				try
				{
					if(	线程_绘图.ThreadState.ToString().Equals("Stopped"))
					{
						线程_绘图=new Thread(new ThreadStart(Thread_drawing));
						//线程_绘图.Priority=System.Threading.ThreadPriority.Highest;
						线程_绘图.Start();
						线程_计时器.Join(50);
					}
					else
					{
						//使主线程暂停
						线程_计时器.Join(5);
					}
				}
				catch(System.NullReferenceException)
				{
					线程_绘图=new Thread(new ThreadStart(Thread_drawing));
					线程_绘图.Start();
				}
			}
		}
		private static void Thread_drawing()
		{
			for(int i=0;i<球体.球体集合.Length;i++)
			{
				if(i==Form1.鼠标指定球体编号)continue;
				球体.球体集合[i].速度_y-=球体.重力效果;
				球体.球体集合[i].坐标_x+=球体.球体集合[i].速度_x;
				球体.球体集合[i].坐标_y+=球体.球体集合[i].速度_y;
			}
			球体.球体碰壁计算();
			球体.分离球体集合();

			Form1.窗体指针.listBox1_显示参数();
			Form1.窗体指针.pictureBox1.Image=Draw.Drawing();
			线程_绘图.Abort();	
		}
	}
}
