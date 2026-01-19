// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//
//#include "stdafx.h"
#include "vnxtpxtrader.h"

///-------------------------------------------------------------------------------------
///从Python对象到C++类型转换用的函数
///-------------------------------------------------------------------------------------

// 嵌套结构体-int类型处理
void getNestedDictValue(dict d, string key1, string key2, int *value) {
	if (d.has_key(key1)) {        //检查字典中是否存在该键值
		dict o1 = (dict)d[key1];    //获取该键值
		if (o1.has_key(key2)) {
			object o2 = o1[key2];    //获取该键值
			extract<int> x(o2);    //创建提取器
			if (x.check()) {        //如果可以提取
				*value = x();    //对目标整数指针赋值
			}
		}
	}
}

// 嵌套结构体-字符串类型处理
void getNestedDictChar(dict d, string key1, string key2, char *value) {
	if (d.has_key(key1)) {        //检查字典中是否存在该键值
		dict o1 = (dict)d[key1];    //获取该键值
		if (o1.has_key(key2)) {
			object o2 = o1[key2];    //获取该键值
			extract<string> x(o2);    //创建提取器
			if (x.check()) {        //如果可以提取
				string s = x();
				const char *buffer = s.c_str();
#ifdef WIN32
				strcpy_s(value, strlen(buffer) + 1, buffer);
#else
				strncpy(value, buffer, strlen(buffer) + 1);
#endif
			}
		}
	}
}

// 嵌套结构体数组-字符串类型处理
void getNestedDictChar2(dict d, string key1, string key2, string key3, char *value, int index) {
	if (d.has_key(key1)) {        //检查字典中是否存在该键值
		dict o1 = (dict)d[key1];    //获取该键值
		if (o1.has_key(key2)) {
			dict o2 = (dict)(((boost::python::list)o1[key2])[index]);    //获取该键值
			if (o2.has_key(key3)) {
				object o3 = o2[key3];    //获取该键值
				extract<string> x(o3);    //创建提取器
				if (x.check()) {        //如果可以提取
					string s = x();
					const char *buffer = s.c_str();
#ifdef WIN32
					strcpy_s(value, strlen(buffer) + 1, buffer);
#else
					strncpy(value, buffer, strlen(buffer) + 1);
#endif
				}
			}
		}
	}
}

// 嵌套结构体数组-int类型处理
void getNestedDictValue2(dict d, string key1, string key2, string key3, int *value, int index) 
{
	if (d.has_key(key1)) {        //检查字典中是否存在该键值
		dict o1 = (dict)d[key1];    //获取该键值
		if (o1.has_key(key2)) {
			dict o2 = (dict)(((boost::python::list)o1[key2])[index]);    //获取该键值
			if (o2.has_key(key3)) {
				object o3 = o2[key3];    //获取该键值
				extract<int> x(o3);    //创建提取器
				if (x.check()) {        //如果可以提取
					*value = x();    //对目标整数指针赋值
				}
			}
		}
	}
}

void getInt(dict d, string key, int *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getUint64(dict d, string key, uint64_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<uint64_t> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getUint32(dict d, string key, uint32_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getUint16(dict d, string key, uint16_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getInt64(dict d, string key, int64_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int64_t> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getDouble(dict d, string key, double *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<double> x(o);
		if (x.check())
		{
			*value = x();
		}
	}
};

void getStr(dict d, string key, char *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *buffer = s.c_str();
			//对字符串指针赋值必须使用strcpy_s, vs2013使用strcpy编译通不过
			//+1应该是因为C++字符串的结尾符号？不是特别确定，不加这个1会出错
#ifdef _MSC_VER //WIN32
			strcpy_s(value, strlen(buffer) + 1, buffer);
#elif __GNUC__
			strncpy(value, buffer, strlen(buffer) + 1);
#endif
		}
	}
};

void getChar(dict d, string key, string& value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			value = s;
			//char buffer[XTP_ACCOUNT_PASSWORD_LEN];
			//strcpy(buffer, s.c_str());
			//const char buffer[XTP_ACCOUNT_PASSWORD_LEN] = s.c_str();
			//*value = *buffer;
		}
	}
};

string addEndingChar(char *value){
	//printf("value:%s\n",value);
	string endStr = value;
	//printf("endStr:%s\n",endStr.c_str());
	return endStr;
}

///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void TraderApi::OnDisconnected(uint64_t session_id, int reason)
{
	Task* task = new Task();
	task->task_name = ONDISCONNECTED;
	task->addtional_int = session_id;		//手动修改
	task->task_id = reason;
	this->task_queue.push(task);
};

void TraderApi::OnServerStatusNotification(uint64_t session_id, uint32_t server_type, bool status)
{
	Task* task = new Task();
	task->task_name = ONSERVERSTATUSNOTIFICATION;
	task->addtional_int = session_id;
	task->task_id = server_type;
	task->addtional_bool = status;
	this->task_queue.push(task);
}

