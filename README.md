# mytts
the project of Multi_media course

some references:

 [MFC让你的应用发声](http://www.vephp.com/jiaocheng/9142.html)

[关于Microsoft Speech SDK 中TTS的研究](https://www.cnblogs.com/ChangTan/archive/2011/06/01/2065324.html)

[VC6 MFC里怎么使用TTS朗读中文？]( https://blog.csdn.net/robinson_911/article/details/20388703 )

[microsoft sdk tutorial](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ee125082%28v%3dvs.85%29)

[Microsoft Speech SDK 编程入门](https://www.cnblogs.com/eping/archive/2010/05/23/1742201.html)





used reference:

https://blog.csdn.net/syytem004/article/details/46712253

 https://www.microsoft.com/en-us/download/confirmation.aspx?id=10121 

https://www.microsoft.com/en-us/download/details.aspx?id=27224[pt sdk11, abandoned]

https://blog.csdn.net/yangshuanzhu/article/details/102776607

https://docs.microsoft.com/en-us/previous-versions/office/developer/speech-technologies/hh378466%28v%3doffice.14%29



https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ee450759(v=vs.85)

https://blog.csdn.net/qq_24977505/article/details/78879043

https://blog.csdn.net/lly1122334/article/details/85164058

https://www.cnblogs.com/eping/archive/2010/05/23/1742201.html

https://blog.csdn.net/yu_20501253/article/details/80735699[important!!!!]

https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ee125081(v=vs.85)[SDK Tutorial (SAPI 5.4) 主要看这个]

 https://blog.csdn.net/thecentry/article/details/79505374 

https://blog.csdn.net/wuquanl/article/details/79525314





 https://blog.csdn.net/wtguo1022/article/details/80882899 [MFC中进度条的学习]

[异步播放声音]SPF_ASYNC ，但怎么停止？

找 TTSApp 代码（找到了）



MFC将ListBox内容保存到txt

https://blog.csdn.net/hanxaiojiao/article/details/82733959





 https://blog.51cto.com/9233403/2094577 [CFileDialog文件对话框用法]

# [[MFC\] CFile读写文件实现(高效)](https://www.cnblogs.com/zwh0214/p/6292036.html)

下拉选项框是combo box ，怎样实现读取combo box？【待定】

 https://blog.csdn.net/vistas_fh/article/details/37886113 [ReadString在UNICODE/多字节下中文乱码的解决办法]



关于读utf-8 的 txt 进 unicode 的MFC：



~~~
CString CMytts3Dlg::getUtf8File(CString filename)
{
	CFile file;
	CString strFile;
	if (! file.Open(filename, CFile::modeRead | CFile::typeBinary))
		return NULL;

	// 判断有无utf-8标志头。如果有的话就先读掉，没有的话得重新回到起点。
	BYTE head[3];
	file.Read(head, 3);
	if (!(head[0] == 0xEF && head[1] == 0xBB && head[2] == 0xBF))
	{
		file.SeekToBegin();
	}


	ULONGLONG FileSize = file.GetLength();
	char* pContent = (char*)calloc(FileSize + 1, sizeof(char));
	file.Read(pContent, FileSize);
	
	int n = MultiByteToWideChar(CP_UTF8, 0, pContent, FileSize + 1, NULL, 0);
	wchar_t* pWideChar = (wchar_t*)calloc(n + 1, sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, pContent, FileSize + 1, pWideChar, n);
	strFile = CString(pWideChar);

	//释放空间
	file.Close();
	free(pContent);
	free(pWideChar);

	return strFile;
}
~~~





~~~
	CString tan = getUtf8File(openfilename);
	//namelist.AddString(tan);
	MessageBox(tan, _T("添加成功2！"), MB_OK);
	UpdateWindow();

	while (TRUE)
	{
		int index = tan.Find(_T("\r\n"));
		if (index == -1)
		{
			namelist.AddString(tan);
			break;
		}
		namelist.AddString(tan.Left(index));
		tan = tan.Right(tan.GetLength() - index - 1);
	}
~~~





写入不是乱码。

![1589644952903](C:\Users\fitar\AppData\Roaming\Typora\typora-user-images\1589644952903.png)





![1589549656324](C:\Users\fitar\AppData\Roaming\Typora\typora-user-images\1589549656324.png)



1. 

2. 设计部分，包括代码整体结构，关键数据类型，关键函数。这门课的还得画个流程图。

   这部分先不急管它，明两天我把代码大部分写完之后做起来就很简单。