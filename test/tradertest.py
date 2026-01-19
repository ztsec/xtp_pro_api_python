# encoding: UTF-8

import os
import uuid
from time import sleep

from vnxtpxtrader import *

    
def printFuncName(*args):
    """"""
    print('*' * 50)
    print(args)
    print('*' * 50)


class TestApi(TraderApi):
    """"""

    def __init__(self):
        """Constructor"""
        super(TestApi, self).__init__()

    #当客户端的某个连接与交易后台通信连接断开时，该方法被调用。
    #@param reason 错误原因，请与错误代码表对应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 用户主动调用logout导致的断线，不会触发此函数。api不会自动重连，当断线发生时，请用户自行选择后续操作，可以在此函数中调用Login重新登录，并更新session_id，此时用户收到的数据跟断线之前是连续的
    def onDisconnected(self,session_id, reason):
        """"""
        printFuncName("onDisconnected",session_id, reason)

    #当登录成功后，中途出现某个服务（资金划拨或者查询）服务状态改变时，该方法将被调用。
    #@param session_id 资金账户对应的session_id，登录时得到
    #@param server_type 服务类型，1-资金划拨服务，2-查询服务
    #@param status 服务是否可用标识，false-服务不可用，true-服务恢复可用
    #@remark 用户登录成功时，默认服务可用。当用户收到服务不可用的通知时，之前没有完成的查询，将不再推送后续的查询消息，需要用户等待查询服务恢复后重新发起查询。
    def onServerStatusNotification(self,session_id,server_type,status):
        """"""
        printFuncName('onServerStatusNotification', session_id,server_type,status)
        
    #错误应答
    #@param error 当服务器响应发生错误时的具体的错误代码和错误信息,当error为空，或者error.error_id为0时，表明没有错误
    #@remark 此函数只有在服务器发生错误时才会调用，一般无需用户处理
    def onError(self, data):
        """"""
        printFuncName('onError', data)
        
    #当客户认证成功时，该方法被调用。
    #@param error_info 当服务器响应发生错误时的具体的错误代码和错误信息,当error_info为空，或者error_info.error_id为0时，表明没有错误
    #@remark 此函数只有在服务器发生错误时才会调用，一般无需用户处理
    def onConnect(self, session_id, user):
        """"""
        printFuncName('onConnect', session_id,user)
        
    #断线重连后，所有需要重传的推送消息（成交回报、订单响应）接收结束通知
    #@param session_id 账户对应的session_id，登录时得到
    #@remark 此函数在用户使用quick第一次登录时，不会有触发。只有在API与服务器以restart方式登录时，或者api与服务器非主动断线，且用户重新login后，进行resume消息重传时，当推送消息重传结束时才会调用，收到此通知就表明断线时的推送消息已经接受完毕，后面收到的推送消息将是实时推送消息
    def onResumeEnd(self, session_id):
        """"""
        printFuncName('onResumeEnd', session_id)
        
    #报单未知状态通知
    #@param order_xtp_id 未知状态订单的xtp id
    #@param session_id 账户对应的session_id，登录时得到
    #@remark 此响应仅表明XTP服务器丢失订单，并没有报送到交易所。
    def onUnknownOrder(self, order_xtp_id, session_id):
        """"""
        printFuncName('onUnknownOrder', order_xtp_id, session_id)
        
    #报单初始状态通知
    #@param data 订单响应具体信息，用户可以通过data.order_xtp_id来管理订单，通过GetClientIDByXTPID() == client_id来过滤自己的订单
    #@param session_id 账户对应的session_id，登录时得到
    #@remark 此响应仅表明XTP服务器收到了报单且没被OMS拒单（OMS内部拒单将没有这条ack消息，仅有OrderEvent的拒单消息），不代表已经报送到交易所
    def onOrderAck(self,data,session_id):
        """"""
        printFuncName('onOrderAck', data, session_id)

    #报单通知
    #@param data 订单响应具体信息，用户可以通过data.order_xtp_id来管理订单，通过GetClientIDByXTPID() == client_id来过滤自己的订单，data.qty_left字段在订单为未成交、部成、全成、废单状态时，表示此订单还没有成交的数量，在部撤、全撤状态时，表示此订单被撤的数量。data.order_cancel_xtp_id为其所对应的撤单ID，不为0时表示此单被撤成功
    #@param error 订单被拒绝或者发生错误时错误代码和错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param session_id 资金账户对应的session，登录时得到
    #@remark 每次订单状态更新时，都会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，在订单未成交、全部成交、全部撤单、部分撤单、已拒绝这些状态时会有响应，对于部分成交的情况，请由订单的成交回报来自行确认。所有登录了此用户的客户端都将收到此用户的订单响应
    def onOrderEvent(self, data, error,session_id):
        """"""
        printFuncName('onOrderEvent', data, error,session_id)
        print("data['order_xtp_id']:",data['order_xtp_id'])#订单号
        print("data['ticker']:",data['ticker'])#证券代码
        print("data['market']:",data['market'])#交易市场
        print("data['order_client_id']:",data['order_client_id'])#报单引用
        print("data['order_local_id']:",data['order_local_id'])#本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
        print("data['exec_type']:",data['exec_type'])#订单执行状态，与交易所回报ExecType字段一致，‘0’-新订单，‘4’-已撤销，‘8’-已拒绝，‘F’-已成交；如果是非交易所的回报，此字段为0
        print("data['order_status']:",data['order_status'])#报单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
        print("data['order_exch_id']:",data['order_exch_id'])#交易所订单编号
        print("data['order_type']:",data['order_type'])#报单类型
        print("data['side']:",data['side'])#买卖方向
        print("data['position_effect']:",data['position_effect'])#开平标志
        print("data['order_submit_status']:",data['order_submit_status'])#报单提交状态，OMS内部使用，用户无需关心
        print("data['quantity']:",data['quantity'])#数量，此订单的报单数量
        
        print("data['price_type']:",data['price_type'])#报单价格条件
        
        print("data['price']:",data['price'])#价格
        print("data['business_type']:",data['business_type'])#业务类型
        print("data['order_cancel_xtp_id']:",data['order_cancel_xtp_id'])#撤单在XTP系统中的id，在XTP系统中唯一（仅撤单成功时有效，此字段为0则表示没有撤单）
        print("data['trade_amount']:",data['trade_amount'])#成交金额
        print("data['qty_traded']:",data['qty_traded'])#今成交数量，为此订单累计成交数量
        print("data['qty_left']:",data['qty_left'])#剩余数量，当撤单成功时，表示撤单数量
        
        
        
        print("data['order_withhold_amount']:",data['order_withhold_amount'])#预扣金额，为此订单的预扣金额（包含预扣手续费，此金额不会改变，仅供参考）
        print("data['order_withhold_fee']:",data['order_withhold_fee'])#预扣手续费，为此订单的预扣手续费（此金额不会改变，仅供参考）
        print("data['exec_id']:",data['exec_id'])#执行编号
        print("data['strategy_type']:",data['strategy_type'])#算法策略类型，仅为算法单时有效
        print("data['set_id']:",data['set_id'])#平台分区号
        print("data['report_index']:",data['report_index'])#执行报告编号
        print("data['transact_time']:",data['transact_time'])#回报时间
        
        print("data['insert_time']:",data['insert_time'])#委托时间，格式为YYYYMMDDHHMMSSsss
        print("data['update_time']:",data['update_time'])#最后修改时间，格式为YYYYMMDDHHMMSSsss
        
        print("data['cancel_time']:",data['cancel_time'])#撤销时间，格式为YYYYMMDDHHMMSSsss
        print("data['strategy_id']:",data['strategy_id'])#算法母单编号ID，仅为算法单时有效
        print("data['error_code']:",data['error_code'])#XTP拒单原因代码
        print("data['extra_error_code']:",data['extra_error_code'])#外部系统拒单原因代码
        print("data['account_id']:",data['account_id'])#证券账户（股卡）
        print("data['branch_pbu']:",data['branch_pbu'])#交易所PBU代码
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #成交通知
    #@param data 成交回报的具体信息，用户可以通过data.order_xtp_id来管理订单，通过GetClientIDByXTPID() == client_id来过滤自己的订单。对于上交所，exec_id可以唯一标识一笔成交。当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交了。对于深交所，exec_id是唯一的，暂时无此判断机制。report_index+market字段可以组成唯一标识表示成交回报。
    #@param session_id 资金账户对应的session，登录时得到
    #@remark 订单有成交发生的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的成交回报。相关订单为部成状态，需要用户通过成交回报的成交数量来确定，OnOrderEvent()不会推送部成状态。
    def onTradeEvent(self, data,session_id):
        """"""
        printFuncName('onTradeEvent', data,session_id)
        print("data['order_xtp_id']:",data['order_xtp_id'])#XTP系统订单ID，此成交回报相关的订单ID，在XTP系统中唯一
        print("data['branch_pbu']:",data['branch_pbu'])#交易所交易员代码
        print("data['ticker']:",data['ticker'])#合约代码
        print("data['market']:",data['market'])#交易市场
        print("data['order_client_id']:",data['order_client_id'])#报单引用
        print("data['trade_time']:",data['trade_time'])#成交时间，格式为YYYYMMDDHHMMSSsss
        print("data['trade_type']:",data['trade_type'])#成交类型  --成交回报中的执行类型
        print("data['order_local_id']:",data['order_local_id'])#本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
        print("data['side']:",data['side'])#买卖方向
        print("data['business_type']:",data['business_type'])#业务类型
        print("data['price']:",data['price'])#价格，此次成交的价格
        print("data['quantity']:",data['quantity'])#数量，此次成交的数量，不是累计数量
        print("data['trade_amount']:",data['trade_amount'])#成交金额，此次成交的总金额 = price*quantity
        print("data['order_exch_id']:",data['order_exch_id'])#报单编号 --交易所单号
        print("data['position_effect']:",data['position_effect'])#开平标志
        print("data['strategy_type']:",data['strategy_type'])#算法策略类型
        print("data['set_id']:",data['set_id'])#平台分区号
        print("data['report_index']:",data['report_index'])#成交序号 --回报记录号，对于单个账户来说，深交所每个平台（不同交易品种）唯一，上交所唯一，对于多账户来说，不唯一
        print("data['strategy_id']:",data['strategy_id'])#算法母单编号ID，仅为算法单时有效
        print("data['exec_id']:",data['exec_id'])#成交编号，深交所唯一，上交所每笔交易唯一，当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交
        
        print("data['account_id']:",data['account_id'])#证券账户（股卡）
        

    #撤单出错响应
    #@param data 撤单具体信息，包括撤单的order_cancel_xtp_id和待撤单的order_xtp_id
    #@param error 撤单被拒绝或者发生错误时错误代码和错误信息，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，当error为空，或者error.error_id为0时，表明没有错误
    #@param session_id 资金账户对应的session，登录时得到
    #@remark 此响应只会在撤单发生错误时被回调
    def onCancelOrderError(self, data, error,session_id):
        """"""
        printFuncName('onCancelOrderError', data, error,session_id)
        print("data['order_xtp_id']:",data['order_xtp_id'])#撤单订单号
        print("data['order_client_id']:",data['order_client_id'])#用户自定义字段
        print("data['ticker']:",data['ticker'])#合约代码
        print("data['market']:",data['market'])#交易市场
        print("data['orig_order_xtp_id']:",data['orig_order_xtp_id'])#原单号
        print("data['transact_time']:",data['transact_time'])#回报时间
        print("data['report_index']:",data['report_index'])#执行报告编号
        print("data['set_id']:",data['set_id'])#平台分区号
        print("data['error_code']:",data['error_code'])#拒单原因代码
        print("data['extra_error_code']:",data['extra_error_code'])#外部系统拒单原因代码
        print("data['orig_order_local_id']:",data['orig_order_local_id'])#原始会员内部订单编号
        print("data['order_local_id']:",data['order_local_id'])#本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #请求查询报单响应
    #@param data 查询到的一个报单
    #@param error 查询报单时发生错误时，返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session，登录时得到
    #@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。此对应的请求函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    def onQueryOrder(self, data, error, reqid, last,session_id):
        """"""
        printFuncName('onQueryOrder', data, error, reqid, last,session_id)
        print("data['order_xtp_id']:",data['order_xtp_id'])#订单号
        print("data['ticker']:",data['ticker'])#证券代码
        print("data['market']:",data['market'])#交易市场
        print("data['order_client_id']:",data['order_client_id'])#报单引用
        print("data['order_local_id']:",data['order_local_id'])#本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
        print("data['exec_type']:",data['exec_type'])#订单执行状态，与交易所回报ExecType字段一致，‘0’-新订单，‘4’-已撤销，‘8’-已拒绝，‘F’-已成交；如果是非交易所的回报，此字段为0
        print("data['order_status']:",data['order_status'])#报单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
        print("data['order_exch_id']:",data['order_exch_id'])#交易所订单编号
        print("data['order_type']:",data['order_type'])#报单类型
        print("data['side']:",data['side'])#买卖方向
        print("data['position_effect']:",data['position_effect'])#开平标志
        print("data['order_submit_status']:",data['order_submit_status'])#报单提交状态，OMS内部使用，用户无需关心
        print("data['quantity']:",data['quantity'])#数量，此订单的报单数量
        
        print("data['price_type']:",data['price_type'])#报单价格条件
        
        print("data['price']:",data['price'])#价格
        print("data['business_type']:",data['business_type'])#业务类型
        print("data['order_cancel_xtp_id']:",data['order_cancel_xtp_id'])#撤单在XTP系统中的id，在XTP系统中唯一（仅撤单成功时有效，此字段为0则表示没有撤单）
        print("data['trade_amount']:",data['trade_amount'])#成交金额
        print("data['qty_traded']:",data['qty_traded'])#今成交数量，为此订单累计成交数量
        print("data['qty_left']:",data['qty_left'])#剩余数量，当撤单成功时，表示撤单数量
        print("data['order_withhold_amount']:",data['order_withhold_amount'])#预扣金额，为此订单的预扣金额（包含预扣手续费，此金额不会改变，仅供参考）
        print("data['order_withhold_fee']:",data['order_withhold_fee'])#预扣手续费，为此订单的预扣手续费（此金额不会改变，仅供参考）
        print("data['exec_id']:",data['exec_id'])#执行编号
        print("data['strategy_type']:",data['strategy_type'])#算法策略类型，仅为算法单时有效
        print("data['set_id']:",data['set_id'])#平台分区号
        print("data['report_index']:",data['report_index'])#执行报告编号
        print("data['transact_time']:",data['transact_time'])#回报时间
        
        print("data['insert_time']:",data['insert_time'])#委托时间，格式为YYYYMMDDHHMMSSsss
        print("data['update_time']:",data['update_time'])#最后修改时间，格式为YYYYMMDDHHMMSSsss
        
        print("data['cancel_time']:",data['cancel_time'])#撤销时间，格式为YYYYMMDDHHMMSSsss
        print("data['strategy_id']:",data['strategy_id'])#算法母单编号ID，仅为算法单时有效
        print("data['error_code']:",data['error_code'])#XTP拒单原因代码
        print("data['extra_error_code']:",data['extra_error_code'])#外部系统拒单原因代码
        print("data['account_id']:",data['account_id'])#证券账户（股卡）
        print("data['branch_pbu']:",data['branch_pbu'])#交易所PBU代码
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])
        

    #分页请求查询报单响应
    #@param data 查询到的一个报单
    #@param req_count 分页请求的最大数量
    #@param order_sequence 分页请求的当前回报数量
    #@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session，登录时得到
    #@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有报单，可以进行下一次分页查询，如果不等，表示所有报单已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    def onQueryOrderByPage(self, data, req_count,order_sequence,query_reference, reqid, last,session_id):
        """"""
        printFuncName('onQueryOrderByPage', data, req_count,order_sequence,query_reference, reqid, last,session_id)
        print("data['order_xtp_id']:",data['order_xtp_id'])#订单号
        print("data['ticker']:",data['ticker'])#证券代码
        print("data['market']:",data['market'])#交易市场
        print("data['order_client_id']:",data['order_client_id'])#报单引用
        print("data['order_local_id']:",data['order_local_id'])#本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
        print("data['exec_type']:",data['exec_type'])#订单执行状态，与交易所回报ExecType字段一致，‘0’-新订单，‘4’-已撤销，‘8’-已拒绝，‘F’-已成交；如果是非交易所的回报，此字段为0
        print("data['order_status']:",data['order_status'])#报单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
        print("data['order_exch_id']:",data['order_exch_id'])#交易所订单编号
        print("data['order_type']:",data['order_type'])#报单类型
        print("data['side']:",data['side'])#买卖方向
        print("data['position_effect']:",data['position_effect'])#开平标志
        print("data['order_submit_status']:",data['order_submit_status'])#报单提交状态，OMS内部使用，用户无需关心
        print("data['quantity']:",data['quantity'])#数量，此订单的报单数量
        
        print("data['price_type']:",data['price_type'])#报单价格条件
        
        print("data['price']:",data['price'])#价格
        print("data['business_type']:",data['business_type'])#业务类型
        print("data['order_cancel_xtp_id']:",data['order_cancel_xtp_id'])#撤单在XTP系统中的id，在XTP系统中唯一（仅撤单成功时有效，此字段为0则表示没有撤单）
        print("data['trade_amount']:",data['trade_amount'])#成交金额
        print("data['qty_traded']:",data['qty_traded'])#今成交数量，为此订单累计成交数量
        print("data['qty_left']:",data['qty_left'])#剩余数量，当撤单成功时，表示撤单数量
        print("data['order_withhold_amount']:",data['order_withhold_amount'])#预扣金额，为此订单的预扣金额（包含预扣手续费，此金额不会改变，仅供参考）
        print("data['order_withhold_fee']:",data['order_withhold_fee'])#预扣手续费，为此订单的预扣手续费（此金额不会改变，仅供参考）
        print("data['exec_id']:",data['exec_id'])#执行编号
        print("data['strategy_type']:",data['strategy_type'])#算法策略类型，仅为算法单时有效
        print("data['set_id']:",data['set_id'])#平台分区号
        print("data['report_index']:",data['report_index'])#执行报告编号
        print("data['transact_time']:",data['transact_time'])#回报时间
        print("data['insert_time']:",data['insert_time'])#委托时间，格式为YYYYMMDDHHMMSSsss
        print("data['update_time']:",data['update_time'])#最后修改时间，格式为YYYYMMDDHHMMSSsss
        
        print("data['cancel_time']:",data['cancel_time'])#撤销时间，格式为YYYYMMDDHHMMSSsss
        print("data['strategy_id']:",data['strategy_id'])#算法母单编号ID，仅为算法单时有效
        print("data['error_code']:",data['error_code'])#XTP拒单原因代码
        print("data['extra_error_code']:",data['extra_error_code'])#外部系统拒单原因代码
        print("data['account_id']:",data['account_id'])#证券账户（股卡）
        print("data['branch_pbu']:",data['branch_pbu'])#交易所PBU代码
        print("req_count:",req_count)#分页请求的最大数量
        print("order_sequence:",order_sequence)#分页请求的当前回报数量
        print("query_reference:",query_reference)#当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
        print("reqid:",reqid)#此消息响应函数对应的请求ID
        print("last:",last)#此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
        print("session_id:",session_id)#资金账户对应的session，登录时得到


    #请求查询成交响应
    #@param data 查询到的一个成交回报
    #@param error 查询成交回报发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session，登录时得到
    #@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。此对应的请求函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    def onQueryTrade(self, data, error, reqid, last,session_id):
        """"""
        printFuncName('onQueryTrade', data, error, reqid, last,session_id)
        print("data['order_xtp_id']:",data['order_xtp_id'])#XTP系统订单ID，此成交回报相关的订单ID，在XTP系统中唯一
        print("data['branch_pbu']:",data['branch_pbu'])#交易所交易员代码
        print("data['ticker']:",data['ticker'])#合约代码
        print("data['market']:",data['market'])#交易市场
        print("data['order_client_id']:",data['order_client_id'])#报单引用
        print("data['trade_time']:",data['trade_time'])#成交时间，格式为YYYYMMDDHHMMSSsss
        print("data['trade_type']:",data['trade_type'])#成交类型  --成交回报中的执行类型
        print("data['order_local_id']:",data['order_local_id'])#本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
        print("data['side']:",data['side'])#买卖方向
        print("data['business_type']:",data['business_type'])#业务类型
        print("data['price']:",data['price'])#价格，此次成交的价格
        print("data['quantity']:",data['quantity'])#数量，此次成交的数量，不是累计数量
        print("data['trade_amount']:",data['trade_amount'])#成交金额，此次成交的总金额 = price*quantity
        print("data['order_exch_id']:",data['order_exch_id'])#报单编号 --交易所单号
        print("data['position_effect']:",data['position_effect'])#开平标志
        print("data['strategy_type']:",data['strategy_type'])#算法策略类型
        print("data['set_id']:",data['set_id'])#平台分区号
        print("data['report_index']:",data['report_index'])#成交序号 --回报记录号，对于单个账户来说，深交所每个平台（不同交易品种）唯一，上交所唯一，对于多账户来说，不唯一
        print("data['strategy_id']:",data['strategy_id'])#算法母单编号ID，仅为算法单时有效
        print("data['exec_id']:",data['exec_id'])#成交编号，深交所唯一，上交所每笔交易唯一，当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交
        print("data['account_id']:",data['account_id'])#证券账户（股卡）
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #分页请求查询成交响应
    #@param data 查询到的一个成交回报
    #@param req_count 分页请求的最大数量
    #@param trade_sequence 分页请求的当前回报数量
    #@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session，登录时得到
    #@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    def onQueryTradeByPage(self, data, req_count, trade_sequence, query_reference, reqid, last,session_id):
        """"""
        printFuncName('onQueryTradeByPage', data, req_count, trade_sequence, query_reference, reqid, last,session_id)
        print("data['order_xtp_id']:",data['order_xtp_id'])#XTP系统订单ID，此成交回报相关的订单ID，在XTP系统中唯一
        print("data['branch_pbu']:",data['branch_pbu'])#交易所交易员代码
        print("data['ticker']:",data['ticker'])#合约代码
        print("data['market']:",data['market'])#交易市场
        print("data['order_client_id']:",data['order_client_id'])#报单引用
        print("data['trade_time']:",data['trade_time'])#成交时间，格式为YYYYMMDDHHMMSSsss
        print("data['trade_type']:",data['trade_type'])#成交类型  --成交回报中的执行类型
        print("data['order_local_id']:",data['order_local_id'])#本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
        print("data['side']:",data['side'])#买卖方向
        print("data['business_type']:",data['business_type'])#业务类型
        print("data['price']:",data['price'])#价格，此次成交的价格
        print("data['quantity']:",data['quantity'])#数量，此次成交的数量，不是累计数量
        print("data['trade_amount']:",data['trade_amount'])#成交金额，此次成交的总金额 = price*quantity
        print("data['order_exch_id']:",data['order_exch_id'])#报单编号 --交易所单号
        print("data['position_effect']:",data['position_effect'])#开平标志
        print("data['strategy_type']:",data['strategy_type'])#算法策略类型
        print("data['set_id']:",data['set_id'])#平台分区号
        print("data['report_index']:",data['report_index'])#成交序号 --回报记录号，对于单个账户来说，深交所每个平台（不同交易品种）唯一，上交所唯一，对于多账户来说，不唯一
        print("data['strategy_id']:",data['strategy_id'])#算法母单编号ID，仅为算法单时有效
        print("data['exec_id']:",data['exec_id'])#成交编号，深交所唯一，上交所每笔交易唯一，当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交
        print("data['account_id']:",data['account_id'])#证券账户（股卡）
        print("req_count:",req_count)#分页请求的最大数量
        print("trade_sequence:",trade_sequence)#分页请求的当前回报数量
        print("query_reference:",query_reference)#当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
        print("reqid:",reqid)#此消息响应函数对应的请求ID
        print("last:",last)#此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
        print("session_id:",session_id)#资金账户对应的session，登录时得到

    #请求查询投资者持仓响应
    #@param data 查询到的一只股票的持仓情况
    #@param error 查询账户持仓发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 由于用户可能持有多个股票，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryPosition(self, data, error, reqid, last,session_id):
        """"""
        printFuncName('onQueryPosition', data, error, reqid, last,session_id)
        print("data['ticker']:",data['ticker'])#证券代码
        print("data['ticker_name']:",data['ticker_name'])#证券名称
        print("data['market']:",data['market'])#交易市场
        print("data['account_id']:",data['account_id'])#证券账户（股卡）
        print("data['total_qty']:",data['total_qty'])#总持仓
        print("data['sellable_qty']:",data['sellable_qty'])#可卖持仓
        print("data['avg_price']:",data['avg_price'])#持仓成本
        print("data['unrealized_pnl']:",data['unrealized_pnl'])#浮动盈亏（保留字段）
        print("data['yesterday_position']:",data['yesterday_position'])#昨日持仓
        print("data['purchase_redeemable_qty']:",data['purchase_redeemable_qty'])#今日申购赎回数量（申购和赎回数量不可能同时存在，因此可以共用一个字段）
        print("data['position_direction']:",data['position_direction'])#持仓方向
        print("data['position_security_type']:",data['position_security_type'])#持仓类型(此字段所有账户都可能用到，可以用来区分股份是否为配售)
        print("data['executable_option']:",data['executable_option'])#可行权合约
        print("data['lockable_position']:",data['lockable_position'])#可锁定标的
        print("data['executable_underlying']:",data['executable_underlying'])#可行权标的
        print("data['locked_position']:",data['locked_position'])#已锁定标的
        print("data['usable_locked_position']:",data['usable_locked_position'])#可用已锁定标的
        print("data['profit_price']:",data['profit_price'])#盈亏成本价
        print("data['buy_cost']:",data['buy_cost'])#买入成本
        print("data['profit_cost']:",data['profit_cost'])#盈亏成本
        print("data['market_value']:",data['market_value'])#持仓市值（此字段目前只有期权账户有值，其他类型账户为0）
        print("data['margin']:",data['margin'])#义务仓占用保证金（此字段目前只有期权账户有值，其他类型账户为0）
        print("data['last_buy_cost']:",data['last_buy_cost'])#昨日买入成本
        print("data['last_profit_cost']:",data['last_profit_cost'])#昨日盈亏成本
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #请求查询用户证券账户信息响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    #@param data 查询到的用户证券账户信息
    #@param error_info 查询用户证券账户信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    #@param request_id 此消息响应函数对应的请求ID
    #@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQuerySecurityAccount(self,data,error,reqid, last, session_id):
        """"""
        printFuncName('onQuerySecurityAccount', data, error, reqid, reqid, last,session_id)
        print("data['market']:",data['market'])#交易市场
        print("data['account_id']:",data['account_id'])#证券账户（股卡）
        print("data['is_main_account']:",data['is_main_account'])#主股东账户标识
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])


    #请求查询资金账户响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    #@param data 查询到的资金账户情况
    #@param error 查询资金账户发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryAsset(self, data, error, reqid, last,session_id):
        """"""
        printFuncName('onQueryAsset', data, error, reqid, reqid, last,session_id)
        print("data['total_asset']:",data['total_asset'])#总资产(=可用资金 + 证券资产（目前为0）+ 预扣的资金)
        print("data['buying_power']:",data['buying_power'])#可用资金
        print("data['security_asset']:",data['security_asset'])#证券资产（保留字段，目前为0)
        print("data['fund_buy_amount']:",data['fund_buy_amount'])#累计买入成交证券占用资金
        print("data['fund_buy_fee']:",data['fund_buy_fee'])#累计买入成交交易费用
        print("data['fund_sell_amount']:",data['fund_sell_amount'])#累计卖出成交证券所得资金
        print("data['fund_sell_fee']:",data['fund_sell_fee'])#累计卖出成交交易费用
        print("data['withholding_amount']:",data['withholding_amount'])#XTP系统预扣的资金（包括购买卖股票时预扣的交易资金+预扣手续费）
        print("data['account_type']:",data['account_type'])#账户类型
        print("data['frozen_margin']:",data['frozen_margin'])#冻结的保证金
        print("data['frozen_exec_cash']:",data['frozen_exec_cash'])#行权冻结资金
        print("data['frozen_exec_fee']:",data['frozen_exec_fee'])#行权费用
        print("data['pay_later']:",data['pay_later'])#垫付资金
        print("data['preadva_pay']:",data['preadva_pay'])#预垫付资金
        print("data['orig_banlance']:",data['orig_banlance'])#昨日余额
        print("data['banlance']:",data['banlance'])#当前余额
        print("data['deposit_withdraw']:",data['deposit_withdraw'])#当天出入金
        print("data['trade_netting']:",data['trade_netting'])#当日交易资金轧差
        print("data['captial_asset']:",data['captial_asset'])#资金资产
        print("data['force_freeze_amount']:",data['force_freeze_amount'])#强锁资金
        print("data['preferred_amount']:",data['preferred_amount'])#可取资金
        print("data['repay_stock_aval_banlance']:",data['repay_stock_aval_banlance'])#融券卖出所得资金余额（仅限信用账户，只能用于买券还券）
        print("data['fund_order_data_charges']:",data['fund_order_data_charges'])#累计订单流量费
        print("data['fund_cancel_data_charges']:",data['fund_cancel_data_charges'])#累计撤单流量费
        print("data['exchange_cur_risk_degree']:",data['exchange_cur_risk_degree'])#交易所实时风险度（仅限期权账户,后续服务器版本支持，目前为0）
        print("data['company_cur_risk_degree']:",data['company_cur_risk_degree'])#公司实时风险度（仅限期权账户,后续服务器版本支持，目前为0）
        print("data['currency_type']:",data['currency_type'])#货币种类
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #请求查询资金划拨订单响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    #@param data 查询到的资金账户情况
    #@param fund_transfer_err_info 返回的资金划拨订单data划拨失败时的错误信息，当fund_transfer_err_info为空，或者fund_transfer_err_info.error_id为0时，表明划转成功，没有错误
    #@param error 查询资金账户发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryFundTransfer(self, data, fund_transfer_err_info, error, reqid, last,session_id):
        """"""
        printFuncName('onQueryFundTransfer', data, fund_transfer_err_info, error, reqid, last,session_id)
        print("data['serial_id']:",data['serial_id'])#资金内转编号
        print("data['transfer_type']:",data['transfer_type'])#内转类型
        print("data['amount']:",data['amount'])#金额
        print("data['oper_status']:",data['oper_status'])#操作结果
        print("data['transfer_time']:",data['transfer_time'])#操作时间
        print("data['site']:",data['site'])#转入或转出的目标服务器对应的节点类型
        print("data['currency_type']:",data['currency_type'])#货币种类
        print("fund_transfer_err_info['error_id']:",fund_transfer_err_info['error_id'])
        print("fund_transfer_err_info['error_msg']:",fund_transfer_err_info['error_msg'])
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #分页请求查询资金划拨订单响应
    #@param data 查询到的一个资金划拨订单
    #@param fund_transfer_err_info 返回的资金划拨订单data划拨失败时的错误信息，当fund_transfer_err_info为空，或者fund_transfer_err_info.error_id为0时，表明划转成功，没有错误
    #@param error 分页查询资金资金划拨订单发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明查询没有错误
	#@param req_count 分页请求的最大数量
    #@param sequence 分页请求的当前回报数量
    #@param query_reference 当前资金划拨订单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果sequence等于req_count，那么表示还有报单，可以进行下一次分页查询，如果不等，表示所有报单已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    def onQueryFundTransferByPage(self,data,fund_transfer_err_info,error, req_count,sequence, query_reference, reqid, last, session_id):
        """"""
        printFuncName('onQueryFundTransferByPage', data, fund_transfer_err_info, error,req_count,sequence, query_reference, reqid, last,session_id)
        print("data['serial_id']:",data['serial_id'])#资金内转编号
        print("data['transfer_type']:",data['transfer_type'])#内转类型
        print("data['amount']:",data['amount'])#金额
        print("data['oper_status']:",data['oper_status'])#操作结果
        print("data['transfer_time']:",data['transfer_time'])#操作时间
        print("data['site']:",data['site'])#转入或转出的目标服务器对应的节点类型
        print("data['currency_type']:",data['currency_type'])#货币种类
        print("fund_transfer_err_info['error_id']:",fund_transfer_err_info['error_id'])
        print("fund_transfer_err_info['error_msg']:",fund_transfer_err_info['error_msg'])
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #资金划拨通知
    #@param data 资金划拨通知的具体信息，用户可以通过data.serial_id来管理订单，通过GetClientIDByXTPID() == client_id来过滤自己的订单。
    #@param error 资金划拨订单被拒绝或者发生错误时错误代码和错误信息，当error为空，或者error.error_id为0时，表明没有错误。当资金划拨方向为一号两中心节点之间划拨，且error.error_id=11000382时，error.error_msg为结点中可用于划拨的资金（以整数为准），用户需进行stringToInt的转化，可据此填写合适的资金，再次发起划拨请求
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 当资金划拨订单有状态变化的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的资金划拨通知。
    def onFundTransfer(self, data, error,session_id):
        """"""
        printFuncName('onFundTransfer', data, error,session_id)
        print("data['serial_id']:",data['serial_id'])#资金内转编号
        print("data['transfer_type']:",data['transfer_type'])#内转类型
        print("data['amount']:",data['amount'])#金额
        print("data['oper_status']:",data['oper_status'])#操作结果
        print("data['transfer_time']:",data['transfer_time'])#操作时间
        print("data['site']:",data['site'])#转入或转出的目标服务器对应的节点类型
        print("data['currency_type']:",data['currency_type'])#货币种类 0-人民币 1-美元 2-港币
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #资金划拨订单未知状态通知
    #@param serial_id 未知状态资金划拨订单的serial id
    #@param session_id 账户对应的session_id，登录时得到
    #@remark 此响应仅表明XTP资金划拨服务器丢失订单，并没有报送到后台。
    def onUnknownFundTransfer(self, serial_id, session_id):
        """"""
        printFuncName('onUnknownFundTransfer', serial_id,session_id)
        

    #请求查询其他节点可用资金的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    #@param data 查询到的其他节点可用资金情况
    #@param error 查询其他节点可用资金发生错误时返回的错误信息，当error.error_id为0时，表明没有错误
    #@param request_id 此消息响应函数对应的请求ID
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryOtherServerFund(self, data, error, reqid,session_id):
        """"""
        printFuncName('onQueryOtherServerFund', data, error, reqid,session_id)
        print("data['amount']:",data['amount'])#amount
        print("data['query_type']:",data['query_type'])#查询类型 0-查询金证主柜台可转资金 1-查询一账号两中心设置时，对方节点的资金 2-查询一账号两中心设置时，对方节点的融券卖余额资金 3-查询一账号两中心设置时，对方节点的授信额度
        print("data['query_site']:",data['query_site'])#对应的交易市场 0-主柜台 2-上海节点 4-深圳节点 8-北京节点 16-香港节点 256-未知节点
        print("data['currency_type']:",data['currency_type'])#货币种类 0-人民币 1-美元 2-港币
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #请求查询ETF清单文件的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    #@param data 查询到的ETF清单文件情况
    #@param error 查询ETF清单文件发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryETF(self, data, error, reqid, last,session_id):
        """"""
        printFuncName('onQueryETF', data, error, reqid, last,session_id)
        print("data['market']:",data['market'])#交易市场
        print("data['etf']:",data['etf'])#etf代码,买卖,申赎统一使用该代码
        print("data['subscribe_redemption_ticker']:",data['subscribe_redemption_ticker'])#etf申购赎回代码
        print("data['unit']:",data['unit'])#最小申购赎回单位对应的ETF份数,例如上证"50ETF"就是900000
        print("data['subscribe_status']:",data['subscribe_status'])#是否允许申购,1-允许,0-禁止
        print("data['redemption_status']:",data['redemption_status'])#是否允许赎回,1-允许,0-禁止
        print("data['max_cash_ratio']:",data['max_cash_ratio'])#最大现金替代比例,小于1的数值   TODO 是否采用double
        print("data['estimate_amount']:",data['estimate_amount'])#T日预估金额
        print("data['cash_component']:",data['cash_component'])#T-X日现金差额
        print("data['net_value']:",data['net_value'])#基金单位净值
        print("data['total_amount']:",data['total_amount'])#最小申赎单位净值总金额=net_value*unit
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #请求查询ETF股票篮的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    #@param data 查询到的ETF合约的相关成分股信息
    #@param error 查询ETF股票篮发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryETFBasket(self, data, error, reqid, last, session_id):
        """"""
        printFuncName('onQueryETFBasket', data, error, reqid, last, session_id)
        print("data['market']:",data['market'])#交易市场
        print("data['ticker']:",data['ticker'])#ETF代码
        print("data['component_ticker']:",data['component_ticker'])#成份股代码
        print("data['component_name']:",data['component_name'])#成份股名称
        print("data['quantity']:",data['quantity'])#成份股数量
        print("data['component_market']:",data['component_market'])#成份股交易市场
        print("data['replace_type']:",data['replace_type'])#成份股替代标识
        print("data['premium_ratio']:",data['premium_ratio'])#溢价比例
        print("data['amount']:",data['amount'])#成分股替代标识为必须现金替代时候的总金额
        print("data['creation_premium_ratio']:",data['creation_premium_ratio'])#申购溢价比例
        print("data['redemption_discount_ratio']:",data['redemption_discount_ratio'])#赎回溢价比例
        print("data['creation_amount']:",data['creation_amount'])#申购时，成分股替代标识为必须现金替代时候的总金额
        print("data['redemption_amount']:",data['redemption_amount'])#赎回时，成分股替代标识为必须现金替代时候的总金额
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #请求查询今日新股申购信息列表的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    #@param data 查询到的今日新股申购的一只股票信息
    #@param error 查询今日新股申购信息列表发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param reqid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryIPOInfoList(self, data, error, reqid, last,session_id):
        """"""
        printFuncName('onQueryIPOInfoList', data, error, reqid, last,session_id)
        print("data['market']:",data['market'])#交易市场
        print("data['ticker']:",data['ticker'])#申购代码
        print("data['ticker_name']:",data['ticker_name'])#申购股票名称
        print("data['ticker_type']:",data['ticker_type'])#证券类别
        print("data['price']:",data['price'])#申购价格
        print("data['unit']:",data['unit'])#申购单元
        print("data['qty_upper_limit']:",data['qty_upper_limit'])#最大允许申购数量
        print("data['is_noprofit']:",data['is_noprofit'])#<是否尚未盈利(仅适用创业板股票，创新企业股票及存托凭证)
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #请求查询用户新股申购额度信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    #@param data 查询到的用户某个市场的今日新股申购额度信息
    #@param error 查查询用户新股申购额度信息发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param reid 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param session_id 资金账户对应的session_id，登录时得到
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryIPOQuotaInfo(self, data, error, reqid, last,session_id):
        """"""
        printFuncName('onQueryIPOQuotaInfo', data, error, reqid, last,session_id)
        print("data['market']:",data['market'])#交易市场
        print("data['quantity']:",data['quantity'])#可申购额度
        print("data['tech_quantity']:",data['tech_quantity'])#上海科创板额度       
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

	#请求查询今日可转债申购信息列表的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	#@param ipo_info 查询到的今日可转债申购的一只可转债信息
	#@param error_info 查询今日可转债申购信息列表发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	#@param request_id 此消息响应函数对应的请求ID
	#@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	#@param session_id 资金账户对应的session_id，登录时得到
	#@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryBondIPOInfoList(self, data, error, reqid, last,session_id):
        """"""
        printFuncName('onQueryBondIPOInfoList', data, error, reqid, last,session_id)
        print("data['market']:",data['market'])#交易市场
        print("data['ticker']:",data['ticker'])#申购代码
        print("data['ticker_name']:",data['ticker_name'])#申购股票名称
        print("data['ticker_type']:",data['ticker_type'])#证券类别
        print("data['price']:",data['price'])#申购价格
        print("data['unit']:",data['unit'])#申购单元
        print("data['qty_upper_limit']:",data['qty_upper_limit'])#最大允许申购数量
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])

    #请求查询用户可转债转股信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	#@param swap_stock_info 查询到某条可转债转股信息
	#@param error_info 查查询可转债转股信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	#@param request_id 此消息响应函数对应的请求ID
	#@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	#@param session_id 资金账户对应的session_id，登录时得到
	#@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryBondSwapStockInfo(self, data, error, reqid, last, session_id):
        """"""
        printFuncName('onQueryBondSwapStockInfo', data, error, reqid, last, session_id)
        print("data['market']:",data["market"])#交易市场
        print("data['ticker']:",data["ticker"])#债券证券代码
        print("data['underlying_ticker']:",data["underlying_ticker"])#转股后的股票证券代码
        print("data['unit']:",data["unit"])#转换数量单位（张）
        print("data['qty_min']:",data["qty_min"])#最小下单量（张）
        print("data['qty_max']:",data["qty_max"])#最大下单量（张）
        print("data['swap_price']:",data["swap_price"])#转股价格
        print("data['swap_flag']:",data["swap_flag"])#是否处于转股期；0: 不可转股；1：可转股；
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])


