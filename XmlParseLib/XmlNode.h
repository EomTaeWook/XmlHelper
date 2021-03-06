#pragma once
#include<string>
#include<vector>
#include<map>
#include "NS.h"
//작성자 엄태욱 2018-01-10
//형태는 Data와 같으나 햇갈릴 위험이 있음으로
NS_XML_BEGIN
class XmlArribute
{
public:
	std::wstring prefix;
	std::wstring attributeKey;
	std::wstring attributeValue;
};
class XmlData
{
public:
	unsigned int depth;
	std::wstring prefix;
	std::wstring element;
	std::wstring elementText;
	std::map <std::wstring, XmlArribute*> attribute;
public:
	XmlData() {};
	~XmlData()
	{
		for (auto it = attribute.begin(); it != attribute.end(); ++it)
		{
			delete it->second;
		}
		attribute.clear();
	};
};

class XmlNode
{
private:
	XmlData _data;
	std::vector<XmlNode*> _child;
	XmlNode* _parent;
	XmlNode* _next;
public:
	XmlNode()
	{
		_parent = nullptr;
		_next = nullptr;
	}
	~XmlNode();
	void Add(XmlNode* node);
	std::vector<XmlNode*>& Node();
	XmlNode* Next();
	bool HasChildNodes();
	XmlData& GetData();
};
inline std::vector<XmlNode*>& XmlNode::Node()
{
	return _child;
}
//형제 노드가 없으면 nullPtr return
inline XmlNode* XmlNode::Next()
{
	return _next;
}
//자식노드 추가
inline void XmlNode::Add(XmlNode* node)
{
	node->_parent = this;
	if (_child.size() != 0)
	{
		_child.back()->_next = node;
	}
	_child.push_back(node);
}
inline XmlData& XmlNode::GetData()
{
	return _data;
}
inline XmlNode::~XmlNode()
{
	for (size_t i = 0; i < _child.size(); i++)
	{
		delete _child[i];
		_child[i] = NULL;
	}
	_child.clear();
}
inline bool XmlNode::HasChildNodes()
{
	return _child.size() != 0;
}
NS_XML_END