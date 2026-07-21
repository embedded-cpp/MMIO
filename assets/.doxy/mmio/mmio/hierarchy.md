
# Class Hierarchy

This inheritance list is sorted roughly, but not completely, alphabetically:


* **class** [**mmio::field**](classmmio_1_1field.md) _Represents a specific bit-field within a register._ 
* **class** [**mmio::reg**](classmmio_1_1reg.md) _Represents a memory-mapped hardware register._ 
* **struct** [**mmio::no\_access**](structmmio_1_1no__access.md) _Tag type for no access registers._ 
* **struct** [**mmio::read\_only**](structmmio_1_1read__only.md) _Tag type for read-only registers._     
    * **struct** [**mmio::read\_write**](structmmio_1_1read__write.md) _Tag type for read-write registers Inherits from both_ [_**read\_only**_](structmmio_1_1read__only.md) _and_[_**write\_only**_](structmmio_1_1write__only.md) _._
    * **struct** [**mmio::write\_1\_to\_clear**](structmmio_1_1write__1__to__clear.md) _Tag type for write-1-to-clear registers._ 
* **struct** [**mmio::write\_only**](structmmio_1_1write__only.md) _Tag type for write-only registers._     
    * **struct** [**mmio::read\_write**](structmmio_1_1read__write.md) _Tag type for read-write registers Inherits from both_ [_**read\_only**_](structmmio_1_1read__only.md) _and_[_**write\_only**_](structmmio_1_1write__only.md) _._
* **struct** [**mmio::size\_trait**](structmmio_1_1size__trait.md) _Base trait for the size of the register._ 
* **struct** [**mmio::size\_trait&lt; BITS\_16 &gt;**](structmmio_1_1size__trait_3_01BITS__16_01_4.md) _Specialization of the base trait for 16-bit register._ 
* **struct** [**mmio::size\_trait&lt; BITS\_32 &gt;**](structmmio_1_1size__trait_3_01BITS__32_01_4.md) _Specialization of the base trait for 32-bit register._ 
* **struct** [**mmio::size\_trait&lt; BITS\_64 &gt;**](structmmio_1_1size__trait_3_01BITS__64_01_4.md) _Specialization of the base trait for 64-bit register._ 
* **struct** [**mmio::size\_trait&lt; BITS\_8 &gt;**](structmmio_1_1size__trait_3_01BITS__8_01_4.md) _Specialization of the base trait for 8-bit register._ 

