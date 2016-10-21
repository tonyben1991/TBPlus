//------------------------------------------------------------------------
// 潘多拉计划 Pandora_getLowPoints(获取最近区间内“实体柱”的低点，最最低点的及其右侧的那些低点)
// 版本 20160809
// 测试品种 通用
// 周期 通用
// 作者 西门吹雪(QQ:149561420)
//------------------------------------------------------------------------

Params
    NumericArrayRef arr;                    //低点的索引组成的数组
    Numeric s_index;                        //取某段k线进行寻找低点，开始位置的索引

Vars
    Numeric i;
    Numeric real_low;                       //最最低点的值
    Numeric real_low_index;                 //最最低点的索引
    NumericArray arr_temp;                  //低点的索引组成的临时数组
    Bool cond_5;                            //最近5根之前满足低点定义
    Bool cond_4;                            //倒数第4根满足低点定义
    Bool cond_3;                            //倒数第3根满足低点定义
    Bool cond_2;                            //倒数第2根满足低点定义
    Bool cond_1;                            //倒数第1根满足低点定义
    Numeric cond_n;                         //5个条件里哪一个满足

Begin
    //获取低点的索引组成的数组，因为在实盘中不能使用未来函数索引不能为负值，此时只能从1到9
    if(CurrentBar >= s_index)
    {
        //先找出整个区域最最低点
        arr_temp[0] = 0;
        for i = CurrentBar - s_index - 5 downto 0
        {
            cond_5                //最近5根之前
            = Min(o[i + 5], c[i + 5]) <= Min(o[i + 9], c[i + 9])
            && Min(o[i + 5], c[i + 5]) <= Min(o[i + 8], c[i + 8])
            && Min(o[i + 5], c[i + 5]) <= Min(o[i + 7], c[i + 7])
            && Min(o[i + 5], c[i + 5]) <= Min(o[i + 6], c[i + 6])       //画倾斜趋势线可能会遇到连续几根k的低点与当前k的相同
            && Min(o[i + 5], c[i + 5]) < Min(o[i + 4], c[i + 4])
            && Min(o[i + 5], c[i + 5]) < Min(o[i + 3], c[i + 3])
            && Min(o[i + 5], c[i + 5]) < Min(o[i + 2], c[i + 2])
            && Min(o[i + 5], c[i + 5]) < Min(o[i + 1], c[i + 1]);

            cond_4
            = i == 0              //倒数第4根
            && Min(o[i + 4], c[i + 4]) < Min(o[i + 9], c[i + 9])
            && Min(o[i + 4], c[i + 4]) <= Min(o[i + 8], c[i + 8])
            && Min(o[i + 4], c[i + 4]) <= Min(o[i + 7], c[i + 7])
            && Min(o[i + 4], c[i + 4]) <= Min(o[i + 6], c[i + 6])
            && Min(o[i + 4], c[i + 4]) <= Min(o[i + 5], c[i + 5])
            && Min(o[i + 4], c[i + 4]) < Min(o[i + 3], c[i + 3])
            && Min(o[i + 4], c[i + 4]) < Min(o[i + 2], c[i + 2])
            && Min(o[i + 4], c[i + 4]) < Min(o[i + 1], c[i + 1]);

            cond_3
            = i == 0              //倒数第3根
            && Min(o[i + 3], c[i + 3]) < Min(o[i + 9], c[i + 9])
            && Min(o[i + 3], c[i + 3]) < Min(o[i + 8], c[i + 8])
            && Min(o[i + 3], c[i + 3]) <= Min(o[i + 7], c[i + 7])
            && Min(o[i + 3], c[i + 3]) <= Min(o[i + 6], c[i + 6])
            && Min(o[i + 3], c[i + 3]) <= Min(o[i + 5], c[i + 5])
            && Min(o[i + 3], c[i + 3]) <= Min(o[i + 4], c[i + 4])
            && Min(o[i + 3], c[i + 3]) < Min(o[i + 2], c[i + 2])
            && Min(o[i + 3], c[i + 3]) < Min(o[i + 1], c[i + 1]);

            /*cond_2
            = i == 0              //倒数第2根
            && Min(o[i + 2], c[i + 2]) < Min(o[i + 9], c[i + 9])
            && Min(o[i + 2], c[i + 2]) < Min(o[i + 8], c[i + 8])
            && Min(o[i + 2], c[i + 2]) < Min(o[i + 7], c[i + 7])
            && Min(o[i + 2], c[i + 2]) <= Min(o[i + 6], c[i + 6])
            && Min(o[i + 2], c[i + 2]) <= Min(o[i + 5], c[i + 5])
            && Min(o[i + 2], c[i + 2]) <= Min(o[i + 4], c[i + 4])
            && Min(o[i + 2], c[i + 2]) <= Min(o[i + 3], c[i + 3])
            && Min(o[i + 2], c[i + 2]) < Min(o[i + 1], c[i + 1]);

            cond_1
            = i == 0              //倒数第1根
            && Min(o[i + 1], c[i + 1]) < Min(o[i + 9], c[i + 9])
            && Min(o[i + 1], c[i + 1]) < Min(o[i + 8], c[i + 8])
            && Min(o[i + 1], c[i + 1]) < Min(o[i + 7], c[i + 7])
            && Min(o[i + 1], c[i + 1]) < Min(o[i + 6], c[i + 6])
            && Min(o[i + 1], c[i + 1]) <= Min(o[i + 5], c[i + 5])
            && Min(o[i + 1], c[i + 1]) <= Min(o[i + 4], c[i + 4])
            && Min(o[i + 1], c[i + 1]) <= Min(o[i + 3], c[i + 3])
            && Min(o[i + 1], c[i + 1]) <= Min(o[i + 2], c[i + 2]);*/

            /*if(cond_5 || cond_4 || cond_3 || cond_2 || cond_1) {*/
            if(cond_5 || cond_4 || cond_3)
            {
                if(cond_5)
                {
                    cond_n = 5;
                }
                else if(cond_4)
                {
                    cond_n = 4;
                }
                else if(cond_3)
                {
                    cond_n = 3;
                }/* else if(cond_2) {
                    cond_n = 2;
                } else if(cond_1) {
                    cond_n = 1;
                }*/

                NumericArrayInsert(arr_temp, GetNumericArraySize(arr_temp) - 1, CurrentBar - i - cond_n);

                if(real_low <= 0
                    || (real_low > 0 && Min(o[i + cond_n], c[i + cond_n]) < real_low)) 
                {
                    real_low = Min(o[i + cond_n], c[i + cond_n]);
                    real_low_index = GetNumericArraySize(arr_temp) - 2;
                }
            }
        }
        NumericArrayErase(arr_temp, GetNumericArraySize(arr_temp) - 1, 1);

        //只取最最低点右侧的那些低点
        NumericArrayInsertRange(arr, 0, arr_temp, real_low_index, GetNumericArraySize(arr_temp) - real_low_index);
    }

    return true;
End
