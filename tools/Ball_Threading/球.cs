using System;

namespace ball
{
	/// <summary>
	/// 球 的摘要说明。
	/// </summary>
	public class 球体
	{
		public static float 碰撞耗损=(float)0.4,重力效果=(float)0.4,分离量=(float)0.1;
		public static 球体[] 球体集合;
		public float 半径;				/*	m	*/
		public float 质量;				/*	kg	*/
		public float 速度_x,速度_y;		/*	m/s	*/
		public float 坐标_x,坐标_y;		/*	m	*/
		public 球体(float 坐标_x,float 坐标_y,float 速度_x,float 速度_y,float 半径,float 质量)
		{
			this.坐标_x=坐标_x;
			this.坐标_y=坐标_y;
			this.速度_x=速度_x;
			this.速度_y=速度_y;
			this.半径=半径;
			this.质量=质量;
		}
		
		public static void 更改相撞球速(球体 球体_1,球体 球体_2)
		{
			#region 取得 总动能_x,总动能_y
			float 总动能_x,总动能_y;
			总动能_x=(float)Math.Pow((球体_1.速度_x-球体_2.速度_x),2)/4*(球体_1.质量+球体_2.质量)/2;
			总动能_y=(float)Math.Pow((球体_1.速度_y-球体_2.速度_y),2)/4*(球体_1.质量+球体_2.质量)/2;
			#endregion
			#region 取得 动能变化_x,动能变化_y;
			float 动能变化_x,动能变化_y;
			float 距离_x=(float)Math.Abs(球体_1.坐标_x-球体_2.坐标_x);
			float 距离_y=(float)Math.Abs(球体_1.坐标_y-球体_2.坐标_y);
			float 距离_xy=(float)Math.Pow((距离_x*距离_x+距离_y*距离_y),0.5);
			动能变化_x=(总动能_x+总动能_y)*(距离_x/距离_xy)*(1-碰撞耗损)/2;
			动能变化_y=(总动能_x+总动能_y)*(距离_y/距离_xy)*(1-碰撞耗损)/2;
			#endregion
			#region 取得 两球旧动能
			float 球体_1_动能_x=(float)Math.Pow(球体_1.速度_x,2)*球体_1.质量/2;
			float 球体_2_动能_x=(float)Math.Pow(球体_2.速度_x,2)*球体_2.质量/2;
			float 球体_1_动能_y=(float)Math.Pow(球体_1.速度_y,2)*球体_1.质量/2;
			float 球体_2_动能_y=(float)Math.Pow(球体_2.速度_y,2)*球体_2.质量/2;
			#endregion
			#region 取得 两球新动能
			float 球体_1_新动能_x=0;
			float 球体_2_新动能_x=0;
			float 球体_1_新动能_y=0;
			float 球体_2_新动能_y=0;
			#region x轴动能
			if(球体_1.坐标_x<球体_2.坐标_x)				/*1 向右撞 2*/
			{
				球体_1_新动能_x=球体_1_动能_x-动能变化_x;
				球体_2_新动能_x=球体_2_动能_x+动能变化_x;
			}
			else if(球体_1.坐标_x>球体_2.坐标_x)				/*2 向右撞 1*/
			{
				球体_1_新动能_x=球体_1_动能_x+动能变化_x;
				球体_2_新动能_x=球体_2_动能_x-动能变化_x;
			}
			#endregion
			#region y轴动能
			if(球体_1.坐标_y<球体_2.坐标_y)				/*1 向上撞 2*/
			{
				球体_1_新动能_y=球体_1_动能_y-动能变化_y;
				球体_2_新动能_y=球体_2_动能_y+动能变化_y;
			}
			else if(球体_1.坐标_y>球体_2.坐标_y)				/*2 向上撞 1*/
			{
				球体_1_新动能_y=球体_1_动能_y+动能变化_y;
				球体_2_新动能_y=球体_2_动能_y-动能变化_y;
			}
			#endregion
			#endregion
			#region 将动能转化为速度
			if(球体_1_新动能_x>0)		球体_1.速度_x=(float)Math.Pow(Math.Abs(球体_1_新动能_x/球体_1.质量*2),0.5);
			else if(球体_1_新动能_x<0)	球体_1.速度_x=-1*(float)Math.Pow(Math.Abs(球体_1_新动能_x/球体_1.质量*2),0.5);

			if(球体_2_新动能_x>0)		球体_2.速度_x=(float)Math.Pow(Math.Abs(球体_2_新动能_x/球体_2.质量*2),0.5);
			else if(球体_2_新动能_x<0)	球体_2.速度_x=-1*(float)Math.Pow(Math.Abs(球体_2_新动能_x/球体_2.质量*2),0.5);

			if(球体_1_新动能_y>0)		球体_1.速度_y=(float)Math.Pow(Math.Abs(球体_1_新动能_y/球体_1.质量*2),0.5);
			else if(球体_1_新动能_y<0)	球体_1.速度_y=-1*(float)Math.Pow(Math.Abs(球体_1_新动能_y/球体_1.质量*2),0.5);

			if(球体_2_新动能_y>0)		球体_2.速度_y=(float)Math.Pow(Math.Abs(球体_2_新动能_y/球体_2.质量*2),0.5);
			else if(球体_2_新动能_y<0)	球体_2.速度_y=-1*(float)Math.Pow(Math.Abs(球体_2_新动能_y/球体_2.质量*2),0.5);
			#endregion
		}
		
