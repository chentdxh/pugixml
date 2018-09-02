// practice.cpp : 定义控制台应用程序的入口点。

#include<iostream>
#include<string>
#include "../include/xml/pugixml.hpp"
#include "../include/xml/integer_to_string.hpp"
#include "../include/xml/pugiconfig.hpp"
#include <sys/time.h>
using namespace std;
using namespace pugi;

static const int32_t nBufSize = 128;
static char szBuf[nBufSize] = { 0 };

// 写操作
void Write(const char *szXmlFileName)
{
	pugi::xml_document xmlDoc;
	pugi::xml_node nodeRoot = xmlDoc.append_child("root");
	// 声明
	pugi::xml_node pre = xmlDoc.prepend_child(pugi::node_declaration);
	pre.append_attribute("version") = "1.0";
	pre.append_attribute("encoding") = "utf-8";

	// 注释节点1
	pugi::xml_node nodeCommentStudents = nodeRoot.append_child(pugi::node_comment);
	nodeCommentStudents.set_value("all students info");
	// 普通节点1
	pugi::xml_node nodeStudents = nodeRoot.append_child("students");
	for (int32_t i = 0; i < 10; ++i)
	{
		snprintf(szBuf, nBufSize, "student_%02d", i);
		pugi::xml_node nodeStudent = nodeStudents.append_child("student");
		// 增加属性
		nodeStudent.append_attribute("name").set_value(szBuf);
		nodeStudent.append_attribute("score").set_value(100 - i*10);
	}

	// 注释节点2
	pugi::xml_node nodeCommentBooks = nodeRoot.append_child(pugi::node_comment);
	nodeCommentBooks.set_value("all books info");
	// 普通结点2
	pugi::xml_node nodeBooks = nodeRoot.append_child("books");
	for (int32_t i = 0; i < 10; ++i)
	{
		snprintf(szBuf, nBufSize, "book_%02d", i);
		pugi::xml_node nodeBook = nodeBooks.append_child("book");
		// 增加属性
		nodeBook.append_attribute("book").set_value(szBuf);
		nodeBook.append_attribute("price").set_value(50 - i);
	}

	// 注释节点3
	pugi::xml_node nodeCommentaddress = nodeRoot.append_child(pugi::node_comment);
	nodeCommentaddress.set_value("IP address");
	// 普通结点3
	pugi::xml_node nodeaddress = nodeRoot.append_child("ip");
	nodeaddress.text().set("192.168.1.11");
	xmlDoc.save_file(szXmlFileName, "\t", 1U, pugi::encoding_utf8);
}

void Read(const char *szXmlFileName)
{
	pugi::xml_document xmlDoc;
	if (!xmlDoc.load_file(szXmlFileName, pugi::parse_default, pugi::encoding_utf8))
	{
		std::cout << "read " << szXmlFileName << " failed" << std::endl;
		return;
	}
	pugi::xml_node nodeRoot = xmlDoc.child("root");
	// 读取第一个节点
	for (pugi::xml_node node = nodeRoot.child("students").first_child(); node; node = node.next_sibling())
	{
		//std::cout << "\t" << node.attribute("name").value() << "," << node.attribute("score").value() << std::endl;
	}
	//std::cout << std::endl;
	// 读取第二个节点
	for (pugi::xml_node node = nodeRoot.child("books").first_child(); node; node = node.next_sibling())
	{
		//std::cout << "\t" << node.attribute("book").value() << "," << node.attribute("price").value() << std::endl;
	}
	// 读取第三个节点
	auto ipresult = nodeRoot.child("ip").text().as_string();
	//std::cout << "\t" << ipresult << std::endl;
	
}

int32_t main()
{
  clock_t start,end;
  start = clock();
  for(int i=0;i<10000;i++)
  {
	  const char *szXmlFileName = "info.xml";
	  //const char *RdXmlFileName = "test.xml";
	  Write(szXmlFileName);
	  Read(szXmlFileName);
  }
  end = clock();
  double seconds = (double)(end - start)/CLOCKS_PER_SEC;
  fprintf(stderr, "Use time is: %.8f\n", seconds);
	std::cout << "finish" << std::endl;
	getchar();
	return 0;
}
