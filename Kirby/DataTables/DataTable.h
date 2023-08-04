#pragma once


class DataTable
{
public:
	enum class Ids
	{
		None = -1,
		String,
		Stage,
	};
protected:
	Ids tableId = Ids::None;

	DataTable(const DataTable& other) = delete;
	bool operator==(const DataTable& other) const = delete;
public:
	static const int TotalIds = 2;
	DataTable(DataTable::Ids id) : tableId(id) {}
	virtual ~DataTable() {}

	virtual bool Load() = 0;
	virtual void Release() = 0;
};

