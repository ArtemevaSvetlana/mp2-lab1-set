// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
  if (len < 0)
    throw "negative length";
  
		BitLen=len;
		MemLen= (len +  BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM;
		pMem=new TELEM[MemLen];
		  if (pMem!=NULL)	
			memset(pMem,0,MemLen*sizeof(TELEM));  
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	  BitLen=bf.BitLen;
	  MemLen=bf.MemLen;
	  pMem=new TELEM[MemLen];
	  if (pMem!=NULL)
		for(int i=0;i<MemLen;i++)
		  pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n<0)||(n>BitLen))
		throw "Error";
	else
		return  n/BITS_IN_ONE_MEM;
	 
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if((n<0)||(n>BitLen))
		throw "Error!";
	else
		return 1<<(n-GetMemIndex(n)*BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0)||(n>BitLen))
		throw "Error!";
	else
		pMem[GetMemIndex(n)]=pMem[GetMemIndex(n)]|GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n<0)||(n>BitLen))
		throw "Error!";
	else
		pMem[GetMemIndex(n)] &=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n<0)||(n>BitLen))
		throw "Error!";

	int res= pMem[GetMemIndex(n)] & GetMemMask(n);
	if(res>0)
		return 1;
	else
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
		BitLen=bf.BitLen;
		if (MemLen!=bf.MemLen)
		{
			MemLen=bf.MemLen;
			if (pMem!=NULL)
				delete [] pMem;
			pMem= new TELEM[MemLen];
		}
		//if (pMem!=NULL)
			for (int i=0;i<MemLen;i++)
				pMem[i]=bf.pMem[i];
	
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res=1;
	if (BitLen!=bf.BitLen)
		res=0;
	else
		for (int i=0;i<MemLen;i++)
			if (pMem[i]!=bf.pMem[i])
			{
				res=0;
				break;
			}
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  	int res=1;
	if (BitLen!=bf.BitLen)
		res=0;
	else
	{
		int k=0;
		for (int i=0;i<MemLen;i++)
			if (pMem[i]==bf.pMem[i])
				k++;
		if (k==MemLen)
			res=0;
	}
	return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, n=BitLen;
	if (BitLen<bf.BitLen)
		n=bf.BitLen;
	TBitField res(n);
	
	for (i=0;i<MemLen;i++)
		res.pMem[i]=pMem[i];
	for (i=0;i<bf.MemLen;i++)
		res.pMem[i] |=bf.pMem[i];		
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int n=BitLen;
	if (BitLen>bf.BitLen)
		n=bf.BitLen;
	TBitField res(n);

	for(int i=0;i<res.MemLen;i++)
		res.pMem[i]=pMem[i]&bf.pMem[i];
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for(int i=0;i<MemLen-1;i++)
		res.pMem[i]=~pMem[i];
	
	for (int i=(res.MemLen-1)*BITS_IN_ONE_MEM; i<res.BitLen;i++)
	{
		if (GetBit(i)==0)
			res.SetBit(i);
		else
			res.ClrBit(i);
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  /*int i=0;
  char ch;{
  do {istr>>ch;}
  while (ch !=' ');
  while (1) {istr>>ch;}
	if (ch=='0')
		bf.SetBit(i++);
	else if (ch=='1')
		bf.SetBit(i++);
	else
		throw "Error!";
  }*/
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  /*int n=bf.GetLength();
  for (int i=0;i<n;i++)
	  if (bf.GetBit(i))
		  ostr<<'1';
	  else
		  ostr<<'1';*/
  return ostr;
}
