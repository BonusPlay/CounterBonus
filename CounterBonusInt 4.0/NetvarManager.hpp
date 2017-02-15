#pragma once

#include <memory>
#include <iostream>
#include <unordered_map>
#include "SourceEngine/Recv.hpp"

//Forward declaration. The class is defined on the cpp file
struct NetvarTable;
class NetvarDatabase;

class NetvarManager
{
private:
	static NetvarManager* instance;

	NetvarManager();
	~NetvarManager();

	NetvarManager(const NetvarManager&) = delete;

public:
	static NetvarManager* getInstance();

	void CreateDatabase();
	void DestroyDatabase();

	void Dump(std::ostream& stream);
	void Dump(const std::string& file);

	int GetNetvarCount() { return m_netvarCount; }
	int GetTableCount() { return m_tableCount; }

	template<typename ...Args>
	uint32_t GetOffset(const std::string& szTableName, Args&&... args)
	{
		return GetOffset(szTableName, { std::forward<Args>(args)... });
	}

private:
	std::unique_ptr<NetvarTable>  InternalLoadTable(SourceEngine::RecvTable* pRecvTable, uint32_t offset);
	void                          Dump(std::ostream& output, NetvarTable& table, int level);
	uint32_t                      GetOffset(const std::string& szTableName, const std::initializer_list<std::string>& props);

	std::unique_ptr<NetvarDatabase>    m_pDatabase = nullptr;
	uint32_t                           m_tableCount = 0;
	uint32_t                           m_netvarCount = 0;
};

#define GET_NETVAR(table, ...) NetvarManager::getInstance()->GetOffset(table, __VA_ARGS__)