//------------------------------------------------------------------------
// 潘多拉计划 Pandora_getHighPoints(获取最近区间内“实体柱”的高点，最最高点的及其右侧的那些高点)
// 版本 20160804
// 测试品种 通用
// 周期 通用
// 作者 西门吹雪(QQ:149561420)
//------------------------------------------------------------------------

Params
    NumericArrayRef arr;                    //高点的索引组成的数组
    Numeric s_index;                        //取某段k线进行寻找高点，开始位置的索引

Vars
    Numeric i;
    Numeric real_high;                      //最最高点的值
    Numeric real_high_index;                //最最高点的索引
    NumericArray arr_temp;                  //高点的索引组成的临时数组
    Bool cond_5;                            //最近5根之前满足高点定义
    Bool cond_4;                            //倒数第4根满足高点定义
    Bool cond_3;                            //倒数第3根满足高点定义
    Bool cond_2;                            //倒数第2根满足高点定义
    Bool cond_1;                            //倒数第1根满足高点定义
    Numeric cond_n;                         //5个条件里哪一个满足

Begin
    //获取高点的索引组成的数组，因为在实盘中不能使用未来函数索引不能为负值，此时只能从1到9
    if(CurrentBar >= s_index)
    {
        //先找出整个区域最最高点
        arr_temp[0] = 0;
        for i = CurrentBar - s_index - 5 downto 0
        {
            cond_5                //最近5根之前
            = Max(o[i + 5], c[i + 5]) >= Max(o[i + 9], c[i + 9])
            && Max(o[i + 5], c[i + 5]) >= Max(o[i + 8], c[i + 8])
            && Max(o[i + 5], c[i + 5]) >= Max(o[i + 7], c[i + 7])
            && Max(o[i + 5], c[i + 5]) >= Max(o[i + 6], c[i + 6])
            && Max(o[i + 5], c[i + 5]) >= Max(o[i + 4], c[i + 4])       //画倾斜趋势线可能会遇到连续几根k的高点与当前k的相同
            && Max(o[i + 5], c[i + 5]) > Max(o[i + 3], c[i + 3])
            && Max(o[i + 5], c[i + 5]) > Max(o[i + 2], c[i + 2])
            && Max(o[i + 5], c[i + 5]) > Max(o[i + 1], c[i + 1]);

            cond_4
            = i == 0              //倒数第4根
            && Max(o[i + 4], c[i + 4]) > Max(o[i + 9], c[i + 9])
            && Max(o[i + 4], c[i + 4]) >= Max(o[i + 8], c[i + 8])
            && Max(o[i + 4], c[i + 4]) >= Max(o[i + 7], c[i + 7])
            && Max(o[i + 4], c[i + 4]) >= Max(o[i + 6], c[i + 6])
            && Max(o[i + 4], c[i + 4]) >= Max(o[i + 5], c[i + 5])
            && Max(o[i + 4], c[i + 4]) > Max(o[i + 3], c[i + 3])
            && Max(o[i + 4], c[i + 4]) > Max(o[i + 2], c[i + 2])
            && Max(o[i + 4], c[i + 4]) > Max(o[i + 1], c[i + 1]);

            cond_3
            = i == 0              //倒数第3根
            && Max(o[i + 3], c[i + 3]) > Max(o[i + 9], c[i + 9])
            && Max(o[i + 3], c[i + 3]) > Max(o[i + 8], c[i + 8])
            && Max(o[i + 3], c[i + 3]) >= Max(o[i + 7], c[i + 7])
            && Max(o[i + 3], c[i + 3]) >= Max(o[i + 6], c[i + 6])
            && Max(o[i + 3], c[i + 3]) >= Max(o[i + 5], c[i + 5])
            && Max(o[i + 3], c[i + 3]) >= Max(o[i + 4], c[i + 4])
            && Max(o[i + 3], c[i + 3]) > Max(o[i + 2], c[i + 2])
            && Max(o[i + 3], c[i + 3]) > Max(o[i + 1], c[i + 1]);

            /*cond_2
            = i == 0              //倒数第2根
            && Max(o[i + 2], c[i + 2]) > Max(o[i + 9], c[i + 9])
            && Max(o[i + 2], c[i + 2]) > Max(o[i + 8], c[i + 8])
            && Max(o[i + 2], c[i + 2]) > Max(o[i + 7], c[i + 7])
            && Max(o[i + 2], c[i + 2]) >= Max(o[i + 6], c[i + 6])
            && Max(o[i + 2], c[i + 2]) >= Max(o[i + 5], c[i + 5])
            && Max(o[i + 2], c[i + 2]) >= Max(o[i + 4], c[i + 4])
            && Max(o[i + 2], c[i + 2]) >= Max(o[i + 3], c[i + 3])
            && Max(o[i + 2], c[i + 2]) > Max(o[i + 1], c[i + 1]);

            cond_1
            = i == 0              //倒数第1根
            && Max(o[i + 1], c[i + 1]) > Max(o[i + 9], c[i + 9])
            && Max(o[i + 1], c[i + 1]) > Max(o[i + 8], c[i + 8])
            && Max(o[i + 1], c[i + 1]) > Max(o[i + 7], c[i + 7])
            && Max(o[i + 1], c[i + 1]) > Max(o[i + 6], c[i + 6])
            && Max(o[i + 1], c[i + 1]) >= Max(o[i + 5], c[i + 5])
            && Max(o[i + 1], c[i + 1]) >= Max(o[i + 4], c[i + 4])
            && Max(o[i + 1], c[i + 1]) >= Max(o[i + 3], c[i + 3])
            && Max(o[i + 1], c[i + 1]) >= Max(o[i + 2], c[i + 2]);*/

            /*if(cond_5 || cond_4 || cond_3 || cond_2 || cond_1) {*/
            if(cond_5 || cond_4 || cond_3) {
                if(cond_5) {
                    cond_n = 5;
                } else if(cond_4) {
                    cond_n = 4;
                } else if(cond_3) {
                    cond_n = 3;
                }/* else if(cond_2) {
                    cond_n = 2;
                } else if(cond_1) {
                    cond_n = 1;
                }*/

                NumericArrayInsert(arr_temp, GetNumericArraySize(arr_temp) - 1, CurrentBar - i - cond_n);

                if(real_high <= 0
                    || (real_high > 0 && Max(o[i + cond_n], c[i + cond_n]) > real_high))
                {
                    real_high = Max(o[i + cond_n], c[i + cond_n]);
                    real_high_index = GetNumericArraySize(arr_temp) - 2;
                }
            }
        }
        NumericArrayErase(arr_temp, GetNumericArraySize(arr_temp) - 1, 1);

        //只取最最高点右侧的那些高点
        NumericArrayInsertRange(arr, 0, arr_temp, real_high_index, GetNumericArraySize(arr_temp) - real_high_index);
    }

    return true;
End
