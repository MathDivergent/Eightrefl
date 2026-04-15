# Eightrefl

![Type](https://img.shields.io/badge/type-engine%20module-%235a6770)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Platforms](https://img.shields.io/badge/platforms-Windows%20%7C%20Linux%20%7C%20macOS-red)
![Tests](https://img.shields.io/badge/tests-automated-yellow)
[![License: MIT](https://img.shields.io/badge/license-MIT-green)](https://opensource.org/license/mit)

**Eightrefl** is a reflection library for C++20 that provides full type introspection **without requiring any changes to reflected class code**. Is an external module of the [Eightgine](https://github.com/MathDivergent/Eightgine) engine.

See last stable library version 3.0.0 [here](https://github.com/MathDivergent/Eightrefl/releases).

---

## Contents

- [Core principles](#core-principles)
- [Architecture](#architecture)
  - [Data structures](#data-structures)
  - [Interaction model](#interaction-model)
- [Quick start](#quick-start)
- [Reflection macros](#reflection-macros)
  - [Reflection declaration](#reflection-declaration)
  - [Reflection body](#reflection-body)
  - [Reflection table macros](#reflection-table-macros)
- [Registry (registry_t)](#registry-registry_t)
- [forward / backward](#forward--backward)
- [Injection (injectable_t)](#injection-injectable_t)
- [Clean and Dirty reflection](#clean-and-dirty-reflection)
- [Lazy Evaluate](#lazy-evaluate)
- [Built-in reflections](#built-in-reflections)
- [CMake options](#cmake-options)
- [Extended documentation](#extended-documentation)

---

## Core principles

1. **External reflection** — no need to modify the reflected type. Reflection is described in separate external files.
2. **Declaration/definition split** — the declaration (`xxeightrefl_traits`) is placed in a `.hpp` file, while the reflection body (`xxeightrefl`) is placed in a `.cpp` file.
3. **Standard C++20** — no code generators or custom preprocessors.
4. **`std::any` as a unified carrier** — all operations on objects are performed via `std::any`, which avoids compile-time coupling to specific types.

---

## Architecture

### Data structures

Each reflected type is stored in a `type_t`, structure synopsis:

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
    registry_t& operator=(registry_t const&) = delete;
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

`attribute_t<T>` is a wrapper over `std::unordered_map<std::string, T>` with `find` / `add` functions, structure synopsis:

```cpp
namespace eightrefl
{

template <class ElementType>
struct attribute_t
{
    attribute_t();
    ElementType* find(std::string const& name);
    ElementType* add(std::string const& name, ElementType const& element);

    std::unordered_map<std::string, ElementType> all{};
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
namespace eightrefl
{

struct EIGHTREFL_API injection_t
{
    type_t* const type = nullptr;
    std::function<void(std::any const& injectable_context)> const call = nullptr;
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

template <typename ReflectableType, typename ParentReflectableType>
auto handler_parent_cast();

} // namespace eightrefl
```

</details>

`factory_t` structure synopsis:

```cpp
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
namespace eightrefl
{

struct EIGHTREFL_API function_t
{
    std::string const name{};
    std::function<std::any(std::any const& context, std::vector<std::any> const& arguments)> const call = nullptr;
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

</details>

`property_t` structure synopsis:

```cpp
namespace eightrefl
{

struct EIGHTREFL_API property_t
{
    std::string const name{};
    type_t* const type = nullptr;
    std::function<void(std::any const& context, std::any& result)> const get = nullptr;
    std::function<void(std::any const& context, std::any const& value)> const set = nullptr;
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

template <typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType iproperty, OPropertyType oproperty);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType const ReflectableType::* iproperty, std::nullptr_t);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void) const, std::nullptr_t);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void) const&, std::nullptr_t);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void), std::nullptr_t);

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void)&, std::nullptr_t);

template <typename PropertyType>
constexpr auto property_pointer(PropertyType(* iproperty)(void), std::nullptr_t);

template <typename PropertyType>
constexpr auto property_pointer(PropertyType const* iproperty, std::nullptr_t);

} // namespace eightrefl
```

</details>

`deleter_t` structure synopsis:

```cpp
namespace eightrefl
{

struct EIGHTREFL_API deleter_t
{
    std::string const name{};
    std::function<void(std::any const& context)> const call = nullptr;
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

</details>

`meta_t` structure synopsis:

```cpp
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

### Interaction model

```
C++ type  ──(REFLECTABLE_DECLARATION)──►  xxeightrefl_traits<T>   (.hpp)
                                               │  body: name, registry, evaluate, ...
                                               ▼
          ──(REFLECTABLE)──────────────►  xxeightrefl<T>          (.cpp)
                                               │  body: factories, functions,properties, parents, ...
                                               ▼
                                     registry_t::all["TypeName"] → type_t*
```

Calling `eightrefl::reflectable<T>()` runs `xxeightrefl<T>::evaluate(injectable_t{})`, which:

1. Calls `find_or_add_type<T>()` — finds or adds `type_t` in the registry.
2. Passes `type_t&` to `injection.type<T>(type)` — lets the injector extend metadata.
3. Executes `add_injections_using_keys<T>()` — automatically registers injections by numeric keys.

`xxfixture` is an `inline static` variable generated by `REFLECTABLE_INIT()` that automatically runs `reflectable<T>()` during program initialization.

<details>
<summary><strong>registration synopsis</strong></summary>

```cpp
namespace eightrefl
{

template <typename ReflectableType>
std::string name_of();

template <typename ReflectableType>
registry_t* registry_of();


template <typename ReflectableType>
using clean_of = typename ::xxeightrefl_dirty<ReflectableType>::R;


template <typename ReflectableType>
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

template <typename ReflectableType, typename ParentReflectableType>
parent_t* find_or_add_parent(type_t* type);

template <typename ReflectableType, typename ParentReflectableType,
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
                                 std::function<void(std::any const&, std::any&)> ihandler,
                                 std::function<void(std::any const&, std::any const&)> ohandler);

template <typename ReflectableType,
          typename BitfieldType,
          class InjectionType>
property_t* find_or_add_bitfield(type_t* type, std::string const& name,
                                 std::function<void(std::any const&, std::any&)> ihandler,
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

template <typename ReflectableType, class InjectionType>
injection_t* find_or_add_injection(type_t* type);


template <typename ReflectableType, std::size_t InjectionKeyValue = 0>
void add_injections_using_keys(type_t* type);

} // namespace eightrefl
```

</details>

---

## Quick start

**MyStruct.hpp**
```cpp
#pragma once
#include <Eightrefl/Core.hpp>

struct MyStruct
{
    int value = 0;
    void Print() const {}
};

// reflection declaration (in .hpp)
REFLECTABLE_DECLARATION(MyStruct)
REFLECTABLE_DECLARATION_INIT()
```

**MyStruct.cpp**
```cpp
#include "MyStruct.hpp"

// reflection body (in .cpp)
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

    // object creation
    std::any object = type->factory.find("MyStruct()")->call({});
    std::any context = type->context(object);  // → MyStruct*

    // set field value
    type->property.find("value")->set(context, std::any{8});

    // read field value
    std::any result;
    type->property.find("value")->get(context, result);
    // *std::any_cast<int*>(result) == 8

    // function call
    type->function.find("Print")->find("void() const")->call(context, {});
}
```

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
    using R = typename ::xxeightrefl_dirty<MyClass>::R;
    [[maybe_unused]] static constexpr auto xxnative_name = "MyClass";
};
```

---

#### `TEMPLATE_REFLECTABLE_DECLARATION(type_template_header, ... /*reflectable_type_template*/)` and `REFLECTABLE_DECLARATION_INIT()`

Declaration for a template type. Automatically includes `REFLECTABLE_LAZY_EVALUATE()`.

```cpp
TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, MyBox<T>)
    REFLECTABLE_NAME("MyBox<" + eightrefl::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()
```

> If `type_template_header` contains a comma (for example, `template <typename K, typename V>`), wrap it in parentheses: `(template <typename K, typename V>)`.

**Equivalent without macro:**
```cpp
template <typename T>
struct xxeightrefl_traits<MyBox<T>>
{
    using R = typename ::xxeightrefl_dirty<MyBox<T>>::R;
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
    using R = typename ::xxeightrefl_dirty<DirtyR>::R;
    struct xxlazy_evaluate;
    static auto name() { return /* ... */; }
};
```

---

#### Helper declaration macros

| Macro | Description |
|-------|-------------|
| `REFLECTABLE_NAME(... /*reflectable_name_string*/)` | Override the type name (string literal or `std::string` expression) |
| `REFLECTABLE_REGISTRY(... /*reflectable_registry_address*/)` | Specify registry (default is `eightrefl::global()`) |
| `REFLECTABLE_LAZY_EVALUATE()` | Mark type as lazily reflected (automatic in template declaration) |

```cpp
REFLECTABLE_DECLARATION(MyClass)
    REFLECTABLE_NAME("my_module::MyClass")
    REFLECTABLE_REGISTRY(MyCustomRegistry())  // MyCustomRegistry() must return registry_t*
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
    using CleanR = typename ::xxeightrefl_dirty<R>::R;

    template <class InjectionType>
    static void evaluate(InjectionType&& injection)
    {
        auto xxtype = eightrefl::find_or_add_type<R>(injection);
        [[maybe_unused]] auto xxmeta = &xxtype->meta;
        eightrefl::add_injections_using_keys<R>(xxtype);
        // FACTORY, PROPERTY, FUNCTION, ...
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

Placed **inside the class body** to grant access to private members.

```cpp
class MyClass {
private:
    int secret_ = 0;
    REFLECTABLE_ACCESS()  // friend xxeightrefl<MyClass>
};
```

---

#### `REFLECTABLE_INJECTION_KEY(injection_key, ... /*reflectable_injection_type*/)`

Registers injector type by numeric key. Automatically applied to **all** reflections that follow this macro in the same translation unit.

```cpp
REFLECTABLE_INJECTION_KEY(0, MyInjection)
```

Maximum number of keys is `EIGHTREFL_INJECTION_TRAITS_MAX_KEY_VALUE` (default `4`).

**Equivalent without macro:**
```cpp
template <>
struct xxeightrefl_injection_traits<0>
{
    using R = MyInjection;
};
```

---

### Reflection table macros

All these macros are used between `REFLECTABLE(...)` (or `TEMPLATE_REFLECTABLE(...)`, or `CONDITIONAL_REFLECTABLE(...)`) and `REFLECTABLE_INIT()`. After each one, `META(...)` can be chained.

---

#### `FACTORY(... /*function_type*/)`

Registers a constructor. The name is formed as a function signature.

```cpp
REFLECTABLE(MyClass)
    FACTORY(R())            // MyClass()
    FACTORY(R(int))         // MyClass(int)
    FACTORY(R(R const&))    // MyClass(MyClass const&)
    FACTORY(SomeBuilder())  // custom builder type
REFLECTABLE_INIT()
```

**Equivalent without macro:**
```cpp
eightrefl::find_or_add_factory<MyClass()>(xxtype);
eightrefl::find_or_add_factory<MyClass(int)>(xxtype);
eightrefl::find_or_add_factory<MyClass(MyClass const&)>(xxtype);
eightrefl::find_or_add_factory<SomeBuilder()>(xxtype);
```

Look-up: `type->factory.find("MyClass(int)")`.

---

#### `FUNCTION(name, ... /*function_type*/)` or `FUNCTION_AS(external_name, internal_name, ... /*function_type*/)`

Registers a member function or static function. `function_type` is required for overloads or templates.

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
eightrefl::find_or_add_function(xxtype, "Overload", (void(MyClass::*)(int)const)&MyClass::Overload);
eightrefl::find_or_add_function(xxtype, "Template<int>", (void(MyClass::*)())&MyClass::Template<int>);
eightrefl::find_or_add_function(xxtype, "Template<int, bool>", (void(MyClass::*)())&MyClass::Template<int, bool>);
eightrefl::find_or_add_function(xxtype, "@wild", &MyClass::Print);
```

---

#### `EXTERNAL_FUNCTION(name, .../*function_type*/)` or `EXTERNAL_FUNCTION_AS(external_name, internal_name, ... /*function_type*/)`

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

#### `PROPERTY(name, ... /*variable_type_or_function_type(s)*/)` or `PROPERTY_AS(external_name, internal_iname, internal_oname, ... /*variable_type_or_function_type(s)*/)`

Registers a member field or accessor pair.

```cpp
REFLECTABLE(MyClass)
    PROPERTY(value)                                            // member field
    PROPERTY(Name, std::string() const, void(std::string))     // get/set accessors
    PROPERTY(Readonly)                                         // const field → set = nullptr
    PROPERTY(Writeonly, void(int))                             // set only → get = nullptr
    PROPERTY_AS("bIsActivate", Activate, IsActivated)
    PROPERTY_AS("flag", setF, getS, void(int), char const*())
REFLECTABLE_INIT()
```

**Equivalent without macro (simplified):**
```cpp
eightrefl::find_or_add_property(xxtype, "value", &MyClass::value, &MyClass::value);
eightrefl::find_or_add_property(xxtype, "Name", (std::string(MyClass::*) const)&MyClass::Name, (void(MyClass::*)(std::string))&MyClass::Name);
eightrefl::find_or_add_property(xxtype, "Readonly", (int const MyClass::*)&MyClass::Readonly, nullptr);
eightrefl::find_or_add_property(xxtype, "Writeonly", nullptr, (void(MyClass::*)(int))&MyClass::Writeonly);
eightrefl::find_or_add_property(xxtype, "bIsActivate", nullptr, (void(MyClass::*)(int))&MyClass::Writeonly);
eightrefl::find_or_add_property(xxtype, "flag", (void(MyClass::*)(int))&MyClass::setF, (char const*(MyClass::*)() const)&MyClass::getS);
```

---

#### `EXTERNAL_PROPERTY(name, ... /*variable_type_or_function_type(s)*/)` or `EXTERNAL_PROPERTY_AS(external_name, internal_iname, internal_oname, ... /*variable_type_or_function_type(s)*/)`

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
    std::uint32_t visible : 1;
    std::uint32_t active : 1;
};

REFLECTABLE(Flags)
    BITFIELD(visible)
    BITFIELD(active)
REFLECTABLE_INIT()
```

> Bitfield type is resolved as `std::decay_t<decltype(object.field)>`.

---

#### `PARENT(... /*reflectable_type*/)`

Registers a base class. Automatically adds `child_t` to the parent type entry (for reverse casting).

```cpp
REFLECTABLE(Derived)
    PARENT(Base)
    PARENT(Interface)
REFLECTABLE_INIT()
```

Up-cast: `type->parent.find("Base")->cast(derived_ctx)` → `Base*`  
Down-cast: `base_type->child.find("Derived")->cast(base_ctx)` → `Derived*`

**Equivalent without macro:**
```cpp
eightrefl::find_or_add_parent<Derived, Base>(xxtype);
```

---

#### `DELETER(... /*function_type*/)`

Registers a destructor or custom memory releaser.

```cpp
REFLECTABLE(MyClass)
    DELETER(void(R*))           // standard destructor
    DELETER(CustomDeleter(R*))  // custom deleter type
REFLECTABLE_INIT()
```

Look-up: `type->deleter.find("void(MyClass*)")`.

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
// Type lookup
eightrefl::type_t* type = eightrefl::global()->find("MyClass");

// Iterate all types
for (auto& [name, type] : eightrefl::global()->all) { /* ... */ }

// Custom registry
eightrefl::registry_t* myRegistry();

REFLECTABLE_DECLARATION(MyClass)
    REFLECTABLE_REGISTRY(myRegistry())
REFLECTABLE_DECLARATION_INIT()

// After init: myRegistry()->find("MyClass") != nullptr
//             eightrefl::global()->find("MyClass") == nullptr
```

### Important: static libraries

By default, the registry is populated automatically through `xxfixture`. When using **static libraries**, the linker may discard translation units without explicit references. `EIGHTREFL_BUILD_SHARED_LIBS=ON` is recommended (default).

---

## forward / backward

Functions are in `include/Eightrefl/Utility.hpp`. They handle conversion between concrete types and `std::any`.

> **Architectural principle:** all data is passed strictly **by value** or **by pointer** — even for references. A reference inside `std::any` is impossible: it is converted to a pointer.

### `forward<ValueType>(std::any const& object) → ValueType`

Extracts a `ValueType` value from `std::any`.

| `ValueType` | What is stored in `std::any` | Behavior |
|-------------|------------------------------|----------|
| `T` (value) | `T` (without const/ref) | `any_cast<T>(object)` — copy |
| `T*` (pointer) | `T*` (without const) | `any_cast<T*>(object)` |
| `T&` (lvalue-ref) | `T*` | `*any_cast<T*>(object)` — dereference |
| `T const&` | `T*` | `*any_cast<T*>(object)` — dereference |

```cpp
std::any object = std::make_any<int>(8);
int prvalue = eightrefl::forward<int>(8);                 // copy (prvalue)
int xvalue = eightrefl::forward<int>(std::move(object));  // copy (xvalue)
int& reference = eightrefl::forward<int&>(object);        // dereference pointer (glvalue)
int* pointer = eightrefl::forward<int*>(object);          // get pointer (glvalue)
```

### `backward<ValueType>(ValueType&& result) → std::any`

Packs a result into `std::any`.

| `ValueType` | What goes into `std::any` |
|-------------|---------------------------|
| `T` (prvalue/xvalue) | copy of `T` (implicit remove const/ref) |
| `T*` | `T*` (without const on pointer) |
| `T&` or `T const&` | `T*` (`std::addressof(result)`) |

```cpp
int glvalue = 8;
std::any copy = eightrefl::backward(glvalue);                   // std::any stores int
std::any reference_as_pointer = eightrefl::backward(&glvalue);  // std::any stores int*
std::any pointer = eightrefl::backward<int&>(glvalue);          // std::any stores int*
```

### get/set chain

```cpp
// get: returns a value in result via backward
property->get(context, result);
// result: std::any stores T (value types) or T* (reference/pointer types)

// set: expects std::any; pass via backward or directly
property->set(context, std::any{8});  // forward<int>(value) inside
```

<details>
<summary><strong>forward / backward synopsis</strong></summary>

```cpp
namespace eightrefl
{

inline namespace utility
{

template <typename ValueType>
ValueType forward(std::any const& object);

template <typename ValueType>
std::any backward(ValueType&& result);

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
    template <typename ReflectableType>
    void type(type_t&) {}          // on type reflection

    template <typename ReflectableType, typename ParentType>
    void parent(parent_t&) {}      // on parent class registration

    template <typename ReflectableType, typename FunctionTypePointer>
    void factory(factory_t&) {}    // on constructor registration

    template <typename ReflectableType, typename FunctionTypePointer>
    void function(function_t&) {}  // on function registration

    template <typename ReflectableType, typename ITypePointer, typename OTypePointer>
    void property(property_t&) {}  // on field/accessor registration

    template <typename ReflectableType, typename BitfieldType>
    void bitfield(property_t&) {}  // on bitfield registration

    template <typename ReflectableType, typename FunctionTypePointer>
    void deleter(deleter_t&) {}    // on destructor registration

    template <typename ReflectableType, typename MetaType>
    void meta(meta_t&) {}          // on metadata registration
};

} // namespace eightrefl
```

### Key-based injection (automatic)

Registered via `REFLECTABLE_INJECTION_KEY(...)`. Automatically applied to all reflections after this macro in the same TU:

```cpp
// my_injection.hpp
struct ToStringInjection : eightrefl::injectable_t
{
    template <typename ReflectableType>
    void type(eightrefl::type_t& type)
    {
        // add ToString to every reflected type
        void(*hToString)(ReflectableType*) = [](ReflectableType* object) { /* ... */ };
        eightrefl::find_or_add_meta(type.meta, "to_string()", hToString);
    }
};

// my_injection.cpp
REFLECTABLE_INJECTION_KEY(0, ToStringInjection)  // ← must be BEFORE REFLECTABLE below

REFLECTABLE_DECLARATION(ToStringInjection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(MyClass)
    FACTORY(R())
REFLECTABLE_INIT()
// ← type.meta.emplace("to_string()", hToString); will be called automatically
```

**Injection call:**
```cpp
auto injection = type->injection.find("ToStringInjection");
auto injectable = std::make_any<ToStringInjection>();
injection->call(injection->type->context(injectable));
```

### Injection without key (manual)

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
// Register manually after init:
auto type = eightrefl::global()->find("MyClass");
eightrefl::find_or_add_injection<MyClass, FlagInjection>(type);

// Execute:
auto injection = type->injection.find("FlagInjection");
auto injectable = std::make_any<FlagInjection>();
injection->call(injection->type->context(injectable));
```

---

## Clean and Dirty reflection

### Concept

- **Clean type** (`CleanR`) — the "clean" type whose members (`&CleanR::field`) are actually described in the reflection table.
- **Dirty type** — an intermediary type or alias. Used when a type cannot be deduced from template context or when re-reflecting under another name is needed.

### Problems Dirty solves

**1. Nested template types** cannot be deduced from context:
```cpp
// Does not compile! Container<T>::Iterator is a dependent type
TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, Container<T>::Iterator)
    // ...
REFLECTABLE_DECLARATION_INIT()
```

**2. Reflecting typedef/using under another name.** `std::size_t` is physically `unsigned long long`, but we want the name `"std::size_t"`, not `"unsigned long long"`.

**3. Re-reflecting one type** under multiple names or in different registries.

### Macros

#### `REFLECTABLE_CLEAN(dirty_type, ... /*clean_reflectable_type*/)`

```cpp
// dirty_type → clean_reflectable_type (does not declare a new type)
REFLECTABLE_CLEAN(std_size_t, std::size_t)
// ↑ Generates:
//   struct std_size_t : eightrefl::meta::inherits<std::size_t> {};
```

---

#### `REFLECTABLE_DIRTY(dirty_type, ... /*clean_reflectable_type*/)`

Declares a **new struct** `dirty_type` as a `clean_reflectable_type` wrapper and immediately registers `REFLECTABLE_CLEAN`:

```cpp
REFLECTABLE_DIRTY(std_size_t, std::size_t)
// ↑ Generates:
//   struct std_size_t : eightrefl::meta::inherits<std::size_t> {};
//   template <> struct xxeightrefl_dirty<std_size_t> { using R = std::size_t; };

REFLECTABLE_DECLARATION(std_size_t)
    REFLECTABLE_NAME("std::size_t")
    REFLECTABLE_REGISTRY(eightrefl::builtin())
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(std_size_t)
    FACTORY(std_size_t())
    FACTORY(R(R))  // R = std_size_t → dirty → clean = size_t
REFLECTABLE_INIT()
```

---

#### `TEMPLATE_REFLECTABLE_DIRTY(dirty_type_template_header, dirty_type, dirty_type_template, ... /*clean_reflectable_type_template*/)` or `TEMPLATE_REFLECTABLE_CLEAN(type_template_header, dirty_type, ... /*clean_reflectable_type_template*/)`

Template variants for nested types:

```cpp
// Reflect Container<T>::Iterator via a dirty intermediary
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

// Now ContainerIterator<T> can be used in the Container<T> table:
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

// Then when reflecting MyStruct:
REFLECTABLE(MyStruct)
    PROPERTY(items, std::vector<int>)
    // ↑ std::vector<int> will be reflected automatically here,
    //   without explicit eightrefl::reflectable<std::vector<int>>()
REFLECTABLE_INIT()
```

> Lazy Evaluate is triggered **only once** (recursion protected by a `lock` flag in `reflectable<T>()`). Requires reflection (`REFLECTABLE(...)` or `TEMPLATE_REFLECTABLE(...)`, or `CONDITIONAL_REFLECTABLE(...)`) to be placed in a `.hpp` file.

---

## Built-in reflections

### BuiltIn (`eightrefl::builtin()`)

Included via `#include <Eightrefl/Core.hpp>` (always active).

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

## CMake options

| Option | Default | Description |
|--------|:-------:|-------------|
| `EIGHTREFL_BUILD_SHARED_LIBS` | `ON` | Shared/static library |
| `EIGHTREFL_FULLY_ENABLE` | `OFF` | Full STL constructor set |
| `EIGHTREFL_RTTI_ENABLE` | `OFF` | `find(std::type_index)`, `-frtti` |
| `EIGHTREFL_STANDARD_ENABLE` | `OFF` | STL reflection |
| `EIGHTREFL_DEV_ENABLE` | `OFF` | Reflection of the library itself |
| `EIGHTREFL_MEMBER_ENABLE` | `OFF` | `name_of<T R::*>()` support |
| `EIGHTREFL_DEBUG_ENABLE` | `ON` | Argument-count checks at call time |
| `EIGHTREFL_BUILD_FAST_LIBS` | `OFF` | `-O3` instead of `-O2` |

Compiled definitions:

| Macro | Description |
|-------|-------------|
| `EIGHTREFL_DISABLE_REFLECTION_FIXTURE` | Disable automatic `xxfixture` registration |
| `EIGHTREFL_REGISTRY_RESERVE_SIZE` | Registry reserve size (default `1024`) |
| `EIGHTREFL_ATTRIBUTE_RESERVE_SIZE` | `attribute_t` reserve size (default `8`) |
| `EIGHTREFL_INJECTION_TRAITS_MAX_KEY_VALUE` | Maximum number of key-based injections (default `4`) |

---

## Extended documentation

<details>
<summary><strong>Reflection without macros</strong></summary>

Each macro is syntactic sugar over C++ template structures. Full manual version (simplified):

```cpp
// MyBaseClass.hpp
class MyBaseClass
{
};

// reflectable declaration with macro:
REFLECTABLE_DECLARATION(MyBaseClass)
REFLECTABLE_DECLARATION_INIT()

// reflectable declaration without macro:
template <>
struct xxeightrefl_traits<MyBaseClass>
{
    using R = typename ::xxeightrefl_dirty<MyBaseClass>::R;
    [[maybe_unused]] static constexpr auto xxnative_name = "MyBaseClass";
};
```

```cpp
// MyRegistry.hpp
eightrefl::registry_t* MyRegistry();

```

```cpp
// MyClass.hpp
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

// reflectable declaration without macro:
template <>
struct xxeightrefl_traits<MyClass>
{
    using R = typename ::xxeightrefl_dirty<MyClass>::R;
    [[maybe_unused]] static constexpr auto xxnative_name = "MyClass";
    static auto registry() { return MyRegistry(); }
    static auto name() { return "my_custom_class"; }
};
```

```cpp
// MyBaseClass.cpp
#include "MyBaseClass.hpp"

// reflectable declaration with macro:
REFLECTABLE(MyBaseClass)
REFLECTABLE_INIT()

// reflectable declaration without macro:
template <>
struct xxeightrefl<MyBaseClass>
{
    using R = MyClass;
    using CleanR = typename ::xxeightrefl_dirty<R>::R;

    template <class InjectionType>
    static void evaluate(InjectionType&& injection)
    {
        auto xxtype = eightrefl::find_or_add_type<R>(injection);
        [[maybe_unused]] auto xxmeta = &xxtype->meta;
        eightrefl::add_injections_using_keys<CleanR>(xxtype);
    }

    inline static auto xxfixture = eightrefl::fixture_of<R>();
}
```

```cpp
// MyClass.cpp
#include "MyClass.hpp"

// reflectable declaration with macro:
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

// reflectable declaration without macro:
template <>
struct xxeightrefl<MyClass>
{
    using R = MyClass;
    using CleanR = typename ::xxeightrefl_dirty<R>::R;

    template <class InjectionType>
    static void evaluate(InjectionType&& injection)
    {
        auto xxtype = eightrefl::find_or_add_type<R>(injection);
        [[maybe_unused]] auto xxmeta = &xxtype->meta;
        eightrefl::add_injections_using_keys<CleanR>(xxtype);

        {
            eightrefl::find_or_add_meta(xxmeta, "Version", 1, injection);
        }
        {
            auto xxparent = eightrefl::find_or_add_parent<R, MyBaseClass>(xxtype, injection);
            xxmeta = &xxparent->meta;
        }
        if constexpr (std::is_default_constructible_v<R>)
        {
            auto xxfactory = eightrefl::find_or_add_factory<R()>(xxtype, injection);
            xxmeta = &xxfactory->meta;
        }
        {
            auto xxdeleter = eightrefl::find_or_add_deleter<void(R*)>(xxtype, injection);
            xxmeta = &xxdeleter->meta;
        }
        {
            auto xxproperty = eightrefl::find_or_add_property(xxtype, "Property", &R::Property, &R::Property, injection);
            xxmeta = &xxproperty->meta;
        }
        {
            eightrefl::find_or_add_meta(*xxmeta, "Default", 8, injection);
        }
        {
            auto xxfunction = eightrefl::find_or_add_function(xxtype, "Function", &R::Function, injection);
            xxmeta = &xxfunction->meta;
        }
    }

    inline static auto xxfixture = eightrefl::fixture_of<R>();
};
```

</details>

<details>
<summary><strong>Overloads and template functions</strong></summary>

```cpp
struct Foo
{
    void Bar() {}
    void Bar() const {}
    void Bar(int) {}
    void Bar(int) const {}
    template <typename T>
    void Template() {}
};

REFLECTABLE(Foo)
    FUNCTION(Bar, void())
    FUNCTION(Bar, void() const)
    FUNCTION(Bar, void(int))
    FUNCTION(Bar, void(int) const)
    FUNCTION(Template<int>, void())
    FUNCTION((Template<float, bool>), void())  // parentheses required for commas
REFLECTABLE_INIT()
```

Overload look-up:
```cpp
auto function = type->function.find("Bar")->find("void(int) const");
```

</details>

<details>
<summary><strong>context() — access to field pointer</strong></summary>

`property_t::context` returns a **pointer to the field itself**, unlike `get`, which returns a copy of the value (or `T*` for reference types):

```cpp
auto property = type->property.find("value");

std::any object_context = type->context(object);                // MyClass*
std::any property_context = property->context(object_context);  // int*  (pointer to field)
int* raw = std::any_cast<int*>(property_context);
```

Context equals `nullptr` if it cannot be deduced from the property.

</details>

<details>
<summary><strong>child_t and reverse casting</strong></summary>

When `PARENT(Base)` is used, the library automatically adds `child_t` into `Base::child`:

```cpp
// up-cast (via parent_t::cast)
auto parent = child->parent.find("Base");
std::any parent_context = parent->cast(child_context);  // Base*

// down-cast (via child_t::cast)
auto parent = eightrefl::global()->find("Base");
auto child = parent->child.find("Derived");
std::any child_context = child->cast(parent_context);  // Derived*
```

</details>

<details>
<summary><strong>name_of and helper functions</strong></summary>

```cpp
// Static type name
std::string name = eightrefl::name_of<std::vector<int>>();  // "std::vector<int>"
std::string name = eightrefl::name_of<int*>();              // "int*"
std::string name = eightrefl::name_of<int const>();         // "int const"
std::string name = eightrefl::name_of<void(int, float)>();  // "void(int, float)"

// Type's custom registry
eightrefl::registry_t* registry = eightrefl::registry_of<MyClass>();

// Resolve dirty → clean type (compile-time)
using CleanT = eightrefl::clean_of<DirtyType>;

// Explicit reflection initialization
eightrefl::reflectable<MyClass>();

// Initialization + object forwarding
auto object = eightrefl::reflectable(MyClass{});
```

</details>

<details>
<summary><strong>RTTI support</strong></summary>

With `EIGHTREFL_RTTI_ENABLE=ON`, `std::type_index` look-up is available:

```cpp
#include <typeindex>
eightrefl::type_t* type = eightrefl::global()->find(typeid(MyClass));
// useful for polymorphism: typeid(*ptr) → type_t*
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

---

## Auto Tests

See library testing [here](https://github.com/MathDivergent/Eightrefl/tree/main/test).

## License

This library is an open source project licensed under: [MIT](https://opensource.org/licenses/MIT).
