#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <iostream>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <memory>
#include <functional>
using namespace std;
#include "Connection.h"
// ʵ�����ӳع���ģ��

class ConnectionPool
{
public:
	// ��ȡ���ӳض���ʵ��
	static ConnectionPool* getConnectionPool();
	// ���ⲿ�ṩ�ӿڣ������ӳ��л�ȡһ�����õĿ�������
	shared_ptr<Connection> getConnection();


	
private:
	ConnectionPool(); // ����#1 ���캯��˽�л�

	bool loadConfigFile(); // �������ļ��м���������
	
	// �����ڶ������߳��У�ר�Ÿ�������������
	void produceConnectionTask();

	// ɨ�����ӵ��̺߳���
	void scannerConnectionTask();

	string _ip; // mysql��ip��ַ
	unsigned short _port; // mysql�Ķ˿ں�
	string _username; // mysql��¼�û���
	string _dbname; // �������ݿ������
	string _password; // mysql��¼����
	int _initSize; // ���ӳصĳ�ʼ������
	int _maxSize; // ���ӳص����������
	int _maxIdleTime; // ���ӳ�������ʱ��
	int _connectionTimeout; // ���ӳػ�ȡ���ӵĳ�ʱʱ��


	queue<Connection*> _connectionQue; // �洢mysql���ӵĶ���
	mutex _queueMutex; // ά�����Ӷ��е��̰߳�ȫ������
	atomic_int _connectionCnt; // ��¼������������connection���ӵ�������
	condition_variable cv; // ���������������������������̺߳������̵߳�ͨ��
};