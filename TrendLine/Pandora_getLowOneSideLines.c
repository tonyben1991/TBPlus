//------------------------------------------------------------------------
// 潘多拉计划 Pandora_getLowOneSideLines(获取最近区间内的低点构成的所有连线组合里，能让其他点都落在该连线同一侧的连线集合)
// 版本 20160809
// 测试品种 通用
// 周期 通用
// 作者 西门吹雪(QQ:149561420)
//------------------------------------------------------------------------

Params
    NumericArrayRef arr_oneside_lines;          //低点两两连线组成的数组（索引构成）
    Numeric s_index;                            //取某段k线进行寻找高点，开始位置的索引

Vars
    NumericArray arr_lines;                     //低点的索引两两连线组成的数组
    NumericArray arr_points;                    //低点的索引组成的数组
    Numeric b;                                  //直线方程 y = kx + b 的纵截距b
    Numeric k;                                  //直线方程 y = kx + b 的斜率k
    Numeric i;
    Numeric j;
    Bool is_one_side;                           //所有点是否都在线的一侧

Begin
    Pandora_getLowPointsLines(arr_lines, s_index);
    Pandora_getLowPoints(arr_points, s_index);

    //遍历低点的索引组成的数组
    if(GetNumericArraySize(arr_lines) > 0 && GetNumericArraySize(arr_points) > 0)
    {
        arr_oneside_lines[0] = 0;
        for i = 0 to GetNumericArraySize(arr_lines) / 2 - 1
        {
            k = (Min(o[CurrentBar - arr_lines[i * 2 + 1]], c[CurrentBar - arr_lines[i * 2 + 1]])
                - Min(o[CurrentBar - arr_lines[i * 2]], c[CurrentBar - arr_lines[i * 2]])) / (arr_lines[i * 2 + 1] - arr_lines[i * 2]);    //k = (y2 - y1) / (x2 - x1)
            b = Min(o[CurrentBar - arr_lines[i * 2]], c[CurrentBar - arr_lines[i * 2]]) - arr_lines[i * 2] * k; //b = y1 - k * x1

            is_one_side = true;

            for j = 0 to GetNumericArraySize(arr_points) - 1
            {
                //当前直线的这两个端点剔除掉
                if(arr_lines[i * 2 + 1] != arr_points[j] && arr_lines[i * 2] != arr_points[j])
                {
                    if(Min(o[CurrentBar - arr_points[j]], c[CurrentBar - arr_points[j]]) <= b + k * arr_points[j])
                    {    //因为是低点的趋势线，所以判断是否在直线的上方，依据y = b + kx，y3 > y则在线上方，否则只要有一个点不满足is_one_side条件都过滤掉
                        is_one_side = false;
                        break;
                    }
                }
            }

            //如果所有点都在线的一侧，且斜率是正的
            if(is_one_side && k >= 0)
            {
                NumericArrayInsert(arr_oneside_lines, GetNumericArraySize(arr_oneside_lines) - 1, arr_lines[i * 2]);
                NumericArrayInsert(arr_oneside_lines, GetNumericArraySize(arr_oneside_lines) - 1, arr_lines[i * 2 + 1]);
            }
        }
        NumericArrayErase(arr_oneside_lines, GetNumericArraySize(arr_oneside_lines) - 1, 1);
    }

    return true;
End
