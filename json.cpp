/*
 * @Author: fannanqi 1773252187@qq.com
 * @Date: 2024-02-27 16:18:30
 * @LastEditors: fannanqi 1773252187@qq.com
 * @LastEditTime: 2024-02-27 21:19:54
 * @FilePath: /json-cpp/json.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
/*
    json类型：数组类型、对象类型
    示例json：
    [
        "tom",19,170,false,
        ["kate","sam"],     /数组类型
        {"sex":"man","friend":"Han"}    /对象类型
    ]
*/
/**
 * @description: 将字符串序列化成json
 * @return {*}
 */
void writeJson()
{
    // 主根节点 root
    Json::Value root;
    root.append("tom");
    root.append("19");
    root.append("170");
    root.append("false");

    //  子节点数组
    Json::Value subArry;
    subArry.append("kate");
    subArry.append("sam");

    //  将子节点添加到root节点
    root.append(subArry);

    //  子节点对象类型
    Json::Value object;
    object["sex"] = "man";
    object["friend"] = "Han";

    //  将子节点添加到root节点
    root.append(object);

    //  将json语句格式化成字符串(标准化)
    std::string json = root.toStyledString();

    //  将json语句格式化成字符串(非标准化)
    Json::FastWriter fw;
    std::string fWjson = fw.write(root);
    std::cout << fWjson << std::endl;

    //  保存到文件中
    std::ofstream ofs("test.json", std::ios::app);
    if (ofs.is_open())
    {
        std::cout << "successful\n";
    }
    ofs << fWjson;
    ofs.close();
}

void judgeMethod(Json::Value &tmp)
{
    if (tmp.isInt())
        std::cout << tmp.asInt() << ", ";
    else if (tmp.isDouble())
    {
        std::cout << tmp.asDouble() << ", ";
    }
    else if (tmp.isBool())
    {
        std::cout << tmp.asBool() << ", ";
    }
    else if (tmp.isString())
    {
        std::cout << tmp.asString() << ", ";
    }
    else if (tmp.isArray())
    {
        for (auto j : tmp)
        {
            judgeMethod(j);
        }
        std::cout << std::endl;
    }
    else if (tmp.isObject())
    {
        //  object的json对象中，以key-value存在,使用getMemberNames获取key集合
        Json::Value::Members keys = tmp.getMemberNames();
        for (auto i : keys)
        {
            std::cout << i << ":" << tmp[i] << ",";
        }
    }
}
/**
 * @description: 对json转化为反序列化
 * @return {*}
 */
void readJson()
{
    std::ifstream ifs("test.json", std::ios::in);
    std::shared_ptr<Json::Reader> rd(new Json::Reader());
    Json::Value root;
    rd->parse(ifs, root);
    //  关于Json::Value的迭代器遍历
    // for (auto it = root.begin(); it != root.end(); it++)
    // {
    //     std::cout << *it;
    // }

    //  解析字符串
    std::for_each(root.begin(), root.end(), [&](Json::Value val)
                  { 
                        Json::Value tmp=val;
                        judgeMethod(tmp);
                        std::cout<<std::endl; });
    ifs.close();
}
int main(void)
{
    readJson();
    return 0;
}