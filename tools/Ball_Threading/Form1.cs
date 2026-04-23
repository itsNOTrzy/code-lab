using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
namespace ball
{
	/// <summary>
	/// Form1 的摘要说明。
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.ComponentModel.Container components = null;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.ListBox listBox1;
		public static int 鼠标指定球体编号=-1;
		public static int[] mouse_point=new int[2];
		public System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.Label label1;
		public static Form1 窗体指针;
		public Form1()
		{
			//
			// Windows 窗体设计器支持所必需的
			//
			InitializeComponent();

			//
			// TODO: 在 InitializeComponent 调用后添加任何构造函数代码
			//
			Form1.窗体指针=this;
		}

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows 窗体设计器生成的代码
		/// <summary>
		/// 设计器支持所需的方法 - 不要使用代码编辑器修改
		/// 此方法的内容。
		/// </summary>
		private void InitializeComponent()
		{
			this.button1 = new System.Windows.Forms.Button();
			this.listBox1 = new System.Windows.Forms.ListBox();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(448, 368);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(40, 24);
			this.button1.TabIndex = 1;
			this.button1.Text = "运行";
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// listBox1
			// 
			this.listBox1.ItemHeight = 12;
			this.listBox1.Location = new System.Drawing.Point(0, 368);
			this.listBox1.Name = "listBox1";
			this.listBox1.Size = new System.Drawing.Size(344, 16);
			this.listBox1.TabIndex = 3;
			// 
			// pictureBox1
			// 
			this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pictureBox1.Location = new System.Drawing.Point(0, 0);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(488, 368);
			this.pictureBox1.TabIndex = 6;
			this.pictureBox1.TabStop = false;
			this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
			this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(344, 368);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(112, 16);
			this.label1.TabIndex = 4;
			this.label1.Text = "请用左键捡球";
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 14);
			this.ClientSize = new System.Drawing.Size(488, 437);
			this.Controls.Add(this.pictureBox1);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.listBox1);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// 应用程序的主入口点。
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		//将double取整
		private int int_double(double xy)
		{
			//将double类型的小数部分去掉，之后返回int数
			string strX=xy.ToString(),int_string;
			char[] CopyToX=new char[strX.Length];
			strX.CopyTo(0,CopyToX,0,strX.Length);

			int_string="";
			for(int i=0;i<strX.Length;i++)
			{
				if(CopyToX[i]!='.')int_string=int_string+CopyToX[i];
				else break;
			}
			return int.Parse(int_string);
		}

		//输出球体信息
		public void listBox1_显示参数()
		{
			listBox1.Items.Clear();
			string 显示信息;
			for(int i=0;i<球体.球体集合.Length;i++)
			{
				显示信息=i.ToString()+"\t";
				显示信息+=球体.球体集合[i].坐标_x.ToString()+"\t";
				显示信息+=球体.球体集合[i].坐标_y.ToString()+"\t";
				显示信息+=球体.球体集合[i].速度_x.ToString()+"\t";
				显示信息+=球体.球体集合[i].速度_y.ToString()+"\t";
				listBox1.Items.Add(显示信息);
			}
			listBox1.SelectedIndex=鼠标指定球体编号;
		}
		private void button1_Click(object sender, System.EventArgs e)
		{
			
			if(button1.Text.Equals("运行"))
			{
				button1.Text="暂停";
				线程.启动线程();
			}
			else
			{
				button1.Text="运行";
				线程.暂停线程();
			}
		}
		private void Form1_Load(object sender, System.EventArgs e)
		{
			球体.球体集合=new 球体[3];
			float 半径;
			for(int i=0;i<球体.球体集合.Length;i++)
			{
				半径=i*2+10;
				球体.球体集合[i]=new 球体(40*i+50,40*i+50,0,0,半径,半径*半径*半径);
			}
			Draw.初始化(pictureBox1.Width,pictureBox1.Height);
			this.listBox1.Size = new System.Drawing.Size(listBox1.Size.Width,(球体.球体集合.Length-1)*12+16);
			mouse_point[0]=-1;
			mouse_point[1]=-1;
		}

		private void pictureBox1_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			for(int i=0;i<球体.球体集合.Length;i++)
			{
				if(i==鼠标指定球体编号)
				{
					球体.球体集合[i].坐标_x=e.X;//-球体.球体集合[i].半径;
					球体.球体集合[i].坐标_y=Draw.Height-e.Y;
					球体.球体集合[i].速度_x=0;
					球体.球体集合[i].速度_y=0;
				}
			}
		}

		private void pictureBox1_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			if(e.Button==MouseButtons.Left)
			{
				if(鼠标指定球体编号==-1)
				{
					double 半径平方=0,距离_x,距离_y;
					for(int i=0;i<球体.球体集合.Length;i++)
					{
						半径平方=Math.Pow(球体.球体集合[i].半径,2);
						距离_x=Math.Pow((e.X-球体.球体集合[i].坐标_x),2);
						距离_y=Math.Pow((e.Y-(Draw.Height-球体.球体集合[i].坐标_y)),2);
						if(距离_x+距离_y<半径平方)
						{
							鼠标指定球体编号=i;
						}
					}
					if(鼠标指定球体编号!=-1)
					{
						label1.Text="锁定"+鼠标指定球体编号.ToString();
						label1.Text=label1.Text+",用右键设置蓄力点";
					}
				}
				else
				{
					//为防出错,如果没有蓄力点,此球自由下落
					if(mouse_point[0]==-1&&mouse_point[1]==-1)
					{
						球体.球体集合[鼠标指定球体编号].速度_x=0;
						球体.球体集合[鼠标指定球体编号].速度_y=0;
						鼠标指定球体编号=-1;
					}
					else
					{
						球体.球体集合[鼠标指定球体编号].速度_x=e.X-mouse_point[0];
						球体.球体集合[鼠标指定球体编号].速度_y=mouse_point[1]-e.Y;
						鼠标指定球体编号=-1;
					}
					label1.Text="请用左键捡球";
					mouse_point[0]=-1;
					mouse_point[1]=-1;
				}
				
			}
			else if(e.Button==MouseButtons.Right)
			{
				if(鼠标指定球体编号!=-1)
				{
					mouse_point[0]=e.X;
					mouse_point[1]=e.Y;
				}
				label1.Text="请按左键发射";
			}
		}

	}
}
