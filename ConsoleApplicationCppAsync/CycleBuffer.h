#pragma once

#include "libH.h"

//����� � ����������� ���������, �� ���� ������������ ������ ��� �������������� ���������� ��� ����������� ������


// ������ ���������� ������
// ��������� ��� ���������:
// ������ ������ - ������ ���� �������� ������,
// ��� ��������� ���������� � ������, �� ��������� unsigned char
template<int SIZE, class DATA_T = unsigned char>
class RingBuffer
{
public:
    // ���������� ��������� ��� �������� 
    typedef uint16_t INDEX_T;
private:
    // ������ ��� �����
    DATA_T _data[SIZE];
    // ���������� ������
    volatile INDEX_T _readCount;
    // ���������� �������
    volatile INDEX_T _writeCount;
    // ����� ��� ��������
    static const INDEX_T _mask = SIZE - 1;
public:
    // ������ � �����, ���������� true ���� �������� ��������
    inline bool Write(DATA_T value)
    {
        if (IsFull())
            return false;
        _data[_writeCount++ & _mask] = value;
        return true;
    }
    // ������ �� ������, ���������� true ���� �������� ���������
    inline bool Read(DATA_T& value)
    {
        if (IsEmpty())
            return false;
        value = _data[_readCount++ & _mask];
        return true;
    }
    // ���������� ������ ������� �� ������, �� ������ ���
    inline DATA_T First()const
    {
        return operator[](0);
    }
    // ���������� ��������� ������� �� ������, �� ������ ���
    inline DATA_T Last()const
    {
        return operator[](Count());
    }
    // ���������� ������� �� �������
    inline DATA_T& operator[] (INDEX_T i)
    {
        if (IsEmpty() || i > Count())
            return DATA_T();
        return _data[(_readCount + i) & _mask];
    }

    inline const DATA_T operator[] (INDEX_T i)const
    {
        if (IsEmpty())
            return DATA_T();
        return _data[(_readCount + i) & _mask];
    }
    // ���� �� �����
    inline bool IsEmpty()const
    {
        return _writeCount == _readCount;
    }
    // ����� �� �����
    inline bool IsFull()const
    {
        return ((INDEX_T)(_writeCount - _readCount) & (INDEX_T)~(_mask)) != 0;
    }
    // ���������� ��������� � ������
    INDEX_T Count()const
    {
        return (_writeCount - _readCount) & _mask;
    }
    // �������� �����
    inline void Clear()
    {
        _readCount = 0;
        _writeCount = 0;
    }
    // ������ ������
    inline unsigned Size()
    {
        return SIZE;
    }
};



// --------------------------------------------------------

#ifdef URSEL
enum { ursel = 1 << URSEL };
#else
enum { ursel = 0 };
#endif
// ������ ������� ����� ������ ������ ��������, ����� ��� ����� ���� �������� 
// ��� �������� �������.
#define IO_REG_WRAPPER(REG_NAME, CLASS_NAME, DATA_TYPE) \
        struct CLASS_NAME\
        {\
                typedef DATA_TYPE DataT;\
                static DataT Get(){return REG_NAME;}\
                static void Set(DataT value){REG_NAME = value;}\
                static void Or(DataT value){REG_NAME |= value;}\
                static void And(DataT value){REG_NAME &= value;}\
                static void Xor(DataT value){REG_NAME ^= value;}\
                static void AndOr(DataT andMask, DataT orMask){REG_NAME = (REG_NAME & andMask) | orMask;}\
                template<int Bit>\
                static bool BitIsSet(){return REG_NAME & (1 << Bit);}\
                template<int Bit>\
                static bool BitIsClear(){return !(REG_NAME & (1 << Bit));}\
        }

// ������� ������-������ ��� ���� ��������� USART
#define DECLARE_HW_USART(ClassName, UDR_Reg, UCSRA_Reg, UCSRB_Reg, UCSRC_Reg, UBRRL_Reg, UBRRH_Reg)\
struct ClassName\
{\
        IO_REG_WRAPPER(UDR_Reg, Udr, uint8_t);\
        IO_REG_WRAPPER(UCSRA_Reg, Ucsra, uint8_t);\
        IO_REG_WRAPPER(UCSRB_Reg, Ucsrb, uint8_t);\
        IO_REG_WRAPPER(UCSRC_Reg, Ucsrc, uint8_t);\
        IO_REG_WRAPPER(UBRRL_Reg, Ubrrl, uint8_t);\
        IO_REG_WRAPPER(UBRRH_Reg, Ubrrh, uint8_t);\
};
// ���� � ��� ���� USART

#ifdef UDR //the one usart
DECLARE_HW_USART(Usart0Regs, UDR, UCSRA, UCSRB, UCSRC, UBRRL, UBRRH)
#endif
// ���� ���
// ��� �������
#ifdef UDR0 //first usart
DECLARE_HW_USART(Usart0Regs, UDR0, UCSR0A, UCSR0B, UCSR0C, UBRR0L, UBRR0H)
#endif
// ��� �������
#ifdef UDR1 //second usart
DECLARE_HW_USART(Usart1Regs, UDR1, UCSR1A, UCSR1B, UCSR1C, UBRR1L, UBRR1H)
#endif

