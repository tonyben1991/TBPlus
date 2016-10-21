//------------------------------------------------------------------------
// 潘多拉计划 Pandora_getHighPointsLines(获取最近区间内的高点构成的所有连线组合)
// 版本 20160804
// 测试品种 通用
// 周期 通用
// 作者 西门吹雪(QQ:149561420)
//------------------------------------------------------------------------

Params
    NumericArrayRef arr_line;                   //高点两两连线组成的数组（索引构成）
    Numeric s_index;                            //取某段k线进行寻找高点，开始位置的索引

Vars
    NumericArray arr;                           //高点的索引组成的数组
    Numeric i;
    Numeric j;

Begin
    Pandora_getHighPoints(arr, s_index);

    //遍历高点的索引组成的数组
    if(GetNumericArraySize(arr) > 0)
    {
        arr_line[0] = 0;
        for i = 0 to GetNumericArraySize(arr) - 1
        {
            for j = i + 1 to GetNumericArraySize(arr) - 1
            {
                //距离小于10根k的也剔除掉
                if(arr[j] - arr[i] > 10)
                {
                    NumericArrayInsert(arr_line, GetNumericArraySize(arr_line) - 1, arr[i]);
                    NumericArrayInsert(arr_line, GetNumericArraySize(arr_line) - 1, arr[j]);
                }
            }
        }
        NumericArrayErase(arr_line, GetNumericArraySize(arr_line) - 1, 1);
    }

    return true;
End
