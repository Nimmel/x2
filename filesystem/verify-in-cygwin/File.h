

#ifndef File_h__
#define File_h__

#include <def.h>
#include <cstdio>
#include "MallocToSimple.h"
#include <Memory.h>
#include <List.h>
/**
* 
*/
class FileDescriptor
{
public:
	enum{ TYPE_FILE=0,TYPE_DIR=1,TYPE_EAP=2};
public:
	AS_MACRO FileDescriptor(char type,size_t sectionStart,size_t sectionSpan,
			size_t fileStart,size_t fileLen,size_t nameStart,unsigned int createdTime,unsigned int lastModefiedTime);

	AS_MACRO char getType()const;

	AS_MACRO size_t getNameOffset()const;
	AS_MACRO void	setNameOffset(size_t off);
	AS_MACRO unsigned int getCreatedTime() const;
	AS_MACRO void setCreatedTime(unsigned int createdTime);
	AS_MACRO size_t getFileLen() const;
	AS_MACRO void setFileLen(size_t fileLen);
	AS_MACRO size_t getFileStart() const;
	AS_MACRO void setFileStart(size_t fileStart);
	AS_MACRO unsigned int getLastModefiedTime() const;
	AS_MACRO void setLastModefiedTime(unsigned int lastModefiedTime);
	AS_MACRO size_t getSectionSpan() const;
	AS_MACRO void setSectionSpan(size_t sectionSpan);
	AS_MACRO size_t getSectionStart() const;
	AS_MACRO void setSectionStart(size_t sectionStart);
	AS_MACRO void setType(char type);

protected:
	char type;
	size_t sectionStart,sectionSpan,fileStart,fileLen,nameStart;
	unsigned int createdTime,lastModefiedTime;

};

/**
 *  about offset: relative to the beginning of that partition
 *		zero(0~3,an integer size) address in   filename should not be used,pointing to them means no name.Only root directory can do that
 *
 *	FreeSpaceSection:
 *		The recorded data is relative the 0.This is because these files does not exist in the memory,so they do not use buffer
 *		0:  record the whole start & limit
 *		....
 *
 *	RAW Section:
 *
 */
class X2fsUtil{
public:
	enum{SecSize=512,KiB=2*SecSize,MiB=1024*KiB,GiB=1024*MiB};
	enum{

		 FileNameSection=2*SecSize,FileNameSectionLen=5*SecSize,
		 DirSection=FileNameSection+FileNameSectionLen,DirSectionLen=15*SecSize,
		 FreeSpaceSection=DirSection+DirSectionLen,FreeSpaceSectionLen=5*SecSize

	};
	typedef X2fsUtil This;
	typedef MallocToSimple<TreeNode<MemoryDescriptor> > TMSmm;
	typedef MallocToSimple<ListNode<LinearSourceDescriptor> > LLSmm;
	typedef MemoryManager<MallocToSimple> FileNameMM;
	typedef SimpleMemoryManager<TreeNode<FileDescriptor> > FileNodeMM;
	typedef FileNodeMM::Node FileNode;
	typedef Tree<FileDescriptor,SimpleMemoryManager> FileTree;
	typedef LinearSourceManager<LinearSourceDescriptor,MallocToSimple> FreeSpaceMM;

	enum{
		FileNodeSize=sizeof(FileNode)
	};
public:
	X2fsUtil(const char *file);//create a handler to the image file.
	~X2fsUtil();

	bool createFileInRoot(const char *name,size_t secNum);//reserved number of sectors
	void listRoot();
	void flush();//write the buffered content back to file

protected:
	void initBuffers();
	void adjustDirbufOffset(int off);//positive or negative


	void retriveFileNameSection();
	/**
	 * This is not necessary for filename section,cause all changes had been made as direct and immediate
	 */
	DEPRECATED void saveFileNameSection();

	void retriveFreeSpaceSection();
	void saveFreeSpaceSection();

	void retriveDirSection();
	void saveDirSection();
	char *getFileName(const FileDescriptor &fd,size_t &nlen);

protected:
	char *namebuf,*dirbuf,*freebuf,*filebuf;
	size_t namebufLen,dirbufLen,freebufLen,filebufLen,reservedLen;
	const char *imgFile;
	FILE *fpimg;
	TMSmm mmnodesmm;
	FileNameMM filenamemm;
	LLSmm listnodesmm;

	FileNodeMM dirsmm;
	FileTree fileTree;
	FreeSpaceMM freemm;



public:
	static void mockMkfsX2fs(void *base,size_t secNum);
	DEPRECATED static void createFile(void *base,const char* name,size_t secNum);//default length=0,start=0,span=secNum
};


//=============Function Macros
//=====class : FileDescriptor
FileDescriptor::FileDescriptor(char type,size_t sectionStart,size_t sectionSpan,size_t fileStart,size_t fileLen,size_t nameStart,unsigned int createdTime,unsigned int lastModefiedTime):
type(type),sectionStart(sectionStart),sectionSpan(sectionSpan),fileStart(fileStart),fileLen(fileLen),
nameStart(nameStart),createdTime(createdTime),lastModefiedTime(lastModefiedTime)
{

}

 unsigned int FileDescriptor::getCreatedTime() const
{
	return createdTime;
}

 void FileDescriptor::setCreatedTime(unsigned int createdTime) {
	this->createdTime = createdTime;
}

 size_t FileDescriptor::getFileLen() const {
	return fileLen;
}

 void FileDescriptor::setFileLen(size_t fileLen) {
	this->fileLen = fileLen;
}

 size_t FileDescriptor::getFileStart() const {
	return fileStart;
}

 void FileDescriptor::setFileStart(size_t fileStart) {
	this->fileStart = fileStart;
}

 unsigned int FileDescriptor::getLastModefiedTime() const {
	return lastModefiedTime;
}

 void FileDescriptor::setLastModefiedTime(unsigned int lastModefiedTime) {
	this->lastModefiedTime = lastModefiedTime;
}

 size_t FileDescriptor::getSectionSpan() const {
	return sectionSpan;
}

 void FileDescriptor::setSectionSpan(size_t sectionSpan) {
	this->sectionSpan = sectionSpan;
}

 size_t FileDescriptor::getSectionStart() const {
	return sectionStart;
}

 void FileDescriptor::setSectionStart(size_t sectionStart) {
	this->sectionStart = sectionStart;
}

char FileDescriptor::getType() const {
	return type;
}

 void FileDescriptor::setType(char type) {
	this->type = type;
}

size_t FileDescriptor::getNameOffset()const
{
	return this->nameStart;
}
void	FileDescriptor::setNameOffset(size_t off)
{
	this->nameStart=off;
}

#endif //File_h__
