#pragma once
#include "DataTable.h"
#include "Singleton.h"
class DataTableManager : public Singleton< DataTableManager>
{
protected:
	std::unordered_map<DataTable::Ids, DataTable*> tables;

	DataTableManager(const DataTableManager& other) = delete;
	bool operator==(const DataTableManager& other) const = delete;
public:
	DataTableManager() = default;
	virtual ~DataTableManager() { ReleaseAll(); }
	void LoadAll();
	void ReleaseAll();

	template <typename T>
	const T* Get(DataTable::Ids id) const;
};

#define DATATABLE_MANAGER (DataTableManager::GetInstance())

template<typename T>
inline const T* DataTableManager::Get(DataTable::Ids id) const
{
	auto find = tables.find(id);
	if (find == tables.end())
	{
		return nullptr;
	}
	return dynamic_cast<T*>(find->second);
}