void TraderApi::OnError(XTPX::API::XTPRI *error_info)
{
	Task* task = new Task();
	task->task_name = ONERROR;

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TraderApi::OnConnect(uint64_t session_id, const char* user_name)
{
	Task* task = new Task();
	task->task_name = ONCONNECT;
	task->addtional_int = session_id;
	std::string user(user_name);
	task->user = user;
	this->task_queue.push(task);
}

void TraderApi::OnResumeEnd(uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONRESUMEEND;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnUnknownOrder(uint64_t order_xtp_id, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONUNKNOWNORDER;
	task->addtional_int = session_id;
	task->addtional_int_five = order_xtp_id;
	this->task_queue.push(task);
}

void TraderApi::OnOrderAck(XTPX::API::XTPOrderInfo *order_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONORDERACK;

	if (order_info)
	{
		XTPX::API::XTPOrderInfo *task_data = new XTPX::API::XTPOrderInfo();
		*task_data = *order_info;
		task->task_data = task_data;
	}
	task->addtional_int = session_id;

	this->task_queue.push(task);
}


void TraderApi::OnOrderEvent(XTPX::API::XTPOrderInfo *order_info, XTPX::API::XTPRI *error_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONORDEREVENT;

	if (order_info)
	{
		XTPX::API::XTPOrderInfo *task_data = new XTPX::API::XTPOrderInfo();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;

	this->task_queue.push(task);
};

void TraderApi::OnTradeEvent(XTPX::API::XTPTradeReport *trade_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONTRADEEVENT;

	if (trade_info)
	{
		XTPX::API::XTPTradeReport *task_data = new XTPX::API::XTPTradeReport();
		*task_data = *trade_info;
		task->task_data = task_data;
	}

	task->addtional_int = session_id;

	this->task_queue.push(task);
};

void TraderApi::OnCancelOrderError(XTPX::API::XTPOrderCancelErrorInfo *cancel_info, XTPX::API::XTPRI *error_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONCANCELORDERERROR;

	if (cancel_info)
	{
		XTPX::API::XTPOrderCancelErrorInfo *task_data = new XTPX::API::XTPOrderCancelErrorInfo();
		*task_data = *cancel_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
		
	this->task_queue.push(task);
};

void TraderApi::OnQueryOrder(XTPX::API::XTPQueryOrderRsp *order_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYORDER;

	if (order_info)
	{
		XTPX::API::XTPQueryOrderRsp *task_data = new XTPX::API::XTPQueryOrderRsp();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};


void TraderApi::OnQueryOrderByPage(XTPX::API::XTPQueryOrderRsp *order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYORDERBYPAGE;

	if (order_info)
	{
		XTPX::API::XTPQueryOrderRsp *task_data = new XTPX::API::XTPQueryOrderRsp();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	task->addtional_int_two = req_count;
	task->addtional_int_three = order_sequence;
	task->addtional_int_four = query_reference;
	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};


void TraderApi::OnQueryTrade(XTPX::API::XTPQueryTradeRsp *trade_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYTRADE;

	if (trade_info)
	{
		XTPX::API::XTPQueryTradeRsp *task_data = new XTPX::API::XTPQueryTradeRsp();
		*task_data = *trade_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryTradeByPage(XTPX::API::XTPQueryTradeRsp *trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYTRADEBYPAGE;

	if (trade_info)
	{
		XTPX::API::XTPQueryTradeRsp *task_data = new XTPX::API::XTPQueryTradeRsp();
		*task_data = *trade_info;
		task->task_data = task_data;
	}

	task->addtional_int_two = req_count;
	task->addtional_int_three = trade_sequence;
	task->addtional_int_four = query_reference;
	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryPosition(XTPX::API::XTPQueryStkPositionRsp *position, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYPOSITION;
	if (position)
	{
		XTPX::API::XTPQueryStkPositionRsp *task_data = new XTPX::API::XTPQueryStkPositionRsp();
		*task_data = *position;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQuerySecurityAccount(XTPX::API::XTPQueryAccountIdRsp *account_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYSECURITYACCOUNT;

	if (account_info)
	{
		XTPX::API::XTPQueryAccountIdRsp *task_data = new XTPX::API::XTPQueryAccountIdRsp();
		*task_data = *account_info;
		task->task_data = task_data;
	}
	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}
	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnQueryAsset(XTPX::API::XTPQueryAssetRsp *asset, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYASSET;

	if (asset)
	{
		XTPX::API::XTPQueryAssetRsp *task_data = new XTPX::API::XTPQueryAssetRsp();
		*task_data = *asset;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};


void TraderApi::OnQueryFundTransfer(XTPX::API::XTPFundTransferLog *fund_transfer_info, XTPX::API::XTPRI *fund_transfer_err_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYFUNDTRANSFER;

	if (fund_transfer_info)
	{
		XTPX::API::XTPFundTransferLog *task_data = new XTPX::API::XTPFundTransferLog();
		*task_data = *fund_transfer_info;
		task->task_data = task_data;
	}
	if (fund_transfer_err_info)
	{
		XTPX::API::XTPRI *task_error_extra = new XTPX::API::XTPRI();
		*task_error_extra = *fund_transfer_err_info;
		task->task_error_extra = task_error_extra;
	}
	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryFundTransferByPage(XTPX::API::XTPFundTransferLog *fund_transfer_info, XTPX::API::XTPRI *fund_transfer_err_info, XTPX::API::XTPRI *error_info, int64_t req_count, int64_t sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYFUNDTRANSFERBYPAGE;
	if (fund_transfer_info)
	{
		XTPX::API::XTPFundTransferLog *task_data = new XTPX::API::XTPFundTransferLog();
		*task_data = *fund_transfer_info;
		task->task_data = task_data;
	}
	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}
	if (fund_transfer_err_info)
	{
		XTPX::API::XTPRI *task_error_extra = new XTPX::API::XTPRI();
		*task_error_extra = *fund_transfer_err_info;
		task->task_error_extra = task_error_extra;
	}
	task->addtional_int_two = req_count;
	task->addtional_int_three = sequence;
	task->addtional_int_four = query_reference;
	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnFundTransfer(XTPX::API::XTPFundTransferNotice *fund_transfer_info, XTPX::API::XTPRI *error_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONFUNDTRANSFER;

	if (fund_transfer_info)
	{
		XTPX::API::XTPFundTransferNotice *task_data = new XTPX::API::XTPFundTransferNotice();
		*task_data = *fund_transfer_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnUnknownFundTransfer(uint64_t serial_id, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONUNKNOWNFUNDTRANSFER;

	task->addtional_int_five = serial_id;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnQueryOtherServerFund(XTPX::API::XTPFundQueryRsp *fund_info, XTPX::API::XTPRI *error_info, int request_id, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONQUERYOTHERSERVERFUND;

	if (fund_info) {
		XTPX::API::XTPFundQueryRsp *task_data = new XTPX::API::XTPFundQueryRsp();
		*task_data = *fund_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnQueryETF(XTPX::API::XTPQueryETFBaseRsp *etf_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYETF;

	if (etf_info)
	{
		XTPX::API::XTPQueryETFBaseRsp *task_data = new XTPX::API::XTPQueryETFBaseRsp();
		*task_data = *etf_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryETFBasket(XTPX::API::XTPQueryETFComponentRsp *etf_component_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYETFBASKET;

	if (etf_component_info)
	{
		XTPX::API::XTPQueryETFComponentRsp *task_data = new XTPX::API::XTPQueryETFComponentRsp();
		*task_data = *etf_component_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryIPOInfoList(XTPX::API::XTPQueryIPOTickerRsp *ipo_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYIPOINFOLIST;

	if (ipo_info)
	{
		XTPX::API::XTPQueryIPOTickerRsp *task_data = new XTPX::API::XTPQueryIPOTickerRsp();
		*task_data = *ipo_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryIPOQuotaInfo(XTPX::API::XTPQueryIPOQuotaRsp *quota_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYIPOQUOTAINFO;

	if (quota_info)
	{
		XTPX::API::XTPQueryIPOQuotaRsp *task_data = new XTPX::API::XTPQueryIPOQuotaRsp();
		*task_data = *quota_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryBondIPOInfoList(XTPX::API::XTPQueryIPOTickerRsp *ipo_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYBONDIPOINFOLIST;

	if (ipo_info)
	{
		XTPX::API::XTPQueryIPOTickerRsp *task_data = new XTPX::API::XTPQueryIPOTickerRsp();
		*task_data = *ipo_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnQueryBondSwapStockInfo(XTPX::API::XTPQueryBondSwapStockRsp *swap_stock_info, XTPX::API::XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYBONDSWAPSTOCKINFO;
	
	if(swap_stock_info)
	{
		XTPX::API::XTPQueryBondSwapStockRsp *task_data = new XTPX::API::XTPQueryBondSwapStockRsp;
		*task_data = *swap_stock_info;
		task->task_data = task_data;
	}
	
	if (error_info)
	{
		XTPX::API::XTPRI *task_error = new XTPX::API::XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

/*void TraderApi::OnQueryOptionAuctionInfo(XTPQueryOptionAuctionInfoRsp *option_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYOPTIONAUCTIONINFO;

	if (option_info)
	{
		XTPQueryOptionAuctionInfoRsp *task_data = new XTPQueryOptionAuctionInfoRsp();
		*task_data = *option_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnCreditCashRepay(XTPCrdCashRepayRsp *cash_repay_info, XTPRI *error_info, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONCREDITCASHREPAY;
	if (cash_repay_info)
	{
		XTPCrdCashRepayRsp *task_data = new XTPCrdCashRepayRsp();
		*task_data = *cash_repay_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryCreditCashRepayInfo(XTPCrdCashRepayInfo * cash_repay_info, XTPRI * error_info, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITCASHREPAYINFO;
	if (cash_repay_info)
	{
		XTPCrdCashRepayInfo *task_data = new XTPCrdCashRepayInfo();
		*task_data = *cash_repay_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryCreditFundInfo(XTPCrdFundInfo * fund_info, XTPRI * error_info, int request_id, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITFUNDINFO;
	if (fund_info)
	{
		XTPCrdFundInfo *task_data = new XTPCrdFundInfo();
		*task_data = *fund_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryCreditDebtInfo(XTPCrdDebtInfo * debt_info, XTPRI * error_info, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITDEBTINFO;
	if (debt_info)
	{
		XTPCrdDebtInfo *task_data = new XTPCrdDebtInfo();
		*task_data = *debt_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryCreditTickerDebtInfo(XTPCrdDebtStockInfo * debt_info, XTPRI * error_info, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITTICKERDEBTINFO;
	if (debt_info)
	{
		XTPCrdDebtStockInfo *task_data = new XTPCrdDebtStockInfo();
		*task_data = *debt_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryCreditAssetDebtInfo(double remain_amount, XTPRI * error_info, int request_id, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITASSETDEBTINFO;
	task->remain_amount = remain_amount;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryCreditTickerAssignInfo(XTPClientQueryCrdPositionStkInfo * assign_info, XTPRI * error_info, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITTICKERASSIGNINFO;
	if (assign_info)
	{
		XTPClientQueryCrdPositionStkInfo *task_data = new XTPClientQueryCrdPositionStkInfo();
		*task_data = *assign_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryCreditExcessStock(XTPClientQueryCrdSurplusStkRspInfo * stock_info, XTPRI * error_info, int request_id, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITEXCESSSTOCK;
	if (stock_info)
	{
		XTPClientQueryCrdSurplusStkRspInfo *task_data = new XTPClientQueryCrdSurplusStkRspInfo();
		*task_data = *stock_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnQueryMulCreditExcessStock(XTPClientQueryCrdSurplusStkRspInfo * stock_info, XTPRI * error_info, int request_id, uint64_t session_id, bool is_last) {

	Task* task = new Task();
	task->task_name = ONQUERYMULCREDITEXCESSSTOCK;
	if (stock_info)
	{
		XTPClientQueryCrdSurplusStkRspInfo *task_data = new XTPClientQueryCrdSurplusStkRspInfo();
		*task_data = *stock_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->addtional_int = session_id;
	task->task_last = is_last;
	this->task_queue.push(task);
}


void TraderApi::OnCreditExtendDebtDate(XTPCreditDebtExtendNotice *debt_extend_info, XTPRI * error_info, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONCREDITEXTENDDEBTDATE;
	if (debt_extend_info)
	{
		XTPCreditDebtExtendNotice *task_data = new XTPCreditDebtExtendNotice();
		*task_data = *debt_extend_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnQueryCreditExtendDebtDateOrders(XTPCreditDebtExtendNotice *debt_extend_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITEXTENDDEBTDATEORDERS;
	if (debt_extend_info)
	{
		XTPCreditDebtExtendNotice *task_data = new XTPCreditDebtExtendNotice();
		*task_data = *debt_extend_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;

	this->task_queue.push(task);
}

void TraderApi::OnQueryCreditFundExtraInfo(XTPCrdFundExtraInfo *fund_info, XTPRI *error_info, int request_id, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITFUNDEXTRAINFO;
	if (fund_info)
	{
		XTPCrdFundExtraInfo *task_data = new XTPCrdFundExtraInfo();
		*task_data = *fund_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->addtional_int = session_id;

	this->task_queue.push(task);
}

void TraderApi::OnQueryCreditPositionExtraInfo(XTPCrdPositionExtraInfo *fund_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYCREDITPOSITIONEXTRAINFO;
	if (fund_info)
	{
		XTPCrdPositionExtraInfo *task_data = new XTPCrdPositionExtraInfo();
		*task_data = *fund_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;

	this->task_queue.push(task);
}

void TraderApi::OnCreditCashRepayDebtInterestFee(XTPCrdCashRepayDebtInterestFeeRsp *cash_repay_info, XTPRI *error_info, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONCREDITCASHREPAYDEBTINTERESTFEE;
	if (cash_repay_info)
	{
		XTPCrdCashRepayDebtInterestFeeRsp *task_data = new XTPCrdCashRepayDebtInterestFeeRsp();
		*task_data = *cash_repay_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}



void TraderApi::OnCancelOptionCombinedOrderError(XTPOrderCancelInfo * cancel_info, XTPRI * error_info, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONCANCELOPTIONCOMBINEDORDERERROR;

	if (cancel_info) {
		XTPOrderCancelInfo *task_data = new XTPOrderCancelInfo();
		*task_data = *cancel_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnOptionCombinedOrderEvent(XTPOptCombOrderInfo * order_info, XTPRI * error_info, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONOPTIONCOMBINEDORDEREVENT;

	if (order_info) {
		XTPOptCombOrderInfo *task_data = new XTPOptCombOrderInfo();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnOptionCombinedTradeEvent(XTPOptCombTradeReport * trade_info, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONOPTIONCOMBINEDTRADEEVENT;

	if (trade_info) {
		XTPOptCombTradeReport *task_data = new XTPOptCombTradeReport();
		*task_data = *trade_info;
		task->task_data = task_data;
	}


	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryOptionCombinedOrders(XTPQueryOptCombOrderRsp * order_info, XTPRI * error_info, int request_id, bool is_last, uint64_t session_id) {
 
	Task* task = new Task();
	task->task_name = ONQUERYOPTIONCOMBINEDORDERS;

	if (order_info) {
		XTPQueryOptCombOrderRsp *task_data = new XTPQueryOptCombOrderRsp();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryOptionCombinedOrdersEx(XTPOptCombOrderInfoEx *order_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYOPTIONCOMBINEDORDERSEX;

	if (order_info)
	{
		XTPOptCombOrderInfoEx *task_data = new XTPOptCombOrderInfoEx();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryOptionCombinedOrdersByPage(XTPQueryOptCombOrderRsp * order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYOPTIONCOMBINEDORDERSBYPAGE;

	if (order_info) {
		XTPQueryOptCombOrderRsp *task_data = new XTPQueryOptCombOrderRsp();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	task->req_count = req_count;
	task->order_sequence = order_sequence;
	task->query_reference = query_reference;

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnQueryOptionCombinedOrdersByPageEx(XTPOptCombOrderInfoEx *order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYOPTIONCOMBINEDORDERSBYPAGEEX;

	if (order_info)
	{
		XTPOptCombOrderInfoEx *task_data = new XTPOptCombOrderInfoEx();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	task->req_count = req_count;
	task->order_sequence = order_sequence;
	task->query_reference = query_reference;

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnQueryOptionCombinedTrades(XTPQueryOptCombTradeRsp * trade_info, XTPRI * error_info, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYOPTIONCOMBINEDTRADES;

	if (trade_info) {
		XTPQueryOptCombTradeRsp *task_data = new XTPQueryOptCombTradeRsp();
		*task_data = *trade_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryOptionCombinedTradesByPage(XTPQueryOptCombTradeRsp * trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYOPTIONCOMBINEDTRADESBYPAGE;


	if (trade_info) {
		XTPQueryOptCombTradeRsp *task_data = new XTPQueryOptCombTradeRsp();
		*task_data = *trade_info;
		task->task_data = task_data;
	}
	task->task_id = request_id;
	task->task_last = is_last;
	task->query_reference = query_reference;

	task->req_count = req_count;
	task->trade_sequence = trade_sequence;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryOptionCombinedPosition(XTPQueryOptCombPositionRsp * position_info, XTPRI * error_info, int request_id, bool is_last, uint64_t session_id) {

	Task* task = new Task();
	task->task_name = ONQUERYOPTIONCOMBINEDPOSITION;

	if (position_info) {
		XTPQueryOptCombPositionRsp *task_data = new XTPQueryOptCombPositionRsp();
		*task_data = *position_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnQueryOptionCombinedStrategyInfo(XTPQueryCombineStrategyInfoRsp * strategy_info, XTPRI * error_info, int request_id, bool is_last, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONQUERYOPTIONCOMBINEDSTRATEGYINFO;

	if (strategy_info) {
		XTPQueryCombineStrategyInfoRsp *task_data = new XTPQueryCombineStrategyInfoRsp();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnQueryOptionCombinedExecPosition(XTPQueryOptCombExecPosRsp *position_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONQUERYOPTIONCOMBINEDEXECPOSITION;
	if (position_info) {
		XTPQueryOptCombExecPosRsp *task_data = new XTPQueryOptCombExecPosRsp();
		*task_data = *position_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}
*/



////////////////////////algo////////////////////////
/*void TraderApi::OnQueryStrategy(XTPStrategyInfoStruct* strategy_info, char* strategy_param, XTPRI *error_info, int32_t request_id, bool is_last, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONQUERYSTRATEGY;
	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}
	
	if(strategy_param)
		task->strategy_param = addEndingChar(strategy_param);
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}
	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
	
}

void TraderApi::OnStrategyStateReport(XTPStrategyStateReportStruct* strategy_state,uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONSTRATEGYASTATEREPORT;

	if (strategy_state) {
		XTPStrategyStateReportStruct *task_data = new XTPStrategyStateReportStruct();
		*task_data = *strategy_state;
		task->task_data = task_data;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnALGOUserEstablishChannel(char* user, XTPRI* error_info, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONALGOUSERESTABLISHCHANNEL;

	task->user = addEndingChar(user);

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}


	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnInsertAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPRI *error_info, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONINSERTALGOORDER;

	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnCancelAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPRI *error_info, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONCANCELALGOORDER;

	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnAlgoDisconnected(int reason){
	Task* task = new Task();
	task->task_name = ONALGODISCONNECTED;


	task->reason = reason;
	this->task_queue.push(task);
}

void TraderApi::OnAlgoConnected(){
	Task* task = new Task();
	task->task_name = ONALGOCONNECTED;

	this->task_queue.push(task);
}

void TraderApi::OnStrategySymbolStateReport(XTPStrategySymbolStateReport* strategy_symbol_state, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONSTRATEGYSYMBOLSTATEREPORT;

	if (strategy_symbol_state)
	{
		XTPStrategySymbolStateReport *task_data = new XTPStrategySymbolStateReport();
		*task_data = *strategy_symbol_state;
		task->task_data = task_data;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnNewStrategyCreateReport(XTPStrategyInfoStruct* strategy_info, char* strategy_param, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONNEWSTRATEGYCREATEREPORT;

	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if(strategy_param)
	{
		task->strategy_param = addEndingChar(strategy_param);
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnStrategyRecommendation(bool basket_flag, XTPStrategyRecommendationInfo* recommendation_info, char* strategy_param, XTPRI *error_info, int32_t request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONSTRATEGYRECOMMENDATION;
	task->addtional_bool = basket_flag;

	if (recommendation_info) {
		XTPStrategyRecommendationInfo *task_data = new XTPStrategyRecommendationInfo();
		*task_data = *recommendation_info;
		task->task_data = task_data;
	}

	if (strategy_param)
	{
		task->strategy_param = addEndingChar(strategy_param);
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnModifyAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPRI *error_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONMODIFYALGOORDER;

	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}*/

///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void TraderApi::processTask()
{
	while (1)
	{
		Task* task = this->task_queue.wait_and_pop();

		switch (task->task_name)
		{
			case ONDISCONNECTED:
			{
				this->processDisconnected(task);
				break;
			}
			case ONSERVERSTATUSNOTIFICATION:
			{
				this->processServerStatusNotification(task);
				break;
			}

			case ONERROR:
			{
				this->processError(task);
				break;
			}
			case ONCONNECT:
			{
				this->processConnect(task);
				break;
			}
			case ONRESUMEEND:
			{
				this->processResumeEnd(task);
				break;
			}
			case ONUNKNOWNORDER:
			{
				this->processUnknownOrder(task);
				break;
			}
			case ONORDERACK:
			{
				this->processOrderAck(task);
				break;
			}

			case ONORDEREVENT:
			{
				this->processOrderEvent(task);
				break;
			}

			case ONTRADEEVENT:
			{
				this->processTradeEvent(task);
				break;
			}

			case ONCANCELORDERERROR:
			{
				this->processCancelOrderError(task);
				break;
			}

			case ONQUERYORDER:
			{
				this->processQueryOrder(task);
				break;
			}
			case ONQUERYORDERBYPAGE:
			{
				this->processQueryOrderByPage(task);
				break;
			}
			case ONQUERYTRADE:
			{
				this->processQueryTrade(task);
				break;
			}
			case ONQUERYTRADEBYPAGE:
			{
				this->processQueryTradeByPage(task);
				break;
			}
			case ONQUERYPOSITION:
			{
				this->processQueryPosition(task);
				break;
			}
			case ONQUERYSECURITYACCOUNT:
			{
				this->processQuerySecurityAccount(task);
				break;
			}
			case ONQUERYASSET:
			{
				this->processQueryAsset(task);
				break;
			}



			case ONQUERYFUNDTRANSFER:
			{
				this->processQueryFundTransfer(task);
				break;
			}
			case ONQUERYFUNDTRANSFERBYPAGE:
			{
				this->processQueryFundTransferByPage(task);
				break;
			}

			case ONFUNDTRANSFER:
			{
				this->processFundTransfer(task);
				break;
			}
			case ONUNKNOWNFUNDTRANSFER:
			{
				this->processUnknownFundTransfer(task);
				break;
			}
			case ONQUERYOTHERSERVERFUND: {
				this->processQueryOtherServerFund(task);
				break;
			}

			case ONQUERYETF:
			{
				this->processQueryETF(task);
				break;
			}

			case ONQUERYETFBASKET:
			{
				this->processQueryETFBasket(task);
				break;
			}

			case ONQUERYIPOINFOLIST:
			{
				this->processQueryIPOInfoList(task);
				break;
			}

			case ONQUERYIPOQUOTAINFO:
			{
				this->processQueryIPOQuotaInfo(task);
				break;
			}

			case ONQUERYBONDIPOINFOLIST:
			{
				this->processQueryBondIPOInfoList(task);
				break;
			}

			case ONQUERYBONDSWAPSTOCKINFO:
			{
				this->processQueryBondSwapStockInfo(task);
				break;
			}
			/*
			case ONQUERYOPTIONAUCTIONINFO:
			{
				this->processQueryOptionAuctionInfo(task);
				break;
			}

			case ONCREDITCASHREPAY: {
				this->processCreditCashRepay(task);
				break;
									}

			case ONQUERYCREDITCASHREPAYINFO: {
				this->processQueryCreditCashRepayInfo(task);
				break;
											 }

			case ONQUERYCREDITFUNDINFO: {
				this->processQueryCreditFundInfo(task);
				break;
										}

			case ONQUERYCREDITDEBTINFO: {
				this->processQueryCreditDebtInfo(task);
				break;
										}

			case ONQUERYCREDITTICKERDEBTINFO: {
				this->processQueryCreditTickerDebtInfo(task);
				break;
											  }

			case ONQUERYCREDITASSETDEBTINFO: {
				this->processQueryCreditAssetDebtInfo(task);
				break;
											 }

			case ONQUERYCREDITTICKERASSIGNINFO: {
				this->processQueryCreditTickerAssignInfo(task);
				break;
												}

			case ONQUERYCREDITEXCESSSTOCK: {
				this->processQueryCreditExcessStock(task);
				break;
										   }
			case ONQUERYMULCREDITEXCESSSTOCK: {
				this->processQueryMulCreditExcessStock(task);
				break;
										   }

			case ONCREDITEXTENDDEBTDATE: {
				this->processCreditExtendDebtDate(task);
				break;
											  }

			case ONQUERYCREDITEXTENDDEBTDATEORDERS: {
				this->processQueryCreditExtendDebtDateOrders(task);
				break;
											 }

			case ONQUERYCREDITFUNDEXTRAINFO: {
				this->processQueryCreditFundExtraInfo(task);
				break;
												}

			case ONQUERYCREDITPOSITIONEXTRAINFO: {
				this->processQueryCreditPositionExtraInfo(task);
				break;
										   }
			case ONCREDITCASHREPAYDEBTINTERESTFEE: {
				this->processCreditCashRepayDebtInterestFee(task);
				break;
									}

			case ONOPTIONCOMBINEDORDEREVENT: {
				this->processOptionCombinedOrderEvent(task);
				break;
											 }

			case ONOPTIONCOMBINEDTRADEEVENT: {
				this->processOptionCombinedTradeEvent(task);
				break;
											 }

			case ONQUERYOPTIONCOMBINEDORDERS: {
				this->processQueryOptionCombinedOrders(task);
				break;
											  }
			case ONQUERYOPTIONCOMBINEDORDERSEX: 
			{
				this->processQueryOptionCombinedOrdersEx(task);
				break;
			}

			case ONQUERYOPTIONCOMBINEDORDERSBYPAGE: {
				this->processQueryOptionCombinedOrdersByPage(task);
				break;
													}
			case ONQUERYOPTIONCOMBINEDORDERSBYPAGEEX:
			{
				this->processQueryOptionCombinedOrdersByPageEx(task);
				break;
			}

			case ONQUERYOPTIONCOMBINEDTRADES: {
				this->processQueryOptionCombinedTrades(task);
				break;
											  }

			case ONQUERYOPTIONCOMBINEDTRADESBYPAGE: {
				this->processQueryOptionCombinedTradesByPage(task);
				break;
													}

			case ONQUERYOPTIONCOMBINEDPOSITION: {
				this->processQueryOptionCombinedPosition(task);
				break;
			}

			case ONQUERYOPTIONCOMBINEDSTRATEGYINFO: {
				this->processQueryOptionCombinedStrategyInfo(task);
				break;
			}
			case ONCANCELOPTIONCOMBINEDORDERERROR: {
				this->processCancelOptionCombinedOrderError(task);
				break;
			}
			case ONQUERYOPTIONCOMBINEDEXECPOSITION: {
				this->processQueryOptionCombinedExecPosition(task);
				break;
			}
			

			case ONQUERYSTRATEGY: {
			   this->processQueryStrategy(task);
			   break;
			}
			
			case ONSTRATEGYASTATEREPORT: {
				this->processStrategyStateReport(task);
				break;
			}
			case ONALGOUSERESTABLISHCHANNEL: {
				this->processALGOUserEstablishChannel(task);
				break;
			}
			case ONINSERTALGOORDER: {
				this->processInsertAlgoOrder(task);
				break;
			}
			case ONCANCELALGOORDER: {
				this->processCancelAlgoOrder(task);
				break;
			}
			case ONALGODISCONNECTED: {
				this->processAlgoDisconnected(task);
				break;
			}case ONALGOCONNECTED: {
				this->processAlgoConnected(task);
				break;
			}
			case ONSTRATEGYSYMBOLSTATEREPORT:
			{
				this->processStrategySymbolStateReport(task);
				break;
			}
			case ONNEWSTRATEGYCREATEREPORT:
			{
				this->processNewStrategyCreateReport(task);
				break;
			}
			case ONSTRATEGYRECOMMENDATION:
			{
				this->processStrategyRecommendation(task);
				break;
			}
			case ONMODIFYALGOORDER:
			{
				this->processModifyAlgoOrder(task);
				break;
			}*/
		};
	}
};

void TraderApi::processDisconnected(Task *task)
{
	PyLock lock;
	this->onDisconnected(task->addtional_int, task->task_id);
	delete task;
};

void TraderApi::processServerStatusNotification(Task *task)
{
	PyLock lock;
	this->onServerStatusNotification(task->addtional_int, task->task_id, task->addtional_bool);
	delete task;
}

void TraderApi::processError(Task *task)
{
	PyLock lock;
	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onError(error);
	delete task;
};

void TraderApi::processConnect(Task *task)
{
	PyLock lock;
	this->onConnect(task->addtional_int, task->user);
	delete task;
}

void TraderApi::processResumeEnd(Task *task)
{
	PyLock lock;
	this->onResumeEnd(task->addtional_int);
	delete task;
}

void TraderApi::processUnknownOrder(Task *task)
{
	PyLock lock;
	this->onUnknownOrder(task->addtional_int_five, task->addtional_int);
	delete task;
}

void TraderApi::processOrderAck(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPOrderInfo *task_data = (XTPX::API::XTPOrderInfo*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["market"] = (int)task_data->market;
		data["order_client_id"] = task_data->order_client_id;
		data["order_local_id"] = addEndingChar(task_data->order_local_id);
		data["exec_type"] = task_data->exec_type;
		data["order_status"] = (int)task_data->order_status;
		data["order_exch_id"] = addEndingChar(task_data->order_exch_id);
		data["order_type"] = task_data->order_type;
		data["side"] = (int)task_data->side;
		data["position_effect"] = (int)task_data->position_effect;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["quantity"] = task_data->quantity;
		data["price"] = task_data->price;
		data["price_type"] = (int)task_data->price_type;
		data["business_type"] = int(task_data->business_type);
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["trade_amount"] = task_data->trade_amount;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["order_withhold_amount"] = task_data->order_withhold_amount;
		data["order_withhold_fee"] = task_data->order_withhold_fee;
		data["exec_id"] = addEndingChar(task_data->exec_id);
		data["strategy_type"] = task_data->strategy_type;
		data["set_id"] = task_data->set_id;
		data["report_index"] = task_data->report_index;
		data["transact_time"] = task_data->transact_time;
		data["insert_time"] = task_data->insert_time;
		data["cancel_time"] = task_data->cancel_time;
		data["update_time"] = task_data->update_time;
		data["strategy_id"] = task_data->strategy_id;
		data["error_code"] = task_data->error_code;
		data["extra_error_code"] = task_data->extra_error_code;
		data["account_id"] = addEndingChar(task_data->account_id);
		data["branch_pbu"] = addEndingChar(task_data->branch_pbu);
		data["unused"] = addEndingChar(task_data->unused);

		delete task->task_data;
	}
	this->onOrderAck(data, task->addtional_int);
	delete task;
}


void TraderApi::processOrderEvent(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPOrderInfo *task_data = (XTPX::API::XTPOrderInfo*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["market"] = (int)task_data->market;
		data["order_client_id"] = task_data->order_client_id;
		data["order_local_id"] = addEndingChar(task_data->order_local_id);
		data["exec_type"] = task_data->exec_type;
		data["order_status"] = (int)task_data->order_status;
		data["order_exch_id"] = addEndingChar(task_data->order_exch_id);
		data["order_type"] = task_data->order_type;
		data["side"] = (int)task_data->side;
		data["position_effect"] = (int)task_data->position_effect;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["quantity"] = task_data->quantity;
		data["price"] = task_data->price;
		data["price_type"] = (int)task_data->price_type;
		data["business_type"] = int(task_data->business_type);
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["trade_amount"] = task_data->trade_amount;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["order_withhold_amount"] = task_data->order_withhold_amount;
		data["order_withhold_fee"] = task_data->order_withhold_fee;
		data["exec_id"] = addEndingChar(task_data->exec_id);
		data["strategy_type"] = task_data->strategy_type;
		data["set_id"] = task_data->set_id;
		data["report_index"] = task_data->report_index;
		data["transact_time"] = task_data->transact_time;
		data["insert_time"] = task_data->insert_time;
		data["cancel_time"] = task_data->cancel_time;
		data["update_time"] = task_data->update_time;
		data["strategy_id"] = task_data->strategy_id;
		data["error_code"] = task_data->error_code;
		data["extra_error_code"] = task_data->extra_error_code;
		data["account_id"] = addEndingChar(task_data->account_id);
		data["branch_pbu"] = addEndingChar(task_data->branch_pbu);
		data["unused"] = addEndingChar(task_data->unused);
		
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onOrderEvent(data, error, task->addtional_int);
	delete task;
};

void TraderApi::processTradeEvent(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPTradeReport *task_data = (XTPX::API::XTPTradeReport*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["market"] = (int)task_data->market;
		data["order_client_id"] = task_data->order_client_id;
		data["trade_time"] = task_data->trade_time;
		data["branch_pbu"] = addEndingChar(task_data->branch_pbu);
		data["trade_type"] = task_data->trade_type;
		data["order_local_id"] = addEndingChar(task_data->order_local_id);
		data["side"] = (int)task_data->side;
		data["business_type"] = int(task_data->business_type);
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["trade_amount"] = task_data->trade_amount;
		data["order_exch_id"] = addEndingChar(task_data->order_exch_id);
		data["position_effect"] = (int)task_data->position_effect;
		data["strategy_type"] = task_data->strategy_type;
		data["set_id"] = task_data->set_id;
		data["report_index"] = task_data->report_index;
		data["strategy_id"] = task_data->strategy_id;
		data["exec_id"] = addEndingChar(task_data->exec_id);
		data["account_id"] = addEndingChar(task_data->account_id);
		
		data["unused"] = addEndingChar(task_data->unused);
		
		delete task->task_data;
	}

	this->onTradeEvent(data, task->addtional_int);
	delete task;
};

void TraderApi::processCancelOrderError(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPOrderCancelErrorInfo *task_data = (XTPX::API::XTPOrderCancelErrorInfo*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["market"] = (int)task_data->market;
		data["order_client_id"] = task_data->order_client_id;
		data["orig_order_xtp_id"] = task_data->orig_order_xtp_id;
		data["transact_time"] = task_data->transact_time;
		data["report_index"] = task_data->report_index;
		data["set_id"] = task_data->set_id;
		data["error_code"] = task_data->error_code;
		data["extra_error_code"] = task_data->extra_error_code;
		data["orig_order_local_id"] = addEndingChar(task_data->orig_order_local_id);
		data["order_local_id"] = addEndingChar(task_data->order_local_id);
		data["unused"] = addEndingChar(task_data->unused);
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onCancelOrderError(data, error, task->addtional_int);
	delete task;
};

void TraderApi::processQueryOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryOrderRsp *task_data = (XTPX::API::XTPQueryOrderRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["market"] = (int)task_data->market;
		data["order_client_id"] = task_data->order_client_id;
		data["order_local_id"] = addEndingChar(task_data->order_local_id);
		data["exec_type"] = task_data->exec_type;
		data["order_status"] = (int)task_data->order_status;
		data["order_exch_id"] = addEndingChar(task_data->order_exch_id);
		data["order_type"] = task_data->order_type;
		data["side"] = (int)task_data->side;
		data["position_effect"] = (int)task_data->position_effect;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["quantity"] = task_data->quantity;
		data["price"] = task_data->price;
		data["price_type"] = (int)task_data->price_type;
		data["business_type"] = int(task_data->business_type);
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["trade_amount"] = task_data->trade_amount;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["order_withhold_amount"] = task_data->order_withhold_amount;
		data["order_withhold_fee"] = task_data->order_withhold_fee;
		data["exec_id"] = addEndingChar(task_data->exec_id);
		data["strategy_type"] = task_data->strategy_type;
		data["set_id"] = task_data->set_id;
		data["report_index"] = task_data->report_index;
		data["transact_time"] = task_data->transact_time;
		data["insert_time"] = task_data->insert_time;
		data["cancel_time"] = task_data->cancel_time;
		data["update_time"] = task_data->update_time;
		data["strategy_id"] = task_data->strategy_id;
		data["error_code"] = task_data->error_code;
		data["extra_error_code"] = task_data->extra_error_code;
		data["account_id"] = addEndingChar(task_data->account_id);
		data["branch_pbu"] = addEndingChar(task_data->branch_pbu);
		data["unused"] = addEndingChar(task_data->unused);
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryOrder(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};


void TraderApi::processQueryOrderByPage(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryOrderRsp *task_data = (XTPX::API::XTPQueryOrderRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["market"] = (int)task_data->market;
		data["order_client_id"] = task_data->order_client_id;
		data["order_local_id"] = addEndingChar(task_data->order_local_id);
		data["exec_type"] = task_data->exec_type;
		data["order_status"] = (int)task_data->order_status;
		data["order_exch_id"] = addEndingChar(task_data->order_exch_id);
		data["order_type"] = task_data->order_type;
		data["side"] = (int)task_data->side;
		data["position_effect"] = (int)task_data->position_effect;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["quantity"] = task_data->quantity;
		data["price"] = task_data->price;
		data["price_type"] = (int)task_data->price_type;
		data["business_type"] = int(task_data->business_type);
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["trade_amount"] = task_data->trade_amount;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["order_withhold_amount"] = task_data->order_withhold_amount;
		data["order_withhold_fee"] = task_data->order_withhold_fee;
		data["exec_id"] = addEndingChar(task_data->exec_id);
		data["strategy_type"] = task_data->strategy_type;
		data["set_id"] = task_data->set_id;
		data["report_index"] = task_data->report_index;
		data["transact_time"] = task_data->transact_time;
		data["insert_time"] = task_data->insert_time;
		data["cancel_time"] = task_data->cancel_time;
		data["update_time"] = task_data->update_time;
		data["strategy_id"] = task_data->strategy_id;
		data["error_code"] = task_data->error_code;
		data["extra_error_code"] = task_data->extra_error_code;
		data["account_id"] = addEndingChar(task_data->account_id);
		data["branch_pbu"] = addEndingChar(task_data->branch_pbu);
		data["unused"] = addEndingChar(task_data->unused);
		delete task->task_data;
	}



	this->onQueryOrderByPage(data, task->addtional_int_two, task->addtional_int_three, task->addtional_int_four, task->task_id, task->task_last, task->addtional_int);
	delete task;
};


void TraderApi::processQueryTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryTradeRsp *task_data = (XTPX::API::XTPQueryTradeRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["market"] = (int)task_data->market;
		data["order_client_id"] = task_data->order_client_id;
		data["trade_time"] = task_data->trade_time;
		data["branch_pbu"] = addEndingChar(task_data->branch_pbu);
		data["trade_type"] = task_data->trade_type;
		data["order_local_id"] = addEndingChar(task_data->order_local_id);
		data["side"] = (int)task_data->side;
		data["business_type"] = int(task_data->business_type);
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["trade_amount"] = task_data->trade_amount;
		data["order_exch_id"] = addEndingChar(task_data->order_exch_id);
		data["position_effect"] = (int)task_data->position_effect;
		data["strategy_type"] = task_data->strategy_type;
		data["set_id"] = task_data->set_id;
		data["report_index"] = task_data->report_index;
		data["strategy_id"] = task_data->strategy_id;
		data["exec_id"] = addEndingChar(task_data->exec_id);
		data["account_id"] = addEndingChar(task_data->account_id);

		data["unused"] = addEndingChar(task_data->unused);
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryTrade(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryTradeByPage(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryTradeRsp *task_data = (XTPX::API::XTPQueryTradeRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["market"] = (int)task_data->market;
		data["order_client_id"] = task_data->order_client_id;
		data["trade_time"] = task_data->trade_time;
		data["branch_pbu"] = addEndingChar(task_data->branch_pbu);
		data["trade_type"] = task_data->trade_type;
		data["order_local_id"] = addEndingChar(task_data->order_local_id);
		data["side"] = (int)task_data->side;
		data["business_type"] = int(task_data->business_type);
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["trade_amount"] = task_data->trade_amount;
		data["order_exch_id"] = addEndingChar(task_data->order_exch_id);
		data["position_effect"] = (int)task_data->position_effect;
		data["strategy_type"] = task_data->strategy_type;
		data["set_id"] = task_data->set_id;
		data["report_index"] = task_data->report_index;
		data["strategy_id"] = task_data->strategy_id;
		data["exec_id"] = addEndingChar(task_data->exec_id);
		data["account_id"] = addEndingChar(task_data->account_id);

		data["unused"] = addEndingChar(task_data->unused);
		delete task->task_data;
	}

	this->onQueryTradeByPage(data, task->addtional_int_two, task->addtional_int_three, task->addtional_int_four, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryStkPositionRsp *task_data = (XTPX::API::XTPQueryStkPositionRsp*)task->task_data;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["ticker_name"] = addEndingChar(task_data->ticker_name);
		data["account_id"] = addEndingChar(task_data->account_id);
		data["market"] = int(task_data->market);
		data["unused"] = addEndingChar(task_data->unused);	//手动修改
		data["total_qty"] = task_data->total_qty;
		data["sellable_qty"] = task_data->sellable_qty;
		data["avg_price"] = task_data->avg_price;
		data["unrealized_pnl"] = task_data->unrealized_pnl;
		data["yesterday_position"] = task_data->yesterday_position;
		data["purchase_redeemable_qty"] = task_data->purchase_redeemable_qty;	

		data["position_direction"] = (int)task_data->position_direction;
		data["position_security_type"] = (int)task_data->position_security_type;
		data["executable_option"] = task_data->executable_option;
		data["lockable_position"] = task_data->lockable_position;
		data["executable_underlying"] = task_data->executable_underlying;
		data["locked_position"] = task_data->locked_position;
		data["usable_locked_position"] = task_data->usable_locked_position;

		data["profit_price"] = task_data->profit_price;
		data["buy_cost"] = task_data->buy_cost;
		data["profit_cost"] = task_data->profit_cost;
		data["market_value"] = task_data->market_value;

		data["margin"] = task_data->margin;
		data["last_buy_cost"] = task_data->last_buy_cost;
		data["last_profit_cost"] = task_data->last_profit_cost;

		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryPosition(data, error, task->task_id, task->task_last, task->addtional_int);

	delete task;
};

void TraderApi::processQuerySecurityAccount(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryAccountIdRsp *task_data = (XTPX::API::XTPQueryAccountIdRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["account_id"] = addEndingChar(task_data->account_id);
		data["is_main_account"] = task_data->is_main_account;
		data["unused"] = addEndingChar(task_data->unused);
		delete task->task_data;

	}
	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}
	this->onQuerySecurityAccount(data, error, task->task_id, task->task_last, task->addtional_int);
}

void TraderApi::processQueryAsset(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryAssetRsp *task_data = (XTPX::API::XTPQueryAssetRsp*)task->task_data;

		data["total_asset"] = task_data->total_asset;
		data["buying_power"] = task_data->buying_power;
		data["security_asset"] = task_data->security_asset;
		data["fund_buy_amount"] = task_data->fund_buy_amount;
		data["fund_buy_fee"] = task_data->fund_buy_fee;
		data["fund_sell_amount"] = task_data->fund_sell_amount;
		data["fund_sell_fee"] = task_data->fund_sell_fee;
		data["withholding_amount"] = task_data->withholding_amount;
		data["account_type"] = (int)task_data->account_type;
		data["currency_type"] = (int)task_data->currency_type;

		data["frozen_margin"] = task_data->frozen_margin;
		data["frozen_exec_cash"] = task_data->frozen_exec_cash;
		data["frozen_exec_fee"] = task_data->frozen_exec_fee;
		data["pay_later"] = task_data->pay_later;
		data["preadva_pay"] = task_data->preadva_pay;
		data["orig_banlance"] = task_data->orig_banlance;
		data["banlance"] = task_data->banlance;
		data["deposit_withdraw"] = task_data->deposit_withdraw;
		data["trade_netting"] = task_data->trade_netting;
		data["captial_asset"] = task_data->captial_asset;
		data["force_freeze_amount"] = task_data->force_freeze_amount;
		data["preferred_amount"] = task_data->preferred_amount;

		data["repay_stock_aval_banlance"] = task_data->repay_stock_aval_banlance;
		data["fund_order_data_charges"] = task_data->fund_order_data_charges;
		data["fund_cancel_data_charges"] = task_data->fund_cancel_data_charges;
		data["exchange_cur_risk_degree"] = task_data->exchange_cur_risk_degree;
		data["company_cur_risk_degree"] = task_data->company_cur_risk_degree;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryAsset(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};


void TraderApi::processQueryFundTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPFundTransferNotice *task_data = (XTPX::API::XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = (int)task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = (int)task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		data["site"] = (int)task_data->site;
		data["currency_type"] = (int)task_data->currency_type;
		delete task->task_data;
	}
	dict fund_transfer_err_info;
	if (task->task_error_extra)
	{
		XTPX::API::XTPRI* task_error_extra = (XTPX::API::XTPRI*)task->task_error_extra;
		fund_transfer_err_info["error_id"] = task_error_extra->error_id;
		fund_transfer_err_info["error_msg"] = addEndingChar(task_error_extra->error_msg);
		delete task->task_error_extra;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryFundTransfer(data, fund_transfer_err_info, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryFundTransferByPage(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPFundTransferLog* task_data = (XTPX::API::XTPFundTransferLog*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = (int)task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = (int)task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		data["site"] = (int)task_data->site;
		data["currency_type"] = (int)task_data->currency_type;
		delete task->task_data;
	}
	dict fund_transfer_err_info;
	if (task->task_error_extra)
	{
		XTPX::API::XTPRI* task_error_extra = (XTPX::API::XTPRI*)task->task_error_extra;
		fund_transfer_err_info["error_id"] = task_error_extra->error_id;
		fund_transfer_err_info["error_msg"] = addEndingChar(task_error_extra->error_msg);
		delete task->task_error_extra;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}
	this->onQueryFundTransferByPage(data, fund_transfer_err_info, error, task->addtional_int_two, task->addtional_int_three, task->addtional_int_four, task->task_id, task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processFundTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPFundTransferNotice *task_data = (XTPX::API::XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = (int)task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = (int)task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		data["site"] = (int)task_data->site;
		data["currency_type"] = (int)task_data->currency_type;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onFundTransfer(data, error, task->addtional_int);
	delete task;
};

void TraderApi::processUnknownFundTransfer(Task *task)
{
	PyLock lock;
	
	this->onUnknownFundTransfer(task->addtional_int_five, task->addtional_int);
	delete task;
}

void TraderApi::processQueryETF(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryETFBaseRsp *task_data = (XTPX::API::XTPQueryETFBaseRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["etf"] = addEndingChar(task_data->etf);
		data["subscribe_redemption_ticker"] = addEndingChar(task_data->subscribe_redemption_ticker);
		data["unit"] = task_data->unit;
		data["subscribe_status"] = task_data->subscribe_status;
		data["redemption_status"] = task_data->redemption_status;
		data["max_cash_ratio"] = task_data->max_cash_ratio;
		data["estimate_amount"] = task_data->estimate_amount;
		data["cash_component"] = task_data->cash_component;
		data["net_value"] = task_data->net_value;
		data["total_amount"] = task_data->total_amount;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryETF(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryETFBasket(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryETFComponentRsp *task_data = (XTPX::API::XTPQueryETFComponentRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["component_ticker"] = addEndingChar(task_data->component_ticker);
		data["component_name"] = addEndingChar(task_data->component_name);
		data["quantity"] = task_data->quantity;
		data["component_market"] = (int)task_data->component_market;
		data["replace_type"] = (int)task_data->replace_type;
		data["premium_ratio"] = task_data->premium_ratio;
		data["amount"] = task_data->amount;
		data["creation_premium_ratio"] = task_data->creation_premium_ratio;
		data["redemption_discount_ratio"] = task_data->redemption_discount_ratio;
		data["creation_amount"] = task_data->creation_amount;
		data["redemption_amount"] = task_data->redemption_amount;
		data["unused"] = addEndingChar(task_data->unused);

		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryETFBasket(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryIPOInfoList(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryIPOTickerRsp *task_data = (XTPX::API::XTPQueryIPOTickerRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["ticker_name"] = addEndingChar(task_data->ticker_name);
		data["ticker_type"] = int(task_data->ticker_type);
		data["price"] = task_data->price;
		data["unit"] = task_data->unit;
		data["qty_upper_limit"] = task_data->qty_upper_limit;
		data["is_noprofit"] = task_data->is_noprofit;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryIPOInfoList(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryIPOQuotaInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryIPOQuotaRsp *task_data = (XTPX::API::XTPQueryIPOQuotaRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["tech_quantity"] = (int)task_data->tech_quantity;	
		data["unused"] = task_data->unused;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryIPOQuotaInfo(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryBondIPOInfoList(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryIPOTickerRsp *task_data = (XTPX::API::XTPQueryIPOTickerRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["ticker_name"] = addEndingChar(task_data->ticker_name);
		data["ticker_type"] = (int)task_data->ticker_type;
		data["price"] = task_data->price;
		data["unit"] = task_data->unit;
		data["qty_upper_limit"] = task_data->qty_upper_limit;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryBondIPOInfoList(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processQueryBondSwapStockInfo(Task *task) 
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPQueryBondSwapStockRsp *task_data = (XTPX::API::XTPQueryBondSwapStockRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["underlying_ticker"] = addEndingChar(task_data->underlying_ticker);
		data["unit"] = task_data->unit;
		data["qty_min"] = task_data->qty_min;
		data["qty_max"] = task_data->qty_max;
		data["swap_price"] = task_data->swap_price;
		data["swap_flag"] = task_data->swap_flag;
		data["unused"] = addEndingChar(task_data->unused);

		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryBondSwapStockInfo(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
}

/*void TraderApi::processQueryOptionAuctionInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryOptionAuctionInfoRsp *task_data = (XTPQueryOptionAuctionInfoRsp*)task->task_data;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["security_id_source"] = (int)task_data->security_id_source;
		data["symbol"] = addEndingChar(task_data->symbol);
		data["contract_id"] = addEndingChar(task_data->contract_id);
		data["underlying_security_id"] = addEndingChar(task_data->underlying_security_id);
		data["underlying_security_id_source"] = (int)task_data->underlying_security_id_source;

		data["list_date"] = task_data->list_date;
		data["last_trade_date"] = task_data->last_trade_date;
		data["ticker_type"] = (int)task_data->ticker_type;
		data["day_trading"] = task_data->day_trading;

		data["call_or_put"] = (int)task_data->call_or_put;
		data["delivery_day"] = task_data->delivery_day;
		data["delivery_month"] = task_data->delivery_month;

		data["exercise_type"] = (int)task_data->exercise_type;
		data["exercise_begin_date"] = task_data->exercise_begin_date;
		data["exercise_end_date"] = task_data->exercise_end_date;
		data["exercise_price"] = task_data->exercise_price;

		data["qty_unit"] = task_data->qty_unit;
		data["contract_unit"] = task_data->contract_unit;
		data["contract_position"] = task_data->contract_position;

		data["prev_close_price"] = task_data->prev_close_price;
		data["prev_clearing_price"] = task_data->prev_clearing_price;

		data["lmt_buy_max_qty"] = task_data->lmt_buy_max_qty;
		data["lmt_buy_min_qty"] = task_data->lmt_buy_min_qty;
		data["lmt_sell_max_qty"] = task_data->lmt_sell_max_qty;
		data["lmt_sell_min_qty"] = task_data->lmt_sell_min_qty;
		data["mkt_buy_max_qty"] = task_data->mkt_buy_max_qty;
		data["mkt_buy_min_qty"] = task_data->mkt_buy_min_qty;
		data["mkt_sell_max_qty"] = task_data->mkt_sell_max_qty;
		data["mkt_sell_min_qty"] = task_data->mkt_sell_min_qty;

		data["price_tick"] = task_data->price_tick;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["sell_margin"] = task_data->sell_margin;
		data["margin_ratio_param1"] = task_data->margin_ratio_param1;
		data["margin_ratio_param2"] = task_data->margin_ratio_param2;

		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryOptionAuctionInfo(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};


void TraderApi::processCreditCashRepay(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCrdCashRepayRsp *task_data = (XTPCrdCashRepayRsp*)task->task_data;
		data["xtp_id"] = task_data->xtp_id;
		data["request_amount"] = task_data->request_amount;
		data["cash_repay_amount"] = task_data->cash_repay_amount;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onCreditCashRepay(data, error, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditCashRepayInfo(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCrdCashRepayInfo *task_data = (XTPCrdCashRepayInfo*)task->task_data;
		data["xtp_id"] = task_data->xtp_id;
		data["status"] = (int)task_data->status;
		data["request_amount"] = task_data->request_amount;
		data["cash_repay_amount"] = task_data->cash_repay_amount;
		data["position_effect"] = (int)task_data->position_effect;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditCashRepayInfo(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditFundInfo(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCrdFundInfo *task_data = (XTPCrdFundInfo*)task->task_data;
		data["maintenance_ratio"] = task_data->maintenance_ratio;
		data["all_asset"] = task_data->all_asset;
		data["all_debt"] = task_data->all_debt;
		data["line_of_credit"] = task_data->line_of_credit;
		data["guaranty"] = task_data->guaranty;
		data["reserved"] = task_data->reserved;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditFundInfo(data, error, task->task_id, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditDebtInfo(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCrdDebtInfo *task_data = (XTPCrdDebtInfo*)task->task_data;
		data["debt_type"] = task_data->debt_type;
		data["debt_id"] = addEndingChar(task_data->debt_id);
		data["position_id"] = task_data->position_id;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["debt_status"] = task_data->debt_status;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["order_date"] = task_data->order_date;
		data["end_date"] = task_data->end_date;
		data["orig_end_date"] = task_data->orig_end_date;
		data["is_extended"] = task_data->is_extended;
		data["remain_amt"] = task_data->remain_amt;
		data["remain_qty"] = task_data->remain_qty;
		data["remain_principal"] = task_data->remain_principal;
		data["due_right_qty"] = task_data->due_right_qty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditDebtInfo(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditTickerDebtInfo(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCrdDebtStockInfo *task_data = (XTPCrdDebtStockInfo*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["stock_repay_quantity"] = task_data->stock_repay_quantity;
		data["stock_total_quantity"] = task_data->stock_total_quantity;
		delete task->task_data;	
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditTickerDebtInfo(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditAssetDebtInfo(Task *task) {
	PyLock lock;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditAssetDebtInfo(task->remain_amount, error, task->task_id, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditTickerAssignInfo(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPClientQueryCrdPositionStkInfo *task_data = (XTPClientQueryCrdPositionStkInfo*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["limit_qty"] = task_data->limit_qty;
		data["yesterday_qty"] = task_data->yesterday_qty;
		data["left_qty"] = task_data->left_qty;
		data["frozen_qty"] = task_data->frozen_qty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditTickerAssignInfo(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditExcessStock(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPClientQueryCrdSurplusStkRspInfo *task_data = (XTPClientQueryCrdSurplusStkRspInfo*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["transferable_quantity"] = task_data->transferable_quantity;
		data["transferred_quantity"] = task_data->transferred_quantity;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditExcessStock(data, error, task->task_id, task->addtional_int);
	delete task;
}


void TraderApi::processQueryMulCreditExcessStock(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPClientQueryCrdSurplusStkRspInfo *task_data = (XTPClientQueryCrdSurplusStkRspInfo*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["transferable_quantity"] = task_data->transferable_quantity;
		data["transferred_quantity"] = task_data->transferred_quantity;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryMulCreditExcessStock(data, error, task->task_id, task->addtional_int, task->task_last);
	delete task;
}

void TraderApi::processCreditExtendDebtDate(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCreditDebtExtendNotice *task_data = (XTPCreditDebtExtendNotice*)task->task_data;
		data["xtpid"] = task_data->xtpid;
		data["debt_id"] = addEndingChar(task_data->debt_id);
		data["oper_status"] = (int)task_data->oper_status;
		data["oper_time"] = task_data->oper_time;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onCreditExtendDebtDate(data, error, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditExtendDebtDateOrders(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCreditDebtExtendNotice *task_data = (XTPCreditDebtExtendNotice*)task->task_data;
		data["xtpid"] = task_data->xtpid;
		data["debt_id"] = addEndingChar(task_data->debt_id);
		data["oper_status"] = (int)task_data->oper_status;
		data["oper_time"] = task_data->oper_time;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditExtendDebtDateOrders(data, error,task->task_id,task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditFundExtraInfo(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCrdFundExtraInfo *task_data = (XTPCrdFundExtraInfo*)task->task_data;
		data["mf_rs_avl_used"] = task_data->mf_rs_avl_used;
		data["security_capital"] = task_data->security_capital;
		data["financing_debts"] = task_data->financing_debts;
		data["short_sell_debts"] = task_data->short_sell_debts;
		data["contract_debts_load"] = task_data->contract_debts_load;
		data["reserve"] = addEndingChar(task_data->reserve);
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditFundExtraInfo(data, error,task->task_id, task->addtional_int);
	delete task;
}

void TraderApi::processQueryCreditPositionExtraInfo(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCrdPositionExtraInfo *task_data = (XTPCrdPositionExtraInfo*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = addEndingChar(task_data->ticker);
		data["mf_rs_avl_used"] = task_data->mf_rs_avl_used;
		data["reserve"] = addEndingChar(task_data->reserve);
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryCreditPositionExtraInfo(data, error,task->task_id,task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processCreditCashRepayDebtInterestFee(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPCrdCashRepayDebtInterestFeeRsp *task_data = (XTPCrdCashRepayDebtInterestFeeRsp*)task->task_data;
		data["xtp_id"] = task_data->xtp_id;
		data["request_amount"] = task_data->request_amount;
		data["cash_repay_amount"] = task_data->cash_repay_amount;
		data["debt_compact_id"] = addEndingChar(task_data->debt_compact_id);
		data["unknow"] = addEndingChar(task_data->unknow);
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onCreditCashRepayDebtInterestFee(data, error, task->addtional_int);
	delete task;
}



void TraderApi::processOptionCombinedOrderEvent(Task *task) {
	PyLock lock;
	dict data;

	if (task->task_data){
		XTPOptCombOrderInfo *task_data = (XTPOptCombOrderInfo*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = task_data->order_local_id;
		data["order_status"] = (int)task_data->order_status;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["order_type"] = task_data->order_type;
		data["strategy_id"] = task_data->opt_comb_info.strategy_id;
		data["comb_num"] = task_data->opt_comb_info.comb_num;
		data["num_legs"] = task_data->opt_comb_info.num_legs;
		boost::python::list leg_detail_list;
		for (int i = 0;i < task_data->opt_comb_info.num_legs; i++) 
		{
			dict leg_detail_dict;
			leg_detail_dict["leg_security_id"] = task_data->opt_comb_info.leg_detail[i].leg_security_id;
			leg_detail_dict["leg_cntr_type"] = (int)task_data->opt_comb_info.leg_detail[i].leg_cntr_type;
			leg_detail_dict["leg_side"] = (int)task_data->opt_comb_info.leg_detail[i].leg_side;
			leg_detail_dict["leg_covered"] = (int)task_data->opt_comb_info.leg_detail[i].leg_covered;
			leg_detail_dict["leg_qty"] = task_data->opt_comb_info.leg_detail[i].leg_qty;
			leg_detail_list.append(leg_detail_dict);
		}
		data["leg_detail"] = leg_detail_list;
	}
	

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onOptionCombinedOrderEvent(data, error,task->addtional_int);
	delete task;
}

void TraderApi::processOptionCombinedTradeEvent(Task *task) {
	PyLock lock;

	dict data;
	if (task->task_data){
		XTPOptCombTradeReport *task_data = (XTPOptCombTradeReport*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["market"] = (int)task_data->market;
		data["local_order_id"] = task_data->local_order_id;
		data["exec_id"] = task_data->exec_id;
		data["quantity"] = task_data->quantity;
		data["trade_time"] = task_data->trade_time;
		data["trade_amount"] = task_data->trade_amount;
		data["report_index"] = task_data->report_index;
		data["order_exch_id"] = task_data->order_exch_id;
		data["trade_type"] = task_data->trade_type;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["branch_pbu"] = task_data->branch_pbu;
		data["strategy_id"] = task_data->opt_comb_info.strategy_id;
		data["comb_num"] = task_data->opt_comb_info.comb_num;
		data["num_legs"] = task_data->opt_comb_info.num_legs;
		boost::python::list leg_detail_list;
		for (int i = 0;i < task_data->opt_comb_info.num_legs; i++) 
		{
			dict leg_detail_dict;
			leg_detail_dict["leg_security_id"] = task_data->opt_comb_info.leg_detail[i].leg_security_id;
			leg_detail_dict["leg_cntr_type"] = (int)task_data->opt_comb_info.leg_detail[i].leg_cntr_type;
			leg_detail_dict["leg_side"] = (int)task_data->opt_comb_info.leg_detail[i].leg_side;
			leg_detail_dict["leg_covered"] = (int)task_data->opt_comb_info.leg_detail[i].leg_covered;
			leg_detail_dict["leg_qty"] = task_data->opt_comb_info.leg_detail[i].leg_qty;
			leg_detail_list.append(leg_detail_dict);
		}
		data["leg_detail"] = leg_detail_list;
	}
	
	this->onOptionCombinedTradeEvent(data,task->addtional_int);
	delete task;
}

void TraderApi::processQueryOptionCombinedOrders(Task *task) {
	PyLock lock;

	dict data;
	if (task->task_data){
		XTPQueryOptCombOrderRsp *task_data = (XTPQueryOptCombOrderRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = task_data->order_local_id;
		data["order_status"] = (int)task_data->order_status;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["order_type"] = task_data->order_type;
		data["strategy_id"] = task_data->opt_comb_info.strategy_id;
		data["comb_num"] = task_data->opt_comb_info.comb_num;
		data["num_legs"] = task_data->opt_comb_info.num_legs;
		boost::python::list leg_detail_list;
		for (int i = 0;i < task_data->opt_comb_info.num_legs; i++) 
		{
			dict leg_detail_dict;
			leg_detail_dict["leg_security_id"] = task_data->opt_comb_info.leg_detail[i].leg_security_id;
			leg_detail_dict["leg_cntr_type"] =(int) task_data->opt_comb_info.leg_detail[i].leg_cntr_type;
			leg_detail_dict["leg_side"] = (int)task_data->opt_comb_info.leg_detail[i].leg_side;
			leg_detail_dict["leg_covered"] = (int)task_data->opt_comb_info.leg_detail[i].leg_covered;
			leg_detail_dict["leg_qty"] = task_data->opt_comb_info.leg_detail[i].leg_qty;
			leg_detail_list.append(leg_detail_dict);
		}
		data["leg_detail"] = leg_detail_list;
	}
	

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryOptionCombinedOrders(data, error, task->task_id, task->task_last,task->addtional_int);
	delete task;
}


void TraderApi::processQueryOptionCombinedOrdersEx(Task *task)
{
	PyLock lock;

	dict data;
	if (task->task_data)
	{
		XTPOptCombOrderInfoEx *task_data = (XTPOptCombOrderInfoEx*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = task_data->order_local_id;
		data["order_status"] = (int)task_data->order_status;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["order_type"] = task_data->order_type;
		data["order_exch_id"] = task_data->order_exch_id;
		data["error_id"] = task_data->order_err_t.error_id;
		data["error_msg"] = addEndingChar(task_data->order_err_t.error_msg);
		data["strategy_id"] = task_data->opt_comb_info.strategy_id;
		data["comb_num"] = task_data->opt_comb_info.comb_num;
		data["num_legs"] = task_data->opt_comb_info.num_legs;
		
		boost::python::list leg_detail_list;
		for (int i = 0; i < task_data->opt_comb_info.num_legs; i++)
		{
			dict leg_detail_dict;
			leg_detail_dict["leg_security_id"] = task_data->opt_comb_info.leg_detail[i].leg_security_id;
			leg_detail_dict["leg_cntr_type"] = (int)task_data->opt_comb_info.leg_detail[i].leg_cntr_type;
			leg_detail_dict["leg_side"] = (int)task_data->opt_comb_info.leg_detail[i].leg_side;
			leg_detail_dict["leg_covered"] = (int)task_data->opt_comb_info.leg_detail[i].leg_covered;
			leg_detail_dict["leg_qty"] = task_data->opt_comb_info.leg_detail[i].leg_qty;
			leg_detail_list.append(leg_detail_dict);
		}
		data["leg_detail"] = leg_detail_list;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}
	this->onQueryOptionCombinedOrdersEx(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processQueryOptionCombinedOrdersByPage(Task *task) {
	PyLock lock;

	dict data;
	if (task->task_data){
		XTPQueryOptCombOrderRsp *task_data = (XTPQueryOptCombOrderRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = task_data->order_local_id;
		data["order_status"] = (int)task_data->order_status;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["order_type"] = task_data->order_type;
		data["strategy_id"] = task_data->opt_comb_info.strategy_id;
		data["comb_num"] = task_data->opt_comb_info.comb_num;
		data["num_legs"] = task_data->opt_comb_info.num_legs;
		boost::python::list leg_detail_list;
		for (int i = 0;i < task_data->opt_comb_info.num_legs; i++) 
		{
			dict leg_detail_dict;
			leg_detail_dict["leg_security_id"] = task_data->opt_comb_info.leg_detail[i].leg_security_id;
			leg_detail_dict["leg_cntr_type"] = (int)task_data->opt_comb_info.leg_detail[i].leg_cntr_type;
			leg_detail_dict["leg_side"] = (int)task_data->opt_comb_info.leg_detail[i].leg_side;
			leg_detail_dict["leg_covered"] = (int)task_data->opt_comb_info.leg_detail[i].leg_covered;
			leg_detail_dict["leg_qty"] = task_data->opt_comb_info.leg_detail[i].leg_qty;
			leg_detail_list.append(leg_detail_dict);
		}
		data["leg_detail"] = leg_detail_list;

	}

	this->onQueryOptionCombinedOrdersByPage(data, task->req_count, task->order_sequence, task->query_reference, task->task_id, task->task_last,task->addtional_int);
	delete task;
}

void TraderApi::processQueryOptionCombinedOrdersByPageEx(Task *task)
{
	PyLock lock;

	dict data;

	if (task->task_data)
	{
		XTPOptCombOrderInfoEx *task_data = (XTPOptCombOrderInfoEx*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = task_data->order_local_id;
		data["order_status"] = (int)task_data->order_status;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["order_type"] = task_data->order_type;
		data["order_exch_id"] = task_data->order_exch_id;
		data["error_id"] = task_data->order_err_t.error_id;
		data["error_msg"] = addEndingChar(task_data->order_err_t.error_msg);
		data["strategy_id"] = task_data->opt_comb_info.strategy_id;
		data["comb_num"] = task_data->opt_comb_info.comb_num;
		data["num_legs"] = task_data->opt_comb_info.num_legs;

		boost::python::list leg_detail_list;
		for (int i = 0; i < task_data->opt_comb_info.num_legs; i++)
		{
			dict leg_detail_dict;
			leg_detail_dict["leg_security_id"] = task_data->opt_comb_info.leg_detail[i].leg_security_id;
			leg_detail_dict["leg_cntr_type"] = (int)task_data->opt_comb_info.leg_detail[i].leg_cntr_type;
			leg_detail_dict["leg_side"] = (int)task_data->opt_comb_info.leg_detail[i].leg_side;
			leg_detail_dict["leg_covered"] = (int)task_data->opt_comb_info.leg_detail[i].leg_covered;
			leg_detail_dict["leg_qty"] = task_data->opt_comb_info.leg_detail[i].leg_qty;
			leg_detail_list.append(leg_detail_dict);
		}
		data["leg_detail"] = leg_detail_list;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryOptionCombinedOrdersByPageEx(data, task->req_count, task->order_sequence, task->query_reference, task->task_id, task->task_last, task->addtional_int);
	delete task;
	
}

void TraderApi::processQueryOptionCombinedTrades(Task *task) {
	PyLock lock;

	dict data;
	if (task->task_data){
		XTPQueryOptCombTradeRsp *task_data = (XTPQueryOptCombTradeRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["market"] = (int)task_data->market;
		data["local_order_id"] = task_data->local_order_id;
		data["exec_id"] = task_data->exec_id;
		data["quantity"] = task_data->quantity;
		data["trade_time"] = task_data->trade_time;
		data["trade_amount"] = task_data->trade_amount;
		data["report_index"] = task_data->report_index;
		data["order_exch_id"] = task_data->order_exch_id;
		data["trade_type"] = task_data->trade_type;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["branch_pbu"] = task_data->branch_pbu;
		data["strategy_id"] = task_data->opt_comb_info.strategy_id;
		data["comb_num"] = task_data->opt_comb_info.comb_num;
		data["num_legs"] = task_data->opt_comb_info.num_legs;
		boost::python::list leg_detail_list;
		for (int i = 0;i < task_data->opt_comb_info.num_legs; i++) 
		{
			dict leg_detail_dict;
			leg_detail_dict["leg_security_id"] = task_data->opt_comb_info.leg_detail[i].leg_security_id;
			leg_detail_dict["leg_cntr_type"] = (int)task_data->opt_comb_info.leg_detail[i].leg_cntr_type;
			leg_detail_dict["leg_side"] = (int)task_data->opt_comb_info.leg_detail[i].leg_side;
			leg_detail_dict["leg_covered"] = (int)task_data->opt_comb_info.leg_detail[i].leg_covered;
			leg_detail_dict["leg_qty"] = task_data->opt_comb_info.leg_detail[i].leg_qty;
			leg_detail_list.append(leg_detail_dict);
		}
		data["leg_detail"] = leg_detail_list;
	}
	


	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryOptionCombinedTrades(data, error, task->task_id, task->task_last,task->addtional_int);
	delete task;
}

void TraderApi::processQueryOptionCombinedTradesByPage(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPQueryOptCombTradeRsp *task_data = (XTPQueryOptCombTradeRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["market"] = (int)task_data->market;
		data["local_order_id"] = task_data->local_order_id;
		data["exec_id"] = task_data->exec_id;
		data["quantity"] = task_data->quantity;
		data["trade_time"] = task_data->trade_time;
		data["trade_amount"] = task_data->trade_amount;
		data["report_index"] = task_data->report_index;
		data["order_exch_id"] = task_data->order_exch_id;
		data["trade_type"] = task_data->trade_type;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["branch_pbu"] = task_data->branch_pbu;
		data["strategy_id"] = task_data->opt_comb_info.strategy_id;
		data["comb_num"] = task_data->opt_comb_info.comb_num;
		data["num_legs"] = task_data->opt_comb_info.num_legs;
		boost::python::list leg_detail_list;
		for (int i = 0;i < task_data->opt_comb_info.num_legs; i++) 
		{
			dict leg_detail_dict;
			leg_detail_dict["leg_security_id"] = task_data->opt_comb_info.leg_detail[i].leg_security_id;
			leg_detail_dict["leg_cntr_type"] = (int)task_data->opt_comb_info.leg_detail[i].leg_cntr_type;
			leg_detail_dict["leg_side"] = (int)task_data->opt_comb_info.leg_detail[i].leg_side;
			leg_detail_dict["leg_covered"] = (int)task_data->opt_comb_info.leg_detail[i].leg_covered;
			leg_detail_dict["leg_qty"] = task_data->opt_comb_info.leg_detail[i].leg_qty;
			leg_detail_list.append(leg_detail_dict);
		}
		data["leg_detail"] = leg_detail_list;
	}
	

	this->onQueryOptionCombinedTradesByPage(data, task->req_count, task->trade_sequence, task->query_reference, task->task_id, task->task_last,task->addtional_int);
	delete task;
}

void TraderApi::processQueryOptionCombinedPosition(Task *task) {
	PyLock lock;

	dict data;
	if (task->task_data){
		XTPQueryOptCombPositionRsp *task_data = (XTPQueryOptCombPositionRsp*)task->task_data;
		data["strategy_id"] = task_data->strategy_id;
		data["strategy_name"] = addEndingChar(task_data->strategy_name);
		data["market"] = (int)task_data->market;
		data["total_qty"] = task_data->total_qty;
		data["available_qty"] = task_data->available_qty;
		data["yesterday_position"] = task_data->yesterday_position;
		data["comb_strategy_id"] = task_data->opt_comb_info.strategy_id;
		data["comb_num"] = task_data->opt_comb_info.comb_num;
		data["num_legs"] = task_data->opt_comb_info.num_legs;
		boost::python::list leg_detail_list;
		for (int i = 0;i < XTP_STRATEGE_LEG_NUM; i++)
		{
			dict leg_detail_dict;
			leg_detail_dict["leg_security_id"] = task_data->opt_comb_info.leg_detail[i].leg_security_id;
			leg_detail_dict["leg_cntr_type"] = (int)task_data->opt_comb_info.leg_detail[i].leg_cntr_type;
			leg_detail_dict["leg_side"] = (int)task_data->opt_comb_info.leg_detail[i].leg_side;
			leg_detail_dict["leg_covered"] = (int)task_data->opt_comb_info.leg_detail[i].leg_covered;
			leg_detail_dict["leg_qty"] = task_data->opt_comb_info.leg_detail[i].leg_qty;
			leg_detail_list.append(leg_detail_dict);
		}
		data["leg_detail"] = leg_detail_list;
		data["secu_comb_margin"] = task_data->secu_comb_margin;
	}


	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryOptionCombinedPosition(data, error, task->task_id, task->task_last,task->addtional_int);
	delete task;
}

void TraderApi::processQueryOptionCombinedStrategyInfo(Task *task) {
	PyLock lock;
	
	dict data;
	if (task->task_data){
		
		XTPQueryCombineStrategyInfoRsp *task_data = (XTPQueryCombineStrategyInfoRsp*)task->task_data;
		//printf("task_data->strategy_id:%s,strategy_name:%s\n",task_data->strategy_id,task_data->strategy_name);
		data["strategy_id"] = addEndingChar(task_data->strategy_id);
		//char strategy_name[64] = {"\0"};
		//printf("sizeof(task_data->strategy_name):%d",sizeof(task_data->strategy_name));
		//strcpy(strategy_name,  task_data->strategy_name);
		//printf("task_data->strategy_name:%s",strategy_name);
		//string strategy_name = addEndingChar(task_data->strategy_name);
		//printf("value:%s\n", task_data->strategy_name);
		//if (string(task_data->strategy_id) == "ZBD")
		//	return;
		
		data["strategy_name"] = addEndingChar(task_data->strategy_name);
		data["market"] = (int)task_data->market;
		data["leg_num"] = task_data->leg_num;
		boost::python::list leg_strategy_list;
		
		for (int i = 0;i < XTP_STRATEGE_LEG_NUM; i++)
		{
			dict leg_strategy_dict;
			leg_strategy_dict["call_or_put"] = (int)task_data->leg_strategy[i].call_or_put;
			leg_strategy_dict["position_side"] = (int)task_data->leg_strategy[i].position_side;
			char price_seq = task_data->leg_strategy[i].exercise_price_seq;
			leg_strategy_dict["exercise_price_seq"] = price_seq;
			leg_strategy_dict["expire_date_seq"] = task_data->leg_strategy[i].expire_date_seq;
			leg_strategy_dict["leg_qty"] = task_data->leg_strategy[i].leg_qty;
			leg_strategy_list.append(leg_strategy_dict);
		}
		
		data["leg_strategy"] = leg_strategy_list;
		data["expire_date_type"] = (int)task_data->expire_date_type;
		data["underlying_type"] = (int)task_data->underlying_type;
		data["auto_sep_type"] = (int)task_data->auto_sep_type;
	}
	

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}
	
	this->onQueryOptionCombinedStrategyInfo(data, error, task->task_id, task->task_last,task->addtional_int);
	delete task;
}


void TraderApi::processCancelOptionCombinedOrderError(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPOptCombOrderCancelInfo *task_data = (XTPOptCombOrderCancelInfo*)task->task_data;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["order_xtp_id"] = task_data->order_xtp_id;
	}
	
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onCancelOptionCombinedOrderError(data, error,task->addtional_int);
	delete task;
}


void TraderApi::processQueryOptionCombinedExecPosition(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPQueryOptCombExecPosRsp *task_data = (XTPQueryOptCombExecPosRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["cntrt_code_1"] = addEndingChar(task_data->cntrt_code_1);
		data["cntrt_name_1"] = addEndingChar(task_data->cntrt_name_1);
		data["position_side_1"] = (int)task_data->position_side_1;
		data["call_or_put_1"] = (int)task_data->call_or_put_1;
		data["avl_qty_1"] = task_data->avl_qty_1;
		data["orig_own_qty_1"] = task_data->orig_own_qty_1;
		data["own_qty_1"] = task_data->own_qty_1;

		data["cntrt_code_2"] = addEndingChar(task_data->cntrt_code_2);
		data["cntrt_name_2"] = addEndingChar(task_data->cntrt_name_2);
		data["position_side_2"] = (int)task_data->position_side_2;
		data["call_or_put_2"] = (int)task_data->call_or_put_2;
		data["avl_qty_2"] = task_data->avl_qty_2;
		data["orig_own_qty_2"] = task_data->orig_own_qty_2;
		data["own_qty_2"] = task_data->own_qty_2;

		data["net_qty"] = task_data->net_qty;
		data["order_qty"] = task_data->order_qty;
		data["confirm_qty"] = task_data->confirm_qty;
		data["avl_qty"] = task_data->avl_qty;
		//data["reserved"] = task_data->reserved;
	}


	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryOptionCombinedExecPosition(data, error,task->task_id, task->task_last,task->addtional_int);
	delete task;
}*/

void TraderApi::processQueryOtherServerFund(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPX::API::XTPFundQueryRsp *task_data = (XTPX::API::XTPFundQueryRsp*)task->task_data;
		data["amount"] = task_data->amount;
		data["query_type"] = (int)task_data->query_type;
		data["query_site"] = (int)task_data->query_site;
		data["currency_type"] = (int)task_data->currency_type;
		data["unused"] = addEndingChar(task_data->unused);
	}


	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPRI *task_error = (XTPX::API::XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onQueryOtherServerFund(data, error,task->task_id,task->addtional_int);
	delete task;
}


//////////algo/////////
/*void TraderApi::processQueryStrategy(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPStrategyInfoStruct *task_data = (XTPStrategyInfoStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_xtp_strategy_id;

	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}
	this->onQueryStrategy(data,task->strategy_param, error,task->task_id,task->task_last,task->addtional_int);
	delete task;
}


void TraderApi::processStrategyStateReport(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPStrategyStateReportStruct *task_data = (XTPStrategyStateReportStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_info.m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_info.m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_strategy_info.m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_strategy_info.m_xtp_strategy_id;

		data["m_strategy_qty"] = task_data->m_strategy_qty;
		data["m_strategy_ordered_qty"] = task_data->m_strategy_ordered_qty;
		data["m_strategy_cancelled_qty"] = task_data->m_strategy_cancelled_qty;
		data["m_strategy_execution_qty"] = task_data->m_strategy_execution_qty;
		data["m_strategy_unclosed_qty"] = task_data->m_strategy_unclosed_qty;
		data["m_strategy_asset"] = task_data->m_strategy_asset;
		data["m_strategy_ordered_asset"] = task_data->m_strategy_ordered_asset;
		data["m_strategy_execution_asset"] = task_data->m_strategy_execution_asset;
		data["m_strategy_execution_price"] = task_data->m_strategy_execution_price;
		data["m_strategy_market_price"] = task_data->m_strategy_market_price;
		data["m_strategy_price_diff"] = task_data->m_strategy_price_diff;
		data["m_strategy_asset_diff"] = task_data->m_strategy_asset_diff;

		data["error_id"] = task_data->m_error_info.error_id;
		data["error_msg"] = addEndingChar(task_data->m_error_info.error_msg);
	}


	this->onStrategyStateReport(data,task->addtional_int);
	delete task;
}

void TraderApi::processALGOUserEstablishChannel(Task *task) {
	PyLock lock;

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onALGOUserEstablishChannel(task->user, error,task->addtional_int);
	delete task;
}

void TraderApi::processInsertAlgoOrder(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPStrategyInfoStruct *task_data = (XTPStrategyInfoStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_xtp_strategy_id;

	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onInsertAlgoOrder(data, error,task->addtional_int);
	delete task;
}

void TraderApi::processCancelAlgoOrder(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPStrategyInfoStruct *task_data = (XTPStrategyInfoStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_xtp_strategy_id;

	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onCancelAlgoOrder(data, error,task->addtional_int);
	delete task;
}

void TraderApi::processAlgoDisconnected(Task *task) {
	PyLock lock;

	this->onAlgoDisconnected(task->reason);
	delete task;
}

void TraderApi::processAlgoConnected(Task *task) {
	PyLock lock;

	this->onAlgoConnected();
	delete task;
}

void TraderApi::processStrategySymbolStateReport(Task *task)
{
	PyLock lock;

	dict data;
	if (task->task_data)
	{
		XTPStrategySymbolStateReport *task_data = (XTPStrategySymbolStateReport*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_info.m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_info.m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_strategy_info.m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_strategy_info.m_xtp_strategy_id;
		data["m_ticker"] = addEndingChar(task_data->m_ticker);
		data["m_market"] = (int)task_data->m_market;
		data["m_side"] = (int)task_data->m_side;
		data["m_strategy_qty"] = task_data->m_strategy_qty;
		data["m_strategy_ordered_qty"] = task_data->m_strategy_ordered_qty;
		data["m_strategy_cancelled_qty"] = task_data->m_strategy_cancelled_qty;
		data["m_strategy_execution_qty"] = task_data->m_strategy_execution_qty;
		data["m_strategy_buy_qty"] = task_data->m_strategy_buy_qty;
		data["m_strategy_sell_qty"] = task_data->m_strategy_sell_qty;
		data["m_strategy_unclosed_qty"] = task_data->m_strategy_unclosed_qty;
		data["m_strategy_asset"] = task_data->m_strategy_asset;
		data["m_strategy_ordered_asset"] = task_data->m_strategy_ordered_asset;
		data["m_strategy_execution_asset"] = task_data->m_strategy_execution_asset;
		data["m_strategy_buy_asset"] = task_data->m_strategy_buy_asset;
		data["m_strategy_sell_asset"] = task_data->m_strategy_sell_asset;
		data["m_strategy_unclosed_asset"] = task_data->m_strategy_unclosed_asset;
		data["m_strategy_asset_diff"] = task_data->m_strategy_asset_diff;
		data["m_strategy_execution_price"] = task_data->m_strategy_execution_price;
		data["m_strategy_market_price"] = task_data->m_strategy_market_price;
		data["m_strategy_price_diff"] = task_data->m_strategy_price_diff;
		data["error_id"] = task_data->m_error_info.error_id;
		data["error_msg"] = addEndingChar(task_data->m_error_info.error_msg);

		delete task->task_data;
	}
	this->onStrategySymbolStateReport(data, task->addtional_int);
	delete task;
}

void TraderApi::processNewStrategyCreateReport(Task *task)
{
	PyLock lock;

	dict data;
	if (task->task_data)
	{
		XTPStrategyInfoStruct *task_data = (XTPStrategyInfoStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_xtp_strategy_id;
	}

	this->onNewStrategyCreateReport(data, task->strategy_param, task->addtional_int);
	delete task;
}

void TraderApi::processStrategyRecommendation(Task *task)
{
	PyLock lock;

	dict data;
	if (task->task_data)
	{
		XTPStrategyRecommendationInfo *task_data = (XTPStrategyRecommendationInfo*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_market"] = (int)task_data->m_market;
		data["m_ticker"] = addEndingChar(task_data->m_ticker);
		data["m_reserved"] = addEndingChar(task_data->m_reserved);
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onStrategyRecommendation(task->addtional_bool, data, task->strategy_param, error, task->task_id,task->task_last, task->addtional_int);
	delete task;
}

void TraderApi::processModifyAlgoOrder(Task *task)
{
	PyLock lock;

	dict data;
	if (task->task_data)
	{
		XTPStrategyInfoStruct *task_data = (XTPStrategyInfoStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_xtp_strategy_id;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onModifyAlgoOrder(data, error, task->addtional_int);
	delete task;
}*/

///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TraderApi::createTraderApi(uint8_t clientid, string path, int log_level)
{
	this->api = XTPX::API::TraderApi::CreateTraderApi(clientid, path.c_str(),(XTPX::API::XTP_LOG_LEVEL)log_level);
	this->api->RegisterSpi(this);
};

void TraderApi::release()
{
	this->api->Release();
};

int TraderApi::exit()
{
	//该函数在原生API里没有，用于安全退出API用，原生的join似乎不太稳定
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

string TraderApi::getTradingDay()
{
	string ret ="";
	const char* p = this->api->GetTradingDay();
	if (p == NULL)
		ret = "NULL";
	else
		ret = p;
	return ret;
};

dict TraderApi::getApiLastError()
{
	dict d;
	XTPX::API::XTPRI *error = this->api->GetApiLastError();
	if(error == NULL)
		return d;

	d["error_id"] = error->error_id;
	d["error_msg"] = addEndingChar(error->error_msg);

	return d;
}

string TraderApi::getApiVersion()
{
	string ret ="";
	const char* p = this->api->GetApiVersion();
	if (p == NULL)
		ret = "NULL";
	else
		ret = p;
	return ret;
}

uint8_t TraderApi::getClientIDByXTPID(uint64_t orderid)
{
	return this->api->GetClientIDByXTPID(orderid);
}

string TraderApi::getAccountByXTPID(uint64_t orderid)
{
	string ret ="";
	const char* p = this->api->GetAccountByXTPID(orderid);
	if (p == NULL)
		ret = "NULL";
	else
		ret = p;
	
	return ret;
}

void TraderApi::subscribePublicTopic(int type)
{
	this->api->SubscribePublicTopic((XTPX::API::XTP_TE_RESUME_TYPE)type);
}

void TraderApi::setSoftwareKey(string key)
{
	this->api->SetSoftwareKey(key.c_str());
}

void TraderApi::setSoftwareVersion(string version)
{
	this->api->SetSoftwareVersion(version.c_str());
}

void TraderApi::setHeartBeatInterval(uint32_t interval)
{
	this->api->SetHeartBeatInterval(interval);
};

uint64_t TraderApi::login(string ip, int port, string user, string password, int socktype,string local_ip)
{
	return this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (XTPX::API::XTP_PROTOCOL_TYPE)socktype,local_ip.c_str());
};

int TraderApi::logout(uint64_t sessionid)
{
	return this->api->Logout(sessionid);
};



uint32_t TraderApi::getAccountTradeMarket(uint64_t session_id)
{
	return this->api->GetAccountTradeMarket(session_id);
}

uint64_t TraderApi::getANewOrderXTPID(uint64_t session_id)
{
	return this->api->GetANewOrderXTPID(session_id);
}

int64_t TraderApi::getMaxReqNumOfPagedQuery(uint64_t session_id)
{
	return this->api->GetMaxReqNumOfPagedQuery(session_id);
}


uint64_t TraderApi::insertOrder(dict req, uint64_t sessionid)
{
	XTPX::API::XTPOrderInsertInfo myreq = XTPX::API::XTPOrderInsertInfo();
	memset(&myreq, 0, sizeof(myreq));
	getDouble(req, "price", &myreq.price);
	getStr(req, "ticker", myreq.ticker);

	getUint32(req, "order_client_id", &myreq.order_client_id);
	getUint64(req, "order_xtp_id", &myreq.order_xtp_id);
	getInt64(req, "quantity", &myreq.quantity);
	getUint16(req, "strategy_type", &myreq.strategy_type);
	getUint64(req, "strategy_id", &myreq.strategy_id);

	getStr(req, "account_id", myreq.account_id);
	getStr(req, "unused", myreq.unused);
	getStr(req, "branch_pbu", myreq.branch_pbu);

	int price_type;
	int side;
	int position_effect;
	
	int market;
	int business_type;
	getInt(req, "price_type", &price_type);
	getInt(req, "side", &side);
	getInt(req, "position_effect", &position_effect);
	
	getInt(req, "market", &market);
	getInt(req, "business_type", &business_type);
	myreq.price_type = (XTPX::API::XTP_PRICE_TYPE)price_type;
	myreq.side = (XTPX::API::XTP_SIDE_TYPE)side;
	myreq.position_effect = (XTPX::API::XTP_POSITION_EFFECT_TYPE)position_effect;
	myreq.market = (XTPX::API::XTP_MARKET_TYPE)market;
	myreq.business_type = (XTPX::API::XTP_BUSINESS_TYPE)business_type;

	return this->api->InsertOrder(&myreq, sessionid);
};

uint64_t TraderApi::insertOrderExtra(dict req, uint64_t session_id)
{
	XTPX::API::XTPOrderInsertInfo myreq = XTPX::API::XTPOrderInsertInfo();
	memset(&myreq, 0, sizeof(myreq));
	getDouble(req, "price", &myreq.price);
	getStr(req, "ticker", myreq.ticker);

	getUint32(req, "order_client_id", &myreq.order_client_id);
	getUint64(req, "order_xtp_id", &myreq.order_xtp_id);
	getInt64(req, "quantity", &myreq.quantity);
	getUint16(req, "strategy_type", &myreq.strategy_type);
	getUint64(req, "strategy_id", &myreq.strategy_id);

	getStr(req, "account_id", myreq.account_id);
	getStr(req, "unused", myreq.unused);
	getStr(req, "branch_pbu", myreq.branch_pbu);

	int price_type;
	int side;
	int position_effect;
	int reserved1;
	int reserved2;
	int market;
	int business_type;
	getInt(req, "price_type", &price_type);
	getInt(req, "side", &side);
	getInt(req, "position_effect", &position_effect);
	getInt(req, "reserved1", &reserved1);
	getInt(req, "reserved2", &reserved2);
	getInt(req, "market", &market);
	getInt(req, "business_type", &business_type);
	myreq.price_type = (XTPX::API::XTP_PRICE_TYPE)price_type;
	myreq.side = (XTPX::API::XTP_SIDE_TYPE)side;
	myreq.position_effect = (XTPX::API::XTP_POSITION_EFFECT_TYPE)position_effect;
	myreq.market = (XTPX::API::XTP_MARKET_TYPE)market;
	myreq.business_type = (XTPX::API::XTP_BUSINESS_TYPE)business_type;

	return this->api->InsertOrderExtra(&myreq, session_id);
}

uint64_t TraderApi::cancelOrder(uint64_t orderid, uint64_t sessionid)
{
	return this->api->CancelOrder(orderid, sessionid);
}

int TraderApi::queryOrderByXTPID(uint64_t orderid, uint64_t sessionid, int reqid)
{
	return this->api->QueryOrderByXTPID(orderid, sessionid, reqid);
};


int TraderApi::queryOrders(dict req, uint64_t sessionid, int reqid)
{
	XTPX::API::XTPQueryOrderReq myreq = XTPX::API::XTPQueryOrderReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);
	getInt64(req, "end_time", &myreq.end_time);
	getInt64(req, "begin_time", &myreq.begin_time);
	return this->api->QueryOrders(&myreq, sessionid, reqid);
};


int TraderApi::queryUnfinishedOrders(uint64_t sessionid, int reqid)
{
	return this->api->QueryUnfinishedOrders(sessionid, reqid);
};

int TraderApi::queryOrdersByPage(dict req, uint64_t sessionid, int reqid)
{
	XTPX::API::XTPQueryOrderByPageReq myreq = XTPX::API::XTPQueryOrderByPageReq();
	memset(&myreq, 0, sizeof(myreq));
	getInt64(req, "req_count", &myreq.req_count);
	getInt64(req, "reference", &myreq.reference);
	getInt64(req, "reserved", &myreq.reserved);
	return this->api->QueryOrdersByPage(&myreq, sessionid, reqid);
};


int TraderApi::queryTradesByXTPID(uint64_t orderid, uint64_t sessionid, int reqid)
{
	return this->api->QueryTradesByXTPID(orderid, sessionid, reqid);
};

int TraderApi::queryTrades(dict req, uint64_t sessionid, int reqid)
{
	XTPX::API::XTPQueryTraderReq myreq = XTPX::API::XTPQueryTraderReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);
	getInt64(req, "end_time", &myreq.end_time);
	getInt64(req, "begin_time", &myreq.begin_time);
	return this->api->QueryTrades(&myreq, sessionid, reqid);
};

int TraderApi::queryTradesByPage(dict req, uint64_t sessionid, int reqid)
{
	XTPX::API::XTPQueryTraderByPageReq myreq = XTPX::API::XTPQueryTraderByPageReq();
	memset(&myreq, 0, sizeof(myreq));
	getInt64(req, "req_count", &myreq.req_count);
	getInt64(req, "reference", &myreq.reference);
	getInt64(req, "reserved", &myreq.reserved);
	return this->api->QueryTradesByPage(&myreq, sessionid, reqid);
};

int TraderApi::queryPosition(string ticker, uint64_t sessionid, int reqid, int market)
{
	return this->api->QueryPosition(ticker.c_str(), sessionid, reqid, (XTPX::API::XTP_MARKET_TYPE)market);
};

int TraderApi::queryAllPosition(dict req, uint64_t session_id, int request_id)
{
	XTPX::API::XTPQueryStkPositionReq myreq = XTPX::API::XTPQueryStkPositionReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);
	getStr(req, "account_id", myreq.account_id);
	getStr(req, "unused", myreq.unused);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTPX::API::XTP_MARKET_TYPE)market;
	return this->api->QueryAllPosition(&myreq, session_id, request_id);
}

int TraderApi::querySecurityAccount(uint64_t session_id, int request_id)
{
	return this->api->QuerySecurityAccount(session_id, request_id);
}

int TraderApi::queryAsset(uint64_t sessionid, int reqid)
{
	return this->api->QueryAsset(sessionid, reqid);
};


uint64_t TraderApi::fundTransfer(dict req, uint64_t sessionid)
{
	XTPX::API::XTPFundTransferReq myreq = XTPX::API::XTPFundTransferReq();
	memset(&myreq, 0, sizeof(myreq));
	getUint64(req, "serial_id", &myreq.serial_id);
	getStr(req, "fund_account", myreq.fund_account);
	getStr(req, "unused", myreq.unused);
	getDouble(req, "amount", &myreq.amount);

	int transfer_type;
	int site;
	int currency_type;
	getInt(req, "transfer_type", &transfer_type);
	getInt(req, "site", &site);
	getInt(req, "currency_type", &currency_type);
	myreq.transfer_type = (XTPX::API::XTP_FUND_TRANSFER_TYPE)transfer_type;
	myreq.site = (XTPX::API::XTP_TRANSFER_SITE_TYPE)site;
	myreq.currency_type = (XTPX::API::XTP_CURRENCY_TYPE)currency_type;

	return this->api->FundTransfer(&myreq, sessionid);
};

int TraderApi::queryFundTransferByID(uint64_t serial_id, uint64_t session_id, int request_id)
{
	return this->api->QueryFundTransferByID(serial_id, session_id, request_id);
};

int TraderApi::queryFundTransferByPage(dict req, uint64_t session_id, int request_id)
{
	XTPX::API::XTPQueryFundTransferByPageReq myreq = XTPX::API::XTPQueryFundTransferByPageReq();
	getInt64(req, "req_count", &myreq.req_count);
	getInt64(req, "reference", &myreq.reference);
	getInt64(req, "reserved", &myreq.reserved);

	return this->api->QueryFundTransferByPage(&myreq, session_id, request_id);
}

int TraderApi::queryOtherServerFund(dict req, uint64_t session_id, int request_id) {
	XTPX::API::XTPFundQueryReq query_param;
	memset(&query_param, 0, sizeof(query_param));
	string account;
	getChar(req, "fund_account", account);
	strncpy(query_param.fund_account, account.c_str(), XTPX::API::XTP_ACCOUNT_NAME_LEN);
	//strcpy(query_param.fund_account, account.c_str());
	//strcpy(query_param.password, password.c_str());
	int query_type;
	int query_site;
	int currency_type;
	getInt(req, "query_type", &query_type);
	getInt(req, "query_site", &query_site);
	getInt(req, "currency_type", &currency_type);
	query_param.query_type = (XTPX::API::XTP_FUND_QUERY_TYPE)query_type;
	query_param.query_site = (XTPX::API::XTP_TRANSFER_SITE_TYPE)query_site;
	query_param.currency_type = (XTPX::API::XTP_CURRENCY_TYPE)currency_type;
	getStr(req, "unused", query_param.unused);
	return this->api->QueryOtherServerFund(&query_param, session_id, request_id);
}


int TraderApi::queryETF(dict req, uint64_t sessionid, int reqid)
{
	XTPX::API::XTPQueryETFBaseReq myreq = XTPX::API::XTPQueryETFBaseReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);
	getStr(req, "unused", myreq.unused);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTPX::API::XTP_MARKET_TYPE)market;

	return this->api->QueryETF(&myreq, sessionid, reqid);
};

int TraderApi::queryETFTickerBasket(dict req, uint64_t sessionid, int reqid)
{
	XTPX::API::XTPQueryETFComponentReq myreq = XTPX::API::XTPQueryETFComponentReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);
	getStr(req, "unused", myreq.unused);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTPX::API::XTP_MARKET_TYPE)market;

	return this->api->QueryETFTickerBasket(&myreq, sessionid, reqid);
};

int TraderApi::queryIPOInfoList(uint64_t sessionid, int reqid)
{
	return this->api->QueryIPOInfoList(sessionid, reqid);
};

int TraderApi::queryIPOQuotaInfo(uint64_t sessionid, int reqid)
{
	return this->api->QueryIPOQuotaInfo(sessionid, reqid);
};

int TraderApi::queryBondIPOInfoList(uint64_t sessionid, int reqid)
{
	return this->api->QueryBondIPOInfoList(sessionid, reqid);
};

int TraderApi::queryBondSwapStockInfo(dict req, uint64_t sessionid, int reqid)
{
	XTPX::API::XTPQueryBondSwapStockReq myreq = XTPX::API::XTPQueryBondSwapStockReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);
	getStr(req, "unused", myreq.unused);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTPX::API::XTP_MARKET_TYPE)market;
	return this->api->QueryBondSwapStockInfo(&myreq, sessionid, reqid);
};

/*int TraderApi::queryOptionAuctionInfo(dict req,uint64_t sessionid, int reqid)
{
	XTPQueryOptionAuctionInfoReq myreq = XTPQueryOptionAuctionInfoReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;
	return this->api->QueryOptionAuctionInfo(&myreq,sessionid, reqid);
};

uint64_t TraderApi::creditCashRepay(double remain_amount, uint64_t session_id = 0) {
	return this->api->CreditCashRepay(remain_amount, session_id);
}

int TraderApi::queryCreditCashRepayInfo(uint64_t session_id, int request_id) {

	return this->api->QueryCreditCashRepayInfo(session_id, request_id);
}

int TraderApi::queryCreditFundInfo(uint64_t session_id, int request_id) {
	return this->api->QueryCreditFundInfo(session_id, request_id);
}

int TraderApi::queryCreditDebtInfo(uint64_t session_id, int request_id) {
	return this->api->QueryCreditDebtInfo(session_id, request_id);
}

int TraderApi::queryCreditTickerDebtInfo(dict req, uint64_t session_id, int request_id) {
	XTPClientQueryCrdDebtStockReq myreq = XTPClientQueryCrdDebtStockReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;
	return this->api->QueryCreditTickerDebtInfo(&myreq, session_id, request_id);
}

int TraderApi::queryCreditAssetDebtInfo(uint64_t session_id, int request_id) {
	return this->api->QueryCreditAssetDebtInfo(session_id, request_id);
}

int TraderApi::queryCreditTickerAssignInfo(dict req, uint64_t session_id, int request_id) {
	XTPClientQueryCrdPositionStockReq myreq = XTPClientQueryCrdPositionStockReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;
	return this->api->QueryCreditTickerAssignInfo(&myreq, session_id, request_id);
}

int TraderApi::queryCreditExcessStock(dict req, uint64_t session_id, int request_id) {
	XTPClientQueryCrdSurplusStkReqInfo myreq = XTPClientQueryCrdSurplusStkReqInfo();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;
	return this->api->QueryCreditExcessStock(&myreq, session_id, request_id);
}

int TraderApi::queryMulCreditExcessStock(dict req, uint64_t session_id, int request_id) {
	XTPClientQueryCrdSurplusStkReqInfo myreq = XTPClientQueryCrdSurplusStkReqInfo();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;
	return this->api->QueryMulCreditExcessStock(&myreq, session_id, request_id);
}

uint64_t TraderApi::creditExtendDebtDate(dict req,uint64_t session_id) {
	XTPCreditDebtExtendReq myreq = XTPCreditDebtExtendReq();
	memset(&myreq, 0, sizeof(myreq));
	getUint64(req, "xtpid", &myreq.xtpid);
	getStr(req, "debt_id", myreq.debt_id);
	getUint32(req, "xtpid", &myreq.defer_days);
	getStr(req, "fund_account", myreq.fund_account);
	getStr(req, "password", myreq.password);

	return this->api->CreditExtendDebtDate(&myreq, session_id);
}

int TraderApi::queryCreditExtendDebtDateOrders(uint64_t xtp_id, uint64_t session_id, int request_id) {

	return this->api->QueryCreditExtendDebtDateOrders(xtp_id, session_id, request_id);
}

int TraderApi::queryCreditFundExtraInfo(uint64_t session_id, int request_id) {

	return this->api->QueryCreditFundExtraInfo(session_id, request_id);
}

int TraderApi::queryCreditPositionExtraInfo(dict req, uint64_t session_id, int request_id) {

	XTPClientQueryCrdPositionStockReq myreq = XTPClientQueryCrdPositionStockReq();
	memset(&myreq, 0, sizeof(myreq));

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;
	getStr(req, "ticker", myreq.ticker);

	return this->api->QueryCreditPositionExtraInfo(&myreq, session_id, request_id);
}



uint64_t TraderApi::creditCashRepayDebtInterestFee(string debt_id, double amount, uint64_t session_id) {
	return this->api->CreditCashRepayDebtInterestFee(debt_id.c_str(),amount, session_id);
}

uint64_t TraderApi::creditSellStockRepayDebtInterestFee(dict req, string debt_id, uint64_t session_id) {
	XTPOrderInsertInfo myreq = XTPOrderInsertInfo();
	memset(&myreq, 0, sizeof(myreq));
	getDouble(req, "stop_price", &myreq.stop_price);
	getDouble(req, "price", &myreq.price);
	getStr(req, "ticker", myreq.ticker);

	getUint32(req, "order_client_id", &myreq.order_client_id);
	getUint64(req, "order_xtp_id", &myreq.order_xtp_id);
	getInt64(req, "quantity", &myreq.quantity);

	int price_type;
	int side;
	int position_effect;
	int reserved1;
	int reserved2;
	int market;
	int business_type;
	getInt(req, "price_type", &price_type);
	getInt(req, "side", &side);
	getInt(req, "position_effect", &position_effect);
	getInt(req, "reserved1", &reserved1);
	getInt(req, "reserved2", &reserved2);
	getInt(req, "market", &market);
	getInt(req, "business_type", &business_type);
	myreq.price_type = (XTP_PRICE_TYPE)price_type;
	myreq.side = (XTP_SIDE_TYPE)side;
	myreq.position_effect = (XTP_POSITION_EFFECT_TYPE)position_effect;
	myreq.reserved1 = reserved1;
	myreq.reserved2 = reserved2;
	myreq.market = (XTP_MARKET_TYPE)market;
	myreq.business_type = (XTP_BUSINESS_TYPE)business_type;

	return this->api->CreditSellStockRepayDebtInterestFee(&myreq,debt_id.c_str(),session_id);
}


uint64_t TraderApi::insertOptionCombinedOrder(dict req, uint64_t session_id) {

	XTPOptCombOrderInsertInfo query_param;
	memset(&query_param, 0, sizeof(query_param));

	getUint64(req, "order_xtp_id", &query_param.order_xtp_id);
	getUint32(req, "order_client_id", &query_param.order_client_id);

	int side;
	int market;
	int business_type;
	dict opt_comb_info; 

	getInt(req, "side", &side);
	getInt(req, "market", &market);
	getInt(req, "business_type", &business_type);
	query_param.side = (XTP_SIDE_TYPE)side;
	query_param.market = (XTP_MARKET_TYPE)market;
	query_param.business_type = (XTP_BUSINESS_TYPE)business_type;

	getNestedDictChar(req, "opt_comb_info", "strategy_id", query_param.opt_comb_info.strategy_id);
	getNestedDictChar(req, "opt_comb_info", "comb_num", query_param.opt_comb_info.comb_num);
	getNestedDictValue(req, "opt_comb_info", "num_legs", &query_param.opt_comb_info.num_legs);

	int leg_cntr_type;
	int leg_side;
	int leg_covered;
	for (int i = 0; i< query_param.opt_comb_info.num_legs; i++)
	{
		getNestedDictChar2(req, "opt_comb_info", "leg_detail", "leg_security_id", query_param.opt_comb_info.leg_detail[i].leg_security_id, i);
		getNestedDictValue2(req, "opt_comb_info", "leg_detail", "leg_cntr_type", &leg_cntr_type, i);
		getNestedDictValue2(req, "opt_comb_info", "leg_detail", "leg_side", &leg_side, i);
		getNestedDictValue2(req, "opt_comb_info", "leg_detail", "leg_covered", &leg_covered, i);
		getNestedDictValue2(req, "opt_comb_info", "leg_detail", "leg_qty", &query_param.opt_comb_info.leg_detail[i].leg_qty, i);
		query_param.opt_comb_info.leg_detail[i].leg_cntr_type = (XTP_OPT_CALL_OR_PUT_TYPE)leg_cntr_type;
		query_param.opt_comb_info.leg_detail[i].leg_side = (XTP_POSITION_DIRECTION_TYPE)leg_side;
		query_param.opt_comb_info.leg_detail[i].leg_covered = (XTP_OPT_COVERED_OR_UNCOVERED)leg_covered;

	}

	getInt64(req, "quantity", &query_param.quantity);
	return this->api->InsertOptionCombinedOrder(&query_param, session_id);
}

uint64_t TraderApi::insertOptionCombinedOrderExtra(dict req, uint64_t session_id)
{
	XTPOptCombOrderInsertInfo query_param;
	memset(&query_param, 0, sizeof(query_param));

	getUint64(req, "order_xtp_id", &query_param.order_xtp_id);
	getUint32(req, "order_client_id", &query_param.order_client_id);

	int side;
	int market;
	int business_type;
	dict opt_comb_info;

	getInt(req, "side", &side);
	getInt(req, "market", &market);
	getInt(req, "business_type", &business_type);
	query_param.side = (XTP_SIDE_TYPE)side;
	query_param.market = (XTP_MARKET_TYPE)market;
	query_param.business_type = (XTP_BUSINESS_TYPE)business_type;

	getNestedDictChar(req, "opt_comb_info", "strategy_id", query_param.opt_comb_info.strategy_id);
	getNestedDictChar(req, "opt_comb_info", "comb_num", query_param.opt_comb_info.comb_num);
	getNestedDictValue(req, "opt_comb_info", "num_legs", &query_param.opt_comb_info.num_legs);

	int leg_cntr_type;
	int leg_side;
	int leg_covered;
	for (int i = 0; i< query_param.opt_comb_info.num_legs; i++)
	{
		getNestedDictChar2(req, "opt_comb_info", "leg_detail", "leg_security_id", query_param.opt_comb_info.leg_detail[i].leg_security_id, i);
		getNestedDictValue2(req, "opt_comb_info", "leg_detail", "leg_cntr_type", &leg_cntr_type, i);
		getNestedDictValue2(req, "opt_comb_info", "leg_detail", "leg_side", &leg_side, i);
		getNestedDictValue2(req, "opt_comb_info", "leg_detail", "leg_covered", &leg_covered, i);
		getNestedDictValue2(req, "opt_comb_info", "leg_detail", "leg_qty", &query_param.opt_comb_info.leg_detail[i].leg_qty, i);
		query_param.opt_comb_info.leg_detail[i].leg_cntr_type = (XTP_OPT_CALL_OR_PUT_TYPE)leg_cntr_type;
		query_param.opt_comb_info.leg_detail[i].leg_side = (XTP_POSITION_DIRECTION_TYPE)leg_side;
		query_param.opt_comb_info.leg_detail[i].leg_covered = (XTP_OPT_COVERED_OR_UNCOVERED)leg_covered;

	}

	getInt64(req, "quantity", &query_param.quantity);
	return this->api->InsertOptionCombinedOrderExtra(&query_param, session_id);
}

int TraderApi::queryOptionCombinedUnfinishedOrders(uint64_t session_id, int request_id) {

	return this->api->QueryOptionCombinedUnfinishedOrders(session_id, request_id);
}

int TraderApi::queryOptionCombinedUnfinishedOrdersEx(uint64_t session_id, int request_id)
{
	return this->api->QueryOptionCombinedUnfinishedOrdersEx(session_id, request_id);
}

int TraderApi::queryOptionCombinedOrderByXTPID(const uint64_t order_xtp_id, uint64_t session_id, int request_id) {

	return this->api->QueryOptionCombinedOrderByXTPID(order_xtp_id, session_id, request_id);
}

int TraderApi::queryOptionCombinedOrderByXTPIDEx(const uint64_t order_xtp_id, uint64_t session_id, int request_id)
{
	return this->api->QueryOptionCombinedOrderByXTPIDEx(order_xtp_id, session_id, request_id);
}

int TraderApi::queryOptionCombinedOrders(dict req, uint64_t session_id, int request_id) {

	XTPQueryOptCombOrderReq query_param;
	memset(&query_param, 0, sizeof(query_param));

	getStr(req, "comb_num", query_param.comb_num);
	getInt64(req, "begin_time", &query_param.begin_time);
	getInt64(req, "end_time", &query_param.end_time);
	return this->api->QueryOptionCombinedOrders(&query_param, session_id, request_id);
}

int TraderApi::queryOptionCombinedOrdersEx(dict req, uint64_t session_id, int request_id)
{
	XTPQueryOptCombOrderReq query_param;
	memset(&query_param, 0, sizeof(query_param));

	getStr(req, "comb_num", query_param.comb_num);
	getInt64(req, "begin_time", &query_param.begin_time);
	getInt64(req, "end_time", &query_param.end_time);
	return this->api->QueryOptionCombinedOrdersEx(&query_param, session_id, request_id);
}

int TraderApi::queryOptionCombinedOrdersByPage(dict req, uint64_t session_id, int request_id) {

	XTPQueryOptCombOrderByPageReq query_param;
	memset(&query_param, 0, sizeof(query_param));

	getInt64(req, "req_count", &query_param.req_count);
	getInt64(req, "reference", &query_param.reference);
	getInt64(req, "reserved", &query_param.reserved);
	return this->api->QueryOptionCombinedOrdersByPage(&query_param, session_id, request_id);
}

int TraderApi::queryOptionCombinedOrdersByPageEx(dict req, uint64_t session_id, int request_id)
{
	XTPQueryOptCombOrderByPageReq query_param;
	memset(&query_param, 0, sizeof(query_param));

	getInt64(req, "req_count", &query_param.req_count);
	getInt64(req, "reference", &query_param.reference);
	getInt64(req, "reserved", &query_param.reserved);
	return this->api->QueryOptionCombinedOrdersByPageEx(&query_param, session_id, request_id);
}

int TraderApi::queryOptionCombinedTradesByXTPID(const uint64_t order_xtp_id, uint64_t session_id, int request_id) {

	return this->api->QueryOptionCombinedTradesByXTPID(order_xtp_id, session_id, request_id);
}

int TraderApi::queryOptionCombinedTrades(dict req, uint64_t session_id, int request_id) {

	XTPQueryOptCombTraderReq query_param;
	memset(&query_param, 0, sizeof(query_param));

	getStr(req, "comb_num", query_param.comb_num);
	getInt64(req, "begin_time", &query_param.begin_time);
	getInt64(req, "end_time", &query_param.end_time);
	return this->api->QueryOptionCombinedTrades(&query_param, session_id, request_id);
}

int TraderApi::queryOptionCombinedTradesByPage(dict req, uint64_t session_id, int request_id) {

	XTPQueryOptCombTraderByPageReq query_param;
	memset(&query_param, 0, sizeof(query_param));

	getInt64(req, "req_count", &query_param.req_count);
	getInt64(req, "reference", &query_param.reference);
	getInt64(req, "reserved", &query_param.reserved);
	return this->api->QueryOptionCombinedTradesByPage(&query_param, session_id, request_id);
}

int TraderApi::queryOptionCombinedPosition(dict req, uint64_t session_id, int request_id) {

	XTPQueryOptCombPositionReq query_param;
	memset(&query_param, 0, sizeof(query_param));

	int market;
	getStr(req, "comb_num", query_param.comb_num);
	getInt(req, "market", &market);
	query_param.market = (XTP_MARKET_TYPE)market;

	//getValue(req, "market", &query_param.market);
	return this->api->QueryOptionCombinedPosition(&query_param, session_id, request_id);
}

int TraderApi::queryOptionCombinedStrategyInfo(uint64_t session_id, int request_id) {
	//getValue(req, "market", &query_param.market);
	return this->api->QueryOptionCombinedStrategyInfo(session_id, request_id);
}

uint64_t TraderApi::cancelOptionCombinedOrder(const uint64_t order_xtp_id, uint64_t session_id = 0) {
	return this->api->CancelOptionCombinedOrder(order_xtp_id, session_id);
}

int TraderApi::queryOptionCombinedExecPosition(dict req,uint64_t session_id, int request_id) {
	XTPQueryOptCombExecPosReq query_param;
	memset(&query_param, 0, sizeof(query_param));

	int market;
	getInt(req, "market", &market);
	query_param.market = (XTP_MARKET_TYPE)market;
	getStr(req, "cntrt_code_1", query_param.cntrt_code_1);
	getStr(req, "cntrt_code_2", query_param.cntrt_code_2);
	return this->api->QueryOptionCombinedExecPosition(&query_param,session_id, request_id);
}




////////////////////algo//////////////////

int TraderApi::loginALGO(string ip, int port, string user, string password, int socktype,string local_ip)
{
	return this->api->LoginALGO(ip.c_str(), port, user.c_str(), password.c_str(), (XTP_PROTOCOL_TYPE)socktype,local_ip.c_str());
};

int TraderApi::queryStrategy(uint32_t strategy_type, uint64_t client_strategy_id, uint64_t xtp_strategy_id, uint64_t session_id, int32_t request_id)
{
	return this->api->QueryStrategy(strategy_type, client_strategy_id,xtp_strategy_id, session_id, request_id);
};

int TraderApi::aLGOUserEstablishChannel(string oms_ip, int oms_port, string user, string password, uint64_t session_id)
{
	return this->api->ALGOUserEstablishChannel(oms_ip.c_str(), oms_port, user.c_str(), password.c_str(), session_id);
};

int TraderApi::insertAlgoOrder(uint32_t strategy_type, uint64_t client_strategy_id, string strategy_param, uint64_t session_id)
{
	return this->api->InsertAlgoOrder(strategy_type, client_strategy_id, (char*)strategy_param.c_str(), session_id);
};

int TraderApi::cancelAlgoOrder(bool cancel_flag, uint64_t xtp_strategy_id, uint64_t session_id)
{
	return this->api->CancelAlgoOrder(cancel_flag, xtp_strategy_id, session_id);
};

uint64_t TraderApi::getAlgorithmIDByOrder(uint64_t order_xtp_id, uint32_t order_client_id)
{
	return this->api->GetAlgorithmIDByOrder(order_xtp_id, order_client_id);
};

int TraderApi::strategyRecommendation(bool basket_flag, char* basket_param, uint64_t session_id, int32_t request_id)
{
	return this->api->StrategyRecommendation(basket_flag, basket_param, session_id, request_id);
};

int TraderApi::modifyAlgoOrder(uint64_t xtp_strategy_id, char* strategy_param, uint64_t session_id)
{
	return this->api->ModifyAlgoOrder(xtp_strategy_id, strategy_param, session_id);
};*/

///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct TraderApiWrap : TraderApi, wrapper < TraderApi >
{
	virtual void onDisconnected(uint64_t session, int reason)
	{
		try
		{
			this->get_override("onDisconnected")(session, reason);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onServerStatusNotification(uint64_t session, uint32_t server_type, bool status)
	{
		try
		{
			this->get_override("onServerStatusNotification")(session, server_type, status);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onError(dict data)
	{
		try
		{
			this->get_override("onError")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onConnect(uint64_t session, string user)
	{
		try
		{
			this->get_override("onConnect")(session, user);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onResumeEnd(uint64_t session)
	{
		try
		{
			this->get_override("onResumeEnd")(session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onUnknownOrder(uint64_t order_xtp_id, uint64_t session)
	{
		try
		{
			this->get_override("onUnknownOrder")(order_xtp_id, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onOrderAck(dict data, uint64_t session)
	{
		try
		{
			this->get_override("onOrderAck")(data, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};


	virtual void onOrderEvent(dict data, dict error, uint64_t session)
	{
		try
		{
			this->get_override("onOrderEvent")(data, error, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onTradeEvent(dict data, uint64_t session)
	{
		try
		{
			this->get_override("onTradeEvent")(data, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onCancelOrderError(dict data, dict error, uint64_t session)
	{
		try
		{
			this->get_override("onCancelOrderError")(data, error, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryOrder(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryOrder")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryOrderByPage(dict data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryOrderByPage")(data,req_count,order_sequence, query_reference, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};


	virtual void onQueryTrade(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryTrade")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryTradeByPage(dict data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryTradeByPage")(data, req_count,trade_sequence,query_reference, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryPosition(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryPosition")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQuerySecurityAccount(dict data, dict error, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQuerySecurityAccount")(data, error, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryAsset(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryAsset")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};


	virtual void onQueryFundTransfer(dict data, dict fund_transfer_err_info, dict error, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryFundTransfer")(data, fund_transfer_err_info, error, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryFundTransferByPage(dict data, dict fund_transfer_err_info, dict error, int64_t req_count, int64_t sequence, int64_t query_reference, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryFundTransferByPage")(data, fund_transfer_err_info, error, req_count, sequence, query_reference, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onFundTransfer(dict data, dict error, uint64_t session)
	{
		try
		{
			this->get_override("onFundTransfer")(data, error, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryOtherServerFund(dict data, dict error_info, int request_id, uint64_t session) {
		PyLock lock;
		printf("onQueryOtherServerFund--");
		try {
			this->get_override("onQueryOtherServerFund")(data, error_info, request_id, session);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onUnknownFundTransfer(uint64_t serial_id, uint64_t session)
	{
		try
		{
			this->get_override("onUnknownFundTransfer")(serial_id, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryETF(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryETF")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryETFBasket(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryETFBasket")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryIPOInfoList(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryIPOInfoList")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryIPOQuotaInfo(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryIPOQuotaInfo")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryBondIPOInfoList(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryBondIPOInfoList")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryBondSwapStockInfo(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryBondSwapStockInfo")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	/*virtual void onQueryOptionAuctionInfo(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryOptionAuctionInfo")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onCreditCashRepay(dict data, dict error_info, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onCreditCashRepay")(data, error_info, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditCashRepayInfo(dict data, dict error_info, int request_id, bool is_last, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditCashRepayInfo")(data, error_info, request_id, is_last, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditFundInfo(dict data, dict error_info, int request_id, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditFundInfo")(data, error_info, request_id, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditDebtInfo(dict data, dict error_info, int request_id, bool is_last, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditDebtInfo")(data, error_info, request_id, is_last, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditTickerDebtInfo(dict data, dict error_info, int request_id, bool is_last, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditTickerDebtInfo")(data, error_info, request_id, is_last, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditAssetDebtInfo(double remain_amount, dict error_info, int request_id, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditAssetDebtInfo")(remain_amount, error_info, request_id, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditTickerAssignInfo(dict data, dict error_info, int request_id, bool is_last, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditTickerAssignInfo")(data, error_info, request_id, is_last, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditExcessStock(dict data, dict error_info, int request_id, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditExcessStock")(data, error_info, request_id, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryMulCreditExcessStock(dict data, dict error_info, int request_id, uint64_t session, bool is_last) {
		PyLock lock;

		try {
			this->get_override("onQueryMulCreditExcessStock")(data, error_info, request_id, session,is_last);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onCreditExtendDebtDate(dict data, dict error_info, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onCreditExtendDebtDate")(data, error_info, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditExtendDebtDateOrders(dict data, dict error_info, int request_id, bool is_last, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditExtendDebtDateOrders")(data, error_info, request_id,is_last, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditFundExtraInfo(dict data, dict error_info, int request_id, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditFundExtraInfo")(data, error_info, request_id, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryCreditPositionExtraInfo(dict data, dict error_info, int request_id, bool is_last, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryCreditPositionExtraInfo")(data, error_info, request_id,is_last, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onCreditCashRepayDebtInterestFee(dict data, dict error_info, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onCreditCashRepayDebtInterestFee")(data, error_info, session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onOptionCombinedOrderEvent(dict data, dict error_info, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onOptionCombinedOrderEvent")(data, error_info, session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onOptionCombinedTradeEvent(dict data, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onOptionCombinedTradeEvent")(data,session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryOptionCombinedOrders(dict data, dict error_info, int request_id, bool is_last, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onQueryOptionCombinedOrders")(data, error_info, request_id, is_last, session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryOptionCombinedOrdersEx(dict data, dict error_info, int request_id, bool is_last, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onQueryOptionCombinedOrdersEx")(data, error_info, request_id, is_last, session_id);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryOptionCombinedOrdersByPage(dict data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onQueryOptionCombinedOrdersByPage")(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryOptionCombinedOrdersByPageEx(dict data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onQueryOptionCombinedOrdersByPageEx")(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryOptionCombinedTrades(dict data, dict error_info, int request_id, bool is_last, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onQueryOptionCombinedTrades")(data, error_info, request_id, is_last,session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryOptionCombinedTradesByPage(dict data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onQueryOptionCombinedTradesByPage")(data, req_count, trade_sequence, query_reference, request_id, is_last,session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryOptionCombinedPosition(dict data, dict error_info, int request_id, bool is_last, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onQueryOptionCombinedPosition")(data, error_info, request_id, is_last,session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryOptionCombinedStrategyInfo(dict data, dict error_info, int request_id, bool is_last, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onQueryOptionCombinedStrategyInfo")(data, error_info, request_id, is_last,session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onCancelOptionCombinedOrderError(dict data, dict error_info, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onCancelOptionCombinedOrderError")(data, error_info,session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onQueryOptionCombinedExecPosition(dict data, dict error_info, int request_id, bool is_last, uint64_t session) {
		PyLock lock;

		try {
			this->get_override("onQueryOptionCombinedExecPosition")(data, error_info, request_id, is_last,session);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};


	virtual void onQueryStrategy(dict data, string strategy_param, dict error_info, int32_t request_id, bool is_last, uint64_t session_id) {
		PyLock lock;
		printf("onQueryStrategy---\n");
		try {
			this->get_override("onQueryStrategy")(data,strategy_param, error_info, request_id,is_last,session_id);
			printf("get_override(onQueryStrategy)---\n");
		} catch (error_already_set const &) {
			PyErr_Print();
			printf("catch(onQueryStrategy)\n");
		}
	};

	virtual void onStrategyStateReport(dict data,  uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onStrategyStateReport")(data,session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onALGOUserEstablishChannel(string user,dict error_info, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onALGOUserEstablishChannel")(user,error_info,session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};
	virtual void onInsertAlgoOrder(dict data,dict error_info, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onInsertAlgoOrder")(data,error_info,session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onCancelAlgoOrder(dict data,dict error_info, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onCancelAlgoOrder")(data,error_info,session_id);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onAlgoDisconnected(int reason) {
		PyLock lock;

		try {
			this->get_override("onAlgoDisconnected")(reason);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onAlgoConnected() {
		PyLock lock;

		try {
			this->get_override("onAlgoConnected")();
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onStrategySymbolStateReport(dict data, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onStrategySymbolStateReport")(data, session_id);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onNewStrategyCreateReport(dict data, string strategy_param, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onNewStrategyCreateReport")(data, strategy_param, session_id);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onStrategyRecommendation(bool basket_flag, dict data, string strategy_param, dict error_info, int32_t request_id, bool is_last, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onStrategyRecommendation")(basket_flag, data, strategy_param, error_info, request_id, is_last, session_id);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onModifyAlgoOrder(dict data, dict error_info, uint64_t session_id) {
		PyLock lock;

		try {
			this->get_override("onModifyAlgoOrder")(data, error_info, session_id);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};*/
};


BOOST_PYTHON_MODULE(vnxtpxtrader)
{
	//PyEval_InitThreads();	//导入时运行，保证先创建GIL
	Py_Initialize();

	class_<TraderApiWrap, boost::noncopyable>("TraderApi")
		.def("createTraderApi", &TraderApiWrap::createTraderApi)
		.def("release", &TraderApiWrap::release)
		.def("exit", &TraderApiWrap::exit)
		.def("getTradingDay", &TraderApiWrap::getTradingDay)
		.def("getApiLastError", &TraderApiWrap::getApiLastError)
		.def("getApiVersion", &TraderApiWrap::getApiVersion)
		.def("getClientIDByXTPID", &TraderApiWrap::getClientIDByXTPID)
		.def("getAccountByXTPID", &TraderApiWrap::getAccountByXTPID)
		.def("subscribePublicTopic", &TraderApiWrap::subscribePublicTopic)
		.def("setSoftwareKey", &TraderApiWrap::setSoftwareKey)
		.def("setSoftwareVersion", &TraderApiWrap::setSoftwareVersion)
		.def("setHeartBeatInterval", &TraderApiWrap::setHeartBeatInterval)
		.def("login", &TraderApiWrap::login)
		.def("logout", &TraderApiWrap::logout)
		.def("getAccountTradeMarket", &TraderApiWrap::getAccountTradeMarket)
		.def("getANewOrderXTPID", &TraderApiWrap::getANewOrderXTPID)
		.def("getMaxReqNumOfPagedQuery", &TraderApiWrap::getMaxReqNumOfPagedQuery)
		.def("insertOrder", &TraderApiWrap::insertOrder)
		.def("insertOrderExtra", &TraderApiWrap::insertOrderExtra)
		.def("cancelOrder", &TraderApiWrap::cancelOrder)
		.def("queryOrderByXTPID", &TraderApiWrap::queryOrderByXTPID)
		.def("queryOrders", &TraderApiWrap::queryOrders)
		.def("queryUnfinishedOrders", &TraderApiWrap::queryUnfinishedOrders)
		.def("queryTradesByXTPID", &TraderApiWrap::queryTradesByXTPID)
		.def("queryTrades", &TraderApiWrap::queryTrades)
		.def("queryPosition", &TraderApiWrap::queryPosition)
		.def("queryAllPosition", &TraderApiWrap::queryAllPosition)
		.def("querySecurityAccount", &TraderApiWrap::querySecurityAccount)
		.def("queryAsset", &TraderApiWrap::queryAsset)
		.def("fundTransfer", &TraderApiWrap::fundTransfer)
		.def("queryFundTransferByID", &TraderApiWrap::queryFundTransferByID)
		.def("queryFundTransferByPage", &TraderApiWrap::queryFundTransferByPage)
		.def("queryETF", &TraderApiWrap::queryETF)
		.def("queryETFTickerBasket", &TraderApiWrap::queryETFTickerBasket)
		.def("queryIPOInfoList", &TraderApiWrap::queryIPOInfoList)
		.def("queryIPOQuotaInfo", &TraderApiWrap::queryIPOQuotaInfo)
		.def("queryBondIPOInfoList", &TraderApiWrap::queryBondIPOInfoList)		
		.def("queryBondSwapStockInfo", &TraderApiWrap::queryBondSwapStockInfo)
		.def("queryOrdersByPage", &TraderApiWrap::queryOrdersByPage)
		.def("queryTradesByPage", &TraderApiWrap::queryTradesByPage)
		.def("queryOtherServerFund", &TraderApiWrap::queryOtherServerFund)
		/*.def("queryOptionAuctionInfo", &TraderApiWrap::queryOptionAuctionInfo)
		.def("creditCashRepay", &TraderApiWrap::creditCashRepay)
		.def("queryCreditCashRepayInfo", &TraderApiWrap::queryCreditCashRepayInfo)
		.def("queryCreditFundInfo", &TraderApiWrap::queryCreditFundInfo)
		.def("queryCreditDebtInfo", &TraderApiWrap::queryCreditDebtInfo)
		.def("queryCreditTickerDebtInfo", &TraderApiWrap::queryCreditTickerDebtInfo)
		.def("queryCreditAssetDebtInfo", &TraderApiWrap::queryCreditAssetDebtInfo)
		.def("queryCreditTickerAssignInfo", &TraderApiWrap::queryCreditTickerAssignInfo)
		.def("queryCreditExcessStock", &TraderApiWrap::queryCreditExcessStock)
		.def("queryMulCreditExcessStock", &TraderApiWrap::queryMulCreditExcessStock)

		.def("creditExtendDebtDate", &TraderApiWrap::creditExtendDebtDate)
		.def("queryCreditExtendDebtDateOrders", &TraderApiWrap::queryCreditExtendDebtDateOrders)
		.def("queryCreditFundExtraInfo", &TraderApiWrap::queryCreditFundExtraInfo)
		.def("queryCreditPositionExtraInfo", &TraderApiWrap::queryCreditPositionExtraInfo)
		
		.def("creditCashRepayDebtInterestFee", &TraderApiWrap::creditCashRepayDebtInterestFee)
		.def("creditSellStockRepayDebtInterestFee", &TraderApiWrap::creditSellStockRepayDebtInterestFee)
		.def("insertOptionCombinedOrder", &TraderApiWrap::insertOptionCombinedOrder)
		.def("insertOptionCombinedOrderExtra", &TraderApiWrap::insertOptionCombinedOrderExtra)
		.def("queryOptionCombinedUnfinishedOrders", &TraderApiWrap::queryOptionCombinedUnfinishedOrders)
		.def("queryOptionCombinedUnfinishedOrdersEx", &TraderApiWrap::queryOptionCombinedUnfinishedOrdersEx)
		.def("queryOptionCombinedOrderByXTPID", &TraderApiWrap::queryOptionCombinedOrderByXTPID)
		.def("queryOptionCombinedOrderByXTPIDEx", &TraderApiWrap::queryOptionCombinedOrderByXTPIDEx)
		.def("queryOptionCombinedOrders", &TraderApiWrap::queryOptionCombinedOrders)
		.def("queryOptionCombinedOrdersEx", &TraderApiWrap::queryOptionCombinedOrdersEx)
		.def("queryOptionCombinedOrdersByPage", &TraderApiWrap::queryOptionCombinedOrdersByPage)
		.def("queryOptionCombinedOrdersByPageEx", &TraderApiWrap::queryOptionCombinedOrdersByPageEx)
		.def("queryOptionCombinedTradesByXTPID", &TraderApiWrap::queryOptionCombinedTradesByXTPID)
		.def("queryOptionCombinedTrades", &TraderApiWrap::queryOptionCombinedTrades)
		.def("queryOptionCombinedTradesByPage", &TraderApiWrap::queryOptionCombinedTradesByPage)
		.def("queryOptionCombinedPosition", &TraderApiWrap::queryOptionCombinedPosition)
		.def("queryOptionCombinedStrategyInfo", &TraderApiWrap::queryOptionCombinedStrategyInfo)
		.def("cancelOptionCombinedOrder", &TraderApiWrap::cancelOptionCombinedOrder)
		.def("queryOptionCombinedExecPosition", &TraderApiWrap::queryOptionCombinedExecPosition)
		

		.def("loginALGO", &TraderApiWrap::loginALGO)
		.def("queryStrategy", &TraderApiWrap::queryStrategy)
		.def("aLGOUserEstablishChannel", &TraderApiWrap::aLGOUserEstablishChannel)
		.def("insertAlgoOrder", &TraderApiWrap::insertAlgoOrder)
		.def("cancelAlgoOrder", &TraderApiWrap::cancelAlgoOrder)
		.def("getAlgorithmIDByOrder", &TraderApiWrap::getAlgorithmIDByOrder)
		.def("strategyRecommendation", &TraderApiWrap::strategyRecommendation)
		.def("modifyAlgoOrder", &TraderApiWrap::modifyAlgoOrder)*/

		////////////////////////回调///////////////////////
		.def("onDisconnected", pure_virtual(&TraderApiWrap::onDisconnected))
		.def("onServerStatusNotification", pure_virtual(&TraderApiWrap::onServerStatusNotification))
		.def("onError", pure_virtual(&TraderApiWrap::onError))
		.def("onConnect", pure_virtual(&TraderApiWrap::onConnect))
		.def("onResumeEnd", pure_virtual(&TraderApiWrap::onResumeEnd))
		.def("onUnknownOrder", pure_virtual(&TraderApiWrap::onUnknownOrder))
		.def("onOrderAck", pure_virtual(&TraderApiWrap::onOrderAck))
		.def("onOrderEvent", pure_virtual(&TraderApiWrap::onOrderEvent))
		.def("onTradeEvent", pure_virtual(&TraderApiWrap::onTradeEvent))
		.def("onCancelOrderError", pure_virtual(&TraderApiWrap::onCancelOrderError))
		.def("onQueryOrder", pure_virtual(&TraderApiWrap::onQueryOrder))
		.def("onQueryTrade", pure_virtual(&TraderApiWrap::onQueryTrade))
		.def("onQueryPosition", pure_virtual(&TraderApiWrap::onQueryPosition))
		.def("onQuerySecurityAccount", pure_virtual(&TraderApiWrap::onQuerySecurityAccount))
		.def("onQueryAsset", pure_virtual(&TraderApiWrap::onQueryAsset))
		.def("onQueryFundTransfer", pure_virtual(&TraderApiWrap::onQueryFundTransfer))
		.def("onQueryFundTransferByPage", pure_virtual(&TraderApiWrap::onQueryFundTransferByPage))
		.def("onFundTransfer", pure_virtual(&TraderApiWrap::onFundTransfer))
		.def("onQueryOtherServerFund", pure_virtual(&TraderApiWrap::onQueryOtherServerFund))
		.def("onUnknownFundTransfer", pure_virtual(&TraderApiWrap::onUnknownFundTransfer))
		.def("onQueryETF", pure_virtual(&TraderApiWrap::onQueryETF))
		.def("onQueryETFBasket", pure_virtual(&TraderApiWrap::onQueryETFBasket))
		.def("onQueryIPOInfoList", pure_virtual(&TraderApiWrap::onQueryIPOInfoList))
		.def("onQueryIPOQuotaInfo", pure_virtual(&TraderApiWrap::onQueryIPOQuotaInfo))
		.def("onQueryBondIPOInfoList", pure_virtual(&TraderApiWrap::onQueryBondIPOInfoList))
		.def("onQueryBondSwapStockInfo", pure_virtual(&TraderApiWrap::onQueryBondSwapStockInfo))
		/*.def("onQueryOptionAuctionInfo", pure_virtual(&TraderApiWrap::onQueryOptionAuctionInfo))
		.def("onCreditCashRepay", pure_virtual(&TraderApiWrap::onCreditCashRepay))
		.def("onQueryCreditCashRepayInfo", pure_virtual(&TraderApiWrap::onQueryCreditCashRepayInfo))
		.def("onQueryCreditFundInfo", pure_virtual(&TraderApiWrap::onQueryCreditFundInfo))
		.def("onQueryCreditDebtInfo", pure_virtual(&TraderApiWrap::onQueryCreditDebtInfo))
		.def("onQueryCreditTickerDebtInfo", pure_virtual(&TraderApiWrap::onQueryCreditTickerDebtInfo))
		.def("onQueryCreditAssetDebtInfo",pure_virtual(&TraderApiWrap::onQueryCreditAssetDebtInfo))
		.def("onQueryCreditTickerAssignInfo", pure_virtual(&TraderApiWrap::onQueryCreditTickerAssignInfo))
		.def("onQueryCreditExcessStock", pure_virtual(&TraderApiWrap::onQueryCreditExcessStock))
		.def("onQueryMulCreditExcessStock", pure_virtual(&TraderApiWrap::onQueryMulCreditExcessStock))

		.def("onCreditExtendDebtDate", pure_virtual(&TraderApiWrap::onCreditExtendDebtDate))
		.def("onQueryCreditExtendDebtDateOrders",pure_virtual(&TraderApiWrap::onQueryCreditExtendDebtDateOrders))
		.def("onQueryCreditFundExtraInfo", pure_virtual(&TraderApiWrap::onQueryCreditFundExtraInfo))
		.def("onQueryCreditPositionExtraInfo", pure_virtual(&TraderApiWrap::onQueryCreditPositionExtraInfo))
		.def("onQueryOrderByPage", pure_virtual(&TraderApiWrap::onQueryOrderByPage))
		.def("onQueryTradeByPage", pure_virtual(&TraderApiWrap::onQueryTradeByPage))
		.def("onCreditCashRepayDebtInterestFee", pure_virtual(&TraderApiWrap::onCreditCashRepayDebtInterestFee))

		.def("onOptionCombinedOrderEvent", pure_virtual(&TraderApiWrap::onOptionCombinedOrderEvent))
		.def("onOptionCombinedTradeEvent", pure_virtual(&TraderApiWrap::onOptionCombinedTradeEvent))
		.def("onQueryOptionCombinedOrders", pure_virtual(&TraderApiWrap::onQueryOptionCombinedOrders))
		.def("onQueryOptionCombinedOrdersEx", pure_virtual(&TraderApiWrap::onQueryOptionCombinedOrdersEx))
		.def("onQueryOptionCombinedOrdersByPage", pure_virtual(&TraderApiWrap::onQueryOptionCombinedOrdersByPage))
		.def("onQueryOptionCombinedOrdersByPageEx", pure_virtual(&TraderApiWrap::onQueryOptionCombinedOrdersByPageEx))
		.def("onQueryOptionCombinedTrades", pure_virtual(&TraderApiWrap::onQueryOptionCombinedTrades))
		.def("onQueryOptionCombinedTradesByPage", pure_virtual(&TraderApiWrap::onQueryOptionCombinedTradesByPage))
		.def("onQueryOptionCombinedPosition", pure_virtual(&TraderApiWrap::onQueryOptionCombinedPosition))
		.def("onQueryOptionCombinedStrategyInfo", pure_virtual(&TraderApiWrap::onQueryOptionCombinedStrategyInfo))
		.def("onCancelOptionCombinedOrderError", pure_virtual(&TraderApiWrap::onCancelOptionCombinedOrderError))
		.def("onQueryOptionCombinedExecPosition", pure_virtual(&TraderApiWrap::onQueryOptionCombinedExecPosition))
		

		.def("onQueryStrategy", pure_virtual(&TraderApiWrap::onQueryStrategy))
		.def("onStrategyStateReport", pure_virtual(&TraderApiWrap::onStrategyStateReport))
		.def("onALGOUserEstablishChannel", pure_virtual(&TraderApiWrap::onALGOUserEstablishChannel))
		.def("onInsertAlgoOrder", pure_virtual(&TraderApiWrap::onInsertAlgoOrder))
		.def("onCancelAlgoOrder", pure_virtual(&TraderApiWrap::onCancelAlgoOrder))
		.def("onAlgoDisconnected", pure_virtual(&TraderApiWrap::onAlgoDisconnected))
		.def("onAlgoConnected", pure_virtual(&TraderApiWrap::onAlgoConnected))
		.def("onStrategySymbolStateReport", pure_virtual(&TraderApiWrap::onStrategySymbolStateReport))
		.def("onNewStrategyCreateReport", pure_virtual(&TraderApiWrap::onNewStrategyCreateReport))
		.def("onStrategyRecommendation", pure_virtual(&TraderApiWrap::onStrategyRecommendation))
		.def("onModifyAlgoOrder", pure_virtual(&TraderApiWrap::onModifyAlgoOrder))*/
		;
};
