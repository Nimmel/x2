/*
 * libx2_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_LIBX2_MACROS_H_
#define INCLUDE_MACROS_LIBX2_MACROS_H_

#include <libx2.h>
//================函数宏区：使用 __attribute__((always_inline))===============
#if defined(CODE32)||defined(CODE16)
void Util::reboot()
{

    __asm__ __volatile__(
    "inb  $0x92,%%eax \n\t"
    "andb $0xfe,%%eax \n\t"
    "outb %%al,$0x92 \n\t"
    "orb $0x1,%%eax \n\t"
    "outb %%al,$0x92\n\t"
    :
    :
    :"eax"
    );
}
void	Util::setStrSel(int sel)
{
	Util::strSel=sel;
}
int  Util::getStrSel()
{
	return Util::strSel;
}
void Util::insertMark(int marker)
{
    __asm__(
     "nop \n\t"
    );
}
void Util::jmpDie()
{
    __asm__("jmp .\n\t");
}

void Util::cli()
{
    __asm__("cli \n\t");
}
void Util::sti()
{
    __asm__("sti \n\t");
}
void Util::enterDs(int seg,int& temp)
{
    if(seg!=SEG_CURRENT)
    {
            __asm__ __volatile__(
            "mov %%ds,%%bx \n\t"
            "mov %%ax,%%ds \n\t"
            :"=b"(temp)
            :"a"(seg)
            :);
    }
}
void Util::leaveDs(int seg,int temp)
{
    if(seg!=SEG_CURRENT)
    {
        __asm__ __volatile__("mov %%ax,%%ds \n\t"::"a"(temp):);
    }
}
 void Util::enterEs(int seg,int& temp)
 {
     __asm__ __volatile__("mov %%es,%%ax\n\t":"=a"(temp)::);
    if(seg==SEG_CURRENT)
    {
        __asm__ __volatile__(
            "mov %%ds,%%ax \n\t"
            "mov %%ax,%%es \n\t"
            :
            :
            :"eax"
        );
    }else{
        __asm__ __volatile__(
        "mov %%ax,%%es \n\t"
        :
        :"a"(seg)
        :
        );
    }
 }
void Util::leaveEs(int temp)
{
    __asm__ __volatile__("mov %%ax,%%es \n\t"::"a"(temp):);
}

void Util::outb(short port,char data)
{
    __asm__(
    "outb %%al,%%dx \n\t"
    :
    :"d"(port),"a"(data)
    :
    );
}
void Util::outw(short port,short data)
{
    __asm__(
    "outw %%ax,%%dx \n\t"
    :
    :"d"(port),"a"(data)
    :
    );
}
char Util::inb(short port)
{
    char temp;
    __asm__(
    "inb %%dx,%%al \n\t"
    :"=a"(temp)
    :"d"(port)
    :
    );
    return temp;
}
short Util::inw(short port)
{
    short temp;
    __asm__(
    "inw %%dx,%%ax \n\t"
    :"=a"(temp)
    :"d"(port)
    :
    );
    return temp;
}
/*
void Util::pusha()
{
    __asm__("pusha \n\t");
}
void Util::popa()
{
    __asm__("popa \n\t");
}
*/
#endif

#if defined(CODE32)
int Printer::getX()
{
    return this->x;
}

int Printer::getY()
{
    return this->y;
}

//=======class ErrorSaver
ErrorSaver::ErrorSaver(int errno):errno(errno) {
}

int ErrorSaver::getErrno() const {
	return this->errno;
}

void ErrorSaver::setErrno(int errno) {
	this->errno=errno;
}

void Util::ltr(int sel)
{
    __asm__ __volatile__(
    "ltr %0 \n\t"
    :
    :"m"(sel)
    :
    );
}
void Util::lldt(int sel)
{
    __asm__ __volatile__(
    "lldt %0 \n\t"
    :
    :"m"(sel)
    :
    );
}
int	Util::getCurrentDs()
{
	int temp;
	__asm__ __volatile__(
	"push %%ds \n\t"
	"pop %%eax \n\t"
	:"=a"(temp)
	:
	:
	);
	return temp;
}
void Util::setCurrentDs(int ds)
{
	__asm__ __volatile__(
			"mov %%eax,%%ds \n\t"
			:
			:"a"(ds)
			 :
			 );
}
void Util::intReturn()
{
    __asm__(
    "leave \n\t"
    "iret \n\t"
    );
}
/**this originally works
void Util::initTarget(void *&target)
{
    __asm__ __volatile__("":"=c"(target)::);
}
*/
/************Deprecated
void Util::initTarget(void **target)
{
__asm__ __volatile__("":"=c"(*(char**)target)::);
}
*/
#endif


#if defined(CODE32)||defined(CODE64)
//=======class : Queue 宏
template <typename T>
int Queue<T>::empty()
{
    return curLen==0;
}
template <typename T>
int Queue<T>::full()
{
    return curLen==len;
}
template <typename T>
unsigned int Queue<T>::size()
{
    return curLen;
}
#endif

//============================================================================




#endif /* INCLUDE_MACROS_LIBX2_MACROS_H_ */
