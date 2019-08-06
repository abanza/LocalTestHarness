#ifndef XML_FILEMANAGER_H
#define XML_FILEMANAGER_H

#include <vector>

class XmlFileManager
{
public:
	typedef std::vector<std::pair<std::string, std::string>> attribElems;
	XmlFileManager(const std::string& xml);
	bool next();
	std::string tag();
	attribElems attributes();
	std::string body();
	std::string element();
	std::string extractIdentifier(std::size_t& pos);
	void reset();
	std::size_t position();
	bool position(std::size_t p);
	std::string& xml();


private:
	// source string
	std::string _xml;
	std::size_t _position;
	// current element parts
	std::string _tag;
	attribElems _attributes;
	std::size_t localposition;
};

#endif // XML_FILEMANAGER