// USART �� ����������� � ���������� �������� �� ����� � ��������.
// TxSize - ������ ������ ��������
// RxSize - ������ ������ �����
// Regs ��� � ������� ���������� ������ ������ ��������� USART

struct Usart0Regs
{
    static struct Ucsrb
    {
        void Set(int TxSize) {}
    };

};

template<int TxSize, int RxSize, class Regs = Usart0Regs>
class Usart
{
public:
    static inline void EnableTxRx()
    {
        Regs::Ucsrb::Set(0x00);
        Regs::Ucsrc::Set(ursel | (1 << UCSZ1) | (1 << UCSZ0));
        Regs::Ucsrb::Set((1 << RXCIE) | (0 << TXCIE) | (1 << UDRIE) | (1 << RXEN) | (1 << TXEN));
    }

    template<unsigned long baund>
    static inline void SetBaundRate()
    {
        const unsigned int ubrr = (F_CPU / 16 / baund - 1);
        const unsigned int ubrr2x(F_CPU / 8 / baund - 1);
        const unsigned long rbaund = (F_CPU / 16 / (ubrr + 1));
        const unsigned long rbaund2x(F_CPU / 8 / (ubrr2x + 1));

        unsigned long err1;
        if (baund > rbaund)
            err1 = (baund - rbaund) * 1000 / baund;
        else
            err1 = (rbaund - baund) * 1000 / rbaund;

        unsigned long err2;
        if (baund > rbaund2x)
            err2 = (baund - rbaund2x) * 1000 / baund;
        else
            err2 = (rbaund2x - baund) * 1000 / rbaund2x;

        unsigned int ubrrToUse;
        if (err1 > err2)
        {
            Regs::Ucsra::Set(1 << U2X);
            ubrrToUse = ubrr2x;
        }
        else
        {
            Regs::Ucsra::Set(0x00);
            ubrrToUse = ubrr;
        }
        Regs::Ubrrl::Set(ubrrToUse);
        Regs::Ubrrh::Set(ubrrToUse >> 8);
    }

    template<unsigned long baund>
    static inline void Init()
    {
        SetBaundRate<baund>();
        EnableTxRx();
    }
    // ��������� ����
    // ���������� true ���� ���� ������� � ������ ��� ���������,
    // ���� ����� ����� - false
    static bool Putch(uint8_t c)
    {
        if (_tx.IsEmpty())
        {
            while (!Regs::Ucsra::template BitIsSet<(UDRE)>());
            Regs::Udr::Set(c);
            Regs::Ucsrb::Or(1 << UDRIE);
            return true;
        }
        else
            return _tx.Write(c);
    }
    // ��������� ����
    // ���������� true ���� ���� ��������
    static bool Getch(uint8_t& c)
    {
        return _rx.Read(c);
    }
    // ���������� ���������� �� �������� �����
    // ������ ���������� �� USART_UDRE_vect
    static inline void TxHandler()
    {
        uint8_t c;
        if (_tx.Read(c))
            Regs::Udr::Set(c);
        else
            Regs::Ucsrb::And(~(1 << UDRIE));
    }
    // ���������� ���������� �� ����� �����
    // ������ ���������� �� USART_RXC_vect
    static inline void RxHandler()
    {
        if (!_rx.Write(Regs::Udr::Get()))//buffer overlow
        {
            //TODO: error handling
            _rx.Clear();
        }
    }

    static void DropBuffers()
    {
        _rx.Clear();
    }

    static void Disable()
    {
        Regs::Ucsra::Set(0);
        Regs::Ucsrb::Set(0);
        Regs::Ucsrc::Set(ursel | 0);
        Regs::Ubrrl::Set(0);
        Regs::Ubrrh::Set(0);

        _rx.Clear();
        _tx.Clear();
    }

    static uint8_t BytesRecived()
    {
        return _rx.Count();
    }
private:
    static RingBuffer<RxSize> _rx;
    static RingBuffer<TxSize> _tx;
};

template<int TxSize, int RxSize, class Regs>
RingBuffer<RxSize> Usart<TxSize, RxSize, Regs>::_rx;
template<int TxSize, int RxSize, class Regs>
RingBuffer<TxSize> Usart<TxSize, RxSize, Regs>::_tx;


// 8 bytes tx fifo buffer, 
// 16 bytes rx fifo buffer
// interrupt driven USART
typedef Usart<16, 16> usart;
//
//ISR(USART_UDRE_vect)
//{
//    usart::TxHandler();
//}
//
//ISR(USART_RXC_vect)
//{
//    usart::RxHandler();
//}

void ex2()
{
    usart::Init<115200>();
    uint8_t c;
    while (1)
    {
        // echo recived data back
        if (usart::Getch(c))
            usart::Putch(c);
    }
}