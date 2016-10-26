/*******************************************************************************
            > 文件:TriangleTest_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-10-26

            > 策略原理:
                1.三角形形态识别函数测试
            > 测试品种:
                1.通用
            > 适用周期:
                1.通用
            > 参数列表:
                1.
*******************************************************************************/

Params
    Numeric Length(100);        //判断周期长短

Vars


Begin
    if (Triangle_Tony(Length))
    {
        PlotBool("T", True);
    }

End
