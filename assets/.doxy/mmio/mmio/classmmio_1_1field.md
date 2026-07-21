

# Class mmio::field

**template &lt;typename Register, std::size\_t Offset, std::size\_t Width&gt;**



[**ClassList**](annotated.md) **>** [**mmio**](namespacemmio.md) **>** [**field**](classmmio_1_1field.md)



_Represents a specific bit-field within a register._ [More...](#detailed-description)

* `#include <mmio.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef Register::policy | [**policy**](#typedef-policy)  <br>_Access policy alias from the parent register._  |
| typedef Register | [**register\_type**](#typedef-register_type)  <br>_Type alias for the parent register._  |
| typedef Register::value\_type | [**value\_type**](#typedef-value_type)  <br>_Underlying integer type (e.g., uint32\_t)_  |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**value\_type**](classmmio_1_1field.md#typedef-value_type) | [**MASK**](#variable-mask)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**field**](#function-field-13) () = delete<br> |
|   | [**field**](#function-field-23) (const [**field**](classmmio_1_1field.md) &) = delete<br> |
|   | [**field**](#function-field-33) ([**field**](classmmio_1_1field.md) &&) = delete<br> |
|  [**field**](classmmio_1_1field.md) & | [**operator=**](#function-operator) (const [**field**](classmmio_1_1field.md) &) = delete<br> |
|  [**field**](classmmio_1_1field.md) & | [**operator=**](#function-operator_1) ([**field**](classmmio_1_1field.md) &&) = delete<br> |
|   | [**~field**](#function-field) () = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**clear**](#function-clear-13) () noexcept<br>_Clears the bit to 0 (Read-Write Policy). Uses RMW to preserve other bits in the register._  |
|  void | [**clear**](#function-clear-23) () noexcept<br>_Clears the bit to 0 (Write-Only Policy)._  |
|  void | [**clear**](#function-clear-33) () noexcept<br>_Clears the bit to 0 (Write-1-to-Clear Policy)._  |
|  bool | [**is\_clear**](#function-is_clear) () noexcept<br>_Check if a bit is clear (0)_  |
|  bool | [**is\_set**](#function-is_set) () noexcept<br>_Check if a bit is set (1)_  |
|  void | [**modify**](#function-modify) (F && func) <br>_Modifies the field value in-place._  |
|  [**value\_type**](classmmio_1_1field.md#typedef-value_type) | [**read**](#function-read) () noexcept<br>_Reads and extracts the field value._  |
|  void | [**set**](#function-set-12) () noexcept<br>_Sets the bit to 1 (Read-Write Policy). Uses RMW to preserve other bits in the register._  |
|  void | [**set**](#function-set-22) () noexcept<br>_Sets the bit to 1 (Write-Only Policy)._  |
|  void | [**toggle**](#function-toggle) () noexcept<br>_Toggles the bit value (0-&gt;1 or 1-&gt;0)._  |
|  void | [**write**](#function-write-13) ([**value\_type**](classmmio_1_1field.md#typedef-value_type) val) noexcept<br>_Writes a value to the field (Read-Write Policy)._  |
|  void | [**write**](#function-write-23) ([**value\_type**](classmmio_1_1field.md#typedef-value_type) val) noexcept<br>_Writes a value to the field (Write-Only Policy)._  |
|  void | [**write**](#function-write-33) ([**value\_type**](classmmio_1_1field.md#typedef-value_type) val) noexcept<br>_Writes a value to the field (Write-1-to-Clear Policy)._  |


























## Detailed Description


Provides safer manipulation of sub-sections of a register by handling bit-shifting and masking automatically.




**Template parameters:**


* `Register` The parent `reg` class. 
* `Offset` The starting bit position (LSB index) of the field. 
* `Width` The width of the field in bits. 




    
## Public Types Documentation




### typedef policy 

_Access policy alias from the parent register._ 
```C++
using mmio::field< Register, Offset, Width >::policy =  Register::policy;
```




<hr>



### typedef register\_type 

_Type alias for the parent register._ 
```C++
using mmio::field< Register, Offset, Width >::register_type =  Register;
```




<hr>



### typedef value\_type 

_Underlying integer type (e.g., uint32\_t)_ 
```C++
using mmio::field< Register, Offset, Width >::value_type =  Register::value_type;
```




<hr>
## Public Static Attributes Documentation




### variable MASK 

```C++
value_type mmio::field< Register, Offset, Width >::MASK;
```




<hr>
## Public Functions Documentation




### function field [1/3]

```C++
mmio::field::field () = delete
```




<hr>



### function field [2/3]

```C++
mmio::field::field (
    const field &
) = delete
```




<hr>



### function field [3/3]

```C++
mmio::field::field (
    field &&
) = delete
```




<hr>



### function operator= 

```C++
field & mmio::field::operator= (
    const field &
) = delete
```




<hr>



### function operator= 

```C++
field & mmio::field::operator= (
    field &&
) = delete
```




<hr>



### function ~field 

```C++
mmio::field::~field () = delete
```




<hr>
## Public Static Functions Documentation




### function clear [1/3]

_Clears the bit to 0 (Read-Write Policy). Uses RMW to preserve other bits in the register._ 
```C++
static inline void mmio::field::clear () noexcept
```




<hr>



### function clear [2/3]

_Clears the bit to 0 (Write-Only Policy)._ 
```C++
static inline void mmio::field::clear () noexcept
```



Writes 0 to the entire register.




**Warning:**

**DESTRUCTIVE**: effectively resets the whole register to 0. 





        

<hr>



### function clear [3/3]

_Clears the bit to 0 (Write-1-to-Clear Policy)._ 
```C++
static inline void mmio::field::clear () noexcept
```




<hr>



### function is\_clear 

_Check if a bit is clear (0)_ 
```C++
static inline bool mmio::field::is_clear () noexcept
```





**Note:**

Requires Read-Only access. 




**Returns:**

true if the bit is clear, false otherwise. 





        

<hr>



### function is\_set 

_Check if a bit is set (1)_ 
```C++
static inline bool mmio::field::is_set () noexcept
```





**Note:**

Requires Read-Only access. 




**Returns:**

true if the bit is set, false otherwise. 





        

<hr>



### function modify 

_Modifies the field value in-place._ 
```C++
template<typename F>
static inline void mmio::field::modify (
    F && func
) 
```



Extracts the current field value, passes it to the user-provided function, and writes the updated value back.




**Note:**

Requires Read-Write access.




**Template parameters:**


* `F` Callable type with signature `void( value_type &)`. 



**Parameters:**


* `func` The callable that transforms the field value. 




        

<hr>



### function read 

_Reads and extracts the field value._ 
```C++
static inline value_type mmio::field::read () noexcept
```



Reads the full register, applies the mask, and shifts the result down to index 0.




**Returns:**

The extracted field value. 





        

<hr>



### function set [1/2]

_Sets the bit to 1 (Read-Write Policy). Uses RMW to preserve other bits in the register._ 
```C++
static inline void mmio::field::set () noexcept
```




<hr>



### function set [2/2]

_Sets the bit to 1 (Write-Only Policy)._ 
```C++
static inline void mmio::field::set () noexcept
```





**Warning:**

**DESTRUCTIVE**: Writes the MASK directly to the register. All other bits become 0. 





        

<hr>



### function toggle 

_Toggles the bit value (0-&gt;1 or 1-&gt;0)._ 
```C++
static inline void mmio::field::toggle () noexcept
```





**Note:**

Strictly requires Read-Write access, as the new state depends on the previous state. 





        

<hr>



### function write [1/3]

_Writes a value to the field (Read-Write Policy)._ 
```C++
static inline void mmio::field::write (
    value_type val
) noexcept
```



Performs a Read-Modify-Write cycle:
* Reads the register.
* Clears the bits corresponding to this field.
* Sets the new value for this field.
* Writes the result back.






**Note:**

This preserves the state of all other bits (neighbors) in the register. 




**Parameters:**


* `val` The value to write (will be masked and shifted automatically). 




        

<hr>



### function write [2/3]

_Writes a value to the field (Write-Only Policy)._ 
```C++
static inline void mmio::field::write (
    value_type val
) noexcept
```



Performs a Direct Write. Since the register cannot be read, it is impossible to preserve the neighbors.




**Warning:**

**DESTRUCTIVE OPERATION**: All other bits in the register will be set to 0. This is typically used for command or trigger registers where neighbors are irrelevant or reserved.




**Parameters:**


* `val` The value to write (will be masked and shifted automatically). 




        

<hr>



### function write [3/3]

_Writes a value to the field (Write-1-to-Clear Policy)._ 
```C++
static inline void mmio::field::write (
    value_type val
) noexcept
```



For fields that clear on write (W1C), writing a '1' will clear the bit, while writing '0' has no effect. This method allows setting bits to be cleared without affecting other bits in the register.




**Parameters:**


* `val` The value to write (only bits set to '1' will be cleared). 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `mmio/mmio.hpp`

