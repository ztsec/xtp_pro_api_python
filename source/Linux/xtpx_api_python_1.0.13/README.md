中泰证券量化交易平台XTP PRO PYTHON API接口

本项目是中泰证券XTP极速交易PYTHON接口的开源实现，供客户在量化交易中使用PYTHON接口快速接入XTP系统。中泰证券XTP是为股票交易而生的极速交易系统，为投资者提供极速交易、极速行情、Level2行情。

目前xtp pro系统最新的api版本为1.0.13，支持windows、linux平台运行。

请先到中泰证券xtp官方网站申请测试账号 https://xtp.zts.com.cn 及测试环境的连接ip、端口等信息。

API参考官方C++版本的接口文档 https://xtp.zts.com.cn/xtp-pro

python版本api封装使用的Visual Studio 2015，如果本地安装的vs是较低的vs2010版本，并且未安装vs环境，运行时会提示ImportError:DLL load failed。需根据python的位数选择对应Visual C++库的运行时组件，64位选vc_redist.x64.exe，执行程序参考文件包vs2015运行库。

官网下载地址：https://www.microsoft.com/zh-CN/download/details.aspx?id=48145

##事项说明:

1.当前xtp pro的python api封装支持win7系统、win10系统和Linux系统，在bin目录下Linux文件夹中有python3封装库，Windows文件夹中有64位的python3封装库。test文件夹下包含行情和交易的测试脚本。

2.当前bin目录下编译时使用的 python3.9.13 + boost_1_80_0 版本，如果直接使用当前的封装库，请注意使用的python版本是否为3.9系列，如果您使用的python版本和我们编译时使用的版本不一致，会导致调用python封装库失败。

3.如果客户需要按自己的python版本编译封装库，可以使用source目录下的代码，根据自己的python的版本，及该python版本对应的编译后的boost库，自行编译所需的python封装库。（具体过程在doc文件夹下有编译过程文档，source文件夹下有源码，包括Linux和Windows下编译的python3封装库）。

4.XTP Pro版本封装的python版本sdk中回调函数onDepthMarketData()的数据data跟之前的版本有区别，stk(股票)，bond(债券)，opt(期权)三个数据作为字典嵌套到data里的,具体参考quotetest.py里的示例。同理，回调函数onTickByTick()的数据data跟之前版本也不同，entrust(逐笔委托)，trade(逐笔成交)，state(逐笔状态)三个数据是作为字段嵌套到data里的，参考quotetest.py里的示例。

5.XTP_PRO_API_1.0.13文件夹下存放最新的C++版本的SDK，当前python封装库分别包含行情和交易库，python封装后的接口与当前c++版本的SDK中的API所有接口都保持一致，只有方法名有所区别，python封装后的接口方法名首字母小写，而C++版本的api方法名首字母大写。

  因此所有封装后的python接口方法使用和功能都可以参见C++版本的SDK的接口方法。请在xtpx_quote_api.h、xtpx_trader_api.h两个头文件中了解各个接口的使用及功能。

6. python版本的sdk包，请在git下使用clone下载：https://github.com/ztsec/xtp_pro_api_python.git
