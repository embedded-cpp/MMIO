

# Namespace mmio



[**Namespace List**](namespaces.md) **>** [**mmio**](namespacemmio.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**field**](classmmio_1_1field.md) &lt;typename Register, Offset, Width&gt;<br>_Represents a specific bit-field within a register._  |
| struct | [**no\_access**](structmmio_1_1no__access.md) <br>_Tag type for no access registers._  |
| struct | [**read\_only**](structmmio_1_1read__only.md) <br>_Tag type for read-only registers._  |
| struct | [**read\_write**](structmmio_1_1read__write.md) <br>_Tag type for read-write registers Inherits from both_ [_**read\_only**_](structmmio_1_1read__only.md) _and_[_**write\_only**_](structmmio_1_1write__only.md) _._ |
| class | [**reg**](classmmio_1_1reg.md) &lt;Addr, BitSize, AccessPolicy&gt;<br>_Represents a memory-mapped hardware register._  |
| struct | [**size\_trait**](structmmio_1_1size__trait.md) &lt;BitSize&gt;<br>_Base trait for the size of the register._  |
| struct | [**size\_trait&lt; BITS\_16 &gt;**](structmmio_1_1size__trait_3_01BITS__16_01_4.md) &lt;&gt;<br>_Specialization of the base trait for 16-bit register._  |
| struct | [**size\_trait&lt; BITS\_32 &gt;**](structmmio_1_1size__trait_3_01BITS__32_01_4.md) &lt;&gt;<br>_Specialization of the base trait for 32-bit register._  |
| struct | [**size\_trait&lt; BITS\_64 &gt;**](structmmio_1_1size__trait_3_01BITS__64_01_4.md) &lt;&gt;<br>_Specialization of the base trait for 64-bit register._  |
| struct | [**size\_trait&lt; BITS\_8 &gt;**](structmmio_1_1size__trait_3_01BITS__8_01_4.md) &lt;&gt;<br>_Specialization of the base trait for 8-bit register._  |
| struct | [**write\_1\_to\_clear**](structmmio_1_1write__1__to__clear.md) <br>_Tag type for write-1-to-clear registers._  |
| struct | [**write\_only**](structmmio_1_1write__only.md) <br>_Tag type for write-only registers._  |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**field**](classmmio_1_1field.md)&lt; Register, Offset, 1 &gt; | [**bit**](#typedef-bit)  <br>_Convenient alias for a single-bit field._  |
| typedef [**no\_access**](structmmio_1_1no__access.md) | [**na**](#typedef-na)  <br> |
| typedef [**read\_only**](structmmio_1_1read__only.md) | [**ro**](#typedef-ro)  <br> |
| typedef [**read\_write**](structmmio_1_1read__write.md) | [**rw**](#typedef-rw)  <br> |
| typedef [**write\_1\_to\_clear**](structmmio_1_1write__1__to__clear.md) | [**w1c**](#typedef-w1c)  <br> |
| typedef [**write\_only**](structmmio_1_1write__only.md) | [**wo**](#typedef-wo)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**BITS\_16**](#variable-bits_16)   = `16U`<br>_Compile-time constant for number of bits in an 16-bit value._  |
|  std::size\_t | [**BITS\_32**](#variable-bits_32)   = `32U`<br>_Compile-time constant for number of bits in an 32-bit value._  |
|  std::size\_t | [**BITS\_64**](#variable-bits_64)   = `64U`<br>_Compile-time constant for number of bits in an 64-bit value._  |
|  std::size\_t | [**BITS\_8**](#variable-bits_8)   = `8U`<br>_Compile-time constant for number of bits in an 8-bit value._  |












































## Public Types Documentation




### typedef bit 

_Convenient alias for a single-bit field._ 
```C++
using mmio::bit =  field<Register, Offset, 1>;
```




<hr>



### typedef na 

```C++
using mmio::na =  no_access;
```




<hr>



### typedef ro 

```C++
using mmio::ro =  read_only;
```




<hr>



### typedef rw 

```C++
using mmio::rw =  read_write;
```




<hr>



### typedef w1c 

```C++
using mmio::w1c =  write_1_to_clear;
```




<hr>



### typedef wo 

```C++
using mmio::wo =  write_only;
```




<hr>
## Public Attributes Documentation




### variable BITS\_16 

_Compile-time constant for number of bits in an 16-bit value._ 
```C++
std::size_t mmio::BITS_16;
```




<hr>



### variable BITS\_32 

_Compile-time constant for number of bits in an 32-bit value._ 
```C++
std::size_t mmio::BITS_32;
```




<hr>



### variable BITS\_64 

_Compile-time constant for number of bits in an 64-bit value._ 
```C++
std::size_t mmio::BITS_64;
```




<hr>



### variable BITS\_8 

_Compile-time constant for number of bits in an 8-bit value._ 
```C++
std::size_t mmio::BITS_8;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `mmio/mmio.hpp`