if __name__ == '__main__':

    p = '122.112.139.0'
    port = 6202
    user = 'username'
    password = 'password'
    reqid = 0
    local_ip = '127.0.0.1'

    #创建TraderApi
    #@param client_id （必须输入）客户端id，用于区分同一用户的不同客户端，由用户自定义，总体取值区间[1,127]，普通用户取值区间[1,24]
    #@param save_file_path （必须输入）存贮订阅信息文件的目录，请设定一个真实存在的有可写权限的路径
    #@param log_level 日志输出级别
    #@return 创建出的UserApi
    #@remark 如果一个账户需要在多个客户端登录，请使用不同的client_id，系统允许一个账户同时登录多个客户端，但是对于同一账户，相同的client_id只能保持一个session连接，后面的登录在前一个session存续期间，无法连接。系统不支持过夜，请确保每天开盘前重新启动
    api = TestApi()
    api.createTraderApi(2, os.getcwd(),4)

    #订阅公共流。
    #@param resume_type 公共流（订单响应、成交回报）重传方式  
    #        XTP_TERT_RESTART(0):从本交易日开始重传
    #        XTP_TERT_RESUME(1):(保留字段，此方式暂未支持)从上次收到的续传
    #        XTP_TERT_QUICK(2):只传送登录后公共流的内容
    #@remark 该方法要在Login方法前调用。若不调用则不会收到公共流的数据。注意在用户断线后，如果不登出就login()，公共流订阅方式不会起作用。用户只会收到断线后的所有消息。如果先logout()再login()，那么公共流订阅方式会起作用，用户收到的数据会根据用户的选择方式而定。
    subscribePublicTopic = api.subscribePublicTopic(2)
    printFuncName('subscribePublicTopic', subscribePublicTopic)

    #设置软件开发Key
    #@param key 用户开发软件Key
    #@remark 此函数必须在Login之前调用
    api.setSoftwareKey("b8aa7173bba3470e390d787219b2112e")


    #设置软件开发版本号
    #@param version 用户开发软件版本号，非api发行版本号，长度不超过15位
    #@remark 此函数必须在Login之前调用，标识的是客户端版本号，而不是API的版本号，由用户自定义
    api.setSoftwareVersion("test")

    #设置心跳检测时间间隔，单位为秒
	#@param interval 心跳检测时间间隔，单位为秒
	#@remark 此函数必须在Login之前调用
    setHeartBeatInterval = api.setHeartBeatInterval(15)   

    #用户登录请求
    #@return session表明此资金账号登录是否成功，“0”表示登录失败，可以调用GetApiLastError()来获取错误代码，非“0”表示登录成功，此时需要记录下这个返回值session，与登录的资金账户对应
    #@param ip 服务器地址，类似“127.0.0.1”
    #@param port 服务器端口号
    #@param user 登录用户名
    #@param password 登录密码
    #@param sock_type “1”代表TCP，“2”代表UDP，目前暂时只支持TCP
    #@param local_ip 本地网卡地址，类似“127.0.0.1”
    #@remark 此函数为同步阻塞式，不需要异步等待登录成功，当函数返回即可进行后续操作，此api可支持多个账户连接，但是同一个账户同一个client_id只能有一个session连接，后面的登录在前一个session存续期间，无法连接
    session_id = api.login(ip, port, user, password, 1,local_ip)
    printFuncName('login', session_id)   
    if session_id == 0 :
       retGetApiLastError = api.getApiLastError()
       printFuncName('getApiLastError', retGetApiLastError) 

    
    

    #获取当前交易日
    #return 获取到的交易日
    #@remark 只有登录成功后,才能得到正确的交易日
    retGetTradingDay = api.getTradingDay()
    printFuncName('getTradingDay', retGetTradingDay)

    #获取API的发行版本号
    #@return 返回api发行版本号
    retGetApiVersion = api.getApiVersion()
    printFuncName('getApiVersion',retGetApiVersion)

    #获取API的系统错误
    #@return 返回的错误信息，可以在Login、InsertOrder、CancelOrder返回值为0时调用，获取失败的原因
    #@remark 可以在调用api接口失败时调用，例如login失败时
    #retGetApiLastError = api.getApiLastError()
    #printFuncName('getApiLastError',retGetApiLastError)
    
    #查询用户在本节点上的可交易市场类型
    #@return 按位来看，从低位开始数，第0位表示沪市，即如果(trade_location&0x01) == 0x01，代表可交易沪市，第1位表示深市，即如果(trade_location&0x02) == 0x02，表示可交易深市，如果第0位和第1位均是1，即(trade_location&(0x01|0x02)) == 0x03，就表示可交易沪深2个市场
    #@param session_id 资金账户对应的session_id,登录时得到
    #@remark  此函数必须在Login之后调用，为同步函数
    retGetAccountTradeMarket = api.getAccountTradeMarket(session_id)
    printFuncName('getAccountTradeMarket',retGetAccountTradeMarket)
    sleep(2)
    
    
    #通过报单在xtp系统中的ID获取下单的客户端id
    #@return 返回客户端id，可以用此方法过滤自己下的订单
    #@param order_xtp_id 报单在xtp系统中的ID
    #@remark 由于系统允许同一用户在不同客户端上登录操作，每个客户端通过不同的client_id进行区分
    
    order_xtp_id = 36989101307593706
    retGetClientIdByXTPID = api.getClientIDByXTPID(order_xtp_id)
    printFuncName('getClientIDByXTPID',retGetClientIdByXTPID)

    

    #报单录入请求
    #@return 报单在XTP系统中的ID,如果为‘0’表示报单发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示报单发送成功，用户需要记录下返回的order_xtp_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    #@param order 报单录入信息，其中order.order_client_id字段是用户自定义字段，用户输入什么值，订单响应OnOrderEvent()返回时就会带回什么值，类似于备注，方便用户自己定位订单。当然，如果你什么都不填，也是可以的。order.order_xtp_id字段无需用户填写，order.ticker必须不带空格，以'\0'结尾
    #@param session_id 资金账户对应的session,登录时得到
    #@remark 交易所接收订单后，会在报单响应函数OnOrderEvent()中返回报单未成交的状态，之后所有的订单状态改变（除了部成状态）都会通过报单响应函数返回
    
    
    sleep(2)
    order = {}
    order['ticker'] = '000001'  # 平安银行
    order['market'] = 1  # 深圳A股
    order['price'] = 13.1
    order['quantity'] = 100
    order['price_type'] = 1  # 限价单
    order['side'] = 1  # 买
    order['position_effect'] = 0  # 开仓
    order['business_type'] = 0  # 普通股票业务（股票买卖，ETF买卖等）
    order['order_client_id'] = 2

    retInsertOrder = api.insertOrder(order, session_id)
    printFuncName('insertOrder', retInsertOrder)
    if retInsertOrder == 0 :         
        retGetApiLastError = api.getApiLastError()
        printFuncName('getApiLastError', retGetApiLastError)   
    
    #为用户获取一个新的订单XTPID，用于报单
	#@return 生成的订单XTPID，非“0”表示获取成功，“0”表示获取失败，此时用户可以调用GetApiLastError()来获取错误代码
	#@param session_id 资金账户对应的session_id,登录时得到
	#@remark 此函数必须在Login之后调用，通过这个函数获取的order_xtp_id仅用于对应的用户报单，如果设置错误，将会导致下单失败
    sleep(2)
    newxtpid = api.getANewOrderXTPID(session_id)
    order['order_xtp_id'] = newxtpid
    retInsertOrder = api.insertOrderExtra(order, session_id)
    printFuncName('insertOrderExtra', retInsertOrder)
    if retInsertOrder == 0 :
        retGetApiLastError = api.getApiLastError()
        printFuncName('getApiLastError',retGetApiLastError)


    #通过报单在xtp系统中的ID获取下单的客户端id
    #@return 返回客户端id，可以用此方法过滤自己下的订单
    #@param order_xtp_id 报单在xtp系统中的ID
    #@remark 由于系统允许同一用户在不同客户端上登录操作，每个客户端通过不同的client_id进行区分    
    order_xtp_id = retInsertOrder
    retGetClientIdByXTPID = api.getClientIDByXTPID(order_xtp_id)
    printFuncName('getClientIDByXTPID',retGetClientIdByXTPID)

    #通过报单在xtp系统中的ID获取相关资金账户名
    #@return 返回资金账户名
    #@param order_xtp_id 报单在xtp系统中的ID
    #@remark 只有资金账户登录成功后,才能得到正确的信息
    retGetAccountByXTPID = api.getAccountByXTPID(order_xtp_id)
    printFuncName('getAccountByXTPID',retGetAccountByXTPID)

    #获取用户分页查询允许的最大查询数量
    #@return 分页查询允许的最大查询数量req_count，非“0”表示获取成功，“0”表示获取失败，此时用户可以调用getApiLastError()来获取错误代码
    #@param session_id 资金账户对应的session_id,登录时得到
    #@remark 此函数必须在Login之后调用，通过这个函数获取的req_count可用于用户进行分页查询请求的填写，如果填写错误，将会导致分页查询接口调用失败
    retMaxSeqNum = api.getMaxReqNumOfPagedQuery(session_id)

    
    #分页请求查询报单
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param query_param 需要分页查询订单的条件，如果第一次查询，那么query_param.reference填0
    #@param session_id 资金账户对应的session_id，登录时得到
    #@param request_id 用于用户定位查询响应的ID，由用户自定义
    #@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用    sleep(1)
    queryOrderByPageReq = {}
    queryOrderByPageReq['req_count'] = retMaxSeqNum #需要查询的成交回报条数,可以填比最大分页查询数量小一点
    queryOrderByPageReq['reference'] = 0 #上一次收到的查询订单结果中带回来的索引，如果是从头查询，请置0
    queryOrderByPageReq['reserved'] = 0 #保留字段
    sleep(1)
    reqid += 1
    retQueryOrdersByPage = api.queryOrdersByPage(queryOrderByPageReq, session_id, reqid)
    printFuncName('queryOrdersByPage', retQueryOrdersByPage)
    if retQueryOrdersByPage != 0 :
        retQueryOrdersByPageError = api.getApiLastError()
        printFuncName('getApiLastError',retQueryOrdersByPageError)

    
    #撤单操作请求
    #@return 撤单在XTP系统中的ID,如果为‘0’表示撤单发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示撤单发送成功，用户需要记录下返回的order_cancel_xtp_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    #@param retInsertOrder 需要撤销的委托单在XTP系统中的ID
    #@param session_id 资金账户对应的session,登录时得到
    #@remark 如果撤单成功，会在报单响应函数OnOrderEvent()里返回原单部撤或者全撤的消息，如果不成功，会在OnCancelOrderError()响应函数中返回错误原因
    sleep(2)
    retCancelOrder = api.cancelOrder(retInsertOrder, session_id)
    printFuncName('cancelOrder',retCancelOrder)
    if retCancelOrder == 0 :
        retCancelOrderError = api.getApiLastError()
        printFuncName('getApiLastError',retCancelOrderError)

    #根据报单ID请求查询报单
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param order_xtp_id 需要查询的报单在xtp系统中的ID，即InsertOrder()成功时返回的order_xtp_id
    #@param session_id 资金账户对应的session，登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    #@remark 该方法不受查询服务是否可用影响
    reqid += 1
    order_xtp_id = retInsertOrder
    retQueryOrderByXTPID = api.queryOrderByXTPID(order_xtp_id,session_id,reqid)
    printFuncName('queryOrderByXTPID',retQueryOrderByXTPID)
    if retQueryOrderByXTPID != 0 :
        retQueryOrderByXTPIDError = api.getApiLastError()
        printFuncName('getApiLastError',retQueryOrderByXTPIDError)
  
    #请求查询报单
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param queryOrdersInfo 需要查询的订单相关筛选条件，其中合约代码可以为空，则默认所有存在的合约代码，如果不为空，其中起始时间格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点，结束时间格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    #@param session_id 资金账户对应的session，登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    #@remark 该方法支持分时段查询，如果股票代码为空，则默认查询时间段内的所有报单，否则查询时间段内所有跟股票代码相关的报单，此函数查询出的结果可能对应多个查询结果响应。此函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    queryOrdersInfo = {}
    queryOrdersInfo['ticker'] = '000001'
    queryOrdersInfo['begin_time'] = 0
    queryOrdersInfo['end_time'] = 0
    sleep(1)
    reqid += 1
    retQueryOrders = api.queryOrders(queryOrdersInfo, session_id, reqid)
    printFuncName('queryOrders',retQueryOrders)
    retGetApiLastError = api.getApiLastError()
    printFuncName('getApiLastError',retGetApiLastError)

    #根据委托编号请求查询相关成交
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param order_xtp_id 需要查询的委托编号，即InsertOrder()成功时返回的order_xtp_id
    #@param session_id 资金账户对应的session，登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    #@remark 此函数查询出的结果可能对应多个查询结果响应
    sleep(1)
    reqid += 1
    retQueryTradesByXTPID = api.queryTradesByXTPID(order_xtp_id, session_id, reqid)
    printFuncName('queryTradesByXTPID', retQueryTradesByXTPID)

    sleep(1)
    #请求查询已成交
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param queryTradesInfo 需要查询的成交回报筛选条件，其中合约代码可以为空，则默认所有存在的合约代码，如果不为空，其中起始时间格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点，结束时间格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    #@param session_id 资金账户对应的session,登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    #@remark 该方法支持分时段查询，如果股票代码为空，则默认查询时间段内的所有成交回报，否则查询时间段内所有跟股票代码相关的成交回报，此函数查询出的结果可能对应多个查询结果响应。此函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    queryTradesInfo = {}
    queryTradesInfo['ticker'] = '000001'
    queryTradesInfo['begin_time'] = 0
    queryTradesInfo['end_time'] = 0
    reqid += 1
    retQueryTrades = api.queryTrades(queryTradesInfo, session_id, reqid)
    printFuncName('queryTrades',retQueryTrades)

    sleep(1)
    #分页请求查询成交回报
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param query_param 需要分页查询成交回报的条件，如果第一次查询，那么reference填0
    #@param session_id 资金账户对应的session_id，登录时得到
    #@param request_id 用于用户定位查询响应的ID，由用户自定义
    #@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
    queryTraderByPageReq = {}
    queryTraderByPageReq['req_count'] = 10 #需要查询的成交回报条数
    queryTraderByPageReq['reference'] = 0 #上一次收到的查询成交回报结果中带回来的索引，如果是从头查询，请置0
    queryTraderByPageReq['reserved'] = 0 #保留字段
    sleep(1)
    reqid += 1
    retQueryTradesByPage = api.queryTradesByPage(queryTraderByPageReq, session_id, reqid)
    printFuncName('queryTradesByPage', retQueryTradesByPage)

    sleep(1)
    #按条件请求查询投资者指定持仓
    #@return 查询发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param ticker 需要查询持仓的合约代码，可以为NULL，表示查询沪深全市场主股卡持仓，如果不为NULL，请不带空格，并以'\0'结尾，注意需与market匹配，不匹配的话，查询不到所需的持仓
    #@param session_id 资金账户对应的session_id,登录时得到
    #@param request_id 用于用户定位查询响应的ID，由用户自定义
    #@param market 需要查询持仓的合约所在市场，仅在合约代码不为NULL的时候，才会使用。使用时，market必须指定。需要查单市场持仓，请使用queryAllPosition()
    #@remark 该方法如果用户提供了合约代码，则会查询此合约的主股卡持仓信息（注意请指定market，不指定查不到所需的持仓,此时不受查询服务是否可用影响），如果合约代码为空，则默认查询沪深市场的主股卡持仓信息,类似于使用QueryAllPosition()。
    reqid += 1
    retQueryPosition = api.queryPosition('', session_id, reqid, 0)
    printFuncName('queryPosition',retQueryPosition)

    sleep(1)
    #按条件请求查询投资者持仓
    #@return 查询发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param query_param 需要查询持仓的条件，可以为NULL，表示查询沪深全市场主股卡持仓，如果不为NULL，会优先看股卡信息，如果提供了股卡，必须与market匹配；如果没有提供股卡信息，则默认查询market对应的主股卡持仓（注意market不可为0。当market不为0，ticker为空时，默认查询主股卡中market对应的持仓；当market不为0，ticker不为空时，默认查询主股卡中market里指定ticker的持仓）
    #@param session_id 资金账户对应的session_id,登录时得到
    #@param request_id 用于用户定位查询响应的ID，由用户自定义
    #@remark 该方法如果用户没有提供股卡信息，则默认查主股卡的持仓，如果提供了股卡，必须与market匹配，否则查不到正确的持仓。此函数支持查指定合约代码的持仓。当查指定合约代码持仓时，不受查询服务是否可用影响。
    reqid += 1
    queryStkPositionReq = {}
    queryStkPositionReq['ticker'] = ''
    queryStkPositionReq['market'] = 1 #深市
    queryStkPositionReq['account_id'] = ''
    retQueryAllPosition = api.queryAllPosition(queryStkPositionReq, session_id, reqid)#查询深市主股卡的持仓
    printFuncName('queryAllPosition',retQueryAllPosition)

    sleep(1)
    #请求查询资产
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param session_id 资金账户对应的session,登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    #@remark 该方法不受查询服务是否可用影响
    reqid += 1
    retQueryAsset = api.queryAsset(session_id, reqid)
    printFuncName('queryAsset',retQueryAsset)


    sleep(1)
    #资金划拨请求
    #@return 资金划拨订单在XTP系统中的ID,如果为‘0’表示消息发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示消息发送成功，用户需要记录下返回的serial_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    #@param fundTransferInfo 资金划拨的请求信息
    #@param session_id 资金账户对应的session,登录时得到
    #@remark 此函数支持一号两中心节点之间的资金划拨，注意资金划拨的方向。
    reqid += 1
    fundTransferInfo = {}
    fundTransferInfo['serial_id'] = 30000
    fundTransferInfo['fund_account'] = '15006594'
    fundTransferInfo['amount'] = 20000
    fundTransferInfo['transfer_type'] = 0
    fundTransferInfo['site'] = 0  #双中心用户跨节点划拨时必填
    retFundTransfer = api.fundTransfer(fundTransferInfo, session_id)
    printFuncName('fundTransfer', retFundTransfer)

    sleep(1)
    #请求查询指定资金划拨订单
    #@return 查询发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param serial_id 需要查询的资金划拨订单ID,不可以为0
    #@param session_id 资金账户对应的session,登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    reqid += 1
    serial_id = retFundTransfer
    retQueryFundTransferByID = api.queryFundTransferByID(serial_id, session_id, reqid)
    printFuncName('queryFundTransferByID', retQueryFundTransferByID)

    sleep(1)
    #分页请求查询资金划拨订单
    #@return 查询发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param query_param 需要分页查询订单的条件，如果第一次查询，那么query_param.reference填0
    #@param session_id 资金账户对应的session_id，登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    #@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用。此函数受资金划拨服务器是否可用影响。
    reqid += 1
    queryFundTransferByPageReq = {}
    queryFundTransferByPageReq['req_count'] = api.getMaxReqNumOfPagedQuery(session_id)
    queryFundTransferByPageReq['reference'] = 0
    retQueryFundTransferByPage = api.queryFundTransferByPage(queryFundTransferByPageReq, session_id, reqid)
    printFuncName('queryFundTransferByPage', retQueryFundTransferByPage)

    #请求查询其他节点可用资金
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param query_param 查询时需要提供的信息
    #@param session_id 资金账户对应的session_id,登录时得到
    #@param request_id 用于用户定位查询响应的ID，由用户自定义
    query_other_server_fund_req = {
        'fund_account': 'username',
        'query_type': 1,
        'query_site': 2
    }
    reqid += 1
    queryOtherServerFund = api.queryOtherServerFund(query_other_server_fund_req,session_id, reqid)
    printFuncName('queryOtherServerFund',queryOtherServerFund)

    sleep(1)
    #请求查询ETF清单文件
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param queryETFInfo 需要查询的ETF清单文件的筛选条件，其中合约代码可以为空，则默认所有存在的ETF合约代码，market字段也可以为初始值，则默认所有市场的ETF合约
    #@param session_id 资金账户对应的session,登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    queryETFInfo = {}
    queryETFInfo['ticker'] = '510050'
    queryETFInfo['market'] = 2
    reqid += 1
    retQueryETF = api.queryETF(queryETFInfo, session_id, reqid)
    printFuncName('queryETF', retQueryETF)

    sleep(1)
    #请求查询ETF股票篮
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param queryETFTickerBasketInfo 需要查询股票篮的的ETF合约，其中合约代码不可以为空，market字段也必须指定
    #@param session_id 资金账户对应的session,登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    queryETFTickerBasketInfo = {}
    queryETFTickerBasketInfo['ticker'] = '510050'
    queryETFTickerBasketInfo['market'] = 2
    reqid += 1
    retQueryETFTickerBasket = api.queryETFTickerBasket(queryETFInfo,session_id, reqid)
    printFuncName('queryETFTickerBasket',retQueryETFTickerBasket)
    sleep(1)
  
    #请求查询今日新股申购信息列表
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param session_id 资金账户对应的session,登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    reqid += 1
    retQueryIPOInfoList = api.queryIPOInfoList(session_id, reqid)
    printFuncName('queryIPOInfoList',retQueryIPOInfoList)
    sleep(1)
    

     #请求查询用户新股申购额度信息
    #@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param session_id 资金账户对应的session_id,登录时得到
    #@param reqid 用于用户定位查询响应的ID，由用户自定义
    reqid += 1
    retQueryIPOQuotaInfo = api.queryIPOQuotaInfo(session_id, reqid)
    printFuncName('queryIPOQuotaInfo',retQueryIPOQuotaInfo)
    sleep(1)

    #请求查询今日可转债申购信息列表
	#@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
	#@param session_id 资金账户对应的session_id,登录时得到
	#@param request_id 用于用户定位查询响应的ID，由用户自定义
    reqid += 1
    retQueryBondIPOInfoList = api.queryBondIPOInfoList(session_id, reqid)
    printFuncName('queryBondIPOInfoList', retQueryBondIPOInfoList)
    if retQueryBondIPOInfoList != 0 :
        retGetApiLastError = api.getApiLastError()
        printFuncName('getApiLastError', retGetApiLastError)   
    sleep(1)
   
  
    #请求查询可转债转股的基本信息
	#@return 查询是否发送成功，“0”表示发送成功，非“0”表示发送出错，此时用户可以调用GetApiLastError()来获取错误代码
	#@param query_param 需要查询的可转债转股信息的筛选条件，可以为NULL（为NULL表示查询所有的可转债转股信息），此参数中合约代码可以为空字符串，如果为空字符串，则查询所有可转债转股信息，如果不为空字符串，请不带空格，并以'\0'结尾，且必须与market匹配
	#@param session_id 资金账户对应的session_id,登录时得到
	#@param request_id 用于用户定位查询响应的ID，由用户自定义
    queryBondSwapStockInfo = {}
    queryBondSwapStockInfo['market'] = 2
    #queryBondSwapStockInfo['ticker'] = '113641'
    reqid += 1
    retQueryBondSwapStockInfo = api.queryBondSwapStockInfo(queryBondSwapStockInfo, session_id, reqid)
    printFuncName('queryBondSwapStockInfo', retQueryBondSwapStockInfo)
    if retQueryBondSwapStockInfo != 0 :
        retGetApiLastError = api.getApiLastError()
        printFuncName('getApiLastError', retGetApiLastError)   
    sleep(500000)

    #sleep为了删除接口对象前将回调数据输出，不sleep直接删除回调对象会自动析构，无法返回回调的数据
    #sleep(5)
   
    #登出请求
    #@return 登出是否成功，“0”表示登出成功，“-1”表示登出失败
    #@param session_id 资金账户对应的session,登录时得到
    logout = api.logout(session_id)
    printFuncName('logout:',logout )

    #删除接口对象本身
    #@remark 不再使用本接口对象时,调用该函数删除接口对象
    #release = api.release()
    #printFuncName('release', release)

    exit = api.exit()
    printFuncName('exit', exit)
    
    

