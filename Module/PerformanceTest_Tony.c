/****************************************************************************************
            > 文件: PerformanceTest_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-10-10-09.00

            > 模块功能: 测试策略的性能
****************************************************************************************/

Params

Vars

Begin
    if (0 == BarStatus)
    {
        FileDelete("E:\\Workspace\\TBPlusTest.txt");
        Commentary(TimeToString(CurrentTime));  //打印策略开始回测时间
        FileAppend("E:\\Workspace\\TBPlusTest.txt", TimeToString(CurrentTime));
        FileAppend("E:\\Workspace\\TBPlusTest.txt", "");
    }

    if (2 == BarStatus)
    {
        Commentary(TimeToString(CurrentTime));  //打印策略完成回测时间
        FileAppend("E:\\Workspace\\TBPlusTest.txt", TimeToString(CurrentTime));
    }

End
