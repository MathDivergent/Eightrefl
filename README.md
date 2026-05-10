# Eightrefl

![Type](https://img.shields.io/badge/type-engine%20module-%235a6770)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Platforms](https://img.shields.io/badge/platforms-Windows%20%7C%20Linux%20%7C%20macOS-red)
![Tests](https://img.shields.io/badge/tests-automated-yellow)
[![License: MIT](https://img.shields.io/badge/license-MIT-green)](https://opensource.org/license/mit)

**Eightrefl** is a reflection library for C++20 that provides full type introspection **without requiring changes to reflected class code in typical external-reflection workflows**. It is an external module of the [Eightgine](https://github.com/MathDivergent/Eightgine) engine.

See last stable library version 3.1.3 [here](https://github.com/MathDivergent/Eightrefl/releases).

---

## Contents

- [Core principles](#core-principles)
- [Architecture](#architecture)
  - [Interaction model](#interaction-model)
  - [Data structures](#data-structures)
- [Quick start](#quick-start)
- [Reflection macros](#reflection-macros)
  - [Reflection declaration](#reflection-declaration)
  - [Reflection body](#reflection-body)
  - [Reflection table macros](#reflection-table-macros)
- [Registry (registry_t)](#registry-registry_t)
- [backward / forward](#backward--forward)
- [Injection (injectable_t)](#injection-injectable_t)
- [Clean and Dirty reflection](#clean-and-dirty-reflection)
- [Lazy Evaluate](#lazy-evaluate)
- [Built-in reflections](#built-in-reflections)
- [Configuration](#configuration)
- [Extended documentation](#extended-documentation)
- [Auto Tests](#auto-tests)
- [Upcoming](#upcoming)
- [License](#license)

---

## Core principles

1. **External reflection** — no need to modify the reflected type. Reflection is described in separate external files. Reflecting private / protected members may still require adding `REFLECTABLE_ACCESS()` inside the reflected class.
2. **Declaration/definition split** — the declaration (`xxeightrefl_traits` from the `#include <Eightrefl/CoreDeclaration.hpp>`) is placed in a `.hpp` file, while the reflection body (`xxeightrefl` from the `#include <Eightrefl/Core.hpp>`) is usually placed in a `.cpp` file (and in a `.hpp` file for lazy/template reflection scenarios).
3. **Standard C++20** — no code generators or custom preprocessors.
4. **`std::any` as a unified carrier** — all operations on objects are performed via `std::any`, which avoids compile-time coupling to specific types.

---

## Architecture

---

### Interaction model

```
C++ type  ──(REFLECTABLE_DECLARATION)──►  xxeightrefl_traits<T>   (.hpp)
                                               │  [declares name, registry and other metadata]
                                               ▼
          ──(REFLECTABLE)──────────────►  xxeightrefl<T>          (.cpp / .hpp for lazy)
                                               │  [builds reflection table]
                                               ▼
                                     registry_t → type_t*  [lookup entry]
```

The interaction model is built around several key components that work together to enable external reflection without modifying the reflected types. Below is a detailed analysis of each component based on the library's architecture:

1. **`xxeightrefl_traits<T>`** - This is the declaration of a reflectable type, containing essential information for type identification:
   - **Name**: Can include `xxnative_name` (default type name) and a custom user-defined name.
    - **Registry reference**: Points to the registry where the type is stored (e.g., global, builtin, standard, dev, etc.).
   - **Optional metadata**: Includes flags like lazy evaluation, whether it's part of the standard library, builtin types, or self-reflectable (dev) types.
   - Typically located in header files (.hpp) to allow sharing between other reflectable types during their registration in `xxeightrefl`. It serves as the entry point for type reflection setup.

2. **`xxeightrefl<T>`** - This is the core of type and attribute registration, requiring a prior specialization of `xxeightrefl_traits<T>`:
   - Handles the registration of types and their attributes (including metadata) in the registry.
   - Usually placed in source files (.cpp) as it's not intended for external use from other translation units. However, for lazy registration, it must be defined in header files.
   - Contains the `evaluate` function that populates the type's attributes like factories, functions, properties, parents, etc., using injection mechanisms.

3. **`registry_t`** - Acts as the storage for registered types, managed both automatically (via `fixture_of`) and manually (via `reflectable`):
   - Provides an interface for adding and reading types; deletion is undefined behavior (UB).
   - Stores and owns pointers to `type_t`, so expanding the storage with potential reallocation does not affect type integrity.
    - Supports multiple registries (global, builtin, standard, dev, etc.) for subsystem isolation.

4. **`type_t`** - Represents a composition and aggregation of metadata and type information:
   - Includes attributes like `injection_t`, `child_t`, `parent_t`, `factory_t`, `function_t`, `property_t`, `deleter_t`, `meta_t`.
   - Contains core type info: name, registry, size, context function.
   - Is a readonly type except for `attribute_t` fields, which support add/read operations.
   - Architecturally cannot exist without a name and registry; all other fields are optional.

<details>
<summary><strong>implementation details</strong></summary>

5. **Functions like `find_or_add_*`** - Used exclusively for extending type attributes or metadata. Direct use for searching is valid but not entirely correct; the "find" in the name implies applying injections to attributes or metadata to avoid complete recreation and loss of previous injections.

6. **`xxeightrefl_dirty_traits<T>`** - Enables reflection of types that cannot be deduced from context (e.g., nested types in class templates) or when re-reflection with different type info and attributes is needed.

</details>

<details>
<summary><strong>reflectable declaration synopsis</strong></summary>

```cpp
#define REFLECTABLE_DECLARATION(... /*reflectable_type*/) /*...*/
#define TEMPLATE_REFLECTABLE_DECLARATION(reflectable_type_template_header, ... /*reflectable_type_template*/) /*...*/
#define CONDITIONAL_REFLECTABLE_DECLARATION(... /*reflectable_type_condition*/) /*...*/

#define REFLECTABLE_REGISTRY(... /*reflectable_registry_pointer*/) /*...*/
#define REFLECTABLE_NAME(... /*reflectable_name_string*/) /*...*/
#define REFLECTABLE_LAZY_EVALUATE() /*...*/

#define REFLECTABLE_DECLARATION_INIT() /*...*/

#define REFLECTABLE_ACCESS() /*...*/


namespace eightrefl
{

template <typename DirtyReflectableType>
std::string name_of();

template <typename DirtyReflectableType>
registry_t* registry_of();

template <typename DirtyReflectableType>
type_t* type_of();

} // namespace eightrefl
```

<details>
<summary><strong>reflectable declaration traits synopsis</strong></summary>

```cpp
template <typename ReflectableType, typename enable = void>
struct xxeightrefl_traits;


template <typename, typename enable = void>
struct xxeightrefl_traits_has_reflectable_name;

template <typename, typename enable = void>
struct xxeightrefl_traits_has_reflectable_registry;

template <typename, typename enable = void>
struct xxeightrefl_traits_has_reflectable_lazy_evaluate;
```

</details>


```cpp
#define REFLECTABLE_CLEAN(dirty_type, ... /*clean_reflectable_type*/) /*...*/
#define TEMPLATE_REFLECTABLE_CLEAN(dirty_type_template_header, dirty_type_template, ... /*clean_reflectable_type_template*/) /*...*/

#define REFLECTABLE_DIRTY(dirty_type, ... /*clean_reflectable_type*/) /*...*/
#define TEMPLATE_REFLECTABLE_DIRTY(dirty_type_template_header, dirty_type, dirty_type_template, ... /*clean_reflectable_type_template*/) /*...*/


namespace eightrefl
{

template <typename DirtyReflectableType>
using clean_of = /*...*/;

} // namespace eightrefl
```

<details>
<summary><strong>reflectable dirty traits synopsis</strong></summary>

```cpp
template <typename ReflectableType, typename enable = void>
struct xxeightrefl_dirty_traits;


template <typename ReflectableType>
struct xxeightrefl_enable_dirty;


template <typename MemberPointerType, typename DirtyMemberPointerType = void>
struct xxeightrefl_mark_dirty;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const>;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const, DirtyReturnType(DirtyArgumentTypes...) const>;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const&>;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const&, DirtyReturnType(DirtyArgumentTypes...) const&>;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...)>;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...), DirtyReturnType(DirtyArgumentTypes...)>;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...)&>;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...)&, DirtyReturnType(DirtyArgumentTypes...)&>;

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(*)(ArgumentTypes...)>;

template <typename ReturnType, typename... ArgumentTypes,
          typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(*)(ArgumentTypes...), DirtyReturnType(DirtyArgumentTypes...)>;

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_mark_dirty<PropertyType ReflectableType::*>;

template <typename ReflectableType, typename PropertyType, typename DirtyPropertyType>
struct xxeightrefl_mark_dirty<PropertyType ReflectableType::*, DirtyPropertyType>;

template <typename PropertyType>
struct xxeightrefl_mark_dirty<PropertyType*>;

template <typename PropertyType, typename DirtyPropertyType>
struct xxeightrefl_mark_dirty<PropertyType*, DirtyPropertyType>;
```

</details>

</details>

<details>
<summary><strong>reflectable registration synopsis</strong></summary>

```cpp
#define REFLECTABLE(... /*reflectable_type*/) \
#define TEMPLATE_REFLECTABLE(reflectable_type_template_header, ... /*reflectable_type_template*/) /*...*/
#define CONDITIONAL_REFLECTABLE(... /*reflectable_type_condition*/) /*...*/

#define REFLECTABLE_INIT() /*...*/


template <typename ReflectableType, typename enable = void>
struct xxeightrefl;


namespace eightrefl
{

template <typename DirtyReflectableType>
void reflectable();

template <typename ReflectableType>
ReflectableType&& reflectable(ReflectableType&& object);


template <typename ReflectableType>
bool fixture_of();

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename DirtyReflectableType>
type_t* find_or_add_type();

template <typename DirtyReflectableType,
          class InjectionType>
type_t* find_or_add_type(InjectionType& injection);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename ReflectableType, typename DirtyReflectableParentType>
parent_t* find_or_add_parent(type_t* type);

template <typename ReflectableType, typename DirtyReflectableParentType,
          class InjectionType>
parent_t* find_or_add_parent(type_t* type, InjectionType& injection);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename DirtyFactoryType>
factory_t* find_or_add_factory(type_t* type);

template <typename ReflectableType,
          typename DirtyFactoryType,
          class InjectionType>
factory_t* find_or_add_factory(type_t* type, InjectionType& injection);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename DirtyFunctionType = void, typename FunctionTypePointer>
function_t* find_or_add_function(type_t* type, std::string const& name, FunctionTypePointer pointer);

template <typename ReflectableType,
          typename DirtyFunctionType = void, typename FunctionTypePointer,
          class InjectionType>
function_t* find_or_add_function(type_t* type, std::string const& name, FunctionTypePointer pointer, InjectionType& injection);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename IODirtyType = void, typename ODirtyType = void /*unused*/,
          typename ITypePointer, typename OTypePointer>
property_t* find_or_add_property(type_t* type, std::string const& name, ITypePointer ipointer, OTypePointer opointer);

template <typename ReflectableType,
          typename IODirtyType = void, typename ODirtyType = void,
          typename ITypePointer, typename OTypePointer,
          class InjectionType>
property_t* find_or_add_property(type_t* type, std::string const& name, ITypePointer ipointer, OTypePointer opointer, InjectionType& injection);


template <typename BitfieldType>
property_t* find_or_add_bitfield(type_t* type, std::string const& name,
                                 std::function<std::any(std::any const&)> ihandler,
                                 std::function<void(std::any const&, std::any const&)> ohandler);

template <typename ReflectableType,
          typename BitfieldType,
          class InjectionType>
property_t* find_or_add_bitfield(type_t* type, std::string const& name,
                                 std::function<std::any(std::any const&)> ihandler,
                                 std::function<void(std::any const&, std::any const&)> ohandler,
                                 InjectionType& injection);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename DirtyDeleterType>
deleter_t* find_or_add_deleter(type_t* type);

template <typename ReflectableType,
          typename DirtyDeleterType,
          class InjectionType>
deleter_t* find_or_add_deleter(type_t* type, InjectionType& injection);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename MetaType>
meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name, MetaType&& value);

template <typename ReflectableType,
          typename MetaType,
          class InjectionType>
meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name, MetaType&& value, InjectionType& injection);

inline meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name);

template <typename ReflectableType,
          class InjectionType>
meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name, InjectionType& injection);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename ReflectableType, class DirtyReflectableInjectionType>
injection_t* find_or_add_injection(type_t* type);

template <typename ReflectableType, class DirtyReflectableInjectionType,
          class InjectionType>
injection_t* find_or_add_injection(type_t* type, InjectionType& injection);

} // namespace eightrefl
```

</details>

---

### Data structures

Each reflected type is stored in a `type_t`; structure synopsis:

```cpp
namespace eightrefl
{

struct EIGHTREFL_API type_t
{
    std::string const name{};                                           // type name (registry key)
    registry_t* const registry = nullptr;                               // registry that owns the type
    std::size_t const size = 0;                                         // sizeof(T), 0 for void
    std::function<std::any(std::any& object)> const context = nullptr;  // extracts T* from std::any

    attribute_t<injection_t> injection{};             // injections
    attribute_t<child_t> child{};                     // child types
    attribute_t<parent_t> parent{};                   // parent types
    attribute_t<factory_t> factory{};                 // constructors
    attribute_t<attribute_t<function_t>> function{};  // functions (name → overloads)
    attribute_t<property_t> property{};               // fields / accessors
    attribute_t<deleter_t> deleter{};                 // destructors
    attribute_t<meta_t> meta{};                       // metadata
};

} // namespace eightrefl
```

<details>
<summary><strong>type_t advance synopsis</strong></summary>

```cpp
namespace eightrefl
{

template <typename ReflectableType>
auto handler_type_context();

template <typename ReflectableType>
auto type_size();

} // namespace eightrefl
```

</details>

`registry_t` structure synopsis:

```cpp
namespace eightrefl
{

struct EIGHTREFL_API registry_t
{
    std::unordered_map<std::string, type_t*> all{};
    #ifdef EIGHTREFL_RTTI_ENABLE
    std::unordered_map<std::type_index, type_t*> rtti_all{};
    #endif // EIGHTREFL_RTTI_ENABLE

    registry_t();
    registry_t(registry_t const&) = delete;
    registry_t(registry_t&&) = delete;
    registry_t& operator=(registry_t const&) = delete;
    registry_t& operator=(registry_t&&) = delete;
    ~registry_t();

    type_t* find(std::string const& name) const;
    #ifdef EIGHTREFL_RTTI_ENABLE
    type_t* find(std::type_index typeindex) const;
    #endif // EIGHTREFL_RTTI_ENABLE

    template <typename ReflectableType, typename DirtyReflectableType = ReflectableType>
    type_t* add(std::string const& name);
};

} // namespace eightrefl
```

<details>
<summary><strong>registry_t advance synopsis</strong></summary>

```cpp
namespace eightrefl
{

extern EIGHTREFL_API registry_t* global();

} // namespace eightrefl
```

</details>

`attribute_t<T>` is a wrapper over `std::unordered_map<std::string, T>` with `find` / `add` functions; structure synopsis:

```cpp
namespace eightrefl
{

template <class ElementType>
struct attribute_t
{
    std::unordered_map<std::string, ElementType> all{};

    attribute_t();
    attribute_t(attribute_t const&) = default;
    attribute_t& operator=(attribute_t const&) = delete;

    ElementType* find(std::string const& name);
    ElementType* add(std::string const& name, ElementType const& element);
};

} // namespace eightrefl
```

Core reflection-table element structures:

| Structure | Key fields |
|-----------|------------|
| `factory_t` | `name`, `call`, `arguments`, `result`, `meta` |
| `function_t` | `name`, `call`, `arguments`, `result`, `pointer`, `meta` |
| `property_t` | `name`, `type`, `get`, `set`, `context`, `pointer`, `meta` |
| `deleter_t` | `name`, `call`, `meta` |
| `parent_t` | `type`, `cast`, `meta` |
| `child_t` | `type`, `cast` |
| `meta_t` | `name`, `value` |
| `injection_t` | `type`, `call` |

<details>
<summary><strong>reflection-table structure synopsis</strong></summary>

`injection_t` structure synopsis:

```cpp
#define INJECTION(... /*reflectable_injection_type*/) /*...*/


namespace eightrefl
{

struct EIGHTREFL_API injection_t
{
    type_t* const type = nullptr;
    std::function<void(std::any const& injectable_context)> const call = nullptr;
    attribute_t<meta_t> meta{};
};

} // namespace eightrefl
```

<details>
<summary><strong>injection_t advance synopsis</strong></summary>

```cpp
namespace eightrefl
{

template <typename ReflectionType, class InjectionType>
auto handler_injection_call();

} // namespace eightrefl
```

</details>

`child_t` structure synopsis:

```cpp
namespace eightrefl
{

struct EIGHTREFL_API child_t
{
    type_t* const type = nullptr;
    std::function<std::any(std::any const& parent_context)> const cast = nullptr;
};

} // namespace eightrefl
```

<details>
<summary><strong>child_t advance synopsis</strong></summary>

```cpp
namespace eightrefl
{

template <typename ReflectableType, typename ChildReflectableType>
auto handler_child_cast();

} // namespace eightrefl
```

</details>

`parent_t` structure synopsis:

```cpp
#define PARENT(... /*reflectable_parent_type*/) /*...*/


namespace eightrefl
{

struct EIGHTREFL_API parent_t
{
    type_t* const type = nullptr;
    std::function<std::any(std::any const& child_context)> const cast = nullptr;
    attribute_t<meta_t> meta{};
};

} // namespace eightrefl
```

<details>
<summary><strong>parent_t advance synopsis</strong></summary>

```cpp
namespace eightrefl
{

template <typename ReflectableType, typename ReflectableParentType>
auto handler_parent_cast();

} // namespace eightrefl
```

</details>

`factory_t` structure synopsis:

```cpp
#define FACTORY(... /*reflectable_function_type*/) /*...*/


namespace eightrefl
{

struct EIGHTREFL_API factory_t
{
    std::string const name{};
    std::function<std::any(std::vector<std::any> const& arguments)> const call = nullptr;
    std::vector<type_t*> const arguments{};
    type_t* const result = nullptr;
    attribute_t<meta_t> meta{};
};

} // namespace eightrefl
```

<details>
<summary><strong>factory_t advance synopsis</strong></summary>

```cpp
namespace eightrefl
{

template <typename ReflectableType, typename... ArgumentTypes>
auto handler_factory_call(ReflectableType(*)(ArgumentTypes...));

} // namespace eightrefl
```

</details>

`function_t` structure synopsis:

```cpp
#define FUNCTION_AS(external_name, internal_name, ... /*reflectable_function_type*/) /*...*/
#define FUNCTION(name, ... /*reflectable_function_type*/) /*...*/

#define EXTERNAL_FUNCTION_AS(external_name, internal_name, ... /*reflectable_function_type*/) /*...*/
#define EXTERNAL_FUNCTION(name, ... /*reflectable_function_type*/) /*...*/


namespace eightrefl
{

struct EIGHTREFL_API function_t
{
    std::string const name{};
    std::function<std::any(std::any const& outer_context, std::vector<std::any> const& arguments)> const call = nullptr;
    std::vector<type_t*> const arguments{};
    type_t* const result = nullptr;
    std::any const pointer{};
    attribute_t<meta_t> meta{};
};

} // namespace eightrefl
```

<details>
<summary><strong>function_t advance synopsis</strong></summary>

```cpp
namespace eightrefl
{

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(ReflectableType::* function)(ArgumentTypes...) const);

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(ReflectableType::* function)(ArgumentTypes...) const&);

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(ReflectableType::* function)(ArgumentTypes...));

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(ReflectableType::* function)(ArgumentTypes...)&);

template <typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(* function)(ArgumentTypes...));

} // namespace eightrefl
```

<details>
<summary><strong>function_t traits synopsis</strong></summary>

```cpp
template <typename>
struct xxeightrefl_function_traits;

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ArgumentTypes...) const>;

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ArgumentTypes...) const&>;

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ArgumentTypes...)>;

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ArgumentTypes...)&>;

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ClassType::*)(ArgumentTypes...) const>;

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ClassType::*)(ArgumentTypes...) const&>;

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ClassType::*)(ArgumentTypes...)>;

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ClassType::*)(ArgumentTypes...)&>;

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(*)(ArgumentTypes...)>;
```

</details>

</details>

`property_t` structure synopsis:

```cpp
#define PROPERTY_AS(external_name, internal_iname, internal_oname, ... /*reflectable_type_or_function_type(s)*/) /*...*/
#define PROPERTY(name, ... /*reflectable_type_or_function_type*/) /*...*/

#define EXTERNAL_PROPERTY_AS(external_name, internal_iname, internal_oname, ... /*reflectable_type_or_function_type(s)*/) /*...*/
#define EXTERNAL_PROPERTY(name, ... /*reflectable_type_or_function_type(s)*/) /*...*/

#define BITFIELD_AS(external_name, internal_name) /*...*/
#define BITFIELD(name) /*...*/


namespace eightrefl
{

struct EIGHTREFL_API property_t
{
    std::string const name{};
    type_t* const type = nullptr;
    std::function<std::any(std::any const& outer_context)> const get = nullptr;
    std::function<void(std::any const& outer_context, std::any const& value)> const set = nullptr;
    std::function<std::any(std::any const& outer_context)> const context = nullptr;
    std::pair<std::any, std::any> const pointer{};
    attribute_t<meta_t> meta{};
};

} // namespace eightrefl
```

<details>
<summary><strong>property_t advance synopsis</strong></summary>

```cpp
namespace eightrefl
{

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType ReflectableType::* property);

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void) const);

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void) const&);

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void));

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void)&);

template <typename PropertyType>
auto handler_property_get(PropertyType* property);

template <typename PropertyType>
auto handler_property_get(PropertyType(* property)(void));

constexpr auto handler_property_get(std::nullptr_t);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType ReflectableType::* property);

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(void(ReflectableType::* property)(PropertyType));

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(void(ReflectableType::* property)(PropertyType)&);

template <typename PropertyType>
auto handler_property_set(PropertyType* property);

template <typename PropertyType>
auto handler_property_set(void(* property)(PropertyType));

constexpr auto handler_property_set(std::nullptr_t);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType ReflectableType::* property);

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void) const);

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void) const&);

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void));

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void)&);

template <typename PropertyType>
auto handler_property_context(PropertyType* property);

template <typename PropertyType>
auto handler_property_context(PropertyType(* property)(void));

constexpr auto handler_property_context(std::nullptr_t);

} // namespace eightrefl
```

```cpp
namespace eightrefl
{

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType ReflectableType::* iproperty, PropertyType ReflectableType::* oproperty);

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void) const, void(ReflectableType::* oproperty)(OPropertyType));

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void) const, void(ReflectableType::* oproperty)(OPropertyType)&);

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void) const&, void(ReflectableType::* oproperty)(OPropertyType));

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void) const&, void(ReflectableType::* oproperty)(OPropertyType)&);

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void), void(ReflectableType::* oproperty)(OPropertyType));

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void), void(ReflectableType::* oproperty)(OPropertyType)&);

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void)&, void(ReflectableType::* oproperty)(OPropertyType));

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void)&, void(ReflectableType::* oproperty)(OPropertyType)&);

template <typename PropertyType>
constexpr auto property_pointer(PropertyType* iproperty, PropertyType* oproperty);

template <typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(* iproperty)(void), void(* oproperty)(OPropertyType))


template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType ReflectableType::* iproperty, std::nullptr_t);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void) const, std::nullptr_t);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void) const&, std::nullptr_t);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void), std::nullptr_t);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void)&, std::nullptr_t);

template <typename PropertyType>
constexpr auto property_pointer(PropertyType* iproperty, std::nullptr_t);

template <typename PropertyType>
constexpr auto property_pointer(PropertyType(* iproperty)(void), std::nullptr_t);


template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType ReflectableType::* oproperty);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType(ReflectableType::* oproperty)(void));

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType(ReflectableType::* oproperty)(void)&);
template <typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType* oproperty);

template <typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType(* oproperty)(void));

} // namespace eightrefl
```

<details>
<summary><strong>property_t traits synopsis</strong></summary>

```cpp
template <typename PropertyType>
struct xxeightrefl_property_traits;

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(void) const>;

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(void) const&>;

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(void)>;

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(void)&>;

template <typename PropertyType>
struct xxeightrefl_property_traits<void(PropertyType)>;

template <typename PropertyType>
struct xxeightrefl_property_traits<void(PropertyType)&>;

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType*>;

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(ReflectableType::*)(void) const>;

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(ReflectableType::*)(void) const&>;

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(ReflectableType::*)(void)>;

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(ReflectableType::*)(void)&>;

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<void(ReflectableType::*)(PropertyType)>;

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<void(ReflectableType::*)(PropertyType)&>;

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(*)(void)>;

template <typename PropertyType>
struct xxeightrefl_property_traits<void(*)(PropertyType)>;

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType ReflectableType::*>;


template <typename PropertyType>
struct xxeightrefl_property_is_gettable;

template <typename PropertyType>
struct xxeightrefl_property_is_settable;
```

</details>

</details>

`deleter_t` structure synopsis:

```cpp
#define DELETER(... /*reflectable_function_type*/) /*...*/


namespace eightrefl
{

struct EIGHTREFL_API deleter_t
{
    std::string const name{};
    std::function<void(std::any const& outer_context)> const call = nullptr;
    attribute_t<meta_t> meta{};
};

} // namespace eightrefl
```

<details>
<summary><strong>deleter_t advance synopsis</strong></summary>

```cpp
namespace eightrefl
{

template <typename ReflectableType>
auto handler_deleter_call(void(*)(ReflectableType*));

template <typename CustomDeleterType, typename ReflectableType>
auto handler_deleter_call(CustomDeleterType(*)(ReflectableType*));

} // namespace eightrefl
```

<details>
<summary><strong>deleter_t traits synopsis</strong></summary>

```cpp
template <typename>
struct xxeightrefl_deleter_traits;

template <typename ReturnType, typename ReflectableType>
struct xxeightrefl_deleter_traits<ReturnType(ReflectableType)>;

template <typename ReturnType, typename ReflectableType>
struct xxeightrefl_deleter_traits<ReturnType(*)(ReflectableType)>;

```

</details>

</details>

`meta_t` structure synopsis:

```cpp
#define META(external_name, ... /*meta_expression*/) /*...*/


namespace eightrefl
{

struct EIGHTREFL_API meta_t
{
    std::string const name{};
    std::any value{};
};

} // namespace eightrefl
```

</details>

---

## Quick start

**MyStruct.hpp**
```cpp
#pragma once
#include <Eightrefl/CoreDeclaration.hpp>

struct MyStruct
{
    int value = 0;
    void Print() const {}
};

// reflection declaration (in .hpp):
REFLECTABLE_DECLARATION(MyStruct)
REFLECTABLE_DECLARATION_INIT()
```

**MyStruct.cpp**
```cpp
#include "MyStruct.hpp"

#include <Eightrefl/Core.hpp>

// reflection body (in .cpp):
REFLECTABLE(MyStruct)
    FACTORY(R())
    PROPERTY(value)
    FUNCTION(Print)
REFLECTABLE_INIT()
```

**main.cpp**
```cpp
#include "MyStruct.hpp"

int main()
{
    eightrefl::type_t* type = eightrefl::global()->find("MyStruct");

    // object creation:
    std::any object = type->factory.find("MyStruct()")->call({});
    std::any context = type->context(object);  // → MyStruct*

    // set field value (non-canonical):
    type->property.find("value")->set(context, 8);

    // get field value (non-canonical):
    std::any result = type->property.find("value")->get(context);
    int value = eightrefl::forward<int>(result); // 8

    // function call:
    type->function.find("Print")->find("void() const")->call(context, {});
}
```

<details>
<summary><strong>canonical set / get </strong></summary>

```cpp
// set field value (canonical):
type->property.find("value")->set(context, eightrefl::backward<int const&>(8));
type->property.find("value")->set(context, eightrefl::backward<int&&>(8));
int value = 8;
type->property.find("value")->set(context, eightrefl::backward(value));

// get field value (canonical):
std::any result = type->property.find("value")->get(context);
int& value = eightrefl::forward<int&>(result);
int* value = eightrefl::forward<int*>(result);
```

</details>

---

## Reflection macros

### Reflection declaration

The declaration is placed in a **header file** (`.hpp`). It registers `xxeightrefl_traits<T>`.

---

#### `REFLECTABLE_DECLARATION(... /*reflectable_type*/)` and `REFLECTABLE_DECLARATION_INIT()`

Declaration for a regular (non-template) type.

```cpp
REFLECTABLE_DECLARATION(MyClass)
    // optional: REFLECTABLE_NAME, REFLECTABLE_REGISTRY, REFLECTABLE_LAZY_EVALUATE, ...
REFLECTABLE_DECLARATION_INIT()
```

**Equivalent without macro:**
```cpp
template <>
struct xxeightrefl_traits<MyClass>
{
    using R = typename ::xxeightrefl_dirty_traits<MyClass>::R;
    [[maybe_unused]] static constexpr auto xxnative_name = "MyClass";
};
```

---

#### `TEMPLATE_REFLECTABLE_DECLARATION(reflectable_type_template_header, ... /*reflectable_type_template*/)` and `REFLECTABLE_DECLARATION_INIT()`

Declaration for a template type. Automatically includes `REFLECTABLE_LAZY_EVALUATE()`.

```cpp
TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, MyBox<T>)
    REFLECTABLE_NAME("MyBox<" + eightrefl::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()
```

> If `reflectable_type_template_header` contains a comma (for example, `template <typename K, typename V>`), wrap it in parentheses: `(template <typename K, typename V>)`.

**Equivalent without macro:**
```cpp
template <typename T>
struct xxeightrefl_traits<MyBox<T>>
{
    using R = typename ::xxeightrefl_dirty_traits<MyBox<T>>::R;
    struct xxlazy_evaluate;  // inserted automatically
    static auto name() { return "MyBox<" + eightrefl::name_of<T>() + ">"; }
};
```

---

#### `CONDITIONAL_REFLECTABLE_DECLARATION(... /*reflectable_type_condition*/)` / `REFLECTABLE_DECLARATION_INIT()`

Conditional declaration via SFINAE. Suitable for an entire category of types.

```cpp
CONDITIONAL_REFLECTABLE_DECLARATION(std::is_enum_v<DirtyR>)
    REFLECTABLE_NAME(/* ... */)
REFLECTABLE_DECLARATION_INIT()
```

**Equivalent without macro:**
```cpp
template <typename DirtyR>
struct xxeightrefl_traits<DirtyR, std::enable_if_t<std::is_enum_v<DirtyR>>>
{
    using R = typename ::xxeightrefl_dirty_traits<DirtyR>::R;
    struct xxlazy_evaluate;
    static auto name() { return /*...*/; }
};
```

---

#### Helper declaration macros

| Macro | Description |
|-------|-------------|
| `REFLECTABLE_NAME(... /*reflectable_name_string*/)` | Override the type name (string literal or `std::string` expression) |
| `REFLECTABLE_REGISTRY(... /*reflectable_registry_pointer*/)` | Specify registry (default is `eightrefl::global()`) |
| `REFLECTABLE_LAZY_EVALUATE()` | Mark type as lazily reflected (automatic in template declaration) |

```cpp
REFLECTABLE_DECLARATION(MyClass)
    REFLECTABLE_NAME("my_module::MyClass")
    REFLECTABLE_REGISTRY(MyCustomRegistry())  // MyCustomRegistry() must return eightrefl::registry_t*
REFLECTABLE_DECLARATION_INIT()
```

---

### Reflection body

The body is placed in a **source file** (`.cpp`). It registers `xxeightrefl<T>`.

---

#### `REFLECTABLE(... /*reflectable_type*/)` and `REFLECTABLE_INIT()`

```cpp
REFLECTABLE(MyClass)
    FACTORY(R())
    PROPERTY(value)
    FUNCTION(Print)
REFLECTABLE_INIT()
```

**Equivalent without macro:**
```cpp
template <>
struct xxeightrefl<MyClass>
{
    using R = MyClass;
    using CleanR = typename ::xxeightrefl_dirty_traits<R>::R;

    template <class InjectionType>
    static void evaluate(InjectionType& injection)
    {
        auto xxtype = eightrefl::find_or_add_type<R>(injection);
        [[maybe_unused]] auto xxmeta = &xxtype->meta;
        /*...*/
    }

    inline static auto xxfixture = eightrefl::fixture_of<R>();
};
```

---

#### `TEMPLATE_REFLECTABLE(reflectable_type_template_header, ... /*reflectable_type_template*/)` and `REFLECTABLE_INIT()`

Body for a template type.

```cpp
TEMPLATE_REFLECTABLE(template <typename T>, MyBox<T>)
    FACTORY(R())
    PROPERTY(value)
REFLECTABLE_INIT()
```

---

#### `CONDITIONAL_REFLECTABLE(... /*reflectable_type_condition*/)` and `REFLECTABLE_INIT()`

Body for conditional reflection (SFINAE on `R`).

```cpp
CONDITIONAL_REFLECTABLE(std::is_enum_v<R>)
    FACTORY(R())
REFLECTABLE_INIT()
```

---

#### `REFLECTABLE_ACCESS()`

Placed **inside the class body** to grant access to private / protected members.

```cpp
class MyClass
{
private:
    int secret_ = 0;
    REFLECTABLE_ACCESS()  // friend xxeightrefl<MyClass>
};
```

---

### Reflection table macros

All these macros are used between `REFLECTABLE(...)` (or `TEMPLATE_REFLECTABLE(...)`, or `CONDITIONAL_REFLECTABLE(...)`) and `REFLECTABLE_INIT()`. After each one, `META(...)` can be chained.

---

#### `FACTORY(... /*reflectable_function_type*/)`

Registers a constructor. The name is formed as a function signature.

```cpp
REFLECTABLE(MyClass)
    FACTORY(R())            // MyClass()
    FACTORY(R(int))         // MyClass(int)
    FACTORY(R(R const&))    // MyClass(MyClass const&)
    FACTORY(SomeBuilder())  // custom builder type
REFLECTABLE_INIT()
```

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_factory<MyClass()>(xxtype);
eightrefl::find_or_add_factory<MyClass(int)>(xxtype);
eightrefl::find_or_add_factory<MyClass(MyClass const&)>(xxtype);
eightrefl::find_or_add_factory<SomeBuilder()>(xxtype);
```

Look-up: `type->factory.find("MyClass(int)")`.

---

#### `FUNCTION(name, ... /*reflectable_function_type*/)` or `FUNCTION_AS(external_name, internal_name, ... /*reflectable_function_type*/)`

Registers a member function or static function. `reflectable_function_type` is required for overloads or templates.

```cpp
REFLECTABLE(MyClass)
    FUNCTION(Print)                          // auto-deduce
    FUNCTION(Overload, void(int))            // specific overload
    FUNCTION(Overload, void(float))
    FUNCTION(Overload, void(int) const)
    FUNCTION(Template<int>, void())          // template function with type argument
    FUNCTION((Template<int, bool>), void())  // parentheses required for commas
    FUNCTION_AS("@wild", Print)              // custom external name
REFLECTABLE_INIT()
```

Look-up: `type->function.find("Overload")->find("void(int)")`.

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_function(xxtype, "Print", &MyClass::Print);
eightrefl::find_or_add_function(xxtype, "Overload", (void(MyClass::*)(int))&MyClass::Overload);
eightrefl::find_or_add_function(xxtype, "Overload", (void(MyClass::*)(float))&MyClass::Overload);
eightrefl::find_or_add_function(xxtype, "Overload", (void(MyClass::*)(int) const)&MyClass::Overload);
eightrefl::find_or_add_function(xxtype, "Template<int>", (void(MyClass::*)())&MyClass::Template<int>);
eightrefl::find_or_add_function(xxtype, "Template<int, bool>", (void(MyClass::*)())&MyClass::Template<int, bool>);
eightrefl::find_or_add_function(xxtype, "@wild", &MyClass::Print);
```

---

#### `EXTERNAL_FUNCTION(name, .../*reflectable_function_type*/)` or `EXTERNAL_FUNCTION_AS(external_name, internal_name, ... /*reflectable_function_type*/)`

Registers a **free function** (not a class member) in a type’s reflection table.

```cpp
void Serialize(MyClass const&);
void Internal_Serialize(MyClass const&, int flags);

REFLECTABLE(MyClass)
    EXTERNAL_FUNCTION(Serialize)
    EXTERNAL_FUNCTION_AS("Serialize", Internal_Serialize, void(MyClass const&, int))
REFLECTABLE_INIT()
```

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_function(xxtype, "Serialize", (void(*)(MyClass const&))&::Serialize);
eightrefl::find_or_add_function(xxtype, "Serialize", (void(*)(MyClass const&, int))&::Internal_Serialize);
```

---

#### `PROPERTY(name, ... /*reflectable_type_or_function_type(s)*/)` or `PROPERTY_AS(external_name, internal_iname, internal_oname, ... /*reflectable_type_or_function_type(s)*/)`

Registers a member field or accessor pair.

```cpp
REFLECTABLE(MyClass)
    PROPERTY(value)                                            // member field
    PROPERTY(Name, std::string() const, void(std::string))     // get / set accessors
    PROPERTY(Readonly)                                         // const field → set = nullptr
    PROPERTY(Writeonly, void(int))                             // set only → get = nullptr
    PROPERTY_AS("bIsActivate", IsActivated, Activate)
    PROPERTY_AS("flag", get_flag, set_flag, char const*(), void(int))
REFLECTABLE_INIT()
```

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_property(xxtype, "value", &MyClass::value, &MyClass::value);
eightrefl::find_or_add_property(xxtype, "Name", (std::string(MyClass::*) const)&MyClass::Name, (void(MyClass::*)(std::string))&MyClass::Name);
eightrefl::find_or_add_property(xxtype, "Readonly", (int const MyClass::*)&MyClass::Readonly, nullptr);
eightrefl::find_or_add_property(xxtype, "Writeonly", nullptr, (void(MyClass::*)(int))&MyClass::Writeonly);
eightrefl::find_or_add_property(xxtype, "bIsActivate", &MyClass::IsActivated, &MyClass::Activate);
eightrefl::find_or_add_property(xxtype, "flag", (char const*(MyClass::*)())&MyClass::get_flag, (void(MyClass::*)(int))&MyClass::set_flag);
```

---

#### `EXTERNAL_PROPERTY(name, ... /*reflectable_type_or_function_type(s)*/)` or `EXTERNAL_PROPERTY_AS(external_name, internal_iname, internal_oname, ... /*reflectable_type_or_function_type(s)*/)`

Registers a **global or static** variable in the reflection table.

```cpp
static int GlobalCounter = 0;

REFLECTABLE(MyClass)
    EXTERNAL_PROPERTY(GlobalCounter)
REFLECTABLE_INIT()
```

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_property(xxtype, "GlobalCounter", &::GlobalCounter);
```

---

#### `BITFIELD(name)` or `BITFIELD_AS(external_name, internal_name)`

Registers a bitfield. Since a bitfield address cannot be taken, copy lambdas are used.

```cpp
struct Flags
{
    std::uint32_t bVisible : 1;
    std::uint32_t C_Active : 1;
};

REFLECTABLE(Flags)
    BITFIELD(bVisible)
    BITFIELD_AS(C_Active, "active")
REFLECTABLE_INIT()
```

> Bitfield type is resolved as `std::decay_t<decltype(object.field)>`.

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_bitfield<std::uint32_t>
(
    xxtype,
    "bVisible",
    [](std::any const& context) -> std::any { return std::uint32_t(std::any_cast<Flags*>(context)->bVisible); },
    [](std::any const& context, std::any const& value) { std::any_cast<Flags*>(context)->bVisible = std::any_cast<std::uint32_t>(value); }
);
eightrefl::find_or_add_bitfield<std::uint32_t>
(
    xxtype,
    "active",
    [](std::any const& context) -> std::any { return std::uint32_t(std::any_cast<Flags*>(context)->C_Active); },
    [](std::any const& context, std::any const& value) { std::any_cast<Flags*>(context)->C_Active = std::any_cast<std::uint32_t>(value); }
);
```

---

#### `PARENT(... /*reflectable_parent_type*/)`

Registers a base class. Automatically adds `child_t` to the parent type entry (for reverse casting).

```cpp
REFLECTABLE(Derived)
    PARENT(Base)
    PARENT(Interface)
REFLECTABLE_INIT()
```

Up-cast: `type->parent.find("Base")->cast(derived_ctx)` → `Base*`  
Down-cast: `base_type->child.find("Derived")->cast(base_ctx)` → `Derived*`

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_parent<Derived, Base>(xxtype);
eightrefl::find_or_add_parent<Derived, Interface>(xxtype);
```

---

#### `DELETER(... /*reflectable_function_type*/)`

Registers a destructor or custom memory releaser.

```cpp
REFLECTABLE(MyClass)
    DELETER(void(R*))           // standard destructor pattern
    DELETER(CustomDeleter(R*))  // custom deleter type
REFLECTABLE_INIT()
```

Look-up: `type->deleter.find("void(MyClass*)")`.

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_deleter<void(MyClass*)>(xxtype);
eightrefl::find_or_add_deleter<CustomDeleter(MyClass*)>(xxtype);
```

---

#### `META(name, ... /*meta_expression*/)` or `META(name)` (without value)

Adds arbitrary metadata to the **previous** table element (or the type itself).

```cpp
REFLECTABLE(MyClass)
    META("DisplayName", "My Class")
    META("Version", 3)

    FACTORY(R())
        META("PostLoad", true)

    PROPERTY(health)
        META("Serializable")              // no value → std::any{}
        META("Range", std::pair{0, 100})

    FUNCTION(Fire, void(int))
        META("MinDamage", 0)
        META("MaxDamage", 100)
REFLECTABLE_INIT()
```

Look-up: `type->meta.find("Version")`, `factory->meta.find("PostLoad")`.

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_meta(*xxmeta, "DisplayName", "My Class");
eightrefl::find_or_add_meta(*xxmeta, "Version", 3);
/*...*/
```

---

## Registry (registry_t)

`registry_t` is the central `string → type_t*` lookup table.

### Why a registry is needed

- **Runtime look-up.** At runtime, you only have a string like `"MyClass"` — the registry resolves it in O(1).
- **Subsystem isolation.** Built-in types, STL, and library-internal types are stored in separate registries so the global namespace is not polluted.
- **RTTI independence.** Standard look-up is string-based. With `EIGHTREFL_RTTI_ENABLE`, `std::type_index` look-up is also available.

### Built-in registries

| Registry | Contents |
|----------|----------|
| `eightrefl::global()` | Intended for user-defined types |
| `eightrefl::builtin()` | Primitive C++ types (`int`, `float`, `void*`, qualifiers, etc.) |
| `eightrefl::standard()` | STL types — when `EIGHTREFL_STANDARD_ENABLE` is enabled |
| `eightrefl::dev()` | Library’s own types — when `EIGHTREFL_DEV_ENABLE` is enabled |

### Usage

```cpp
// type lookup:
eightrefl::type_t* type = eightrefl::global()->find("MyClass");

// Iterate all types
for (auto& [name, type] : eightrefl::global()->all) { /* ... */ }

// custom registry:
eightrefl::registry_t* myRegistry();

REFLECTABLE_DECLARATION(MyClass)
    REFLECTABLE_REGISTRY(myRegistry())
REFLECTABLE_DECLARATION_INIT()

// after init: myRegistry()->find("MyClass") != nullptr
//             eightrefl::global()->find("MyClass") == nullptr
```

### Important: static libraries

By default, the registry is populated automatically through `xxfixture`. When using **static libraries**, the linker may discard translation units without explicit references. `EIGHTREFL_BUILD_SHARED_LIBS=ON` is recommended (default).

---

## backward / forward

Functions are in `include/Eightrefl/Utility.hpp`. They handle conversion between concrete types and `std::any`.

> **Architectural principle:** all data is passed strictly **by value** or **by pointer** — even for references. A reference inside `std::any` is impossible: it is converted to a pointer. Use `backward<ValueType>(as_value)` to pack values into `std::any` (handles glvalue, xvalue, prvalue, pointers, and references), and `forward<ValueType>(as_any)` to unpack them back (typically used with values previously packed via `backward`).

### `backward<ValueType>(ValueType&& result) → std::any`

Packs a result into `std::any`.

| `ValueType` | What goes into `std::any` |
|-------------|---------------------------|
| `T` (prvalue/xvalue) | copy of `T` (implicit remove const/ref) |
| `T*` | `T*` (without const on pointer) |
| `T&` or `T const&` | `T*` (`std::addressof(result)`) |

```cpp
int glvalue = 8;
std::any as_any = eightrefl::backward(glvalue);                  // std::any stores int* (glvalue)
std::any as_any = eightrefl::backward(std::move(glvalue));       // std::any stores int (xvalue)
std::any as_any = eightrefl::backward(8);                        // std::any stores int (prvalue)

int& glvalue_reference = glvalue;
std::any as_any = eightrefl::backward(glvalue_reference);        // std::any stores int* (glvalue)

int* glvalue_pointer = &glvalue;
std::any as_any = eightrefl::backward(glvalue_pointer);          // std::any stores int** (glvalue)

int const& const_glvalue_reference = glvalue;
std::any as_any = eightrefl::backward(const_glvalue_reference);  // std::any stores int* (glvalue)

int const* const_glvalue_pointer = &glvalue;
std::any as_any = eightrefl::backward(const_glvalue_pointer);    // std::any stores int const** (glvalue)
```

### `forward<ValueType>(std::any const& object) → ValueType`

Extracts a `ValueType` value from `std::any`.

| `ValueType` | What is stored in `std::any` | Behavior |
|-------------|------------------------------|----------|
| `T` (value) | `T` (without const/ref) | `any_cast<T>(object)` — copy |
| `T*` (pointer) | `T*` (without const) | `any_cast<T*>(object)` |
| `T&` (lvalue-ref) | `T*` | `*any_cast<T*>(object)` — dereference |
| `T const&` | `T*` | `*any_cast<T*>(object)` — dereference |

```cpp
int glvalue = 8;
std::any as_any = std::make_any<int*>(&glvalue);               // glvalue
int& as_value = eightrefl::forward<int&>(as_any);              // dereference
int const& as_value = eightrefl::forward<int const&>(as_any);  // dereference + const
int* as_value = eightrefl::forward<int*>(as_any);              // pointer
int const* as_value = eightrefl::forward<int const*>(as_any);  // pointer + const

std::any as_any = std::make_any<int>(glvalue);                 // xvalue | prvalue
int as_value = eightrefl::forward<int>(as_any);                // copy
const int as_value = eightrefl::forward<int const>(as_any);    // copy + const
```

### get/set chain

```cpp
// function property example: int(), void(int)

// get: returns a value in result via eightrefl::backward
std::any result = property->get(context); // result: std::any stores T (value types) or T* (reference/pointer types)

// set: expects std::any; pass via eightrefl::backward or directly
property->set(context, 8);  // calls eightrefl::forward<int>(value) inside
```

<details>
<summary><strong>backward / forward synopsis</strong></summary>

```cpp
namespace eightrefl
{

inline namespace utility
{

template <typename ValueType>
std::any backward(ValueType&& result);

template <typename ValueType>
ValueType forward(std::any const& object);

} // inline namespace utility

} // namespace eightrefl
```

</details>

---

## Injection (injectable_t)

### Why injectable_t is needed

`injectable_t` is the base type for all injectors. It solves **extending/dispatching type metadata without modifying their reflection code**. An injector gets access to each reflection-table element during reflection and can add metadata, register handlers, and so on.

Typical use cases:
- **Serializer** — traverses the table and builds JSON/binary format.
- **Script binding** (Chai Script, Lua) — binds functions and fields to a scripting engine.
- **Validator** — checks metadata correctness.
- **Code analyzer** — gathers statistics for all reflected types.

### injectable_t structure

Override only the methods you need:

```cpp
namespace eightrefl
{

struct injectable_t
{
    template <typename DirtyReflectableType>
    void type(type_t&) {}            // on type reflection

    template <typename ReflectableType, typename DirtyReflectableParentType>
    void parent(parent_t&) {}        // on parent class registration

    template <typename ReflectableType, typename FunctionTypePointer>
    void factory(factory_t&) {}      // on constructor registration

    template <typename ReflectableType, typename FunctionTypePointer>
    void function(function_t&) {}    // on function registration

    template <typename ReflectableType, typename ITypePointer, typename OTypePointer>
    void property(property_t&) {}    // on field/accessor registration

    template <typename ReflectableType, typename BitfieldType>
    void bitfield(property_t&) {}    // on bitfield registration

    template <typename ReflectableType, typename FunctionTypePointer>
    void deleter(deleter_t&) {}      // on destructor registration

    template <typename ReflectableType, typename DirtyReflectableInjectionType>
    void injection(injection_t&) {}  // on injection registration

    template <typename ReflectableType, typename MetaType>
    void meta(meta_t&) {}            // on metadata registration
};

} // namespace eightrefl
```

### Injection (automatic)

```cpp
// to_string_injection.hpp
struct ToStringInjection : eightrefl::injectable_t
{
    template <typename ReflectableType>
    void type(eightrefl::type_t& type)
    {
        void(*hToString)(ReflectableType*) = [](ReflectableType* object) { /*...*/ };
        eightrefl::find_or_add_meta(type.meta, "to_string()", hToString);
    }
};

// to_string_injection.cpp
REFLECTABLE_DECLARATION(ToStringInjection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(MyClass)
    INJECTION(ToStringInjection)
REFLECTABLE_INIT()
```

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_injection<MyClass, ToStringInjection>(xxtype);
```

**Injection call:**
```cpp
auto injection = type->injection.find("ToStringInjection");

// inject:
auto injectable = std::make_any<ToStringInjection>();
injection->call(injection->type->context(injectable));
// same as:
ToStringInjection injectable{};
injection->call(&injectable);
```

### Injection (manual)

```cpp
struct FlagInjection : eightrefl::injectable_t
{
    template <typename ReflectableType, typename FunctionTypePointer>
    void factory(eightrefl::factory_t& factory)
    {
        eightrefl::find_or_add_meta(factory.meta, "IsDefault", factory.arguments.empty());
    }
};

REFLECTABLE_DECLARATION(FlagInjection)
REFLECTABLE_DECLARATION_INIT()
```

```cpp
// register manually after init:
auto type = eightrefl::global()->find("MyClass");
eightrefl::find_or_add_injection<MyClass, FlagInjection>(type);

// inject:
auto injection = type->injection.find("FlagInjection");
auto injectable = std::make_any<FlagInjection>();
injection->call(injection->type->context(injectable));
```

---

## Clean and Dirty reflection

### Concept

- **Clean type** (`CleanR`) — the "clean" type whose attributes are actually described in the reflection table.
- **Dirty type** — an intermediary type or alias. Used when a type cannot be deduced from template context or when re-reflecting under another name is needed.

### Problems Dirty solves

**1. Nested template types** cannot be deduced from context:
```cpp
// does not compile! Container<T>::Iterator is a dependent type:
TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, Container<T>::Iterator)
REFLECTABLE_DECLARATION_INIT()
```

**2. Reflecting typedef/using under another name.** `std::size_t` is physically `unsigned long long`, but we want the name `"std::size_t"`, not `"unsigned long long"`.

**3. Re-reflecting one type** under multiple names or in different registries.

### Macros

#### `REFLECTABLE_CLEAN(dirty_type, ... /*clean_reflectable_type*/)`

```cpp
// dirty_type → clean_reflectable_type (does not declare a new type)
REFLECTABLE_CLEAN(std_size_t, std::size_t)
```

**Equivalent without macro (simplified):**
```cpp
template <> struct xxeightrefl_dirty_traits<std_size_t> { using R = std::size_t; };
```

---

#### `REFLECTABLE_DIRTY(dirty_type, ... /*clean_reflectable_type*/)`

Declares a **new struct** `dirty_type` as a `clean_reflectable_type` wrapper and immediately registers `REFLECTABLE_CLEAN`:

```cpp
REFLECTABLE_DIRTY(std_size_t, std::size_t)

REFLECTABLE_DECLARATION(std_size_t)
    REFLECTABLE_NAME("std::size_t")
    REFLECTABLE_REGISTRY(eightrefl::builtin())
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(std_size_t)
    FACTORY(std_size_t())
    FACTORY(R(R))  // R = std_size_t → dirty → clean = size_t
REFLECTABLE_INIT()
```

**Equivalent without macro (simplified):**
```cpp
struct std_size_t : xxeightrefl_enable_dirty<std::size_t> {};
template <> struct xxeightrefl_dirty_traits<std_size_t> { using R = std::size_t; };
```

---

#### `TEMPLATE_REFLECTABLE_DIRTY(dirty_type_template_header, dirty_type, dirty_type_template, ... /*clean_reflectable_type_template*/)` or `TEMPLATE_REFLECTABLE_CLEAN(dirty_type_template_header, dirty_type_template, ... /*clean_reflectable_type_template*/)`

Template variants for nested types:

```cpp
// reflect Container<T>::Iterator via a dirty intermediary:
TEMPLATE_REFLECTABLE_DIRTY
(
    template <typename T>,
    ContainerIterator,               // new intermediary struct
    ContainerIterator<T>,            // dirty template type
    typename Container<T>::Iterator  // clean type
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, ContainerIterator<T>)
    REFLECTABLE_NAME(eightrefl::name_of<Container<T>>() + "::Iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, ContainerIterator<T>)
REFLECTABLE_INIT()

// now ContainerIterator<T> can be used in the Container<T> table:
TEMPLATE_REFLECTABLE(template <typename T>, Container<T>)
    FUNCTION(Begin, ContainerIterator<T>())
REFLECTABLE_INIT()
```

---

## Lazy Evaluate

### Problem

Reflection cannot be auto-started via `xxfixture` for template types, so it must be triggered lazily or manually.

### Solution

If a type is marked with `REFLECTABLE_LAZY_EVALUATE()` (automatic for `TEMPLATE_REFLECTABLE_DECLARATION(...)` and `CONDITIONAL_REFLECTABLE_DECLARATION(...)`), then on first access `find_or_add_type<T>()` **automatically** runs `reflectable<T>()`:

```cpp
// std::vector<T> has lazy evaluate automatically
TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, std::vector<T>)
    REFLECTABLE_NAME("std::vector<" + eightrefl::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()

// then when reflecting MyStruct:
REFLECTABLE(MyStruct)
    PROPERTY(items) // items has std::vector<int> type
    // ↑ std::vector<int> will be reflected automatically here, without explicit eightrefl::reflectable<std::vector<int>>()
REFLECTABLE_INIT()
```

> Lazy Evaluate is triggered **only once** (recursion protected by a `lock` flag in `reflectable<T>()`). Requires reflection (`REFLECTABLE(...)` or `TEMPLATE_REFLECTABLE(...)`, or `CONDITIONAL_REFLECTABLE(...)`) to be placed in a `.hpp` file.

---

## Built-in reflections

### BuiltIn (`eightrefl::builtin()`)

Included via `#include <Eightrefl/Builtin/Builtin.hpp>` (all types via derived `#include <Eightrefl/CoreDeclaration.hpp>`).

| Category | Types |
|----------|-------|
| Void | `void` |
| Nullptr | `std::nullptr_t` |
| Bool | `bool` |
| Char | `char`, `wchar_t`, `char8_t`, `char16_t`, `char32_t` |
| Integral | `signed char`, `unsigned char`, `short`, `unsigned short`, `int`, `unsigned int`, `long`, `unsigned long`, `long long`, `unsigned long long` |
| Floating | `float`, `double`, `long double` |
| Dirty integral | `std::size_t`, `std::ptrdiff_t` |
| Pointer | `T*` (template) |
| Qualifier | `T&`, `T const`, `T(&)[N]` |
| StaticArray | `T[N]` |
| Function types | `R(Args...)`, `R(Args...)&`, `R(Args...) const`, `R(Args...) const&` |

For each non-`void` type, `FACTORY(R())` and `FACTORY(R(R))` are registered.

### Standard (`eightrefl::standard()`)

Requires `EIGHTREFL_STANDARD_ENABLE`. Included individually or via `#include <Eightrefl/Standard/Standard.hpp>`.

Supported STL types: `std::vector`, `std::list`, `std::deque`, `std::forward_list`, `std::array`, `std::set`, `std::multiset`, `std::unordered_set`, `std::unordered_multiset`, `std::map`, `std::multimap`, `std::unordered_map`, `std::unordered_multimap`, `std::stack`, `std::queue`, `std::priority_queue`, `std::string`, `std::wstring`, `std::pair`, `std::tuple`, `std::variant`, `std::optional`, `std::any`, `std::function`, `std::shared_ptr`, `std::unique_ptr`, `std::weak_ptr`, `std::reference_wrapper`, `std::initializer_list`, `std::complex`, `std::bitset`, `std::type_info`, `std::type_index`, `std::allocator`, iterators, `std::char_traits`, `std::partial_ordering`, `std::weak_ordering`, `std::strong_ordering`.

With `EIGHTREFL_FULLY_ENABLE=ON`, additional constructor and method overloads are registered.

### Dev (`eightrefl::dev()`)

Reflection of the library itself. Requires `EIGHTREFL_DEV_ENABLE` and `EIGHTREFL_STANDARD_ENABLE`.

```cpp
#include <Eightrefl/Dev/Dev.hpp>
```

Reflected types: `type_t`, `registry_t`, `attribute_t<T>`, `parent_t`, `child_t`, `factory_t`, `function_t`, `property_t`, `deleter_t`, `meta_t`, `injection_t`, `injectable_t`.

This allows **metaprogrammatic** traversal of the reflection structure itself through reflection.

---

## Configuration

| Option | Default | Description |
|--------|:-------:|-------------|
| `EIGHTREFL_BUILD_SHARED_LIBS` | `ON` | Builds library as a shared (dynamic) library instead of static |
| `EIGHTREFL_FULLY_ENABLE` | `OFF` | Enables extended standard library type reflection |
| `EIGHTREFL_RTTI_ENABLE` | `OFF` | Enables runtime type information support (RTTI); allows `find(std::type_index)` lookups |
| `EIGHTREFL_STANDARD_ENABLE` | `OFF` | Enables reflection for standard library types (STL containers, utilities, etc.) |
| `EIGHTREFL_DEV_ENABLE` | `OFF` | Enables reflection of the library's own types; useful for CLI debugging and configuration |
| `EIGHTREFL_MEMBER_ENABLE` | `OFF` | Enables reflection support for data member pointers and member function pointers |
| `EIGHTREFL_CANONICAL_PROPERTY_ENABLE` | `ON` | Enables canonical property semantics for non-functional data fields: getters like `T&()`, setters like `void(T&)`; otherwise getters like `T()`, setters like `void(T)` |
| `EIGHTREFL_DEBUG_ENABLE` | `ON` | Enables additional runtime checks |
| `EIGHTREFL_BUILD_FAST_LIBS` | `OFF` | Enables high-level optimization (`-O3`) for library builds; important when using `EIGHTREFL_STANDARD_ENABLE` with `EIGHTREFL_FULLY_ENABLE` |

Compiled definitions:

| Macro | Description |
|-------|-------------|
| `EIGHTREFL_DISABLE_REFLECTION_FIXTURE` | Disable automatic `xxfixture` registration |
| `EIGHTREFL_REGISTRY_RESERVE_SIZE` | Registry reserve size (default `1024`) |
| `EIGHTREFL_ATTRIBUTE_RESERVE_SIZE` | `attribute_t` reserve size (default `8`) |

---

## Extended documentation

<details>
<summary><strong>reflection without macros</strong></summary>

Each macro is syntactic sugar over C++ template structures. Full manual version (simplified):

```cpp
// MyBaseClass.hpp
#include <Eightrefl/CoreDeclaration.hpp>

class MyBaseClass
{
};

// reflectable declaration with macro:
REFLECTABLE_DECLARATION(MyBaseClass)
REFLECTABLE_DECLARATION_INIT()
// ↑ generates:
// template <>
// struct xxeightrefl_traits<MyBaseClass>
// {
//     using R = typename ::xxeightrefl_dirty_traits<MyBaseClass>::R;
//     [[maybe_unused]] static constexpr auto xxnative_name = "MyBaseClass";
// };

// reflectable declaration without macro (manual):
template <>
struct xxeightrefl_traits<MyBaseClass>
{
    static constexpr name() { return "MyBaseClass"; }
};
```

```cpp
// MyRegistry.hpp
#include <Eightrefl/CoreDeclaration.hpp>

eightrefl::registry_t* MyRegistry();

```

```cpp
// MyClass.hpp
#include <Eightrefl/CoreDeclaration.hpp>

#include "MyBaseClass.hpp"
#include "MyRegistry.hpp"

class MyClass : public MyBaseClass
{
    int Property;

    void Function();
};

// reflectable declaration with macro:
REFLECTABLE_DECLARATION(MyClass)
    REFLECTABLE_REGISTRY()
    REFLECTABLE_NAME("my_custom_class")
REFLECTABLE_DECLARATION_INIT()
// ↑ generates:
// template <>
// struct xxeightrefl_traits<MyClass>
// {
//     using R = typename ::xxeightrefl_dirty_traits<MyClass>::R;
//     [[maybe_unused]] static constexpr auto xxnative_name = "MyClass";
//     static auto registry() { return MyRegistry(); }
//     static auto name() { return "my_custom_class"; }
// };

// reflectable declaration without macro (manual):
template <>
struct xxeightrefl_traits<MyClass>
{
    static auto registry() { return MyRegistry(); }
    static auto name() { return "my_custom_class"; }
};
```

```cpp
// MyBaseClass.cpp
#include "MyBaseClass.hpp"

#include <Eightrefl/Core.hpp>

// reflectable with macro:
REFLECTABLE(MyBaseClass)
REFLECTABLE_INIT()
// ↑ generates:
// template <>
// struct xxeightrefl<MyBaseClass>
// {
//     using R = MyBaseClass;
//     using CleanR = typename ::xxeightrefl_dirty_traits<R>::R;
//
//     template <class InjectionType>
//     static void evaluate(InjectionType& injection)
//     {
//         auto xxtype = eightrefl::find_or_add_type<R>(injection);
//         [[maybe_unused]] auto xxmeta = &xxtype->meta;
//     }
//
//     inline static auto xxfixture = eightrefl::fixture_of<R>();
// };

// reflectable without macro (manual):
template <>
struct xxeightrefl<MyBaseClass>
{
    template <class InjectionType>
    static void evaluate(InjectionType& injection)
    {
        eightrefl::find_or_add_type<MyBaseClass>(injection);
    }

    inline static auto xxfixture = eightrefl::fixture_of<MyBaseClass>();
};
```

```cpp
// MyClass.cpp
#include "MyClass.hpp"

#include <Eightrefl/Core.hpp>

// reflectable with macro:
REFLECTABLE(MyClass)
    META("Version", 1)
    PARENT(MyBaseClass)
    if constexpr (std::is_default_constructible_v<R>)
        FACTORY(R())
    DELETER(void(R*))
    PROPERTY(Property)
        META("Default", 8)
    FUNCTION(Function)
REFLECTABLE_INIT()
// ↑ generates:
// template <>
// struct xxeightrefl<MyClass>
// {
//     using R = MyClass;
//     using CleanR = typename ::xxeightrefl_dirty_traits<R>::R;
//
//     template <class InjectionType>
//     static void evaluate(InjectionType& injection)
//     {
//         auto xxtype = eightrefl::find_or_add_type<R>(injection);
//         [[maybe_unused]] auto xxmeta = &xxtype->meta;
//
//         {
//             eightrefl::find_or_add_meta<CleanR>(*xxmeta, "Version", 1, injection);
//         }
//         {
//             auto xxparent = eightrefl::find_or_add_parent<CleanR, MyBaseClass>(xxtype, injection);
//             xxmeta = &xxparent->meta;
//         }
//         if constexpr (std::is_default_constructible_v<R>)
//         {
//             auto xxfactory = eightrefl::find_or_add_factory<CleanR, R()>(xxtype, injection);
//             xxmeta = &xxfactory->meta;
//         }
//         {
//             auto xxdeleter = eightrefl::find_or_add_deleter<CleanR, void(R*)>(xxtype, injection);
//             xxmeta = &xxdeleter->meta;
//         }
//         {
//             auto xxproperty = eightrefl::find_or_add_property<CleanR>(xxtype, "Property", &R::Property, &R::Property, injection);
//             xxmeta = &xxproperty->meta;
//         }
//         {
//             eightrefl::find_or_add_meta<CleanR>(*xxmeta, "Default", 8, injection);
//         }
//         {
//             auto xxfunction = eightrefl::find_or_add_function<CleanR>(xxtype, "Function", &R::Function, injection);
//             xxmeta = &xxfunction->meta;
//         }
//     }
//
//     inline static auto xxfixture = eightrefl::fixture_of<R>();
// };

// reflectable without macro (manual):
template <>
struct xxeightrefl<MyClass>
{
    template <class InjectionType>
    static void evaluate(InjectionType& injection)
    {
        auto xxtype = eightrefl::find_or_add_type<MyClass>(injection);

        eightrefl::find_or_add_meta<MyClass>(xxtype->meta, "Version", 1, injection);
        eightrefl::find_or_add_parent<MyClass, MyBaseClass>(xxtype, injection);

        if constexpr (std::is_default_constructible_v<MyClass>)
        {
            eightrefl::find_or_add_factory<MyClass, MyClass()>(xxtype, injection);
        }

        eightrefl::find_or_add_deleter<MyClass, void(MyClass*)>(xxtype, injection);

        {
            auto xxproperty = eightrefl::find_or_add_property<CleanR>(xxtype, "Property", &MyClass::Property, &MyClass::Property, injection);
            eightrefl::find_or_add_meta<MyClass>(xxproperty->meta, "Default", 8, injection);
        }

        eightrefl::find_or_add_function<MyClass>(xxtype, "Function", &MyClass::Function, injection);
    }

    inline static auto xxfixture = eightrefl::fixture_of<MyClass>();
};
```

</details>

<details>
<summary><strong>context() — access to field pointer</strong></summary>

`property_t::context` returns a **pointer to the field itself**, unlike `get`, which returns a copy of the value or `T*` for reference types:

```cpp
auto property = type->property.find("value");

std::any object_context = type->context(object);                // MyClass*
std::any property_context = property->context(object_context);  // int* (pointer to field)
int* raw = std::any_cast<int*>(property_context);
```

Context equals `nullptr` if it cannot be deduced from the property.

</details>

<details>
<summary><strong>child_t and reverse casting</strong></summary>

When `PARENT(Base)` is used, the library automatically adds `child_t` into `Base::child`:

```cpp
// up-cast (via eightrefl::parent_t::cast)
auto parent = child->parent.find("Base");
std::any parent_context = parent->cast(child_context);  // Base*

// down-cast (via eightrefl::child_t::cast)
auto parent = eightrefl::global()->find("Base");
auto child = parent->child.find("Derived");
std::any child_context = child->cast(parent_context);  // Derived*
```

</details>

<details>
<summary><strong>name_of and helper functions</strong></summary>

```cpp
// compile-time type name:
std::string name = eightrefl::name_of<std::vector<int>>();  // "std::vector<int>"
std::string name = eightrefl::name_of<int*>();              // "int*"
std::string name = eightrefl::name_of<int const>();         // "int const"
std::string name = eightrefl::name_of<void(int, float)>();  // "void(int, float)"

// type's custom registry:
eightrefl::registry_t* registry = eightrefl::registry_of<MyClass>();

// resolve dirty → clean type (compile-time):
using CleanT = eightrefl::clean_of<DirtyType>;

// explicit reflection registration:
eightrefl::reflectable<MyClass>();

// registration + object forwarding:
auto object = eightrefl::reflectable(MyClass{});
```

</details>

<details>
<summary><strong>RTTI support</strong></summary>

With `EIGHTREFL_RTTI_ENABLE=ON`, `std::type_index` look-up is available:

```cpp
#include <typeindex>
eightrefl::type_t* type = eightrefl::global()->find(typeid(MyClass));
// useful for polymorphism: typeid(*pointer) → eightrefl::type_t*
```

</details>

<details>
<summary><strong>EIGHTREFL_DISABLE_REFLECTION_FIXTURE</strong></summary>

`REFLECTABLE_INIT()` generates `inline static auto xxfixture = eightrefl::fixture_of<R>()`, which guarantees automatic reflection during TU initialization.

Define `EIGHTREFL_DISABLE_REFLECTION_FIXTURE` to disable this and manage initialization order manually:

```cpp
eightrefl::reflectable<MyClass>();  // explicit call
eightrefl::reflectable(object);     // explicit call
```

Useful in unit tests.

</details>

<details>
<summary><strong>dynamic (runtime) type registration</strong></summary>

The library architecture allows you to dynamically register types at runtime (e.g., when loading modules or plugins) without rebuilding the main application, and to immediately access them through the reflection API.

**Example:**

Module or plugin:
```cpp
// MyType.hpp
REFLECTABLE_DECLARATION(MyType)
REFLECTABLE_DECLARATION_INIT()

// MyType.cpp
REFLECTABLE(MyType)
REFLECTABLE_INIT()
```

Main application:
```cpp
// main.cpp
#include <Eightrefl/CoreDeclaration.hpp>

extern void* LoadModule(char const* fpathnoextension);

int main()
{
    LoadModule("MyModule");

    // if the type is registered in the global registry:
    eightrefl::type_t* type = eightrefl::global()->find("MyType");

    // if in a custom plugin registry:
    // eightrefl::type_t* type = MyModuleRegistry()->find("MyType");

    if (type)
    {
        // use the reflection API
    }
}
```

</details>

---

## Auto Tests

See library testing [here](https://github.com/MathDivergent/Eightrefl/tree/main/test).

---

## Upcoming

- Add support for replacing `std::any`, `std::function`, `std::unordered_map`, and `std::string` with custom placeholder types.
- Add override support for `std::any` and `std::function` with preservation of reflected types and pointers for improved performance and ABI compatibility.
- Add minimal support for standard types such as `std::filesystem`, `std::fstream`, `std::string_view` and others, while reducing full support for standard types such as `std::string`, `std::vector`, `std::map`, `std::set` and similar.
- Include support for standard library iterators, moving from the full set to a minimal supported subset.
- Documentation expansion, new examples, advanced-level library API.
- Improve library stability with even greater automated test coverage.

---

## License

This library is an open source project licensed under: [MIT](https://opensource.org/licenses/MIT).