		public static void 球体碰壁计算()
		{
			for(int i=0;i<球体集合.Length;i++)
			{
				if(i==Form1.鼠标指定球体编号)continue;
				#region 横向处理
				if(球体集合[i].坐标_x<球体集合[i].半径)
				{
					球体集合[i].坐标_x=球体集合[i].半径;
					球体集合[i].速度_x=Math.Abs(球体集合[i].速度_x*(1-碰撞耗损));
				}
				else if(球体集合[i].坐标_x>Draw.Width-球体集合[i].半径)
				{
					球体集合[i].坐标_x=Draw.Width-球体集合[i].半径;
					球体集合[i].速度_x=-Math.Abs(球体集合[i].速度_x*(1-碰撞耗损));
				}
				#endregion
				#region 纵向处理
				if(球体集合[i].坐标_y<球体集合[i].半径)
				{
					球体集合[i].坐标_y=球体集合[i].半径;
					球体集合[i].速度_y=Math.Abs(球体集合[i].速度_y*(1-碰撞耗损));
				}
				else if(球体集合[i].坐标_y>Draw.Height-球体集合[i].半径)
				{
					球体集合[i].坐标_y=Draw.Height-球体集合[i].半径;
					球体集合[i].速度_y=-Math.Abs(球体集合[i].速度_y*(1-碰撞耗损));
				}
				#endregion
			}
		}

		public static void 分离接触球体(球体 球体_1,球体 球体_2)
		{
			do
			{
				if(球体_1.坐标_x<球体_2.坐标_x)
				{
					if(球体_1.坐标_x>球体_1.半径)				球体_1.坐标_x-=分离量;
					else	球体_1.坐标_x=球体_1.半径;

					if(球体_2.坐标_x<Draw.Width-球体_2.半径)	球体_2.坐标_x+=分离量;
					else	球体_2.坐标_x=Draw.Width-球体_2.半径;
				}
				else if(球体_1.坐标_x>球体_2.坐标_x)
				{
					if(球体_1.坐标_x<Draw.Width-球体_1.半径)		球体_1.坐标_x+=分离量;
					else	球体_1.坐标_x=Draw.Width-球体_1.半径;
					
					if(球体_2.坐标_x>球体_2.半径)					球体_2.坐标_x-=分离量;
					else	球体_2.坐标_x=Draw.Width-球体_2.半径;
					
				}
				if(球体_1.坐标_y<球体_2.坐标_y)
				{
					if(球体_1.坐标_y>球体_1.半径)				球体_1.坐标_y-=分离量;
					else	球体_1.坐标_y=球体_1.半径;

					if(球体_2.坐标_y<Draw.Height-球体_2.半径)	球体_2.坐标_y+=分离量;
					else	球体_2.坐标_y=Draw.Height-球体_2.半径;
				}
				else if(球体_1.坐标_y>球体_2.坐标_y)
				{
					if(球体_1.坐标_y<Draw.Height-球体_1.半径)	球体_1.坐标_y+=分离量;
					else	球体_1.坐标_y=Draw.Height-球体_1.半径;
					if(球体_2.坐标_y>球体_2.半径)						球体_2.坐标_y-=分离量;
					else	球体_2.坐标_y=球体_2.半径;
				}
			}
			while(
				(
				(Math.Pow((球体_1.坐标_x-球体_2.坐标_x),2)+
				(Math.Pow((球体_1.坐标_y-球体_2.坐标_y),2)
				)
				<
				Math.Pow((球体_1.半径+球体_2.半径),2))
				));
			string 球="";
		}

		public static void 分离球体集合()
		{
			//处理冲撞_分离接触球体有错
			for(int i=0;i<球体.球体集合.Length;i++)
			{
				if(i==Form1.鼠标指定球体编号)continue;
				for(int j=0;j<球体.球体集合.Length;j++)
				{
					if(j==Form1.鼠标指定球体编号||j==i)continue;
					//分开球,并改变速度
					if(
						(Math.Pow((球体集合[i].坐标_x-球体集合[j].坐标_x),2)+
						Math.Pow((球体集合[i].坐标_y-球体集合[j].坐标_y),2))
						<Math.Pow((球体集合[i].半径+球体集合[j].半径),2))
					{
						分离接触球体(球体集合[i],球体集合[j]);
						更改相撞球速(球体集合[i],球体集合[j]);
					}
				}
			}
		}
	}
}
