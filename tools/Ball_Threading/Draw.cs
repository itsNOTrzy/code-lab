using System;
using System.Drawing;
namespace ball
{
	/// <summary>
	/// Draw 的摘要说明。
	/// </summary>
	public class Draw
	{
		private static Bitmap 图;
		private static Graphics 图纸;
		private static Pen pen=new Pen(Color.Black);
		public static float Width,Height;
		public static void 初始化(int Width,int Height)
		{
			Draw.Width=Width;
			Draw.Height=Height;
			图=new System.Drawing.Bitmap(Width,Height);
			图纸=System.Drawing.Graphics.FromImage(图);
		}
		public static Bitmap Drawing()
		{
			#region 绘图准备
			图纸.Clear(Color.White);
			#endregion
			#region 绘图
			float 半径;
			for(int i=0;i<球体.球体集合.Length;i++)
			{	
				半径=球体.球体集合[i].半径;
				图纸.DrawEllipse(pen,球体.球体集合[i].坐标_x-半径,Height-球体.球体集合[i].坐标_y-半径,半径*2,半径*2);
				if((Form1.鼠标指定球体编号==i)&&
					(Form1.mouse_point[0]!=-1)&&
					(Form1.mouse_point[1]!=-1))
				{
					图纸.DrawLine(pen,
						球体.球体集合[i].坐标_x,
						Height-球体.球体集合[i].坐标_y,
						Form1.mouse_point[0],Form1.mouse_point[1]);
				}
			}
			#endregion
			return 图;
		}
	}
}
