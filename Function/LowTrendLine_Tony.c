//------------------------------------------------------------------------
// 潘多拉计划 LowTrendLine(获取最近区间内的低点构成的趋势线)
// 版本 20160810
// 测试品种 通用
// 周期 通用(默认15分钟周期)
// 作者 西门吹雪(QQ:149561420)
//------------------------------------------------------------------------

Params
    NumericArrayRef arr_trend_lines;            //趋势线两端点的数组（索引构成）
    Numeric s_index;                            //取某段k线进行寻找高点，开始位置的索引

Vars
    NumericArray arr_lines;                     //获取最近区间内的低点构成的所有连线组合里，能让其他点都落在该连线同一侧的连线集合（索引构成）
    NumericArray arr_points;                    //低点的索引组成的数组
    NumericArray arr_distance_sum;              //其他所有低点到某根线的距离之和组成的数组
    NumericSeries b;                                  //直线方程 y = kx + b 的纵截距b
    NumericSeries k;                                  //直线方程 y = kx + b 的斜率k
    Numeric i;
    Numeric j;
    Numeric proportionYX;                       //在图表上y轴与x轴的比值(看区域内当前品种的价格差与区域内k线数量的比值，为了接近肉眼观察到的图表距离，统一折算成x轴刻度)
    Numeric temp_distance_min;                  //记录arr_distance_sum里最小的那项
    Numeric temp_distance_min_index;            //记录arr_distance_sum里最小的那项的索引

Begin
    Pandora_getLowOneSideLines(arr_lines, s_index);
    Pandora_getLowPoints(arr_points, s_index);

    proportionYX = IntPart((Highest(h[1], CurrentBar - arr_points[0] - 1) - Lowest(l[1], CurrentBar - arr_points[0] - 1)) / (CurrentBar - arr_points[0] - 1));

    //遍历低点的索引组成的数组
    if(GetNumericArraySize(arr_lines) > 0 && GetNumericArraySize(arr_points) > 0)
    {
        for i = 0 to GetNumericArraySize(arr_lines) / 2 - 1
        {
            k = (Min(o[CurrentBar - arr_lines[i * 2 + 1]], c[CurrentBar - arr_lines[i * 2 + 1]]) - Min(o[CurrentBar - arr_lines[i * 2]], c[CurrentBar - arr_lines[i * 2]])) / proportionYX / (arr_lines[i * 2 + 1] - arr_lines[i * 2]); //k = (y2 - y1) / (x2 - x1)
            b = Min(o[CurrentBar - arr_lines[i * 2]], c[CurrentBar - arr_lines[i * 2]]) / proportionYX - arr_lines[i * 2] * k;  //b = y1 - k * x1

            arr_distance_sum[i] = 0;
            for j = 0 to GetNumericArraySize(arr_points) - 1
            {
                //当前直线的这两个端点剔除掉
                if(arr_lines[i * 2 + 1] != arr_points[j] && arr_lines[i * 2] != arr_points[j])
                {
                    //其他所有低点到某根线的距离之和
                    arr_distance_sum[i] = arr_distance_sum[i] + cos(atan(k)) * abs(Min(o[CurrentBar - arr_points[j]], c[CurrentBar - arr_points[j]]) / proportionYX - (b + k * arr_points[j]));
                }
            }

            //找出arr_distance_sum里最小的那项
            if(i != 0)
            {
                if(arr_distance_sum[i] < temp_distance_min)
                {
                    temp_distance_min = arr_distance_sum[i];
                    temp_distance_min_index = i;
                }
            }
            else
            {
                temp_distance_min = arr_distance_sum[0];
                temp_distance_min_index = 0;
            }
        }

        arr_trend_lines[0] = arr_lines[temp_distance_min_index * 2];
        arr_trend_lines[1] = arr_lines[temp_distance_min_index * 2 + 1];
        arr_trend_lines[2] = k[temp_distance_min_index] * proportionYX;
        arr_trend_lines[3] = b[temp_distance_min_index] * proportionYX;
    }

    return true;
End
