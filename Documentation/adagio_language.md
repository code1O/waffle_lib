# HOW-TO `.htconfig`

based in ``ARM32`` / ``ARM64``,
`adagio` is a network configuration language, able to handle either web servers or networks (subnetting, ip protocol, traffic monitoring)


<details>

<summary><h1>Data types</h1></summary>

Likewise other languages, in `adagio` exists different types of data,
and you can differentiate it based on the characters

- **Arrays**
  
  It's defined by a `?` character

- **Options**
  
  Defined by `<?>` character.

  Tells to the program which of many options will handle, it's followed by a `depends{...}` type

  Syntax:

  ```
  <?> .variable_name -> depends{array_ptr, array_count, ...}
  ```

- **Strings**
  
  It's defined by a dollar symbol `$`

- **numerical**
  
  It's defined by `num`, detects automatically its numerical type (int, float, ...)



</details>


---

<details>

<summary><h1>Syntaxis</h1></summary>

## Including from ``.asm`` or other `.nc` files

```haskell

-- import certain functions --
include from __asm__ add_two_num, mult_two_num

-- import all --
include from myfile * 

```

## Defining functions

```haskell

start_func __some_function:
  
  num .num_variable_x -> 2
  num .num_variable_y -> 4

  num .result -> add_two_num(.num_variable_x, .num_variable_y)
  ret result

end_func

start_func oother_function:
  
  num .my_variable_x -> 6
  num .my_variable_y -> 8
  num .result -> mult_two_num(.my_variable_x, my_variable_y)
  ret .result -- returns: 48 --

end_func

```

## Calling main ``config`` function

```haskell

start_func __start_config:

  -- Hello World! this is a comment --

  $ .my_title -> "MyTitle"
  ? .my_routes -> ["/", "/HelloWorld", "/Other"]
  <?> .my_darktheme -> depends{.my_routes, 2, "/HelloWorld", "/Other"}

  mov .global_title, #.my_title
  mov .routes, #.my_routes
  mov .darktheme, #.my_darktheme


end_func

```


# Setting a TCP/IP Web Server

```haskell

start_func set_net_info:
  
  num .net_protocol -> TCP -- automatically detects as 6 --
  num .net_hostport -> 8080
  num .server_addr -> INADDR_ANY

  mov .protocol, #.net_protocol
  mov .hostport, #.net_hostport
  mov .addr, #.server_addr

end_func

start_func set_html_info:
  
  $ .http_title -> "SodaHTTP"
  ? .page_routes -> ["/", "/HelloWorld", "/login"]
  <?> .set_darktheme -> depends{.page_routes, 1, "/"}

  call set_values
  mov .global_title, #.http_title
  mov .routes, #.page_routes
  mov .darktheme #.set_darktheme


end_func

start_func __start_config:

  call set_net_info
  call set_html_info

end_func

```


</details>

---