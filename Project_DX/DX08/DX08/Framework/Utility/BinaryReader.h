#pragma once
class BinaryReader
{
public:
	BinaryReader(wstring path);
	~BinaryReader();
	
	bool Bool();
	int Int();
	UINT UInt();
	float Float();
	string String();

	void Byte(OUT void** data, UINT dataSize);

private:
	HANDLE _file;
	DWORD _size;
};