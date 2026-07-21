

# Class mmio::reg

**template &lt;std::uintptr\_t Addr, std::size\_t BitSize, access\_policy AccessPolicy&gt;**



[**ClassList**](annotated.md) **>** [**mmio**](namespacemmio.md) **>** [**reg**](classmmio_1_1reg.md)



_Represents a memory-mapped hardware register._ [More...](#detailed-description)

* `#include <mmio.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef AccessPolicy | [**policy**](#typedef-policy)  <br>_Access policy alias._  |
| typedef [**size\_trait**](structmmio_1_1size__trait.md)&lt; BitSize &gt;::type | [**value\_type**](#typedef-value_type)  <br>_Underlying integer type (e.g., uint32\_t)_  |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  std::uintptr\_t | [**ADDRESS**](#variable-address)   = `Addr`<br>_Physical address._  |
|  std::size\_t | [**BIT\_SIZE**](#variable-bit_size)   = `BitSize`<br>_Register width in bits._  |














## Public Functions

| Type | Name |
| ---: | :--- |
|  [**reg**](classmmio_1_1reg.md) & | [**operator=**](#function-operator) (const [**reg**](classmmio_1_1reg.md) &) = delete<br> |
|  [**reg**](classmmio_1_1reg.md) & | [**operator=**](#function-operator_1) ([**reg**](classmmio_1_1reg.md) &&) = delete<br> |
|   | [**reg**](#function-reg-13) () = delete<br> |
|   | [**reg**](#function-reg-23) (const [**reg**](classmmio_1_1reg.md) &) = delete<br> |
|   | [**reg**](#function-reg-33) ([**reg**](classmmio_1_1reg.md) &&) = delete<br> |
|   | [**~reg**](#function-reg) () = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**modify**](#function-modify) (F && func) <br>_Modifies the register value using a Read-Modify-Write (RMW) cycle._  |
|  [**value\_type**](classmmio_1_1reg.md#typedef-value_type) | [**read**](#function-read) () noexcept<br>_Reads the full value of the register._  |
|  void | [**write**](#function-write-12) ([**value\_type**](classmmio_1_1reg.md#typedef-value_type) val) noexcept<br>_Writes a value to the register._  |
|  void | [**write**](#function-write-22) ([**value\_type**](classmmio_1_1reg.md#typedef-value_type) val) noexcept<br>_Writes a value to the register, clearing bits that are set to 1._  |
|  void | [**write\_set**](#function-write_set) () noexcept<br>_Writes multiple bit-fields simultaneously in a single hardware operation._  |


























## Detailed Description


This class is a zero-overhead wrapper around a specific memory address. It enforces access policies (Read-Only, Write-Only, Read-Write) and data width constraints at compile time using C++20 concepts.




**Template parameters:**


* `Addr` The physical base address of the register. 
* `BitSize` The width of the register in bits (e.g., 8, 16, 32, 64). 
* `AccessPolicy` The access permission policy (ro, wo, rw, etc..). 




    
## Public Types Documentation




### typedef policy 

_Access policy alias._ 
```C++
using mmio::reg< Addr, BitSize, AccessPolicy >::policy =  AccessPolicy;
```




<hr>



### typedef value\_type 

_Underlying integer type (e.g., uint32\_t)_ 
```C++
using mmio::reg< Addr, BitSize, AccessPolicy >::value_type =  size_trait<BitSize>::type;
```




<hr>
## Public Static Attributes Documentation




### variable ADDRESS 

_Physical address._ 
```C++
std::uintptr_t mmio::reg< Addr, BitSize, AccessPolicy >::ADDRESS;
```




<hr>



### variable BIT\_SIZE 

_Register width in bits._ 
```C++
std::size_t mmio::reg< Addr, BitSize, AccessPolicy >::BIT_SIZE;
```




<hr>
## Public Functions Documentation




### function operator= 

```C++
reg & mmio::reg::operator= (
    const reg &
) = delete
```




<hr>



### function operator= 

```C++
reg & mmio::reg::operator= (
    reg &&
) = delete
```




<hr>



### function reg [1/3]

```C++
mmio::reg::reg () = delete
```




<hr>



### function reg [2/3]

```C++
mmio::reg::reg (
    const reg &
) = delete
```




<hr>



### function reg [3/3]

```C++
mmio::reg::reg (
    reg &&
) = delete
```




<hr>



### function ~reg 

```C++
mmio::reg::~reg () = delete
```




<hr>
## Public Static Functions Documentation




### function modify 

_Modifies the register value using a Read-Modify-Write (RMW) cycle._ 
```C++
template<typename F>
static inline void mmio::reg::modify (
    F && func
) 
```



This function reads the current value, applies the provided callable transformation, and writes the result back.




**Note:**

This operation is NOT atomic regarding interrupts or multi-threading. If the register is shared, external locking is required.




**Template parameters:**


* `F` Callable type (e.g., lambda) with signature `void( value_type &)`. 



**Parameters:**


* `func` The callable that modifies the value in-place. 




        

<hr>



### function read 

_Reads the full value of the register._ 
```C++
static inline value_type mmio::reg::read () noexcept
```





**Note:**

This operation performs a volatile load from memory. 




**Returns:**

The current value of the register. 





        

<hr>



### function write [1/2]

_Writes a value to the register._ 
```C++
static inline void mmio::reg::write (
    value_type val
) noexcept
```





**Note:**

This operation performs a volatile store to memory. It overwrites the entire content of the register.




**Parameters:**


* `val` The value to write. 




        

<hr>



### function write [2/2]

_Writes a value to the register, clearing bits that are set to 1._ 
```C++
static inline void mmio::reg::write (
    value_type val
) noexcept
```





**Note:**

This operation performs a volatile store to memory. It overwrites the entire content of the register.




**Warning:**

This method is only meaningful for registers with a Write-1-to-Clear (W1C) policy. Writing a '1' will clear the corresponding bit, while writing '0' has no effect.




**Parameters:**


* `val` The value to write. 




        

<hr>



### function write\_set 

_Writes multiple bit-fields simultaneously in a single hardware operation._ 
```C++
template<typename... Fields>
static inline void mmio::reg::write_set () noexcept
```



This function leverages Variadic Templates and Fold Expressions (C++17) to calculate a merged global mask at compile-time. It ensures that only a single write instruction (STORE) is generated to configure all specified fields.




**Template parameters:**


* `Fields` A list of `mmio::field` or `mmio::bit` types belonging exclusively to this register.



**Note:**

**Optimization:** The expression `(Fields::mask | ...)` is entirely resolved by the compiler. The resulting machine code is typically reduced to an immediate constant load followed by a memory transfer, which is the fastest operation possible.




**Warning:**

**Destructive Behavior:** Since this function calls `write()`, ALL register bits not included in the provided `Fields` types will be cleared to zero (0).
* To preserve other bits in the register, use `modify()` (Read-Modify-Write).
* For a clean initial configuration (Cold Boot), `write_set` is the ideal choice.






**Precondition:**

The register must have a `writable` access policy. 




**Precondition:**

All `Fields` must be compatible with the register's `value_type`. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `mmio/mmio.hpp`

