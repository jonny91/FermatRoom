/*********************************************************/
/*                                                       */
/* MP3操作指令                                           */
/*                                                       */
/*********************************************************/
void playMp3(int musicId)
{
		send(0X7E);//指令开始位
		send(0X04);//说明指令长度
		send(0X41);//指定文件夹播放
		send(0X00);//定位到名称为“01”的文件夹
		send(musicId);//播放第1个音频文件
		send(0XEF);//指令结束位 
}

void mp3(unsigned char comd)
{
  switch(comd)
	  {
	    case 0X00: send(0X7E);//指令开始位
				   send(0X04);//说明指令长度
				   send(0X41);//指定文件夹播放
				   send(0X00);//定位到名称为“01”的文件夹
				   send(0x01);//播放第1个音频文件
				   send(0XEF);//指令结束位 
		   	   break;
		case 0X07: send(0X7E);//指令开始位
				   send(0X04);//说明指令长度
				   send(0X41);//指定文件夹播放
				   send(0X00);//定位到名称为“01”的文件夹
				   send(0x02);//播放第2个音频文件
				   send(0XEF);//指令结束位 
		   	   break;
		case 0X08: send(0X7E);//指令开始位
				   send(0X04);//说明指令长度
				   send(0X41);//指定文件夹播放
				   send(0X00);//定位到名称为“01”的文件夹
				   send(0x03);//播放第3个音频文件
				   send(0XEF);//指令结束位 
		   	   break;
		case 0X01: 
					 send(0X7E);//指令开始位
				   send(0X02);//说明指令长度
				   send(0X01);//播放
				   send(0XEF);//指令结束位 
		   	   break;
		case 0X02: send(0X7E);//指令开始位
				   send(0X02);//说明指令长度
				   send(0x02);//暂停
				   send(0XEF);//指令结束位 
		   	       break;
		case 0X03: send(0X7E);//指令开始位
				   send(0X02);//说明指令长度
				   send(0X03);//下一曲
				   send(0XEF);//指令结束位 
		   	       break;
		case 0X04: send(0X7E);//指令开始位
				   send(0X02);//说明指令长度
				   send(0X04);//上一曲
				   send(0XEF);//指令结束位 
		   	       break; 
		   	       break;
		case 0X05: send(0X7E);//指令开始位
				   send(0X02);//说明指令长度
				   send(0X05);//音量加
				   send(0XEF);//指令结束位 
		   	       break; 
		   	       break;
		case 0X06: send(0X7E);//指令开始位
				   send(0X02);//说明指令长度
				   send(0X06);//音量减
				   send(0XEF);//指令结束位 
		   	       break;
		case 0X31: send(0X7E);//指令开始位
				   send(0X03);//说明指令长度
				   send(0X31);//设置音量
				   send(0X14);//20
				   send(0XEF);//指令结束位 
		   	       break;
		case 0X33: send(0X7E);//指令开始位
				   send(0X03);//说明指令长度
				   send(0X33);//设置循环模式
				   send(0X01);//文件夹循环
				   send(0XEF);//指令结束位 
		   	       break;


	  }
  
}
/*********************************************************/
/*                                                       */
/* MP3初始化                                             */
/*                                                       */
/*********************************************************/
void mp3_init()
{
  mp3(0x33);                 //设置循环模式为文件夹循环
  mp3(0x31);                 //设置音量为20
  //mp3(0x00);                 //开机播放

  /*不关闭串行中断的话一上电就会发送STOP，这样会影响曲名和播放歌曲的对应关系*/
  ES=0;					   //串行中断禁止
  delay_ms(100);			   //等待MP3准备好
  ES=1;
}